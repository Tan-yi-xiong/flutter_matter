import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/presentation_fixtures.dart';

void main() {
  test('accepts a real Matter Wi-Fi/IP setup', () {
    final result = DeviceTestSetupValidator.validate(
      draft: _draft(),
      controller: controllerInfo,
      preflightChecks: readyPreflight,
      hasStoredSecrets: false,
    );

    expect(result.isValid, isTrue, reason: result.errors.toString());
  });

  test('rejects virtual commissionees for quick and full profiles', () {
    for (final profile in TestProfile.values) {
      final result = DeviceTestSetupValidator.validate(
        draft: _draft(
          profile: profile,
          commissioneeType: CommissioneeType.virtual,
        ),
        controller: controllerInfo,
        preflightChecks: readyPreflight,
        hasStoredSecrets: false,
      );

      expect(
        result.errors[SetupField.commissioneeType],
        'Device validation requires a real Matter commissionee.',
        reason: profile.name,
      );
    }
  });

  test('rejects non-Wi-Fi network transports', () {
    final result = DeviceTestSetupValidator.validate(
      draft: _draft(networkTransport: NetworkTransport.thread),
      controller: controllerInfo,
      preflightChecks: readyPreflight,
      hasStoredSecrets: false,
    );

    expect(
      result.errors[SetupField.networkCredentials],
      'Only Wi-Fi/IP commissioning is supported.',
    );
  });
}

DeviceTestSetupDraft _draft({
  TestProfile profile = TestProfile.full,
  CommissioneeType commissioneeType = CommissioneeType.real,
  NetworkTransport networkTransport = NetworkTransport.wifi,
}) {
  return DeviceTestSetupDraft(
    commissioneeType: commissioneeType,
    model: 'Matter On/Off Plug',
    firmware: '1.0.0',
    commissioningTransport: CommissioningTransport.ip,
    networkTransport: networkTransport,
    stateChangeMethod: StateChangeMethod.physicalControl,
    setupCode: 'MT:TEST-SETUP-CODE',
    wifiSsid: 'test-network',
    wifiPassword: 'test-password',
    profile: profile,
    cleanCycle: const CleanCycleConfirmations(
      controllerClean: true,
      commissioneeClean: true,
      secretsPurged: true,
    ),
  );
}
