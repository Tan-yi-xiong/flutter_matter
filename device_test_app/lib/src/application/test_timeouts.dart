import '../domain/domain.dart';

/// Production and test-overridable time budgets for each fixed test.
class TestTimeouts {
  const TestTimeouts({
    this.buildInstall = const Duration(seconds: 60),
    this.ipDiscovery = const Duration(seconds: 15),
    this.ipCommissioning = const Duration(seconds: 120),
    this.operationalConnect = const Duration(seconds: 30),
    this.onOffInvoke = const Duration(seconds: 10),
    this.onOffSubscription = const Duration(seconds: 15),
    this.nodeLabelPersistence = const Duration(seconds: 75),
    this.appRestart = const Duration(seconds: 60),
    this.factoryResetRecommission = const Duration(seconds: 180),
    this.invalidSetupPasscode = const Duration(seconds: 120),
    this.invalidWifiPassword = const Duration(seconds: 120),
    this.removeFabricUi = const Duration(seconds: 60),
  });

  final Duration buildInstall;
  final Duration ipDiscovery;
  final Duration ipCommissioning;
  final Duration operationalConnect;
  final Duration onOffInvoke;
  final Duration onOffSubscription;
  final Duration nodeLabelPersistence;
  final Duration appRestart;
  final Duration factoryResetRecommission;
  final Duration invalidSetupPasscode;
  final Duration invalidWifiPassword;
  final Duration removeFabricUi;

  Duration forTest(DeviceTestId testId) => switch (testId) {
    DeviceTestId.buildInstall => buildInstall,
    DeviceTestId.ipDiscovery => ipDiscovery,
    DeviceTestId.ipCommissioning => ipCommissioning,
    DeviceTestId.operationalConnect => operationalConnect,
    DeviceTestId.onoffInvoke => onOffInvoke,
    DeviceTestId.onoffSubscription => onOffSubscription,
    DeviceTestId.nodeLabelPersistence => nodeLabelPersistence,
    DeviceTestId.appRestart => appRestart,
    DeviceTestId.factoryResetRecommission => factoryResetRecommission,
    DeviceTestId.invalidSetupPasscode => invalidSetupPasscode,
    DeviceTestId.invalidWifiPassword => invalidWifiPassword,
    DeviceTestId.removeFabricUi => removeFabricUi,
  };
}
