/// Protocol v1 for communication between the device-test app and the host CLI.
///
/// The protocol is intentionally transport-neutral. The app uses a WebSocket
/// client, while tests may build envelopes directly.
library;

import 'dart:convert';
import 'dart:math';

const String agentProtocolName = 'flutter_matter.device_test_agent';
const int agentProtocolVersion = 1;

final Random _idRandom = Random.secure();

/// Creates an opaque identifier suitable for message and app-instance IDs.
String newAgentId({String prefix = 'agent'}) {
  final bytes = List<int>.generate(16, (_) => _idRandom.nextInt(256));
  final hex = bytes
      .map((value) => value.toRadixString(16).padLeft(2, '0'))
      .join();
  return '$prefix-$hex';
}

/// The message types defined by protocol v1.
enum AgentMessageType {
  hello,
  state,
  event,
  command,
  commandResult,
  screenshot,
  report,
  error,
}

extension AgentMessageTypeWire on AgentMessageType {
  String get wireName => switch (this) {
    AgentMessageType.hello => 'hello',
    AgentMessageType.state => 'state',
    AgentMessageType.event => 'event',
    AgentMessageType.command => 'command',
    AgentMessageType.commandResult => 'command_result',
    AgentMessageType.screenshot => 'screenshot',
    AgentMessageType.report => 'report',
    AgentMessageType.error => 'error',
  };
}

AgentMessageType agentMessageTypeFromWire(Object? value) {
  return switch (value) {
    'hello' => AgentMessageType.hello,
    'state' => AgentMessageType.state,
    'event' => AgentMessageType.event,
    'command' => AgentMessageType.command,
    'command_result' => AgentMessageType.commandResult,
    'screenshot' => AgentMessageType.screenshot,
    'report' => AgentMessageType.report,
    'error' => AgentMessageType.error,
    _ => throw AgentProtocolException('Unsupported message type: $value'),
  };
}

/// The lifecycle phase reported by the app runner.
enum AgentRunStatus {
  idle,
  running,
  waitingForApp,
  waitingForAgentAndroid,
  waitingForHuman,
  passed,
  failed,
  notRun,
  stopped,
}

extension AgentRunStatusWire on AgentRunStatus {
  String get wireName => switch (this) {
    AgentRunStatus.idle => 'idle',
    AgentRunStatus.running => 'running',
    AgentRunStatus.waitingForApp => 'waiting_for_app',
    AgentRunStatus.waitingForAgentAndroid => 'waiting_for_agent_android',
    AgentRunStatus.waitingForHuman => 'waiting_for_human',
    AgentRunStatus.passed => 'passed',
    AgentRunStatus.failed => 'failed',
    AgentRunStatus.notRun => 'not_run',
    AgentRunStatus.stopped => 'stopped',
  };

  static AgentRunStatus parse(Object? value) => switch (value) {
    'idle' => AgentRunStatus.idle,
    'running' => AgentRunStatus.running,
    'waiting_for_app' => AgentRunStatus.waitingForApp,
    'waiting_for_agent_android' => AgentRunStatus.waitingForAgentAndroid,
    'waiting_for_human' => AgentRunStatus.waitingForHuman,
    'passed' => AgentRunStatus.passed,
    'failed' => AgentRunStatus.failed,
    'not_run' => AgentRunStatus.notRun,
    'stopped' => AgentRunStatus.stopped,
    _ => throw AgentProtocolException('Unsupported run status: $value'),
  };
}

enum AgentRunMode { none, quick, full }

extension AgentRunModeWire on AgentRunMode {
  String get wireName => switch (this) {
    AgentRunMode.none => 'none',
    AgentRunMode.quick => 'quick',
    AgentRunMode.full => 'full',
  };

  static AgentRunMode parse(Object? value) => switch (value) {
    'none' => AgentRunMode.none,
    'quick' => AgentRunMode.quick,
    'full' => AgentRunMode.full,
    _ => throw AgentProtocolException('Unsupported run mode: $value'),
  };
}

enum AgentPromptChannel { agentAndroid, human }

extension AgentPromptChannelWire on AgentPromptChannel {
  String get wireName => switch (this) {
    AgentPromptChannel.agentAndroid => 'agent_android',
    AgentPromptChannel.human => 'human',
  };

