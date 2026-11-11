import 'dart:async';
import 'dart:typed_data';

import '../domain/domain.dart';
import 'operator_prompt.dart';
import 'runner_state.dart';

/// A hardware-independent request to discover the configured commissionee.
class BleDiscoveryRequest {
  const BleDiscoveryRequest({required this.timeout, this.onboardingPayload});

  final Duration timeout;
  final String? onboardingPayload;
}

class BleCommissionee {
  const BleCommissionee({required this.opaqueId, required this.displayName})
    : assert(opaqueId != ''),
      assert(displayName != '');

  /// An adapter-owned identifier. It must not be logged as a BLE address.
  final String opaqueId;
  final String displayName;
}

class BleDiscoveryResult {
  const BleDiscoveryResult({required this.candidateCount, this.target})
    : assert(candidateCount >= 0);

  final int candidateCount;
  final BleCommissionee? target;
}

enum BleDiscoveryFailureCode {
  bluetoothUnavailable,
  permissionDenied,
  adapterUnavailable,
  timeout,
  other,
}

extension BleDiscoveryFailureCodeWire on BleDiscoveryFailureCode {
  String get wireName => switch (this) {
    BleDiscoveryFailureCode.bluetoothUnavailable => 'bluetooth_unavailable',
    BleDiscoveryFailureCode.permissionDenied => 'permission_denied',
    BleDiscoveryFailureCode.adapterUnavailable => 'adapter_unavailable',
    BleDiscoveryFailureCode.timeout => 'timeout',
    BleDiscoveryFailureCode.other => 'other',
  };
}

class BleDiscoveryException implements Exception {
  BleDiscoveryException(this.code);

  final BleDiscoveryFailureCode code;

  @override
  String toString() => 'BleDiscoveryException(${code.wireName})';
}

abstract interface class BleDiscoveryPort {
  Future<BleDiscoveryResult> discover(BleDiscoveryRequest request);
}

/// Controller identity material stays behind the adapter. The application only
/// sees an opaque identity handle.
enum ControllerIdentityPurpose {
  main,
  invalidSetupPasscode,
  invalidWifiPassword,
  removeFabricUi,
}

extension ControllerIdentityPurposeWire on ControllerIdentityPurpose {
  String get wireName => switch (this) {
    ControllerIdentityPurpose.main => 'main',
    ControllerIdentityPurpose.invalidSetupPasscode => 'invalid_setup_passcode',
    ControllerIdentityPurpose.invalidWifiPassword => 'invalid_wifi_password',
    ControllerIdentityPurpose.removeFabricUi => 'remove_fabric_ui',
  };

  static ControllerIdentityPurpose parse(Object? value) => switch (value) {
    'main' => ControllerIdentityPurpose.main,
    'invalid_setup_passcode' => ControllerIdentityPurpose.invalidSetupPasscode,
    'invalid_wifi_password' => ControllerIdentityPurpose.invalidWifiPassword,
    'remove_fabric_ui' => ControllerIdentityPurpose.removeFabricUi,
    _ => throw FormatException('Unknown controller identity purpose: $value'),
  };
}

class ControllerIdentity {
  ControllerIdentity({required this.opaqueId, required this.purpose}) {
    if (opaqueId.trim().isEmpty) {
      throw ArgumentError.value(opaqueId, 'opaqueId', 'Must not be empty');
    }
  }

  final String opaqueId;
  final ControllerIdentityPurpose purpose;
}

class ControllerIdentityRequest {
  const ControllerIdentityRequest({
    required this.runId,
    required this.purpose,
    required this.platform,
  });

  final String runId;
  final ControllerIdentityPurpose purpose;
  final ControllerPlatform platform;
}

abstract interface class ControllerIdentityPort {
  Future<ControllerIdentity> loadOrCreate(ControllerIdentityRequest request);

  Future<void> reset(ControllerIdentityRequest request);
}

sealed class ProvisioningNetworkSecret {
  const ProvisioningNetworkSecret();

  NetworkTransport get transport;
}

