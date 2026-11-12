import 'dart:async';

import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';

final DateTime testNow = DateTime.utc(2026, 11, 11, 12);

class FakeClock implements ClockPort {
  FakeClock({DateTime? initial}) : current = initial ?? testNow;

  DateTime current;

  @override
  DateTime now() => current;

  void advance(Duration duration) {
    current = current.add(duration);
  }
}

class MemoryRunPersistencePort implements RunPersistencePort {
  PersistedRunState? persisted;
  bool cleared = false;
  int saveCount = 0;
  final List<PersistedRunState> savedStates = <PersistedRunState>[];

  @override
  Future<void> clearUnfinished() async {
    cleared = true;
    persisted = null;
  }

  @override
  Future<PersistedRunState?> loadUnfinished() async =>
      cleared ? null : persisted;

  @override
  Future<void> save(PersistedRunState state) async {
    persisted = state;
    cleared = false;
    saveCount++;
    savedStates.add(state);
  }
}

class FakeSecretAccessPort implements SecretAccessPort {
  FakeSecretAccessPort(this.secrets, {this.loadError});

  ProvisioningSecrets? secrets;
  Object? loadError;
  final List<String> loadedRunIds = <String>[];

  @override
  Future<ProvisioningSecrets?> load(String runId) async {
    loadedRunIds.add(runId);
    if (loadError != null) {
      throw loadError!;
    }
    return secrets;
  }

  @override
  Future<void> purge(String runId) async {
    secrets = null;
  }
}

typedef PromptHandler =
    FutureOr<OperatorDecision> Function(OperatorPrompt prompt);

class FakeOperatorPromptPort implements OperatorPromptPort {
  FakeOperatorPromptPort({PromptHandler? handler})
    : handler = handler ?? ((_) => OperatorDecision.confirmed());

  PromptHandler handler;
  final List<OperatorPrompt> prompts = <OperatorPrompt>[];

  @override
  Future<OperatorDecision> request(OperatorPrompt prompt) async {
    prompts.add(prompt);
    return handler(prompt);
  }
}

class FakeCommissioningDiscoveryPort implements CommissioningDiscoveryPort {
  FakeCommissioningDiscoveryPort({
    CommissioningTransport transport = CommissioningTransport.ip,
    BleCommissionee? bleTarget,
    this.failureCode,
    this.handler,
  }) : result = CommissioningDiscoveryResult(
         transport: transport,
         bleTarget: transport == CommissioningTransport.ble
             ? bleTarget ??
                   const BleCommissionee(
                     opaqueId: 'commissionee-opaque',
                     displayName: 'Test commissionee',
                   )
             : null,
       );

  CommissioningDiscoveryResult result;
  CommissioningDiscoveryFailureCode? failureCode;
  Future<CommissioningDiscoveryResult> Function(
    CommissioningDiscoveryRequest request,
  )?
  handler;
  final List<CommissioningDiscoveryRequest> requests =
      <CommissioningDiscoveryRequest>[];

  @override
  Future<CommissioningDiscoveryResult> discover(
    CommissioningDiscoveryRequest request,
  ) async {
    requests.add(request);
    if (handler != null) {
      return handler!(request);
    }
    final code = failureCode;
    if (code != null) {
      throw CommissioningDiscoveryException(code);
    }
    return result;
  }
}

class FakeCommissioningPort implements CommissioningPort {
  FakeCommissioningPort({this.handler});

  Future<CommissioningResult> Function(CommissioningRequest request)? handler;
  final List<CommissioningRequest> requests = <CommissioningRequest>[];

  @override
  Future<CommissioningResult> commission(CommissioningRequest request) async {
    requests.add(request);
    if (handler != null) {
      return handler!(request);
    }
    if (request.setupPinCode != 20202021) {
      return const CommissioningResult(errorCode: 1);
    }
    final network = request.network;
    if (network is WifiProvisioningSecret &&
        network.password.contains('#invalid')) {
      return const CommissioningResult(errorCode: 2);
    }
    return CommissioningResult(
      errorCode: 0,
      nodeId: request.targetNodeId,
      networkTransport: request.network.transport,
    );
  }
}

