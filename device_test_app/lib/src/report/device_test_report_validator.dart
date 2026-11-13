import 'dart:convert';

import '../domain/domain.dart';
import 'device_test_report.dart';
import 'sensitive_data_policy.dart';

enum ReportValidationIssueKind { schema, semantic, sensitive, profile }

class ReportValidationIssue {
  const ReportValidationIssue({
    required this.kind,
    required this.path,
    required this.message,
  });

  final ReportValidationIssueKind kind;
  final String path;
  final String message;

  @override
  String toString() => '${kind.name} at $path: $message';

  @override
  bool operator ==(Object other) {
    return other is ReportValidationIssue &&
        other.kind == kind &&
        other.path == path &&
        other.message == message;
  }

  @override
  int get hashCode => Object.hash(kind, path, message);
}

class ReportValidationResult {
  ReportValidationResult(Iterable<ReportValidationIssue> issues)
    : issues = List<ReportValidationIssue>.unmodifiable(issues);

  final List<ReportValidationIssue> issues;

  bool get isValid => issues.isEmpty;

  bool contains(ReportValidationIssueKind kind) {
    return issues.any((issue) => issue.kind == kind);
  }

  @override
  String toString() {
    if (isValid) {
      return 'ReportValidationResult(valid)';
    }
    return 'ReportValidationResult(${issues.join('; ')})';
  }
}

/// Validates the canonical schema subset used by device-test-report.schema.json
/// and the semantic rules that JSON Schema cannot express.
class DeviceTestReportValidator {
  DeviceTestReportValidator._(this._schema);

  static const String schemaAssetPath = 'assets/device-test-report.schema.json';

  final Map<String, dynamic> _schema;

  factory DeviceTestReportValidator.fromSchemaJson(String schemaJson) {
    final decoded = jsonDecode(schemaJson);
    if (decoded is! Map<String, dynamic>) {
      throw const FormatException('Report schema must be a JSON object');
    }
    if (decoded[r'$schema'] != 'https://json-schema.org/draft/2020-12/schema') {
      throw const FormatException('Report schema must use JSON Schema 2020-12');
    }
    return DeviceTestReportValidator._(decoded);
  }

  factory DeviceTestReportValidator.fromSchemaMap(Map<String, dynamic> schema) {
    return DeviceTestReportValidator.fromSchemaJson(jsonEncode(schema));
  }

  ReportValidationResult validateJson(String jsonText) {
    final Object? decoded;
    try {
      decoded = jsonDecode(jsonText);
    } on FormatException catch (error) {
      return ReportValidationResult(<ReportValidationIssue>[
        ReportValidationIssue(
          kind: ReportValidationIssueKind.schema,
          path: r'$',
          message: 'Invalid JSON: ${error.message}',
        ),
      ]);
    }

    if (decoded is! Map<String, dynamic>) {
      return ReportValidationResult(<ReportValidationIssue>[
        const ReportValidationIssue(
          kind: ReportValidationIssueKind.schema,
          path: r'$',
          message: 'Report must be a JSON object.',
        ),
      ]);
    }
    return validateMap(decoded);
  }

  ReportValidationResult validateMap(Map<String, dynamic> report) {
    final issues = <ReportValidationIssue>[];
    final checker = _JsonSchemaChecker(_schema);
    checker.validate(report, _schema, r'$', issues);
    _validateSemantics(report, issues);
    return ReportValidationResult(_deduplicate(issues));
  }

  /// Validates a typed report for formal evidence use.
  ///
  /// JSON schema v4 deliberately has no profile field. The caller supplies the
  /// profile that produced the report, and formal evidence must be full.
  ReportValidationResult validateModel(
    DeviceTestReportV4 report, {
    TestProfile profile = TestProfile.full,
  }) {
    final issues = <ReportValidationIssue>[];
    final checker = _JsonSchemaChecker(_schema);
    final json = report.toJson();
    checker.validate(json, _schema, r'$', issues);
    _validateSemantics(json, issues);

    if (profile != TestProfile.full) {
      issues.add(
        const ReportValidationIssue(
          kind: ReportValidationIssueKind.profile,
          path: r'$.profile',
          message: 'Formal reports require the full test profile.',
        ),
      );
    }

    return ReportValidationResult(_deduplicate(issues));
  }
}

