import '../../domain/domain.dart';
import '../test_case.dart';
import '../test_context.dart';

class IpDiscoveryCase implements DeviceTestCase {
  const IpDiscoveryCase();

  @override
  DeviceTestId get id => DeviceTestId.ipDiscovery;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for Wi-Fi/IP discovery.',
      );
    }
    if (secrets.commissioningTransport != CommissioningTransport.ip) {
      return TestCaseOutcome.failed(
        'The Run is not configured for Wi-Fi/IP commissioning.',
      );
    }
    if (!secrets.supportsOnNetworkDiscovery) {
      return TestCaseOutcome.failed(
        'The setup payload does not advertise on-network discovery.',
      );
    }
    return const TestCaseOutcome.passed(
      notes:
          'Setup payload advertises on-network discovery for Wi-Fi/IP commissioning.',
    );
  }
}
