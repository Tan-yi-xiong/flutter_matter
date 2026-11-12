import 'package:flutter_matter_device_test_app/src/bootstrap/agent_run_request_parser.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';
import 'package:flutter_test/flutter_test.dart';

const _controllerInfo = ControllerInfoViewModel(
  platform: ControllerPlatform.android,
  deviceModel: 'Pixel 8',
  osVersion: 'Android 15',
  appBuild: 'debug 1.0.0 (1)',
);

const _readyPreflight = <PreflightCheckViewModel>[
  PreflightCheckViewModel(
    id: 'bluetooth',
    label: 'Bluetooth permission',
    status: PreflightStatus.passed,
  ),
  PreflightCheckViewModel(
    id: 'local-network',
    label: 'Local network connectivity',
    status: PreflightStatus.passed,
  ),
];

DeviceTestUiState _setupState({bool hasStoredSecrets = false}) {
  return DeviceTestUiState(
    screen: DeviceTestScreen.setup,
    controllerInfo: _controllerInfo,
    preflightChecks: _readyPreflight,
    hasStoredSecrets: hasStoredSecrets,
  );
}

Map<String, Object?> _minimalArguments({
  String mode = 'quick',
  bool commissioneeClean = true,
}) {
  return <String, Object?>{
    'mode': mode,
    'setup_code': 'MT:PRIVATE-SETUP-CODE',
    'wifi_ssid': 'test-network',
    'wifi_password': 'test-password',
    'clean_cycle': <String, Object?>{'commissionee_clean': commissioneeClean},
  };
}

void main() {
  const parser = AgentRunRequestParser();

  test('parses the minimal full Run request', () {
    final state = _setupState();
    final request = parser.parse(
      arguments: _minimalArguments(mode: 'full'),
      state: state,
    );

    expect(request.profile, TestProfile.full);
    expect(request.controller, same(state.controllerInfo));
    expect(request.setupCode, 'MT:PRIVATE-SETUP-CODE');
    expect(request.wifiSsid, 'test-network');
    expect(request.wifiPassword, 'test-password');
    expect(request.cleanCycle.commissioneeClean, isTrue);
  });

  test('parses the minimal quick Run request', () {
    final request = parser.parse(
      arguments: _minimalArguments(mode: 'quick'),
      state: _setupState(),
    );

    expect(request.profile, TestProfile.quick);
    expect(request.cleanCycle.commissioneeClean, isTrue);
  });

  test('supports an empty password for an open Wi-Fi network', () {
    final arguments = _minimalArguments()..['wifi_password'] = '';

    final request = parser.parse(arguments: arguments, state: _setupState());

    expect(request.wifiPassword, isEmpty);
  });

  test('requires a supported Run mode', () {
    final arguments = _minimalArguments()..['mode'] = 'smoke';

    expect(
      () => parser.parse(arguments: arguments, state: _setupState()),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues,
          'issues',
          containsPair('mode', 'Expected quick or full.'),
        ),
      ),
    );
  });

  test('requires the commissionee reset confirmation', () {
    final arguments = _minimalArguments(commissioneeClean: false);

    expect(
      () => parser.parse(arguments: arguments, state: _setupState()),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues,
          'issues',
          containsPair(
            'clean_cycle.commissionee_clean',
            'Confirm the commissionee is ready for commissioning.',
          ),
        ),
      ),
    );
  });

  test('rejects every retired top-level field', () {
    const retiredFields = <String>[
      'commissionee_type',
      'commissioning_transport',
      'network_transport',
      'model',
      'firmware',
      'state_change_method',
      'state_change_notes',
      'thread_operational_dataset',
      'controller_clean',
      'secrets_purged',
      'virtual_device',
      'fallback_transport',
    ];

    for (final field in retiredFields) {
      final arguments = _minimalArguments()
        ..[field] = field == 'commissionee_type' ? 'virtual' : 'unused';
      try {
        parser.parse(arguments: arguments, state: _setupState());
        fail('Expected $field to be rejected.');
      } on AgentRunRequestException catch (error) {
        expect(
          error.issues,
          containsPair(field, 'This field is not supported.'),
          reason: 'Expected $field to be rejected.',
        );
        expect(
          error.toString(),
          isNot(contains('unused')),
          reason: 'Retired field values must not appear in the message.',
        );
      }
    }
  });

  test('rejects retired or unknown clean_cycle fields', () {
    for (final field in const <String>[
      'controller_clean',
      'secrets_purged',
      'unknown',
    ]) {
      final arguments = _minimalArguments();
      final cleanCycle = arguments['clean_cycle']! as Map<String, Object?>;
      cleanCycle[field] = true;

      expect(
        () => parser.parse(arguments: arguments, state: _setupState()),
        throwsA(
          isA<AgentRunRequestException>().having(
            (error) => error.issues,
            'issues',
            containsPair('clean_cycle.$field', 'This field is not supported.'),
          ),
        ),
        reason: field,
      );
    }
  });

  test('rejects a Run while stored secrets have not been purged', () {
    final arguments = _minimalArguments(mode: 'full')
      ..['secrets_purged'] = false;

    expect(
      () => parser.parse(
        arguments: arguments,
        state: _setupState(hasStoredSecrets: true),
      ),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues,
          'issues',
          containsPair('secrets_purged', 'This field is not supported.'),
        ),
      ),
    );
  });

  test('never includes supplied secret values in an error', () {
    final arguments = <String, Object?>{
      'mode': 'full',
      'setup_code': 'MT:VERY-PRIVATE-SETUP-CODE',
      'wifi_ssid': 'private-ssid',
      'wifi_password': 'private-password',
    };

    try {
      parser.parse(arguments: arguments, state: _setupState());
      fail('Expected an AgentRunRequestException.');
    } on AgentRunRequestException catch (error) {
      final rendered = error.toString() + error.issues.toString();
      expect(rendered, isNot(contains('MT:VERY-PRIVATE-SETUP-CODE')));
      expect(rendered, isNot(contains('private-ssid')));
      expect(rendered, isNot(contains('private-password')));
    }
  });
}
