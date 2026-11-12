import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

import 'support/fake_device_test_ui_controller.dart';
import 'support/presentation_fixtures.dart';

void main() {
  testWidgets(
    'runner renders the fixed test list with priorities and statuses',
    (tester) async {
      final run = activeRun(
        statuses: const <DeviceTestId, DeviceTestStatus>{
          DeviceTestId.buildInstall: DeviceTestStatus.passed,
          DeviceTestId.commissioningDiscovery: DeviceTestStatus.running,
        },
      );
      final controller = FakeDeviceTestUiController(runnerState(run: run));
      await tester.pumpWidget(
        DeviceTestAppShell(
          controller: controller,
          initialScreen: DeviceTestScreen.runner,
        ),
      );
      await tester.pump(const Duration(milliseconds: 500));

      for (final testId in DeviceTestCatalog.all) {
        expect(find.byKey(DeviceTestUiKeys.testRow(testId)), findsOneWidget);
      }
      expect(find.text('P0'), findsWidgets);
      expect(find.text('Running'), findsWidgets);
      expect(find.text('Passed'), findsWidgets);
      expect(find.byKey(DeviceTestUiKeys.currentInstruction), findsOneWidget);
      expect(
        find.descendant(
          of: find.byKey(DeviceTestUiKeys.testRow(DeviceTestId.buildInstall)),
          matching: find.byType(TextField),
        ),
        findsNothing,
      );
    },
  );

  testWidgets('runner shows the app restart waiting state', (tester) async {
    final run = activeRun(
      currentTestId: DeviceTestId.appRestart,
      currentInstruction: 'Reopen the controller app and resume the Run.',
      awaitingAppRestart: true,
    );
    final controller = FakeDeviceTestUiController(runnerState(run: run));
    await tester.pumpWidget(
      DeviceTestAppShell(
        controller: controller,
        initialScreen: DeviceTestScreen.runner,
      ),
    );
    await tester.pump(const Duration(milliseconds: 500));

    expect(find.byKey(DeviceTestUiKeys.waitingForAppRestart), findsOneWidget);
    expect(
      find.textContaining('Waiting for the controller app to restart'),
      findsOneWidget,
    );
  });
}
