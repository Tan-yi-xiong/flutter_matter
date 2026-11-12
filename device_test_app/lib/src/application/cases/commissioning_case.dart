import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class CommissioningCase implements DeviceTestCase {
  const CommissioningCase();

  @override
  DeviceTestId get id => DeviceTestId.commissioning;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for commissioning.',
      );
    }
    final transport = context.execution.commissioningTransport;
    if (transport == null) {
      return TestCaseOutcome.failed(
        'Commissioning discovery did not select a transport.',
      );
    }
    final identity =
        context.execution.identity ??
        await ensureIdentity(context, purpose: ControllerIdentityPurpose.main);

    final timeout = context.timeoutFor(id);
    try {
      final result = await commissionTarget(
        context,
        target: context.execution.target,
        identity: identity,
        secrets: secrets,
        commissioningTransport: transport,
        timeout: timeout,
      );
      if (!result.succeeded) {
        return TestCaseOutcome.failed(
          'Commissioning returned error code ${result.errorCode}.',
        );
      }
      final nodeId = result.nodeId ?? context.targetNodeId;
      final networkTransport = result.networkTransport ?? secrets.transport;
      await context.updateExecution((execution) {
        execution.nodeId = nodeId;
        execution.networkTransport = networkTransport;
      });
      return TestCaseOutcome.passed(
        notes:
            'Commissioning completed with error code 0 over '
            '${transport.wireName}.',
      );
    } on CommissioningException catch (error) {
      return TestCaseOutcome.failed(
        'Commissioning failed with ${error.code.wireName}'
        '${error.errorCode == null ? '' : ' (code ${error.errorCode})'}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Commissioning timed out after ${timeoutLabel(timeout)}.',
      );
    }
  }
}
