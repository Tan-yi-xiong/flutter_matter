import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

abstract interface class MatterControllerPort {
  Future<void> setNocChainIssuer(NOCChainIssuer issuer);

  Future<void> pairDevice({
    required int nodeId,
    required int? connectId,
    required int setupPinCode,
    required String? onboardingPayload,
    required NetworkCredentials networkCredentials,
    required DeviceAttestationDelegate? attestationDelegate,
    required CompletionListener completionListener,
  });

  Future<void> pairDeviceWithAddress({
    required int nodeId,
    required String address,
    required int port,
    required int discriminator,
    required int setupPincode,
    Uint8List? csrNonce,
    required DeviceAttestationDelegate? attestationDelegate,
    required CompletionListener completionListener,
  });

  Future<void> stopDevicePairing(int nodeId);

  Future<Uint8List> publicKeyFromCSR(Uint8List csr);

  Future<int> onNOCChainGeneration(
    ControllerParams params, {
    String? onNOCChainGenerationCompleteHandle,
  });

  Future<void> continueCommissioning(
    int devicePtr,
    bool ignoreAttestationFailure,
  );

  Future<void> connectedDevice(
    int nodeId,
    ConnectedDeviceCallback callback, {
    Object? connectContext,
  });

  Future<void> releaseConnectContext(Object connectContext);

  Future<void> invoke(
    InvokeCallback callback,
    int nodeId,
    InvokeElement invokeElement, {
    Object? connectContext,
    int timedRequestTimeoutMs = 0,
    int imTimeoutMs = 0,
  });

  Future<void> read(
    int nodeId,
    ReportCallback callback,
    List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    bool isFabricFiltered,
    int imTimeoutMs,
    int eventMin, {
    Object? connectContext,
  });

  Future<void> write(
    int nodeId,
    WriteAttributesCallback callback,
    List<AttributeWriteRequest> attributeList,
    int timedRequestTimeoutMs,
    int imTimeoutMs, {
    Object? connectContext,
  });

  Future<void> subscribe(
    int nodeId,
    SubscriptionCallback callback,
    List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    int minInterval,
    int maxInterval,
    bool keepSubscriptions,
    bool isFabricFiltered,
    int imTimeoutMs,
    int eventMin, {
    Object? connectContext,
  });

  Future<int?> getFabricIndex();

  Future<bool> unSubscription(int fabricIndex, int nodeId, int subscriptionId);

  Future<void> deleteDeviceController();
}

abstract interface class MatterControllerFactory {
  Future<MatterControllerPort> create(ControllerParams params);
}

class FlutterMatterControllerFactory implements MatterControllerFactory {
  const FlutterMatterControllerFactory();

  @override
  Future<MatterControllerPort> create(ControllerParams params) async {
    final controller = await ChipDeviceController.newControllerIfNotExist(
      params,
    );
    return FlutterMatterControllerPort(controller);
  }
}

class FlutterMatterControllerPort implements MatterControllerPort {
  FlutterMatterControllerPort(this._controller);

  final ChipDeviceController _controller;

  @override
  Future<void> setNocChainIssuer(NOCChainIssuer issuer) {
    return _controller.setNocChainIssuer(issuer);
  }

  @override
  Future<void> pairDevice({
    required int nodeId,
    required int? connectId,
    required int setupPinCode,
    required String? onboardingPayload,
    required NetworkCredentials networkCredentials,
    required DeviceAttestationDelegate? attestationDelegate,
    required CompletionListener completionListener,
  }) {
    return _controller.pairDevice(
      nodeId,
      connectId,
      setupPinCode,
      onboardingPayload,
      null,
      networkCredentials,
      attestationDelegate: attestationDelegate,
      completionListener: completionListener,
    );
  }

