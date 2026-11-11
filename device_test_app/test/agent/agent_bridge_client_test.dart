import 'dart:convert';

import 'package:flutter_matter_device_test_app/src/agent/agent_bridge_client.dart';
import 'package:flutter_matter_device_test_app/src/agent/protocol.dart';
import 'package:flutter_test/flutter_test.dart';

import 'fake_websocket_channel.dart';

void main() {
  final hello = AgentHelloPayload(
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

  test(
    'sends hello first, then the latest state, with monotonic sequence',
    () async {
      final connector = FakeWebSocketConnector();
      final client = AgentBridgeClient(
        endpoint: Uri.parse('ws://127.0.0.1:8765/agent'),
        hello: hello,
        onCommand: (_) async => const AgentCommandOutcome.completed(),
        connector: connector.connect,
        reconnectDelay: const Duration(milliseconds: 1),
      );
      client.sendState(_idleState());

      await client.start();
      await _eventually(() => connector.channels.length == 1);
      final channel = connector.channels.single;
      await _eventually(() => channel.sent.length >= 2);

      final messages = channel.sent.map(_decode).toList();
      expect(messages[0].type, AgentMessageType.hello);
      expect(messages[1].type, AgentMessageType.state);
      expect(messages[0].sequence, 1);
      expect(messages[1].sequence, 2);

      client.sendEvent(
        const AgentEventPayload(kind: 'ready', message: 'Ready.'),
      );
      await _eventually(() => channel.sent.length >= 3);
      expect(_decode(channel.sent[2]).sequence, 3);

      await client.stop();
    },
  );

  test(
    'reconnects and continues the app sequence without resetting it',
    () async {
      final connector = FakeWebSocketConnector();
      final client = AgentBridgeClient(
        endpoint: Uri.parse('ws://127.0.0.1:8765/agent'),
        hello: hello,
        onCommand: (_) async => const AgentCommandOutcome.completed(),
        connector: connector.connect,
        reconnectDelay: const Duration(milliseconds: 1),
      );
      client.sendState(_idleState());
      await client.start();
      await _eventually(() => connector.channels.length == 1);
      final first = connector.channels[0];
      await _eventually(() => first.sent.length >= 2);
      final lastFirstSequence = _decode(first.sent.last).sequence;

      await first.disconnectFromHost();
      await _eventually(() => connector.channels.length == 2);
      final second = connector.channels[1];
      await _eventually(() => second.sent.length >= 2);

      final reconnectMessages = second.sent.map(_decode).toList();
      expect(reconnectMessages[0].type, AgentMessageType.hello);
      expect(reconnectMessages[1].type, AgentMessageType.state);
      expect(reconnectMessages[0].sequence, greaterThan(lastFirstSequence));

      await client.stop();
    },
  );

  test('deduplicates command IDs and returns cached results', () async {
    final connector = FakeWebSocketConnector();
    var executions = 0;
    final client = AgentBridgeClient(
      endpoint: Uri.parse('ws://127.0.0.1:8765/agent'),
      hello: hello,
      onCommand: (command) async {
        executions++;
        return AgentCommandOutcome.completed(
          data: <String, Object?>{'command': command.command.name},
        );
      },
      connector: connector.connect,
      reconnectDelay: const Duration(milliseconds: 1),
    );
    await client.start();
    await _eventually(() => connector.channels.length == 1);
    final channel = connector.channels.single;
    await _eventually(() => channel.sent.isNotEmpty);

    channel.addFromHost(_commandEnvelope(sequence: 1, commandId: 'command-1'));
    await _eventually(
      () => channel.sent.any((message) {
        final decoded = _decode(message);
        return decoded.type == AgentMessageType.commandResult;
      }),
    );

    channel.addFromHost(_commandEnvelope(sequence: 2, commandId: 'command-1'));
    await _eventually(
      () =>
          channel.sent.where((message) {
            return _decode(message).type == AgentMessageType.commandResult;
          }).length ==
          2,
    );

    final results = channel.sent
        .map(_decode)
        .where((message) => message.type == AgentMessageType.commandResult)
        .toList();
    expect(executions, 1);
    expect(
      AgentCommandResultPayload.fromJson(results[0].payload).status,
      AgentCommandStatus.completed,
    );
    expect(
      AgentCommandResultPayload.fromJson(results[1].payload).status,
      AgentCommandStatus.duplicate,
    );
    expect(
      results.every((message) => message.commandId == 'command-1'),
      isTrue,
    );

    await client.stop();
  });

  test(
    'sends screenshot and report artifacts before the command result',
    () async {
      final connector = FakeWebSocketConnector();
      final screenshot = AgentScreenshotPayload(
        mimeType: 'image/png',
        dataBase64: base64Encode(<int>[1, 2, 3]),
        capturedAt: DateTime.utc(2026, 11, 11, 12),
        label: 'runner',
      );
      final report = AgentReportPayload(
        runId: 'run-1',
        reportJson: const <String, Object?>{'schema_version': 1},
        reportMarkdown: '### Device validation summary\n',
      );
      final client = AgentBridgeClient(
        endpoint: Uri.parse('ws://127.0.0.1:8765/agent'),
        hello: hello,
        onCommand: (_) async => AgentCommandOutcome.completed(
          screenshot: screenshot,
          report: report,
        ),
        connector: connector.connect,
        reconnectDelay: const Duration(milliseconds: 1),
      );
      await client.start();
      await _eventually(() => connector.channels.length == 1);
      final channel = connector.channels.single;
      await _eventually(() => channel.sent.isNotEmpty);

      channel.addFromHost(
        _commandEnvelope(sequence: 1, commandId: 'artifact-command'),
      );
      await _eventually(() => channel.sent.length >= 4);

      final messages = channel.sent.map(_decode).toList();
      expect(messages.map((message) => message.type), <AgentMessageType>[
        AgentMessageType.hello,
        AgentMessageType.screenshot,
        AgentMessageType.report,
        AgentMessageType.commandResult,
      ]);
      expect(
        messages
            .skip(1)
            .every((message) => message.commandId == 'artifact-command'),
        isTrue,
      );

      await client.stop();
    },
  );
}

AgentStatePayload _idleState() => const AgentStatePayload(
  status: AgentRunStatus.idle,
  mode: AgentRunMode.none,
  completedTests: 0,
  totalTests: 13,
);

AgentEnvelope _decode(String source) => AgentEnvelope.fromJsonString(source);

String _commandEnvelope({required int sequence, required String commandId}) {
  return AgentEnvelope(
    type: AgentMessageType.command,
    sequence: sequence,
    messageId: 'host-message-$sequence',
    sentAt: DateTime.utc(2026, 11, 11, 12).add(Duration(seconds: sequence)),
    commandId: commandId,
    payload: const AgentCommandPayload(
      name: 'noop',
      arguments: <String, Object?>{'value': 1},
    ).toJson(),
  ).toJsonString();
}

Future<void> _eventually(bool Function() predicate) async {
  final deadline = DateTime.now().add(const Duration(seconds: 3));
  while (!predicate()) {
    if (!DateTime.now().isBefore(deadline)) {
      fail('Condition was not met before timeout.');
    }
    await Future<void>.delayed(const Duration(milliseconds: 10));
  }
}
