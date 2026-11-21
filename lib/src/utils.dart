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
    // Android's org.json serializes Java bytes as signed values (-128..127),
    // while iOS and other platform bridges use unsigned values (0..255).
    // Accept exactly the union of those wire representations and normalize
    // signed values to their two's-complement byte.
    if (value is! int || value < -0x80 || value > 0xff) {
      throw ArgumentError.value(
        value,
        'bytes[$i]',
        'must be a signed or unsigned byte represented as an integer',
      );
    }
    bytes.add(value & 0xff);
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
