/// Reconnect-friendly app-side client for protocol v1.
library;

import 'dart:async';
import 'dart:collection';
import 'dart:convert';

import 'package:web_socket_channel/io.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

import 'protocol.dart';

/// Creates a WebSocket channel for [uri]. Tests inject a fake factory.
typedef AgentWebSocketConnector = WebSocketChannel Function(Uri uri);

/// Handles one command. Throwing is treated as a failed command.
typedef AgentCommandHandler =
    Future<AgentCommandOutcome> Function(AgentCommand command);

/// Reported connection state for app diagnostics and UI.
enum AgentBridgeConnectionState {
  stopped,
  connecting,
  connected,
  waitingToReconnect,
}

/// Optional artifacts returned with a command result.
class AgentCommandOutcome {
  const AgentCommandOutcome({
    required this.status,
    this.data = const <String, Object?>{},
    this.errorCode,
    this.errorMessage,
    this.screenshot,
    this.report,
  });

  const AgentCommandOutcome.completed({
    Map<String, Object?> data = const <String, Object?>{},
    AgentScreenshotPayload? screenshot,
    AgentReportPayload? report,
  }) : this(
         status: AgentCommandStatus.completed,
         data: data,
         screenshot: screenshot,
         report: report,
       );

  const AgentCommandOutcome.failed({
    required String errorCode,
    required String errorMessage,
    Map<String, Object?> data = const <String, Object?>{},
  }) : this(
         status: AgentCommandStatus.failed,
         data: data,
         errorCode: errorCode,
         errorMessage: errorMessage,
       );

  final AgentCommandStatus status;
  final Map<String, Object?> data;
  final String? errorCode;
  final String? errorMessage;
  final AgentScreenshotPayload? screenshot;
  final AgentReportPayload? report;
}

/// Maintains a WebSocket session to the host CLI.
///
/// Messages are sequenced per app process and continue across reconnects. The
/// latest semantic state is resent after each reconnect. Commands are executed
/// serially and cached by command ID so a host retry never repeats side effects.
class AgentBridgeClient {
  AgentBridgeClient({
    required this.endpoint,
    required this.hello,
    required AgentCommandHandler onCommand,
    AgentWebSocketConnector? connector,
    this.connectTimeout = const Duration(seconds: 8),
    this.reconnectDelay = const Duration(seconds: 1),
    this.maxReconnectDelay = const Duration(seconds: 30),
    this.maxBufferedMessages = 200,
    this.commandCacheSize = 256,
  }) : _onCommand = onCommand,
       _connector = connector ?? _defaultConnector {
    if (maxBufferedMessages < 1) {
      throw ArgumentError.value(maxBufferedMessages, 'maxBufferedMessages');
    }
    if (commandCacheSize < 1) {
      throw ArgumentError.value(commandCacheSize, 'commandCacheSize');
    }
  }

  final Uri endpoint;
  final AgentHelloPayload hello;
  final Duration connectTimeout;
  final Duration reconnectDelay;
  final Duration maxReconnectDelay;
  final int maxBufferedMessages;
  final int commandCacheSize;

  final AgentCommandHandler _onCommand;
  final AgentWebSocketConnector _connector;
  final StreamController<AgentBridgeConnectionState> _stateController =
      StreamController<AgentBridgeConnectionState>.broadcast();
  final Queue<_OutboundMessage> _bufferedMessages = Queue<_OutboundMessage>();
  final LinkedHashMap<String, AgentCommandOutcome> _commandCache =
      LinkedHashMap<String, AgentCommandOutcome>();

  WebSocketChannel? _channel;
  StreamSubscription<Object?>? _subscription;
  Timer? _reconnectTimer;
  AgentStatePayload? _latestState;
  Future<void> _commandTail = Future<void>.value();
  AgentBridgeConnectionState _connectionState =
      AgentBridgeConnectionState.stopped;
  bool _started = false;
  bool _stopping = false;
  int _sequence = 0;
  int _lastHostSequence = 0;
  int _reconnectAttempt = 0;
  int _connectionGeneration = 0;
  int _droppedBufferedMessages = 0;

  /// Connection transitions, suitable for UI status indicators.
  Stream<AgentBridgeConnectionState> get connectionState =>
      _stateController.stream;

  AgentBridgeConnectionState get currentConnectionState => _connectionState;

  /// Number of buffered messages discarded because the reconnect queue filled.
  int get droppedBufferedMessages => _droppedBufferedMessages;

  /// Starts the reconnect loop. Calling this more than once is harmless.
  Future<void> start() async {
    if (_started) {
      return;
    }
    _started = true;
    _stopping = false;
    unawaited(_connect());
  }

  /// Stops reconnecting and closes the current socket.
  Future<void> stop() async {
    if (_stopping) {
      return;
    }
    _stopping = true;
    _started = false;
    _reconnectTimer?.cancel();
    _reconnectTimer = null;
    final subscription = _subscription;
    _subscription = null;
    await subscription?.cancel();
    final channel = _channel;
    _channel = null;
    if (channel != null) {
      await channel.sink.close();
    }
    _setConnectionState(AgentBridgeConnectionState.stopped);
    await _stateController.close();
  }

