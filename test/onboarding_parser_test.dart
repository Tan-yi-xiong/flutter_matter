import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  const channel = MethodChannel('flutter_matter');
  late List<MethodCall> calls;
  late int responseCode;

  setUp(() {
    calls = <MethodCall>[];
    responseCode = 0;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      calls.add(call);
      return jsonEncode({
        'code': responseCode,
        'jsonData': {
          'version': 0,
          'vendorId': 10,
          'productId': 20,
          'commissioningFlow': 0,
          'discoveryCapabilities': [2, 3],
          'discriminator': 100,
          'hasShortDiscriminator': false,
          'setupPinCode': 20202021,
        },
      });
    });
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('QR payloads use the QR parser route and decode capabilities', () async {
    final payload = await OnboardingPayloadParser().parse('MT:mock-qr-code');

    expect(calls.single.method, 'zgMatter://Onboarding/parseQrCode');
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

    expect(calls.single.method, 'zgMatter://Onboarding/parseManualPairingCode');
  });

  test('non-success parser responses throw', () async {
    responseCode = 1;

    expect(
      () => OnboardingPayloadParser().parse('MT:mock-qr-code'),
      throwsA(isA<Exception>()),
    );
  });
}
