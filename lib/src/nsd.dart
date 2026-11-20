import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_matter/src/constant.dart';

import '../flutter_matter_platform_interface.dart';
import 'exception.dart';
import 'platform_transport_types.dart';
import 'utils.dart';

const String nsdHostName = "nsd";

abstract class ResolveCallback {
  /// Resolve an address for the given instance name and service type
  void resolve(String serviceName, String serviceType,
      Future Function(NsdServiceInfo) chipMdnsCallback);
}

abstract class RemoveServicesCallback {
  void removeServices();
}

abstract class PublishCallback {
  void publish(
      String serviceName,
      String hostName,
      String type,
      int port,
      List<String>? textEntriesKeys,
      List<String>? subTypes,
      List<Uint8List>? textEntriesDatas);
}

class NsdServiceInfo {
  final String hostName;
  final String serviceType;
  final String serviceName;
  final String address;
  final int port;
  final Map<String, Uint8List>? attributes;

  NsdServiceInfo(
      {required this.hostName,
      required this.serviceType,
      required this.serviceName,
      required this.address,
      required this.port,
      this.attributes});

  toJson() => {
        'hostName': hostName,
        'serviceType': serviceType,
        'serviceName': serviceName,
        'address': address,
        'port': port,
        'attributes':
            attributes?.map((key, value) => MapEntry(key, List.from(value)))
      };
}

List<String>? _optionalStringList(
  Map<dynamic, dynamic> arguments,
  String key,
  String context,
) {
  final value = arguments[key];
  if (value == null) {
    return null;
  }
  if (value is! List) {
    throw ArgumentError.value(
      value,
      key,
      '$context: $key must be a list of strings',
    );
  }
  final result = <String>[];
  for (var i = 0; i < value.length; i++) {
    final item = value[i];
    if (item is! String) {
      throw ArgumentError.value(
        item,
        '$key[$i]',
        '$context: $key[$i] must be a string',
      );
    }
    result.add(item);
  }
  return result;
}

List<Uint8List>? _optionalByteArrayList(
  Map<dynamic, dynamic> arguments,
  String key,
  String context,
) {
  final value = arguments[key];
  if (value == null) {
    return null;
  }
  if (value is! List) {
    throw ArgumentError.value(
      value,
      key,
      '$context: $key must be a list of byte arrays',
    );
  }
  final result = <Uint8List>[];
  for (var i = 0; i < value.length; i++) {
    final item = value[i];
    if (item is! List) {
      throw ArgumentError.value(
        item,
        '$key[$i]',
        '$context: $key[$i] must be a byte array',
      );
    }
    final bytes = <int>[];
    for (var j = 0; j < item.length; j++) {
      final byte = item[j];
      if (byte is! int || byte < 0 || byte > 0xff) {
        throw ArgumentError.value(
          byte,
          '$key[$i][$j]',
          '$context: $key[$i][$j] must be a byte between 0 and 255',
        );
      }
      bytes.add(byte);
    }
    result.add(Uint8List.fromList(bytes));
  }
  return result;
}

class NsdManager implements MethodCallHandler {
  static NsdManager? _instance;
  NsdManager._() {
    FlutterMatterPlatform.instance.addHandler(this);
  }

  factory NsdManager() => _instance ??= NsdManager._();

  ResolveCallback? _resolveCallback;
  RemoveServicesCallback? _removeServicesCallback;
  PublishCallback? _publishCallback;

