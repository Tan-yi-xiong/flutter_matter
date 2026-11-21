import 'dart:convert';

/// Result returned by a platform request envelope.
class PlatformResult {
  final int code;
  final Map<String, dynamic> jsonData;

  PlatformResult({required this.code, required this.jsonData});

  @override
  String toString() {
    return 'PlatformResult(code: $code, jsonData: <redacted>)';
  }
}

/// Request payload sent through the platform transport.
class RequestPlatformParams {
  final String methodName;
  final String methodParamsJson;

  RequestPlatformParams({
    required this.methodName,
    required this.methodParamsJson,
  });

  @override
  String toString() {
    return 'RequestPlatformParams(methodName: $methodName)';
  }
}

/// Result returned from a native callback to the platform channel.
class PlatformCallResult extends TransportObject {
  final int code;
  final String resultJson;

  PlatformCallResult({required this.code, required this.resultJson});

  @override
  String encode() {
    return jsonEncode({'code': code, 'resultJson': resultJson});
  }
}

/// Handler for platform calls initiated by native code.
abstract class MethodCallHandler {
  bool match(String method, dynamic arguments);

  dynamic call(String method, dynamic arguments);
}

/// Object that can encode itself for a platform callback response.
abstract class TransportObject {
  String encode();
}

/// Builds the stable MethodChannel URL used by Dart-to-native requests.
String createRequestPlatformUrl(String host, String path) {
  return Uri(scheme: 'zgMatter', host: host, path: path).toString();
}
