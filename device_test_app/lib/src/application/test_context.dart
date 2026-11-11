import '../domain/domain.dart';
import 'operator_prompt.dart';
import 'ports.dart';
import 'test_timeouts.dart';

/// Mutable, in-memory details for the active run.
///
/// Only [RunExecutionContextSnapshot] is persisted. Live transport handles and
/// secrets never enter this object's snapshot.
class RunExecutionContext {
  RunExecutionContext();

  ControllerIdentity? identity;
  int? nodeId;
  NetworkTransport? networkTransport;
  BleCommissionee? target;
  OperationalConnectionLease? connection;
  OnOffState? lastOnOffState;

  RunExecutionContextSnapshot toSnapshot() => RunExecutionContextSnapshot(
    identityOpaqueId: identity?.opaqueId,
    identityPurpose: identity?.purpose,
    nodeId: nodeId,
    networkTransport: networkTransport,
    lastOnOffState: lastOnOffState,
  );

  factory RunExecutionContext.fromSnapshot(
    RunExecutionContextSnapshot snapshot,
  ) {
    final execution = RunExecutionContext()
      ..nodeId = snapshot.nodeId
      ..networkTransport = snapshot.networkTransport
      ..lastOnOffState = snapshot.lastOnOffState;
    final identityOpaqueId = snapshot.identityOpaqueId;
    final identityPurpose = snapshot.identityPurpose;
    if (identityOpaqueId != null && identityPurpose != null) {
      execution.identity = ControllerIdentity(
        opaqueId: identityOpaqueId,
        purpose: identityPurpose,
      );
    }
    return execution;
  }
}

/// The application-owned context passed to exactly one test case.
class TestContext {
  TestContext({
    required this.session,
    required this.testId,
    required this.ports,
    required this.execution,
    required this.timeouts,
    required this.targetNodeId,
    required this.secrets,
    required this.resumeCheckpoint,
    required Future<void> Function() onExecutionChanged,
    required Future<OperatorDecision> Function(OperatorPrompt prompt) onPrompt,
    required Future<void> Function(AppRestartCheckpoint checkpoint)
    onSaveAppRestartCheckpoint,
    required Future<void> Function() onClearAppRestartCheckpoint,
  }) : _onExecutionChanged = onExecutionChanged,
       _onPrompt = onPrompt,
       _onSaveAppRestartCheckpoint = onSaveAppRestartCheckpoint,
       _onClearAppRestartCheckpoint = onClearAppRestartCheckpoint;

  final RunSession session;
  final DeviceTestId testId;
  final TestPorts ports;
  final RunExecutionContext execution;
  final TestTimeouts timeouts;
  final int targetNodeId;
  final ProvisioningSecrets? secrets;
  final AppRestartCheckpoint? resumeCheckpoint;

  final Future<void> Function() _onExecutionChanged;
  final Future<OperatorDecision> Function(OperatorPrompt prompt) _onPrompt;
  final Future<void> Function(AppRestartCheckpoint checkpoint)
  _onSaveAppRestartCheckpoint;
  final Future<void> Function() _onClearAppRestartCheckpoint;

  String get runId => session.id;

  ControllerMetadata? get controller => session.controller;

  CommissioneeMetadata? get commissionee => session.commissionee;

  bool get hasProvisioningSecrets => secrets != null;

  Duration timeoutFor(DeviceTestId id) => timeouts.forTest(id);

  RequiredActor get commissioneeActionActor => RequiredActor.human;

  RequiredActor get controllerSystemActor =>
      controller?.platform == ControllerPlatform.android
      ? RequiredActor.agentAndroid
      : RequiredActor.human;

  RequiredActor get controllerAppRestartActor => controllerSystemActor;

  RequiredActor get appUiActor => RequiredActor.app;

  Future<void> updateExecution(
    void Function(RunExecutionContext execution) update,
  ) async {
    update(execution);
    await _onExecutionChanged();
  }

  Future<OperatorDecision> prompt(OperatorPrompt prompt) {
    if (prompt.testId != null && prompt.testId != testId) {
      throw ArgumentError.value(
        prompt.testId,
        'prompt.testId',
        'Prompt does not belong to the active test',
      );
    }
    return _onPrompt(prompt);
  }

  Future<void> saveAppRestartCheckpoint(AppRestartCheckpoint checkpoint) =>
      _onSaveAppRestartCheckpoint(checkpoint);

  Future<void> clearAppRestartCheckpoint() => _onClearAppRestartCheckpoint();
}
