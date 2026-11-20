import 'dart:collection';

import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/platform_transport_types.dart';
import 'package:flutter_matter/src/utils.dart';

abstract class CallbackHandler<T> implements MethodCallHandler {
  final Map<String, T> _handlers = <String, T>{};

  CallbackHandler() {
    FlutterMatterPlatform.instance.addHandler(this);
  }

  Map<String, T> get handlers => UnmodifiableMapView(_handlers);

  String addHandler(T handler) {
    final id = handler.hashCode.toString();
    _handlers[id] = handler;
    return id;
  }

  bool removeHandler(String handlerId) {
    return _handlers.remove(handlerId) != null;
  }

  onCallbackMethodCall(String methodName, dynamic arguments);

  @override
  bool match(String method, dynamic arguments) {
    try {
      final splitPaths = _splitCallbackPath(method);
      final m =
          splitPaths.length >= 2 && splitPaths.firstOrNull == T.toString();
      matterPrint('$T CallbackHandler match result: $m');
      return m;
    } on ArgumentError {
      return false;
    }
  }

  @override
  call(String method, dynamic arguments) {
    final splitPaths = _splitCallbackPath(method);
    if (splitPaths.length < 2) {
      throw ArgumentError.value(
        method,
        'method',
        'callback path must contain a callback type and method name',
      );
    }
    return onCallbackMethodCall(splitPaths.sublist(1).join('/'), arguments);
  }

  static List<String> _splitCallbackPath(String method) {
    if (method.trim().isEmpty) {
      throw ArgumentError.value(method, 'method', 'must not be empty');
    }

    final Uri uri;
    try {
      uri = Uri.parse(method);
    } on FormatException catch (error) {
      throw ArgumentError.value(
        method,
        'method',
        'must be a valid callback URI: ${error.message}',
      );
    }

    return uri.path
        .split('/')
        .where((element) => element.trim().isNotEmpty)
        .toList(growable: false);
  }
}
