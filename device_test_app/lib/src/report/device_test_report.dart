import 'dart:collection';

import '../domain/domain.dart';

enum ReportResult {
  passed('passed'),
  failed('failed'),
  notRun('not_run');

  const ReportResult(this.wireName);

  final String wireName;

  static ReportResult parse(String value) {
    for (final result in values) {
      if (result.wireName == value) {
        return result;
      }
    }
    throw FormatException('Unknown report result: $value');
  }
}

class ReportSummary {
  const ReportSummary({
    required this.result,
    required this.passed,
    required this.failed,
    required this.notRun,
  });

  final ReportResult result;
  final int passed;
  final int failed;
  final int notRun;

  int get total => passed + failed + notRun;

  factory ReportSummary.calculate(Iterable<DeviceTestResult> tests) {
    var passed = 0;
    var failed = 0;
    var notRun = 0;
    var hasP0NotRun = false;

    for (final test in tests) {
      if (!test.isTerminal) {
        throw ArgumentError.value(
          test.status,
          'tests',
          'Summary can only be calculated from terminal results',
        );
      }
      switch (test.status) {
        case DeviceTestStatus.passed:
          passed++;
        case DeviceTestStatus.failed:
          failed++;
        case DeviceTestStatus.notRun:
          notRun++;
          if (test.testId.priority == DeviceTestPriority.p0) {
            hasP0NotRun = true;
          }
        case DeviceTestStatus.pending:
        case DeviceTestStatus.running:
          throw StateError('Unreachable non-terminal result');
      }
    }

    final ReportResult result;
    if (failed > 0) {
      result = ReportResult.failed;
    } else if (hasP0NotRun || passed + failed + notRun == 0) {
      result = ReportResult.notRun;
    } else {
      result = ReportResult.passed;
    }

    return ReportSummary(
      result: result,
      passed: passed,
      failed: failed,
      notRun: notRun,
    );
  }

  factory ReportSummary.fromJson(Map<String, dynamic> json) {
    return ReportSummary(
      result: ReportResult.parse(_requiredString(json, 'result')),
      passed: _requiredInt(json, 'passed'),
      failed: _requiredInt(json, 'failed'),
      notRun: _requiredInt(json, 'not_run'),
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'result': result.wireName,
    'passed': passed,
    'failed': failed,
    'not_run': notRun,
  };

  bool matches(Iterable<DeviceTestResult> tests) {
    final calculated = ReportSummary.calculate(tests);
    return calculated == this;
  }

  @override
  bool operator ==(Object other) {
    return other is ReportSummary &&
        other.result == result &&
        other.passed == passed &&
        other.failed == failed &&
        other.notRun == notRun;
  }

  @override
  int get hashCode => Object.hash(result, passed, failed, notRun);
}

/// The schema-backed, formal device-validation report.
///
/// Formal reports are always full-profile reports. Quick-profile smoke runs
/// must not be represented by this type; use [RunSession] progress instead.
class DeviceTestReportV4 {
  DeviceTestReportV4({
    required this.generatedAt,
    required this.testApp,
    required this.pluginCommit,
    required this.controller,
    required this.commissionee,
    required this.summary,
    required Map<DeviceTestId, DeviceTestResult> tests,
    required this.sanitizationReviewed,
    this.schemaVersion = 4,
    this.sanitizationPolicyVersion = 1,
  }) : _tests = _normalizeTests(tests) {
    if (schemaVersion != 4) {
      throw ArgumentError.value(
        schemaVersion,
        'schemaVersion',
        'Only schema version 4 is supported',
      );
    }
    if (sanitizationPolicyVersion != 1) {
      throw ArgumentError.value(
        sanitizationPolicyVersion,
        'sanitizationPolicyVersion',
        'Only sanitization policy version 1 is supported',
      );
    }
  }

  final int schemaVersion;
  final DateTime generatedAt;
  final TestAppMetadata testApp;
  final String pluginCommit;
  final ControllerMetadata controller;
  final CommissioneeMetadata commissionee;
  final ReportSummary summary;
  final Map<DeviceTestId, DeviceTestResult> _tests;
  final bool sanitizationReviewed;
  final int sanitizationPolicyVersion;

  /// Formal reports are full-profile artifacts by definition.
  ///
  /// Profile is not serialized because schema v4 deliberately has no profile
  /// field; the presence of every catalog test ID is the JSON-level invariant.
  TestProfile get profile => TestProfile.full;

