import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_matter/src/constant.dart';

import '../flutter_matter_method_channel.dart';
import '../flutter_matter_platform_interface.dart';
import 'exception.dart';
import 'utils.dart';

const String nsdHostName = "nsd";


abstract class ResolveCallback {

  /// Resolve an address for the given instance name and service type
  void resolve(String serviceName, String serviceType, Future Function(NsdServiceInfo) chipMdnsCallback);

}

abstract class RemoveServicesCallback {
  void removeServices();
}

abstract class PublishCallback {
  void publish(String serviceName, String hostName, String type, int port, List<String>? textEntriesKeys, List<String>? subTypes, List<Uint8List>? textEntriesDatas);
}

class NsdServiceInfo {
  final String hostName;
  final String serviceType;
  final String serviceName;
  final String address;
  final int port;
  final Map<String, Uint8List>? attributes;

  NsdServiceInfo({required this.hostName, required this.serviceType, required this.serviceName, required this.address, required this.port, this.attributes});

  toJson() => {
    'hostName': hostName,
    'serviceType': serviceType,
    'serviceName': serviceName,
    'address': address,
    'port': port,
    'attributes': attributes?.map((key, value) => MapEntry(key, List.from(value)))
  };
}



class NsdManager implements MethodCallHandler {

  static NsdManager? _instance;
  NsdManager._() {
    (FlutterMatterPlatform.instance as MethodChannelFlutterMatter).addHandler(this);
  }
  
  factory NsdManager() => _instance ??= NsdManager._();

  ResolveCallback? _resolveCallback;
  RemoveServicesCallback? _removeServicesCallback;
  PublishCallback? _publishCallback;

  @override
  call(String method, arguments) {
    final uri = Uri.parse(method);
    final decodeArgs = jsonDecode(arguments);
    switch (uri.pathSegments.first) {
      case 'resolve':
        final callbackHandle = checkCallArgNotNull(decodeArgs, "chipMdnsCallbackHandle");
        _resolveCallback?.resolve(
          checkCallArgNotNull(decodeArgs, "instanceName"),
          checkCallArgNotNull(decodeArgs, "serviceType"),
          (nsdServiceInfo) async {
            return _handleServiceResolve(callbackHandle, nsdServiceInfo);
          }
        );
        return createPlatformCallSuccessResult();
      case 'publish':
        // jsonKeyHandle to proxyHandle,
        //                     "serviceName" to serviceName,
        //                     "hostName" to hostName,
        //                     "type" to type,
        //                     "port" to port,
        //                     "textEntriesKeys" to if (textEntriesKeys == null) null else JSONArray(
        //                         textEntriesKeys
        //                     ),
        //                     "textEntriesDatas" to if (textEntriesDatas == null) null else JSONArray(textEntriesDatas.map { JSONArray(it) }),
        //                     "subTypes" to if (textEntriesKeys == null) null else JSONArray(subTypes),
        _publishCallback?.publish(
          checkCallArgNotNull(decodeArgs, 'serviceName'),
          checkCallArgNotNull(decodeArgs, 'hostName'),
          checkCallArgNotNull(decodeArgs, 'type'),
          checkCallArgNotNull(decodeArgs, 'port'),
          decodeArgs['textEntriesKeys'] == null ? null : (decodeArgs['textEntriesKeys'] as List).cast(),
          decodeArgs['subTypes'] == null ? null : (decodeArgs['subTypes'] as List).cast(),
          decodeArgs['textEntriesDatas'] == null ? null : (decodeArgs['textEntriesDatas'] as List).map((e) => Uint8List.fromList(e.cast())).toList().cast()
        );
        return createPlatformCallSuccessResult();
      case 'removeServices':
        _removeServicesCallback?.removeServices();
        return createPlatformCallSuccessResult();
      default:
        return createPlatformCallExceptionResult(methodNoFound, 'Not found $method');
    }
  }
  
  @override
  bool match(String method, arguments) {
    try {
      final uri = Uri.parse(method);
      return uri.host == nsdHostName;
    } catch (e, s) {
      matterPrint('$runtimeType match error $s') ;
    }
    return false;
  }

  Future<Map<String, dynamic>?> _requestPlatform(String methodName, String methodParamsJson) async {
    final channelFlutterMatter = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
    final result = await channelFlutterMatter.requestPlatform(
      RequestPlatformParams(methodName: createRequestPlatformUrl(nsdHostName, methodName), methodParamsJson: methodParamsJson));
    if (result.code == 0) {
      return result.jsonData;
    }
    throw CallPlatformException("[${result.code}] Call $methodName params $methodParamsJson failed");
  }


  Future<void> setResolveHandle(ResolveCallback? resolveCallback) async {
    await _requestPlatform("setResolve", jsonEncode({
      'proxyHandle': resolveCallback?.hashCode.toString(),
    })).then((v) {
      _resolveCallback = resolveCallback;
      return v;
    });
  }
  
  Future<void> _handleServiceResolve(String handleId, NsdServiceInfo serviceInfo) async {
    await _requestPlatform("handleServiceResolve", jsonEncode({
      jsonKeyHandle: handleId,
      ...serviceInfo.toJson()
    }));
  }

  Future<void> setPublishHandle(PublishCallback? callback) async {
    await _requestPlatform("setPublish", jsonEncode({
      jsonKeyHandle: callback?.hashCode.toString(),
    })).then((value) => _publishCallback = callback);
  }

  Future<void> setRemoveServices(RemoveServicesCallback? callback) async {
    await _requestPlatform("setRemoveServices", jsonEncode({
      jsonKeyHandle: callback?.hashCode.toString(),
    })).then((value) => _removeServicesCallback = callback);
  }
}