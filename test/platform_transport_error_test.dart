import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/src/exception.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  const channel = MethodChannel('flutter_matter');
  final params = RequestPlatformParams(
    methodName: 'zgmatter://devicecontroller/new',
    methodParamsJson: '{"secret":"must-not-leak"}',
  );

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('native PlatformException becomes a typed safe platform failure',
      () async {
    const secret = 'native-error-secret';
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      throw PlatformException(
        code: '7',
        message: secret,
        details: secret,
      );
    });

    await expectLater(
      MethodChannelFlutterMatter().requestPlatform(params),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', 7)
            .having(
                (error) => error.methodName, 'methodName', params.methodName)
            .having(
              (error) => error.toString(),
              'message',
              isNot(contains(secret)),
            )
            .having(
              (error) => error.cause,
              'cause',
              isA<PlatformException>(),
            ),
      ),
    );
  });

  test('MissingPluginException becomes a typed safe platform failure',
      () async {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);

    await expectLater(
      MethodChannelFlutterMatter().requestPlatform(params),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', methodNoFound)
            .having(
                (error) => error.methodName, 'methodName', params.methodName)
            .having(
              (error) => error.details?['category'],
              'category',
              'missing-plugin',
            )
            .having(
              (error) => error.toString(),
              'message',
              isNot(contains('must-not-leak')),
            ),
      ),
    );
  });

  test('malformed envelopes remain protocol and format failures', () async {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({
        'code': 0,
        'jsonData': <String, dynamic>{},
      }).substring(0, 5);
    });

    await expectLater(
      MethodChannelFlutterMatter().requestPlatform(params),
      throwsA(
        isA<PlatformProtocolException>()
            .having(
              (error) => error.methodName,
              'methodName',
              params.methodName,
            )
            .having(
              (error) => error.violation,
              'violation',
              'response is not valid JSON',
            ),
      ),
    );
    await expectLater(
      MethodChannelFlutterMatter().requestPlatform(params),
      throwsA(isA<FormatException>()),
    );
  });
}
