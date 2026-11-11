import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';

class BleDiscoveryCase implements DeviceTestCase {
  const BleDiscoveryCase();

  @override
  DeviceTestId get id => DeviceTestId.bleDiscovery;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for BLE discovery.',
      );
    }

    try {
      final result = await context.ports.bleDiscovery.discover(
        BleDiscoveryRequest(
          timeout: context.timeoutFor(id),
          onboardingPayload: secrets.onboardingPayload,
        ),
      );
      final target = result.target;
      if (target == null) {
        return TestCaseOutcome.failed(
          'The expected Matter commissionee was not discovered.',
        );
      }
      await context.updateExecution((execution) {
        execution.target = target;
      });
      return TestCaseOutcome.passed(
        notes:
            'Discovered the expected commissionee among '
            '${result.candidateCount} candidate(s).',
      );
    } on BleDiscoveryException catch (error) {
      return TestCaseOutcome.failed(
        'BLE discovery failed with ${error.code.wireName}.',
      );
    }
  }
}
