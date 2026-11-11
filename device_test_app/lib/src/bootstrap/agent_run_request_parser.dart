import '../domain/domain.dart';
import '../presentation/presentation.dart';

/// Parses bridge command arguments into the same setup request used by the UI.
///
/// Argument values, especially setup codes and network credentials, are never
/// included in thrown messages. Validation errors contain field names only.
class AgentRunRequestParser {
  const AgentRunRequestParser();

  DeviceTestSetupRequest parse({
    required Map<String, Object?> arguments,
    required DeviceTestUiState state,
  }) {
    final mode = _requiredString(arguments, 'mode');
    final profile = switch (mode) {
      'quick' => TestProfile.quick,
      'full' => TestProfile.full,
      _ => throw AgentRunRequestException(
        'mode must be quick or full.',
        issues: const <String, String>{'mode': 'Expected quick or full.'},
      ),
    };
    final commissioneeType = _enumValue(
      arguments,
      'commissionee_type',
      CommissioneeType.parse,
    );
    if (commissioneeType != CommissioneeType.real) {
      throw const AgentRunRequestException(
        'commissionee_type must be real.',
        issues: <String, String>{
          'commissionee_type':
              'Device validation requires real Matter hardware.',
        },
      );
    }
    final commissioningTransport = _enumValueOrDefault(
      arguments,
      'commissioning_transport',
      CommissioningTransport.parse,
      defaultValue: CommissioningTransport.ip.wireName,
    );
    if (commissioningTransport != CommissioningTransport.ip) {
      throw const AgentRunRequestException(
        'commissioning_transport must be ip.',
        issues: <String, String>{
          'commissioning_transport':
              'Only Wi-Fi/IP commissioning is supported.',
        },
      );
    }
    final networkTransport = _enumValue(
      arguments,
      'network_transport',
      NetworkTransport.parse,
    );
    if (networkTransport != NetworkTransport.wifi) {
      throw const AgentRunRequestException(
        'network_transport must be wifi.',
        issues: <String, String>{
          'network_transport': 'Only Wi-Fi/IP commissioning is supported.',
        },
      );
    }
    final stateChangeMethod = _enumValue(
      arguments,
      'state_change_method',
      StateChangeMethod.parse,
    );
    final cleanCycle = _requiredMap(arguments, 'clean_cycle');
    final controller = state.controllerInfo;
    final draft = DeviceTestSetupDraft(
      commissioneeType: commissioneeType,
      model: _requiredString(arguments, 'model'),
      firmware: _requiredString(arguments, 'firmware'),
      commissioningTransport: commissioningTransport,
      networkTransport: networkTransport,
      stateChangeMethod: stateChangeMethod,
      stateChangeNotes: _optionalString(arguments, 'state_change_notes') ?? '',
      setupCode: _requiredString(arguments, 'setup_code'),
      wifiSsid: _optionalString(arguments, 'wifi_ssid') ?? '',
      wifiPassword: _optionalString(arguments, 'wifi_password') ?? '',
      profile: profile,
      cleanCycle: CleanCycleConfirmations(
        controllerClean: _requiredBool(
          cleanCycle,
          'controller_clean',
          parent: 'clean_cycle',
        ),
        commissioneeClean: _requiredBool(
          cleanCycle,
          'commissionee_clean',
          parent: 'clean_cycle',
        ),
        secretsPurged: _requiredBool(
          cleanCycle,
          'secrets_purged',
          parent: 'clean_cycle',
        ),
      ),
    );
    final validation = DeviceTestSetupValidator.validate(
      draft: draft,
      controller: controller,
      preflightChecks: state.preflightChecks,
      hasStoredSecrets: state.hasStoredSecrets,
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
      commissioneeType: draft.commissioneeType,
      model: draft.model,
      firmware: draft.firmware,
      commissioningTransport: draft.commissioningTransport,
      networkTransport: draft.networkTransport,
      stateChangeMethod: draft.stateChangeMethod,
      stateChangeNotes: draft.stateChangeNotes,
      setupCode: draft.setupCode,
      wifiSsid: draft.wifiSsid,
      wifiPassword: draft.wifiPassword,
      threadOperationalDataset: draft.threadOperationalDataset,
      profile: draft.profile,
      cleanCycle: draft.cleanCycle,
    );
  }

  String _fieldWireName(SetupField field) {
    return field.name.replaceAllMapped(
      RegExp(r'([a-z0-9])([A-Z])'),
      (match) => '${match[1]}_${match[2]!.toLowerCase()}',
    );
  }

  T _enumValue<T>(
    Map<String, Object?> arguments,
    String key,
    T Function(String value) parse,
  ) {
    return _parseEnumValue(key, _requiredString(arguments, key), parse);
  }

  T _enumValueOrDefault<T>(
    Map<String, Object?> arguments,
    String key,
    T Function(String value) parse, {
    required String defaultValue,
  }) {
    return _parseEnumValue(
      key,
      _optionalString(arguments, key) ?? defaultValue,
      parse,
    );
  }

  T _parseEnumValue<T>(String key, String value, T Function(String) parse) {
    try {
      return parse(value.trim());
    } on FormatException {
      throw AgentRunRequestException(
        '$key has an unsupported value.',
        issues: <String, String>{key: 'Unsupported value.'},
      );
    }
  }

  String _requiredString(Map<String, Object?> values, String key) {
    final value = values[key];
    if (value is! String || value.trim().isEmpty) {
      throw AgentRunRequestException(
        'Missing required string argument: $key.',
        issues: <String, String>{key: 'Required non-empty string.'},
      );
    }
    return value.trim();
  }

  String? _optionalString(Map<String, Object?> values, String key) {
    final value = values[key];
    if (value == null) {
      return null;
    }
    if (value is! String) {
      throw AgentRunRequestException(
        '$key must be a string.',
        issues: <String, String>{key: 'Expected string.'},
      );
    }
    return value;
  }

  bool _requiredBool(
    Map<String, Object?> values,
    String key, {
    required String parent,
  }) {
    final value = values[key];
    if (value is! bool) {
      throw AgentRunRequestException(
        '$parent.$key must be a boolean.',
        issues: <String, String>{'$parent.$key': 'Expected boolean.'},
      );
    }
    return value;
  }

  Map<String, Object?> _requiredMap(Map<String, Object?> values, String key) {
    final value = values[key];
    if (value is! Map) {
      throw AgentRunRequestException(
        '$key must be an object.',
        issues: <String, String>{key: 'Expected object.'},
      );
    }
    return <String, Object?>{
      for (final entry in value.entries) entry.key.toString(): entry.value,
    };
  }
}

/// A safe, structured setup parsing failure for an Agent command result.
class AgentRunRequestException implements Exception {
  const AgentRunRequestException(this.message, {required this.issues});

  final String message;
  final Map<String, String> issues;

  @override
  String toString() => 'AgentRunRequestException: $message';
}