  /// Publishes the latest semantic runner state.
  void sendState(AgentStatePayload state) {
    _latestState = state;
    if (_channel != null) {
      _transmit(AgentMessageType.state, payload: state.toJson());
    }
  }

  /// Publishes an event. Events are buffered while disconnected.
  void sendEvent(AgentEventPayload event) {
    _enqueue(AgentMessageType.event, payload: event.toJson());
  }

  void sendScreenshot(
    AgentScreenshotPayload screenshot, {
    required String commandId,
  }) {
    _enqueue(
      AgentMessageType.screenshot,
      payload: screenshot.toJson(),
      commandId: commandId,
    );
  }

  void sendReport(AgentReportPayload report, {required String commandId}) {
    _enqueue(
      AgentMessageType.report,
      payload: report.toJson(),
      commandId: commandId,
    );
  }

  void sendProtocolError(AgentErrorPayload error, {String? commandId}) {
    _enqueue(
      AgentMessageType.error,
      payload: error.toJson(),
      commandId: commandId,
    );
  }

  Future<void> _connect() async {
    if (!_started || _stopping) {
      return;
    }
    final generation = ++_connectionGeneration;
    _setConnectionState(AgentBridgeConnectionState.connecting);
    WebSocketChannel? channel;
    try {
      channel = _connector(endpoint);
      await channel.ready.timeout(connectTimeout);
    } on Object {
      await channel?.sink.close();
      if (generation == _connectionGeneration && _started) {
        _scheduleReconnect();
      }
      return;
    }

    if (!_started || _stopping || generation != _connectionGeneration) {
      await channel.sink.close();
      return;
    }

    _channel = channel;
    _lastHostSequence = 0;
    _reconnectAttempt = 0;
    _subscription = channel.stream.listen(
      (data) => _handleIncoming(generation, data),
      onError: (Object error, StackTrace stackTrace) =>
          _handleDisconnect(generation),
      onDone: () => _handleDisconnect(generation),
      cancelOnError: true,
    );
    _setConnectionState(AgentBridgeConnectionState.connected);
    _transmit(AgentMessageType.hello, payload: hello.toJson());
    final state = _latestState;
    if (state != null) {
      _transmit(AgentMessageType.state, payload: state.toJson());
    }
    _flushBufferedMessages();
  }

  void _handleDisconnect(int generation) {
    if (generation != _connectionGeneration) {
      return;
    }
    final subscription = _subscription;
    _subscription = null;
    unawaited(subscription?.cancel());
    _channel = null;
    if (_started && !_stopping) {
      _setConnectionState(AgentBridgeConnectionState.waitingToReconnect);
      _scheduleReconnect();
    }
  }

  void _scheduleReconnect() {
    if (!_started || _stopping || _reconnectTimer?.isActive == true) {
      return;
    }
    final exponent = _reconnectAttempt > 5 ? 5 : _reconnectAttempt;
    var delay = reconnectDelay * (1 << exponent);
    if (delay > maxReconnectDelay) {
      delay = maxReconnectDelay;
    }
    _reconnectAttempt++;
    _setConnectionState(AgentBridgeConnectionState.waitingToReconnect);
    _reconnectTimer = Timer(delay, () {
      _reconnectTimer = null;
      unawaited(_connect());
    });
  }

  void _handleIncoming(int generation, Object? data) {
    if (generation != _connectionGeneration || _channel == null) {
      return;
    }
    AgentEnvelope envelope;
    try {
      final text = switch (data) {
        String value => value,
        List<int> value => utf8.decode(value),
        _ => throw AgentProtocolException(
          'WebSocket messages must be UTF-8 text',
        ),
      };
      envelope = AgentEnvelope.fromJsonString(text);
    } on Object catch (error) {
      sendProtocolError(
        AgentErrorPayload(
          code: 'invalid_message',
          message: error is AgentProtocolException
              ? error.message
              : 'Invalid JSON message',
          retryable: false,
        ),
      );
      return;
    }

    if (envelope.type != AgentMessageType.command) {
      sendProtocolError(
        AgentErrorPayload(
          code: 'unsupported_message_type',
          message: 'The app accepts only command messages',
          details: <String, Object?>{'type': envelope.type.wireName},
        ),
        commandId: envelope.commandId,
      );
      return;
    }
    if (envelope.sequence <= _lastHostSequence) {
      sendProtocolError(
        AgentErrorPayload(
          code: 'out_of_order_sequence',
          message: 'Host sequence must increase for every command',
          details: <String, Object?>{
            'received': envelope.sequence,
            'last': _lastHostSequence,
          },
        ),
        commandId: envelope.commandId,
      );
      return;
    }
    _lastHostSequence = envelope.sequence;

    final commandId = envelope.commandId;
    if (commandId == null || commandId.isEmpty) {
      sendProtocolError(
        const AgentErrorPayload(
          code: 'missing_command_id',
          message: 'Command messages require a command_id',
        ),
      );
      return;
    }

    AgentCommandPayload command;
    try {
      command = AgentCommandPayload.fromJson(envelope.payload);
    } on Object catch (error) {
      _sendCommandResult(
        commandId,
        AgentCommandOutcome.failed(
          errorCode: 'invalid_command',
          errorMessage: error is AgentProtocolException
              ? error.message
              : 'Invalid command payload',
        ),
      );
      return;
    }

    final received = AgentCommand(envelope: envelope, command: command);
    _commandTail = _commandTail.then((_) => _executeCommand(received));
  }