void _validateSemantics(
  Map<String, dynamic> report,
  List<ReportValidationIssue> issues,
) {
  _validateFormalSafety(report, issues);
  final rawTests = report['tests'];
  if (rawTests is Map<String, dynamic>) {
    final actualIds = rawTests.keys.toSet();
    final expectedIds = DeviceTestCatalog.all
        .map((testId) => testId.wireName)
        .toSet();
    final missing = expectedIds.difference(actualIds);
    final unexpected = actualIds.difference(expectedIds);
    final expectedCount = DeviceTestCatalog.all.length;
    if (actualIds.length != expectedCount ||
        missing.isNotEmpty ||
        unexpected.isNotEmpty) {
      final details = <String>[
        if (missing.isNotEmpty) 'missing ${missing.join(', ')}',
        if (unexpected.isNotEmpty) 'unexpected ${unexpected.join(', ')}',
      ];
      issues.add(
        ReportValidationIssue(
          kind: ReportValidationIssueKind.semantic,
          path: r'$.tests',
          message:
              'All $expectedCount fixed test IDs must appear exactly once'
              '${details.isEmpty ? '' : ': ${details.join('; ')}'}.',
        ),
      );
    }

    for (final testId in DeviceTestCatalog.all) {
      final rawResult = rawTests[testId.wireName];
      if (rawResult is! Map<String, dynamic>) {
        continue;
      }
      if (rawResult['status'] == DeviceTestStatus.notRun.wireName) {
        final notes = rawResult['notes'];
        if (notes is! String || notes.trim().isEmpty) {
          issues.add(
            ReportValidationIssue(
              kind: ReportValidationIssueKind.semantic,
              path: r'$.tests.' + testId.wireName,
              message: 'A not_run result requires a non-empty reason in notes.',
            ),
          );
        }
      }
    }

    _validateSummary(report, rawTests, issues);
  }

  _validateCommit(report, 'plugin_commit', r'$.plugin_commit', issues);
  final rawTestApp = report['test_app'];
  if (rawTestApp is Map<String, dynamic>) {
    _validateCommit(rawTestApp, 'commit', r'$.test_app.commit', issues);
  }

  for (final finding in SensitiveDataPolicy.scan(report)) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.sensitive,
        path: finding.path,
        message: '${finding.category} is not allowed in public report data.',
      ),
    );
  }
}

/// Semantic checks for formal-report safety that stay meaningful even when
/// a caller supplies a schema older or looser than the canonical v4 asset.
void _validateFormalSafety(
  Map<String, dynamic> report,
  List<ReportValidationIssue> issues,
) {
  final commissionee = report['commissionee'];
  if (commissionee is! Map<String, dynamic>) {
    return;
  }

  final networkTransport = commissionee['network_transport'];
  if (networkTransport is String &&
      networkTransport != NetworkTransport.wifi.wireName) {
    issues.add(
      const ReportValidationIssue(
        kind: ReportValidationIssueKind.semantic,
        path: r'$.commissionee.network_transport',
        message: 'Formal reports require Wi-Fi network transport.',
      ),
    );
  }
}

