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
}
