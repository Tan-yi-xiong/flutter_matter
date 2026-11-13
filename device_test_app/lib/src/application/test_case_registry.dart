import '../domain/domain.dart';
import 'cases/app_restart_case.dart';
import 'cases/build_install_case.dart';
import 'cases/factory_reset_recommission_case.dart';
import 'cases/invalid_setup_passcode_case.dart';
import 'cases/invalid_wifi_password_case.dart';
import 'cases/commissioning_case.dart';
import 'cases/node_label_persistence_case.dart';
import 'cases/onoff_invoke_case.dart';
import 'cases/onoff_subscription_case.dart';
import 'cases/operational_connect_case.dart';
import 'cases/remove_fabric_ui_case.dart';
import 'test_case.dart';

class TestCaseRegistryException implements Exception {
  TestCaseRegistryException(this.message);

  final String message;

  @override
  String toString() => 'TestCaseRegistryException: $message';
}

/// Maps every fixed test ID to exactly one case implementation.
class TestCaseRegistry {
  TestCaseRegistry(Iterable<DeviceTestCase> cases) {
    final byId = <DeviceTestId, DeviceTestCase>{};
    for (final testCase in cases) {
      if (byId.containsKey(testCase.id)) {
        throw TestCaseRegistryException(
          'Duplicate test case for ${testCase.id.wireName}.',
        );
      }
      byId[testCase.id] = testCase;
    }
    final missing = DeviceTestCatalog.allIds.difference(byId.keys.toSet());
    if (missing.isNotEmpty) {
      final names = missing.map((id) => id.wireName).toList()..sort();
      throw TestCaseRegistryException(
        'Missing test cases: ${names.join(', ')}.',
      );
    }
    _cases = Map<DeviceTestId, DeviceTestCase>.unmodifiable(byId);
  }

  factory TestCaseRegistry.canonical() => TestCaseRegistry(<DeviceTestCase>[
    const BuildInstallCase(),
    const CommissioningCase(),
    const OperationalConnectCase(),
    const OnOffInvokeCase(),
    const OnOffSubscriptionCase(),
    const NodeLabelPersistenceCase(),
    const AppRestartCase(),
    const FactoryResetRecommissionCase(),
    const InvalidSetupPasscodeCase(),
    const InvalidWifiPasswordCase(),
    const RemoveFabricUiCase(),
  ]);

  late final Map<DeviceTestId, DeviceTestCase> _cases;

  /// Returns cases in the canonical execution order for [profile].
  List<DeviceTestCase> forProfile(TestProfile profile) {
    return <DeviceTestCase>[
      for (final testId in profile.testIds) _cases[testId]!,
    ];
  }

  DeviceTestCase caseFor(DeviceTestId testId) => _cases[testId]!;

  List<DeviceTestCase> get allCases => forProfile(TestProfile.full);
}
