import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/ble.dart';
import 'package:flutter_matter/src/constant.dart';
import 'package:flutter_matter/src/exception.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  late MethodChannelFlutterMatter platform;

  setUp(() {
    platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(platform.methodChannel, null);
  });

  test('BLE callback validates byte arrays and keeps the error boundary',
      () async {
    final callbackHandler = BlePlatformDelegateCallbackHandler();
    final delegate = _RecordingBlePlatformDelegate();
    final handle = callbackHandler.addHandler(delegate);

    final validEnvelope = await _invokeCallback(
      'sendWriteRequest',
      jsonEncode({
        jsonKeyHandle: handle,
        'connObj': 7,
        'svcId': <int>[0, 255],
        'charId': <int>[1, 2],
        'data': <int>[3, 4, 255],
      }),
    );

    expect(validEnvelope['code'], successCode);
    expect(delegate.writeCalls, 1);
    expect(delegate.svcId, orderedEquals(<int>[0, 255]));
    expect(delegate.charId, orderedEquals(<int>[1, 2]));
    expect(delegate.data, orderedEquals(<int>[3, 4, 255]));

    final invalidEnvelope = await _invokeCallback(
      'sendWriteRequest',
      jsonEncode({
        jsonKeyHandle: handle,
        'connObj': 7,
        'svcId': <int>[0],
        'charId': <int>[1],
        'data': <int>[256],
      }),
    );

    expect(invalidEnvelope['code'], argsInvalid);
    expect(delegate.writeCalls, 1);

    final nonListEnvelope = await _invokeCallback(
      'sendWriteRequest',
      jsonEncode({
        jsonKeyHandle: handle,
        'connObj': 7,
        'svcId': <int>[0],
        'charId': <int>[1],
        'data': 'not-bytes',
      }),
    );

    expect(nonListEnvelope['code'], argsInvalid);
    expect(delegate.writeCalls, 1);
  });

  test('BLE delegate registration rolls back after failure and can retry',
      () async {
    final delegate = _RecordingBlePlatformDelegate();
    final handles = <Object?>[];
    var setDelegateCalls = 0;
    var allowClear = false;

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(platform.methodChannel, (call) async {
      if (!call.method.endsWith('/setBlePlatformDelegate')) {
        return jsonEncode({'code': 0, 'jsonData': <String, dynamic>{}});
      }

      setDelegateCalls++;
      final params = jsonDecode(call.arguments as String) as Map;
      handles.add(params[jsonKeyHandle]);

      if (!allowClear && (setDelegateCalls == 1 || setDelegateCalls == 3)) {
        return jsonEncode({'code': 1, 'jsonData': <String, dynamic>{}});
      }
      return jsonEncode({'code': 0, 'jsonData': <String, dynamic>{}});
    });

    addTearDown(() async {
      allowClear = true;
      try {
        await BLELayerPlatform.setBlePlatformDelegate(null);
      } catch (_) {
        // Best-effort cleanup if an assertion aborted the scenario.
      }
    });

    await expectLater(
      BLELayerPlatform.setBlePlatformDelegate(delegate),
      throwsA(isA<CallPlatformException>()),
    );
    expect(setDelegateCalls, 1);
    expect(handles.single, delegate.hashCode.toString());

    await BLELayerPlatform.setBlePlatformDelegate(delegate);
    expect(setDelegateCalls, 2);
    expect(handles.last, delegate.hashCode.toString());

    await expectLater(
      BLELayerPlatform.setBlePlatformDelegate(null),
      throwsA(isA<CallPlatformException>()),
    );
    expect(setDelegateCalls, 3);
    expect(handles.last, isNull);

    await expectLater(
      BLELayerPlatform.setBlePlatformDelegate(delegate),
      throwsA(isA<Exception>()),
    );
    expect(setDelegateCalls, 3);

    allowClear = true;
    await BLELayerPlatform.setBlePlatformDelegate(null);
    expect(setDelegateCalls, 4);
    expect(handles.last, isNull);
  });
}

Future<Map<String, dynamic>> _invokeCallback(
  String callbackMethod,
  String arguments,
) async {
  const codec = StandardMethodCodec();
  final response = await TestDefaultBinaryMessengerBinding
      .instance.defaultBinaryMessenger
      .handlePlatformMessage(
    'flutter_matter',
    codec.encodeMethodCall(
      MethodCall(
        'zgMatter://ignored/BlePlatformDelegate/$callbackMethod',
        arguments,
      ),
    ),
    null,
  );

  return jsonDecode(codec.decodeEnvelope(response!) as String)
      as Map<String, dynamic>;
}

class _RecordingBlePlatformDelegate implements BlePlatformDelegate {
  int writeCalls = 0;
  Uint8List? svcId;
  Uint8List? charId;
  Uint8List? data;

  @override
  Future<bool> closeConnection(dynamic connObj) async => true;

  @override
  Future<int> getMTU(dynamic connObj) async => 20;

  @override
  Future<bool> sendIndication(dynamic connObj, Uint8List svcId,
      Uint8List charId, Uint8List pBuf) async {
    return true;
  }

  @override
  Future<bool> sendReadRequest(dynamic connObj, Uint8List svcId,
      Uint8List charId, Uint8List pBuf) async {
    return true;
  }

  @override
  Future<bool> sendReadResponse(dynamic connObj, dynamic requestContext,
      Uint8List svcId, Uint8List charId) async {
    return true;
  }

  @override
  Future<bool> sendWriteRequest(dynamic connObj, Uint8List svcId,
      Uint8List charId, Uint8List pBuf) async {
    writeCalls++;
    this.svcId = svcId;
    this.charId = charId;
    data = pBuf;
    return true;
  }

  @override
  Future<bool> subscribeCharacteristic(
      dynamic connObj, Uint8List svcId, Uint8List charId) async {
    return true;
  }

  @override
  Future<bool> unsubscribeCharacteristic(
      dynamic connObj, Uint8List svcId, Uint8List charId) async {
    return true;
  }
}
