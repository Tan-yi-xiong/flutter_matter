/// Transport-agnostic app-side router for protocol v1 agent commands.
///
/// The router validates the reserved command contract, forwards each call to
/// a [DeviceTestAgentHost], and converts the result into a sanitized
/// [AgentCommandOutcome]. Outcomes never echo raw command arguments,
/// provisioning secrets, device identifiers, raw exception text, or stack
/// traces.
library;

import '../report/sensitive_data_policy.dart';
import 'agent_bridge_client.dart';
import 'protocol.dart';

/// Reserved command names accepted by [DeviceTestAgentCommandHandler].
abstract final class AgentCommandNames {
  /// Starts a run: `{"mode": "quick" | "full"}`.
  static const String startRun = 'start_run';

  /// Stops the active run: `{}`.
  static const String stopRun = 'stop_run';

  /// Confirms the current prompt: `{"prompt_id": "..."}`.
  static const String confirmPrompt = 'confirm_prompt';

  /// Skips the current prompt: `{"prompt_id": "...", "reason": "..."}`.
  static const String skipPrompt = 'skip_prompt';

  /// Fails the current prompt: `{"prompt_id": "...", "reason": "..."}`.
  static const String failPrompt = 'fail_prompt';

  /// Captures an app screenshot: `{"label": "..."}` (optional).
  static const String screenshot = 'screenshot';

  /// Builds the formal report: `{"run_id": "..."}` (optional).
  static const String report = 'report';
}

/// Stable error codes produced by [DeviceTestAgentCommandHandler].
abstract final class AgentCommandErrorCodes {
  /// The command name is not part of the reserved v1 contract.
  static const String unknownCommand = 'unknown_command';

  /// A command argument failed validation.
  static const String invalidArguments = 'invalid_arguments';

  /// The host raised an unmapped or unexpected failure.
  static const String hostFailed = 'host_failed';
}

/// A controlled failure raised by a [DeviceTestAgentHost] implementation.
///
/// [code] must be a stable, machine-readable snake_case identifier that the
/// host CLI can branch on. [message] must be safe for public evidence: no
/// provisioning secrets, device identifiers, raw exception text, or stack
/// traces. The command router re-checks both fields with
/// [SensitiveDataPolicy] before forwarding them.
class DeviceTestAgentHostException implements Exception {
  const DeviceTestAgentHostException({
    required this.code,
    required this.message,
  });

  /// Stable snake_case failure identifier.
  final String code;

  /// Reviewer-safe explanation of the failure.
  final String message;

  @override
  String toString() => 'DeviceTestAgentHostException($code)';
}

/// The transport-agnostic operations behind the reserved agent commands.
///
/// Implementations adapt the app controller and runner. The interface is
/// intentionally independent of any concrete controller so the command
/// contract stays testable with compile-time fakes.
abstract interface class DeviceTestAgentHost {
  /// Starts a declarative run for [mode].
  Future<void> startRun(AgentRunMode mode);

  /// Stops the active run without manufacturing a passing report.
  Future<void> stopRun();

  /// Confirms the prompt identified by [promptId].
  Future<void> confirmPrompt(String promptId);

  /// Skips the prompt identified by [promptId] with a non-empty [reason].
  Future<void> skipPrompt({required String promptId, required String reason});

  /// Fails the prompt identified by [promptId] with a non-empty [reason].
  Future<void> failPrompt({required String promptId, required String reason});

  /// Captures a screenshot, optionally labeled.
  Future<AgentScreenshotPayload> captureScreenshot({String? label});

  /// Builds the sanitized formal report, optionally for a specific run.
  Future<AgentReportPayload> buildReport({String? runId});
}

/// Routes validated protocol v1 commands to a [DeviceTestAgentHost].
///
/// [handle] matches the [AgentCommandHandler] typedef used by
/// [AgentBridgeClient], so bootstrap code can wire it directly:
///
/// ```dart
/// final handler = DeviceTestAgentCommandHandler(host: myHost);
/// AgentBridgeClient(
///   ...,
///   onCommand: handler.handle,
/// );
/// ```
class DeviceTestAgentCommandHandler {
  /// Creates a router backed by [host].
  const DeviceTestAgentCommandHandler({required this.host});

  /// Maximum length of a host-provided failure message before truncation.
  static const int maxHostMessageLength = 512;

  /// The app operations used by the reserved commands.
  final DeviceTestAgentHost host;

  /// Handles one command. Any thrown error is mapped to a sanitized failure.
  Future<AgentCommandOutcome> handle(AgentCommand command) async {
    try {
      switch (command.command.name) {
        case AgentCommandNames.startRun:
          return await _startRun(command);
        case AgentCommandNames.stopRun:
          return await _stopRun(command);
        case AgentCommandNames.confirmPrompt:
          return await _confirmPrompt(command);
        case AgentCommandNames.skipPrompt:
          return await _skipPrompt(command);
        case AgentCommandNames.failPrompt:
          return await _failPrompt(command);
        case AgentCommandNames.screenshot:
          return await _screenshot(command);
        case AgentCommandNames.report:
          return await _report(command);
        default:
          return AgentCommandOutcome.failed(
            errorCode: AgentCommandErrorCodes.unknownCommand,
            errorMessage: 'The command is not supported by this app.',
          );
      }
    } on _InvalidArguments catch (error) {
      return AgentCommandOutcome.failed(
        errorCode: AgentCommandErrorCodes.invalidArguments,
        errorMessage: error.message,
      );
    } on DeviceTestAgentHostException catch (error) {
      return _hostFailure(error);
    } on Object {
      return AgentCommandOutcome.failed(
        errorCode: AgentCommandErrorCodes.hostFailed,
        errorMessage: 'The app failed to execute the command.',
      );
    }
  }

