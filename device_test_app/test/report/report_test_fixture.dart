import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';

const fixtureTestApp = TestAppMetadata(
  name: 'flutter_matter_device_test_app',
  version: '1.0.0',
  commit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
);

const fixturePluginCommit = 'dddd0d7d0b4ba273eaa8cd16a5d68c59e8e1b112';

final fixtureGeneratedAt = DateTime.utc(2026, 11, 11, 12);

DeviceTestReportV3 buildFixtureReport() {
  return const DeviceTestReportBuilder().buildFormal(
    buildFixtureSession(),
    generatedAt: fixtureGeneratedAt,
    sanitizationReviewed: true,
  );
}

RunSession buildFixtureSession({
  Map<DeviceTestId, DeviceTestResult>? overrides,
  CommissioneeMetadata? commissionee,
}) {
  final results = <DeviceTestId, DeviceTestResult>{
    for (final testId in DeviceTestCatalog.all)
      testId: DeviceTestResult(
        testId: testId,
        status: testId == DeviceTestId.removeFabricUi
            ? DeviceTestStatus.notRun
            : DeviceTestStatus.passed,
        duration: testId == DeviceTestId.removeFabricUi
            ? Duration.zero
            : Duration(milliseconds: 1000 + testId.index),
        notes: testId == DeviceTestId.removeFabricUi
            ? 'The optional UI path was unavailable after the factory reset.'
            : null,
        evidenceFiles: testId == DeviceTestId.buildInstall
            ? const <String>['android-build-install.png']
            : const <String>[],
      ),
  };
  if (overrides != null) {
    results.addAll(overrides);
  }

  return RunSession(
    id: 'fixture-run',
    profile: TestProfile.full,
    testApp: fixtureTestApp,
    pluginCommit: fixturePluginCommit,
    createdAt: fixtureGeneratedAt,
    updatedAt: fixtureGeneratedAt,
    phase: RunPhase.completed,
    controller: const ControllerMetadata(
      platform: ControllerPlatform.android,
      deviceModel: 'Pixel 8',
      osVersion: 'Android 15',
      appBuild: 'debug 1.0.0 (1)',
    ),
    commissionee:
        commissionee ??
        const CommissioneeMetadata(
          vendorId: 4660,
          productId: 22136,
          commissioningTransport: CommissioningTransport.ip,
          networkTransport: NetworkTransport.wifi,
        ),
    results: results,
  );
}
