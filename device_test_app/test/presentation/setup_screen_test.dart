import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

import 'support/fake_device_test_ui_controller.dart';
import 'support/presentation_fixtures.dart';

void main() {
  testWidgets('setup validation reports missing required fields', (
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
    expect(find.text('Commissionee model is required.'), findsOneWidget);
    expect(find.text('Firmware version is required.'), findsOneWidget);
    expect(
      find.text('Matter setup code or QR payload is required.'),
      findsOneWidget,
    );
    expect(find.text('Wi-Fi SSID is required.'), findsOneWidget);
    expect(
      find.text(
        'Confirm the controller starts from a clean fabric and app state.',
      ),
      findsOneWidget,
    );
    expect(find.byKey(DeviceTestUiKeys.setupValidationSummary), findsOneWidget);
  });

  testWidgets(
    'virtual commissionee requires fallback reason and confirmation',
    (tester) async {
      final controller = FakeDeviceTestUiController(setupState());
      await tester.pumpWidget(
        DeviceTestAppShell(
          controller: controller,
          initialScreen: DeviceTestScreen.setup,
        ),
      );
      await tester.pumpAndSettle();

      await tester.tap(find.byKey(DeviceTestUiKeys.virtualCommissionee));
      await tester.pumpAndSettle();
      await tester.ensureVisible(find.byKey(DeviceTestUiKeys.startRun));
      await tester.tap(find.byKey(DeviceTestUiKeys.startRun));
      await tester.pumpAndSettle();

      expect(controller.submittedRequest, isNull);
      expect(
        find.text('Explain why no qualified real Matter device is available.'),
        findsOneWidget,
      );
      expect(
        find.text('Confirm that the virtual commissionee is the fallback.'),
        findsOneWidget,
      );
    },
  );

  testWidgets('valid setup submits a request and enters the runner', (
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

    await tester.enterText(
      find.byKey(DeviceTestUiKeys.modelField),
      'Example Matter Plug',
    );
    await tester.enterText(find.byKey(DeviceTestUiKeys.firmwareField), '1.2.3');
    await tester.enterText(
      find.byKey(DeviceTestUiKeys.setupCode),
      'MT:TEST-SETUP-CODE',
    );
    await tester.enterText(
      find.byKey(DeviceTestUiKeys.wifiSsid),
      'matter-test-network',
    );

    for (final key in <Key>[
      DeviceTestUiKeys.controllerClean,
      DeviceTestUiKeys.commissioneeClean,
      DeviceTestUiKeys.secretsPurged,
    ]) {
      final tile = tester.widget<CheckboxListTile>(find.byKey(key));
      tile.onChanged!(true);
      await tester.pump();
      expect(tester.widget<CheckboxListTile>(find.byKey(key)).value, isTrue);
    }

    await _center(tester, find.byKey(DeviceTestUiKeys.startRun));
    await tester.tap(find.byKey(DeviceTestUiKeys.startRun));
    await tester.pumpAndSettle();

    final request = controller.submittedRequest;
    expect(request, isNotNull);
    expect(request!.commissioneeType, CommissioneeType.real);
    expect(request.model, 'Example Matter Plug');
    expect(request.firmware, '1.2.3');
    expect(request.networkTransport, NetworkTransport.wifi);
    expect(request.wifiSsid, 'matter-test-network');
    expect(request.profile, TestProfile.full);
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