void _validateSummary(
  Map<String, dynamic> report,
  Map<String, dynamic> rawTests,
  List<ReportValidationIssue> issues,
) {
  final rawSummary = report['summary'];
  if (rawSummary is! Map<String, dynamic>) {
    return;
  }

  final passed = rawSummary['passed'];
  final failed = rawSummary['failed'];
  final notRun = rawSummary['not_run'];
  if (passed is int && failed is int && notRun is int) {
    final expectedCount = DeviceTestCatalog.all.length;
    if (passed + failed + notRun != expectedCount) {
      issues.add(
        ReportValidationIssue(
          kind: ReportValidationIssueKind.semantic,
          path: r'$.summary',
          message: 'Summary counts must total $expectedCount.',
        ),
      );
    }
  }

  final results = <DeviceTestResult>[];
  for (final testId in DeviceTestCatalog.all) {
    final rawResult = rawTests[testId.wireName];
    if (rawResult is! Map<String, dynamic>) {
      return;
    }
    final rawStatus = rawResult['status'];
    if (rawStatus is! String) {
      return;
    }
    final DeviceTestStatus status;
    try {
      status = DeviceTestStatus.parse(rawStatus);
    } on FormatException {
      return;
    }
    if (!status.isTerminal) {
      return;
    }
    results.add(DeviceTestResult(testId: testId, status: status));
  }
  if (results.length != DeviceTestCatalog.all.length) {
    return;
  }

  final calculated = ReportSummary.calculate(results);
  if (passed is int && passed != calculated.passed) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.semantic,
        path: r'$.summary.passed',
        message: 'Expected ${calculated.passed}, found $passed.',
      ),
    );
  }
  if (failed is int && failed != calculated.failed) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.semantic,
        path: r'$.summary.failed',
        message: 'Expected ${calculated.failed}, found $failed.',
      ),
    );
  }
  if (notRun is int && notRun != calculated.notRun) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.semantic,
        path: r'$.summary.not_run',
        message: 'Expected ${calculated.notRun}, found $notRun.',
      ),
    );
  }

  final result = rawSummary['result'];
  if (result is String && result != calculated.result.wireName) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.semantic,
        path: r'$.summary.result',
        message: 'Expected ${calculated.result.wireName}, found $result.',
      ),
    );
  }
}

final RegExp _gitCommitPattern = RegExp(r'^[0-9a-f]{40}$');

void _validateCommit(
  Map<String, dynamic> source,
  String key,
  String path,
  List<ReportValidationIssue> issues,
) {
  final value = source[key];
  if (value is String && !_gitCommitPattern.hasMatch(value)) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.semantic,
        path: path,
        message: 'Commit must be a 40-character lowercase hexadecimal SHA.',
      ),
    );
  }
}

List<ReportValidationIssue> _deduplicate(
  Iterable<ReportValidationIssue> issues,
) {
  final seen = <ReportValidationIssue>{};
  final result = <ReportValidationIssue>[];
  for (final issue in issues) {
    if (seen.add(issue)) {
      result.add(issue);
    }
  }
  return result;
}

class _JsonSchemaChecker {
  _JsonSchemaChecker(this.rootSchema);

  final Map<String, dynamic> rootSchema;

  void validate(
    Object? value,
    Object? schemaNode,
    String path,
    List<ReportValidationIssue> issues,
  ) {
    if (schemaNode is bool) {
      if (!schemaNode) {
        _schemaIssue(issues, path, 'Value is rejected by the schema.');
      }
      return;
    }
    if (schemaNode is! Map<String, dynamic>) {
      _schemaIssue(issues, path, 'Schema node must be an object or boolean.');
      return;
    }

    final reference = schemaNode[r'$ref'];
    if (reference != null) {
      if (reference is! String || !reference.startsWith('#/')) {
        _schemaIssue(
          issues,
          path,
          'Only local schema references are supported.',
        );
      } else {
        final target = _resolveReference(reference);
        if (target == null) {
          _schemaIssue(issues, path, 'Unresolved schema reference $reference.');
        } else {
          validate(value, target, path, issues);
        }
      }
    }

    final allOf = schemaNode['allOf'];
    if (allOf is List<dynamic>) {
      for (final subschema in allOf) {
        validate(value, subschema, path, issues);
      }
    }

    final typeNode = schemaNode['type'];
    if (typeNode != null) {
      final allowedTypes = typeNode is String
          ? <String>[typeNode]
          : typeNode is List<dynamic>
          ? typeNode.whereType<String>().toList(growable: false)
          : const <String>[];
      if (allowedTypes.isEmpty ||
          !allowedTypes.any((type) => _matchesType(value, type))) {
        _schemaIssue(
          issues,
          path,
          'Expected ${allowedTypes.isEmpty ? typeNode : allowedTypes.join(' or ')}, '
          'found ${_typeName(value)}.',
        );
        return;
      }
    }

    if (schemaNode.containsKey('const') &&
        !_deepEquals(value, schemaNode['const'])) {
      _schemaIssue(
        issues,
        path,
        'Expected constant ${jsonEncode(schemaNode['const'])}.',
      );
    }

    final enumValues = schemaNode['enum'];
    if (enumValues is List<dynamic> &&
        !enumValues.any((candidate) => _deepEquals(value, candidate))) {
      _schemaIssue(issues, path, 'Expected one of ${jsonEncode(enumValues)}.');
    }

    if (value is String) {
      _validateString(value, schemaNode, path, issues);
    } else if (value is Map<String, dynamic>) {
      _validateObject(value, schemaNode, path, issues);
    } else if (value is List<dynamic>) {
      _validateArray(value, schemaNode, path, issues);
    } else if (value is num) {
      _validateNumber(value, schemaNode, path, issues);
    }

    final notSchema = schemaNode['not'];
    if (notSchema != null) {
      final nestedIssues = <ReportValidationIssue>[];
      validate(value, notSchema, path, nestedIssues);
      if (nestedIssues.isEmpty) {
        _schemaIssue(issues, path, 'Value matches a forbidden schema.');
      }
    }
  }

