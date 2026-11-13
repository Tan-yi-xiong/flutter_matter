import '../domain/domain.dart';
import 'operator_prompt.dart';
import 'ports.dart';
import 'test_timeouts.dart';

/// Mutable, in-memory details for the active run.
///
/// Runs are one-shot: this context lives only for the duration of a single
/// Run and is never persisted or restored.
class RunExecutionContext {
  RunExecutionContext();

  ControllerIdentity? identity;
  int? nodeId;
  NetworkTransport? networkTransport;
  OperationalConnectionLease? connection;
  OnOffState? lastOnOffState;
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
    required Future<OperatorDecision> Function(OperatorPrompt prompt) onPrompt,
  }) : _onPrompt = onPrompt;

  final RunSession session;
  final DeviceTestId testId;
  final TestPorts ports;
  final RunExecutionContext execution;
  final TestTimeouts timeouts;
  final int targetNodeId;
  final ProvisioningSecrets? secrets;

  final Future<OperatorDecision> Function(OperatorPrompt prompt) _onPrompt;

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

  /// Applies an execution update. The returned future resolves immediately;
  /// keeping the async shape preserves call-site compatibility across cases.
  Future<void> updateExecution(
    void Function(RunExecutionContext execution) update,
  ) async {
    update(execution);
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
}
