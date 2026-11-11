import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

class _FakeCase implements DeviceTestCase {
  _FakeCase(this.id);

  @override
  final DeviceTestId id;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async =>
      const TestCaseOutcome.passed();
}

void main() {
  group('TestCaseRegistry', () {
    test('contains all 13 fixed cases in canonical order', () {
      final registry = TestCaseRegistry.canonical();
      expect(registry.allCases.length, 13);
      expect(
        registry.allCases.map((testCase) => testCase.id).toList(),
        DeviceTestCatalog.all,
      );
    });

    test('quick profile has exactly the five quick cases', () {
      final registry = TestCaseRegistry.canonical();
      expect(
        registry.forProfile(TestProfile.quick).map((testCase) => testCase.id),
        DeviceTestCatalog.quickTestIds,
      );
    });

    test('rejects missing and duplicate cases', () {
      final cases = <DeviceTestCase>[
        for (final id in DeviceTestCatalog.all) _FakeCase(id),
      ];
      expect(
        () => TestCaseRegistry(cases.sublist(0, 12)),
        throwsA(isA<TestCaseRegistryException>()),
      );
      expect(
        () => TestCaseRegistry(<DeviceTestCase>[
          ...cases,
          _FakeCase(DeviceTestId.buildInstall),
        ]),
        throwsA(isA<TestCaseRegistryException>()),
      );
    });

    test('returns a case by fixed ID', () {
      final registry = TestCaseRegistry.canonical();
      expect(
        registry.caseFor(DeviceTestId.onoffInvoke).id,
        DeviceTestId.onoffInvoke,
      );
    });
  });
}
