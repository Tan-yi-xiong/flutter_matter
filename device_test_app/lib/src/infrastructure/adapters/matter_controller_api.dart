import 'dart:async';
import 'dart:typed_data';

import 'package:pointycastle/export.dart';

import '../../application/ports.dart';
import '../matter/matter.dart';

/// Narrow controller surface used by adapters and their focused tests.
abstract interface class MatterControllerApi {
  Future<MatterCommissionResult> commission(MatterCommissionRequest request);

  Future<MatterConnection> connect(MatterConnectRequest request);

  Future<void> releaseConnection(MatterConnection connection);

  Future<MatterInvokeResult> invokeOnOff(MatterOnOffRequest request);

  Future<MatterAttributeValue> readAttribute(
    MatterReadAttributeRequest request,
  );

  Future<String> readNodeLabel({
    required int nodeId,
    MatterConnection? connection,
  });

  Future<MatterWriteResult> writeNodeLabel(MatterWriteNodeLabelRequest request);

  Future<MatterSubscription> subscribeOnOff({
    required int nodeId,
    MatterConnection? connection,
  });

  Future<MatterInvokeResult> removeFabric(MatterRemoveFabricRequest request);

  Future<void> close();
}

class MatterControllerServiceApi implements MatterControllerApi {
  MatterControllerServiceApi(this._service);

  final MatterControllerService _service;

  @override
  Future<MatterCommissionResult> commission(MatterCommissionRequest request) {
    return _service.commission(request);
  }

  @override
  Future<MatterConnection> connect(MatterConnectRequest request) {
    return _service.connect(request);
  }

  @override
  Future<void> releaseConnection(MatterConnection connection) {
    return _service.releaseConnection(connection);
  }

  @override
  Future<MatterInvokeResult> invokeOnOff(MatterOnOffRequest request) {
    return _service.invokeOnOff(request);
  }

  @override
  Future<MatterAttributeValue> readAttribute(
    MatterReadAttributeRequest request,
  ) {
    return _service.readAttribute(request);
  }

  @override
  Future<String> readNodeLabel({
    required int nodeId,
    MatterConnection? connection,
  }) {
    return _service.readNodeLabel(nodeId: nodeId, connection: connection);
  }

  @override
  Future<MatterWriteResult> writeNodeLabel(
    MatterWriteNodeLabelRequest request,
  ) {
    return _service.writeNodeLabel(request);
  }

  @override
  Future<MatterSubscription> subscribeOnOff({
    required int nodeId,
    MatterConnection? connection,
  }) {
    return _service.subscribeOnOff(nodeId: nodeId, connection: connection);
  }

  @override
  Future<MatterInvokeResult> removeFabric(MatterRemoveFabricRequest request) {
    return _service.removeFabric(request);
  }

  @override
  Future<void> close() {
    return _service.close();
  }
}

/// Identity persistence surface kept separate from live controller operations.
abstract interface class MatterControllerIdentityStoreApi {
  Future<MatterControllerCredentials> loadOrCreate(
    MatterControllerConfig config,
  );

  Future<void> clear();
}

class MatterControllerCredentialsStoreApi
    implements MatterControllerIdentityStoreApi {
  MatterControllerCredentialsStoreApi(this._service);

  final MatterControllerCredentialsService _service;

  @override
  Future<MatterControllerCredentials> loadOrCreate(
    MatterControllerConfig config,
  ) {
    return _service.loadOrCreate(config);
  }

  @override
  Future<void> clear() {
    return _service.clear();
  }
}

/// Converts a controller identity into an opaque, stable run handle.
String matterIdentityOpaqueId({
  required ControllerIdentityPurpose purpose,
  required Uint8List publicKey,
}) {
  final digest = _sha256(publicKey);
  final suffix = digest
      .sublist(0, 12)
      .map((value) => value.toRadixString(16).padLeft(2, '0'))
      .join();
  return 'controller-${purpose.wireName}-$suffix';
}

Uint8List _sha256(Uint8List input) {
  return SHA256Digest().process(input);
}
