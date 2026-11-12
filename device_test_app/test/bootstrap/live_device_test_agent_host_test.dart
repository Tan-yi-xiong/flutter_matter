import 'package:flutter/widgets.dart';
import 'package:flutter_matter_device_test_app/src/agent/agent_command_handler.dart';
import 'package:flutter_matter_device_test_app/src/agent/protocol.dart';
import 'package:flutter_matter_device_test_app/src/bootstrap/live_device_test_agent_host.dart';
import 'package:flutter_matter_device_test_app/src/bootstrap/widget_screenshot_capture.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/ui_models.dart';
import 'package:flutter_test/flutter_test.dart';

import '../app/support/fakes.dart';

void main() {
  late String schemaJson;

  setUpAll(() async {
    schemaJson = await loadReportSchema();
  });

  test(
    'starts a Run through the same parser and controller as the UI',
    () async {
      final harness = buildHarness(schemaJson: schemaJson);
      addTearDown(harness.close);
      await harness.controller.initialize();
      final host = LiveDeviceTestAgentHost(
        controller: harness.controller,
        runner: harness.runner,
        screenshotCapture: WidgetScreenshotCapture(boundaryKey: GlobalKey()),
      );
      final handler = DeviceTestAgentCommandHandler(host: host);
      final outcome = await handler.handle(
        _command(AgentCommandNames.startRun, _runArguments('full')),
      );
      await pumpEventQueue();

      expect(outcome.status, AgentCommandStatus.completed);
      expect(harness.controller.state.screen, DeviceTestScreen.runner);
      expect(harness.controller.state.hasStoredSecrets, isTrue);
      expect(harness.runner.startRequest?.profile, TestProfile.full);
      expect(harness.runner.startRequest?.commissionee.vendorId, 1);
      expect(harness.runner.startRequest?.commissionee.productId, 1);
      expect(
        harness.runner.startRequest?.commissionee.commissioningTransport,
        isNull,
      );
    },
  );

  test('rejects a mode mismatch before touching the controller', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();
    final host = LiveDeviceTestAgentHost(
      controller: harness.controller,
      runner: harness.runner,
      screenshotCapture: WidgetScreenshotCapture(boundaryKey: GlobalKey()),
    );

    await expectLater(
      host.startRun(AgentRunMode.quick, _runArguments('full')),
      throwsA(
        isA<DeviceTestAgentHostException>().having(
          (error) => error.code,
          'code',
          'invalid_arguments',
        ),
      ),
    );
    expect(harness.runner.startRequest, isNull);
  });

  test('does not purge or replace an unfinished Run', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();
    final host = LiveDeviceTestAgentHost(
      controller: harness.controller,
      runner: harness.runner,
      screenshotCapture: WidgetScreenshotCapture(boundaryKey: GlobalKey()),
    );
    await host.startRun(AgentRunMode.quick, _runArguments('quick'));
    await pumpEventQueue();
    final savedBefore = Map<String, Object?>.of(harness.secrets.saved);

    await expectLater(
      host.startRun(AgentRunMode.quick, _runArguments('quick')),
      throwsA(
        isA<DeviceTestAgentHostException>().having(
          (error) => error.code,
          'code',
          'run_already_active',
        ),
      ),
    );
    expect(harness.secrets.saved, savedBefore);
  });

  test('maps missing setup fields to a field-only validation error', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();
    final host = LiveDeviceTestAgentHost(
      controller: harness.controller,
      runner: harness.runner,
      screenshotCapture: WidgetScreenshotCapture(boundaryKey: GlobalKey()),
    );
    final arguments = _runArguments('quick')..remove('setup_code');

    await expectLater(
      host.startRun(AgentRunMode.quick, arguments),
      throwsA(
        isA<DeviceTestAgentHostException>()
            .having((error) => error.code, 'code', 'invalid_arguments')
            .having(
              (error) => error.message,
              'message',
              contains('setup_code'),
            ),
      ),
    );
    expect(harness.runner.startRequest, isNull);
  });

  test('prompt commands fail safely when no prompt is active', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();
    final host = LiveDeviceTestAgentHost(
      controller: harness.controller,
      runner: harness.runner,
      screenshotCapture: WidgetScreenshotCapture(boundaryKey: GlobalKey()),
    );

    await expectLater(
      host.confirmPrompt('prompt-missing'),
      throwsA(
        isA<DeviceTestAgentHostException>().having(
          (error) => error.code,
          'code',
          'prompt_mismatch',
        ),
      ),
    );
    await expectLater(
      host.skipPrompt(promptId: 'prompt-missing', reason: 'Not ready.'),
      throwsA(isA<DeviceTestAgentHostException>()),
    );
    await expectLater(
      host.failPrompt(promptId: 'prompt-missing', reason: 'Not ready.'),
      throwsA(isA<DeviceTestAgentHostException>()),
    );
  });

  test(
    'maps unavailable screenshot and report artifacts to stable codes',
    () async {
      final harness = buildHarness(schemaJson: schemaJson);
      addTearDown(harness.close);
      await harness.controller.initialize();
      final host = LiveDeviceTestAgentHost(
        controller: harness.controller,
        runner: harness.runner,
        screenshotCapture: WidgetScreenshotCapture(boundaryKey: GlobalKey()),
      );

      await expectLater(
        host.captureScreenshot(),
        throwsA(
          isA<DeviceTestAgentHostException>().having(
            (error) => error.code,
            'code',
            'screenshot_unavailable',
          ),
        ),
      );
      await expectLater(
        host.buildReport(),
        throwsA(
          isA<DeviceTestAgentHostException>().having(
            (error) => error.code,
            'code',
            'report_not_ready',
          ),
        ),
      );
    },
  );
}

Map<String, Object?> _runArguments(String mode) {
  return <String, Object?>{
    'mode': mode,
    'setup_code': 'MT:TEST-SETUP-CODE',
    'wifi_ssid': 'Test Wi-Fi',
    'wifi_password': 'secret',
    'clean_cycle': <String, Object?>{'commissionee_clean': true},
  };
}

AgentCommand _command(String name, Map<String, Object?> arguments) {
  final payload = AgentCommandPayload(name: name, arguments: arguments);
  return AgentCommand(
    envelope: AgentEnvelope(
      type: AgentMessageType.command,
      sequence: 1,
      messageId: 'message-1',
      sentAt: DateTime.utc(2026, 11, 12),
      commandId: 'command-1',
      payload: payload.toJson(),
    ),
    command: payload,
  );
}
