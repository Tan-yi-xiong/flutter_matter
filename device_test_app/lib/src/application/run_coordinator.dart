import 'dart:async';

import '../domain/domain.dart';
import '../report/device_test_report.dart';
import '../report/device_test_report_builder.dart';
import 'operator_prompt.dart';
import 'ports.dart';
import 'runner_state.dart';
import 'test_case.dart';
import 'test_case_registry.dart';
import 'test_context.dart';
import 'test_timeouts.dart';

class RunCoordinatorException implements Exception {
  RunCoordinatorException(this.message);

  final String message;

  @override
  String toString() => 'RunCoordinatorException: $message';
}

class RunStartRequest {
  RunStartRequest({
    required this.runId,
    required this.profile,
    required this.testApp,
    required this.pluginCommit,
    required this.controller,
    required this.commissionee,
    required this.targetNodeId,
  }) {
    if (runId.trim().isEmpty) {
      throw ArgumentError.value(runId, 'runId', 'Must not be empty');
    }
    if (targetNodeId < 1) {
      throw ArgumentError.value(
        targetNodeId,
        'targetNodeId',
        'Must be positive',
      );
    }
  }

  final String runId;
  final TestProfile profile;
  final TestAppMetadata testApp;
  final String pluginCommit;
  final ControllerMetadata controller;
  final CommissioneeMetadata commissionee;
  final int targetNodeId;
}

class _CaseTimeout implements Exception {
  const _CaseTimeout(this.timeout);
  final Duration timeout;
}

/// Executes the declarative device test sequence and persists every mutation.
class RunCoordinator {
  RunCoordinator({
    required this.ports,
    this.registry,
    this.timeouts = const TestTimeouts(),
  }) : _registry = registry ?? TestCaseRegistry.canonical(),
       _snapshot = RunnerStateSnapshot.idle(at: ports.clock.now());

  final ApplicationPorts ports;
  final TestCaseRegistry? registry;
  final TestTimeouts timeouts;
  final TestCaseRegistry _registry;

  final StreamController<RunnerStateSnapshot> _stateController =
      StreamController<RunnerStateSnapshot>.broadcast();
  final StreamController<RunnerEvent> _eventController =
      StreamController<RunnerEvent>.broadcast();

  RunSession? _session;
  RunExecutionContext _execution = RunExecutionContext();
  ProvisioningSecrets? _secrets;
  AppRestartCheckpoint? _checkpoint;
  OperatorPrompt? _activePrompt;
  RunnerStateSnapshot _snapshot;
  bool _runLoopActive = false;
  bool _stopRequested = false;
  int _eventSequence = 0;
  String? _message;

  RunnerStateSnapshot get snapshot => _snapshot;

  Stream<RunnerStateSnapshot> get stateStream => _stateController.stream;

  Stream<RunnerEvent> get eventStream => _eventController.stream;

  Future<RunnerStateSnapshot> start(RunStartRequest request) async {
    if (_runLoopActive) {
      throw RunCoordinatorException('A run is already active.');
    }
    final unfinished = await ports.persistence.loadUnfinished();
    if (unfinished != null && !unfinished.session.phase.isTerminal) {
      throw RunCoordinatorException(
        'An unfinished run must be resumed before starting a new run.',
      );
    }
    if (unfinished != null) {
      await ports.persistence.clearUnfinished();
    }

    final startedAt = ports.clock.now();
    var session = RunSession.start(
      id: request.runId,
      profile: request.profile,
      testApp: request.testApp,
      pluginCommit: request.pluginCommit,
      startedAt: startedAt,
      controller: request.controller,
      commissionee: request.commissionee,
    );
    session = _replaceSession(
      session,
      phase: RunPhase.preparing,
      updatedAt: startedAt,
      clearLastError: true,
    );

    _session = session;
    _execution = RunExecutionContext();
    _checkpoint = null;
    _activePrompt = null;
    _stopRequested = false;
    _secrets = await _loadSecrets(request.runId);
    _targetNodeId = request.targetNodeId;
    _message = 'Preparing the device test run.';
    await _persistCurrent();
    await _emitEvent(
      RunnerEventType.runStarted,
      'Started ${request.profile.wireName} device test run.',
      data: <String, Object?>{'profile': request.profile.wireName},
    );

    _runLoopActive = true;
    try {
      await _runToTerminal();
    } finally {
      _runLoopActive = false;
    }
    return _snapshot;
  }