  Future<AgentCommandOutcome> _startRun(AgentCommand command) async {
    final arguments = _validatedArguments(command, const <String>{'mode'});
    final modeText = arguments['mode'];
    if (modeText is! String) {
      throw const _InvalidArguments(
        "start_run requires mode to be 'quick' or 'full'.",
      );
    }
    final mode = switch (modeText.trim()) {
      'quick' => AgentRunMode.quick,
      'full' => AgentRunMode.full,
      _ => null,
    };
    if (mode == null) {
      throw const _InvalidArguments(
        "start_run requires mode to be 'quick' or 'full'.",
      );
    }
    await host.startRun(mode);
    return AgentCommandOutcome.completed(
      data: <String, Object?>{'mode': mode.wireName},
    );
  }

  Future<AgentCommandOutcome> _stopRun(AgentCommand command) async {
    _validatedArguments(command, const <String>{});
    await host.stopRun();
    return const AgentCommandOutcome.completed();
  }

  Future<AgentCommandOutcome> _confirmPrompt(AgentCommand command) async {
    final arguments = _validatedArguments(command, const <String>{'prompt_id'});
    final promptId = _requiredArgument(
      arguments,
      'prompt_id',
      commandName: AgentCommandNames.confirmPrompt,
    );
    await host.confirmPrompt(promptId);
    return const AgentCommandOutcome.completed();
  }

  Future<AgentCommandOutcome> _skipPrompt(AgentCommand command) async {
    final arguments = _validatedArguments(command, const <String>{
      'prompt_id',
      'reason',
    });
    final promptId = _requiredArgument(
      arguments,
      'prompt_id',
      commandName: AgentCommandNames.skipPrompt,
    );
    final reason = _requiredArgument(
      arguments,
      'reason',
      commandName: AgentCommandNames.skipPrompt,
    );
    await host.skipPrompt(promptId: promptId, reason: reason);
    return const AgentCommandOutcome.completed();
  }

  Future<AgentCommandOutcome> _failPrompt(AgentCommand command) async {
    final arguments = _validatedArguments(command, const <String>{
      'prompt_id',
      'reason',
    });
    final promptId = _requiredArgument(
      arguments,
      'prompt_id',
      commandName: AgentCommandNames.failPrompt,
    );
    final reason = _requiredArgument(
      arguments,
      'reason',
      commandName: AgentCommandNames.failPrompt,
    );
    await host.failPrompt(promptId: promptId, reason: reason);
    return const AgentCommandOutcome.completed();
  }

  Future<AgentCommandOutcome> _screenshot(AgentCommand command) async {
    final arguments = _validatedArguments(command, const <String>{'label'});
    final label = _optionalArgument(
      arguments,
      'label',
      commandName: AgentCommandNames.screenshot,
    );
    final screenshot = await host.captureScreenshot(label: label);
    return AgentCommandOutcome.completed(screenshot: screenshot);
  }

  Future<AgentCommandOutcome> _report(AgentCommand command) async {
    final arguments = _validatedArguments(command, const <String>{'run_id'});
    final runId = _optionalArgument(
      arguments,
      'run_id',
      commandName: AgentCommandNames.report,
    );
    final report = await host.buildReport(runId: runId);
    return AgentCommandOutcome.completed(report: report);
  }

  /// Returns the command arguments after rejecting unsupported keys.
  Map<String, Object?> _validatedArguments(
    AgentCommand command,
    Set<String> allowedKeys,
  ) {
    for (final key in command.command.arguments.keys) {
      if (!allowedKeys.contains(key)) {
        throw _InvalidArguments(
          '${command.command.name} contains an unsupported argument.',
        );
      }
    }
    return command.command.arguments;
  }

  /// Validates a required string argument without echoing its value.
  String _requiredArgument(
    Map<String, Object?> arguments,
    String key, {
    required String commandName,
  }) {
    final value = arguments[key];
    if (value is! String) {
      throw _InvalidArguments(
        '$commandName requires $key to be a non-empty string.',
      );
    }
    final trimmed = value.trim();
    if (trimmed.isEmpty) {
      throw _InvalidArguments(
        '$commandName requires $key to be a non-empty string.',
      );
    }
    if (SensitiveDataPolicy.containsSensitiveData(trimmed)) {
      throw _InvalidArguments(
        '$commandName arguments must not contain sensitive values.',
      );
    }
    return trimmed;
  }

  /// Validates an optional string argument without echoing its value.
  String? _optionalArgument(
    Map<String, Object?> arguments,
    String key, {
    required String commandName,
  }) {
    if (arguments[key] == null) {
      return null;
    }
    return _requiredArgument(arguments, key, commandName: commandName);
  }

  /// Maps a controlled host failure, sanitizing code and message.
  AgentCommandOutcome _hostFailure(DeviceTestAgentHostException error) {
    var code = error.code.trim();
    if (code.isEmpty || SensitiveDataPolicy.containsSensitiveData(code)) {
      code = AgentCommandErrorCodes.hostFailed;
    }
    var message = error.message.trim();
    if (message.isEmpty || SensitiveDataPolicy.containsSensitiveData(message)) {
      message = 'The app rejected the command.';
    } else if (message.length > maxHostMessageLength) {
      message = '${message.substring(0, maxHostMessageLength - 3)}...';
    }
    return AgentCommandOutcome.failed(errorCode: code, errorMessage: message);
  }
}

class _InvalidArguments implements Exception {
  const _InvalidArguments(this.message);

  final String message;
}
