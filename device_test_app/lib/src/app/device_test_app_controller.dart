import 'dart:async';
import 'dart:convert';

import 'package:flutter/foundation.dart';
import 'package:flutter_matter/flutter_matter.dart' show DiscoveryCapability;

import '../application/application.dart';
import '../domain/domain.dart';
import '../presentation/ui_controller.dart';
import '../presentation/ui_models.dart';
import '../report/report.dart';
import 'app_ports.dart';
import 'operator_prompt_broker.dart';
import 'stable_target_node_id.dart';

/// Binds presentation intent to the resumable RunCoordinator.
///
/// The controller owns no hardware handles. It coordinates the bootstrap,
/// onboarding parser, secure secret storage, report artifacts, and the one
/// active operator prompt. State and event streams are sanitized projections
/// suitable for the Agent bridge.
class DeviceTestAppController extends ChangeNotifier
    implements DeviceTestUiController {
  DeviceTestAppController({
    required DeviceTestRunPort runner,
    required OperatorPromptBroker prompts,
    required DeviceTestBootstrapPort bootstrap,
    required ProvisioningSecretsPort secrets,
    required OnboardingPayloadReader onboardingPayloads,
    required DeviceTestReportArtifactPort reportArtifacts,
    required DeviceTestReportSharePort reportSharing,
    required String Function() runIdFactory,
    ClockPort clock = const SystemClockPort(),
    TestTimeouts timeouts = const TestTimeouts(),
    TargetNodeIdFactory? targetNodeIdFactory,
  }) : _runner = runner,
       _prompts = prompts,
       _bootstrapPort = bootstrap,
       _secrets = secrets,
       _onboardingPayloads = onboardingPayloads,
       _reportArtifacts = reportArtifacts,
       _reportSharing = reportSharing,
       _runIdFactory = runIdFactory,
       _clock = clock,
       _timeouts = timeouts,
       _targetNodeIdFactory = targetNodeIdFactory ?? _defaultTargetNodeId {
    _stateSubscription = _runner.stateStream.listen((snapshot) {
      _applyRunnerSnapshot(snapshot);
    });
    _eventSubscription = _runner.eventStream.listen(_handleRunnerEvent);
    _promptSubscription = _prompts.activePromptStream.listen((_) {
      _publishProjection();
    });
  }

  static const Object _keep = Object();
  static final JsonEncoder _jsonEncoder = const JsonEncoder.withIndent('  ');
  static const DeviceTestReportMarkdownRenderer _markdownRenderer =
      DeviceTestReportMarkdownRenderer();

  final DeviceTestRunPort _runner;
  final OperatorPromptBroker _prompts;
  final DeviceTestBootstrapPort _bootstrapPort;
  final ProvisioningSecretsPort _secrets;
  final OnboardingPayloadReader _onboardingPayloads;
  final DeviceTestReportArtifactPort _reportArtifacts;
  final DeviceTestReportSharePort _reportSharing;
  final String Function() _runIdFactory;
  final ClockPort _clock;
  final TestTimeouts _timeouts;
  final TargetNodeIdFactory _targetNodeIdFactory;

  final StreamController<DeviceTestUiState> _stateController =
      StreamController<DeviceTestUiState>.broadcast();
  final StreamController<RunnerEvent> _eventController =
      StreamController<RunnerEvent>.broadcast();

  late final StreamSubscription<RunnerStateSnapshot> _stateSubscription;
  late final StreamSubscription<RunnerEvent> _eventSubscription;
  late final StreamSubscription<OperatorPrompt?> _promptSubscription;

  DeviceTestUiState _state = const DeviceTestUiState();
  DeviceTestAppBootstrap? _bootstrap;
  RunSession? _activeSession;
  RunnerStateSnapshot? _lastRunnerSnapshot;
  RecentRunViewModel? _recentRun;
  ReportValidationViewModel _reportValidation = const ReportValidationViewModel(
    status: ReportUiValidationStatus.unavailable,
    message: 'No formal report is available yet.',
  );
  DeviceTestReportV2? _formalReport;
  ReportValidationResult? _validationResult;
  DeviceTestReportFiles? _reportFiles;
  String? _markdownContents;
  String? _secretRunId;
  String? _reportAttemptedRunId;
  Future<void>? _initialization;
  bool _runInFlight = false;
  bool _awaitingAppRestart = false;
  bool _closed = false;

  @override
  DeviceTestUiState get state => _state;

  /// Sanitized state stream for the Agent bridge and diagnostics.
  Stream<DeviceTestUiState> get stateStream => _stateController.stream;

  /// Sanitized runner events for the Agent bridge.
  Stream<RunnerEvent> get eventStream => _eventController.stream;

  /// The single active prompt stream. Queued prompts are never exposed.
  Stream<OperatorPrompt?> get promptStream => _prompts.activePromptStream;

  /// Provided to ApplicationPorts during production wiring.
  OperatorPromptPort get operatorPromptPort => _prompts;

  DeviceTestReportV2? get formalReport => _formalReport;

  ReportValidationResult? get reportValidation => _validationResult;

  DeviceTestReportFiles? get reportFiles => _reportFiles;

  Map<String, Object?>? get formalReportJson => _formalReport?.toJson();

  String? get formalReportMarkdown => _markdownContents;

  /// Runs once before the app shell is shown.
  Future<void> initialize() {
    return _initialization ??= _initialize();
  }

  Future<void> _initialize() async {
    _setState(busy: true, errorMessage: null);
    try {
      final bootstrap = await _bootstrapPort.load();
      _bootstrap = bootstrap;

      final unfinished = await _runner.loadUnfinished();
      if (unfinished != null && !unfinished.session.phase.isTerminal) {
        _activeSession = unfinished.session;
        _awaitingAppRestart =
            unfinished.appRestartCheckpoint?.stage ==
            AppRestartCheckpointStage.awaitingRestart;
        _lastRunnerSnapshot = RunnerStateSnapshot.forSession(
          session: unfinished.session,
          at: _clock.now(),
          message: 'An unfinished Run is ready to resume.',
        );
        final storedSecrets = await _secrets.load(unfinished.session.id);
        _secretRunId = storedSecrets == null ? null : unfinished.session.id;
      }

      _setState(
        busy: false,
        controllerInfo: bootstrap.controller,
        preflightChecks: bootstrap.preflightChecks,
        hasStoredSecrets: _secretRunId != null,
      );
      _publishProjection();
    } on Object {
      _setState(
        busy: false,
        errorMessage: 'Device test environment initialization failed.',
        preflightChecks: const <PreflightCheckViewModel>[
          PreflightCheckViewModel(
            id: 'bootstrap',
            label: 'App bootstrap',
            status: PreflightStatus.failed,
            detail: 'Controller information and build checks could not load.',
          ),
        ],
      );
    }
  }

  @override
  void navigate(DeviceTestScreen screen) {
    _setState(screen: screen);
  }

  @override
  Future<void> startRun(DeviceTestSetupRequest request) async {
    if (_runInFlight ||
        (_activeSession != null && !_activeSession!.phase.isTerminal)) {
      _setError('A Run is already active.');
      return;
    }
    final bootstrap = _bootstrap;
    if (bootstrap == null) {
      _setError('Controller information is not ready.');
      return;
    }
    if (bootstrap.hasBlockingChecks) {
      _setError(
        'Resolve blocking preflight checks before starting: '
        '${bootstrap.blockingCheckIds.join(', ')}.',
      );
      return;
    }

    final safetyIssues = _deviceRunSafetyIssues(request);
    if (safetyIssues.isNotEmpty) {
      _setError(
        'Device runs require a real Matter commissionee, IP commissioning '
        'transport, and Wi-Fi network transport. ${safetyIssues.join(' ')}',
      );
      return;
    }

    _setState(busy: true, errorMessage: null);
    try {
      final setupCode = request.setupCode.trim();
      final payload = await _onboardingPayloads.parse(setupCode);
      final network = _networkSecret(request);
      final runId = _runIdFactory();
      final targetNodeId = _targetNodeIdFactory(runId);
      final secrets = ProvisioningSecrets(
        onboardingPayload: setupCode,
        setupPinCode: payload.setupPinCode,
        network: network,
        commissioningTransport: request.commissioningTransport,
        supportsOnNetworkDiscovery: payload.discoveryCapabilities.contains(
          DiscoveryCapability.on_network,
        ),
      );

      await _secrets.save(runId, secrets);
      _secretRunId = runId;

      final startRequest = RunStartRequest(
        runId: runId,
        profile: request.profile,
        testApp: bootstrap.testApp,
        pluginCommit: bootstrap.pluginCommit,
        controller: ControllerMetadata(
          platform: request.controller.platform,
          deviceModel: request.controller.deviceModel,
          osVersion: request.controller.osVersion,
          appBuild: request.controller.appBuild,
        ),
        commissionee: CommissioneeMetadata(
          type: request.commissioneeType,
          model: request.model.trim(),
          firmware: request.firmware.trim(),
          commissioningTransport: request.commissioningTransport,
          networkTransport: request.networkTransport,
          stateChangeMethod: request.stateChangeMethod,
          stateChangeNotes: request.stateChangeNotes.trim().isEmpty
              ? null
              : request.stateChangeNotes.trim(),
        ),
        targetNodeId: targetNodeId,
      );

      _activeSession = null;
      _lastRunnerSnapshot = null;
      _awaitingAppRestart = false;
      _formalReport = null;
      _validationResult = null;
      _reportFiles = null;
      _markdownContents = null;
      _reportAttemptedRunId = null;
      _reportValidation = const ReportValidationViewModel(
        status: ReportUiValidationStatus.unavailable,
        message: 'The formal report is available after the Run completes.',
      );
      _setState(
        screen: DeviceTestScreen.runner,
        busy: false,
        errorMessage: null,
        activeRun: null,
        prompt: null,
        results: null,
        hasStoredSecrets: true,
      );
      _runInFlight = true;
      unawaited(_launchRun(startRequest));
    } on ArgumentError {
      _setState(
        busy: false,
        errorMessage: 'The setup details could not be converted into a Run.',
      );
    } on FormatException {
      _setState(
        busy: false,
        errorMessage: 'The setup code or network credentials are invalid.',
      );
    } on Object {
      _setState(
        busy: false,
        errorMessage: 'Provisioning secrets could not be prepared.',
      );
    }
  }

  Future<void> _launchRun(RunStartRequest request) async {
    try {
      final finalState = await _runner.start(request);
      if (_activeSession?.id != request.runId) {
        _applyRunnerSnapshot(finalState);
      }
    } on RunCoordinatorException catch (error) {
      _setState(
        screen: DeviceTestScreen.setup,
        busy: false,
        errorMessage: error.message,
      );
    } on Object {
      _setState(
        screen: DeviceTestScreen.setup,
        busy: false,
        errorMessage: 'The device test Run could not be started.',
      );
    } finally {
      _runInFlight = false;
    }
  }

  @override
  Future<void> resumeActiveRun() async {
    if (_runInFlight) {
      _setError('A Run operation is already in progress.');
      return;
    }
    if (_activeSession == null) {
      _setError('No unfinished Run is available to resume.');
      return;
    }
    final bootstrap = _bootstrap;
    if (bootstrap == null || bootstrap.hasBlockingChecks) {
      _setError('Resolve blocking preflight checks before resuming the Run.');
      return;
    }

    _setState(screen: DeviceTestScreen.runner, busy: true, errorMessage: null);
    _runInFlight = true;
    unawaited(_launchResume());
  }

  Future<void> _launchResume() async {
    try {
      final finalState = await _runner.resume();
      if (finalState == null) {
        _activeSession = null;
        _lastRunnerSnapshot = null;
        _publishProjection();
        _setState(
          busy: false,
          errorMessage: 'No unfinished Run is available to resume.',
          activeRun: null,
          prompt: null,
          results: null,
        );
        return;
      }
      _setState(busy: false);
      if (_activeSession?.id != finalState.runId) {
        _applyRunnerSnapshot(finalState);
      }
    } on RunCoordinatorException catch (error) {
      _setState(busy: false, errorMessage: error.message);
    } on Object {
      _setState(
        busy: false,
        errorMessage: 'The unfinished device test Run could not be resumed.',
      );
    } finally {
      _runInFlight = false;
    }
  }

  @override
  Future<void> confirmPrompt() async {
    try {
      _prompts.confirmActive();
      _setState(errorMessage: null);
    } on StateError {
      _setError('No operator action is active.');
    }
  }

  @override
  Future<void> skipPrompt(String reason) async {
    try {
      _prompts.skipActive(reason);
      _setState(errorMessage: null);
    } on ArgumentError {
      _setError('Enter a reason before skipping the test.');
    } on StateError {
      _setError('The active operator action cannot be skipped.');
    }
  }

  @override
  Future<void> failPrompt(String reason) async {
    try {
      _prompts.failActive(reason);
      _setState(errorMessage: null);
    } on ArgumentError {
      _setError('Enter a reason before failing the test.');
    } on StateError {
      _setError('No operator action is active.');
    }
  }

  @override
  Future<void> purgeSecrets() async {
    final runId = _secretRunId ?? _activeSession?.id;
    if (runId == null) {
      _setState(hasStoredSecrets: false);
      return;
    }
    final session = _activeSession;
    if (_runInFlight &&
        session != null &&
        !session.phase.isTerminal &&
        !_awaitingAppRestart) {
      _setError('Secrets cannot be purged while the Run is active.');
      return;
    }
    _setState(busy: true, errorMessage: null);
    try {
      await _secrets.purge(runId);
      _secretRunId = null;
      _setState(busy: false, hasStoredSecrets: false);
    } on Object {
      _setState(
        busy: false,
        errorMessage: 'Stored provisioning secrets could not be purged.',
      );
    }
  }

  @override
  Future<void> shareJsonReport() => _share(DeviceTestReportShareFormat.json);

  @override
  Future<void> shareMarkdownReport() =>
      _share(DeviceTestReportShareFormat.markdown);

  Future<void> _share(DeviceTestReportShareFormat format) async {
    final files = _reportFiles;
    if (files == null || !_reportValidation.isValid) {
      _setError('A validated formal report is not available to share.');
      return;
    }
    _setState(busy: true, errorMessage: null);
    try {
      await _reportSharing.share(files, format: format);
      _setState(busy: false);
    } on Object {
      _setState(busy: false, errorMessage: 'The report could not be shared.');
    }
  }

  void _applyRunnerSnapshot(RunnerStateSnapshot snapshot) {
    if (_closed) {
      return;
    }
    _lastRunnerSnapshot = snapshot;
    final session = snapshot.session;
    if (session == null) {
      return;
    }
    _activeSession = session;
    if (session.phase.isTerminal) {
      _awaitingAppRestart = false;
    }
    _publishProjection();
    if (session.phase.isTerminal) {
      unawaited(_ensureFormalReport(session));
    }
  }

  void _handleRunnerEvent(RunnerEvent event) {
    if (_closed) {
      return;
    }
    if (!_eventController.isClosed) {
      _eventController.add(event);
    }
    if (event.type == RunnerEventType.checkpointSaved &&
        event.testId == DeviceTestId.appRestart) {
      _awaitingAppRestart = event.data['stage'] != 'awaiting_reconnect';
    } else if (event.type == RunnerEventType.checkpointCleared ||
        (event.testId == DeviceTestId.appRestart &&
            (event.type == RunnerEventType.testPassed ||
                event.type == RunnerEventType.testFailed ||
                event.type == RunnerEventType.testNotRun))) {
      _awaitingAppRestart = false;
    } else {
      return;
    }
    _publishProjection();
  }

  void _publishProjection() {
    if (_closed) {
      return;
    }
    final session = _activeSession;
    final prompt = _prompts.activePrompt;
    if (session == null) {
      _setState(
        activeRun: null,
        prompt: prompt == null ? null : _toRunnerPrompt(prompt),
        results: null,
      );
      return;
    }

    final activeRun = _toActiveRun(session, prompt);
    final results = _toResults(session);
    _setState(
      activeRun: activeRun,
      prompt: prompt == null ? null : _toRunnerPrompt(prompt),
      results: results,
      recentRun: session.phase.isTerminal ? _toRecentRun(session) : _recentRun,
    );
  }

  ActiveRunViewModel _toActiveRun(RunSession session, OperatorPrompt? prompt) {
    final snapshot = _lastRunnerSnapshot;
    final currentTestId =
        prompt?.testId ??
        (snapshot?.runId == session.id ? snapshot?.currentTestId : null) ??
        session.nextActionableTestId;
    return ActiveRunViewModel(
      runId: session.id,
      profile: session.profile,
      phase: session.phase,
      tests: <TestProgressViewModel>[
        for (final testId in session.expectedTestIds)
          _toProgress(session.results[testId]!),
      ],
      currentTestId: currentTestId,
      currentInstruction: prompt?.instructions ?? snapshot?.message,
      currentTimeout: currentTestId == null
          ? null
          : _timeouts.forTest(currentTestId),
      awaitingAppRestart: _awaitingAppRestart,
    );
  }

  TestProgressViewModel _toProgress(DeviceTestResult result) {
    return TestProgressViewModel(
      testId: result.testId,
      status: result.status,
      duration: result.duration,
      notes: result.notes,
    );
  }

  RunnerPromptViewModel _toRunnerPrompt(OperatorPrompt prompt) {
    return RunnerPromptViewModel(
      id: prompt.id,
      title: prompt.title,
      instructions: prompt.instructions,
      requiredActor: prompt.requiredActor,
      testId: prompt.testId,
      confirmLabel: prompt.confirmLabel,
      canSkip: prompt.canSkip,
      skipRequiresReason: prompt.skipRequiresReason,
    );
  }

  ResultsViewModel _toResults(RunSession session) {
    final terminal = session.allResultsTerminal;
    final validation = session.profile == TestProfile.quick
        ? const ReportValidationViewModel(
            status: ReportUiValidationStatus.notApplicable,
            message: 'Quick Runs do not produce formal reports.',
          )
        : terminal
        ? _reportValidation
        : const ReportValidationViewModel(
            status: ReportUiValidationStatus.unavailable,
            message: 'The formal report is available when all tests finish.',
          );
    final filesAvailable =
        validation.isValid &&
        _reportFiles != null &&
        _activeSession?.id == session.id;
    return ResultsViewModel(
      profile: session.profile,
      tests: <TestProgressViewModel>[
        for (final testId in session.expectedTestIds)
          _toProgress(session.results[testId]!),
      ],
      summary: terminal
          ? ReportSummary.calculate(session.orderedResults)
          : null,
      validation: validation,
      jsonAvailable: filesAvailable,
      markdownAvailable: filesAvailable,
    );
  }

  RecentRunViewModel _toRecentRun(RunSession session) {
    final summary = ReportSummary.calculate(session.orderedResults);
    final recent = RecentRunViewModel(
      profile: session.profile,
      summary: summary,
      completedAt: session.updatedAt,
      formalEvidence:
          session.profile == TestProfile.full && _reportValidation.isValid,
    );
    _recentRun = recent;
    return recent;
  }

  Future<void> _ensureFormalReport(RunSession session) async {
    if (session.profile == TestProfile.quick) {
      _reportValidation = const ReportValidationViewModel(
        status: ReportUiValidationStatus.notApplicable,
        message: 'Quick Runs do not produce formal reports.',
      );
      _formalReport = null;
      _validationResult = null;
      _reportFiles = null;
      _markdownContents = null;
      _publishProjection();
      return;
    }
    if (_reportAttemptedRunId == session.id) {
      return;
    }
    _reportAttemptedRunId = session.id;
    _reportValidation = const ReportValidationViewModel(
      status: ReportUiValidationStatus.unavailable,
      message: 'Validating the formal report.',
    );
    _publishProjection();

    try {
      final report = await _runner.buildFormalReport(
        generatedAt: _clock.now(),
        sanitizationReviewed: true,
      );
      if (report == null) {
        _setReportInvalid(
          'The Run did not produce a formal full-profile report.',
        );
        return;
      }

      final jsonContents = _jsonEncoder.convert(report.toJson());
      final markdownContents = _markdownRenderer.render(report);
      final schema = await _reportArtifacts.loadCanonicalSchema();
      final validation = DeviceTestReportValidator.fromSchemaJson(
        schema,
      ).validateJson(jsonContents);
      _validationResult = validation;
      if (!validation.isValid) {
        _setReportInvalid(
          'The formal report failed schema or semantic validation.',
          issues: validation.issues.map((issue) => issue.toString()),
        );
        return;
      }

      final files = await _reportArtifacts.write(
        runId: session.id,
        jsonContents: jsonContents,
        markdownContents: markdownContents,
      );
      _formalReport = report;
      _reportFiles = files;
      _markdownContents = markdownContents;
      _reportValidation = const ReportValidationViewModel(
        status: ReportUiValidationStatus.valid,
        message: 'The formal report is valid and ready to share.',
      );
      _publishProjection();
    } on ReportBuildException catch (error) {
      _setReportInvalid(
        'The formal report could not be built.',
        issues: error.issues,
      );
    } on Object {
      _setReportInvalid('The formal report could not be validated or written.');
    }
  }

  void _setReportInvalid(String message, {Iterable<String> issues = const []}) {
    _formalReport = null;
    _validationResult = null;
    _reportFiles = null;
    _markdownContents = null;
    _reportValidation = ReportValidationViewModel(
      status: ReportUiValidationStatus.invalid,
      message: message,
      issues: List<String>.unmodifiable(issues),
    );
    _publishProjection();
  }

  /// Defense-in-depth check enforced before any session state or secret is
  /// written. Only real commissionees commissioned over Wi-Fi/IP are allowed.
  List<String> _deviceRunSafetyIssues(DeviceTestSetupRequest request) {
    final issues = <String>[];
    if (request.commissioneeType != CommissioneeType.real) {
      issues.add('The commissionee type must be real.');
    }
    if (request.commissioningTransport != CommissioningTransport.ip) {
      issues.add('The commissioning transport must be ip.');
    }
    if (request.networkTransport != NetworkTransport.wifi) {
      issues.add('The network transport must be wifi.');
    }
    return issues;
  }

  ProvisioningNetworkSecret _networkSecret(DeviceTestSetupRequest request) {
    return switch (request.networkTransport) {
      NetworkTransport.wifi => WifiProvisioningSecret(
        ssid: request.wifiSsid.trim(),
        password: request.wifiPassword,
      ),
      NetworkTransport.thread => ThreadProvisioningSecret(
        operationalDataset: _parseThreadDataset(
          request.threadOperationalDataset,
        ),
      ),
      NetworkTransport.unknown => throw const FormatException(
        'A network transport is required.',
      ),
    };
  }

  Uint8List _parseThreadDataset(String value) {
    var normalized = value.trim();
    if (normalized.toLowerCase().startsWith('0x')) {
      normalized = normalized.substring(2);
    }
    normalized = normalized.replaceAll(RegExp(r'[\s:_-]'), '');
    if (normalized.isEmpty ||
        normalized.length.isOdd ||
        !RegExp(r'^[0-9a-fA-F]+$').hasMatch(normalized)) {
      throw const FormatException(
        'Thread operational dataset must be hexadecimal.',
      );
    }
    return Uint8List.fromList(<int>[
      for (var index = 0; index < normalized.length; index += 2)
        int.parse(normalized.substring(index, index + 2), radix: 16),
    ]);
  }

  void _setError(String message, {DeviceTestScreen? screen}) {
    _setState(screen: screen, errorMessage: message);
  }

  void _setState({
    DeviceTestScreen? screen,
    bool? busy,
    Object? errorMessage = _keep,
    Object? controllerInfo = _keep,
    Object? preflightChecks = _keep,
    Object? activeRun = _keep,
    Object? prompt = _keep,
    Object? recentRun = _keep,
    Object? results = _keep,
    bool? hasStoredSecrets,
  }) {
    if (_closed) {
      return;
    }
    final next = DeviceTestUiState(
      screen: screen ?? _state.screen,
      busy: busy ?? _state.busy,
      errorMessage: identical(errorMessage, _keep)
          ? _state.errorMessage
          : errorMessage as String?,
      controllerInfo: identical(controllerInfo, _keep)
          ? _state.controllerInfo
          : controllerInfo as ControllerInfoViewModel?,
      preflightChecks: identical(preflightChecks, _keep)
          ? _state.preflightChecks
          : preflightChecks as List<PreflightCheckViewModel>,
      activeRun: identical(activeRun, _keep)
          ? _state.activeRun
          : activeRun as ActiveRunViewModel?,
      prompt: identical(prompt, _keep)
          ? _state.prompt
          : prompt as RunnerPromptViewModel?,
      recentRun: identical(recentRun, _keep)
          ? _state.recentRun
          : recentRun as RecentRunViewModel?,
      results: identical(results, _keep)
          ? _state.results
          : results as ResultsViewModel?,
      hasStoredSecrets: hasStoredSecrets ?? _state.hasStoredSecrets,
    );
    _state = next;
    notifyListeners();
    if (!_stateController.isClosed) {
      _stateController.add(next);
    }
  }

  @override
  void dispose() {
    if (_closed) {
      return;
    }
    _closed = true;
    unawaited(_closeResources());
    super.dispose();
  }

  Future<void> close() async {
    if (_closed) {
      return;
    }
    _closed = true;
    await _closeResources();
    super.dispose();
  }

  Future<void> _closeResources() async {
    await _stateSubscription.cancel();
    await _eventSubscription.cancel();
    await _promptSubscription.cancel();
    _prompts.dispose();
    await _runner.dispose();
    await _stateController.close();
    await _eventController.close();
  }
}

int _defaultTargetNodeId(String runId) {
  return const StableTargetNodeIdGenerator().call(runId);
}