  /// Resumes the persisted unfinished run, if one exists.
  Future<RunnerStateSnapshot?> resume() async {
    if (_runLoopActive) {
      throw RunCoordinatorException('A run is already active.');
    }
    final state = await ports.persistence.loadUnfinished();
    if (state == null) {
      return null;
    }
    if (state.session.phase.isTerminal) {
      await ports.persistence.clearUnfinished();
      return null;
    }

    _session = state.session;
    _execution = RunExecutionContext.fromSnapshot(state.execution);
    _secrets = await _loadSecrets(state.session.id);
    _checkpoint = state.appRestartCheckpoint;
    _activePrompt = null;
    _stopRequested = false;
    _targetNodeId = state.targetNodeId;

    final actionableId = state.session.nextActionableTestId;
    if (actionableId == null) {
      _message = 'Finalizing the resumed device test run.';
      await _persistCurrent();
      await _finalizeRun();
      return _snapshot;
    }

    if (state.session.results[actionableId]!.status ==
        DeviceTestStatus.running) {
      final canResumeAppRestart =
          actionableId == DeviceTestId.appRestart && _checkpoint != null;
      if (!canResumeAppRestart) {
        await _resetRunningTestToPending(actionableId);
      }
    } else if (_checkpoint != null) {
      _checkpoint = null;
    }

    final phase = _phaseForTest(actionableId);
    if (_session!.phase == RunPhase.awaitingOperator ||
        _session!.phase == RunPhase.failed) {
      _session = _replaceSession(
        _session!,
        phase: phase,
        updatedAt: ports.clock.now(),
      );
    }
    _message = 'Resuming the device test run.';
    await _persistCurrent();
    await _emitEvent(
      RunnerEventType.runResumed,
      'Resumed the unfinished ${_session!.profile.wireName} run.',
      data: <String, Object?>{'completed_tests': _session!.terminalResultCount},
    );

    _runLoopActive = true;
    try {
      await _runToTerminal();
    } finally {
      _runLoopActive = false;
    }
    return _snapshot;
  }

  /// Requests a cooperative stop. The active case is allowed to finish or
  /// time out; remaining cases are recorded as not run.
  Future<void> stop({String reason = 'Stopped by operator.'}) async {
    if (!_runLoopActive || _session == null) {
      return;
    }
    _stopRequested = true;
    _message = reason;
    await _persistCurrent();
    await _emitEvent(
      RunnerEventType.runStopped,
      reason,
      data: <String, Object?>{'requested': true},
    );
  }

  /// Builds formal evidence only for a completed full-profile run.
  ///
  /// Quick runs always return null and never produce a formal report.
  Future<DeviceTestReportV1?> buildFormalReport({
    required DateTime generatedAt,
    required bool sanitizationReviewed,
  }) async {
    final session = _session;
    if (session == null || session.profile != TestProfile.full) {
      return null;
    }
    return const DeviceTestReportBuilder().buildFormal(
      session,
      generatedAt: generatedAt,
      sanitizationReviewed: sanitizationReviewed,
    );
  }

  Future<void> dispose() async {
    await _stateController.close();
    await _eventController.close();
  }

  Future<ProvisioningSecrets?> _loadSecrets(String runId) async {
    try {
      return await ports.secrets.load(runId);
    } on Object {
      return null;
    }
  }

