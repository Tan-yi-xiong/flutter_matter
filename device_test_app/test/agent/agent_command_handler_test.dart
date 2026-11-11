import 'package:flutter_matter_device_test_app/src/agent/agent_bridge_client.dart';
import 'package:flutter_matter_device_test_app/src/agent/agent_command_handler.dart';
import 'package:flutter_matter_device_test_app/src/agent/protocol.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('DeviceTestAgentCommandHandler', () {
    late _RecordingHost host;
    late DeviceTestAgentCommandHandler handler;

    setUp(() {
      host = _RecordingHost();
      handler = DeviceTestAgentCommandHandler(host: host);
    });

    test('handle is assignable to the AgentCommandHandler typedef', () {
      final AgentCommandHandler bridged = handler.handle;

      expect(bridged, isNotNull);
    });

    group('start_run', () {
      test('starts a quick run and echoes only the validated mode', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.startRun, <String, Object?>{
            'mode': 'quick',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.data, <String, Object?>{'mode': 'quick'});
        expect(host.calls, <Object>[(method: 'startRun', detail: 'quick')]);
      });

      test('starts a full run', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.startRun, <String, Object?>{
            'mode': 'full',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.data, <String, Object?>{'mode': 'full'});
        expect(host.calls, <Object>[(method: 'startRun', detail: 'full')]);
      });

      test('rejects an unsupported mode without echoing it', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.startRun, <String, Object?>{
            'mode': 'ultra',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(outcome.errorMessage, contains('quick'));
        expect(outcome.errorMessage, isNot(contains('ultra')));
        expect(host.calls, isEmpty);
      });

      test('rejects a missing or non-string mode', () async {
        for (final arguments in <Map<String, Object?>>[
          <String, Object?>{},
          <String, Object?>{'mode': 42},
        ]) {
          final outcome = await handler.handle(
            _command(AgentCommandNames.startRun, arguments),
          );

          expect(outcome.status, AgentCommandStatus.failed);
          expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        }
        expect(host.calls, isEmpty);
      });

      test('rejects an unsupported argument key', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.startRun, <String, Object?>{
            'mode': 'quick',
            'profile': 'custom',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(outcome.errorMessage, isNot(contains('profile')));
        expect(host.calls, isEmpty);
      });
    });

    group('stop_run', () {
      test('stops the active run', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.stopRun, <String, Object?>{}),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.data, isEmpty);
        expect(host.calls, <Object>[(method: 'stopRun', detail: null)]);
      });

      test('rejects any argument', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.stopRun, <String, Object?>{'force': true}),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(host.calls, isEmpty);
      });
    });

    group('confirm_prompt', () {
      test('confirms the referenced prompt with a trimmed id', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.confirmPrompt, <String, Object?>{
            'prompt_id': ' prompt-1 ',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.data, isEmpty);
        expect(host.calls, <Object>[
          (method: 'confirmPrompt', detail: 'prompt-1'),
        ]);
      });

      test('rejects a missing, blank, or non-string prompt id', () async {
        for (final arguments in <Map<String, Object?>>[
          <String, Object?>{},
          <String, Object?>{'prompt_id': '   '},
          <String, Object?>{'prompt_id': 7},
        ]) {
          final outcome = await handler.handle(
            _command(AgentCommandNames.confirmPrompt, arguments),
          );

          expect(outcome.status, AgentCommandStatus.failed);
          expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        }
        expect(host.calls, isEmpty);
      });
    });

    group('skip_prompt', () {
      test('skips the prompt with a trimmed reason', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.skipPrompt, <String, Object?>{
            'prompt_id': 'prompt-2',
            'reason': ' operator deferred this step ',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(host.calls, <Object>[
          (
            method: 'skipPrompt',
            detail: 'prompt-2|operator deferred this step',
          ),
        ]);
      });

      test('rejects a missing reason', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.skipPrompt, <String, Object?>{
            'prompt_id': 'prompt-2',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(outcome.errorMessage, contains('reason'));
        expect(host.calls, isEmpty);
      });

      test('rejects a whitespace-only reason', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.skipPrompt, <String, Object?>{
            'prompt_id': 'prompt-2',
            'reason': '   ',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(host.calls, isEmpty);
      });
    });

    group('fail_prompt', () {
      test('fails the prompt with the given reason', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.failPrompt, <String, Object?>{
            'prompt_id': 'prompt-3',
            'reason': 'operator reported a hardware fault',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(host.calls, <Object>[
          (
            method: 'failPrompt',
            detail: 'prompt-3|operator reported a hardware fault',
          ),
        ]);
      });

      test('rejects a missing reason', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.failPrompt, <String, Object?>{
            'prompt_id': 'prompt-3',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(host.calls, isEmpty);
      });
    });

    group('screenshot', () {
      test('captures a screenshot without a label', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.screenshot, <String, Object?>{}),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.screenshot, isNotNull);
        expect(outcome.screenshot?.mimeType, 'image/png');
        expect(host.calls, <Object>[
          (method: 'captureScreenshot', detail: null),
        ]);
      });

      test('captures a labeled screenshot', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.screenshot, <String, Object?>{
            'label': 'home-screen',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.screenshot?.label, 'home-screen');
        expect(host.calls, <Object>[
          (method: 'captureScreenshot', detail: 'home-screen'),
        ]);
      });

      test('rejects a blank label', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.screenshot, <String, Object?>{
            'label': '   ',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(host.calls, isEmpty);
      });
    });

    group('report', () {
      test('builds the formal report for the current run', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.report, <String, Object?>{}),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(outcome.report, isNotNull);
        expect(outcome.report?.runId, 'run-1');
        expect(outcome.report?.sanitized, isTrue);
        expect(host.calls, <Object>[(method: 'buildReport', detail: null)]);
      });

      test('builds the report for a requested run', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.report, <String, Object?>{
            'run_id': 'run-42',
          }),
        );

        expect(outcome.status, AgentCommandStatus.completed);
        expect(host.calls, <Object>[(method: 'buildReport', detail: 'run-42')]);
      });

      test('rejects a non-string run id', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.report, <String, Object?>{'run_id': 42}),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(host.calls, isEmpty);
      });
    });

    group('unknown commands', () {
      test('fails without calling the host or echoing the name', () async {
        final outcome = await handler.handle(
          _command('self_destruct', <String, Object?>{
            'code': 'MT:VERY-PRIVATE-SETUP-CODE',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.unknownCommand);
        expect(outcome.errorMessage, isNot(contains('self_destruct')));
        expect(outcome.errorMessage, isNot(contains('MT:')));
        expect(host.calls, isEmpty);
      });
    });

    group('sensitive argument defense', () {
      test('rejects a reason that carries an onboarding payload', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.skipPrompt, <String, Object?>{
            'prompt_id': 'prompt-9',
            'reason': 'setup code MT:VERY-PRIVATE-SETUP-CODE was rejected',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(outcome.errorMessage, isNot(contains('MT:')));
        expect(host.calls, isEmpty);
      });

      test('rejects a label that carries a device address', () async {
        final outcome = await handler.handle(
          _command(AgentCommandNames.screenshot, <String, Object?>{
            'label': 'device 00:11:22:33:44:55',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.invalidArguments);
        expect(outcome.errorMessage, isNot(contains('00:11:22')));
        expect(host.calls, isEmpty);
      });
    });

    group('host failure mapping', () {
      test('forwards a controlled host exception code and message', () async {
        host.failWith(
          const DeviceTestAgentHostException(
            code: 'run_already_active',
            message: 'A run is already active.',
          ),
        );

        final outcome = await handler.handle(
          _command(AgentCommandNames.stopRun, <String, Object?>{}),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, 'run_already_active');
        expect(outcome.errorMessage, 'A run is already active.');
      });

      test('sanitizes a host exception message that leaks a secret', () async {
        host.failWith(
          const DeviceTestAgentHostException(
            code: 'prompt_failed',
            message: 'Rejected setup_code=MT:TOP-SECRET for this prompt.',
          ),
        );

        final outcome = await handler.handle(
          _command(AgentCommandNames.confirmPrompt, <String, Object?>{
            'prompt_id': 'prompt-4',
          }),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, 'prompt_failed');
        expect(outcome.errorMessage, 'The app rejected the command.');
        expect(outcome.errorMessage, isNot(contains('MT:TOP-SECRET')));
      });

      test('replaces a sensitive or empty host error code', () async {
        host.failWith(
          const DeviceTestAgentHostException(
            code: 'MT:BAD-CODE',
            message: 'Unusable.',
          ),
        );
        var outcome = await handler.handle(
          _command(AgentCommandNames.stopRun, <String, Object?>{}),
        );
        expect(outcome.errorCode, AgentCommandErrorCodes.hostFailed);

        host.failWith(
          const DeviceTestAgentHostException(code: '  ', message: 'No.'),
        );
        outcome = await handler.handle(
          _command(AgentCommandNames.stopRun, <String, Object?>{}),
        );
        expect(outcome.errorCode, AgentCommandErrorCodes.hostFailed);
      });

      test('maps an unexpected host error to a generic failure', () async {
        host.failWith(StateError('secret MT:UNEXPECTED leaked'));

        final outcome = await handler.handle(
          _command(AgentCommandNames.report, <String, Object?>{}),
        );

        expect(outcome.status, AgentCommandStatus.failed);
        expect(outcome.errorCode, AgentCommandErrorCodes.hostFailed);
        expect(outcome.errorMessage, 'The app failed to execute the command.');
        expect(outcome.errorMessage, isNot(contains('MT:UNEXPECTED')));
        expect(outcome.errorMessage, isNot(contains('StateError')));
      });

      test('truncates an over-long host message', () async {
        host.failWith(
          DeviceTestAgentHostException(
            code: 'verbose_failure',
            message: 'x' * 2000,
          ),
        );

        final outcome = await handler.handle(
          _command(AgentCommandNames.stopRun, <String, Object?>{}),
        );

        expect(outcome.errorMessage!.length, 512);
        expect(outcome.errorMessage, endsWith('...'));
      });
    });
  });
}

AgentCommand _command(
  String name, [
  Map<String, Object?> arguments = const <String, Object?>{},
]) {
  final payload = AgentCommandPayload(name: name, arguments: arguments);
  return AgentCommand(
    envelope: AgentEnvelope(
      type: AgentMessageType.command,
      sequence: 1,
      messageId: 'message-1',
      sentAt: DateTime.utc(2026, 1, 1),
      commandId: 'command-1',
      payload: payload.toJson(),
    ),
    command: payload,
  );
}

/// Compile-time fake that records every host call.
class _RecordingHost implements DeviceTestAgentHost {
  final List<({String method, String? detail})> calls =
      <({String method, String? detail})>[];
  Object? failure;

  void failWith(Object error) => failure = error;

  Future<void> _record(String method, String? detail) async {
    calls.add((method: method, detail: detail));
    final error = failure;
    if (error != null) {
      throw error;
    }
  }

  @override
  Future<void> startRun(AgentRunMode mode) async {
    await _record('startRun', mode.wireName);
  }

  @override
  Future<void> stopRun() async {
    await _record('stopRun', null);
  }

  @override
  Future<void> confirmPrompt(String promptId) async {
    await _record('confirmPrompt', promptId);
  }

  @override
  Future<void> skipPrompt({
    required String promptId,
    required String reason,
  }) async {
    await _record('skipPrompt', '$promptId|$reason');
  }

  @override
  Future<void> failPrompt({
    required String promptId,
    required String reason,
  }) async {
    await _record('failPrompt', '$promptId|$reason');
  }

  @override
  Future<AgentScreenshotPayload> captureScreenshot({String? label}) async {
    await _record('captureScreenshot', label);
    return AgentScreenshotPayload(
      mimeType: 'image/png',
      dataBase64: 'aGk=',
      capturedAt: DateTime.utc(2026, 1, 1),
      label: label,
      width: 4,
      height: 4,
    );
  }

  @override
  Future<AgentReportPayload> buildReport({String? runId}) async {
    await _record('buildReport', runId);
    return AgentReportPayload(
      runId: runId ?? 'run-1',
      reportJson: const <String, Object?>{'schema': 1},
      reportMarkdown: '# Device test report',
    );
  }
}
