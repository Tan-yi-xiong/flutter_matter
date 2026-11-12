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
    expect(first.summary.passed, 11);
    expect(first.summary.notRun, 1);
    expect(first.summary.result, ReportResult.passed);
    expect(first.profile, TestProfile.full);
    expect(
      first.commissionee.commissioningTransport,
      CommissioningTransport.ip,
    );
    expect(first.commissionee.vendorId, 4660);
    expect(first.commissionee.productId, 22136);
  });

  test('typed reports survive a JSON round trip', () {
    final original = buildFixtureReport();
    final decoded = DeviceTestReportV3.fromJson(
      jsonDecode(jsonEncode(original.toJson())) as Map<String, dynamic>,
    );

    expect(jsonEncode(decoded.toJson()), jsonEncode(original.toJson()));
  });

  test('accepts a selected BLE commissioning route', () {
    final report = builder.buildFormal(
      buildFixtureSession(
        commissionee: const CommissioneeMetadata(
          vendorId: 4660,
          productId: 22136,
          commissioningTransport: CommissioningTransport.ble,
          networkTransport: NetworkTransport.wifi,
        ),
      ),
      generatedAt: fixtureGeneratedAt,
      sanitizationReviewed: true,
    );

    expect(
      report.commissionee.commissioningTransport,
      CommissioningTransport.ble,
    );
    expect(report.commissionee.networkTransport, NetworkTransport.wifi);
  });

  test('accepts a selected IP commissioning route', () {
    final report = builder.buildFormal(
      buildFixtureSession(
        commissionee: const CommissioneeMetadata(
          vendorId: 4660,
          productId: 22136,
          commissioningTransport: CommissioningTransport.ip,
          networkTransport: NetworkTransport.wifi,
        ),
      ),
      generatedAt: fixtureGeneratedAt,
      sanitizationReviewed: true,
    );

    expect(
      report.commissionee.commissioningTransport,
      CommissioningTransport.ip,
    );
  });

  test('rejects a missing commissioning route', () {
    final session = buildFixtureSession(
      commissionee: const CommissioneeMetadata(
        vendorId: 4660,
        productId: 22136,
        networkTransport: NetworkTransport.wifi,
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
          contains('selected commissioning transport'),
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
        commissioningTransport: CommissioningTransport.ip,
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
        commissioningTransport: CommissioningTransport.ip,
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

  test('rejects schema version 1 reports', () {
    final legacyJson = <String, Object?>{
      ...buildFixtureReport().toJson(),
      'schema_version': 1,
    };

    expect(() => DeviceTestReportV3.fromJson(legacyJson), throwsArgumentError);
    expect(
      () => DeviceTestReportV3(
        schemaVersion: 1,
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