  Future<void> _runToTerminal() async {
    while (_session != null && !_session!.allResultsTerminal) {
      if (_stopRequested) {
        await _blockRemaining(
          'Run was stopped by the operator.',
          stopped: true,
        );
        break;
      }
      final testId = _session!.nextActionableTestId;
      if (testId == null) {
        break;
      }
      final testCase = _registry.caseFor(testId);
      await _executeCase(testCase);
      if (_stopRequested) {
        await _blockRemaining(
          'Run was stopped by the operator.',
          stopped: true,
        );
        break;
      }
      final result = _session!.results[testId]!;
      if (_shouldStopAfter(testId, result)) {
        final reason =
            '${testId.priority.label} test '
            '${testId.wireName} ${result.status.wireName}.';
        await _blockRemaining(reason);
        break;
      }
    }
    await _finalizeRun();
  }

  Future<void> _executeCase(DeviceTestCase testCase) async {
    final testId = testCase.id;
    final current = _session!;
    if (current.results[testId]!.status == DeviceTestStatus.pending) {
      _message = 'Running ${testId.title}.';
      await _setPhase(_phaseForTest(testId));
      _session = _session!.startTest(testId, at: ports.clock.now());
      await _persistCurrent();
      await _emitEvent(
        RunnerEventType.testStarted,
        'Started ${testId.wireName}.',
        testId: testId,
      );
    } else {
      _message = 'Resuming ${testId.title}.';
      await _setPhase(_phaseForTest(testId));
      await _emitEvent(
        RunnerEventType.testResumed,
        'Resumed ${testId.wireName}.',
        testId: testId,
      );
    }

    final start = ports.clock.now();
    final resumeCheckpoint = testId == DeviceTestId.appRestart
        ? _checkpoint
        : null;
    final context = TestContext(
      session: _session!,
      testId: testId,
      ports: ports.testPorts,
      execution: _execution,
      timeouts: timeouts,
      targetNodeId: _targetNodeId,
      secrets: _secrets,
      resumeCheckpoint: resumeCheckpoint,
      onExecutionChanged: _persistCurrent,
      onPrompt: (prompt) => _handlePrompt(prompt),
      onSaveAppRestartCheckpoint: _saveAppRestartCheckpoint,
      onClearAppRestartCheckpoint: _clearAppRestartCheckpoint,
    );

    TestCaseOutcome outcome;
    try {
      final timeout = timeouts.forTest(testId);
      // Give a case's own operation timeout a brief chance to report a
      // specific failure before the coordinator's safety timeout fires.
      final guardTimeout = timeout + const Duration(milliseconds: 10);
      outcome = await testCase
          .execute(context)
          .timeout(guardTimeout, onTimeout: () => throw _CaseTimeout(timeout));
    } on _CaseTimeout catch (error) {
      outcome = TestCaseOutcome.failed(
        'Timed out after ${_formatDuration(error.timeout)}.',
      );
    } on TimeoutException {
      outcome = TestCaseOutcome.failed(
        'Timed out after ${_formatDuration(timeouts.forTest(testId))}.',
      );
    } on Object catch (error) {
      outcome = TestCaseOutcome.failed(
        'Unexpected test failure (${error.runtimeType}).',
      );
    }

    final finishedAt = ports.clock.now();
    final duration = _safeDuration(start, finishedAt);
    final result = DeviceTestResult(
      testId: testId,
      status: outcome.status,
      duration: duration,
      notes: outcome.notes,
    );

    _activePrompt = null;
    if (_checkpoint != null) {
      _checkpoint = null;
    }
    _session = _replaceResultDirect(_session!, result, updatedAt: finishedAt);
    _message = _resultMessage(testId, outcome);
    await _persistCurrent();
    await _emitEvent(
      _eventTypeForOutcome(outcome),
      _resultMessage(testId, outcome),
      testId: testId,
      data: <String, Object?>{
        'status': outcome.status.wireName,
        'duration_ms': duration.inMilliseconds,
      },
    );
    if (outcome.status == DeviceTestStatus.failed ||
        outcome.status == DeviceTestStatus.notRun) {
      await _captureFailure(testId, outcome.status);
    }
  }

