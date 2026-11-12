import 'dart:convert';
import 'dart:io';

import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';
import 'package:flutter_test/flutter_test.dart';

import 'report_test_fixture.dart';

void main() {
  late DeviceTestReportValidator validator;

  setUpAll(() {
    final schemaFile = File('assets/device-test-report.schema.json');
    expect(schemaFile.existsSync(), isTrue);
    validator = DeviceTestReportValidator.fromSchemaJson(
      schemaFile.readAsStringSync(),
    );
  });

  test('accepts the canonical fixture report', () {
    final report = buildFixtureReport();
    final jsonResult = validator.validateJson(jsonEncode(report.toJson()));
    final modelResult = validator.validateModel(report);

    expect(jsonResult.issues, isEmpty, reason: jsonResult.toString());
    expect(modelResult.issues, isEmpty, reason: modelResult.toString());
  });

  test('accepts the repository report example', () {
    final exampleFile = File('../doc/device-test-report.example.json');
    expect(exampleFile.existsSync(), isTrue);

    final result = validator.validateJson(exampleFile.readAsStringSync());

    expect(result.issues, isEmpty, reason: result.toString());
  });

  test('rejects a missing fixed test ID', () {
    final json = _clone(buildFixtureReport().toJson());
    final tests = json['tests']! as Map<String, dynamic>;
    tests.remove(DeviceTestId.removeFabricUi.wireName);

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.schema), isTrue);
    expect(result.contains(ReportValidationIssueKind.semantic), isTrue);
    expect(
      result.issues.map((issue) => issue.message).join(' '),
      contains('All 12 fixed test IDs'),
    );
  });

  test('rejects additional device-identifying fields', () {
    final json = _clone(buildFixtureReport().toJson());
    final controller = json['controller']! as Map<String, dynamic>;
    controller['serial_number'] = 'ABC123';

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.schema), isTrue);
    expect(
      result.issues.map((issue) => issue.path).join(' '),
      contains(r'$.controller.serial_number'),
    );
  });

  test('rejects invalid commits through both schema and semantics', () {
    final json = _clone(buildFixtureReport().toJson());
    json['plugin_commit'] = 'A' * 40;

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(
      result.issues.where((issue) => issue.path == r'$.plugin_commit'),
      isNotEmpty,
    );
  });

  test('rejects summary counts or results that do not match tests', () {
    final json = _clone(buildFixtureReport().toJson());
    final summary = json['summary']! as Map<String, dynamic>;
    summary['passed'] = 10;
    summary['result'] = 'failed';

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.semantic), isTrue);
    expect(
      result.issues.map((issue) => issue.path),
      containsAll(<String>[r'$.summary.passed', r'$.summary.result']),
    );
  });

  test('requires a non-empty notes reason for every not_run result', () {
    final json = _clone(buildFixtureReport().toJson());
    final tests = json['tests']! as Map<String, dynamic>;
    final removeFabric =
        tests[DeviceTestId.removeFabricUi.wireName]! as Map<String, dynamic>;
    removeFabric['notes'] = '   ';

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.semantic), isTrue);
    expect(
      result.issues.map((issue) => issue.message).join(' '),
      contains('non-empty reason'),
    );
  });

  test('rejects retired commissionee fields', () {
    final json = _clone(buildFixtureReport().toJson());
    final commissionee = json['commissionee']! as Map<String, dynamic>;
    commissionee['model'] = 'Example Matter Plug';
    commissionee['firmware'] = '1.0.0';
    commissionee['state_change_method'] = 'physical_control';
    commissionee['state_change_notes'] = 'The plug has a local On/Off button.';

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(
      result.issues.map((issue) => issue.path),
      containsAll(<String>[
        r'$.commissionee.model',
        r'$.commissionee.firmware',
        r'$.commissionee.state_change_method',
        r'$.commissionee.state_change_notes',
      ]),
    );
  });

  test('accepts a selected BLE commissioning route', () {
    final json = _clone(buildFixtureReport().toJson());
    final commissionee = json['commissionee']! as Map<String, dynamic>;
    commissionee['commissioning_transport'] = 'ble';

    final result = validator.validateMap(json);

    expect(result.isValid, isTrue, reason: result.toString());
  });

  test(
    'rejects a missing commissioning route through schema and semantics',
    () {
      final json = _clone(buildFixtureReport().toJson());
      final commissionee = json['commissionee']! as Map<String, dynamic>;
      commissionee.remove('commissioning_transport');

      final result = validator.validateMap(json);

      expect(result.isValid, isFalse);
      expect(
        result.issues.map((issue) => issue.path),
        contains(r'$.commissionee.commissioning_transport'),
      );
      expect(
        result.issues.map((issue) => issue.message).join(' '),
        contains('selected commissioning transport'),
      );
    },
  );

  test('rejects setup credentials even when they appear in a note', () {
    final json = _clone(buildFixtureReport().toJson());
    final tests = json['tests']! as Map<String, dynamic>;
    final commissioning =
        tests[DeviceTestId.commissioning.wireName]! as Map<String, dynamic>;
    commissioning['notes'] = 'Used setup code: 12345678901 for the retry.';

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.sensitive), isTrue);
  });

  test('rejects schema version 1 reports', () {
    final json = _clone(buildFixtureReport().toJson());
    json['schema_version'] = 1;

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(
      result.issues.map((issue) => issue.path),
      contains(r'$.schema_version'),
    );
  });

  test('rejects a non-wifi network transport', () {
    final json = _clone(buildFixtureReport().toJson());
    final commissionee = json['commissionee']! as Map<String, dynamic>;
    commissionee['network_transport'] = 'thread';

    final result = validator.validateMap(json);

    expect(result.isValid, isFalse);
    expect(
      result.issues.map((issue) => issue.path),
      contains(r'$.commissionee.network_transport'),
    );
    expect(
      result.issues.map((issue) => issue.message).join(' '),
      contains('Wi-Fi network transport'),
    );
  });

  test('rejects quick-profile data as formal evidence', () {
    final result = validator.validateModel(
      buildFixtureReport(),
      profile: TestProfile.quick,
    );

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.profile), isTrue);
  });

  test('rejects syntactically invalid JSON', () {
    final result = validator.validateJson('{not json');

    expect(result.isValid, isFalse);
    expect(result.contains(ReportValidationIssueKind.schema), isTrue);
  });
}

Map<String, dynamic> _clone(Map<String, Object?> value) {
  return jsonDecode(jsonEncode(value)) as Map<String, dynamic>;
}
