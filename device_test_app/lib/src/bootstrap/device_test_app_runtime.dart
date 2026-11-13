import 'dart:async';

import 'package:flutter/widgets.dart';

import '../agent/agent.dart';
import '../app/app.dart';
import '../application/application.dart';
import '../domain/domain.dart';
import '../infrastructure/adapters/adapters.dart';
import '../infrastructure/platform/build_metadata.dart';
import '../infrastructure/platform/platform_info_service.dart';
import '../infrastructure/platform/run_id_generator.dart';
import '../infrastructure/reporting/report_file_repository.dart';
import '../infrastructure/storage/file_run_persistence.dart';
import '../infrastructure/storage/provisioning_secret_store.dart';
import '../infrastructure/storage/run_directory.dart';
import '../infrastructure/storage/secure_secret_store.dart';
import '../infrastructure/storage/wifi_credential_cache.dart';
import '../infrastructure/wifi/wifi.dart';
import '../presentation/presentation.dart';
import 'agent_bridge_projection.dart';
import 'live_device_test_agent_host.dart';
import 'widget_screenshot_capture.dart';

/// Complete production object graph for the dedicated device-test app.
class DeviceTestAppRuntime {
  DeviceTestAppRuntime._({
    required this.controller,
    required this.screenshotBoundaryKey,
    required DeviceTestRunPort runner,
    required MatterControllerAdapter matterAdapter,
    required FlutterMatterControllerRuntimeProvider runtimeProvider,
  }) : _runner = runner,
       _matterAdapter = matterAdapter,
       _runtimeProvider = runtimeProvider;

  static const String _webSocketEndpointDefine = String.fromEnvironment(
    'AGENT_WS_URL',
  );
  static const AgentBridgeProjection _projection = AgentBridgeProjection();
  static const List<String> agentCapabilities = <String>[
    'state',
    'event',
    'command',
    ...AgentCommandNames.all,
  ];

  final DeviceTestAppController controller;
  final GlobalKey screenshotBoundaryKey;
  final DeviceTestRunPort _runner;
  final MatterControllerAdapter _matterAdapter;
  final FlutterMatterControllerRuntimeProvider _runtimeProvider;
  AgentBridgeClient? _agentBridge;
  StreamSubscription<DeviceTestUiState>? _stateSubscription;
  StreamSubscription<RunnerEvent>? _eventSubscription;
  bool _closed = false;

  static Future<DeviceTestAppRuntime> create() async {
    final platformInfo = await PlatformInfoService().load();
    final controllerPlatform = ControllerPlatform.parse(platformInfo.platform);
    final runDirectory = RunDirectory();
    final secureSecrets = ProvisioningSecretStore(
      secureStore: SecureSecretStore(),
    );
    final promptBroker = OperatorPromptBroker();
    final runtimeProvider = FlutterMatterControllerRuntimeProvider();
    final matterAdapter = MatterControllerAdapter(
      runtimeProvider: runtimeProvider,
      platform: controllerPlatform,
    );
    final provisioningSecrets = LiveProvisioningSecrets(
      secureSecrets,
      runDirectory,
    );
    final wifiSetup = LiveWifiSetup(
      ssidReader: WifiSsidReader(source: NetworkInfoWifiSsidSource()),
      cache: WifiCredentialCache(secureStore: SecureSecretStore()),
    );
    final maintenance = LiveRunMaintenance(
      secrets: provisioningSecrets,
      controllerIdentities: matterAdapter,
      persistence: FileRunPersistence(runDirectory: runDirectory),
      platform: controllerPlatform,
    );
    final coordinator = RunCoordinator(
      ports: ApplicationPorts(
        testPorts: TestPorts(
          commissioning: matterAdapter,
          operationalConnection: matterAdapter,
          onOff: matterAdapter,
          nodeLabel: matterAdapter,
          fabric: matterAdapter,
          controllerIdentity: matterAdapter,
        ),
        persistence: FileRunPersistence(runDirectory: runDirectory),
        secrets: secureSecrets,
        operatorPrompts: promptBroker,
        clock: const SystemClockPort(),
      ),
    );
    final runner = LiveDeviceTestRunner(coordinator);
    final appController = DeviceTestAppController(
      runner: runner,
      prompts: promptBroker,
      bootstrap: LiveDeviceTestBootstrap(
        platformInfo: PlatformInfoService(),
        buildMetadata: BuildMetadata.current,
      ),
      secrets: provisioningSecrets,
      maintenance: maintenance,
      wifiSetup: wifiSetup,
      onboardingPayloads: MethodChannelOnboardingPayloadReader(),
      reportArtifacts: LiveDeviceTestReportArtifacts(
        ReportFileRepository(runDirectory: runDirectory),
      ),
      reportSharing: SharePlusDeviceTestReportSharer(),
      runIdFactory: const RunIdGenerator().next,
    );
    await appController.initialize();

    final screenshotBoundaryKey = GlobalKey();
    final runtime = DeviceTestAppRuntime._(
      controller: appController,
      screenshotBoundaryKey: screenshotBoundaryKey,
      runner: runner,
      matterAdapter: matterAdapter,
      runtimeProvider: runtimeProvider,
    );
    try {
      await runtime._startAgentBridgeIfConfigured(
        platformInfo: platformInfo,
        screenshotCapture: WidgetScreenshotCapture(
          boundaryKey: screenshotBoundaryKey,
        ),
      );
      return runtime;
    } on Object {
      await runtime.close();
      rethrow;
    }
  }