  static AgentPromptChannel parse(Object? value) => switch (value) {
    'agent_android' => AgentPromptChannel.agentAndroid,
    'human' => AgentPromptChannel.human,
    _ => throw AgentProtocolException('Unsupported prompt channel: $value'),
  };
}

enum AgentEventSeverity { debug, info, warning, error }

extension AgentEventSeverityWire on AgentEventSeverity {
  String get wireName => name;

  static AgentEventSeverity parse(Object? value) => switch (value) {
    'debug' => AgentEventSeverity.debug,
    'info' => AgentEventSeverity.info,
    'warning' => AgentEventSeverity.warning,
    'error' => AgentEventSeverity.error,
    _ => throw AgentProtocolException('Unsupported event severity: $value'),
  };
}

enum AgentCommandStatus { completed, failed, duplicate }

extension AgentCommandStatusWire on AgentCommandStatus {
  String get wireName => name;

  static AgentCommandStatus parse(Object? value) => switch (value) {
    'completed' => AgentCommandStatus.completed,
    'failed' => AgentCommandStatus.failed,
    'duplicate' => AgentCommandStatus.duplicate,
    _ => throw AgentProtocolException('Unsupported command status: $value'),
  };
}

/// A protocol error caused by malformed or incompatible JSON.
class AgentProtocolException implements Exception {
  AgentProtocolException(this.message);

  final String message;

  @override
  String toString() => 'AgentProtocolException: $message';
}

/// The common v1 envelope shared by every message.
///
/// Each sender increments [sequence] for every message it transmits. A bridge
/// instance keeps its sequence moving forward across reconnects. A new app
/// process gets a new [AgentHelloPayload.instanceId] and may reset to sequence
/// one. Receivers reject non-increasing sequence values within one instance.
class AgentEnvelope {
  const AgentEnvelope({
    required this.type,
    required this.sequence,
    required this.messageId,
    required this.sentAt,
    required this.payload,
    this.commandId,
  });

  final AgentMessageType type;
  final int sequence;
  final String messageId;
  final DateTime sentAt;
  final String? commandId;
  final Map<String, Object?> payload;

  factory AgentEnvelope.fromJson(Map<String, Object?> json) {
    if (json['protocol'] != agentProtocolName) {
      throw AgentProtocolException('Unsupported protocol: ${json['protocol']}');
    }
    if (json['version'] != agentProtocolVersion) {
      throw AgentProtocolException(
        'Unsupported protocol version: ${json['version']}',
      );
    }
    final sequence = _requiredInt(json, 'sequence');
    if (sequence < 1) {
      throw AgentProtocolException('sequence must be positive');
    }
    final messageId = _requiredString(json, 'message_id');
    final sentAtText = _requiredString(json, 'sent_at');
    final sentAt = DateTime.tryParse(sentAtText);
    if (sentAt == null) {
      throw AgentProtocolException('sent_at must be an ISO-8601 timestamp');
    }
    final commandId = json['command_id'];
    if (commandId != null && (commandId is! String || commandId.isEmpty)) {
      throw AgentProtocolException('command_id must be a non-empty string');
    }
    return AgentEnvelope(
      type: agentMessageTypeFromWire(json['type']),
      sequence: sequence,
      messageId: messageId,
      sentAt: sentAt.toUtc(),
      commandId: commandId as String?,
      payload: _requiredMap(json, 'payload'),
    );
  }

  factory AgentEnvelope.fromJsonString(String source) {
    final decoded = jsonDecode(source);
    if (decoded is! Map) {
      throw AgentProtocolException('Message must be a JSON object');
    }
    return AgentEnvelope.fromJson(_stringKeyedMap(decoded));
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'protocol': agentProtocolName,
    'version': agentProtocolVersion,
    'type': type.wireName,
    'sequence': sequence,
    'message_id': messageId,
    'sent_at': sentAt.toUtc().toIso8601String(),
    if (commandId != null) 'command_id': commandId,
    'payload': payload,
  };

  String toJsonString() => jsonEncode(toJson());
}

/// App identity and runtime capabilities advertised after every reconnect.
class AgentHelloPayload {
  const AgentHelloPayload({
    required this.instanceId,
    required this.appName,
    required this.appVersion,
    required this.appBuild,
    required this.appCommit,
    required this.pluginCommit,
    required this.controllerPlatform,
    required this.deviceModel,
    required this.osVersion,
    required this.capabilities,
  });

