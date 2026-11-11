import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter_device_test_app/src/infrastructure/ble/matter_ble.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('MatterDiscriminatorMatcher', () {
    test('extracts the little-endian discriminator after the opcode', () {
      final data = Uint8List.fromList([0x00, 0xcd, 0x0a, 0xaa, 0xbb]);
      expect(MatterDiscriminatorMatcher.extractDiscriminator(data), 0x0acd);
    });

    test('matches a full discriminator', () {
      final data = Uint8List.fromList([0x00, 0xcd, 0x0a]);
      expect(
        MatterDiscriminatorMatcher.matches(
          serviceData: data,
          discriminator: 0x0acd,
          hasShortDiscriminator: false,
        ),
        isTrue,
      );
    });

    test('matches a short discriminator against its high nibble', () {
      final data = Uint8List.fromList([0x00, 0xcd, 0x0a]);
      expect(
        MatterDiscriminatorMatcher.matches(
          serviceData: data,
          discriminator: 0x0a,
          hasShortDiscriminator: true,
        ),
        isTrue,
      );
      expect(
        MatterDiscriminatorMatcher.matches(
          serviceData: data,
          discriminator: 0x0b,
          hasShortDiscriminator: true,
        ),
        isFalse,
      );
    });

    test('rejects truncated Matter service data', () {
      expect(
        MatterDiscriminatorMatcher.extractDiscriminator(
          Uint8List.fromList([0x00, 0x01]),
        ),
        isNull,
      );
    });
  });

  group('MatterBleScanner', () {
    test('returns a matching device and always stops scanning', () async {
      final platform = _FakeMatterBlePlatform();
      final scanner = MatterBleScanner(
        platform: platform,
        cleanupTimeout: const Duration(milliseconds: 100),
      );
      final request = MatterBleDiscoveryRequest(
        discriminator: 0x0acd,
        hasShortDiscriminator: false,
        timeout: const Duration(milliseconds: 200),
      );

      final result = await scanner.scan(request);

      expect(result.discriminator, 0x0acd);
      expect(result.device.deviceId, 'matter-device-1');
      expect(platform.stopCount, greaterThanOrEqualTo(2));
    });

    test('reports discovery timeout when no advertisement matches', () async {
      final platform = _FakeMatterBlePlatform(emitAdvertisement: false);
      final scanner = MatterBleScanner(
        platform: platform,
        cleanupTimeout: const Duration(milliseconds: 100),
      );

      await expectLater(
        scanner.scan(
          MatterBleDiscoveryRequest(
            discriminator: 0x0acd,
            hasShortDiscriminator: false,
            timeout: const Duration(milliseconds: 30),
          ),
        ),
        throwsA(
          isA<MatterBleException>().having(
            (error) => error.code,
            'code',
            MatterBleFailureCode.discoveryTimeout,
          ),
        ),
      );
      expect(platform.stopCount, greaterThanOrEqualTo(2));
    });
  });
}

class _FakeMatterBlePlatform implements MatterBlePlatform {
  _FakeMatterBlePlatform({this.emitAdvertisement = true});

  final bool emitAdvertisement;
  final StreamController<MatterBleAdvertisement> _advertisements =
      StreamController<MatterBleAdvertisement>.broadcast();
  final _FakeMatterBleDevice device = _FakeMatterBleDevice();
  int stopCount = 0;

  @override
  Stream<MatterBleAdvertisement> get advertisements => _advertisements.stream;

  @override
  Future<void> ensureAdapterIsOn(Duration timeout) async {}

  @override
  Future<void> startScan(Duration timeout) async {
    if (!emitAdvertisement) {
      return;
    }
    scheduleMicrotask(() {
      _advertisements.add(
        MatterBleAdvertisement(
          device: device,
          serviceData: <String, Uint8List>{
            matterGattServiceUuid: Uint8List.fromList([
              0x00,
              0xcd,
              0x0a,
              0xaa,
              0xbb,
            ]),
          },
          rssi: -48,
          advertisedName: 'Matter Commissionee',
        ),
      );
    });
  }

  @override
  Future<void> stopScan() async {
    stopCount++;
  }
}

class _FakeMatterBleDevice implements MatterBleDevice {
  @override
  String get deviceId => 'matter-device-1';

  @override
  bool get isConnected => false;

  @override
  int get mtu => 185;

  @override
  Future<void> connect(Duration timeout) async {}

  @override
  Future<void> disconnect() async {}

  @override
  Future<List<MatterBleGattService>> discoverServices(Duration timeout) async {
    return const [];
  }
}
