import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

import 'support/fake_device_test_ui_controller.dart';
import 'support/presentation_fixtures.dart';

void main() {
  testWidgets('agent and human prompts expose distinct required-actor labels', (
    tester,
  ) async {
    final semantics = tester.ensureSemantics();
    try {
      final controller = FakeDeviceTestUiController(
        runnerState(activePrompt: prompt(actor: RequiredActor.agentAndroid)),
      );
      await tester.pumpWidget(
        DeviceTestAppShell(
          controller: controller,
          initialScreen: DeviceTestScreen.runner,
        ),
      );
      await tester.pump(const Duration(milliseconds: 500));

      expect(find.text('Agent (Android) required'), findsOneWidget);
      expect(
        tester.getSemantics(find.byKey(DeviceTestUiKeys.requiredActor)).label,
        contains('Required actor: Agent (Android)'),
      );

      controller.emit(
        runnerState(
          activePrompt: prompt(
            actor: RequiredActor.human,
            id: 'human-prompt',
            title: 'Press the physical On/Off control',
          ),
        ),
      );
      await tester.pump(const Duration(milliseconds: 500));

      expect(find.text('Human required'), findsOneWidget);
      expect(
        tester.getSemantics(find.byKey(DeviceTestUiKeys.requiredActor)).label,
        contains('Required actor: Human'),
      );
    } finally {
      semantics.dispose();
    }
  });
}
