import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('DeviceTestCatalog', () {
    test('keeps the contract order and priorities', () {
      expect(DeviceTestCatalog.all.map((testId) => testId.wireName), <String>[
        'build_install',
        'commissioning',
        'operational_connect',
        'app_restart',
        'onoff_invoke',
        'onoff_subscription',
        'node_label_read_write',
        'invalid_setup_passcode',
      ]);
      expect(
        DeviceTestCatalog.all.map((testId) => testId.priority),
        <DeviceTestPriority>[
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p1,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
          DeviceTestPriority.p0,
        ],
      );
    });

    test('quick is the four-step minimum operational path', () {
      expect(TestProfile.quick.testIds, <DeviceTestId>[
        DeviceTestId.buildInstall,
        DeviceTestId.commissioning,
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
      expect(TestProfile.full.testIds.toSet(), hasLength(8));
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
