import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import '../ble/matter_ble_contracts.dart';
import 'matter_tlv.dart';

enum MatterTargetPlatform { android, ios }

/// Transport used to establish commissioning with a Matter device.
enum MatterCommissioningTransport {
  /// Commission over an already-on-network IP transport.
  ip,

  /// Commission over the Matter BLE transport.
  ble,
}

enum MatterFailureCode {
  invalidArgument,
  notInitialized,
  initializationFailed,
  bleDiscoveryFailed,
  bleConnectionFailed,
  pairingFailed,
  commissioningFailed,
  callbackTimeout,
  connectFailed,
  invokeFailed,
  readFailed,
  writeFailed,
  subscribeFailed,
  unsubscribeFailed,
  unsupportedOperation,
}

class MatterException implements Exception {
  MatterException(this.code, this.message, [this.cause]);

  final MatterFailureCode code;
  final String message;
  final Object? cause;

  @override
  String toString() => 'MatterException($code): $message';
}

class MatterTimeoutException extends MatterException {
  MatterTimeoutException(String operation)
    : super(MatterFailureCode.callbackTimeout, '$operation timed out');
}

/// Stable controller settings for this test app.
///
/// Values mirror the plugin's worked example so a controller can be reused
/// across runs. Callers may override them for an isolated fabric.
class MatterControllerConfig {
  MatterControllerConfig({
    this.fabricId = 709394,
    this.controllerNodeId = kTestControllerNodeId,
    this.issuerId = 0,
    this.controllerVendorId = 0xfff4,
    this.adminSubject = 0,
    Uint8List? ipk,
    this.operationTimeout = const Duration(seconds: 15),
    this.connectTimeout = const Duration(seconds: 30),
    this.commissioningTimeout = const Duration(seconds: 120),
    this.subscriptionTimeout = const Duration(seconds: 30),
  }) : ipk = Uint8List.fromList(ipk ?? defaultIpk) {
    if (fabricId < 1) {
      throw ArgumentError.value(fabricId, 'fabricId', 'Must be positive');
    }
    if (controllerNodeId < 1) {
      throw ArgumentError.value(
        controllerNodeId,
        'controllerNodeId',
        'Must be positive',
      );
    }
    if (issuerId < 0) {
      throw ArgumentError.value(issuerId, 'issuerId', 'Must not be negative');
    }
    if (controllerVendorId < 1) {
      throw ArgumentError.value(
        controllerVendorId,
        'controllerVendorId',
        'Must be positive',
      );
    }
    if (adminSubject < 0) {
      throw ArgumentError.value(
        adminSubject,
        'adminSubject',
        'Must not be negative',
      );
    }
    if (this.ipk.isEmpty) {
      throw ArgumentError.value(ipk, 'ipk', 'Must not be empty');
    }
    _validateTimeout(operationTimeout, 'operationTimeout');
    _validateTimeout(connectTimeout, 'connectTimeout');
    _validateTimeout(commissioningTimeout, 'commissioningTimeout');
    _validateTimeout(subscriptionTimeout, 'subscriptionTimeout');
  }

  final int fabricId;
  final int controllerNodeId;
  final int issuerId;
  final int controllerVendorId;
  final int adminSubject;
  final Uint8List ipk;
  final Duration operationTimeout;
  final Duration connectTimeout;
  final Duration commissioningTimeout;
  final Duration subscriptionTimeout;

  static void _validateTimeout(Duration timeout, String name) {
    if (timeout <= Duration.zero) {
      throw ArgumentError.value(timeout, name, 'Must be positive');
    }
  }
}

class MatterWifiCredentials {
  MatterWifiCredentials({required this.ssid, required this.password}) {
    if (ssid.isEmpty) {
      throw ArgumentError.value(ssid, 'ssid', 'Must not be empty');
    }
  }

  final String ssid;
  final String password;
}

class MatterThreadCredentials {
  MatterThreadCredentials({required Uint8List operationalDataset})
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
}

sealed class MatterNetworkCredentials {
  const MatterNetworkCredentials();

  NetworkCredentials toPluginCredentials();
}

class MatterWifiNetworkCredentials extends MatterNetworkCredentials {
  const MatterWifiNetworkCredentials(this.credentials);

  final MatterWifiCredentials credentials;

  @override
  NetworkCredentials toPluginCredentials() {
    return NetworkCredentials(
      wifiCredentials: WiFiCredentials(
        ssid: credentials.ssid,
        password: credentials.password,
      ),
    );
  }
}

class MatterThreadNetworkCredentials extends MatterNetworkCredentials {
  const MatterThreadNetworkCredentials(this.credentials);

  final MatterThreadCredentials credentials;

  @override
  NetworkCredentials toPluginCredentials() {
    return NetworkCredentials.thread(
      ThreadCredentials(operationalDataset: credentials.operationalDataset),
    );
  }
}

class MatterCommissionRequest {
  MatterCommissionRequest({
    required this.onboardingPayload,
    required this.setupPinCode,
    required this.discriminator,
    required this.hasShortDiscriminator,
    required this.nodeId,
    required this.networkCredentials,
    required this.commissioningTransport,
    this.discoveredBleDevice,
    this.bleScanTimeout = const Duration(seconds: 15),
    this.timeout,
  }) {
    if (onboardingPayload.isEmpty) {
      throw ArgumentError.value(
        onboardingPayload,
        'onboardingPayload',
        'Must not be empty',
      );
    }
    if (setupPinCode <= 0) {
      throw ArgumentError.value(
        setupPinCode,
        'setupPinCode',
        'Must be positive',
      );
    }
    final maximumDiscriminator = hasShortDiscriminator ? 0x0f : 0x0fff;
    if (discriminator < 0 || discriminator > maximumDiscriminator) {
      throw ArgumentError.value(
        discriminator,
        'discriminator',
        'Must be between 0 and $maximumDiscriminator',
      );
    }
    if (nodeId < 1) {
      throw ArgumentError.value(nodeId, 'nodeId', 'Must be positive');
    }
    if (bleScanTimeout <= Duration.zero) {
      throw ArgumentError.value(
        bleScanTimeout,
        'bleScanTimeout',
        'Must be positive',
      );
    }
    if (timeout != null && timeout! <= Duration.zero) {
      throw ArgumentError.value(timeout, 'timeout', 'Must be positive');
    }
  }

