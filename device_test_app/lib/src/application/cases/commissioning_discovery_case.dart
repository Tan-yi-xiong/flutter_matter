import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class CommissioningDiscoveryCase implements DeviceTestCase {
  const CommissioningDiscoveryCase();

  @override
  DeviceTestId get id => DeviceTestId.commissioningDiscovery;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for commissioning discovery.',
      );
    }

    try {
      final result = await context.ports.commissioningDiscovery.discover(
        CommissioningDiscoveryRequest(
          onboardingPayload: secrets.onboardingPayload,
          timeout: context.timeoutFor(id),
        ),
      );
      await context.updateExecution((execution) {
        execution.commissioningTransport = result.transport;
        execution.target = result.bleTarget;
      });
      return TestCaseOutcome.passed(
        notes: 'Matched the commissionee over ${result.transport.wireName}.',
      );
    } on CommissioningDiscoveryException catch (error) {
      return TestCaseOutcome.failed(
        'Commissioning discovery failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Commissioning discovery timed out after '
        '${timeoutLabel(context.timeoutFor(id))}.',
      );
    }
  }
}
