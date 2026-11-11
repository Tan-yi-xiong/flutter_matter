import 'package:flutter_matter_device_test_app/src/bootstrap/agent_run_request_parser.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

import '../presentation/support/presentation_fixtures.dart';

void main() {
  const parser = AgentRunRequestParser();

  test('parses a complete virtual Wi-Fi full run', () {
    final state = setupState();
    final request = parser.parse(
      arguments: <String, Object?>{
        'mode': 'full',
        'commissionee_type': 'virtual',
        'fallback_reason': 'No qualified physical Matter device is available.',
        'virtual_fallback_confirmed': true,
        'model': 'Virtual OnOff Switch',
        'firmware': 'v1.6.1.0',
        'network_transport': 'wifi',
        'state_change_method': 'commissionee_ui',
        'state_change_notes': 'Use the test App UI.',
        'setup_code': 'MT:PRIVATE-SETUP-CODE',
        'wifi_ssid': 'test-network',
        'wifi_password': 'test-password',
        'clean_cycle': <String, Object?>{
          'controller_clean': true,
          'commissionee_clean': true,
          'secrets_purged': true,
        },
      },
      state: state,
    );

    expect(request.profile, TestProfile.full);
    expect(request.commissioneeType, CommissioneeType.virtual);
    expect(request.networkTransport, NetworkTransport.wifi);
    expect(request.stateChangeMethod, StateChangeMethod.commissioneeUi);
    expect(request.controller, same(state.controllerInfo));
  });

  test('parses a Thread quick run', () {
    final request = parser.parse(
      arguments: <String, Object?>{
        'mode': 'quick',
        'commissionee_type': 'real',
        'model': 'Matter switch',
        'firmware': '1.2.3',
        'network_transport': 'thread',
        'state_change_method': 'physical_control',
        'setup_code': 'MT:PRIVATE-SETUP-CODE',
        'thread_operational_dataset': '0x00112233',
        'clean_cycle': <String, Object?>{
          'controller_clean': true,
          'commissionee_clean': true,
          'secrets_purged': true,
        },
      },
      state: setupState(),
    );

    expect(request.profile, TestProfile.quick);
    expect(request.networkTransport, NetworkTransport.thread);
  });

  test('rejects virtual setups without fallback acknowledgement', () {
    expect(
      () => parser.parse(
        arguments: <String, Object?>{
          'mode': 'quick',
          'commissionee_type': 'virtual',
          'model': 'Virtual switch',
          'firmware': '1.0.0',
          'network_transport': 'wifi',
          'state_change_method': 'commissionee_ui',
          'setup_code': 'MT:PRIVATE-SETUP-CODE',
          'wifi_ssid': 'test-network',
          'clean_cycle': <String, Object?>{
            'controller_clean': true,
            'commissionee_clean': true,
            'secrets_purged': true,
          },
        },
        state: setupState(),
      ),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues.keys,
          'issue keys',
          containsAll(<String>['fallback_reason', 'fallback_confirmation']),
        ),
      ),
    );
  });

  test('rejects an unknown network transport', () {
    final arguments = <String, Object?>{
      'mode': 'quick',
      'commissionee_type': 'real',
      'model': 'Matter switch',
      'firmware': '1.2.3',
      'network_transport': 'unknown',
      'state_change_method': 'physical_control',
      'setup_code': 'MT:PRIVATE-SETUP-CODE',
      'clean_cycle': <String, Object?>{
        'controller_clean': true,
        'commissionee_clean': true,
        'secrets_purged': true,
      },
    };

    expect(
      () => parser.parse(arguments: arguments, state: setupState()),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues.keys,
          'issue keys',
          contains('network_transport'),
        ),
      ),
    );
  });

  test('requires notes for the other state-change method', () {
    final arguments = <String, Object?>{
      'mode': 'quick',
      'commissionee_type': 'real',
      'model': 'Matter switch',
      'firmware': '1.2.3',
      'network_transport': 'wifi',
      'state_change_method': 'other',
      'setup_code': 'MT:PRIVATE-SETUP-CODE',
      'wifi_ssid': 'test-network',
      'clean_cycle': <String, Object?>{
        'controller_clean': true,
        'commissionee_clean': true,
        'secrets_purged': true,
      },
    };

    expect(
      () => parser.parse(arguments: arguments, state: setupState()),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues.keys,
          'issue keys',
          contains('state_change_notes'),
        ),
      ),
    );
  });

  test('rejects a Run while stored secrets have not been purged', () {
    expect(
      () => parser.parse(
        arguments: <String, Object?>{
          'mode': 'full',
          'commissionee_type': 'real',
          'model': 'Matter switch',
          'firmware': '1.2.3',
          'network_transport': 'wifi',
          'state_change_method': 'physical_control',
          'setup_code': 'MT:PRIVATE-SETUP-CODE',
          'wifi_ssid': 'test-network',
          'clean_cycle': <String, Object?>{
            'controller_clean': true,
            'commissionee_clean': true,
            'secrets_purged': true,
          },
        },
        state: setupState(hasStoredSecrets: true),
      ),
      throwsA(
        isA<AgentRunRequestException>().having(
          (error) => error.issues.keys,
          'issue keys',
          contains('secrets_purged'),
        ),
      ),
    );
  });

  test('never includes supplied secret values in an error', () {
    try {
      parser.parse(
        arguments: <String, Object?>{
          'mode': 'full',
          'commissionee_type': 'real',
          'model': 'Matter switch',
          'firmware': '1.2.3',
          'network_transport': 'wifi',
          'state_change_method': 'physical_control',
          'setup_code': 'MT:VERY-PRIVATE-SETUP-CODE',
          'wifi_ssid': 'private-ssid',
          'wifi_password': 'private-password',
          'clean_cycle': <String, Object?>{
            'controller_clean': false,
            'commissionee_clean': false,
            'secrets_purged': false,
          },
        },
        state: setupState(),
      );
      fail('Expected an AgentRunRequestException.');
    } on AgentRunRequestException catch (error) {
      final rendered = error.toString() + error.issues.toString();
      expect(rendered, isNot(contains('MT:VERY-PRIVATE-SETUP-CODE')));
      expect(rendered, isNot(contains('private-ssid')));
      expect(rendered, isNot(contains('private-password')));
    }
  });
}
