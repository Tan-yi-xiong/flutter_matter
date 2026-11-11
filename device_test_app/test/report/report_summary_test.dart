import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('all-passed results produce a passed summary', () {
    final summary = ReportSummary.calculate(<DeviceTestResult>[
      for (final testId in DeviceTestCatalog.all)
        DeviceTestResult(testId: testId, status: DeviceTestStatus.passed),
    ]);

    expect(summary.result, ReportResult.passed);
    expect(summary.passed, 12);
    expect(summary.failed, 0);
    expect(summary.notRun, 0);
    expect(summary.total, 12);
  });

  test('a P0 not_run makes the overall result not_run', () {
    final summary = ReportSummary.calculate(<DeviceTestResult>[
      for (final testId in DeviceTestCatalog.all)
        DeviceTestResult(
          testId: testId,
          status: testId == DeviceTestId.operationalConnect
              ? DeviceTestStatus.notRun
              : DeviceTestStatus.passed,
        ),
    ]);

    expect(summary.result, ReportResult.notRun);
    expect(summary.notRun, 1);
  });

  test('P1 and P2 not_run results do not block a passed summary', () {
    final summary = ReportSummary.calculate(<DeviceTestResult>[
      for (final testId in DeviceTestCatalog.all)
        DeviceTestResult(
          testId: testId,
          status: testId.priority == DeviceTestPriority.p0
              ? DeviceTestStatus.passed
              : DeviceTestStatus.notRun,
        ),
    ]);

    expect(summary.result, ReportResult.passed);
    expect(summary.passed, 7);
    expect(summary.notRun, 5);
  });

  test('any failure makes the overall result failed', () {
    final summary = ReportSummary.calculate(<DeviceTestResult>[
      for (final testId in DeviceTestCatalog.all)
        DeviceTestResult(
          testId: testId,
          status: testId == DeviceTestId.invalidWifiPassword
              ? DeviceTestStatus.failed
              : DeviceTestStatus.passed,
        ),
    ]);

    expect(summary.result, ReportResult.failed);
    expect(summary.failed, 1);
  });

  test('pending or running results cannot be summarized', () {
    expect(
      () => ReportSummary.calculate(<DeviceTestResult>[
        DeviceTestResult(
          testId: DeviceTestId.buildInstall,
          status: DeviceTestStatus.running,
        ),
      ]),
      throwsArgumentError,
    );
  });

  test('empty results do not claim success', () {
    final summary = ReportSummary.calculate(const <DeviceTestResult>[]);
    expect(summary.result, ReportResult.notRun);
    expect(summary.total, 0);
  });
}