  Future<void> _executeCommand(AgentCommand command) async {
    final commandId = command.commandId;
    final cached = _commandCache.remove(commandId);
    if (cached != null) {
      _commandCache[commandId] = cached;
      _sendOutcome(commandId, cached, duplicate: true);
      return;
    }

    AgentCommandOutcome outcome;
    try {
      outcome = await _onCommand(command);
    } on Object {
      outcome = AgentCommandOutcome.failed(
        errorCode: 'handler_failed',
        errorMessage: 'Command handler failed.',
      );
    }
    _rememberOutcome(commandId, outcome);
    _sendOutcome(commandId, outcome, duplicate: false);
  }

  void _rememberOutcome(String commandId, AgentCommandOutcome outcome) {
    _commandCache.remove(commandId);
    _commandCache[commandId] = outcome;
    while (_commandCache.length > commandCacheSize) {
      _commandCache.remove(_commandCache.keys.first);
    }
  }

  void _sendOutcome(
    String commandId,
    AgentCommandOutcome outcome, {
    required bool duplicate,
  }) {
    final screenshot = outcome.screenshot;
    if (screenshot != null) {
      sendScreenshot(screenshot, commandId: commandId);
    }
    final report = outcome.report;
    if (report != null) {
      sendReport(report, commandId: commandId);
    }
    _sendCommandResult(commandId, outcome, duplicate: duplicate);
  }

  void _sendCommandResult(
    String commandId,
    AgentCommandOutcome outcome, {
    bool duplicate = false,
  }) {
    final status = duplicate ? AgentCommandStatus.duplicate : outcome.status;
    final result = AgentCommandResultPayload(
      status: status,
      data: outcome.data,
      errorCode: outcome.errorCode,
      errorMessage: outcome.errorMessage,
    );
    _enqueue(
      AgentMessageType.commandResult,
      payload: result.toJson(),
      commandId: commandId,
    );
  }

  void _enqueue(
    AgentMessageType type, {
    required Map<String, Object?> payload,
    String? commandId,
  }) {
    final message = _OutboundMessage(
      type: type,
      payload: payload,
      commandId: commandId,
    );
    if (_channel != null) {
      _transmitMessage(message);
      return;
    }
    while (_bufferedMessages.length >= maxBufferedMessages) {
      _bufferedMessages.removeFirst();
      _droppedBufferedMessages++;
    }
    _bufferedMessages.add(message);
  }

  void _flushBufferedMessages() {
    while (_channel != null && _bufferedMessages.isNotEmpty) {
      _transmitMessage(_bufferedMessages.removeFirst());
    }
  }

  void _transmit(
    AgentMessageType type, {
    required Map<String, Object?> payload,
    String? commandId,
  }) {
    _transmitMessage(
      _OutboundMessage(type: type, payload: payload, commandId: commandId),
    );
  }

  void _transmitMessage(_OutboundMessage message) {
    final channel = _channel;
    if (channel == null) {
      _enqueue(
        message.type,
        payload: message.payload,
        commandId: message.commandId,
      );
      return;
    }
    final sequence = ++_sequence;
    final envelope = AgentEnvelope(
      type: message.type,
      sequence: sequence,
      messageId: newAgentId(prefix: 'message'),
      sentAt: DateTime.now().toUtc(),
      commandId: message.commandId,
      payload: message.payload,
    );
    try {
      channel.sink.add(envelope.toJsonString());
    } on Object {
      _channel = null;
      if (message.type != AgentMessageType.hello) {
        _enqueue(
          message.type,
          payload: message.payload,
          commandId: message.commandId,
        );
      }
      _handleDisconnect(_connectionGeneration);
    }
  }

  void _setConnectionState(AgentBridgeConnectionState next) {
    if (_connectionState == next || _stateController.isClosed) {
      return;
    }
    _connectionState = next;
    _stateController.add(next);
  }

  static WebSocketChannel _defaultConnector(Uri uri) {
    return IOWebSocketChannel.connect(
      uri,
      connectTimeout: const Duration(seconds: 8),
      pingInterval: const Duration(seconds: 20),
    );
  }
}

class _OutboundMessage {
  const _OutboundMessage({
    required this.type,
    required this.payload,
    this.commandId,
  });

  final AgentMessageType type;
  final Map<String, Object?> payload;
  final String? commandId;
}
