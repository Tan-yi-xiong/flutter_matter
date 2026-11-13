import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

/// Rebuilds the controller runtime from its persisted credentials and
/// verifies the commissioned device accepts a fresh CASE session without
/// recommissioning.
///
/// The restart is runtime-scoped: the live controller handle is disposed and
/// recreated from the stored identity, which is the library-level behavior
/// under test. A process-level restart is an app lifecycle concern and is
/// intentionally out of scope for this validation Run.
class AppRestartCase implements DeviceTestCase {
  const AppRestartCase();

  @override
  DeviceTestId get id => DeviceTestId.appRestart;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final identity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    if (identity == null || nodeId == null) {
      return TestCaseOutcome.notRun(
        'A main controller identity and commissioned node are required.',
      );
    }

    try {
      final restartedIdentity = await context.ports.controllerIdentity.restart(
        ControllerIdentityRequest(
          runId: context.runId,
          purpose: ControllerIdentityPurpose.main,
          platform: context.controller!.platform,
        ),
      );
      if (restartedIdentity.opaqueId != identity.opaqueId) {
        return TestCaseOutcome.failed(
          'The controller identity changed across the runtime restart.',
        );
      }

      final connection = await context.ports.operationalConnection.reconnect(
        identity: restartedIdentity,
        nodeId: nodeId,
        timeout: context.timeoutFor(DeviceTestId.operationalConnect),
      );
      if (!connection.isValid) {
        return TestCaseOutcome.failed(
          'Operational reconnection was invalid after the runtime restart.',
        );
      }
      context.updateExecution((execution) {
        execution.identity = restartedIdentity;
        execution.nodeId = nodeId;
        execution.connection = connection;
      });
      return const TestCaseOutcome.passed(
        notes:
            'Controller runtime restart reconnected without recommissioning.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Controller reconnect timed out after '
        '${timeoutLabel(context.timeoutFor(DeviceTestId.operationalConnect))}.',
      );
    } on Object {
      return TestCaseOutcome.failed('Controller runtime restart failed.');
    }
  }
}
