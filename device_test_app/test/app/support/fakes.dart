import 'dart:async';
import 'dart:io';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/app/app.dart';
import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/ui_models.dart';
import 'package:flutter_matter_device_test_app/src/report/report.dart';

const testPluginCommit = 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa';
const testAppCommit = 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb';
const testRunId = 'run-app-controller-test';
const testTargetNodeId = 424242;

final testNow = DateTime.utc(2026, 11, 12, 12);

class FixedClock implements ClockPort {
  const FixedClock(this.value);

  final DateTime value;

  @override
  DateTime now() => value;
}

class FakeDeviceTestBootstrap implements DeviceTestBootstrapPort {
  FakeDeviceTestBootstrap(this.value);

  final DeviceTestAppBootstrap value;

  @override
  Future<DeviceTestAppBootstrap> load() async => value;
}

class FakeProvisioningSecrets implements ProvisioningSecretsPort {
  final Map<String, ProvisioningSecrets> saved =
      <String, ProvisioningSecrets>{};
  final List<String> log = <String>[];

  @override
  Future<ProvisioningSecrets?> load(String runId) async {
    log.add('secret.load:$runId');
    return saved[runId];
  }

  @override
  Future<void> purge(String runId) async {
    log.add('secret.purge:$runId');
    saved.remove(runId);
  }

  @override
  Future<void> save(String runId, ProvisioningSecrets secrets) async {
    log.add('secret.save:$runId');
    saved[runId] = secrets;
  }

  @override
  Future<void> purgeAll() async {
    log.add('secret.purgeAll');
    saved.clear();
  }
}

class FakeRunMaintenance implements DeviceRunMaintenancePort {
  int prepareCount = 0;
  Object? error;

  @override
  Future<void> prepareForNewRun() async {
    prepareCount++;
    if (error != null) {
      throw error!;
    }
  }
}

class FakeWifiSetup implements WifiSetupPort {
  WifiSetupPrefill prefill = const WifiSetupPrefill(
    currentSsid: 'Test Wi-Fi',
    password: 'cached-secret',
    manualSsidRequired: false,
  );
  int clearCount = 0;
  String? rememberedSsid;
  String? rememberedPassword;

  @override
  Future<WifiSetupPrefill> loadPrefill() async => prefill;

  @override
  Future<void> remember({
    required String ssid,
    required String password,
  }) async {
    rememberedSsid = ssid;
    rememberedPassword = password;
  }

  @override
  Future<void> clear() async {
    clearCount++;
    prefill = WifiSetupPrefill(
      currentSsid: prefill.currentSsid,
      manualSsidRequired: prefill.manualSsidRequired,
    );
  }
}

class FakeOnboardingPayloadReader implements OnboardingPayloadReader {
  FakeOnboardingPayloadReader({this.setupPinCode = 20202021});

  final int setupPinCode;
  int parseCount = 0;

  @override
  Future<OnboardingPayload> parse(String setupCode) async {
    parseCount++;
    return OnboardingPayload(
      version: 0,
      vendorId: 1,
      productId: 1,
      commissioningFlow: 0,
      discoveryCapabilities: const <DiscoveryCapability>{
        DiscoveryCapability.ble,
      },
      discriminator: 1,
      hasShortDiscriminator: false,
      setupPinCode: setupPinCode,
    );
  }
}

class FakeReportArtifacts implements DeviceTestReportArtifactPort {
  FakeReportArtifacts(this.schemaJson);

  final String schemaJson;
  final List<Map<String, String>> writes = <Map<String, String>>[];

  @override
  Future<String> loadCanonicalSchema() async => schemaJson;

  @override
  Future<DeviceTestReportFiles> write({
    required String runId,
    required String jsonContents,
    required String markdownContents,
  }) async {
    writes.add(<String, String>{
      'run_id': runId,
      'json': jsonContents,
      'markdown': markdownContents,
    });
    return DeviceTestReportFiles(
      jsonPath: '/reports/$runId/device-test-report.json',
      markdownPath: '/reports/$runId/device-test-report.md',
    );
  }
}

class FakeReportSharing implements DeviceTestReportSharePort {
  final List<DeviceTestReportShareFormat> shares =
      <DeviceTestReportShareFormat>[];

  @override
  Future<void> share(
    DeviceTestReportFiles files, {
    required DeviceTestReportShareFormat format,
  }) async {
    shares.add(format);
  }
}