  Future<void> _blockRemaining(String reason, {bool stopped = false}) async {
    final session = _session;
    if (session == null || session.allResultsTerminal) {
      return;
    }
    if (session.nextActionableTestId == null) {
      return;
    }
    final blockingReason = stopped ? reason : 'Not run because $reason';
    for (final testId in session.expectedTestIds) {
      final result = _session!.results[testId]!;
      if (result.status != DeviceTestStatus.pending &&
          result.status != DeviceTestStatus.running) {
        continue;
      }
      _session = _replaceResultDirect(
        _session!,
        DeviceTestResult(
          testId: testId,
          status: DeviceTestStatus.notRun,
          notes: blockingReason,
        ),
        updatedAt: ports.clock.now(),
      );
      _message = '${testId.title} marked not run.';
      await _persistCurrent();
      await _emitEvent(
        RunnerEventType.testBlocked,
        'Marked ${testId.wireName} not run.',
        testId: testId,
        data: <String, Object?>{'reason': blockingReason},
      );
    }
    if (stopped) {
      _session = _replaceSession(
        _session!,
        phase: RunPhase.cancelled,
        updatedAt: ports.clock.now(),
      );
    } else {
      _session = _replaceSession(
        _session!,
        phase: RunPhase.failed,
        updatedAt: ports.clock.now(),
      );
    }
    await _persistCurrent();
  }

  Future<void> _finalizeRun() async {
    final session = _session;
    if (session == null) {
      return;
    }
    final allTerminal = session.allResultsTerminal;
    final hasFailed = session.orderedResults.any(
      (result) => result.status == DeviceTestStatus.failed,
    );
    final hasP0NotRun = session.orderedResults.any(
      (result) =>
          result.testId.priority == DeviceTestPriority.p0 &&
          result.status == DeviceTestStatus.notRun,
    );
    final phase = _stopRequested
        ? RunPhase.cancelled
        : hasFailed || hasP0NotRun
        ? RunPhase.failed
        : RunPhase.completed;
    _session = _replaceSession(
      session,
      phase: phase,
      updatedAt: ports.clock.now(),
    );
    _message = hasFailed
        ? 'Run finished with failures.'
        : hasP0NotRun
        ? 'Run finished with a required P0 test not run.'
        : 'Run completed successfully.';
    await _persistCurrent();
    await _emitEvent(
      _stopRequested
          ? RunnerEventType.runStopped
          : RunnerEventType.runCompleted,
      _message!,
      data: <String, Object?>{
        'all_terminal': allTerminal,
        'status': _snapshot.status.wireName,
      },
    );
    await ports.persistence.clearUnfinished();
  }

  Future<void> _resetRunningTestToPending(DeviceTestId testId) async {
    final session = _session!;
    final result = session.results[testId]!;
    _session = _replaceResultDirect(
      session,
      DeviceTestResult(testId: testId),
      updatedAt: ports.clock.now(),
    );
    _message = 'Resetting interrupted ${testId.wireName} before resume.';
    await _persistCurrent();
    if (result.status == DeviceTestStatus.running) {
      await _emitEvent(
        RunnerEventType.testResumed,
        'Reset interrupted ${testId.wireName} for a safe resume.',
        testId: testId,
      );
    }
  }

  Future<void> _setPhase(RunPhase phase) async {
    _session = _replaceSession(
      _session!,
      phase: phase,
      updatedAt: ports.clock.now(),
    );
    await _persistCurrent();
  }

  Future<void> _saveAppRestartCheckpoint(
    AppRestartCheckpoint checkpoint,
  ) async {
    if (_session == null) {
      throw RunCoordinatorException('No active run for checkpoint.');
    }
    _checkpoint = checkpoint;
    _message = 'App restart checkpoint saved.';
    await _persistCurrent();
    await _emitEvent(
      RunnerEventType.checkpointSaved,
      'Saved app restart checkpoint.',
      testId: DeviceTestId.appRestart,
      data: <String, Object?>{'stage': checkpoint.stage.wireName},
    );
  }