class FakeOperationalConnectionPort extends OperationalConnectionPort {
  FakeOperationalConnectionPort({
    this.connectValid = true,
    this.reconnectValid = true,
    this.connectHandler,
    this.reconnectHandler,
  });

  bool connectValid;
  bool reconnectValid;
  Future<OperationalConnectionLease> Function({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  })?
  connectHandler;
  Future<OperationalConnectionLease> Function({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  })?
  reconnectHandler;
  int connectCount = 0;
  int reconnectCount = 0;
  int disconnectCount = 0;

  @override
  Future<OperationalConnectionLease> connect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  }) async {
    connectCount++;
    if (connectHandler != null) {
      return connectHandler!(
        identity: identity,
        nodeId: nodeId,
        timeout: timeout,
      );
    }
    return OperationalConnectionLease(
      opaqueId: 'connection-$nodeId',
      nodeId: nodeId,
      isValid: connectValid,
    );
  }

  @override
  Future<OperationalConnectionLease> reconnect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  }) async {
    reconnectCount++;
    if (reconnectHandler != null) {
      return reconnectHandler!(
        identity: identity,
        nodeId: nodeId,
        timeout: timeout,
      );
    }
    return OperationalConnectionLease(
      opaqueId: 'reconnection-$nodeId',
      nodeId: nodeId,
      isValid: reconnectValid,
    );
  }

  @override
  Future<void> disconnect(OperationalConnectionLease connection) async {
    disconnectCount++;
  }
}

class FakeOnOffPort extends OnOffPort {
  FakeOnOffPort({this.currentState = OnOffState.on, this.handler});

  OnOffState currentState;
  Future<OnOffInvocation> Function(
    OperationalConnectionLease connection,
    OnOffCommand command,
    Duration timeout,
  )?
  handler;
  final List<OnOffCommand> invokedCommands = <OnOffCommand>[];
  final StreamController<OnOffState> _updates =
      StreamController<OnOffState>.broadcast();
  int subscribeCount = 0;
  int cancelCount = 0;
  Object? readError;
  Object? subscribeError;

