class SecretKeys {
  const SecretKeys._();

  static String setupCode(String runId) => 'device_test.$runId.setup_code';
  static String wifiSsid(String runId) => 'device_test.$runId.wifi_ssid';
  static String wifiPassword(String runId) =>
      'device_test.$runId.wifi_password';
  static String controllerIdentity(String runId) =>
      'device_test.$runId.controller_identity';
  static String secretsBundle(String runId) =>
      'device_test.$runId.provisioning_secrets';

  /// Prefix of the global Wi-Fi prefill keys. Not scoped by runId and never
  /// removed by run-secret purges.
  static const String latestWifiPrefix = 'device_test.latest_wifi.';

  /// Global key for the latest remembered Wi-Fi SSID. Not scoped by runId and
  /// never removed by run-secret purges.
  static const String latestWifiSsid = 'device_test.latest_wifi.ssid';

  /// Global key for the latest remembered Wi-Fi password. Not scoped by runId
  /// and never removed by run-secret purges.
  static const String latestWifiPassword = 'device_test.latest_wifi.password';
}
