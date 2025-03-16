
import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_matter/src/constant.dart';
import 'package:flutter_matter/src/exception.dart';

import '../flutter_matter_method_channel.dart';

matterPrint(msg) {
  print('[flutter_matter] $msg');
}

PlatformCallResult createPlatformCallExceptionResult(int code, String errorMsg) {
  return PlatformCallResult(code: code, resultJson: jsonEncode({"msg": errorMsg}));
}

PlatformCallResult createPlatformCallSuccessResult({String? successMsg}) {
  return PlatformCallResult(code: successCode, resultJson: successMsg ?? successJsonMessage );
}

Uint8List toUint8List(List list) {
  return Uint8List.fromList(list.cast<int>());
}

checkCallArgNotNull(Map jsonData, String keyName) {
  final value = jsonData[keyName];
  if (value == null) {
    throw createPlatformCallExceptionResult(argsInvalid, "$keyName must not be null");
  }
  return value;
}