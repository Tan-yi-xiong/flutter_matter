import '../application/ports.dart';
import '../domain/domain.dart';
import '../presentation/presentation.dart';

/// Parses bridge command arguments into the same minimal setup request used by
/// the UI.
///
/// Argument values, especially setup codes and network credentials, are never
/// included in thrown messages. Validation errors contain field names only.
class AgentRunRequestParser {
  const AgentRunRequestParser();

  static const Set<String> _allowedFields = <String>{
    'mode',
    'setup_code',
    'wifi_ssid',
    'wifi_password',
    'commissionee_ip',
    'commissionee_port',
  };

  static const Set<String> _retiredFields = <String>{'clean_cycle'};

  DeviceTestSetupRequest parse({
    required Map<String, Object?> arguments,
    required DeviceTestUiState state,
  }) {
    for (final retired in _retiredFields) {
      if (arguments.containsKey(retired)) {
        throw AgentRunRequestException(
          'The Run request contains retired fields: $retired.',
          issues: <String, String>{
            retired:
                'This field was retired. The commissionee reset is now an '
                'operator action after the Run finishes.',
          },
        );
      }
    }
    final unsupported =
        arguments.keys
            .where((key) => !_allowedFields.contains(key))
            .toList(growable: false)
          ..sort();
    if (unsupported.isNotEmpty) {
      throw AgentRunRequestException(
        'The Run request contains unsupported fields: ${unsupported.join(', ')}.',
        issues: <String, String>{
          for (final field in unsupported)
            field: 'This field is not supported.',
        },
      );
    }

    final mode = _requiredString(arguments, 'mode');
    final profile = switch (mode) {
      'quick' => TestProfile.quick,
      'full' => TestProfile.full,
      _ => throw AgentRunRequestException(
        'mode must be quick or full.',
        issues: const <String, String>{'mode': 'Expected quick or full.'},
      ),
    };
    final controller = state.controllerInfo;
    final draft = DeviceTestSetupDraft(
      setupCode: _requiredString(arguments, 'setup_code'),
      wifiSsid: _requiredString(arguments, 'wifi_ssid'),
      wifiPassword: _optionalString(arguments, 'wifi_password') ?? '',
      profile: profile,
    );
    final validation = DeviceTestSetupValidator.validate(
      draft: draft,
      controller: controller,
      preflightChecks: state.preflightChecks,
    );
    if (!validation.isValid) {
      throw AgentRunRequestException(
        'The Run setup is incomplete or unsafe.',
        issues: <String, String>{
          for (final entry in validation.errors.entries)
            _fieldWireName(entry.key): entry.value,
        },
      );
    }

    return DeviceTestSetupRequest(
      controller: controller!,
      setupCode: draft.setupCode.trim(),
      wifiSsid: draft.wifiSsid.trim(),
      wifiPassword: draft.wifiPassword,
      profile: draft.profile,
      onNetworkEndpoint: _optionalOnNetworkEndpoint(arguments),
    );
  }

  OnNetworkCommissioningEndpoint? _optionalOnNetworkEndpoint(
    Map<String, Object?> arguments,
  ) {
    final addressValue = arguments['commissionee_ip'];
    final portValue = arguments['commissionee_port'];
    if (addressValue == null && portValue == null) {
      return null;
    }
    if (addressValue is! String || addressValue.trim().isEmpty) {
      throw const AgentRunRequestException(
        'commissionee_ip and commissionee_port must be provided together.',
        issues: <String, String>{
          'commissionee_ip': 'A non-empty string is required.',
        },
      );
    }
    if (portValue is! int || portValue < 1 || portValue > 65535) {
      throw const AgentRunRequestException(
        'commissionee_port must be a valid TCP/UDP port.',
        issues: <String, String>{
          'commissionee_port': 'An integer from 1 to 65535 is required.',
        },
      );
    }
    return OnNetworkCommissioningEndpoint(
      address: addressValue.trim(),
      port: portValue,
    );
  }

  String _fieldWireName(SetupField field) {
    return field.name.replaceAllMapped(
      RegExp(r'([a-z0-9])([A-Z])'),
      (match) => '${match[1]}_${match[2]!.toLowerCase()}',
    );
  }

  String _requiredString(Map<String, Object?> arguments, String key) {
    final value = arguments[key];
    if (value is! String || value.trim().isEmpty) {
      throw AgentRunRequestException(
        '$key is required.',
        issues: <String, String>{key: 'A non-empty string is required.'},
      );
    }
    return value;
  }

  String? _optionalString(Map<String, Object?> arguments, String key) {
    final value = arguments[key];
    if (value == null) {
      return null;
    }
    if (value is! String) {
      throw AgentRunRequestException(
        '$key must be a string.',
        issues: <String, String>{key: 'Expected a string.'},
      );
    }
    return value;
  }
}

class AgentRunRequestException implements Exception {
  const AgentRunRequestException(this.message, {required this.issues});

  final String message;
  final Map<String, String> issues;

  @override
  String toString() => 'AgentRunRequestException: $message';
}