class WifiProvisioningSecret extends ProvisioningNetworkSecret {
  const WifiProvisioningSecret({required this.ssid, required this.password});

  final String ssid;
  final String password;

  @override
  NetworkTransport get transport => NetworkTransport.wifi;

  @override
  String toString() => 'WifiProvisioningSecret(redacted)';
}

class ThreadProvisioningSecret extends ProvisioningNetworkSecret {
  ThreadProvisioningSecret({required List<int> operationalDataset})
    : operationalDataset = Uint8List.fromList(operationalDataset) {
    if (operationalDataset.isEmpty) {
      throw ArgumentError.value(
        operationalDataset,
        'operationalDataset',
        'Must not be empty',
      );
    }
  }

  final Uint8List operationalDataset;

  @override
  NetworkTransport get transport => NetworkTransport.thread;

  @override
  String toString() => 'ThreadProvisioningSecret(redacted)';
}

/// Secrets used by a run. This object is never persisted or serialized.
class ProvisioningSecrets {
  ProvisioningSecrets({
    required this.onboardingPayload,
    required this.setupPinCode,
    required this.network,
    this.commissioningTransport = CommissioningTransport.ip,
    this.supportsOnNetworkDiscovery = false,
  }) {
    if (onboardingPayload.trim().isEmpty) {
      throw ArgumentError.value(
        onboardingPayload,
        'onboardingPayload',
        'Must not be empty',
      );
    }
    if (setupPinCode < 1 || setupPinCode > 99999998) {
      throw ArgumentError.value(
        setupPinCode,
        'setupPinCode',
        'Must be a valid Matter setup passcode',
      );
    }
  }

  final String onboardingPayload;
  final int setupPinCode;
  final ProvisioningNetworkSecret network;
  final CommissioningTransport commissioningTransport;
  final bool supportsOnNetworkDiscovery;

  NetworkTransport get transport => network.transport;

  int get invalidSetupPinCode {
    final candidate = setupPinCode + 1;
    return candidate > 99999998 ? 1 : candidate;
  }

  ProvisioningSecrets withInvalidWifiPassword() {
    final networkSecret = network;
    if (networkSecret is! WifiProvisioningSecret) {
      throw StateError('Wi-Fi secrets are not configured');
    }
    return ProvisioningSecrets(
      onboardingPayload: onboardingPayload,
      setupPinCode: setupPinCode,
      network: WifiProvisioningSecret(
        ssid: networkSecret.ssid,
        password: '${networkSecret.password}#invalid',
      ),
      commissioningTransport: commissioningTransport,
      supportsOnNetworkDiscovery: supportsOnNetworkDiscovery,
    );
  }

  @override
  String toString() => 'ProvisioningSecrets(redacted)';
}

abstract interface class SecretAccessPort {
  Future<ProvisioningSecrets?> load(String runId);

  Future<void> purge(String runId);
}

class CommissioningRequest {
  const CommissioningRequest({
    this.target,
    required this.identity,
    required this.targetNodeId,
    required this.onboardingPayload,
    required this.setupPinCode,
    required this.network,
    this.commissioningTransport = CommissioningTransport.ip,
    required this.timeout,
  });

  final BleCommissionee? target;
  final ControllerIdentity identity;
  final int targetNodeId;
  final String onboardingPayload;
  final int setupPinCode;
  final ProvisioningNetworkSecret network;
  final CommissioningTransport commissioningTransport;
  final Duration timeout;
}

class CommissioningResult {
  const CommissioningResult({
    required this.errorCode,
    this.nodeId,
    this.networkTransport,
  });

  final int errorCode;
  final int? nodeId;
  final NetworkTransport? networkTransport;

  bool get succeeded => errorCode == 0;
}

enum CommissioningFailureCode {
  invalidSetupCode,
  invalidCredentials,
  bluetoothUnavailable,
  permissionDenied,
  timeout,
  alreadyCommissioned,
  commissioningFailed,
  other,
}

