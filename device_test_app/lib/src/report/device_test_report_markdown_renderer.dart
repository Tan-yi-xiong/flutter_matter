import '../domain/domain.dart';
import 'device_test_report.dart';

/// Renders the canonical PR-facing Markdown summary from report data.
class DeviceTestReportMarkdownRenderer {
  const DeviceTestReportMarkdownRenderer();

  String render(DeviceTestReportV4 report) {
    final buffer = StringBuffer()
      ..writeln('### Device validation summary')
      ..writeln()
      ..writeln('- Plugin commit: `${report.pluginCommit}`')
      ..writeln(
        '- Test app: `${report.testApp.name} ${report.testApp.version} '
        '(${report.testApp.commit})`',
      )
      ..writeln(
        '- Controller: `${report.controller.platform.wireName}` / '
        '`${report.controller.deviceModel}` / '
        '`${report.controller.osVersion}`',
      )
      ..writeln(
        '- Commissionee: '
        'vendor `${report.commissionee.vendorId}` / '
        'product `${report.commissionee.productId}`',
      )
      ..writeln(
        '- Network transport: '
        '`${report.commissionee.networkTransport.wireName}`',
      )
      ..writeln('- Overall result: `${report.summary.result.wireName}`')
      ..writeln()
      ..writeln('| ID | Priority | Result | Duration | Notes |')
      ..writeln('| --- | --- | --- | --- | --- |');

    for (final testId in DeviceTestCatalog.all) {
      final result = report.resultFor(testId);
      final notes = result.notes == null ? '' : _escapeTableCell(result.notes!);
      buffer.writeln(
        '| `${testId.wireName}` | ${testId.priority.label} | '
        '`${result.status.wireName}` | '
        '`${result.duration.inMilliseconds} ms` | $notes |',
      );
    }

    buffer
      ..writeln()
      ..writeln('#### P1 and P2 notes');

    final noteworthy = <DeviceTestResult>[];
    for (final testId in DeviceTestCatalog.all) {
      if (testId.priority == DeviceTestPriority.p0) {
        continue;
      }
      final result = report.resultFor(testId);
      if (result.status == DeviceTestStatus.failed ||
          result.status == DeviceTestStatus.notRun) {
        noteworthy.add(result);
      }
    }

    if (noteworthy.isEmpty) {
      buffer.writeln('- None.');
    } else {
      for (final result in noteworthy) {
        final reason = _escapeListText(result.notes ?? 'No note provided.');
        buffer.writeln(
          '- `${result.testId.wireName}` '
          '(${result.testId.priority.label}, `${result.status.wireName}`): '
          '$reason',
        );
      }
    }

    buffer
      ..writeln()
      ..writeln('#### Evidence files');

    final evidenceFiles = <String>{};
    for (final testId in DeviceTestCatalog.all) {
      evidenceFiles.addAll(report.resultFor(testId).evidenceFiles);
    }
    if (evidenceFiles.isEmpty) {
      buffer.writeln('- None.');
    } else {
      for (final file in evidenceFiles) {
        buffer.writeln('- `$file`');
      }
    }

    buffer
      ..writeln()
      ..writeln('#### Sanitization')
      ..writeln()
      ..writeln(
        'Confirmed: no device identifiers, provisioning secrets, '
        'certificates, private keys, or raw logs are attached.',
      );

    return buffer.toString();
  }
}

String _escapeTableCell(String value) {
  return value
      .replaceAll(r'\', r'\\')
      .replaceAll('|', r'\|')
      .replaceAll('\r\n', '<br>')
      .replaceAll('\n', '<br>')
      .replaceAll('\r', '<br>');
}

String _escapeListText(String value) {
  return value
      .replaceAll('\r\n', '<br>')
      .replaceAll('\n', '<br>')
      .replaceAll('\r', '<br>');
}
