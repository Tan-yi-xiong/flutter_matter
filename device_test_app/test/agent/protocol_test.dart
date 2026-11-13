import 'package:flutter_matter_device_test_app/src/agent/protocol.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('protocol v1 round-trips a hello envelope', () {
    final payload = AgentHelloPayload(
      instanceId: 'instance-1',
      appName: 'flutter_matter device test app',
      appVersion: '1.0.0',
      appBuild: '1',
      appCommit: 'a' * 40,
      pluginCommit: 'b' * 40,
      controllerPlatform: 'android',
      deviceModel: 'PH-1',
      osVersion: '12',
      capabilities: const <String>[
        'state',
        'event',
        'command',
        'screenshot',
        'report',
      ],
    );
    final envelope = AgentEnvelope(
      type: AgentMessageType.hello,
      sequence: 1,
      messageId: 'message-1',
      sentAt: DateTime.utc(2026, 11, 11, 12),
      payload: payload.toJson(),
    );

    final decoded = AgentEnvelope.fromJsonString(envelope.toJsonString());
    final decodedHello = AgentHelloPayload.fromJson(decoded.payload);

    expect(decoded.type, AgentMessageType.hello);
    expect(decoded.sequence, 1);
    expect(decodedHello.instanceId, 'instance-1');
    expect(decodedHello.capabilities, contains('report'));
  });

  test('protocol rejects an unsupported version', () {
    expect(
      () => AgentEnvelope.fromJson(<String, Object?>{
        'protocol': agentProtocolName,
        'version': 99,
        'type': 'hello',
        'sequence': 1,
        'message_id': 'message-1',
        'sent_at': '2026-11-11T12:00:00Z',
        'payload': <String, Object?>{},
      }),
      throwsA(isA<AgentProtocolException>()),
    );
  });

  test('event, command, screenshot, and report payloads round-trip', () {
    final event = AgentEventPayload(
      kind: 'test_completed',
      severity: AgentEventSeverity.info,
      message: 'Commissioning passed.',
      testId: 'commissioning',
      data: const <String, Object?>{'duration_ms': 1234},
    ).toJson();
    expect(AgentEventPayload.fromJson(event).testId, 'commissioning');

    final command = AgentCommandPayload(
      name: 'start_run',
      arguments: const <String, Object?>{'mode': 'quick'},
    ).toJson();
    expect(AgentCommandPayload.fromJson(command).name, 'start_run');

    final screenshot = AgentScreenshotPayload(
      mimeType: 'image/png',
      dataBase64: 'AQID',
      capturedAt: DateTime.utc(2026, 11, 11, 12),
      label: 'onoff',
      width: 1,
      height: 1,
    ).toJson();
    expect(AgentScreenshotPayload.fromJson(screenshot).mimeType, 'image/png');

    final report = AgentReportPayload(
      runId: 'run-1',
      reportJson: const <String, Object?>{'schema_version': 3},
      reportMarkdown: '### Device validation summary\n',
    ).toJson();
    expect(AgentReportPayload.fromJson(report).sanitized, isTrue);
  });

  test('state and prompt payloads expose semantic waiting information', () {
    final state = AgentStatePayload(
      runId: 'run-1',
      status: AgentRunStatus.waitingForAgentAndroid,
      mode: AgentRunMode.quick,
      currentTestId: 'commissioning',
      completedTests: 2,
      totalTests: 12,
      message: 'Confirm the Android Bluetooth dialog.',
      prompt: const AgentPrompt(
        promptId: 'prompt-1',
        channel: AgentPromptChannel.agentAndroid,
        title: 'Bluetooth permission',
        instructions: 'Tap Allow.',
        action: 'accept_bluetooth_dialog',
        testId: 'commissioning',
      ),
    );

    final decoded = AgentStatePayload.fromJson(state.toJson());
    expect(decoded.status, AgentRunStatus.waitingForAgentAndroid);
    expect(decoded.prompt?.channel, AgentPromptChannel.agentAndroid);
    expect(decoded.completedTests, 2);
  });
}