extension CommissioningFailureCodeWire on CommissioningFailureCode {
  String get wireName => switch (this) {
    CommissioningFailureCode.invalidSetupCode => 'invalid_setup_code',
    CommissioningFailureCode.invalidCredentials => 'invalid_credentials',
    CommissioningFailureCode.bluetoothUnavailable => 'bluetooth_unavailable',
    CommissioningFailureCode.permissionDenied => 'permission_denied',
    CommissioningFailureCode.timeout => 'timeout',
    CommissioningFailureCode.alreadyCommissioned => 'already_commissioned',
    CommissioningFailureCode.commissioningFailed => 'commissioning_failed',
    CommissioningFailureCode.other => 'other',
  };
}

class CommissioningException implements Exception {
  CommissioningException(this.code, {this.errorCode});

  final CommissioningFailureCode code;
  final int? errorCode;

  @override
  String toString() =>
      'CommissioningException(${code.wireName}, errorCode: $errorCode)';
}

abstract interface class CommissioningPort {
  Future<CommissioningResult> commission(CommissioningRequest request);
}

class OperationalConnectionLease {
  OperationalConnectionLease({
    required this.opaqueId,
    required this.nodeId,
    required this.isValid,
  }) {
    if (opaqueId.trim().isEmpty) {
      throw ArgumentError.value(opaqueId, 'opaqueId', 'Must not be empty');
    }
    if (nodeId < 1) {
      throw ArgumentError.value(nodeId, 'nodeId', 'Must be positive');
    }
  }

  final String opaqueId;
  final int nodeId;
  final bool isValid;
}

abstract class OperationalConnectionPort {
  Future<OperationalConnectionLease> connect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  });

  Future<OperationalConnectionLease> reconnect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  }) => connect(identity: identity, nodeId: nodeId, timeout: timeout);

  Future<void> disconnect(OperationalConnectionLease connection) async {}
}

enum OnOffState {
  off('off'),
  on('on');

  const OnOffState(this.wireName);

  final String wireName;

  OnOffState get toggled =>
      this == OnOffState.on ? OnOffState.off : OnOffState.on;

  static OnOffState parse(Object? value) => switch (value) {
    'off' => OnOffState.off,
    'on' => OnOffState.on,
    _ => throw FormatException('Unknown OnOff state: $value'),
  };
}

enum OnOffCommand {
  off('off'),
  on('on'),
  toggle('toggle');

  const OnOffCommand(this.wireName);

  final String wireName;
}

class OnOffInvocation {
  const OnOffInvocation({
    required this.previousState,
    required this.currentState,
  });

  final OnOffState previousState;
  final OnOffState currentState;

  bool get changed => previousState != currentState;
}

class OnOffSubscription {
  const OnOffSubscription({
    required this.initialState,
    required this.updates,
    required this.cancel,
  });

  final OnOffState initialState;
  final Stream<OnOffState> updates;
  final Future<void> Function() cancel;
}

enum OnOffFailureCode {
  notConnected,
  invokeRejected,
  readFailed,
  subscribeFailed,
  timeout,
  other,
}

extension OnOffFailureCodeWire on OnOffFailureCode {
  String get wireName => switch (this) {
    OnOffFailureCode.notConnected => 'not_connected',
    OnOffFailureCode.invokeRejected => 'invoke_rejected',
    OnOffFailureCode.readFailed => 'read_failed',
    OnOffFailureCode.subscribeFailed => 'subscribe_failed',
    OnOffFailureCode.timeout => 'timeout',
    OnOffFailureCode.other => 'other',
  };
}

class OnOffException implements Exception {
  OnOffException(this.code);

  final OnOffFailureCode code;

  @override
  String toString() => 'OnOffException(${code.wireName})';
}

abstract class OnOffPort {
  Future<OnOffState> readState({
    required OperationalConnectionLease connection,
    required Duration timeout,
  });

  Future<OnOffInvocation> invoke({
    required OperationalConnectionLease connection,
    required OnOffCommand command,
    required Duration timeout,
  });

