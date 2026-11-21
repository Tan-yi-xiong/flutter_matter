import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/src/exception.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  const channel = MethodChannel('flutter_matter');
  late List<MethodCall> calls;
  late int responseCode;
  late Map<String, dynamic> responseData;

  setUp(() {
    calls = <MethodCall>[];
    responseCode = 0;
    responseData = <String, dynamic>{
      'version': 0,
      'vendorId': 10,
      'productId': 20,
      'commissioningFlow': 0,
      'discoveryCapabilities': <int>[2, 3],
      'discriminator': 100,
      'hasShortDiscriminator': false,
      'setupPinCode': 20202021,
    };
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      calls.add(call);
      return jsonEncode({
        'code': responseCode,
        'jsonData': responseData,
      });
    });
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('QR payloads use the QR parser route and decode capabilities', () async {
    final payload = await OnboardingPayloadParser().parse('MT:mock-qr-code');

    expect(calls.single.method, 'zgmatter://onboarding/parseQrCode');
    expect(payload.vendorId, 10);
    expect(payload.productId, 20);
    expect(payload.setupPinCode, 20202021);
    expect(payload.discoveryCapabilities, {
      DiscoveryCapability.ble,
      DiscoveryCapability.on_network,
    });
  });

  test('manual payloads use the manual parser route', () async {
    await OnboardingPayloadParser().parse('12345678901234567890');

    expect(
      calls.single.method,
      'zgmatter://onboarding/parseManualPairingCode',
    );
  });

  test('non-success QR responses preserve code and method name', () async {
    responseCode = 7;

    await expectLater(
      OnboardingPayloadParser().parse('MT:mock-qr-code'),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', 7)
            .having((error) => error.methodName, 'methodName', 'parseQrCode'),
      ),
    );
  });

  test('manual parser failure uses the manual error message', () async {
    responseCode = 9;

    await expectLater(
      OnboardingPayloadParser().parse('12345678901234567890'),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', 9)
            .having(
              (error) => error.methodName,
              'methodName',
              'parseManualPairingCode',
            )
            .having(
              (error) => error.message,
              'message',
              contains('manual pairing code'),
            ),
      ),
    );
  });

  test('invalid native payload is wrapped with parser context', () async {
    responseData = <String, dynamic>{
      'vendorId': 10,
      'productId': 20,
      'commissioningFlow': 0,
      'discoveryCapabilities': <int>[2],
      'discriminator': 100,
      'hasShortDiscriminator': false,
      'setupPinCode': 20202021,
    };

    await expectLater(
      OnboardingPayloadParser().parseQrCode('MT:mock-qr-code'),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', 0)
            .having((error) => error.methodName, 'methodName', 'parseQrCode')
            .having(
              (error) => error.details?['category'],
              'category',
              'invalid-payload',
            )
            .having((error) => error.cause, 'cause', isA<FormatException>()),
      ),
    );
  });

  test('empty parser inputs fail as argument errors before platform I/O',
      () async {
    final parser = OnboardingPayloadParser();
    await expectLater(parser.parse(''), throwsArgumentError);
    await expectLater(parser.parseQrCode('   '), throwsArgumentError);
    await expectLater(parser.parseManualPairingCode(''), throwsArgumentError);
    expect(calls, isEmpty);
  });

  test('OnboardingPayload.decode reports field-specific format errors', () {
    expect(
      () => OnboardingPayload.decode(<String, dynamic>{
        'vendorId': 10,
        'productId': 20,
        'commissioningFlow': 0,
        'discoveryCapabilities': <int>[2],
        'discriminator': 100,
        'hasShortDiscriminator': false,
        'setupPinCode': 20202021,
      }),
      throwsA(
        isA<FormatException>().having(
          (error) => error.message,
          'message',
          contains('OnboardingPayload.version'),
        ),
      ),
    );

    expect(
      () => OnboardingPayload.decode(<String, dynamic>{
        ...responseData,
        'discoveryCapabilities': 'ble',
      }),
      throwsA(
        isA<FormatException>().having(
          (error) => error.message,
          'message',
          contains('OnboardingPayload.discoveryCapabilities'),
        ),
      ),
    );

    expect(
      () => OnboardingPayload.decode(<String, dynamic>{
        ...responseData,
        'hasShortDiscriminator': 'false',
      }),
      throwsA(
        isA<FormatException>().having(
          (error) => error.message,
          'message',
          contains('OnboardingPayload.hasShortDiscriminator'),
        ),
      ),
    );
  });

  test('empty discovery capabilities are accepted', () {
    final payload = OnboardingPayload.decode(<String, dynamic>{
      ...responseData,
      'discoveryCapabilities': <int>[],
    });

    expect(payload.discoveryCapabilities, isEmpty);
  });

  test('iOS-style supported discovery capabilities still decode', () {
    final payload = OnboardingPayload.decode(<String, dynamic>{
      ...responseData,
      'discoveryCapabilities': <int>[1, 2, 3],
    });

    expect(payload.discoveryCapabilities, {
      DiscoveryCapability.soft_ap,
      DiscoveryCapability.ble,
      DiscoveryCapability.on_network,
    });
  });

  test('unknown discovery capabilities are rejected even when mixed', () {
    expect(
      () => OnboardingPayload.decode(<String, dynamic>{
        ...responseData,
        'discoveryCapabilities': <int>[1, 99, 3],
      }),
      throwsA(
        isA<FormatException>().having(
          (error) => error.message,
          'message',
          contains('unsupported value 99'),
        ),
      ),
    );
  });

  test('all-unknown discovery capabilities are rejected', () {
    expect(
      () => OnboardingPayload.decode(<String, dynamic>{
        ...responseData,
        'discoveryCapabilities': <int>[99, 100],
      }),
      throwsA(isA<FormatException>()),
    );
  });
}
