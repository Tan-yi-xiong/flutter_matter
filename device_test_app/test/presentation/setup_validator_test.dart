import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/presentation_fixtures.dart';

void main() {
  test('accepts a minimal Wi-Fi setup', () {
    final result = DeviceTestSetupValidator.validate(
      draft: _draft(),
      controller: controllerInfo,
      preflightChecks: readyPreflight,
    );

    expect(result.isValid, isTrue, reason: result.errors.toString());
  });

  test('requires a setup code and SSID', () {
    final result = DeviceTestSetupValidator.validate(
      draft: _draft(setupCode: '', wifiSsid: ''),
      controller: controllerInfo,
      preflightChecks: readyPreflight,
    );

    expect(result[SetupField.setupCode], isNotNull);
    expect(result[SetupField.networkCredentials], isNotNull);
  });

  test('requires blocking preflight checks to pass', () {
    final result = DeviceTestSetupValidator.validate(
      draft: _draft(),
      controller: controllerInfo,
      preflightChecks: const <PreflightCheckViewModel>[
        PreflightCheckViewModel(
          id: 'build',
          label: 'Build metadata',
          status: PreflightStatus.failed,
        ),
      ],
    );

    expect(result[SetupField.preflight], isNotNull);
  });
}

DeviceTestSetupDraft _draft({
  String setupCode = 'MT:TEST-SETUP-CODE',
  String wifiSsid = 'test-network',
  TestProfile profile = TestProfile.full,
}) {
  return DeviceTestSetupDraft(
    setupCode: setupCode,
    wifiSsid: wifiSsid,
    wifiPassword: 'test-password',
    profile: profile,
  );
}
