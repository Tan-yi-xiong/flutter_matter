import '../domain/domain.dart';

/// Production and test-overridable time budgets for each fixed test.
class TestTimeouts {
  const TestTimeouts({
    this.buildInstall = const Duration(seconds: 60),
    this.commissioning = const Duration(seconds: 120),
    this.operationalConnect = const Duration(seconds: 30),
    this.onOffInvoke = const Duration(seconds: 10),
    this.onOffSubscription = const Duration(seconds: 15),
    this.nodeLabelReadWrite = const Duration(seconds: 45),
    this.appRestart = const Duration(seconds: 60),
    this.invalidSetupPasscode = const Duration(seconds: 120),
    this.fabricRemove = const Duration(seconds: 60),
    this.commissioningWindow = const Duration(seconds: 30),
  });

  final Duration buildInstall;
  final Duration commissioning;
  final Duration operationalConnect;
  final Duration onOffInvoke;
  final Duration onOffSubscription;
  final Duration nodeLabelReadWrite;
  final Duration appRestart;
  final Duration invalidSetupPasscode;
  final Duration fabricRemove;

  /// Budget for re-opening a commissioning window as a case sub-step.
  final Duration commissioningWindow;

  Duration forTest(DeviceTestId testId) => switch (testId) {
    DeviceTestId.buildInstall => buildInstall,
    DeviceTestId.commissioning => commissioning,
    DeviceTestId.operationalConnect => operationalConnect,
    DeviceTestId.onoffInvoke => onOffInvoke,
    DeviceTestId.onoffSubscription => onOffSubscription,
    DeviceTestId.nodeLabelReadWrite => nodeLabelReadWrite,
    DeviceTestId.appRestart => appRestart,
    DeviceTestId.invalidSetupPasscode => invalidSetupPasscode,
    DeviceTestId.fabricRemove => fabricRemove,
  };
}
