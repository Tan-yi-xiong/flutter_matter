import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_matter/src/constant.dart';
import 'package:flutter_matter/src/exception.dart';

import 'platform_transport_types.dart';

void matterPrint(dynamic msg) {
  print('[flutter_matter] $msg');
}

/// Reports an error without logging request parameters, payloads, or raw
/// exception messages. Stack traces contain source locations only and are
/// useful for diagnosing callback failures without exposing credentials.
void reportMatterError(String context, Object error, [StackTrace? stackTrace]) {
  matterPrint('[error] $context: ${_safeErrorSummary(error)}');
  final trace = stackTrace?.toString().trim();
  if (trace != null && trace.isNotEmpty) {
    matterPrint('[error] $context stack:\n$trace');
  }
}

String _safeErrorSummary(Object error) {
  if (error is PlatformProtocolException) {
    return 'PlatformProtocolException(${error.violation})';
  }
  if (error is CallPlatformException) {
    final fields = <String>[];
    if (error.code != null) {
      fields.add('code: ${error.code}');
    }
    if (error.methodName != null) {
      fields.add('method: ${error.methodName}');
    }
    return 'CallPlatformException(${fields.join(', ')})';
  }
  if (error is ArgumentError) {
    final fields = <String>[];
    if (error.name != null) {
      fields.add('name: ${error.name}');
    }
    return 'ArgumentError(${fields.join(', ')})';
  }
  return error.runtimeType.toString();
}

PlatformCallResult createPlatformCallExceptionResult(
    int code, String errorMsg) {
  return PlatformCallResult(
      code: code, resultJson: jsonEncode({"msg": errorMsg}));
}

PlatformCallResult createPlatformCallSuccessResult({String? successMsg}) {
  return PlatformCallResult(
      code: successCode, resultJson: successMsg ?? successJsonMessage);
}

Uint8List toUint8List(List list) {
  final bytes = <int>[];
  for (var i = 0; i < list.length; i++) {
    final value = list[i];
    if (value is! int || value < 0 || value > 0xff) {
      throw ArgumentError.value(
        value,
        'bytes[$i]',
        'must be an integer between 0 and 255',
      );
    }
    bytes.add(value);
  }
  return Uint8List.fromList(bytes);
}

dynamic checkCallArgNotNull(Map jsonData, String keyName, {String? context}) {
  final value = jsonData[keyName];
  if (value == null) {
    final contextMessage = context == null ? '' : '$context: ';
    throw ArgumentError.value(
      null,
      keyName,
      '$contextMessage$keyName must not be null',
    );
  }
  return value;
}