  Future<void> _clearAppRestartCheckpoint() async {
    if (_checkpoint == null) {
      return;
    }
    _checkpoint = null;
    _message = 'App restart checkpoint cleared.';
    await _persistCurrent();
    await _emitEvent(
      RunnerEventType.checkpointCleared,
      'Cleared app restart checkpoint.',
      testId: DeviceTestId.appRestart,
    );
  }

  Future<OperatorDecision> _handlePrompt(OperatorPrompt prompt) async {
    final session = _session;
    if (session == null) {
      throw RunCoordinatorException('No active run for prompt.');
    }
    final testId = session.nextActionableTestId;
    if (testId == null) {
      throw RunCoordinatorException('No active test for prompt.');
    }
    final effectivePrompt = prompt.testId == null
        ? prompt.copyWith(testId: testId)
        : prompt;
    _activePrompt = effectivePrompt;
    _message = effectivePrompt.title;
    await _setPhase(RunPhase.awaitingOperator);
    await _emitEvent(
      RunnerEventType.promptRequested,
      effectivePrompt.title,
      testId: testId,
      data: <String, Object?>{
        'prompt_id': effectivePrompt.id,
        'required_actor': effectivePrompt.requiredActor.wireName,
      },
    );
    try {
      final decision = await ports.operatorPrompts.request(effectivePrompt);
      _activePrompt = null;
      _message = 'Resumed after ${effectivePrompt.title}.';
      await _setPhase(_phaseForTest(testId));
      await _emitEvent(
        RunnerEventType.promptResolved,
        'Prompt resolved.',
        testId: testId,
        data: <String, Object?>{
          'prompt_id': effectivePrompt.id,
          'decision': decision.status.name,
        },
      );
      return decision;
    } on Object catch (error) {
      _activePrompt = null;
      await _setPhase(_phaseForTest(testId));
      await _emitEvent(
        RunnerEventType.promptResolved,
        'Prompt failed.',
        testId: testId,
        data: <String, Object?>{
          'prompt_id': effectivePrompt.id,
          'decision': 'failed',
          'error_type': error.runtimeType.toString(),
        },
      );
      rethrow;
    }
  }

  Future<void> _persistCurrent() async {
    final session = _session;
    if (session == null) {
      return;
    }
    final state = PersistedRunState(
      session: session,
      execution: _execution.toSnapshot(),
      targetNodeId: _targetNodeId,
      appRestartCheckpoint: _checkpoint,
      activePrompt: _activePrompt == null
          ? null
          : ActiveOperatorPromptSnapshot(
              testId: _activePrompt!.testId ?? session.nextActionableTestId!,
              prompt: _activePrompt!,
            ),
    );
    await ports.persistence.save(state);
    _snapshot = RunnerStateSnapshot.forSession(
      session: session,
      activePrompt: _activePrompt,
      at: ports.clock.now(),
      message: _message,
    );
    _stateController.add(_snapshot);
    try {
      await ports.hooks.onStateChanged(_snapshot);
    } on Object {
      // Observers must not affect device validation outcomes.
    }
  }

  Future<void> _captureFailure(
    DeviceTestId testId,
    DeviceTestStatus status,
  ) async {
    try {
      await ports.screenshot.capture(
        ScreenshotRequest(
          runId: _session!.id,
          testId: testId,
          label: status == DeviceTestStatus.failed ? 'failed' : 'not_run',
        ),
      );
      await _emitEvent(
        RunnerEventType.screenshotCaptured,
        'Requested failure screenshot.',
        testId: testId,
        data: <String, Object?>{'label': status.wireName},
      );
    } on Object {
      await _emitEvent(
        RunnerEventType.screenshotCaptured,
        'Failure screenshot request failed.',
        testId: testId,
        data: <String, Object?>{'label': status.wireName},
      );
    }
  }

