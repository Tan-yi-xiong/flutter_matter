part of '../flutter_matter_platform_interface.dart';

/// An implementation of [FlutterMatterPlatform] that uses method channels.
class MethodChannelFlutterMatter extends FlutterMatterPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_matter');

  final _handlers = <MethodCallHandler>{};

  @override
  void addHandler(MethodCallHandler handler) {
    _handlers.add(handler);
  }

  @override
  void removeHandler(MethodCallHandler handler) {
    _handlers.remove(handler);
  }

  MethodChannelFlutterMatter() {
    methodChannel.setMethodCallHandler((call) async {
      final method = call.method;
      try {
        final h = _handlers.firstWhereOrNull(
            (element) => element.match(method, call.arguments));
        if (h == null) {
          return createPlatformCallExceptionResult(
            methodNoFound,
            'No callback handler matched the request',
          ).encode();
        }
        final result = await h.call(method, call.arguments);
        if (result is TransportObject) {
          return result.encode();
        }
        return result;
      } catch (e, s) {
        reportMatterError('$runtimeType incoming call $method', e, s);
        if (e is TransportObject) {
          return e.encode();
        }
        if (e is ArgumentError) {
          final key = e.name == null ? '' : ' for ${e.name}';
          return createPlatformCallExceptionResult(
            argsInvalid,
            'Invalid callback arguments$key',
          ).encode();
        }
        return createPlatformCallExceptionResult(
          unHandlerException,
          'Platform callback failed',
        ).encode();
      }
    });
  }

  @override
  Future<PlatformResult> requestPlatform(RequestPlatformParams params) async {
    matterPrint('$runtimeType requestPlatform -> ${params.methodName}');

    final dynamic result;
    try {
      result = await methodChannel.invokeMethod<dynamic>(
        params.methodName,
        params.methodParamsJson,
      );
    } on MissingPluginException catch (error) {
      throw CallPlatformException(
        'Platform request ${params.methodName} is unavailable',
        code: methodNoFound,
        methodName: params.methodName,
        details: const <String, Object?>{
          'category': 'missing-plugin',
        },
        cause: error,
      );
    } on PlatformException catch (error) {
      final code = int.tryParse(error.code);
      throw CallPlatformException(
        'Platform request ${params.methodName} failed with code '
        '${code ?? unHandlerException}',
        code: code ?? unHandlerException,
        methodName: params.methodName,
        details: <String, Object?>{
          'category': 'platform-error',
          'platformCode': error.code,
        },
        cause: error,
      );
    }

    if (result is! String) {
      throw PlatformProtocolException(
        'response is not a JSON string',
        methodName: params.methodName,
      );
    }

    dynamic decoded;
    try {
      decoded = jsonDecode(result);
    } catch (e) {
      throw PlatformProtocolException(
        'response is not valid JSON',
        methodName: params.methodName,
        cause: e,
      );
    }
    if (decoded is! Map) {
      throw PlatformProtocolException(
        'response must be a JSON object',
        methodName: params.methodName,
      );
    }
    if (!decoded.containsKey('code')) {
      throw PlatformProtocolException(
        'response is missing code',
        methodName: params.methodName,
      );
    }
    final code = decoded['code'];
    if (code is! int) {
      throw PlatformProtocolException(
        'response code must be an integer',
        methodName: params.methodName,
      );
    }
    if (!decoded.containsKey('jsonData')) {
      throw PlatformProtocolException(
        'response is missing jsonData',
        methodName: params.methodName,
      );
    }
    final rawData = decoded['jsonData'];
    if (rawData is! Map) {
      throw PlatformProtocolException(
        'response jsonData must be an object',
        methodName: params.methodName,
      );
    }

    final jsonData = <String, dynamic>{};
    for (final entry in rawData.entries) {
      if (entry.key is! String) {
        throw PlatformProtocolException(
          'response jsonData keys must be strings',
          methodName: params.methodName,
        );
      }
      jsonData[entry.key as String] = entry.value;
    }

    matterPrint(
        '$runtimeType requestPlatform ${params.methodName} <- code $code');
    return PlatformResult(code: code, jsonData: jsonData);
  }
}