  void _validateString(
    String value,
    Map<String, dynamic> schemaNode,
    String path,
    List<ReportValidationIssue> issues,
  ) {
    final minLength = schemaNode['minLength'];
    if (minLength is int && value.runes.length < minLength) {
      _schemaIssue(
        issues,
        path,
        'String must contain at least $minLength characters.',
      );
    }
    final maxLength = schemaNode['maxLength'];
    if (maxLength is int && value.runes.length > maxLength) {
      _schemaIssue(
        issues,
        path,
        'String must contain at most $maxLength characters.',
      );
    }

    final pattern = schemaNode['pattern'];
    if (pattern is String) {
      try {
        if (!RegExp(pattern).hasMatch(value)) {
          _schemaIssue(issues, path, 'String does not match $pattern.');
        }
      } on FormatException {
        _schemaIssue(issues, path, 'Schema pattern is invalid.');
      }
    }

    final format = schemaNode['format'];
    if (format == 'date-time' && !_isDateTime(value)) {
      _schemaIssue(issues, path, 'String must be an RFC 3339 date-time.');
    }
  }

  void _validateObject(
    Map<String, dynamic> value,
    Map<String, dynamic> schemaNode,
    String path,
    List<ReportValidationIssue> issues,
  ) {
    final required = schemaNode['required'];
    if (required is List<dynamic>) {
      for (final key in required.whereType<String>()) {
        if (!value.containsKey(key)) {
          _schemaIssue(issues, '$path.$key', 'Required property is missing.');
        }
      }
    }

    final propertiesNode = schemaNode['properties'];
    final properties = propertiesNode is Map<String, dynamic>
        ? propertiesNode
        : const <String, dynamic>{};
    for (final entry in properties.entries) {
      if (value.containsKey(entry.key)) {
        validate(value[entry.key], entry.value, '$path.${entry.key}', issues);
      }
    }

    final additional = schemaNode['additionalProperties'];
    for (final entry in value.entries) {
      if (properties.containsKey(entry.key)) {
        continue;
      }
      if (additional == false) {
        _schemaIssue(
          issues,
          '$path.${entry.key}',
          'Additional properties are not allowed.',
        );
      } else if (additional is Map<String, dynamic>) {
        validate(entry.value, additional, '$path.${entry.key}', issues);
      }
    }
  }

  void _validateArray(
    List<dynamic> value,
    Map<String, dynamic> schemaNode,
    String path,
    List<ReportValidationIssue> issues,
  ) {
    final maxItems = schemaNode['maxItems'];
    if (maxItems is int && value.length > maxItems) {
      _schemaIssue(issues, path, 'Array must contain at most $maxItems items.');
    }
    final minItems = schemaNode['minItems'];
    if (minItems is int && value.length < minItems) {
      _schemaIssue(
        issues,
        path,
        'Array must contain at least $minItems items.',
      );
    }

    final itemsSchema = schemaNode['items'];
    if (itemsSchema != null) {
      for (var index = 0; index < value.length; index++) {
        validate(value[index], itemsSchema, '$path[$index]', issues);
      }
    }

    if (schemaNode['uniqueItems'] == true) {
      for (var left = 0; left < value.length; left++) {
        for (var right = left + 1; right < value.length; right++) {
          if (_deepEquals(value[left], value[right])) {
            _schemaIssue(
              issues,
              '$path[$right]',
              'Array items must be unique.',
            );
          }
        }
      }
    }
  }