  Future<void> _emitEvent(
    RunnerEventType type,
    String message, {
    DeviceTestId? testId,
    Map<String, Object?> data = const <String, Object?>{},
  }) async {
    final event = RunnerEvent(
      sequence: ++_eventSequence,
      type: type,
      timestamp: ports.clock.now(),
      message: message,
      runId: _session?.id,
      testId: testId ?? _session?.nextActionableTestId,
      data: data,
    );
    _eventController.add(event);
    try {
      await ports.hooks.onEvent(event);
    } on Object {
      // Observers must not affect device validation outcomes.
    }
  }

  bool _shouldStopAfter(DeviceTestId testId, DeviceTestResult result) {
    if (result.status != DeviceTestStatus.failed &&
        result.status != DeviceTestStatus.notRun) {
      return false;
    }
    if (testId.priority == DeviceTestPriority.p0) {
      return true;
    }
    return testId == DeviceTestId.factoryResetRecommission;
  }

  RunPhase _phaseForTest(DeviceTestId testId) => switch (testId) {
    DeviceTestId.buildInstall => RunPhase.preparing,
    DeviceTestId.bleDiscovery => RunPhase.discovering,
    DeviceTestId.bleCommissioning => RunPhase.commissioning,
    DeviceTestId.operationalConnect => RunPhase.connecting,
    _ => RunPhase.testing,
  };

  String _resultMessage(DeviceTestId testId, TestCaseOutcome outcome) {
    return switch (outcome.status) {
      DeviceTestStatus.passed => '${testId.wireName} passed.',
      DeviceTestStatus.failed => '${testId.wireName} failed.',
      DeviceTestStatus.notRun => '${testId.wireName} not run.',
      _ => '${testId.wireName} finished.',
    };
  }

  RunnerEventType _eventTypeForOutcome(TestCaseOutcome outcome) {
    return switch (outcome.status) {
      DeviceTestStatus.passed => RunnerEventType.testPassed,
      DeviceTestStatus.failed => RunnerEventType.testFailed,
      DeviceTestStatus.notRun => RunnerEventType.testNotRun,
      _ => RunnerEventType.testFailed,
    };
  }

  RunSession _replaceResultDirect(
    RunSession session,
    DeviceTestResult result, {
    required DateTime updatedAt,
  }) {
    final results = Map<DeviceTestId, DeviceTestResult>.of(session.results);
    results[result.testId] = result;
    return RunSession(
      id: session.id,
      profile: session.profile,
      testApp: session.testApp,
      pluginCommit: session.pluginCommit,
      createdAt: session.createdAt,
      updatedAt: updatedAt,
      phase: session.phase,
      controller: session.controller,
      commissionee: session.commissionee,
      lastError: session.lastError,
      results: results,
    );
  }

  RunSession _replaceSession(
    RunSession session, {
    required RunPhase phase,
    required DateTime updatedAt,
    bool clearLastError = true,
    String? lastError,
  }) {
    return RunSession(
      id: session.id,
      profile: session.profile,
      testApp: session.testApp,
      pluginCommit: session.pluginCommit,
      createdAt: session.createdAt,
      updatedAt: updatedAt,
      phase: phase,
      controller: session.controller,
      commissionee: session.commissionee,
      lastError: clearLastError ? lastError : lastError ?? session.lastError,
      results: session.results,
    );
  }

  Duration _safeDuration(DateTime start, DateTime end) {
    final duration = end.difference(start);
    return duration.isNegative ? Duration.zero : duration;
  }

  String _formatDuration(Duration duration) {
    if (duration.inMilliseconds < 1000) {
      return '${duration.inMilliseconds} ms';
    }
    final seconds = duration.inMilliseconds / 1000;
    return '${seconds.toStringAsFixed(seconds == seconds.roundToDouble() ? 0 : 1)} s';
  }

  int _targetNodeId = 1;
}