  Future<void> _startAgentBridgeIfConfigured({
    required PlatformInfo platformInfo,
    required WidgetScreenshotCapture screenshotCapture,
  }) async {
    final endpointText = _webSocketEndpointDefine.trim();
    if (endpointText.isEmpty) {
      return;
    }
    final endpoint = Uri.tryParse(endpointText);
    if (endpoint == null ||
        (endpoint.scheme != 'ws' && endpoint.scheme != 'wss') ||
        endpoint.host.isEmpty) {
      throw StateError('AGENT_WS_URL must be a valid ws:// or wss:// URL.');
    }

    debugPrint('Agent bridge connecting to ${endpoint.host}:${endpoint.port}.');

    final host = LiveDeviceTestAgentHost(
      controller: controller,
      runner: _runner,
      screenshotCapture: screenshotCapture,
    );
    final commandHandler = DeviceTestAgentCommandHandler(host: host);
    final metadata = BuildMetadata.current;
    final bridge = AgentBridgeClient(
      endpoint: endpoint,
      hello: AgentHelloPayload(
        instanceId: newAgentId(prefix: 'instance'),
        appName: 'flutter_matter_device_test_app',
        appVersion: platformInfo.appVersion,
        appBuild: platformInfo.appBuild,
        appCommit: metadata.testAppCommit,
        pluginCommit: metadata.pluginCommit,
        controllerPlatform: platformInfo.platform,
        deviceModel: platformInfo.deviceModel,
        osVersion: platformInfo.osVersion,
        capabilities: agentCapabilities,
      ),
      onCommand: commandHandler.handle,
    );
    _agentBridge = bridge;
    _stateSubscription = controller.stateStream.listen((state) {
      bridge.sendState(_projection.projectState(state));
    });
    _eventSubscription = controller.eventStream.listen((event) {
      bridge.sendEvent(_projection.projectEvent(event));
    });
    bridge.sendState(_projection.projectState(controller.state));
    await bridge.start();
  }

  Future<void> close() async {
    if (_closed) {
      return;
    }
    _closed = true;
    Object? firstError;
    StackTrace? firstStackTrace;

    Future<void> closeStep(Future<void> Function() action) async {
      try {
        await action();
      } on Object catch (error, stackTrace) {
        firstError ??= error;
        firstStackTrace ??= stackTrace;
      }
    }

    await closeStep(() async {
      await _stateSubscription?.cancel();
    });
    await closeStep(() async {
      await _eventSubscription?.cancel();
    });
    await closeStep(() async {
      await _agentBridge?.stop();
    });
    await closeStep(controller.close);
    await closeStep(_matterAdapter.close);
    await closeStep(_runtimeProvider.close);

    if (firstError != null) {
      Error.throwWithStackTrace(firstError!, firstStackTrace!);
    }
  }
}
