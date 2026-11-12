import '../domain/domain.dart';
import 'device_test_report.dart';
import 'sensitive_data_policy.dart';

class ReportBuildException implements Exception {
  ReportBuildException(Iterable<String> issues)
    : issues = List<String>.unmodifiable(issues);

  final List<String> issues;

  @override
  String toString() => 'ReportBuildException: ${issues.join('; ')}';
}

/// Builds a formal report from a completed full-profile run.
///
/// The caller supplies [generatedAt] so identical session snapshots and inputs
/// always produce byte-for-byte identical report JSON.
class DeviceTestReportBuilder {
  const DeviceTestReportBuilder();

  DeviceTestReportV3 buildFormal(
    RunSession session, {
    required DateTime generatedAt,
    required bool sanitizationReviewed,
  }) {
    final issues = <String>[];
    if (session.profile != TestProfile.full) {
      issues.add('Formal reports require the full test profile.');
    }
    if (session.controller == null) {
      issues.add('Controller metadata is required.');
    }
    if (session.commissionee == null) {
      issues.add('Commissionee metadata is required.');
    } else {
      if (session.commissionee!.commissioningTransport == null) {
        issues.add(
          'Formal reports require a selected commissioning transport.',
        );
      }
      if (session.commissionee!.networkTransport != NetworkTransport.wifi) {
        issues.add('Formal reports require Wi-Fi network transport.');
      }
    }
    if (!session.allResultsTerminal) {
      issues.add('Every test must have a terminal result.');
    }
    if (!_isGitCommit(session.pluginCommit)) {
      issues.add('plugin_commit must be a 40-character lowercase Git SHA.');
    }
    if (!_isGitCommit(session.testApp.commit)) {
      issues.add('test_app.commit must be a 40-character lowercase Git SHA.');
    }
    if (!sanitizationReviewed) {
      issues.add('Sanitization review must be confirmed.');
    }

    for (final result in session.orderedResults) {
      if (result.status == DeviceTestStatus.notRun &&
          (result.notes == null || result.notes!.trim().isEmpty)) {
        issues.add('${result.testId.wireName} requires a not_run reason.');
      }
    }

    if (issues.isNotEmpty) {
      throw ReportBuildException(issues);
    }

    final results = <DeviceTestId, DeviceTestResult>{
      for (final testId in DeviceTestCatalog.all)
        testId: session.results[testId]!,
    };
    final report = DeviceTestReportV3(
      generatedAt: generatedAt,
      testApp: session.testApp,
      pluginCommit: session.pluginCommit,
      controller: session.controller!,
      commissionee: session.commissionee!,
      summary: ReportSummary.calculate(results.values),
      tests: results,
      sanitizationReviewed: sanitizationReviewed,
    );

    final findings = SensitiveDataPolicy.scan(report.toJson());
    if (findings.isNotEmpty) {
      throw ReportBuildException(
        findings.map(
          (finding) => '${finding.path}: ${finding.category} is not allowed.',
        ),
      );
    }

    return report;
  }
}

final RegExp _gitCommitPattern = RegExp(r'^[0-9a-f]{40}$');

bool _isGitCommit(String value) => _gitCommitPattern.hasMatch(value);
