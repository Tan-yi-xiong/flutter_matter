/// The fixed device-validation test catalog.
///
/// The declaration order is the canonical execution and report order. Test IDs
/// must remain stable because they are part of the report schema contract.
enum DeviceTestId {
  buildInstall(
    wireName: 'build_install',
    priority: DeviceTestPriority.p0,
    title: 'Build and install',
  ),
  bleDiscovery(
    wireName: 'ble_discovery',
    priority: DeviceTestPriority.p0,
    title: 'BLE discovery',
  ),
  bleCommissioning(
    wireName: 'ble_commissioning',
    priority: DeviceTestPriority.p0,
    title: 'BLE commissioning',
  ),
  operationalConnect(
    wireName: 'operational_connect',
    priority: DeviceTestPriority.p0,
    title: 'Operational connection',
  ),
  onoffInvoke(
    wireName: 'onoff_invoke',
    priority: DeviceTestPriority.p0,
    title: 'OnOff invoke',
  ),
  onoffSubscription(
    wireName: 'onoff_subscription',
    priority: DeviceTestPriority.p0,
    title: 'OnOff subscription',
  ),
  nodeLabelPersistence(
    wireName: 'node_label_persistence',
    priority: DeviceTestPriority.p0,
    title: 'NodeLabel persistence',
  ),
  appRestart(
    wireName: 'app_restart',
    priority: DeviceTestPriority.p1,
    title: 'Controller app restart',
  ),
  factoryResetRecommission(
    wireName: 'factory_reset_recommission',
    priority: DeviceTestPriority.p1,
    title: 'Factory reset and recommission',
  ),
  invalidSetupPasscode(
    wireName: 'invalid_setup_passcode',
    priority: DeviceTestPriority.p2,
    title: 'Invalid setup passcode',
  ),
  bluetoothDisabled(
    wireName: 'bluetooth_disabled',
    priority: DeviceTestPriority.p2,
    title: 'Bluetooth disabled',
  ),
  invalidWifiPassword(
    wireName: 'invalid_wifi_password',
    priority: DeviceTestPriority.p2,
    title: 'Invalid Wi-Fi password',
  ),
  removeFabricUi(
    wireName: 'remove_fabric_ui',
    priority: DeviceTestPriority.p2,
    title: 'Remove fabric UI',
  );

  const DeviceTestId({
    required this.wireName,
    required this.priority,
    required this.title,
  });

  final String wireName;
  final DeviceTestPriority priority;
  final String title;

  static DeviceTestId? tryParse(String value) {
    for (final testId in values) {
      if (testId.wireName == value) {
        return testId;
      }
    }
    return null;
  }

  static DeviceTestId parse(String value) {
    final testId = tryParse(value);
    if (testId == null) {
      throw FormatException('Unknown device test ID: $value');
    }
    return testId;
  }
}

enum DeviceTestPriority {
  p0('P0'),
  p1('P1'),
  p2('P2');

  const DeviceTestPriority(this.label);

  final String label;
}

/// Test profiles select a stable, ordered subset of [DeviceTestId] values.
enum TestProfile {
  quick('quick'),
  full('full');

  const TestProfile(this.wireName);

  final String wireName;

  List<DeviceTestId> get testIds => switch (this) {
    TestProfile.quick => DeviceTestCatalog.quickTestIds,
    TestProfile.full => DeviceTestCatalog.all,
  };

  bool includes(DeviceTestId testId) => testIds.contains(testId);

  static TestProfile? tryParse(String value) {
    for (final profile in values) {
      if (profile.wireName == value) {
        return profile;
      }
    }
    return null;
  }

  static TestProfile parse(String value) {
    final profile = tryParse(value);
    if (profile == null) {
      throw FormatException('Unknown test profile: $value');
    }
    return profile;
  }
}

abstract final class DeviceTestCatalog {
  /// Every contract test in canonical order.
  static List<DeviceTestId> get all => DeviceTestId.values;

  /// The minimum smoke path: build through the first successful OnOff invoke.
  static const List<DeviceTestId> quickTestIds = <DeviceTestId>[
    DeviceTestId.buildInstall,
    DeviceTestId.bleDiscovery,
    DeviceTestId.bleCommissioning,
    DeviceTestId.operationalConnect,
    DeviceTestId.onoffInvoke,
  ];

  static List<DeviceTestId> forProfile(TestProfile profile) => profile.testIds;

  static Set<DeviceTestId> get allIds => DeviceTestId.values.toSet();
}
