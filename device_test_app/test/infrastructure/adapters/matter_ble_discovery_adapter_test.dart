import 'package:flutter_matter_device_test_app/src/application/ports.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/adapters/adapters.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/ble/matter_ble.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/fakes.dart';

void main() {
  group('MatterBleDiscoveryAdapter', () {
    test('maps onboarding payload and returns an opaque target', () async {
      final scanner = FakeMatterBleScanner(
        discovered: makeDiscoveredDevice(name: 'Kitchen plug'),
      );
      final resolver = FakeOnboardingPayloadResolver(discriminator: 0x0acd);
      final adapter = MatterBleDiscoveryAdapter(
        scanner: scanner,
        payloadResolver: resolver,
      );

      final result = await adapter.discover(
        const BleDiscoveryRequest(
          timeout: Duration(seconds: 2),
          onboardingPayload: 'MT:PAYLOAD',
        ),
      );

      expect(result.candidateCount, 1);
      expect(result.target, isNotNull);
      expect(result.target!.opaqueId, isNotEmpty);
      expect(result.target!.displayName, 'Kitchen plug');
      expect(resolver.requests, ['MT:PAYLOAD']);
      expect(scanner.requests.single.discriminator, 0x0acd);
      expect(scanner.requests.single.hasShortDiscriminator, isFalse);
      expect(scanner.requests.single.timeout, const Duration(seconds: 2));
    });

    test(
      'returns no candidates when no onboarding payload is available',
      () async {
        final scanner = FakeMatterBleScanner();
        final adapter = MatterBleDiscoveryAdapter(
          scanner: scanner,
          payloadResolver: FakeOnboardingPayloadResolver(),
        );

        final result = await adapter.discover(
          const BleDiscoveryRequest(timeout: Duration(seconds: 2)),
        );

        expect(result.candidateCount, 0);
        expect(result.target, isNull);
        expect(scanner.requests, isEmpty);
      },
    );

    test('maps adapter unavailability to the discovery failure enum', () async {
      final scanner = FakeMatterBleScanner(
        error: MatterBleException(
          MatterBleFailureCode.adapterUnavailable,
          'Bluetooth adapter unavailable',
        ),
      );
      final adapter = MatterBleDiscoveryAdapter(
        scanner: scanner,
        payloadResolver: FakeOnboardingPayloadResolver(),
      );

      await expectLater(
        adapter.discover(
          const BleDiscoveryRequest(
            timeout: Duration(seconds: 2),
            onboardingPayload: 'MT:PAYLOAD',
          ),
        ),
        throwsA(
          isA<BleDiscoveryException>().having(
            (error) => error.code,
            'code',
            BleDiscoveryFailureCode.adapterUnavailable,
          ),
        ),
      );
    });

    test('maps permission errors during adapter preflight', () async {
      final platform = FakeMatterBlePlatform(
        error: permissionPlatformException(),
      );
      final adapter = MatterBleDiscoveryAdapter(
        scanner: FakeMatterBleScanner(),
        payloadResolver: FakeOnboardingPayloadResolver(),
        platform: platform,
      );

      await expectLater(
        adapter.discover(
          const BleDiscoveryRequest(
            timeout: Duration(seconds: 2),
            onboardingPayload: 'MT:PAYLOAD',
          ),
        ),
        throwsA(
          isA<BleDiscoveryException>().having(
            (error) => error.code,
            'code',
            BleDiscoveryFailureCode.permissionDenied,
          ),
        ),
      );
      expect(platform.ensureAdapterCalled, isTrue);
    });
  });
}