  final String instanceId;
  final String appName;
  final String appVersion;
  final String appBuild;
  final String appCommit;
  final String pluginCommit;
  final String controllerPlatform;
  final String deviceModel;
  final String osVersion;
  final List<String> capabilities;

  Map<String, Object?> toJson() => <String, Object?>{
    'instance_id': instanceId,
    'app_name': appName,
    'app_version': appVersion,
    'app_build': appBuild,
    'app_commit': appCommit,
    'plugin_commit': pluginCommit,
    'controller_platform': controllerPlatform,
    'device_model': deviceModel,
    'os_version': osVersion,
    'capabilities': capabilities,
  };

  factory AgentHelloPayload.fromJson(Map<String, Object?> json) {
    final capabilities = json['capabilities'];
    if (capabilities is! List ||
        capabilities.any((value) => value is! String)) {
      throw AgentProtocolException('hello.capabilities must be a string array');
    }
    return AgentHelloPayload(
      instanceId: _requiredString(json, 'instance_id'),
      appName: _requiredString(json, 'app_name'),
      appVersion: _requiredString(json, 'app_version'),
      appBuild: _requiredString(json, 'app_build'),
      appCommit: _requiredString(json, 'app_commit'),
      pluginCommit: _requiredString(json, 'plugin_commit'),
      controllerPlatform: _requiredString(json, 'controller_platform'),
      deviceModel: _requiredString(json, 'device_model'),
      osVersion: _requiredString(json, 'os_version'),
      capabilities: List<String>.unmodifiable(capabilities.cast<String>()),
    );
  }
}

/// A prompt that tells the agent or operator which external action to perform.
class AgentPrompt {
  const AgentPrompt({
    required this.promptId,
    required this.channel,
    required this.title,
    required this.instructions,
    this.action,
    this.testId,
    this.confirmLabel = 'Confirm',
    this.canSkip = true,
    this.skipRequiresReason = true,
  });

  final String promptId;
  final AgentPromptChannel channel;
  final String title;
  final String instructions;
  final String? action;
  final String? testId;
  final String confirmLabel;
  final bool canSkip;
  final bool skipRequiresReason;

  Map<String, Object?> toJson() => <String, Object?>{
    'prompt_id': promptId,
    'channel': channel.wireName,
    'title': title,
    'instructions': instructions,
    if (action != null) 'action': action,
    if (testId != null) 'test_id': testId,
    'confirm_label': confirmLabel,
    'can_skip': canSkip,
    'skip_requires_reason': skipRequiresReason,
  };

  factory AgentPrompt.fromJson(Map<String, Object?> json) => AgentPrompt(
    promptId: _requiredString(json, 'prompt_id'),
    channel: AgentPromptChannelWire.parse(json['channel']),
    title: _requiredString(json, 'title'),
    instructions: _requiredString(json, 'instructions'),
    action: _optionalString(json, 'action'),
    testId: _optionalString(json, 'test_id'),
    confirmLabel: _optionalString(json, 'confirm_label') ?? 'Confirm',
    canSkip: json['can_skip'] != false,
    skipRequiresReason: json['skip_requires_reason'] != false,
  );
}

/// Semantic runner state. Callers must keep secrets out of [message] and
/// [details]; the host only needs status and actionable prompt information.
class AgentStatePayload {
  const AgentStatePayload({
    required this.status,
    required this.mode,
    required this.completedTests,
    required this.totalTests,
    this.runId,
    this.currentTestId,
    this.message,
    this.prompt,
    this.details = const <String, Object?>{},
  });

  final String? runId;
  final AgentRunStatus status;
  final AgentRunMode mode;
  final String? currentTestId;
  final int completedTests;
  final int totalTests;
  final String? message;
  final AgentPrompt? prompt;
  final Map<String, Object?> details;

  Map<String, Object?> toJson() => <String, Object?>{
    if (runId != null) 'run_id': runId,
    'status': status.wireName,
    'mode': mode.wireName,
    if (currentTestId != null) 'current_test_id': currentTestId,
    'completed_tests': completedTests,
    'total_tests': totalTests,
    if (message != null) 'message': message,
    if (prompt != null) 'prompt': prompt!.toJson(),
    'details': details,
  };

