import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';

/// Converts a prompt decision into a terminal outcome when the run must stop
/// the current case. A confirmed decision returns null.
TestCaseOutcome? outcomeForPromptDecision(
  OperatorPrompt prompt,
  OperatorDecision decision,
) {
  switch (decision.status) {
    case OperatorPromptDecisionStatus.confirmed:
      return null;
    case OperatorPromptDecisionStatus.skipped:
      if (!prompt.canSkip) {
        return TestCaseOutcome.failed('${prompt.title} cannot be skipped.');
      }
      final reason = decision.reason;
      if (prompt.skipRequiresReason &&
          (reason == null || reason.trim().isEmpty)) {
        return TestCaseOutcome.failed(
          '${prompt.title} requires a skip reason.',
        );
      }
      return TestCaseOutcome.notRun(reason ?? '${prompt.title} was skipped.');
    case OperatorPromptDecisionStatus.failed:
      return TestCaseOutcome.failed(
        decision.reason ?? '${prompt.title} failed.',
      );
  }
}

Future<ControllerIdentity> ensureIdentity(
  TestContext context, {
  ControllerIdentityPurpose purpose = ControllerIdentityPurpose.main,
}) async {
  final existing = context.execution.identity;
  if (existing != null && existing.purpose == purpose) {
    return existing;
  }
  final identity = await context.ports.controllerIdentity.loadOrCreate(
    ControllerIdentityRequest(
      runId: context.runId,
      purpose: purpose,
      platform: context.controller!.platform,
    ),
  );
  await context.updateExecution((execution) {
    execution.identity = identity;
  });
  return identity;
}

/// Restores a lost in-memory operational lease after a process interruption.
///
/// A persisted run intentionally does not contain live connection handles.
/// Callers should distinguish a missing identity/node (not run) from a failed
/// reconnect (failed) using [TestContext.execution].
Future<OperationalConnectionLease?> restoreConnection(
  TestContext context,
) async {
  final existing = context.execution.connection;
  if (existing != null && existing.isValid) {
    return existing;
  }
  final identity = context.execution.identity;
  final nodeId = context.execution.nodeId;
  if (identity == null || nodeId == null) {
    return null;
  }
  final connection = await context.ports.operationalConnection.reconnect(
    identity: identity,
    nodeId: nodeId,
    timeout: context.timeoutFor(DeviceTestId.operationalConnect),
  );
  if (!connection.isValid) {
    return null;
  }
  await context.updateExecution((execution) {
    execution.connection = connection;
  });
  return connection;
}

Future<CommissioningResult> commissionTarget(
  TestContext context, {
  BleCommissionee? target,
  required ControllerIdentity identity,
  required ProvisioningSecrets secrets,
  required Duration timeout,
  int? setupPinCode,
}) {
  return context.ports.commissioning.commission(
    CommissioningRequest(
      target: target,
      identity: identity,
      targetNodeId: context.targetNodeId,
      onboardingPayload: secrets.onboardingPayload,
      setupPinCode: setupPinCode ?? secrets.setupPinCode,
      network: secrets.network,
      commissioningTransport: secrets.commissioningTransport,
      timeout: timeout,
    ),
  );
}

String timeoutLabel(Duration timeout) {
  if (timeout.inMilliseconds < 1000) {
    return '${timeout.inMilliseconds} ms';
  }
  final seconds = timeout.inMilliseconds / 1000;
  return '${seconds.toStringAsFixed(seconds == seconds.roundToDouble() ? 0 : 1)} s';
}