  @override
  call(String method, arguments) {
    final uri = Uri.parse(method);
    if (uri.pathSegments.isEmpty) {
      throw ArgumentError.value(
        method,
        'method',
        'NSD callback path must include an operation',
      );
    }
    final decoded = jsonDecode(arguments);
    if (decoded is! Map) {
      throw ArgumentError.value(
        decoded,
        'arguments',
        'NSD callback arguments must be a JSON object',
      );
    }
    final decodeArgs = decoded;
    final callbackContext = '$runtimeType ${uri.path}';
    switch (uri.pathSegments.first) {
      case 'resolve':
        final callback = _resolveCallback;
        if (callback == null) {
          return createPlatformCallExceptionResult(
            argsInvalid,
            'Resolve callback is not set',
          );
        }
        final callbackHandle = checkCallArgNotNull(
          decodeArgs,
          'chipMdnsCallbackHandle',
          context: callbackContext,
        );
        callback.resolve(
          checkCallArgNotNull(
            decodeArgs,
            'instanceName',
            context: callbackContext,
          ),
          checkCallArgNotNull(
            decodeArgs,
            'serviceType',
            context: callbackContext,
          ),
          (nsdServiceInfo) async {
            return _handleServiceResolve(callbackHandle, nsdServiceInfo);
          },
        );
        return createPlatformCallSuccessResult();
      case 'publish':
        final callback = _publishCallback;
        if (callback == null) {
          return createPlatformCallExceptionResult(
            argsInvalid,
            'Publish callback is not set',
          );
        }
        final port = checkCallArgNotNull(
          decodeArgs,
          'port',
          context: callbackContext,
        );
        if (port is! int) {
          throw ArgumentError.value(
            port,
            'port',
            '$callbackContext: port must be an integer',
          );
        }
        callback.publish(
          checkCallArgNotNull(
            decodeArgs,
            'serviceName',
            context: callbackContext,
          ),
          checkCallArgNotNull(
            decodeArgs,
            'hostName',
            context: callbackContext,
          ),
          checkCallArgNotNull(
            decodeArgs,
            'type',
            context: callbackContext,
          ),
          port,
          _optionalStringList(
            decodeArgs,
            'textEntriesKeys',
            callbackContext,
          ),
          _optionalStringList(decodeArgs, 'subTypes', callbackContext),
          _optionalByteArrayList(
            decodeArgs,
            'textEntriesDatas',
            callbackContext,
          ),
        );
        return createPlatformCallSuccessResult();
      case 'removeServices':
        final callback = _removeServicesCallback;
        if (callback == null) {
          return createPlatformCallExceptionResult(
            argsInvalid,
            'Remove-services callback is not set',
          );
        }
        callback.removeServices();
        return createPlatformCallSuccessResult();
      default:
        return createPlatformCallExceptionResult(
          methodNoFound,
          'Not found $method',
        );
    }
  }

  @override
  bool match(String method, arguments) {
    try {
      final uri = Uri.parse(method);
      return uri.host == nsdHostName;
    } catch (e, s) {
      reportMatterError('$runtimeType match', e, s);
    }
    return false;
  }

  Future<Map<String, dynamic>> _requestPlatform(
      String methodName, String methodParamsJson) async {
    final channelFlutterMatter = FlutterMatterPlatform.instance;
    final result = await channelFlutterMatter.requestPlatform(
        RequestPlatformParams(
            methodName: createRequestPlatformUrl(nsdHostName, methodName),
            methodParamsJson: methodParamsJson));
    if (result.code == 0) {
      return result.jsonData;
    }
    throw CallPlatformException(
      'Call $methodName failed with code ${result.code}',
      code: result.code,
      methodName: methodName,
      details: const <String, Object?>{
        'host': nsdHostName,
        'category': 'platform-error',
      },
    );
  }

  Future<void> setResolveHandle(ResolveCallback? resolveCallback) async {
    await _requestPlatform(
        "setResolve",
        jsonEncode({
          'proxyHandle': resolveCallback?.hashCode.toString(),
        })).then((v) {
      _resolveCallback = resolveCallback;
      return v;
    });
  }

  Future<void> _handleServiceResolve(
      String handleId, NsdServiceInfo serviceInfo) async {
    await _requestPlatform("handleServiceResolve",
        jsonEncode({jsonKeyHandle: handleId, ...serviceInfo.toJson()}));
  }

  Future<void> setPublishHandle(PublishCallback? callback) async {
    await _requestPlatform(
        "setPublish",
        jsonEncode({
          jsonKeyHandle: callback?.hashCode.toString(),
        })).then((value) => _publishCallback = callback);
  }

  Future<void> setRemoveServices(RemoveServicesCallback? callback) async {
    await _requestPlatform(
        "setRemoveServices",
        jsonEncode({
          jsonKeyHandle: callback?.hashCode.toString(),
        })).then((value) => _removeServicesCallback = callback);
  }
}
