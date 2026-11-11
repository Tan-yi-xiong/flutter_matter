import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class IpCommissioningCase implements DeviceTestCase {
  const IpCommissioningCase();

  @override
  DeviceTestId get id => DeviceTestId.ipCommissioning;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for commissioning.',
      );
    }
    if (secrets.commissioningTransport != CommissioningTransport.ip) {
      return TestCaseOutcome.failed(
        'The Run is not configured for Wi-Fi/IP commissioning.',
      );
    }
    final identity =
        context.execution.identity ??
        await ensureIdentity(context, purpose: ControllerIdentityPurpose.main);

    final timeout = context.timeoutFor(id);
    try {
      final result = await commissionTarget(
        context,
        identity: identity,
        secrets: secrets,
        timeout: timeout,
      );
      if (!result.succeeded) {
        return TestCaseOutcome.failed(
          'Commissioning returned error code ${result.errorCode}.',
        );
      }
      final nodeId = result.nodeId ?? context.targetNodeId;
      final transport = result.networkTransport ?? secrets.transport;
      await context.updateExecution((execution) {
        execution.nodeId = nodeId;
        execution.networkTransport = transport;
      });
      return TestCaseOutcome.passed(
        notes: 'Commissioning completed with error code 0 over Wi-Fi/IP.',
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