  @override
  Future<OnOffState> readState({
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    if (readError != null) {
      throw readError!;
    }
    return currentState;
  }

  @override
  Future<OnOffInvocation> invoke({
    required OperationalConnectionLease connection,
    required OnOffCommand command,
    required Duration timeout,
  }) async {
    invokedCommands.add(command);
    if (handler != null) {
      return handler!(connection, command, timeout);
    }
    final previous = currentState;
    currentState = switch (command) {
      OnOffCommand.off => OnOffState.off,
      OnOffCommand.on => OnOffState.on,
      OnOffCommand.toggle => currentState.toggled,
    };
    return OnOffInvocation(previousState: previous, currentState: currentState);
  }

  @override
  Future<OnOffSubscription> subscribe({
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    subscribeCount++;
    if (subscribeError != null) {
      throw subscribeError!;
    }
    return OnOffSubscription(
      initialState: currentState,
      updates: _updates.stream,
      cancel: () async {
        cancelCount++;
      },
    );
  }

  void pushUpdate(OnOffState state) {
    currentState = state;
    _updates.add(state);
  }

  Future<void> close() => _updates.close();
}

class FakeNodeLabelPort implements NodeLabelPort {
  FakeNodeLabelPort({this.readHandler, this.writeHandler});

  String? readHandlerResult;
  Future<String> Function()? readHandler;
  Future<void> Function(String value)? writeHandler;
  String? value;
  int readCount = 0;
  int writeCount = 0;

  @override
  Future<String> read({
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    readCount++;
    if (readHandler != null) {
      return readHandler!();
    }
    return readHandlerResult ?? value ?? '';
  }

  @override
  Future<void> write({
    required OperationalConnectionLease connection,
    required String value,
    required Duration timeout,
  }) async {
    writeCount++;
    if (writeHandler != null) {
      await writeHandler!(value);
      return;
    }
    this.value = value;
  }
}

class FakeFabricPort implements FabricPort {
  FakeFabricPort({this.status = const FabricStatus(present: true)});

  FabricStatus status;
  Future<FabricStatus> Function()? inspectHandler;
  int inspectCount = 0;
  int removeCount = 0;
  Object? inspectError;

  @override
  Future<FabricStatus> inspect({
    required ControllerIdentity identity,
    required int nodeId,
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    inspectCount++;
    if (inspectError != null) {
      throw inspectError!;
    }
    if (inspectHandler != null) {
      return inspectHandler!();
    }
    return status;
  }

  @override
  Future<void> remove({
    required ControllerIdentity identity,
    required int nodeId,
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    removeCount++;
    status = const FabricStatus(present: false);
  }
}

class FakeControllerIdentityPort implements ControllerIdentityPort {
  final Map<ControllerIdentityPurpose, ControllerIdentity> identities =
      <ControllerIdentityPurpose, ControllerIdentity>{};
  final List<ControllerIdentityRequest> requests =
      <ControllerIdentityRequest>[];
  int resetCount = 0;
  String opaquePrefix = 'identity';

  @override
  Future<ControllerIdentity> loadOrCreate(
    ControllerIdentityRequest request,
  ) async {
    requests.add(request);
    return identities.putIfAbsent(
      request.purpose,
      () => ControllerIdentity(
        opaqueId: '$opaquePrefix-${request.purpose.wireName}',
        purpose: request.purpose,
      ),
    );
  }

  @override
  Future<void> reset(ControllerIdentityRequest request) async {
    resetCount++;
    identities.remove(request.purpose);
  }
}

class FakeScreenshotPort implements ScreenshotPort {
  final List<ScreenshotRequest> requests = <ScreenshotRequest>[];
  Object? error;

  @override
  Future<void> capture(ScreenshotRequest request) async {
    requests.add(request);
    if (error != null) {
      throw error!;
    }
  }
}

class RecordingHooksPort extends RunnerHooksPort {
  final List<RunnerStateSnapshot> states = <RunnerStateSnapshot>[];
  final List<RunnerEvent> events = <RunnerEvent>[];

  @override
  Future<void> onStateChanged(RunnerStateSnapshot state) async {
    states.add(state);
  }

  @override
  Future<void> onEvent(RunnerEvent event) async {
    events.add(event);
  }
}

class FakeHardware {
  FakeHardware({FakeCommissioningDiscoveryPort? commissioningDiscovery})
    : commissioningDiscovery =
          commissioningDiscovery ?? FakeCommissioningDiscoveryPort();

  final FakeCommissioningDiscoveryPort commissioningDiscovery;
  final FakeCommissioningPort commissioning = FakeCommissioningPort();
  final FakeOperationalConnectionPort operational =
      FakeOperationalConnectionPort();
  final FakeOnOffPort onOff = FakeOnOffPort();
  final FakeNodeLabelPort nodeLabel = FakeNodeLabelPort();
  final FakeFabricPort fabric = FakeFabricPort();
  final FakeControllerIdentityPort identity = FakeControllerIdentityPort();

  TestPorts get ports => TestPorts(
    commissioningDiscovery: commissioningDiscovery,
    commissioning: commissioning,
    operationalConnection: operational,
    onOff: onOff,
    nodeLabel: nodeLabel,
    fabric: fabric,
    controllerIdentity: identity,
  );

  ApplicationPorts applicationPorts({
    required MemoryRunPersistencePort persistence,
    required FakeSecretAccessPort secrets,
    required FakeOperatorPromptPort prompts,
    required FakeClock clock,
    FakeScreenshotPort? screenshot,
    RecordingHooksPort? hooks,
  }) {
    return ApplicationPorts(
      testPorts: ports,
      persistence: persistence,
      secrets: secrets,
      operatorPrompts: prompts,
      clock: clock,
      screenshot: screenshot ?? FakeScreenshotPort(),
      hooks: hooks ?? RecordingHooksPort(),
    );
  }
}

ProvisioningSecrets makeSecrets({ProvisioningNetworkSecret? network}) =>
    ProvisioningSecrets(
      onboardingPayload: 'MT:TEST-ONBOARDING-PAYLOAD',
      setupPinCode: 20202021,
      network:
          network ??
          const WifiProvisioningSecret(ssid: 'matter-lab', password: 'correct'),
    );

const TestTimeouts fastTimeouts = TestTimeouts(
  buildInstall: Duration(milliseconds: 100),
  commissioningDiscovery: Duration(milliseconds: 100),
  commissioning: Duration(milliseconds: 100),
  operationalConnect: Duration(milliseconds: 100),
  onOffInvoke: Duration(milliseconds: 100),
  onOffSubscription: Duration(milliseconds: 100),
  nodeLabelPersistence: Duration(milliseconds: 100),
  appRestart: Duration(milliseconds: 100),
  factoryResetRecommission: Duration(milliseconds: 100),
  invalidSetupPasscode: Duration(milliseconds: 100),
  invalidWifiPassword: Duration(milliseconds: 100),
  removeFabricUi: Duration(milliseconds: 100),
);

RunSession makeSession({
  TestProfile profile = TestProfile.full,
  ControllerMetadata? controller,
  CommissioneeMetadata? commissionee,
}) {
  const controllerMetadata = ControllerMetadata(
    platform: ControllerPlatform.android,
    deviceModel: 'Pixel test',
    osVersion: '16',
    appBuild: '1.0.0+1',
  );
  const commissioneeMetadata = CommissioneeMetadata(
    vendorId: 4660,
    productId: 258,
    networkTransport: NetworkTransport.wifi,
  );
  final now = testNow;
  return RunSession.start(
    id: 'run-001',
    profile: profile,
    testApp: const TestAppMetadata(
      name: 'flutter_matter_device_test_app',
      version: '1.0.0',
      commit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
    ),
    pluginCommit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
    startedAt: now,
    controller: controller ?? controllerMetadata,
    commissionee: commissionee ?? commissioneeMetadata,
  ).withPhase(RunPhase.testing, at: now);
}

RunExecutionContext makeExecution({
  bool withIdentity = true,
  bool withNode = true,
  bool withConnection = true,
}) {
  final execution = RunExecutionContext();
  if (withIdentity) {
    execution.identity = ControllerIdentity(
      opaqueId: 'identity-main',
      purpose: ControllerIdentityPurpose.main,
    );
  }
  if (withNode) {
    execution.nodeId = 1;
  }
  if (withConnection) {
    execution.connection = OperationalConnectionLease(
      opaqueId: 'connection-1',
      nodeId: 1,
      isValid: true,
    );
  }
  return execution;
}

class TestContextHarness {
  TestContextHarness({
    required this.testId,
    TestPorts? ports,
    ProvisioningSecrets? secrets,
    bool withSecrets = true,
    RunExecutionContext? execution,
    RunSession? session,
    this.resumeCheckpoint,
    this.operatorHandler,
    TestTimeouts? timeouts,
  }) : ports = ports ?? FakeHardware().ports,
       secrets = withSecrets ? secrets ?? makeSecrets() : null,
       execution = execution ?? makeExecution(),
       session = session ?? makeSession(),
       timeouts = timeouts ?? fastTimeouts;

  final DeviceTestId testId;
  final TestPorts ports;
  final ProvisioningSecrets? secrets;
  final RunExecutionContext? execution;
  final RunSession? session;
  final AppRestartCheckpoint? resumeCheckpoint;
  final PromptHandler? operatorHandler;
  final TestTimeouts timeouts;
  final List<OperatorPrompt> prompts = <OperatorPrompt>[];
  final List<AppRestartCheckpoint> savedCheckpoints = <AppRestartCheckpoint>[];
  AppRestartCheckpoint? clearedCheckpoint;
  int executionPersistCount = 0;

  TestContext build() {
    final handler = operatorHandler ?? ((_) => OperatorDecision.confirmed());
    return TestContext(
      session: session!,
      testId: testId,
      ports: ports,
      execution: execution!,
      timeouts: timeouts,
      targetNodeId: 1,
      secrets: secrets,
      resumeCheckpoint: resumeCheckpoint,
      onExecutionChanged: () async {
        executionPersistCount++;
      },
      onPrompt: (prompt) async {
        prompts.add(prompt);
        return handler(prompt);
      },
      onSaveAppRestartCheckpoint: (checkpoint) async {
        savedCheckpoints.add(checkpoint);
      },
      onClearAppRestartCheckpoint: () async {
        clearedCheckpoint = resumeCheckpoint;
      },
    );
  }
}
