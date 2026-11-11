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
    expect(request.commissionee.model, 'Matter test plug');
    expect(request.commissionee.firmware, '1.2.3');
    expect(request.commissionee.networkTransport, NetworkTransport.wifi);
    expect(
      request.commissionee.stateChangeMethod,
      StateChangeMethod.physicalControl,
    );

    final secrets = harness.secrets.saved[testRunId];
    expect(secrets, isNotNull);
    expect(secrets!.setupPinCode, 20202021);
    expect(secrets.onboardingPayload, 'MT:TEST-SETUP-CODE');
    final network = secrets.network as WifiProvisioningSecret;
    expect(network.ssid, 'Test Wi-Fi');
    expect(network.password, 'secret');

    expect(harness.controller.state.screen, DeviceTestScreen.runner);
    expect(harness.controller.state.activeRun?.runId, testRunId);
    expect(harness.controller.state.hasStoredSecrets, isTrue);
  });

  test('maps Thread credentials into secure provisioning bytes', () async {
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    await harness.controller.initialize();

    await harness.controller.startRun(
      setupRequest(networkTransport: NetworkTransport.thread),
    );
    await pumpEventQueue();

    final network =
        harness.secrets.saved[testRunId]!.network as ThreadProvisioningSecret;
    expect(network.operationalDataset, <int>[
      0x0e,
      0x08,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x01,
      0x00,
      0x00,
    ]);
    expect(
      harness.runner.startRequest?.commissionee.networkTransport,
      NetworkTransport.thread,
    );
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

  test('loads and resumes an unfinished Run', () async {
    final session = RunSession.start(
      id: testRunId,
      profile: TestProfile.full,
      testApp: const TestAppMetadata(
        name: 'flutter_matter_device_test_app',
        version: '1.0.0',
        commit: testAppCommit,
      ),
      pluginCommit: testPluginCommit,
      startedAt: testNow,
      controller: const ControllerMetadata(
        platform: ControllerPlatform.android,
        deviceModel: 'Pixel test controller',
        osVersion: 'Android 16',
        appBuild: '1.0.0 (1)',
      ),
      commissionee: const CommissioneeMetadata(
        type: CommissioneeType.real,
        model: 'Matter test plug',
        firmware: '1.2.3',
        networkTransport: NetworkTransport.wifi,
        stateChangeMethod: StateChangeMethod.physicalControl,
      ),
    ).withPhase(RunPhase.testing, at: testNow);
    final harness = buildHarness(schemaJson: schemaJson);
    addTearDown(harness.close);
    harness.runner.unfinished = PersistedRunState(
      session: session,
      execution: const RunExecutionContextSnapshot(),
      targetNodeId: 99,
    );
    harness.runner.resumeSnapshot = RunnerStateSnapshot.forSession(
      session: session,
      at: testNow,
      message: 'Resuming the device test Run.',
    );
    harness.secrets.saved[testRunId] = ProvisioningSecrets(
      onboardingPayload: 'MT:TEST-SETUP-CODE',
      setupPinCode: 20202021,
      network: const WifiProvisioningSecret(
        ssid: 'Test Wi-Fi',
        password: 'secret',
      ),
    );

    await harness.controller.initialize();

    expect(harness.controller.state.activeRun?.runId, testRunId);
    expect(harness.controller.state.activeRun?.canResume, isTrue);
    expect(harness.controller.state.hasStoredSecrets, isTrue);

    await harness.controller.resumeActiveRun();
    await pumpEventQueue();

    expect(harness.runner.resumeCount, 1);
    expect(harness.controller.state.screen, DeviceTestScreen.runner);
    expect(harness.controller.state.activeRun?.runId, testRunId);
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
