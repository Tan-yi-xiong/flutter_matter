// ignore_for_file: depend_on_referenced_packages

import 'dart:async';

import 'package:stream_channel/stream_channel.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

class FakeWebSocketConnector {
  final List<FakeWebSocketChannel> channels = <FakeWebSocketChannel>[];

  WebSocketChannel connect(Uri uri) {
    final channel = FakeWebSocketChannel();
    channels.add(channel);
    return channel;
  }
}

class FakeWebSocketChannel extends StreamChannelMixin<Object?>
    implements WebSocketChannel {
  FakeWebSocketChannel() {
    sink = FakeWebSocketSink(
      onAdd: (value) {
        if (value is! String) {
          throw StateError('The bridge must send text frames.');
        }
        sent.add(value);
      },
      onClose: () async {
        if (!_incoming.isClosed) {
          await _incoming.close();
        }
      },
    );
  }

  final StreamController<Object?> _incoming = StreamController<Object?>();
  final List<String> sent = <String>[];

  @override
  late final FakeWebSocketSink sink;

  @override
  int? closeCode;

  @override
  String? closeReason;

  @override
  String? protocol;

  @override
  Future<void> get ready => Future<void>.value();

  @override
  Stream<Object?> get stream => _incoming.stream;

  void addFromHost(String message) {
    _incoming.add(message);
  }

  Future<void> disconnectFromHost() async {
    if (!_incoming.isClosed) {
      await _incoming.close();
    }
  }
}

class FakeWebSocketSink implements WebSocketSink {
  FakeWebSocketSink({required this.onAdd, required this.onClose});

  final void Function(dynamic value) onAdd;
  final Future<void> Function() onClose;
  final Completer<void> _done = Completer<void>();

  @override
  Future<void> get done => _done.future;

  @override
  void add(dynamic data) {
    onAdd(data);
  }

  @override
  void addError(Object error, [StackTrace? stackTrace]) {
    throw error;
  }

  @override
  Future<void> addStream(Stream<dynamic> stream) async {
    await for (final value in stream) {
      add(value);
    }
  }

  @override
  Future<void> close([int? closeCode, String? closeReason]) async {
    await onClose();
    if (!_done.isCompleted) {
      _done.complete();
    }
  }
}
