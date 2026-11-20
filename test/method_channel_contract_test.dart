import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/src/exception.dart';

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

  test('createRequestPlatformUrl normalizes scheme and host but preserves path',
      () {
    expect(
      createRequestPlatformUrl('devicecontroller', 'new'),
      'zgmatter://devicecontroller/new',
    );
    expect(
      createRequestPlatformUrl('BLE', 'connectDevice'),
      'zgmatter://ble/connectDevice',
    );
  });

  test('request parameter envelope uses methodName and methodParamsJson', () {
    final params = RequestPlatformParams(
      methodName: 'zgMatter://devicecontroller/new',
      methodParamsJson: '{"fabricId":1}',
    );

    expect(params.methodName, 'zgMatter://devicecontroller/new');
    expect(params.methodParamsJson, '{"fabricId":1}');
  });

  test('platform result envelopes use the documented JSON keys', () {
    final result = PlatformResult(code: 0, jsonData: {'value': 1});
    final callResult = PlatformCallResult(code: 1, resultJson: '{"msg":"bad"}');

    expect(result.code, 0);
    expect(result.jsonData, {'value': 1});
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

  test('requestPlatform rejects malformed envelopes without leaking payloads',
      () async {
    const secret = 'wifi-password-that-must-not-leak';
    final messenger =
        TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger;
    final params = RequestPlatformParams(
      methodName: 'zgMatter://devicecontroller/new',
      methodParamsJson: jsonEncode({'password': secret}),
    );

    Future<void> expectViolation(dynamic response, String violation) async {
      messenger.setMockMethodCallHandler(channel, (call) async => response);
      final platform = MethodChannelFlutterMatter();
      await expectLater(
        platform.requestPlatform(params),
        throwsA(
          predicate(
            (error) =>
                error is PlatformProtocolException &&
                error.violation == violation &&
                !error.toString().contains(secret),
          ),
        ),
      );
    }

    await expectViolation(null, 'response is not a JSON string');
    await expectViolation('not-json', 'response is not valid JSON');
    await expectViolation(
      jsonEncode({
        'jsonData': {'secret': secret},
      }),
      'response is missing code',
    );
    await expectViolation(
      jsonEncode({
        'code': '0',
        'jsonData': {'secret': secret},
      }),
      'response code must be an integer',
    );
    await expectViolation(
      jsonEncode({'code': 0}),
      'response is missing jsonData',
    );
    await expectViolation(
      jsonEncode({'code': 0, 'jsonData': <dynamic>[]}),
      'response jsonData must be an object',
    );
  });

  test('unmatched callback returns a safe method-not-found envelope', () async {
    const secret = 'unmatched-sensitive-payload';
    const codec = StandardMethodCodec();
    final response = await TestDefaultBinaryMessengerBinding
        .instance.defaultBinaryMessenger
        .handlePlatformMessage(
      'flutter_matter',
      codec.encodeMethodCall(
        MethodCall(
          'zgMatter://unknown/Unmatched/onEvent',
          jsonEncode({'secret': secret}),
        ),
      ),
      null,
    );

    final encoded = codec.decodeEnvelope(response!) as String;
    final envelope = jsonDecode(encoded) as Map<String, dynamic>;
    expect(envelope['code'], methodNoFound);
    expect(envelope['resultJson'], isNot(contains(secret)));
  });

  test('callback argument errors return the compatible safe envelope',
      () async {
    const secret = 'sensitive-callback-payload';
    final platform = MethodChannelFlutterMatter();
    platform.addHandler(_ThrowingCallbackHandler());

    const codec = StandardMethodCodec();
    final response = await TestDefaultBinaryMessengerBinding
        .instance.defaultBinaryMessenger
        .handlePlatformMessage(
      'flutter_matter',
      codec.encodeMethodCall(
        MethodCall(
          'zgMatter://ignored/ThrowingCallback/onEvent',
          jsonEncode({'secret': secret}),
        ),
      ),
      null,
    );

    final encoded = codec.decodeEnvelope(response!) as String;
    final envelope = jsonDecode(encoded) as Map<String, dynamic>;
    expect(envelope['code'], argsInvalid);
    expect(envelope['resultJson'], isNot(contains(secret)));
  });

  test('unexpected callback errors return a safe -99 envelope', () async {
    const secret = 'sensitive-runtime-payload';
    final platform = MethodChannelFlutterMatter();
    platform.addHandler(_RuntimeThrowingCallbackHandler(StateError(secret)));

    const codec = StandardMethodCodec();
    final response = await TestDefaultBinaryMessengerBinding
        .instance.defaultBinaryMessenger
        .handlePlatformMessage(
      'flutter_matter',
      codec.encodeMethodCall(
        const MethodCall('zgMatter://ignored/ThrowingCallback/onEvent', '{}'),
      ),
      null,
    );

    final encoded = codec.decodeEnvelope(response!) as String;
    final envelope = jsonDecode(encoded) as Map<String, dynamic>;
    expect(envelope['code'], unHandlerException);
    expect(envelope['resultJson'], isNot(contains(secret)));
  });
}

class _ThrowingCallbackHandler implements MethodCallHandler {
  @override
  bool match(String method, dynamic arguments) =>
      method.contains('ThrowingCallback');

  @override
  dynamic call(String method, dynamic arguments) {
    throw ArgumentError.value(null, 'requiredField', 'Missing callback field');
  }
}

class _RuntimeThrowingCallbackHandler implements MethodCallHandler {
  _RuntimeThrowingCallbackHandler(this.error);

  final Object error;

  @override
  bool match(String method, dynamic arguments) =>
      method.contains('ThrowingCallback');

  @override
  dynamic call(String method, dynamic arguments) => throw error;
}