  Future<OnOffSubscription> subscribe({
    required OperationalConnectionLease connection,
    required Duration timeout,
  });
}

enum NodeLabelFailureCode {
  notConnected,
  readFailed,
  writeFailed,
  timeout,
  other,
}

extension NodeLabelFailureCodeWire on NodeLabelFailureCode {
  String get wireName => switch (this) {
    NodeLabelFailureCode.notConnected => 'not_connected',
    NodeLabelFailureCode.readFailed => 'read_failed',
    NodeLabelFailureCode.writeFailed => 'write_failed',
    NodeLabelFailureCode.timeout => 'timeout',
    NodeLabelFailureCode.other => 'other',
  };
}

class NodeLabelException implements Exception {
  NodeLabelException(this.code);

  final NodeLabelFailureCode code;

  @override
  String toString() => 'NodeLabelException(${code.wireName})';
}

abstract interface class NodeLabelPort {
  Future<String> read({
    required OperationalConnectionLease connection,
    required Duration timeout,
  });

  Future<void> write({
    required OperationalConnectionLease connection,
    required String value,
    required Duration timeout,
  });
}

class FabricStatus {
  const FabricStatus({required this.present, this.fabricIndex});

  final bool present;
  final int? fabricIndex;
}

enum FabricFailureCode {
  notConnected,
  inspectFailed,
  removeFailed,
  timeout,
  other,
}

extension FabricFailureCodeWire on FabricFailureCode {
  String get wireName => switch (this) {
    FabricFailureCode.notConnected => 'not_connected',
    FabricFailureCode.inspectFailed => 'inspect_failed',
    FabricFailureCode.removeFailed => 'remove_failed',
    FabricFailureCode.timeout => 'timeout',
    FabricFailureCode.other => 'other',
  };
}

class FabricException implements Exception {
  FabricException(this.code);

  final FabricFailureCode code;

  @override
  String toString() => 'FabricException(${code.wireName})';
}

abstract interface class FabricPort {
  Future<FabricStatus> inspect({
    required ControllerIdentity identity,
    required int nodeId,
    required OperationalConnectionLease connection,
    required Duration timeout,
  });

  Future<void> remove({
    required ControllerIdentity identity,
    required int nodeId,
    required OperationalConnectionLease connection,
    required Duration timeout,
  });
}

class ScreenshotRequest {
  const ScreenshotRequest({
    required this.runId,
    required this.testId,
    required this.label,
  });

  final String runId;
  final DeviceTestId testId;
  final String label;
}

abstract interface class ScreenshotPort {
  Future<void> capture(ScreenshotRequest request);
}

class NoopScreenshotPort implements ScreenshotPort {
  const NoopScreenshotPort();

  @override
  Future<void> capture(ScreenshotRequest request) async {}
}

abstract interface class ClockPort {
  DateTime now();
}

class SystemClockPort implements ClockPort {
  const SystemClockPort();

  @override
  DateTime now() => DateTime.now();
}

abstract interface class OperatorPromptPort {
  Future<OperatorDecision> request(OperatorPrompt prompt);
}

enum AppRestartCheckpointStage { awaitingRestart, awaitingReconnect }

extension AppRestartCheckpointStageWire on AppRestartCheckpointStage {
  String get wireName => switch (this) {
    AppRestartCheckpointStage.awaitingRestart => 'awaiting_restart',
    AppRestartCheckpointStage.awaitingReconnect => 'awaiting_reconnect',
  };

  static AppRestartCheckpointStage parse(Object? value) => switch (value) {
    'awaiting_restart' => AppRestartCheckpointStage.awaitingRestart,
    'awaiting_reconnect' => AppRestartCheckpointStage.awaitingReconnect,
    _ => throw FormatException('Unknown app restart checkpoint stage: $value'),
  };
}

class AppRestartCheckpoint {
  const AppRestartCheckpoint({
    required this.stage,
    required this.identityOpaqueId,
    required this.nodeId,
  });

  final AppRestartCheckpointStage stage;
  final String identityOpaqueId;
  final int nodeId;

