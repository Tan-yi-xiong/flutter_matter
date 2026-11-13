import 'dart:convert';
import 'dart:typed_data';

import '../../application/ports.dart';
import '../../domain/domain.dart';
import 'key_value_store.dart';
import 'secret_keys.dart';

/// Persists provisioning secrets in the platform secure store.
///
/// The serialized value never appears in logs or report files and the
/// containing storage must be Keychain or Android Keystore backed.
class ProvisioningSecretStore implements SecretAccessPort {
  ProvisioningSecretStore({required KeyValueStore secureStore})
    : _secureStore = secureStore;

  final KeyValueStore _secureStore;

  Future<void> save(String runId, ProvisioningSecrets secrets) {
    final network = secrets.network;
    final networkJson = switch (network) {
      WifiProvisioningSecret() => <String, Object?>{
        'transport': NetworkTransport.wifi.wireName,
        'ssid': network.ssid,
        'password': network.password,
      },
      ThreadProvisioningSecret() => <String, Object?>{
        'transport': NetworkTransport.thread.wireName,
        'operational_dataset': base64Encode(network.operationalDataset),
      },
    };
    return _secureStore.write(
      SecretKeys.secretsBundle(runId),
      jsonEncode(<String, Object?>{
        'onboarding_payload': secrets.onboardingPayload,
        'invalid_setup_onboarding_payload':
            secrets.invalidSetupOnboardingPayload,
        'setup_pin_code': secrets.setupPinCode,
        'setup_discriminator': secrets.setupDiscriminator,
        'on_network_endpoint': switch (secrets.onNetworkEndpoint) {
          null => null,
          final endpoint => <String, Object?>{
            'address': endpoint.address,
            'port': endpoint.port,
          },
        },
        'network': networkJson,
      }),
    );
  }

  @override
  Future<ProvisioningSecrets?> load(String runId) async {
    final contents = await _secureStore.read(SecretKeys.secretsBundle(runId));
    if (contents == null) {
      return null;
    }
    final decoded = jsonDecode(contents);
    if (decoded is! Map<String, dynamic>) {
      throw const FormatException('Stored provisioning secrets are invalid.');
    }
    final network = decoded['network'];
    if (network is! Map<String, dynamic>) {
      throw const FormatException('Stored network credentials are invalid.');
    }
    final transport = network['transport'];
    final ProvisioningNetworkSecret networkSecret;
    switch (transport) {
      case 'wifi':
        final ssid = network['ssid'];
        final password = network['password'];
        if (ssid is! String || password is! String) {
          throw const FormatException('Stored Wi-Fi credentials are invalid.');
        }
        networkSecret = WifiProvisioningSecret(ssid: ssid, password: password);
      case 'thread':
        final dataset = network['operational_dataset'];
        if (dataset is! String) {
          throw const FormatException('Stored Thread credentials are invalid.');
        }
        networkSecret = ThreadProvisioningSecret(
          operationalDataset: Uint8List.fromList(base64Decode(dataset)),
        );
      default:
        throw FormatException('Unknown stored network transport: $transport');
    }

    final payload = decoded['onboarding_payload'];
    final invalidPayload = decoded['invalid_setup_onboarding_payload'];
    final pin = decoded['setup_pin_code'];
    if (payload is! String || invalidPayload is! String || pin is! int) {
      throw const FormatException('Stored setup credentials are invalid.');
    }
    final discriminator = decoded['setup_discriminator'];
    if (discriminator != null && discriminator is! int) {
      throw const FormatException('Stored setup discriminator is invalid.');
    }
    final endpointJson = decoded['on_network_endpoint'];
    OnNetworkCommissioningEndpoint? endpoint;
    if (endpointJson != null) {
      if (endpointJson is! Map<String, dynamic>) {
        throw const FormatException('Stored on-network endpoint is invalid.');
      }
      final address = endpointJson['address'];
      final port = endpointJson['port'];
      if (address is! String || port is! int) {
        throw const FormatException('Stored on-network endpoint is invalid.');
      }
      endpoint = OnNetworkCommissioningEndpoint(address: address, port: port);
    }
    return ProvisioningSecrets(
      onboardingPayload: payload,
      invalidSetupOnboardingPayload: invalidPayload,
      setupPinCode: pin,
      setupDiscriminator: discriminator as int?,
      onNetworkEndpoint: endpoint,
      network: networkSecret,
    );
  }

  /// Deletes every stored per-Run provisioning key, including orphans whose
  /// run directory no longer exists. The global Wi-Fi prefill cache uses a
  /// dedicated prefix and is intentionally preserved.
  Future<void> purgeAllStored() async {
    final all = await _secureStore.readAll();
    for (final key in all.keys) {
      if (!key.startsWith('device_test.')) {
        continue;
      }
      if (key.startsWith(SecretKeys.latestWifiPrefix)) {
        continue;
      }
      await _secureStore.delete(key);
    }
  }

  @override
  Future<void> purge(String runId) async {
    await Future.wait<void>([
      _secureStore.delete(SecretKeys.secretsBundle(runId)),
      _secureStore.delete(SecretKeys.setupCode(runId)),
      _secureStore.delete(SecretKeys.wifiSsid(runId)),
      _secureStore.delete(SecretKeys.wifiPassword(runId)),
      _secureStore.delete(SecretKeys.controllerIdentity(runId)),
    ]);
  }
}
