import '../domain/domain.dart';
import 'operator_prompt.dart';

/// UI and Agent-facing lifecycle status derived from the current run.
enum RunnerStatus {
  idle,
  running,
  waitingForApp,
  waitingForAgentAndroid,
  waitingForHuman,
  passed,
  failed,
  notRun,
  stopped;

  String get wireName => switch (this) {
    RunnerStatus.idle => 'idle',
    RunnerStatus.running => 'running',
    RunnerStatus.waitingForApp => 'waiting_for_app',
    RunnerStatus.waitingForAgentAndroid => 'waiting_for_agent_android',
    RunnerStatus.waitingForHuman => 'waiting_for_human',
    RunnerStatus.passed => 'passed',
    RunnerStatus.failed => 'failed',
    RunnerStatus.notRun => 'not_run',
    RunnerStatus.stopped => 'stopped',
  };
}

enum RunnerEventType {
  runStarted,
  runResumed,
  testStarted,
  testResumed,
  testPassed,
  testFailed,
  testNotRun,
  testBlocked,
  promptRequested,
  promptResolved,
  checkpointSaved,
  checkpointCleared,
  screenshotCaptured,
  runCompleted,
  runStopped,
  persistenceFailed,
}

/// A sanitized event emitted by the runner.
class RunnerEvent {
  const RunnerEvent({
    required this.sequence,
    required this.type,
    required this.timestamp,
    required this.message,
    this.runId,
    this.testId,
    this.data = const <String, Object?>{},
  });

  final int sequence;
  final RunnerEventType type;
  final DateTime timestamp;
  final String message;
  final String? runId;
  final DeviceTestId? testId;
  final Map<String, Object?> data;

  Map<String, Object?> toJson() => <String, Object?>{
    'sequence': sequence,
    'type': type.name,
    'timestamp': timestamp.toUtc().toIso8601String(),
    'message': message,
    if (runId != null) 'run_id': runId,
    if (testId != null) 'test_id': testId!.wireName,
    if (data.isNotEmpty) 'data': data,
  };
}

/// Immutable semantic state suitable for a visible UI or Agent bridge.
class RunnerStateSnapshot {
  const RunnerStateSnapshot({
    required this.status,
    required this.updatedAt,
    this.session,
    this.activePrompt,
    this.message,
  });

  final RunnerStatus status;
  final DateTime updatedAt;
  final RunSession? session;
  final OperatorPrompt? activePrompt;
  final String? message;

  String? get runId => session?.id;

  TestProfile? get profile => session?.profile;

  RunPhase? get phase => session?.phase;

  DeviceTestId? get currentTestId =>
      activePrompt?.testId ?? session?.nextActionableTestId;

  int get completedTests => session?.terminalResultCount ?? 0;

  int get totalTests => session?.expectedTestIds.length ?? 0;

  bool get isFormalEvidenceEligible =>
      session != null &&
      session!.profile == TestProfile.full &&
      session!.allResultsTerminal;

  factory RunnerStateSnapshot.idle({required DateTime at}) =>
      RunnerStateSnapshot(status: RunnerStatus.idle, updatedAt: at);

  factory RunnerStateSnapshot.forSession({
    required RunSession session,
    required DateTime at,
    OperatorPrompt? activePrompt,
    String? message,
  }) {
    return RunnerStateSnapshot(
      status: _deriveStatus(session, activePrompt),
      updatedAt: at,
      session: session,
      activePrompt: activePrompt,
      message: message,
    );
  }

  Map<String, Object?> toJson() {
    final currentSession = session;
    return <String, Object?>{
      'status': status.wireName,
      'updated_at': updatedAt.toUtc().toIso8601String(),
      if (currentSession != null) ...<String, Object?>{
        'run_id': currentSession.id,
        'profile': currentSession.profile.wireName,
        'phase': currentSession.phase.wireName,
        'completed_tests': completedTests,
        'total_tests': totalTests,
        if (currentTestId != null) 'current_test_id': currentTestId!.wireName,
        'results': <String, Object?>{
          for (final testId in currentSession.expectedTestIds)
            testId.wireName: currentSession.results[testId]!.toJson(),
        },
      },
      if (activePrompt != null) 'active_prompt': activePrompt!.toJson(),
      if (message != null) 'message': message,
    };
  }
}

RunnerStatus _deriveStatus(RunSession session, OperatorPrompt? prompt) {
  if (prompt != null) {
    return switch (prompt.requiredActor) {
      RequiredActor.app => RunnerStatus.waitingForApp,
      RequiredActor.agentAndroid => RunnerStatus.waitingForAgentAndroid,
      RequiredActor.human => RunnerStatus.waitingForHuman,
    };
  }
  if (session.phase == RunPhase.cancelled) {
    return RunnerStatus.stopped;
  }
  if (session.allResultsTerminal) {
    if (session.orderedResults.any(
      (result) => result.status == DeviceTestStatus.failed,
    )) {
      return RunnerStatus.failed;
    }
    if (session.orderedResults.any(
      (result) =>
          result.testId.priority == DeviceTestPriority.p0 &&
          result.status == DeviceTestStatus.notRun,
    )) {
      return RunnerStatus.notRun;
    }
    return RunnerStatus.passed;
  }
  if (session.phase == RunPhase.failed) {
    return RunnerStatus.failed;
  }
  return RunnerStatus.running;
}

/// Optional adapter hooks for UI persistence, Agent bridging, or diagnostics.
///
/// Hook failures must never fail a device test run.
abstract class RunnerHooksPort {
  const RunnerHooksPort();

  Future<void> onStateChanged(RunnerStateSnapshot state) async {}

  Future<void> onEvent(RunnerEvent event) async {}
}

class NoopRunnerHooksPort extends RunnerHooksPort {
  const NoopRunnerHooksPort();
}