  @override
  Future<void> pairDeviceWithAddress({
    required int nodeId,
    required String address,
    required int port,
    required int discriminator,
    required int setupPincode,
    Uint8List? csrNonce,
    required DeviceAttestationDelegate? attestationDelegate,
    required CompletionListener completionListener,
  }) {
    return _controller.pairDeviceWithAddress(
      deviceId: nodeId,
      address: address,
      port: port,
      discriminator: discriminator,
      setupPincode: setupPincode,
      csrNonce: csrNonce,
      attestationDelegate: attestationDelegate,
      completionListener: completionListener,
    );
  }

  @override
  Future<void> stopDevicePairing(int nodeId) {
    return _controller.stopDevicePairing(nodeId);
  }

  @override
  Future<Uint8List> publicKeyFromCSR(Uint8List csr) {
    return _controller.publicKeyFromCSR(csr);
  }

  @override
  Future<int> onNOCChainGeneration(
    ControllerParams params, {
    String? onNOCChainGenerationCompleteHandle,
  }) {
    return _controller.onNOCChainGeneration(
      params,
      onNOCChainGenerationCompleteHandle: onNOCChainGenerationCompleteHandle,
    );
  }

  @override
  Future<void> continueCommissioning(
    int devicePtr,
    bool ignoreAttestationFailure,
  ) {
    return _controller.continueCommissioning(
      devicePtr,
      ignoreAttestationFailure,
    );
  }

  @override
  Future<void> connectedDevice(
    int nodeId,
    ConnectedDeviceCallback callback, {
    Object? connectContext,
  }) {
    return _controller.connectedDevice(
      nodeId,
      callback,
      connectContext: connectContext,
    );
  }

  @override
  Future<void> releaseConnectContext(Object connectContext) {
    return _controller.releaseConnectContext(connectContext);
  }

  @override
  Future<void> invoke(
    InvokeCallback callback,
    int nodeId,
    InvokeElement invokeElement, {
    Object? connectContext,
    int timedRequestTimeoutMs = 0,
    int imTimeoutMs = 0,
  }) {
    return _controller.invoke(
      callback,
      nodeId,
      invokeElement,
      connectContext: connectContext,
      timedRequestTimeoutMs: timedRequestTimeoutMs,
      imTimeoutMs: imTimeoutMs,
    );
  }

  @override
  Future<void> read(
    int nodeId,
    ReportCallback callback,
    List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    bool isFabricFiltered,
    int imTimeoutMs,
    int eventMin, {
    Object? connectContext,
  }) {
    return _controller.read(
      nodeId,
      callback,
      attributePaths,
      eventPaths,
      dataVersionFilters,
      isFabricFiltered,
      imTimeoutMs,
      eventMin,
      connectContext: connectContext,
    );
  }

  @override
  Future<void> write(
    int nodeId,
    WriteAttributesCallback callback,
    List<AttributeWriteRequest> attributeList,
    int timedRequestTimeoutMs,
    int imTimeoutMs, {
    Object? connectContext,
  }) {
    return _controller.write(
      nodeId,
      callback,
      attributeList,
      timedRequestTimeoutMs,
      imTimeoutMs,
      connectContext: connectContext,
    );
  }

  @override
  Future<void> subscribe(
    int nodeId,
    SubscriptionCallback callback,
    List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    int minInterval,
    int maxInterval,
    bool keepSubscriptions,
    bool isFabricFiltered,
    int imTimeoutMs,
    int eventMin, {
    Object? connectContext,
  }) {
    return _controller.subscribe(
      nodeId,
      callback,
      attributePaths,
      eventPaths,
      dataVersionFilters,
      minInterval,
      maxInterval,
      keepSubscriptions,
      isFabricFiltered,
      imTimeoutMs,
      eventMin,
      connectContext: connectContext,
    );
  }

  @override
  Future<int?> getFabricIndex() {
    return _controller.getFabricIndex();
  }

  @override
  Future<bool> unSubscription(int fabricIndex, int nodeId, int subscriptionId) {
    return _controller.unSubscription(fabricIndex, nodeId, subscriptionId);
  }

  @override
  Future<void> deleteDeviceController() {
    return _controller.deleteDeviceController();
  }
}