  factory AgentStatePayload.fromJson(Map<String, Object?> json) {
    final completed = _requiredInt(json, 'completed_tests');
    final total = _requiredInt(json, 'total_tests');
    if (completed < 0 || total < 0 || completed > total) {
      throw AgentProtocolException('Invalid completed/total test counts');
    }
    final promptJson = json['prompt'];
    return AgentStatePayload(
      runId: _optionalString(json, 'run_id'),
      status: AgentRunStatusWire.parse(json['status']),
      mode: AgentRunModeWire.parse(json['mode']),
      currentTestId: _optionalString(json, 'current_test_id'),
      completedTests: completed,
      totalTests: total,
      message: _optionalString(json, 'message'),
      prompt: promptJson == null
          ? null
          : AgentPrompt.fromJson(_asStringKeyedMap(promptJson, 'state.prompt')),
      details: _optionalMap(json, 'details'),
    );
  }
}

/// A monotonic, reviewer-safe event stream entry.
class AgentEventPayload {
  const AgentEventPayload({
    required this.kind,
    required this.message,
    this.severity = AgentEventSeverity.info,
    this.testId,
    this.data = const <String, Object?>{},
  });

  final String kind;
  final AgentEventSeverity severity;
  final String message;
  final String? testId;
  final Map<String, Object?> data;

  Map<String, Object?> toJson() => <String, Object?>{
    'kind': kind,
    'severity': severity.wireName,
    'message': message,
    if (testId != null) 'test_id': testId,
    'data': data,
  };

  factory AgentEventPayload.fromJson(Map<String, Object?> json) =>
      AgentEventPayload(
        kind: _requiredString(json, 'kind'),
        severity: AgentEventSeverityWire.parse(json['severity']),
        message: _requiredString(json, 'message'),
        testId: _optionalString(json, 'test_id'),
        data: _optionalMap(json, 'data'),
      );
}

/// A host-to-app command. Retries must reuse [commandId].
class AgentCommandPayload {
  const AgentCommandPayload({
    required this.name,
    this.arguments = const <String, Object?>{},
  });

  final String name;
  final Map<String, Object?> arguments;

  Map<String, Object?> toJson() => <String, Object?>{
    'name': name,
    'arguments': arguments,
  };

  factory AgentCommandPayload.fromJson(Map<String, Object?> json) =>
      AgentCommandPayload(
        name: _requiredString(json, 'name'),
        arguments: _optionalMap(json, 'arguments'),
      );
}

/// A typed command received by the app.
class AgentCommand {
  const AgentCommand({required this.envelope, required this.command});

  final AgentEnvelope envelope;
  final AgentCommandPayload command;

  String get commandId {
    final id = envelope.commandId;
    if (id == null || id.isEmpty) {
      throw AgentProtocolException('command messages require command_id');
    }
    return id;
  }
}

/// The terminal result of a command execution.
class AgentCommandResultPayload {
  const AgentCommandResultPayload({
    required this.status,
    this.data = const <String, Object?>{},
    this.errorCode,
    this.errorMessage,
  });

  final AgentCommandStatus status;
  final Map<String, Object?> data;
  final String? errorCode;
  final String? errorMessage;

  Map<String, Object?> toJson() => <String, Object?>{
    'status': status.wireName,
    'data': data,
    if (errorCode != null) 'error_code': errorCode,
    if (errorMessage != null) 'error_message': errorMessage,
  };

  factory AgentCommandResultPayload.fromJson(Map<String, Object?> json) {
    final status = AgentCommandStatusWire.parse(json['status']);
    final errorCode = _optionalString(json, 'error_code');
    if (status == AgentCommandStatus.failed && errorCode == null) {
      throw AgentProtocolException('failed command results require error_code');
    }
    return AgentCommandResultPayload(
      status: status,
      data: _optionalMap(json, 'data'),
      errorCode: errorCode,
      errorMessage: _optionalString(json, 'error_message'),
    );
  }
}

/// A PNG (or future image type) captured by the app.
class AgentScreenshotPayload {
  const AgentScreenshotPayload({
    required this.mimeType,
    required this.dataBase64,
    required this.capturedAt,
    this.label,
    this.width,
    this.height,
  });

  final String mimeType;
  final String dataBase64;
  final DateTime capturedAt;
  final String? label;
  final int? width;
  final int? height;