  void _validateNumber(
    num value,
    Map<String, dynamic> schemaNode,
    String path,
    List<ReportValidationIssue> issues,
  ) {
    final minimum = schemaNode['minimum'];
    if (minimum is num && value < minimum) {
      _schemaIssue(issues, path, 'Number must be at least $minimum.');
    }
    final maximum = schemaNode['maximum'];
    if (maximum is num && value > maximum) {
      _schemaIssue(issues, path, 'Number must be at most $maximum.');
    }
  }

  Object? _resolveReference(String reference) {
    var current = rootSchema as Object?;
    for (final rawSegment in reference.substring(2).split('/')) {
      if (current is! Map<String, dynamic>) {
        return null;
      }
      final segment = rawSegment.replaceAll('~1', '/').replaceAll('~0', '~');
      current = current[segment];
    }
    return current;
  }

  void _schemaIssue(
    List<ReportValidationIssue> issues,
    String path,
    String message,
  ) {
    issues.add(
      ReportValidationIssue(
        kind: ReportValidationIssueKind.schema,
        path: path,
        message: message,
      ),
    );
  }
}

bool _matchesType(Object? value, String type) {
  return switch (type) {
    'object' => value is Map<String, dynamic>,
    'array' => value is List<dynamic>,
    'string' => value is String,
    'integer' => value is int,
    'number' => value is num,
    'boolean' => value is bool,
    'null' => value == null,
    _ => false,
  };
}

String _typeName(Object? value) {
  if (value == null) {
    return 'null';
  }
  if (value is Map<String, dynamic>) {
    return 'object';
  }
  if (value is List<dynamic>) {
    return 'array';
  }
  if (value is String) {
    return 'string';
  }
  if (value is int) {
    return 'integer';
  }
  if (value is double) {
    return 'number';
  }
  if (value is bool) {
    return 'boolean';
  }
  return value.runtimeType.toString();
}

bool _deepEquals(Object? left, Object? right) {
  if (left is Map && right is Map) {
    if (left.length != right.length) {
      return false;
    }
    for (final entry in left.entries) {
      if (!right.containsKey(entry.key) ||
          !_deepEquals(entry.value, right[entry.key])) {
        return false;
      }
    }
    return true;
  }
  if (left is List && right is List) {
    if (left.length != right.length) {
      return false;
    }
    for (var index = 0; index < left.length; index++) {
      if (!_deepEquals(left[index], right[index])) {
        return false;
      }
    }
    return true;
  }
  if (left is num && right is num) {
    return left == right;
  }
  return left == right;
}

final RegExp _dateTimePattern = RegExp(
  r'^(\d{4})-(\d{2})-(\d{2})T'
  r'(\d{2}):(\d{2}):(\d{2})(?:\.\d+)?'
  r'(?:Z|[+-](?:[01]\d|2[0-3]):[0-5]\d)$',
);

bool _isDateTime(String value) {
  final match = _dateTimePattern.firstMatch(value);
  if (match == null) {
    return false;
  }
  final year = int.parse(match.group(1)!);
  final month = int.parse(match.group(2)!);
  final day = int.parse(match.group(3)!);
  final hour = int.parse(match.group(4)!);
  final minute = int.parse(match.group(5)!);
  final second = int.parse(match.group(6)!);
  if (hour > 23 || minute > 59 || second > 59) {
    return false;
  }
  final date = DateTime.utc(year, month, day, hour, minute, second);
  return date.year == year &&
      date.month == month &&
      date.day == day &&
      date.hour == hour &&
      date.minute == minute &&
      date.second == second;
}
