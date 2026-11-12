import 'package:flutter_matter_device_test_app/src/application/ports.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/key_value_store.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/provisioning_secret_store.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/secret_keys.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/wifi_credential_cache.dart';
import 'package:flutter_test/flutter_test.dart';

class _MemoryStore implements KeyValueStore {
  final Map<String, String> values = <String, String>{};

  @override
  Future<String?> read(String key) async => values[key];

  @override
  Future<void> write(String key, String value) async {
    values[key] = value;
  }

  @override
  Future<void> delete(String key) async {
    values.remove(key);
  }

  @override
  Future<void> deleteAll() async {
    values.clear();
  }
}

class _FailingPasswordWriteStore extends _MemoryStore {
  @override
  Future<void> write(String key, String value) async {
    if (key == SecretKeys.latestWifiPassword) {
      throw StateError('secure store write failed');
    }
    await super.write(key, value);
  }
}

void main() {
  group('WifiCredentialCache', () {
    test('round-trips, replaces, and clears the latest pair', () async {
      final backing = _MemoryStore();
      final cache = WifiCredentialCache(secureStore: backing);

      await cache.save(ssid: 'home-net', password: 'secret-1');
      expect(
        await cache.load(),
        const WifiCredentials(ssid: 'home-net', password: 'secret-1'),
      );

      await cache.save(ssid: '  home-net  ', password: 'secret-2');
      expect(
        await cache.load(),
        const WifiCredentials(ssid: 'home-net', password: 'secret-2'),
      );

      await cache.clear();
      expect(await cache.load(), isNull);
      expect(backing.values, isEmpty);
    });

    test('round-trips an empty password for open networks', () async {
      final cache = WifiCredentialCache(secureStore: _MemoryStore());

      await cache.save(ssid: 'open-net', password: '');

      expect(
        await cache.load(),
        const WifiCredentials(ssid: 'open-net', password: ''),
      );
    });

    test('rejects blank SSIDs', () async {
      final cache = WifiCredentialCache(secureStore: _MemoryStore());

      expect(
        () => cache.save(ssid: '   ', password: 'secret'),
        throwsArgumentError,
      );
    });

    test('returns null when only one key is stored', () async {
      final backing = _MemoryStore();
      final cache = WifiCredentialCache(secureStore: backing);

      backing.values[SecretKeys.latestWifiSsid] = 'home-net';
      expect(await cache.load(), isNull);

      backing.values.remove(SecretKeys.latestWifiSsid);
      backing.values[SecretKeys.latestWifiPassword] = 'secret-1';
      expect(await cache.load(), isNull);
    });

    test('never surfaces a pair when the password write fails', () async {
      final backing = _FailingPasswordWriteStore();
      final cache = WifiCredentialCache(secureStore: backing);

      await expectLater(
        cache.save(ssid: 'home-net', password: 'secret-1'),
        throwsA(isA<StateError>()),
      );

      expect(await cache.load(), isNull);
    });

    test('redacts the password in toString', () async {
      final cache = WifiCredentialCache(secureStore: _MemoryStore());

      await cache.save(ssid: 'home-net', password: 'super-secret-password');
      final loaded = await cache.load();

      expect(loaded, isNotNull);
      expect(loaded.toString(), isNot(contains('super-secret-password')));
      expect(loaded.toString(), contains('home-net'));
    });

    test('run-secret purge leaves the latest Wi-Fi cache intact', () async {
      final backing = _MemoryStore();
      final secretStore = ProvisioningSecretStore(secureStore: backing);
      final cache = WifiCredentialCache(secureStore: backing);

      await secretStore.save(
        'run-1',
        ProvisioningSecrets(
          onboardingPayload: 'MT:TEST-PAYLOAD',
          setupPinCode: 20202021,
          network: const WifiProvisioningSecret(
            ssid: 'run-net',
            password: 'run-secret',
          ),
        ),
      );
      await cache.save(ssid: 'cache-net', password: 'cache-secret');

      await secretStore.purge('run-1');

      expect(await secretStore.load('run-1'), isNull);
      expect(
        await cache.load(),
        const WifiCredentials(ssid: 'cache-net', password: 'cache-secret'),
      );
    });
  });
}