  Map<DeviceTestId, DeviceTestResult> get tests =>
      UnmodifiableMapView<DeviceTestId, DeviceTestResult>(_tests);

  DeviceTestResult resultFor(DeviceTestId testId) {
    return _tests[testId]!;
  }

  factory DeviceTestReportV4.fromJson(Map<String, dynamic> json) {
    final rawTests = _requiredMap(json, 'tests');
    final tests = <DeviceTestId, DeviceTestResult>{};
    for (final entry in rawTests.entries) {
      final testId = DeviceTestId.parse(entry.key);
      final value = _asMap(entry.value, 'tests.${entry.key}');
      tests[testId] = DeviceTestResult.fromJson(testId, value);
    }

    final sanitization = _requiredMap(json, 'sanitization');
    final reviewed = sanitization['reviewed'];
    final policyVersion = sanitization['policy_version'];
    if (reviewed is! bool) {
      throw const FormatException('sanitization.reviewed must be a boolean');
    }
    if (policyVersion is! int) {
      throw const FormatException(
        'sanitization.policy_version must be an integer',
      );
    }

    final schemaVersion = json['schema_version'];
    if (schemaVersion is! int) {
      throw const FormatException('schema_version must be an integer');
    }

    return DeviceTestReportV4(
      schemaVersion: schemaVersion,
      generatedAt: _requiredDateTime(json, 'generated_at'),
      testApp: TestAppMetadata.fromJson(_requiredMap(json, 'test_app')),
      pluginCommit: _requiredString(json, 'plugin_commit'),
      controller: ControllerMetadata.fromJson(_requiredMap(json, 'controller')),
      commissionee: CommissioneeMetadata.fromJson(
        _requiredMap(json, 'commissionee'),
      ),
      summary: ReportSummary.fromJson(_requiredMap(json, 'summary')),
      tests: tests,
      sanitizationReviewed: reviewed,
      sanitizationPolicyVersion: policyVersion,
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'schema_version': schemaVersion,
    'generated_at': generatedAt.toUtc().toIso8601String(),
    'test_app': testApp.toJson(),
    'plugin_commit': pluginCommit,
    'controller': controller.toJson(),
    'commissionee': commissionee.toJson(),
    'summary': summary.toJson(),
    'tests': <String, Object?>{
      for (final testId in DeviceTestCatalog.all)
        testId.wireName: _tests[testId]!.toJson(),
    },
    'sanitization': <String, Object?>{
      'reviewed': sanitizationReviewed,
      'policy_version': sanitizationPolicyVersion,
    },
  };
}

Map<DeviceTestId, DeviceTestResult> _normalizeTests(
  Map<DeviceTestId, DeviceTestResult> source,
) {
  final expectedIds = DeviceTestCatalog.allIds;
  if (source.length != expectedIds.length ||
      !source.keys.toSet().containsAll(expectedIds)) {
    throw ArgumentError.value(
      source.keys,
      'tests',
      'A formal report must contain every fixed test ID exactly once',
    );
  }

  final normalized = <DeviceTestId, DeviceTestResult>{};
  for (final testId in DeviceTestCatalog.all) {
    final result = source[testId]!;
    if (result.testId != testId) {
      throw ArgumentError.value(
        testId,
        'tests',
        'Result key and testId must match',
      );
    }
    normalized[testId] = result;
  }
  return UnmodifiableMapView<DeviceTestId, DeviceTestResult>(normalized);
}

Map<String, dynamic> _requiredMap(Map<String, dynamic> json, String key) {
  return _asMap(json[key], key);
}

Map<String, dynamic> _asMap(Object? value, String key) {
  if (value is! Map<String, dynamic>) {
    throw FormatException('$key must be an object');
  }
  return value;
}

String _requiredString(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! String) {
    throw FormatException('$key must be a string');
  }
  return value;
}

int _requiredInt(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! int) {
    throw FormatException('$key must be an integer');
  }
  return value;
}

DateTime _requiredDateTime(Map<String, dynamic> json, String key) {
  final value = _requiredString(json, key);
  final parsed = DateTime.tryParse(value);
  if (parsed == null) {
    throw FormatException('$key must be an ISO-8601 date-time');
  }
  return parsed;
}
