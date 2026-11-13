import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

import 'support/fake_device_test_ui_controller.dart';
import 'support/presentation_fixtures.dart';

void main() {
  testWidgets(
    'prompt controls confirm, skip with reason, and fail with reason',
    (tester) async {
      final controller = FakeDeviceTestUiController(
        runnerState(activePrompt: prompt()),
      );
      await tester.pumpWidget(
        DeviceTestAppShell(
          controller: controller,
          initialScreen: DeviceTestScreen.runner,
        ),
      );
      await tester.pump(const Duration(milliseconds: 500));

      await tester.ensureVisible(find.byKey(DeviceTestUiKeys.promptConfirm));
      await tester.tap(find.byKey(DeviceTestUiKeys.promptConfirm));
      await tester.pump(const Duration(milliseconds: 500));
      expect(controller.confirmCalls, 1);

      await tester.tap(find.byKey(DeviceTestUiKeys.promptSkip));
      await tester.pump(const Duration(milliseconds: 500));
      await tester.enterText(
        find.byKey(DeviceTestUiKeys.skipReasonField),
        'The commissionee control was unavailable.',
      );
      await tester.tap(find.byKey(DeviceTestUiKeys.reasonDialogSubmit));
      await tester.pump(const Duration(milliseconds: 500));
      expect(
        controller.lastSkipReason,
        'The commissionee control was unavailable.',
      );

      await tester.tap(find.byKey(DeviceTestUiKeys.promptFail));
      await tester.pump(const Duration(milliseconds: 500));
      await tester.enterText(
        find.byKey(DeviceTestUiKeys.failReasonField),
        'The device did not advertise after setup.',
      );
      await tester.tap(find.byKey(DeviceTestUiKeys.reasonDialogSubmit));
      await tester.pump(const Duration(milliseconds: 500));
      expect(
        controller.lastFailReason,
        'The device did not advertise after setup.',
      );
    },
  );
}