  final String onboardingPayload;
  final int setupPinCode;
  final int discriminator;
  final bool hasShortDiscriminator;
  final int nodeId;
  final MatterNetworkCredentials networkCredentials;
  final MatterCommissioningTransport commissioningTransport;
  final MatterBleDiscoveredDevice? discoveredBleDevice;
  final Duration bleScanTimeout;
  final Duration? timeout;
}

class MatterCommissioningStage {
  MatterCommissioningStage({
    required this.nodeId,
    required this.stage,
    required this.errorCode,
  });

  final int nodeId;
  final String stage;
  final int errorCode;
}

class MatterCommissionResult {
  MatterCommissionResult({required this.nodeId, required this.stages});

  final int nodeId;
  final List<MatterCommissioningStage> stages;
}

class MatterConnection {
  const MatterConnection({required this.nodeId, required this.context});

  final int nodeId;
  final Object? context;
}

class MatterConnectRequest {
  MatterConnectRequest({required this.nodeId, this.timeout});

  final int nodeId;
  final Duration? timeout;
}

enum MatterOnOffCommand { off, on, toggle }

class MatterOnOffRequest {
  const MatterOnOffRequest({
    required this.nodeId,
    required this.command,
    this.endpointId = 1,
    this.connection,
    this.timedRequestTimeoutMs = 5000,
    this.imTimeoutMs = 0,
  });

  final int nodeId;
  final MatterOnOffCommand command;
  final int endpointId;
  final MatterConnection? connection;
  final int timedRequestTimeoutMs;
  final int imTimeoutMs;
}

class MatterInvokeResult {
  MatterInvokeResult({
    required this.successCode,
    this.responseTlv,
    this.responseJson,
  });

  final int successCode;
  final Uint8List? responseTlv;
  final String? responseJson;

  bool get isSuccess => successCode == 0;
}

class MatterReadAttributeRequest {
  const MatterReadAttributeRequest({
    required this.nodeId,
    required this.clusterId,
    required this.attributeId,
    this.endpointId = 0,
    this.connection,
    this.imTimeoutMs = 5000,
  });

  final int nodeId;
  final int clusterId;
  final int attributeId;
  final int endpointId;
  final MatterConnection? connection;
  final int imTimeoutMs;
}

class MatterAttributeValue {
  MatterAttributeValue({
    required this.endpointId,
    required this.clusterId,
    required this.attributeId,
    required Uint8List tlv,
  }) : tlv = Uint8List.fromList(tlv);

  final int endpointId;
  final int clusterId;
  final int attributeId;
  final Uint8List tlv;

  String decodeString() => decodeMatterString(tlv);

  bool decodeBool() => decodeMatterBool(tlv);

  int decodeUnsigned() => decodeMatterUnsigned(tlv);
}

class MatterWriteNodeLabelRequest {
  MatterWriteNodeLabelRequest({
    required this.nodeId,
    required this.label,
    this.endpointId = 0,
    this.connection,
    this.timedRequestTimeoutMs = 5000,
    this.imTimeoutMs = 5000,
  }) {
    if (label.isEmpty) {
      throw ArgumentError.value(label, 'label', 'Must not be empty');
    }
  }

  final int nodeId;
  final String label;
  final int endpointId;
  final MatterConnection? connection;
  final int timedRequestTimeoutMs;
  final int imTimeoutMs;
}

class MatterWriteResult {
  const MatterWriteResult({required this.statusCode, this.clusterStatus});

  final int statusCode;
  final int? clusterStatus;

  bool get isSuccess => statusCode == 0;
}

class MatterSubscribeRequest {
  const MatterSubscribeRequest({
    required this.nodeId,
    required this.clusterId,
    required this.attributeId,
    this.endpointId = 0,
    this.connection,
    this.minInterval = 3,
    this.maxInterval = 8,
    this.keepSubscriptions = true,
    this.isFabricFiltered = false,
    this.imTimeoutMs = 6000,
    this.eventMin = 0,
    this.establishTimeout,
  });

  final int nodeId;
  final int clusterId;
  final int attributeId;
  final int endpointId;
  final MatterConnection? connection;
  final int minInterval;
  final int maxInterval;
  final bool keepSubscriptions;
  final bool isFabricFiltered;
  final int imTimeoutMs;
  final int eventMin;
  final Duration? establishTimeout;
}

abstract interface class MatterSubscription {
  int get subscriptionId;

  Future<int> waitForEstablished(Duration timeout);

  Stream<MatterAttributeValue> get reports;

  Stream<MatterException> get errors;

  Future<bool> close({Duration timeout = const Duration(seconds: 10)});
}

class MatterRemoveFabricRequest {
  const MatterRemoveFabricRequest({
    required this.nodeId,
    this.fabricIndex,
    this.endpointId = 0,
    this.connection,
    this.timedRequestTimeoutMs = 5000,
    this.imTimeoutMs = 5000,
  });

  final int nodeId;
  final int? fabricIndex;
  final int endpointId;
  final MatterConnection? connection;
  final int timedRequestTimeoutMs;
  final int imTimeoutMs;
}
