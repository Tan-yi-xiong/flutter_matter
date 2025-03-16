import 'dart:collection';

import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/utils.dart';

import '../flutter_matter_method_channel.dart';

abstract class CallbackHandler<T> implements MethodCallHandler {
  Map<String, T> _handlers = {};

  CallbackHandler() {
    (FlutterMatterPlatform.instance as MethodChannelFlutterMatter).addHandler(this);
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
    final uri = Uri.parse(method);
    final splitPaths = uri.path.split('/').where((element) => element.trim().isNotEmpty).toList();
    final m = splitPaths.length >= 2 && splitPaths.firstOrNull == T.toString();
    matterPrint('$T CallbackHandler match result: $m');
    return m;
  }

  @override
  call(String method, dynamic arguments) {
    final splitPaths = Uri.parse(method).path.split('/').where((element) => element.trim().isNotEmpty).toList();
    return onCallbackMethodCall(splitPaths.sublist(1).join('/'), arguments);
  }
}