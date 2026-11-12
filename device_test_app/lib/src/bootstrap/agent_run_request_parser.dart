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
    'clean_cycle',
  };

  DeviceTestSetupRequest parse({
    required Map<String, Object?> arguments,
    required DeviceTestUiState state,
  }) {
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
    final cleanCycle = _requiredMap(arguments, 'clean_cycle');
    final unexpectedCleanCycleFields =
        cleanCycle.keys
            .where((key) => key != 'commissionee_clean')
            .toList(growable: false)
          ..sort();
    if (unexpectedCleanCycleFields.isNotEmpty) {
      throw AgentRunRequestException(
        'The Run request contains unsupported clean_cycle fields: '
        '${unexpectedCleanCycleFields.join(', ')}.',
        issues: <String, String>{
          for (final field in unexpectedCleanCycleFields)
            'clean_cycle.$field': 'This field is not supported.',
        },
      );
    }
    final commissioneeClean = _requiredBool(
      cleanCycle,
      'commissionee_clean',
      parent: 'clean_cycle',
    );
    if (!commissioneeClean) {
      throw const AgentRunRequestException(
        'The commissionee must be factory-reset and in a commissioning window.',
        issues: <String, String>{
          'clean_cycle.commissionee_clean':
              'Confirm the commissionee is ready for commissioning.',
        },
      );
    }

    final controller = state.controllerInfo;
    final draft = DeviceTestSetupDraft(
      setupCode: _requiredString(arguments, 'setup_code'),
      wifiSsid: _requiredString(arguments, 'wifi_ssid'),
      wifiPassword: _optionalString(arguments, 'wifi_password') ?? '',
      profile: profile,
      cleanCycle: const CleanCycleConfirmations(commissioneeClean: true),
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
      cleanCycle: draft.cleanCycle,
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

  Map<String, Object?> _requiredMap(
    Map<String, Object?> arguments,
    String key,
  ) {
    final value = arguments[key];
    if (value is! Map<String, Object?>) {
      throw AgentRunRequestException(
        '$key is required.',
        issues: <String, String>{key: 'An object is required.'},
      );
    }
    return value;
  }

  bool _requiredBool(
    Map<String, Object?> arguments,
    String key, {
    required String parent,
  }) {
    final value = arguments[key];
    if (value is! bool) {
      throw AgentRunRequestException(
        '$parent.$key is required.',
        issues: <String, String>{'$parent.$key': 'A boolean is required.'},
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