  Map<String, Object?> toJson() => <String, Object?>{
    'stage': stage.wireName,
    'identity_opaque_id': identityOpaqueId,
    'node_id': nodeId,
  };

  factory AppRestartCheckpoint.fromJson(Map<String, dynamic> json) =>
      AppRestartCheckpoint(
        stage: AppRestartCheckpointStageWire.parse(json['stage']),
        identityOpaqueId: _requiredString(json, 'identity_opaque_id'),
        nodeId: _requiredInt(json, 'node_id'),
      );
}

class RunExecutionContextSnapshot {
  const RunExecutionContextSnapshot({
    this.identityOpaqueId,
    this.identityPurpose,
    this.nodeId,
    this.networkTransport,
    this.lastOnOffState,
  });

  final String? identityOpaqueId;
  final ControllerIdentityPurpose? identityPurpose;
  final int? nodeId;
  final NetworkTransport? networkTransport;
  final OnOffState? lastOnOffState;

  Map<String, Object?> toJson() => <String, Object?>{
    if (identityOpaqueId != null) 'identity_opaque_id': identityOpaqueId,
    if (identityPurpose != null) 'identity_purpose': identityPurpose!.wireName,
    if (nodeId != null) 'node_id': nodeId,
    if (networkTransport != null)
      'network_transport': networkTransport!.wireName,
    if (lastOnOffState != null) 'last_onoff_state': lastOnOffState!.wireName,
  };

  factory RunExecutionContextSnapshot.fromJson(Map<String, dynamic> json) {
    final identityOpaqueId = json['identity_opaque_id'];
    final identityPurpose = json['identity_purpose'];
    final nodeId = json['node_id'];
    final networkTransport = json['network_transport'];
    final lastOnOffState = json['last_onoff_state'];
    if (identityOpaqueId != null && identityOpaqueId is! String) {
      throw const FormatException('identity_opaque_id must be a string');
    }
    if (identityPurpose != null && identityPurpose is! String) {
      throw const FormatException('identity_purpose must be a string');
    }
    if (nodeId != null && nodeId is! int) {
      throw const FormatException('node_id must be an integer');
    }
    if (networkTransport != null && networkTransport is! String) {
      throw const FormatException('network_transport must be a string');
    }
    if (lastOnOffState != null && lastOnOffState is! String) {
      throw const FormatException('last_onoff_state must be a string');
    }
    return RunExecutionContextSnapshot(
      identityOpaqueId: identityOpaqueId as String?,
      identityPurpose: identityPurpose == null
          ? null
          : ControllerIdentityPurposeWire.parse(identityPurpose),
      nodeId: nodeId as int?,
      networkTransport: networkTransport == null
          ? null
          : NetworkTransport.parse(networkTransport as String),
      lastOnOffState: lastOnOffState == null
          ? null
          : OnOffState.parse(lastOnOffState),
    );
  }
}

class ActiveOperatorPromptSnapshot {
  const ActiveOperatorPromptSnapshot({
    required this.testId,
    required this.prompt,
  });

  final DeviceTestId testId;
  final OperatorPrompt prompt;

  Map<String, Object?> toJson() => <String, Object?>{
    'test_id': testId.wireName,
    'prompt': prompt.toJson(),
  };

  factory ActiveOperatorPromptSnapshot.fromJson(Map<String, dynamic> json) =>
      ActiveOperatorPromptSnapshot(
        testId: DeviceTestId.parse(_requiredString(json, 'test_id')),
        prompt: OperatorPrompt.fromJson(
          _asMap(json['prompt'], 'active_prompt.prompt'),
        ),
      );
}

/// Durable application state. Secrets and live connection handles are absent.
class PersistedRunState {
  const PersistedRunState({
    required this.session,
    required this.execution,
    required this.targetNodeId,
    this.appRestartCheckpoint,
    this.activePrompt,
  });

  final RunSession session;
  final RunExecutionContextSnapshot execution;
  final int targetNodeId;
  final AppRestartCheckpoint? appRestartCheckpoint;
  final ActiveOperatorPromptSnapshot? activePrompt;

