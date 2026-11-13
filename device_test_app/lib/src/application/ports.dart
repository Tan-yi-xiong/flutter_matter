import 'dart:async';
import 'dart:typed_data';

import '../domain/domain.dart';
import 'matter_manual_pairing_code.dart';
import 'operator_prompt.dart';
import 'runner_state.dart';

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

  /// Disposes the live controller runtime for [request.purpose] while keeping
  /// the persisted credentials, then rebuilds the runtime from those stored
  /// credentials. Returns the restored identity.
  Future<ControllerIdentity> restart(ControllerIdentityRequest request);

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

/// Secrets used by a run. Persist them only in platform-secure storage.
class ProvisioningSecrets {
  ProvisioningSecrets({
    required this.onboardingPayload,
    required this.invalidSetupOnboardingPayload,
    required this.setupPinCode,
    required this.network,
    this.setupDiscriminator,
    this.onNetworkEndpoint,
  }) {
    if (onboardingPayload.trim().isEmpty) {
      throw ArgumentError.value(
        onboardingPayload,
        'onboardingPayload',
        'Must not be empty',
      );
    }
    if (invalidSetupOnboardingPayload.trim().isEmpty) {
      throw ArgumentError.value(
        invalidSetupOnboardingPayload,
        'invalidSetupOnboardingPayload',
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
    final discriminator = setupDiscriminator;
    if (discriminator != null &&
        (discriminator < 0 || discriminator > 0x0fff)) {
      throw ArgumentError.value(
        discriminator,
        'setupDiscriminator',
        'Must be between 0 and 4095',
      );
    }
  }

  final String onboardingPayload;
  final String invalidSetupOnboardingPayload;
  final int setupPinCode;
  final ProvisioningNetworkSecret network;
  final int? setupDiscriminator;
  final OnNetworkCommissioningEndpoint? onNetworkEndpoint;

  NetworkTransport get transport => network.transport;

  int get invalidSetupPinCode => invalidMatterSetupPinCodeFor(setupPinCode);

  ProvisioningSecrets withInvalidWifiPassword() {
    final networkSecret = network;
    if (networkSecret is! WifiProvisioningSecret) {
      throw StateError('Wi-Fi secrets are not configured');
    }
    return ProvisioningSecrets(
      onboardingPayload: onboardingPayload,
      invalidSetupOnboardingPayload: invalidSetupOnboardingPayload,
      setupPinCode: setupPinCode,
      setupDiscriminator: setupDiscriminator,
      onNetworkEndpoint: onNetworkEndpoint,
      network: WifiProvisioningSecret(
        ssid: networkSecret.ssid,
        password: '${networkSecret.password}#invalid',
      ),
    );
  }

  @override
  String toString() => 'ProvisioningSecrets(redacted)';
}

/// An already reachable commissionee endpoint used for on-network PASE.
class OnNetworkCommissioningEndpoint {
  OnNetworkCommissioningEndpoint({required this.address, required this.port}) {
    if (address.trim().isEmpty) {
      throw ArgumentError.value(address, 'address', 'Must not be empty');
    }
    if (port < 1 || port > 65535) {
      throw ArgumentError.value(port, 'port', 'Must be between 1 and 65535');
    }
  }

  final String address;
  final int port;
}

abstract interface class SecretAccessPort {
  Future<ProvisioningSecrets?> load(String runId);

  Future<void> purge(String runId);
}

class CommissioningRequest {
  const CommissioningRequest({
    required this.identity,
    required this.targetNodeId,
    required this.onboardingPayload,
    required this.setupPinCode,
    required this.network,
    this.setupDiscriminator,
    this.onNetworkEndpoint,
    required this.timeout,
  });

  final ControllerIdentity identity;
  final int targetNodeId;
  final String onboardingPayload;
  final int setupPinCode;
  final ProvisioningNetworkSecret network;
  final int? setupDiscriminator;
  final OnNetworkCommissioningEndpoint? onNetworkEndpoint;
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

/// Cleans up leftover run state files from interrupted Runs.
///
/// Runs are intentionally one-shot: an interrupted Run is discarded, never
/// resumed, so persistence only exists to remove stale artifacts.
abstract interface class RunPersistencePort {
  Future<void> cleanupUnfinished();
}

/// Hardware-facing ports used directly by test cases.
class TestPorts {
  const TestPorts({
    required this.commissioning,
    required this.operationalConnection,
    required this.onOff,
    required this.nodeLabel,
    required this.fabric,
    required this.controllerIdentity,
  });

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
