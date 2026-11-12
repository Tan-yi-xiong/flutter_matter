import 'key_value_store.dart';
import 'secret_keys.dart';

/// Latest Wi-Fi credentials remembered for prefilling the setup form.
///
/// The pair lives in the platform secure store under global keys that are not
/// scoped by runId, so run-secret purges leave it intact. A load returns
/// credentials only when both keys exist, which prevents a partially written
/// pair from being surfaced after an interrupted save.
class WifiCredentialCache {
  WifiCredentialCache({required KeyValueStore secureStore})
    : _secureStore = secureStore;

  final KeyValueStore _secureStore;

  /// Returns the latest credentials, or `null` when either key is missing.
  Future<WifiCredentials?> load() async {
    final values = await Future.wait<String?>([
      _secureStore.read(SecretKeys.latestWifiSsid),
      _secureStore.read(SecretKeys.latestWifiPassword),
    ]);
    final ssid = values[0];
    final password = values[1];
    if (ssid == null || password == null || ssid.isEmpty) {
      return null;
    }
    return WifiCredentials(ssid: ssid, password: password);
  }

  /// Replaces the remembered pair.
  ///
  /// The password key is removed before the new pair is written so a save
  /// interrupted between steps can never leave a mismatched SSID/password
  /// pair readable: at least one key is always missing on load.
  Future<void> save({required String ssid, required String password}) async {
    final trimmedSsid = ssid.trim();
    if (trimmedSsid.isEmpty) {
      throw ArgumentError.value(ssid, 'ssid', 'SSID must not be empty.');
    }
    await _secureStore.delete(SecretKeys.latestWifiPassword);
    await _secureStore.write(SecretKeys.latestWifiSsid, trimmedSsid);
    await _secureStore.write(SecretKeys.latestWifiPassword, password);
  }

  /// Removes both cached keys.
  Future<void> clear() async {
    await _secureStore.delete(SecretKeys.latestWifiSsid);
    await _secureStore.delete(SecretKeys.latestWifiPassword);
  }
}

/// A remembered SSID/password pair. An empty password models an open network.
class WifiCredentials {
  const WifiCredentials({required this.ssid, required this.password});

  final String ssid;
  final String password;

  @override
  String toString() => 'WifiCredentials(ssid: $ssid, password: ${'*' * 6})';

  @override
  bool operator ==(Object other) =>
      other is WifiCredentials &&
      other.ssid == ssid &&
      other.password == password;

  @override
  int get hashCode => Object.hash(ssid, password);
}
