import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

import 'support/fake_device_test_ui_controller.dart';
import 'support/presentation_fixtures.dart';

void main() {
  testWidgets('setup validation only reports remaining required fields', (
    tester,
  ) async {
    final controller = FakeDeviceTestUiController(setupState());
    await tester.pumpWidget(
      DeviceTestAppShell(
        controller: controller,
        initialScreen: DeviceTestScreen.setup,
      ),
    );
    await tester.pumpAndSettle();

    await _center(tester, find.byKey(DeviceTestUiKeys.startRun));
    await tester.tap(find.byKey(DeviceTestUiKeys.startRun));
    await tester.pumpAndSettle();

    expect(controller.submittedRequest, isNull);
    expect(
      find.text('Matter setup code or QR payload is required.'),
      findsOneWidget,
    );
    expect(
      find.text(
        'Confirm the commissionee was factory-reset and is in a '
        'commissioning window.',
      ),
      findsOneWidget,
    );
    expect(find.text('Commissionee model is required.'), findsNothing);
    expect(find.text('Firmware version is required.'), findsNothing);
    expect(find.byKey(DeviceTestUiKeys.setupValidationSummary), findsOneWidget);
  });

  testWidgets(
    'removed setup fields are absent and passed preflight is hidden',
    (tester) async {
      final controller = FakeDeviceTestUiController(setupState());
      await tester.pumpWidget(
        DeviceTestAppShell(
          controller: controller,
          initialScreen: DeviceTestScreen.setup,
        ),
      );
      await tester.pumpAndSettle();

      expect(find.byKey(DeviceTestUiKeys.wifiSsidDisplay), findsOneWidget);
      expect(find.byKey(DeviceTestUiKeys.wifiSsidManual), findsNothing);
      expect(find.byKey(DeviceTestUiKeys.preflightList), findsNothing);
      expect(find.text('Thread operational dataset'), findsNothing);
      expect(find.text('Controller model'), findsNothing);
      expect(find.text('Manufacturer model'), findsNothing);
      expect(find.text('Firmware version'), findsNothing);
      expect(find.text('State change notes'), findsNothing);
      expect(find.text('Purge Secrets Now'), findsNothing);
      expect(
        find.textContaining('BLE and Wi-Fi/IP at the same time'),
        findsOneWidget,
      );
    },
  );

  testWidgets('cached matching Wi-Fi values prefill the form', (tester) async {
    final controller = FakeDeviceTestUiController(setupState());
    await tester.pumpWidget(
      DeviceTestAppShell(
        controller: controller,
        initialScreen: DeviceTestScreen.setup,
      ),
    );
    await tester.pumpAndSettle();

    expect(find.text('matter-test-network'), findsOneWidget);
    final password = tester.widget<TextField>(
      find.byKey(DeviceTestUiKeys.wifiPassword),
    );
    expect(password.controller!.text, 'cached-password');
  });

  testWidgets('manual SSID fallback and cache clear are available', (
    tester,
  ) async {
    final controller = FakeDeviceTestUiController(setupState())
      ..wifiPrefill = const WifiSetupPrefill(manualSsidRequired: true);
    await tester.pumpWidget(
      DeviceTestAppShell(
        controller: controller,
        initialScreen: DeviceTestScreen.setup,
      ),
    );
    await tester.pumpAndSettle();

    expect(find.byKey(DeviceTestUiKeys.wifiSsidManual), findsOneWidget);
    await _center(tester, find.byKey(DeviceTestUiKeys.wifiClearCredentials));
    await tester.tap(find.byKey(DeviceTestUiKeys.wifiClearCredentials));
    await tester.pumpAndSettle();
    expect(controller.clearWifiCalls, 1);
  });

  testWidgets('valid setup submits only the minimal request', (tester) async {
    final controller = FakeDeviceTestUiController(setupState());
    await tester.pumpWidget(
      DeviceTestAppShell(
        controller: controller,
        initialScreen: DeviceTestScreen.setup,
      ),
    );
    await tester.pumpAndSettle();

    await tester.enterText(
      find.byKey(DeviceTestUiKeys.setupCode),
      'MT:TEST-SETUP-CODE',
    );
    final tile = tester.widget<CheckboxListTile>(
      find.byKey(DeviceTestUiKeys.commissioneeClean),
    );
    tile.onChanged!(true);
    await tester.pump();

    await _center(tester, find.byKey(DeviceTestUiKeys.startRun));
    await tester.tap(find.byKey(DeviceTestUiKeys.startRun));
    await tester.pumpAndSettle();

    final request = controller.submittedRequest;
    expect(request, isNotNull);
    expect(request!.setupCode, 'MT:TEST-SETUP-CODE');
    expect(request.wifiSsid, 'matter-test-network');
    expect(request.wifiPassword, 'cached-password');
    expect(request.profile, TestProfile.full);
    expect(request.cleanCycle.commissioneeClean, isTrue);
    expect(controller.state.screen, DeviceTestScreen.runner);
  });
}

Future<void> _center(WidgetTester tester, Finder finder) async {
  await Scrollable.ensureVisible(
    tester.element(finder),
    alignment: 0.5,
    duration: Duration.zero,
  );
  await tester.pump();
}
