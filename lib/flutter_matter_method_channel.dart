import 'dart:convert';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:collection/collection.dart';
import 'package:flutter_matter/src/exception.dart';
import 'package:flutter_matter/src/utils.dart';
import 'flutter_matter_platform_interface.dart';

class PlatformResult {
  final int code;
  final Map<String, dynamic> jsonData;

  PlatformResult({required this.code, required this.jsonData});

  @override
  String toString() {
    return jsonEncode({
      'code': code,
      'jsonData': jsonData
    });
  }
}

class RequestPlatformParams {
  final String methodName;
  final String methodParamsJson;

  RequestPlatformParams({required this.methodName, required this.methodParamsJson});

  @override
  String toString() {
    return jsonEncode({
      'methodName': methodName,
      'methodParamsJson': methodParamsJson
    });
  }
}

class PlatformCallResult extends TransportObject {
  final int code;
  final String resultJson;

  PlatformCallResult({required this.code, required this.resultJson});


  @override
  String encode() {
    return jsonEncode({
      'code': code,
      'resultJson': resultJson
    });
  }  
}

abstract class MethodCallHandler {
  bool match(String method, dynamic arguments);

  call(String method, dynamic arguments);
}

abstract class TransportObject {
  String encode();
}

String createRequestPlatformUrl(String host, String path) {
  return Uri(scheme: "zgMatter", host: host, path: path).toString();
}

/// An implementation of [FlutterMatterPlatform] that uses method channels.
class MethodChannelFlutterMatter extends FlutterMatterPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_matter');

  final _handlers = <MethodCallHandler>{};

  void addHandler(MethodCallHandler handler) {
    _handlers.add(handler);
  }
  
  void removeHandler(MethodCallHandler handler) {
    _handlers.remove(handler);
  }

  MethodChannelFlutterMatter() {
    methodChannel.setMethodCallHandler((call) async {
      matterPrint('methodChannel called: ${call.method} with arguments: ${call.arguments}');
      String m = call.method;
      dynamic p = call.arguments;
      try {
        final h = _handlers.firstWhereOrNull((element) => element.match(m, p));
        matterPrint('$h matched for $m');
        final result = await h?.call(m, p);
        if (result is TransportObject) {
          return result.encode();
        }
        return result;
      } catch (e, s) {
        matterPrint('setMethodCallHandler exception: $s');
        if (e is PlatformCallResult) {
          return e;
        }
        return createPlatformCallExceptionResult(unHandlerException, s.toString());
      }
    });
  }

  Future<PlatformResult> requestPlatform(RequestPlatformParams params) async {
    matterPrint("$runtimeType requestPlatform -> $params");
    final result = await methodChannel.invokeMethod(params.methodName, params.methodParamsJson);
    assert(result is String);
    final decodeResult = jsonDecode(result);
    assert(decodeResult['code'] is int);
    assert(decodeResult['jsonData'] is Map);
    matterPrint('$runtimeType requestPlatform ${params.methodName} <- $decodeResult');
    return PlatformResult(code: decodeResult['code'], jsonData: decodeResult['jsonData'].cast<String, dynamic>());
  }
}
