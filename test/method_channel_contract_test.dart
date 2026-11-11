import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  const channel = MethodChannel('flutter_matter');
  late List<MethodCall> calls;

  setUp(() {
    calls = <MethodCall>[];
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      calls.add(call);
      return jsonEncode({
        'code': 0,
        'jsonData': {'status': 'ok'},
      });
    });
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('createRequestPlatformUrl preserves the protocol host and path', () {
    expect(
      createRequestPlatformUrl('devicecontroller', 'new'),
      'zgMatter://devicecontroller/new',
    );
    expect(
      createRequestPlatformUrl('BLE', 'connectDevice'),
      'zgMatter://BLE/connectDevice',
    );
  });

  test('request parameter envelope uses methodName and methodParamsJson', () {
    final params = RequestPlatformParams(
      methodName: 'zgMatter://devicecontroller/new',
      methodParamsJson: '{"fabricId":1}',
    );

    expect(jsonDecode(params.toString()), {
      'methodName': 'zgMatter://devicecontroller/new',
      'methodParamsJson': '{"fabricId":1}',
    });
  });

  test('platform result envelopes use the documented JSON keys', () {
    final result = PlatformResult(code: 0, jsonData: {'value': 1});
    final callResult = PlatformCallResult(code: 1, resultJson: '{"msg":"bad"}');

    expect(jsonDecode(result.toString()), {
      'code': 0,
      'jsonData': {'value': 1},
    });
    expect(jsonDecode(callResult.encode()), {
      'code': 1,
      'resultJson': '{"msg":"bad"}',
    });
  });

  test('requestPlatform sends the method and JSON payload to the channel',
      () async {
    final platform = MethodChannelFlutterMatter();
    final result = await platform.requestPlatform(
      RequestPlatformParams(
        methodName: 'zgMatter://devicecontroller/new',
        methodParamsJson: '{"fabricId":1}',
      ),
    );

    expect(calls, hasLength(1));
    expect(calls.single.method, 'zgMatter://devicecontroller/new');
    expect(jsonDecode(calls.single.arguments as String), {'fabricId': 1});
    expect(result.code, 0);
    expect(result.jsonData, {'status': 'ok'});
  });
}
