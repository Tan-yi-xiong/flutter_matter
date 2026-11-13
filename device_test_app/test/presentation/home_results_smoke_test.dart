import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';

import 'support/fake_device_test_ui_controller.dart';
import 'support/presentation_fixtures.dart';

void main() {
  testWidgets('home exposes new Run, recent result, and purge actions', (
    tester,
  ) async {
    final summary = ReportSummary.calculate(
      testProgress(
        TestProfile.full,
        statuses: <DeviceTestId, DeviceTestStatus>{
          for (final testId in DeviceTestCatalog.all)
            testId: DeviceTestStatus.passed,
        },
      ).map(
        (test) => DeviceTestResult(testId: test.testId, status: test.status),
      ),
    );
    final controller = FakeDeviceTestUiController(
      DeviceTestUiState(
        controllerInfo: controllerInfo,
        preflightChecks: readyPreflight,
        activeRun: activeRun(),
        recentRun: RecentRunViewModel(
          profile: TestProfile.full,
          summary: summary,
          completedAt: DateTime.utc(2026, 11, 11, 12),
          formalEvidence: true,
        ),
        hasStoredSecrets: true,
      ),
    );

    await tester.pumpWidget(DeviceTestAppShell(controller: controller));
    await tester.pump(const Duration(milliseconds: 200));

    expect(find.byKey(DeviceTestUiKeys.newRun), findsOneWidget);
    expect(find.byKey(DeviceTestUiKeys.homeViewResults), findsOneWidget);
    expect(find.byKey(DeviceTestUiKeys.purgeSecrets), findsOneWidget);
  });

  testWidgets('results renders summary, table, validation, and share actions', (
    tester,
  ) async {
    final tests = <TestProgressViewModel>[
      for (final testId in DeviceTestCatalog.all)
        TestProgressViewModel(
          testId: testId,
          status: DeviceTestStatus.passed,
          duration: const Duration(seconds: 2),
        ),
    ];
    final summary = ReportSummary(
      result: ReportResult.passed,
      passed: tests.length,
      failed: 0,
      notRun: 0,
    );
    final controller = FakeDeviceTestUiController(
      DeviceTestUiState(
        screen: DeviceTestScreen.results,
        controllerInfo: controllerInfo,
        preflightChecks: readyPreflight,
        results: ResultsViewModel(
          profile: TestProfile.full,
          tests: tests,
          summary: summary,
          validation: const ReportValidationViewModel(
            status: ReportUiValidationStatus.valid,
            message: 'Schema and semantic validation passed.',
          ),
          jsonAvailable: true,
          markdownAvailable: true,
        ),
        hasStoredSecrets: true,
      ),
    );

    await tester.pumpWidget(
      DeviceTestAppShell(
        controller: controller,
        initialScreen: DeviceTestScreen.results,
      ),
    );
    await tester.pump(const Duration(milliseconds: 200));

    expect(find.byKey(DeviceTestUiKeys.resultsSummary), findsOneWidget);
    expect(find.byKey(DeviceTestUiKeys.resultsValidation), findsOneWidget);
    expect(find.byKey(DeviceTestUiKeys.resultsTable), findsOneWidget);
    for (final testId in DeviceTestCatalog.all) {
      expect(find.byKey(DeviceTestUiKeys.resultsRow(testId)), findsOneWidget);
    }

    tester
        .widget<FilledButton>(find.byKey(DeviceTestUiKeys.shareJson))
        .onPressed!();
    await tester.pump();
    tester
        .widget<OutlinedButton>(find.byKey(DeviceTestUiKeys.shareMarkdown))
        .onPressed!();
    await tester.pump();

    expect(controller.shareJsonCalls, 1);
    expect(controller.shareMarkdownCalls, 1);
  });
}