class FakeDeviceTestRunner implements DeviceTestRunPort {
  final StreamController<RunnerStateSnapshot> _states =
      StreamController<RunnerStateSnapshot>.broadcast();
  final StreamController<RunnerEvent> _events =
      StreamController<RunnerEvent>.broadcast();

  RunnerStateSnapshot? _snapshot;
  PersistedRunState? unfinished;
  RunnerStateSnapshot? resumeSnapshot;
  DeviceTestReportV3? reportToBuild;
  int buildReportCount = 0;
  int resumeCount = 0;
  RunStartRequest? startRequest;
  bool disposed = false;

  @override
  RunnerStateSnapshot get snapshot =>
      _snapshot ?? RunnerStateSnapshot.idle(at: testNow);

  @override
  Stream<RunnerStateSnapshot> get stateStream => _states.stream;

  @override
  Stream<RunnerEvent> get eventStream => _events.stream;

  void emit(RunnerStateSnapshot snapshot) {
    _snapshot = snapshot;
    _states.add(snapshot);
  }

  void emitEvent(RunnerEvent event) {
    _events.add(event);
  }

  @override
  Future<PersistedRunState?> loadUnfinished() async => unfinished;

  @override
  Future<RunnerStateSnapshot> start(RunStartRequest request) async {
    startRequest = request;
    final session = RunSession.start(
      id: request.runId,
      profile: request.profile,
      testApp: request.testApp,
      pluginCommit: request.pluginCommit,
      startedAt: testNow,
      controller: request.controller,
      commissionee: request.commissionee,
    ).withPhase(RunPhase.preparing, at: testNow);
    final snapshot = RunnerStateSnapshot.forSession(
      session: session,
      at: testNow,
      message: 'Preparing the device test Run.',
    );
    emit(snapshot);
    return snapshot;
  }

  @override
  Future<RunnerStateSnapshot?> resume() async {
    resumeCount++;
    final snapshot = resumeSnapshot;
    if (snapshot != null) {
      emit(snapshot);
    }
    return snapshot;
  }

  @override
  Future<void> stop({String reason = 'Stopped by operator.'}) async {}

  @override
  Future<DeviceTestReportV3?> buildFormalReport({
    required DateTime generatedAt,
    required bool sanitizationReviewed,
  }) async {
    buildReportCount++;
    return reportToBuild;
  }

  @override
  Future<void> dispose() async {
    disposed = true;
    await _states.close();
    await _events.close();
  }
}

DeviceTestAppBootstrap bootstrap({
  bool blocking = false,
  String pluginCommit = testPluginCommit,
}) {
  return DeviceTestAppBootstrap(
    controller: const ControllerInfoViewModel(
      platform: ControllerPlatform.android,
      deviceModel: 'Pixel test controller',
      osVersion: 'Android 16',
      appBuild: '1.0.0 (1)',
    ),
    preflightChecks: <PreflightCheckViewModel>[
      PreflightCheckViewModel(
        id: 'plugin_commit',
        label: 'PLUGIN_COMMIT',
        status: blocking ? PreflightStatus.failed : PreflightStatus.passed,
      ),
      const PreflightCheckViewModel(
        id: 'test_app_commit',
        label: 'TEST_APP_COMMIT',
        status: PreflightStatus.passed,
      ),
    ],
    testApp: const TestAppMetadata(
      name: 'flutter_matter_device_test_app',
      version: '1.0.0',
      commit: testAppCommit,
    ),
    pluginCommit: pluginCommit,
  );
}

DeviceTestSetupRequest setupRequest({
  TestProfile profile = TestProfile.full,
  String setupCode = 'MT:TEST-SETUP-CODE',
  String wifiSsid = 'Test Wi-Fi',
  String wifiPassword = 'secret',
  bool commissioneeClean = true,
}) {
  return DeviceTestSetupRequest(
    controller: const ControllerInfoViewModel(
      platform: ControllerPlatform.android,
      deviceModel: 'Pixel test controller',
      osVersion: 'Android 16',
      appBuild: '1.0.0 (1)',
    ),
    setupCode: setupCode,
    wifiSsid: wifiSsid,
    wifiPassword: wifiPassword,
    profile: profile,
    cleanCycle: CleanCycleConfirmations(commissioneeClean: commissioneeClean),
  );
}