  Map<String, Object?> toJson() => <String, Object?>{
    'mime_type': mimeType,
    'data_base64': dataBase64,
    'captured_at': capturedAt.toUtc().toIso8601String(),
    if (label != null) 'label': label,
    if (width != null) 'width': width,
    if (height != null) 'height': height,
  };

  factory AgentScreenshotPayload.fromJson(Map<String, Object?> json) {
    final capturedAt = DateTime.tryParse(_requiredString(json, 'captured_at'));
    if (capturedAt == null) {
      throw AgentProtocolException('screenshot.captured_at must be ISO-8601');
    }
    return AgentScreenshotPayload(
      mimeType: _requiredString(json, 'mime_type'),
      dataBase64: _requiredString(json, 'data_base64'),
      capturedAt: capturedAt.toUtc(),
      label: _optionalString(json, 'label'),
      width: _optionalInt(json, 'width'),
      height: _optionalInt(json, 'height'),
    );
  }
}

/// A sanitized report generated from one test run.
class AgentReportPayload {
  const AgentReportPayload({
    required this.runId,
    required this.reportJson,
    required this.reportMarkdown,
    this.sanitized = true,
  });

  final String runId;
  final Map<String, Object?> reportJson;
  final String reportMarkdown;
  final bool sanitized;

  Map<String, Object?> toJson() => <String, Object?>{
    'run_id': runId,
    'report_json': reportJson,
    'report_markdown': reportMarkdown,
    'sanitized': sanitized,
  };

  factory AgentReportPayload.fromJson(Map<String, Object?> json) {
    final sanitized = json['sanitized'];
    if (sanitized is! bool) {
      throw AgentProtocolException('report.sanitized must be a boolean');
    }
    return AgentReportPayload(
      runId: _requiredString(json, 'run_id'),
      reportJson: _requiredMap(json, 'report_json'),
      reportMarkdown: _requiredString(json, 'report_markdown'),
      sanitized: sanitized,
    );
  }
}

/// A protocol-level error that does not terminate the socket.
class AgentErrorPayload {
  const AgentErrorPayload({
    required this.code,
    required this.message,
    this.retryable = false,
    this.details = const <String, Object?>{},
  });

  final String code;
  final String message;
  final bool retryable;
  final Map<String, Object?> details;

  Map<String, Object?> toJson() => <String, Object?>{
    'code': code,
    'message': message,
    'retryable': retryable,
    'details': details,
  };

  factory AgentErrorPayload.fromJson(Map<String, Object?> json) =>
      AgentErrorPayload(
        code: _requiredString(json, 'code'),
        message: _requiredString(json, 'message'),
        retryable: json['retryable'] == true,
        details: _optionalMap(json, 'details'),
      );
}

Map<String, Object?> _stringKeyedMap(Map<Object?, Object?> source) {
  return <String, Object?>{
    for (final entry in source.entries) entry.key.toString(): entry.value,
  };
}

Map<String, Object?> _asStringKeyedMap(Object? value, String field) {
  if (value is! Map) {
    throw AgentProtocolException('$field must be an object');
  }
  return _stringKeyedMap(value);
}

Map<String, Object?> _requiredMap(Map<String, Object?> json, String field) {
  final value = json[field];
  if (value == null) {
    throw AgentProtocolException('$field is required');
  }
  return _asStringKeyedMap(value, field);
}

Map<String, Object?> _optionalMap(Map<String, Object?> json, String field) {
  final value = json[field];
  if (value == null) {
    return const <String, Object?>{};
  }
  return _asStringKeyedMap(value, field);
}

String _requiredString(Map<String, Object?> json, String field) {
  final value = json[field];
  if (value is! String || value.isEmpty) {
    throw AgentProtocolException('$field must be a non-empty string');
  }
  return value;
}

String? _optionalString(Map<String, Object?> json, String field) {
  final value = json[field];
  if (value == null) {
    return null;
  }
  if (value is! String || value.isEmpty) {
    throw AgentProtocolException(
      '$field must be a non-empty string when present',
    );
  }
  return value;
}

int _requiredInt(Map<String, Object?> json, String field) {
  final value = json[field];
  if (value is! int) {
    throw AgentProtocolException('$field must be an integer');
  }
  return value;
}

int? _optionalInt(Map<String, Object?> json, String field) {
  final value = json[field];
  if (value == null) {
    return null;
  }
  if (value is! int) {
    throw AgentProtocolException('$field must be an integer when present');
  }
  return value;
}
