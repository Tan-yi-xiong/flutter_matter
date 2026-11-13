import 'dart:collection';

import 'device_test_catalog.dart';
import 'device_test_result.dart';
import 'test_metadata.dart';

enum RunPhase {
  idle('idle'),
  preparing('preparing'),
  commissioning('commissioning'),
  connecting('connecting'),
  testing('testing'),
  awaitingOperator('awaiting_operator'),
  finalizing('finalizing'),
  completed('completed'),
  failed('failed'),
  cancelled('cancelled');

  const RunPhase(this.wireName);

  final String wireName;

  bool get isTerminal =>
      this == completed || this == failed || this == cancelled;

  static RunPhase parse(String value) {
    for (final phase in values) {
      if (phase.wireName == value) {
        return phase;
      }
    }
    throw FormatException('Unknown run phase: $value');
  }
}

/// Test progress represented as an immutable, persistable snapshot.
class RunSession {
  RunSession({
    required this.id,
    required this.profile,
    required this.testApp,
    required this.pluginCommit,
    required this.createdAt,
    required this.updatedAt,
    this.phase = RunPhase.idle,
    this.controller,
    this.commissionee,
    this.lastError,
    Map<DeviceTestId, DeviceTestResult> results = const {},
  }) : results = _normalizeResults(profile, results) {
    if (id.trim().isEmpty) {
      throw ArgumentError.value(id, 'id', 'Must not be empty');
    }
    if (updatedAt.isBefore(createdAt)) {
      throw ArgumentError.value(
        updatedAt,
        'updatedAt',
        'Must not be before createdAt',
      );
    }
  }

  final String id;
  final TestProfile profile;
  final TestAppMetadata testApp;
  final String pluginCommit;
  final DateTime createdAt;
  final DateTime updatedAt;
  final RunPhase phase;
  final ControllerMetadata? controller;
  final CommissioneeMetadata? commissionee;
  final String? lastError;
  final Map<DeviceTestId, DeviceTestResult> results;

  factory RunSession.start({
    required String id,
    required TestProfile profile,
    required TestAppMetadata testApp,
    required String pluginCommit,
    required DateTime startedAt,
    ControllerMetadata? controller,
    CommissioneeMetadata? commissionee,
  }) {
    return RunSession(
      id: id,
      profile: profile,
      testApp: testApp,
      pluginCommit: pluginCommit,
      createdAt: startedAt,
      updatedAt: startedAt,
      controller: controller,
      commissionee: commissionee,
    );
  }

  List<DeviceTestId> get expectedTestIds => profile.testIds;

  Iterable<DeviceTestResult> get orderedResults sync* {
    for (final testId in expectedTestIds) {
      yield results[testId]!;
    }
  }

  DeviceTestResult? get nextActionableResult {
    for (final result in orderedResults) {
      if (result.status == DeviceTestStatus.pending ||
          result.status == DeviceTestStatus.running) {
        return result;
      }
    }
    return null;
  }

  DeviceTestId? get nextActionableTestId => nextActionableResult?.testId;

  int get terminalResultCount =>
      orderedResults.where((result) => result.isTerminal).length;

  double get progress {
    if (expectedTestIds.isEmpty) {
      return 0;
    }
    return terminalResultCount / expectedTestIds.length;
  }

  bool get allResultsTerminal => terminalResultCount == expectedTestIds.length;

  RunSession withPhase(
    RunPhase phase, {
    required DateTime at,
    String? lastError,
  }) {
    return _copy(
      phase: phase,
      updatedAt: at,
      lastError: lastError ?? this.lastError,
    );
  }

  RunSession withOperatorMetadata({
    required ControllerMetadata controller,
    required CommissioneeMetadata commissionee,
    required DateTime at,
  }) {
    return _copy(
      controller: controller,
      commissionee: commissionee,
      updatedAt: at,
    );
  }

  RunSession startTest(DeviceTestId testId, {required DateTime at}) {
    final current = _resultForExpectedTest(testId);
    if (current.isTerminal) {
      return this;
    }
    return _replaceResult(
      current.copyWith(status: DeviceTestStatus.running),
      at: at,
    );
  }

  RunSession recordResult(DeviceTestResult result, {required DateTime at}) {
    if (!result.isTerminal) {
      throw ArgumentError.value(
        result.status,
        'result.status',
        'Recorded results must be terminal',
      );
    }
    _resultForExpectedTest(result.testId);
    return _replaceResult(result, at: at);
  }