RunSession terminalSession({
  TestProfile profile = TestProfile.full,
  String id = testRunId,
}) {
  final results = <DeviceTestId, DeviceTestResult>{
    for (final testId in profile.testIds)
      testId: DeviceTestResult(
        testId: testId,
        status: DeviceTestStatus.passed,
        duration: const Duration(seconds: 1),
      ),
  };
  return RunSession(
    id: id,
    profile: profile,
    testApp: const TestAppMetadata(
      name: 'flutter_matter_device_test_app',
      version: '1.0.0',
      commit: testAppCommit,
    ),
    pluginCommit: testPluginCommit,
    createdAt: testNow,
    updatedAt: testNow,
    phase: RunPhase.completed,
    controller: const ControllerMetadata(
      platform: ControllerPlatform.android,
      deviceModel: 'Pixel test controller',
      osVersion: 'Android 16',
      appBuild: '1.0.0 (1)',
    ),
    commissionee: const CommissioneeMetadata(
      vendorId: 1,
      productId: 2,
      commissioningTransport: CommissioningTransport.ip,
      networkTransport: NetworkTransport.wifi,
    ),
    results: results,
  );
}

RunnerStateSnapshot terminalSnapshot({
  TestProfile profile = TestProfile.full,
  String id = testRunId,
}) {
  return RunnerStateSnapshot.forSession(
    session: terminalSession(profile: profile, id: id),
    at: testNow,
    message: 'Run completed successfully.',
  );
}

Future<String> loadReportSchema() {
  return File('assets/device-test-report.schema.json').readAsString();
}

class ControllerHarness {
  ControllerHarness({
    required this.controller,
    required this.runner,
    required this.prompts,
    required this.bootstrapPort,
    required this.secrets,
    required this.maintenance,
    required this.wifiSetup,
    required this.onboarding,
    required this.artifacts,
    required this.sharing,
  });

  final DeviceTestAppController controller;
  final FakeDeviceTestRunner runner;
  final OperatorPromptBroker prompts;
  final FakeDeviceTestBootstrap bootstrapPort;
  final FakeProvisioningSecrets secrets;
  final FakeRunMaintenance maintenance;
  final FakeWifiSetup wifiSetup;
  final FakeOnboardingPayloadReader onboarding;
  final FakeReportArtifacts artifacts;
  final FakeReportSharing sharing;

  Future<void> close() => controller.close();
}

ControllerHarness buildHarness({
  required String schemaJson,
  DeviceTestAppBootstrap? appBootstrap,
  FakeDeviceTestRunner? runner,
  FakeProvisioningSecrets? secrets,
  FakeRunMaintenance? maintenance,
  FakeWifiSetup? wifiSetup,
}) {
  final fakeRunner = runner ?? FakeDeviceTestRunner();
  final fakeBootstrap = FakeDeviceTestBootstrap(appBootstrap ?? bootstrap());
  final fakeSecrets = secrets ?? FakeProvisioningSecrets();
  final fakeMaintenance = maintenance ?? FakeRunMaintenance();
  final fakeWifiSetup = wifiSetup ?? FakeWifiSetup();
  final fakeOnboarding = FakeOnboardingPayloadReader();
  final fakeArtifacts = FakeReportArtifacts(schemaJson);
  final fakeSharing = FakeReportSharing();
  final prompts = OperatorPromptBroker();
  final controller = DeviceTestAppController(
    runner: fakeRunner,
    prompts: prompts,
    bootstrap: fakeBootstrap,
    secrets: fakeSecrets,
    maintenance: fakeMaintenance,
    wifiSetup: fakeWifiSetup,
    onboardingPayloads: fakeOnboarding,
    reportArtifacts: fakeArtifacts,
    reportSharing: fakeSharing,
    runIdFactory: () => testRunId,
    clock: FixedClock(testNow),
    targetNodeIdFactory: (_) => testTargetNodeId,
  );
  return ControllerHarness(
    controller: controller,
    runner: fakeRunner,
    prompts: prompts,
    bootstrapPort: fakeBootstrap,
    secrets: fakeSecrets,
    maintenance: fakeMaintenance,
    wifiSetup: fakeWifiSetup,
    onboarding: fakeOnboarding,
    artifacts: fakeArtifacts,
    sharing: fakeSharing,
  );
}
