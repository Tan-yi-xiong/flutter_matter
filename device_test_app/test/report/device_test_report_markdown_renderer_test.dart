import 'dart:convert';

import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';
import 'package:flutter_test/flutter_test.dart';

import 'report_test_fixture.dart';

void main() {
  const renderer = DeviceTestReportMarkdownRenderer();

  test('renders every JSON report identity and result', () {
    final report = buildFixtureReport();
    final json =
        jsonDecode(jsonEncode(report.toJson())) as Map<String, dynamic>;
    final markdown = renderer.render(report);

    expect(markdown, contains('### Device validation summary'));
    expect(markdown, contains(report.pluginCommit));
    expect(markdown, contains('flutter_matter_device_test_app 1.0.0'));
    expect(markdown, contains('Pixel 8'));
    expect(markdown, contains('Android 15'));
    expect(markdown, contains('Example Matter Plug'));
    expect(markdown, contains('android-build-install.png'));
    expect(markdown, contains('The optional UI path was unavailable'));

    final rawTests = json['tests']! as Map<String, dynamic>;
    for (final testId in DeviceTestCatalog.all) {
      final rawResult = rawTests[testId.wireName]! as Map<String, dynamic>;
      expect(markdown, contains('`${testId.wireName}`'));
      expect(markdown, contains('`${rawResult['status']}`'));
    }
  });

  test('renders summary states and escapes Markdown table content', () {
    final report = buildFixtureReport();
    final markdown = renderer.render(report);

    expect(markdown, contains('- Commissioning transport: `ip`'));
    expect(markdown, contains('- Network transport: `wifi`'));
    expect(markdown, isNot(contains('- Commissioning transport: `ble`')));
    expect(markdown, contains('- Overall result: `passed`'));
    expect(markdown, contains('#### P1 and P2 notes'));
    expect(markdown, contains('#### Evidence files'));
    expect(
      markdown,
      contains(
        'Confirmed: no device identifiers, provisioning secrets, '
        'certificates, private keys, or raw logs are attached.',
      ),
    );
  });

  test('escapes pipes and line breaks from notes', () {
    final report = const DeviceTestReportBuilder().buildFormal(
      buildFixtureSession(
        overrides: <DeviceTestId, DeviceTestResult>{
          DeviceTestId.invalidWifiPassword: DeviceTestResult(
            testId: DeviceTestId.invalidWifiPassword,
            status: DeviceTestStatus.failed,
            notes: 'failed | with\ntwo lines',
          ),
        },
      ),
      generatedAt: fixtureGeneratedAt,
      sanitizationReviewed: true,
    );

    final markdown = renderer.render(report);

    expect(markdown, contains(r'failed \| with<br>two lines'));
    expect(markdown, isNot(contains('failed | with\n')));
  });
}
