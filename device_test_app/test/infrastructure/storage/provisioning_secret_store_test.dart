import 'package:flutter_matter_device_test_app/src/application/ports.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/key_value_store.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/provisioning_secret_store.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('round-trips Wi-Fi secrets and purges all run keys', () async {
    final backing = _MemoryStore();
    final store = ProvisioningSecretStore(secureStore: backing);
    final secrets = ProvisioningSecrets(
      onboardingPayload: 'MT:TEST-PAYLOAD',
      invalidSetupOnboardingPayload: '24129507534',
      setupPinCode: 20202021,
      network: const WifiProvisioningSecret(
        ssid: 'test-network',
        password: 'test-password',
      ),
    );

    await store.save('run-1', secrets);
    final loaded = await store.load('run-1');

    expect(loaded?.onboardingPayload, secrets.onboardingPayload);
    expect(
      loaded?.invalidSetupOnboardingPayload,
      secrets.invalidSetupOnboardingPayload,
    );
    expect(loaded?.setupPinCode, secrets.setupPinCode);
    expect(loaded?.network, isA<WifiProvisioningSecret>());
    final network = loaded!.network as WifiProvisioningSecret;
    expect(network.ssid, 'test-network');
    expect(network.password, 'test-password');
    expect(loaded.toString(), isNot(contains('test-password')));

    await store.purge('run-1');
    expect(await store.load('run-1'), isNull);
    expect(backing.values, isEmpty);
  });

  test('round-trips Thread credentials', () async {
    final backing = _MemoryStore();
    final store = ProvisioningSecretStore(secureStore: backing);
    final secrets = ProvisioningSecrets(
      onboardingPayload: 'MT:TEST-PAYLOAD',
      invalidSetupOnboardingPayload: '24129507534',
      setupPinCode: 20202021,
      network: ThreadProvisioningSecret(operationalDataset: [1, 2, 3, 4]),
    );

    await store.save('run-thread', secrets);
    final loaded = await store.load('run-thread');

    expect(loaded?.network, isA<ThreadProvisioningSecret>());
    expect((loaded!.network as ThreadProvisioningSecret).operationalDataset, [
      1,
      2,
      3,
      4,
    ]);
  });
}

class _MemoryStore implements KeyValueStore {
  final Map<String, String> values = <String, String>{};

  @override
  Future<Map<String, String>> readAll() async =>
      Map<String, String>.from(values);

  @override
  Future<void> delete(String key) async {
    values.remove(key);
  }

  @override
  Future<void> deleteAll() async {
    values.clear();
  }

  @override
  Future<String?> read(String key) async => values[key];

  @override
  Future<void> write(String key, String value) async {
    values[key] = value;
  }
}