  Map<String, Object?> toJson() {
    return <String, Object?>{
      'snapshot_version': 2,
      'id': id,
      'profile': profile.wireName,
      'test_app': testApp.toJson(),
      'plugin_commit': pluginCommit,
      'created_at': createdAt.toUtc().toIso8601String(),
      'updated_at': updatedAt.toUtc().toIso8601String(),
      'phase': phase.wireName,
      if (controller != null) 'controller': controller!.toJson(),
      if (commissionee != null) 'commissionee': commissionee!.toJson(),
      if (lastError != null) 'last_error': lastError,
      'results': <String, Object?>{
        for (final testId in expectedTestIds)
          testId.wireName: results[testId]!.toJson(),
      },
    };
  }

  factory RunSession.fromJson(Map<String, dynamic> json) {
    final version = json['snapshot_version'];
    if (version != 2) {
      throw FormatException('Unsupported run snapshot version: $version');
    }

    final rawResults = json['results'];
    if (rawResults != null && rawResults is! Map<String, dynamic>) {
      throw const FormatException('results must be an object');
    }
    final parsedResults = <DeviceTestId, DeviceTestResult>{};
    if (rawResults != null) {
      for (final entry in (rawResults as Map<String, dynamic>).entries) {
        final testId = DeviceTestId.parse(entry.key);
        final value = entry.value;
        if (value is! Map<String, dynamic>) {
          throw FormatException('${entry.key} result must be an object');
        }
        parsedResults[testId] = DeviceTestResult.fromJson(testId, value);
      }
    }

    final rawController = json['controller'];
    final rawCommissionee = json['commissionee'];
    final rawLastError = json['last_error'];
    if (rawLastError != null && rawLastError is! String) {
      throw const FormatException('last_error must be a string');
    }

    return RunSession(
      id: _requiredString(json, 'id'),
      profile: TestProfile.parse(_requiredString(json, 'profile')),
      testApp: TestAppMetadata.fromJson(_requiredMap(json, 'test_app')),
      pluginCommit: _requiredString(json, 'plugin_commit'),
      createdAt: _requiredDateTime(json, 'created_at'),
      updatedAt: _requiredDateTime(json, 'updated_at'),
      phase: RunPhase.parse(_requiredString(json, 'phase')),
      controller: rawController == null
          ? null
          : ControllerMetadata.fromJson(_asMap(rawController, 'controller')),
      commissionee: rawCommissionee == null
          ? null
          : CommissioneeMetadata.fromJson(
              _asMap(rawCommissionee, 'commissionee'),
            ),
      lastError: rawLastError as String?,
      results: parsedResults,
    );
  }

  DeviceTestResult _resultForExpectedTest(DeviceTestId testId) {
    if (!profile.includes(testId)) {
      throw ArgumentError.value(
        testId,
        'testId',
        'Test is not part of the ${profile.wireName} profile',
      );
    }
    return results[testId]!;
  }

  RunSession _replaceResult(DeviceTestResult result, {required DateTime at}) {
    final updatedResults = Map<DeviceTestId, DeviceTestResult>.of(results);
    updatedResults[result.testId] = result;
    return _copy(results: updatedResults, updatedAt: at);
  }

  RunSession _copy({
    RunPhase? phase,
    DateTime? updatedAt,
    ControllerMetadata? controller,
    CommissioneeMetadata? commissionee,
    String? lastError,
    Map<DeviceTestId, DeviceTestResult>? results,
  }) {
    return RunSession(
      id: id,
      profile: profile,
      testApp: testApp,
      pluginCommit: pluginCommit,
      createdAt: createdAt,
      updatedAt: updatedAt ?? this.updatedAt,
      phase: phase ?? this.phase,
      controller: controller ?? this.controller,
      commissionee: commissionee ?? this.commissionee,
      lastError: lastError ?? this.lastError,
      results: results ?? this.results,
    );
  }
}

Map<DeviceTestId, DeviceTestResult> _normalizeResults(
  TestProfile profile,
  Map<DeviceTestId, DeviceTestResult> source,
) {
  final expectedIds = profile.testIds.toSet();
  for (final entry in source.entries) {
    if (!expectedIds.contains(entry.key)) {
      throw ArgumentError.value(
        entry.key,
        'results',
        'Result is not part of the ${profile.wireName} profile',
      );
    }
    if (entry.value.testId != entry.key) {
      throw ArgumentError.value(
        entry.key,
        'results',
        'Result key and testId must match',
      );
    }
  }

  final normalized = <DeviceTestId, DeviceTestResult>{
    for (final testId in profile.testIds)
      testId: source[testId] ?? DeviceTestResult(testId: testId),
  };
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

DateTime _requiredDateTime(Map<String, dynamic> json, String key) {
  final value = _requiredString(json, key);
  final parsed = DateTime.tryParse(value);
  if (parsed == null) {
    throw FormatException('$key must be an ISO-8601 date-time');
  }
  return parsed;
}