  PersistedRunState copyWith({
    RunSession? session,
    RunExecutionContextSnapshot? execution,
    int? targetNodeId,
    AppRestartCheckpoint? appRestartCheckpoint,
    bool clearAppRestartCheckpoint = false,
    ActiveOperatorPromptSnapshot? activePrompt,
    bool clearActivePrompt = false,
  }) {
    return PersistedRunState(
      session: session ?? this.session,
      execution: execution ?? this.execution,
      targetNodeId: targetNodeId ?? this.targetNodeId,
      appRestartCheckpoint: clearAppRestartCheckpoint
          ? null
          : appRestartCheckpoint ?? this.appRestartCheckpoint,
      activePrompt: clearActivePrompt
          ? null
          : activePrompt ?? this.activePrompt,
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'snapshot_version': 1,
    'session': session.toJson(),
    'execution': execution.toJson(),
    'target_node_id': targetNodeId,
    if (appRestartCheckpoint != null)
      'app_restart_checkpoint': appRestartCheckpoint!.toJson(),
    if (activePrompt != null) 'active_prompt': activePrompt!.toJson(),
  };

  factory PersistedRunState.fromJson(Map<String, dynamic> json) {
    final version = json['snapshot_version'];
    if (version != 1) {
      throw FormatException('Unsupported persisted run version: $version');
    }
    final checkpointJson = json['app_restart_checkpoint'];
    final promptJson = json['active_prompt'];
    return PersistedRunState(
      session: RunSession.fromJson(_asMap(json['session'], 'session')),
      execution: RunExecutionContextSnapshot.fromJson(
        _asMap(json['execution'], 'execution'),
      ),
      targetNodeId: _requiredInt(json, 'target_node_id'),
      appRestartCheckpoint: checkpointJson == null
          ? null
          : AppRestartCheckpoint.fromJson(
              _asMap(checkpointJson, 'app_restart_checkpoint'),
            ),
      activePrompt: promptJson == null
          ? null
          : ActiveOperatorPromptSnapshot.fromJson(
              _asMap(promptJson, 'active_prompt'),
            ),
    );
  }
}

abstract interface class RunPersistencePort {
  Future<PersistedRunState?> loadUnfinished();

  Future<void> save(PersistedRunState state);

  Future<void> clearUnfinished();
}

/// Hardware-facing ports used directly by test cases.
class TestPorts {
  const TestPorts({
    required this.bleDiscovery,
    required this.commissioning,
    required this.operationalConnection,
    required this.onOff,
    required this.nodeLabel,
    required this.fabric,
    required this.controllerIdentity,
  });

  final BleDiscoveryPort bleDiscovery;
  final CommissioningPort commissioning;
  final OperationalConnectionPort operationalConnection;
  final OnOffPort onOff;
  final NodeLabelPort nodeLabel;
  final FabricPort fabric;
  final ControllerIdentityPort controllerIdentity;
}

/// Complete dependency set for the application runner.
class ApplicationPorts {
  const ApplicationPorts({
    required this.testPorts,
    required this.persistence,
    required this.secrets,
    required this.operatorPrompts,
    required this.clock,
    this.screenshot = const NoopScreenshotPort(),
    this.hooks = const NoopRunnerHooksPort(),
  });

  final TestPorts testPorts;
  final RunPersistencePort persistence;
  final SecretAccessPort secrets;
  final OperatorPromptPort operatorPrompts;
  final ClockPort clock;
  final ScreenshotPort screenshot;
  final RunnerHooksPort hooks;
}

Map<String, dynamic> _asMap(Object? value, String name) {
  if (value is! Map<String, dynamic>) {
    throw FormatException('$name must be an object');
  }
  return value;
}

String _requiredString(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! String) {
    throw FormatException('$key must be a string');
  }
  return value;
}

int _requiredInt(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! int) {
    throw FormatException('$key must be an integer');
  }
  return value;
}
