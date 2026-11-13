import 'dart:convert';

import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';
import 'package:flutter_test/flutter_test.dart';

import 'report_test_fixture.dart';

void main() {
  const builder = DeviceTestReportBuilder();

  test('builds a deterministic full-profile report', () {
    final first = builder.buildFormal(
      buildFixtureSession(),
      generatedAt: fixtureGeneratedAt,
      sanitizationReviewed: true,
    );
    final second = builder.buildFormal(
      buildFixtureSession(),
      generatedAt: fixtureGeneratedAt,
      sanitizationReviewed: true,
    );

    expect(jsonEncode(first.toJson()), jsonEncode(second.toJson()));
    expect(first.summary.passed, 10);
    expect(first.summary.notRun, 1);
    expect(first.summary.result, ReportResult.passed);
    expect(first.profile, TestProfile.full);
    expect(first.commissionee.vendorId, 4660);
    expect(first.commissionee.productId, 22136);
    expect(first.commissionee.networkTransport, NetworkTransport.wifi);
  });

  test('emits schema version 4 without any transport route field', () {
    final report = buildFixtureReport();
    final json = report.toJson();

    expect(report.schemaVersion, 4);
    expect(json['schema_version'], 4);
    expect(
      (json['commissionee']! as Map<String, dynamic>).containsKey(
        'commissioning_transport',
      ),
      isFalse,
    );
    expect(
      jsonEncode(report.toJson()),
      isNot(contains('commissioning_transport')),
    );
  });

  test('typed reports survive a JSON round trip', () {
    final original = buildFixtureReport();
    final decoded = DeviceTestReportV4.fromJson(
      jsonDecode(jsonEncode(original.toJson())) as Map<String, dynamic>,
    );

    expect(jsonEncode(decoded.toJson()), jsonEncode(original.toJson()));
  });

  test('rejects legacy v2 and v3 schema versions', () {
    final v3Json = <String, Object?>{
      ...buildFixtureReport().toJson(),
      'schema_version': 3,
    };
    final v2Json = <String, Object?>{
      ...buildFixtureReport().toJson(),
      'schema_version': 2,
    };

    expect(() => DeviceTestReportV4.fromJson(v3Json), throwsArgumentError);
    expect(() => DeviceTestReportV4.fromJson(v2Json), throwsArgumentError);
  });

  test('rejects constructing a typed report with a retired schema version', () {
    expect(
      () => DeviceTestReportV4(
        schemaVersion: 3,
        generatedAt: fixtureGeneratedAt,
        testApp: fixtureTestApp,
        pluginCommit: fixturePluginCommit,
        controller: buildFixtureSession().controller!,
        commissionee: buildFixtureSession().commissionee!,
        summary: buildFixtureReport().summary,
        tests: buildFixtureReport().tests,
        sanitizationReviewed: true,
      ),
      throwsArgumentError,
    );
  });

  test('rejects sessions without commissionee metadata', () {
    final session = buildFixtureSession();

    expect(
      () => builder.buildFormal(
        RunSession(
          id: session.id,
          profile: session.profile,
          testApp: session.testApp,
          pluginCommit: session.pluginCommit,
          createdAt: session.createdAt,
          updatedAt: session.updatedAt,
          phase: session.phase,
          controller: session.controller,
          commissionee: null,
          results: session.results,
        ),
        generatedAt: fixtureGeneratedAt,
        sanitizationReviewed: true,
      ),
      throwsA(
        isA<ReportBuildException>().having(
          (error) => error.issues.join(' '),
          'issues',
          contains('Commissionee metadata is required'),
        ),
      ),
    );
  });

  test('rejects quick-profile sessions', () {
    final quick = RunSession(
      id: 'quick-run',
      profile: TestProfile.quick,
      testApp: fixtureTestApp,
      pluginCommit: fixturePluginCommit,
      createdAt: fixtureGeneratedAt,
      updatedAt: fixtureGeneratedAt,
      controller: const ControllerMetadata(
        platform: ControllerPlatform.android,
        deviceModel: 'Pixel 8',
        osVersion: 'Android 15',
        appBuild: 'debug 1.0.0 (1)',
      ),
      commissionee: const CommissioneeMetadata(
        vendorId: 4660,
        productId: 22136,
        networkTransport: NetworkTransport.wifi,
      ),
      results: <DeviceTestId, DeviceTestResult>{
        for (final testId in TestProfile.quick.testIds)
          testId: DeviceTestResult(
            testId: testId,
            status: DeviceTestStatus.passed,
          ),
      },
    );

    expect(
      () => builder.buildFormal(
        quick,
        generatedAt: fixtureGeneratedAt,
        sanitizationReviewed: true,
      ),
      throwsA(
        isA<ReportBuildException>().having(
          (error) => error.issues.join(' '),
          'issues',
          contains('full test profile'),
        ),
      ),
    );
  });

  test('rejects a non-wifi network transport for formal evidence', () {
    final session = buildFixtureSession(
      commissionee: const CommissioneeMetadata(
        vendorId: 4660,
        productId: 22136,
        networkTransport: NetworkTransport.thread,
      ),
    );

    expect(
      () => builder.buildFormal(
        session,
        generatedAt: fixtureGeneratedAt,
        sanitizationReviewed: true,
      ),
      throwsA(
        isA<ReportBuildException>().having(
          (error) => error.issues.join(' '),
          'issues',
          contains('Wi-Fi network transport'),
        ),
      ),
    );
  });

  test('rejects a report with a pending test', () {
    final session = buildFixtureSession(
      overrides: <DeviceTestId, DeviceTestResult>{
        DeviceTestId.commissioning: DeviceTestResult(
          testId: DeviceTestId.commissioning,
        ),
      },
    );

    expect(
      () => builder.buildFormal(
        session,
        generatedAt: fixtureGeneratedAt,
        sanitizationReviewed: true,
      ),
      throwsA(
        isA<ReportBuildException>().having(
          (error) => error.issues.join(' '),
          'issues',
          contains('terminal result'),
        ),
      ),
    );
  });

  test('rejects not_run results without a reason', () {
    final session = buildFixtureSession(
      overrides: <DeviceTestId, DeviceTestResult>{
        DeviceTestId.removeFabricUi: DeviceTestResult(
          testId: DeviceTestId.removeFabricUi,
          status: DeviceTestStatus.notRun,
        ),
      },
    );

    expect(
      () => builder.buildFormal(
        session,
        generatedAt: fixtureGeneratedAt,
        sanitizationReviewed: true,
      ),
      throwsA(
        isA<ReportBuildException>().having(
          (error) => error.issues.join(' '),
          'issues',
          contains('requires a not_run reason'),
        ),
      ),
    );
  });

  test('requires explicit sanitization review', () {
    expect(
      () => builder.buildFormal(
        buildFixtureSession(),
        generatedAt: fixtureGeneratedAt,
        sanitizationReviewed: false,
      ),
      throwsA(
        isA<ReportBuildException>().having(
          (error) => error.issues.join(' '),
          'issues',
          contains('Sanitization review'),
        ),
      ),
    );
  });
}
