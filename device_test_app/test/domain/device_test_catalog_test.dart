import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('DeviceTestCatalog', () {
    test('keeps the contract order and priorities', () {
      expect(DeviceTestCatalog.all.map((testId) => testId.wireName), <String>[
        'build_install',
        'ip_discovery',
        'ip_commissioning',
        'operational_connect',
        'onoff_invoke',
        'onoff_subscription',
        'node_label_persistence',
        'app_restart',
        'factory_reset_recommission',
        'invalid_setup_passcode',
        'invalid_wifi_password',
        'remove_fabric_ui',
      ]);
      expect(
        DeviceTestCatalog.all.map((testId) => testId.priority),
        <DeviceTestPriority>[
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p1,
          DeviceTestPriority.p1,
          DeviceTestPriority.p2,
          DeviceTestPriority.p2,
          DeviceTestPriority.p2,
        ],
      );
    });

    test('quick is the five-step minimum operational path', () {
      expect(TestProfile.quick.testIds, <DeviceTestId>[
        DeviceTestId.buildInstall,
        DeviceTestId.ipDiscovery,
        DeviceTestId.ipCommissioning,
        DeviceTestId.operationalConnect,
        DeviceTestId.onoffInvoke,
      ]);
      expect(
        TestProfile.quick.testIds,
        isNot(contains(DeviceTestId.onoffSubscription)),
      );
    });

    test('full contains every fixed test in canonical order', () {
      expect(TestProfile.full.testIds, DeviceTestCatalog.all);
      expect(TestProfile.full.testIds.toSet(), hasLength(12));
    });

    test('wire names round trip and unknown names fail', () {
      for (final testId in DeviceTestCatalog.all) {
        expect(DeviceTestId.parse(testId.wireName), testId);
      }
      expect(() => DeviceTestId.parse('not_a_test'), throwsFormatException);
      expect(TestProfile.parse('quick'), TestProfile.quick);
      expect(() => TestProfile.parse('partial'), throwsFormatException);
    });
  });
}
