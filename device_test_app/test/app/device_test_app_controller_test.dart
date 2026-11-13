import 'dart:convert';

import 'package:flutter_matter_device_test_app/src/app/app.dart';
import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/ui_models.dart';
import 'package:flutter_test/flutter_test.dart';

import '../report/report_test_fixture.dart';
import 'support/fakes.dart';

void main() {
  late String schemaJson;

  setUpAll(() async {
    schemaJson = await loadReportSchema();
  });

  test('maps setup to a Run request and persists secrets first', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();

    await harness.controller.startRun(setupRequest());
    await pumpEventQueue();

    final request = harness.runner.startRequest;
    expect(request, isNotNull);
    expect(request!.runId, testRunId);
    expect(request.profile, TestProfile.full);
    expect(request.pluginCommit, testPluginCommit);
    expect(request.testApp.commit, testAppCommit);
    expect(request.targetNodeId, testTargetNodeId);
    expect(request.controller.platform, ControllerPlatform.android);
    expect(request.commissionee.vendorId, 1);
    expect(request.commissionee.productId, 1);
    expect(request.commissionee.networkTransport, NetworkTransport.wifi);
    expect(harness.maintenance.prepareCount, 1);
    expect(harness.wifiSetup.rememberedSsid, 'Test Wi-Fi');
    expect(harness.wifiSetup.rememberedPassword, 'secret');

    final secrets = harness.secrets.saved[testRunId];
    expect(secrets, isNotNull);
    expect(secrets!.setupPinCode, 20202021);
    expect(secrets.onboardingPayload, 'MT:TEST-SETUP-CODE');
    expect(
      secrets.invalidSetupOnboardingPayload,
      buildMatterManualPairingCode(
        discriminator: 1,
        hasShortDiscriminator: false,
        setupPinCode: invalidMatterSetupPinCodeFor(20202021),
        commissioningFlow: 0,
        vendorId: 1,
        productId: 1,
      ),
    );
    final network = secrets.network as WifiProvisioningSecret;
    expect(network.ssid, 'Test Wi-Fi');
    expect(network.password, 'secret');

    expect(harness.controller.state.screen, DeviceTestScreen.runner);
    expect(harness.controller.state.activeRun?.runId, testRunId);
    expect(harness.controller.state.hasStoredSecrets, isTrue);
  });

  test('blocks a Run when automatic cleanup fails', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    harness.maintenance.error = StateError('cleanup failed');
    await harness.controller.initialize();

    await harness.controller.startRun(setupRequest());
    await pumpEventQueue();

    expect(harness.maintenance.prepareCount, 1);
    expect(harness.runner.startRequest, isNull);
    expect(harness.onboarding.parseCount, 1);
    expect(harness.secrets.saved, isEmpty);
    expect(harness.controller.state.errorMessage, contains('cleanup'));
  });

  test('loads Wi-Fi prefill without projecting it into UI state', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();

    final prefill = await harness.controller.loadWifiSetupPrefill();

    expect(prefill.currentSsid, 'Test Wi-Fi');
    expect(prefill.password, 'cached-secret');
    expect(prefill.manualSsidRequired, isFalse);
    expect(harness.controller.state.hasStoredSecrets, isFalse);
  });

  test('clears the Wi-Fi credential cache explicitly', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();

    await harness.controller.clearWifiCredentials();

    expect(harness.wifiSetup.clearCount, 1);
  });

  test('blocks a Run when commit preflight fails', () async {
    final harness = buildHarness(
      schemaJson: schemaJson,
      appBootstrap: bootstrap(blocking: true),
    );
    addTearDown(harness.close);
    await harness.controller.initialize();

    await harness.controller.startRun(setupRequest());
    await pumpEventQueue();

    expect(harness.runner.startRequest, isNull);
    expect(harness.onboarding.parseCount, 0);
    expect(harness.secrets.saved, isEmpty);
    expect(harness.controller.state.errorMessage, contains('preflight'));
  });

  test('startup cleanup removes stale run state and stored secrets', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();

    expect(harness.runner.cleanupCount, 1);
    expect(harness.secrets.log, contains('secret.purgeAllStored'));
    expect(harness.controller.state.screen, DeviceTestScreen.home);
    expect(harness.controller.state.activeRun, isNull);
    expect(harness.controller.state.hasStoredSecrets, isFalse);
  });

  test('quick Runs show not-applicable report status', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();
    harness.runner.reportToBuild = buildFixtureReport();

    harness.runner.emit(terminalSnapshot(profile: TestProfile.quick));
    await pumpEventQueue();

    expect(harness.runner.buildReportCount, 0);
    expect(harness.artifacts.writes, isEmpty);
    expect(
      harness.controller.state.results?.validation.status,
      ReportUiValidationStatus.notApplicable,
    );
    expect(harness.controller.state.results?.jsonAvailable, isFalse);
    expect(harness.controller.state.results?.markdownAvailable, isFalse);
    expect(harness.controller.state.recentRun?.formalEvidence, isFalse);
  });

  test('releases busy and allows navigation when the Run completes', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();

    await harness.controller.startRun(setupRequest());
    await pumpEventQueue();
    expect(harness.controller.state.busy, isTrue);

    harness.runner.emit(terminalSnapshot(profile: TestProfile.quick));
    await pumpEventQueue();

    expect(harness.controller.state.busy, isFalse);
    expect(harness.controller.state.screen, DeviceTestScreen.runner);

    harness.controller.navigate(DeviceTestScreen.home);
    expect(harness.controller.state.screen, DeviceTestScreen.home);
  });

  test('full Runs validate, write, share, and purge from one report', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();
    final report = buildFixtureReport();
    harness.runner.reportToBuild = report;

    harness.runner.emit(terminalSnapshot());
    await pumpEventQueue(times: 20);

    expect(harness.runner.buildReportCount, 1);
    expect(harness.artifacts.writes, hasLength(1));
    final write = harness.artifacts.writes.single;
    expect(write['run_id'], testRunId);
    expect(jsonDecode(write['json']!), report.toJson());
    expect(write['markdown'], contains('### Device validation summary'));
    expect(
      harness.controller.state.results?.validation.status,
      ReportUiValidationStatus.valid,
    );
    expect(harness.controller.state.results?.jsonAvailable, isTrue);
    expect(harness.controller.state.results?.markdownAvailable, isTrue);
    expect(harness.controller.state.recentRun?.formalEvidence, isTrue);
    expect(harness.controller.formalReportJson, report.toJson());

    await harness.controller.shareJsonReport();
    await harness.controller.shareMarkdownReport();
    expect(harness.sharing.shares, <DeviceTestReportShareFormat>[
      DeviceTestReportShareFormat.json,
      DeviceTestReportShareFormat.markdown,
    ]);

    await harness.controller.purgeSecrets();
    expect(harness.secrets.log, contains('secret.purge:$testRunId'));
    expect(harness.controller.state.hasStoredSecrets, isFalse);
  });
}
