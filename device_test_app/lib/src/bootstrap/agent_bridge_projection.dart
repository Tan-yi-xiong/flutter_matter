import '../agent/protocol.dart';
import '../application/operator_prompt.dart';
import '../application/runner_state.dart';
import '../domain/domain.dart';
import '../presentation/ui_models.dart';
import '../report/sensitive_data_policy.dart';

/// Converts sanitized application and presentation state into protocol v1
/// messages for the Agent bridge.
class AgentBridgeProjection {
  const AgentBridgeProjection();

  AgentStatePayload projectState(DeviceTestUiState state) {
    final run = state.activeRun;
    final prompt = _projectPrompt(state.prompt);
    return AgentStatePayload(
      runId: run?.runId,
      status: _runStatus(state),
      mode: _runMode(run?.profile),
      currentTestId: run?.currentTestId?.wireName,
      completedTests: run?.completedCount ?? 0,
      totalTests: run?.totalCount ?? 0,
      message: _safeMessage(state.errorMessage ?? run?.currentInstruction),
      prompt: prompt,
      details: _stateDetails(state),
    );
  }

  AgentEventPayload projectEvent(RunnerEvent event) {
    final safeData = <String, Object?>{
      for (final entry in event.data.entries)
        if (_allowedEventDataKeys.contains(entry.key) &&
            !SensitiveDataPolicy.containsSensitiveData(entry.value))
          entry.key: entry.value,
    };
    return AgentEventPayload(
      kind: event.type.name,
      severity: _eventSeverity(event.type),
      message: _safeMessage(event.message) ?? 'Device test event.',
      testId: event.testId?.wireName,
      data: safeData,
    );
  }

  AgentRunStatus _runStatus(DeviceTestUiState state) {
    final prompt = state.prompt;
    if (prompt != null) {
      return switch (prompt.requiredActor) {
        RequiredActor.app => AgentRunStatus.waitingForApp,
        RequiredActor.agentAndroid => AgentRunStatus.waitingForAgentAndroid,
        RequiredActor.human => AgentRunStatus.waitingForHuman,
      };
    }

    final run = state.activeRun;
    if (run == null) {
      return AgentRunStatus.idle;
    }
    switch (run.phase) {
      case RunPhase.cancelled:
        return AgentRunStatus.stopped;
      case RunPhase.failed:
        return AgentRunStatus.failed;
      case RunPhase.completed:
        if (run.tests.any((test) => test.status == DeviceTestStatus.failed)) {
          return AgentRunStatus.failed;
        }
        if (run.tests.any(
          (test) =>
              test.priority == DeviceTestPriority.p0 &&
              test.status == DeviceTestStatus.notRun,
        )) {
          return AgentRunStatus.notRun;
        }
        return AgentRunStatus.passed;
      case RunPhase.idle:
      case RunPhase.preparing:
      case RunPhase.commissioning:
      case RunPhase.connecting:
      case RunPhase.testing:
      case RunPhase.awaitingOperator:
      case RunPhase.finalizing:
        return AgentRunStatus.running;
    }
  }

  AgentRunMode _runMode(TestProfile? profile) => switch (profile) {
    null => AgentRunMode.none,
    TestProfile.quick => AgentRunMode.quick,
    TestProfile.full => AgentRunMode.full,
  };

  AgentPrompt? _projectPrompt(RunnerPromptViewModel? prompt) {
    if (prompt == null || prompt.requiredActor == RequiredActor.app) {
      return null;
    }
    return AgentPrompt(
      promptId: prompt.id,
      channel: switch (prompt.requiredActor) {
        RequiredActor.agentAndroid => AgentPromptChannel.agentAndroid,
        RequiredActor.human => AgentPromptChannel.human,
        RequiredActor.app => throw StateError('App prompts are not bridged.'),
      },
      title: prompt.title,
      instructions: prompt.instructions,
      action: prompt.testId?.wireName,
      testId: prompt.testId?.wireName,
      confirmLabel: prompt.confirmLabel,
      canSkip: prompt.canSkip,
      skipRequiresReason: prompt.skipRequiresReason,
    );
  }

  Map<String, Object?> _stateDetails(DeviceTestUiState state) {
    final run = state.activeRun;
    return <String, Object?>{
      'screen': state.screen.name,
      'busy': state.busy,
      if (run != null) 'phase': run.phase.wireName,
      if (state.results != null)
        'report_validation': state.results!.validation.status.name,
      if (state.controllerInfo case final controller?)
        'controller': <String, Object?>{
          'platform': controller.platformLabel,
          'device_model': controller.deviceModel,
          'os_version': controller.osVersion,
          'app_build': controller.appBuild,
        },
      'preflight_checks': <Map<String, Object?>>[
        for (final check in state.preflightChecks)
          <String, Object?>{'id': check.id, 'status': check.status.name},
      ],
    };
  }

  String? _safeMessage(String? value) {
    final trimmed = value?.trim();
    if (trimmed == null || trimmed.isEmpty) {
      return null;
    }
    if (SensitiveDataPolicy.containsSensitiveData(trimmed)) {
      return null;
    }
    return trimmed;
  }

  AgentEventSeverity _eventSeverity(RunnerEventType type) {
    return switch (type) {
      RunnerEventType.testFailed ||
      RunnerEventType.persistenceFailed ||
      RunnerEventType.runStopped => AgentEventSeverity.error,
      RunnerEventType.testNotRun ||
      RunnerEventType.testBlocked ||
      RunnerEventType.promptResolved => AgentEventSeverity.warning,
      RunnerEventType.screenshotCaptured => AgentEventSeverity.debug,
      RunnerEventType.runStarted ||
      RunnerEventType.testStarted ||
      RunnerEventType.testPassed ||
      RunnerEventType.promptRequested ||
      RunnerEventType.runCompleted ||
      RunnerEventType.commissioneeResetConfirmed => AgentEventSeverity.info,
    };
  }

  static const Set<String> _allowedEventDataKeys = <String>{
    'stage',
    'decision',
    'profile',
    'reason_code',
    'error_code',
    'duration_ms',
    'test_id',
    'attempt',
    'phase',
    'report_status',
  };
}
