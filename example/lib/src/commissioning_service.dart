import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import 'android_ble_transport.dart';
import 'identity.dart';
import 'models.dart';

class MatterCommissioningService {
  Future<CommissionedNode> commission({
    required MatterIdentity identity,
    required OnboardingPayload payload,
    required String onboardingPayload,
    required String ssid,
    required String password,
    required int nodeId,
    required String deviceLabel,
    required bool useAndroidBle,
    required void Function(String stage) onStage,
  }) async {
    AndroidBleTransport? bleTransport;
    ChipDeviceController? controller;
    try {
      int? connectId;
      if (Platform.isAndroid && useAndroidBle) {
        bleTransport = AndroidBleTransport();
        connectId = await bleTransport.connect(payload, onStage: onStage);
      }

      onStage('Creating the Matter controller');
      controller = await ChipDeviceController.newControllerIfNotExist(
        identity.controllerParams,
      );
      final delegate = _CommissioningDelegate(
        identity: identity,
        controller: controller,
        nodeId: nodeId,
        onStage: onStage,
      );
      await controller.setNocChainIssuer(delegate);
      onStage('Waiting for commissioning to complete');
      await controller.pairDevice(
        nodeId,
        connectId,
        payload.setupPinCode,
        onboardingPayload,
        null,
        NetworkCredentials.wifi(
          WiFiCredentials(ssid: ssid, password: password),
        ),
        attestationDelegate: delegate,
        completionListener: delegate,
        displayName: deviceLabel,
      );
      final completedNodeId = await delegate.completion.future.timeout(
        const Duration(seconds: 180),
      );
      return CommissionedNode(
        nodeId: completedNodeId,
        controller: controller,
        vendorId: payload.vendorId,
        productId: payload.productId,
      );
    } catch (_) {
      if (controller != null) {
        await controller.stopDevicePairing(nodeId).catchError((Object _) {});
        await controller.deleteDeviceController().catchError((Object _) {});
      }
      rethrow;
    } finally {
      await bleTransport?.dispose();
    }
  }

  Future<CommissionedNode> commissionWithAddress({
    required MatterIdentity identity,
    required String address,
    required int port,
    required int discriminator,
    required int setupPin,
    required int nodeId,
    required void Function(String stage) onStage,
  }) async {
    ChipDeviceController? controller;
    try {
      onStage('Creating direct-address controller');
      controller = await ChipDeviceController.newControllerIfNotExist(
        identity.controllerParams,
      );
      final delegate = _CommissioningDelegate(
        identity: identity,
        controller: controller,
        nodeId: nodeId,
        onStage: onStage,
      );
      await controller.setNocChainIssuer(delegate);
      onStage('Starting PASE against the supplied endpoint');
      await controller.pairDeviceWithAddress(
        deviceId: nodeId,
        address: address,
        port: port,
        discriminator: discriminator,
        setupPincode: setupPin,
        attestationDelegate: delegate,
        completionListener: delegate,
      );
      final completedNodeId = await delegate.completion.future.timeout(
        const Duration(seconds: 180),
      );
      return CommissionedNode(nodeId: completedNodeId, controller: controller);
    } catch (_) {
      if (controller != null) {
        await controller.stopDevicePairing(nodeId).catchError((Object _) {});
        await controller.deleteDeviceController().catchError((Object _) {});
      }
      rethrow;
    }
  }
}

class _CommissioningDelegate
    implements CompletionListener, DeviceAttestationDelegate, NOCChainIssuer {
  _CommissioningDelegate({
    required this.identity,
    required this.controller,
    required this.nodeId,
    required this.onStage,
  });

  final MatterIdentity identity;
  final ChipDeviceController controller;
  final int nodeId;
  final void Function(String stage) onStage;
  final Completer<int> completion = Completer<int>();

  void _fail(Object error) {
    if (!completion.isCompleted) {
      completion.completeError(error);
    }
  }

  @override
  void onCommissioningComplete(int? commissionedNodeId, int errorCode) {
    if (errorCode != 0) {
      _fail(StateError('Commissioning failed with error code $errorCode.'));
      return;
    }
    if (!completion.isCompleted) {
      completion.complete(commissionedNodeId ?? nodeId);
    }
  }

  @override
  void onCommissioningStatusUpdate(int nodeId, String stage, int errorCode) {
    onStage(errorCode == 0 ? stage : '$stage (error $errorCode)');
  }

  @override
  void onConnectDeviceComplete() => onStage('Device connected');

  @override
  void onError(Exception error) => _fail(error);

  @override
  void onICDRegistrationComplete(int errorCode, ICDDeviceInfo? icdDeviceInfo) {
    onStage(
      errorCode == 0 ? 'ICD registration complete' : 'ICD registration failed',
    );
  }

  @override
  void onICDRegistrationInfoRequired() {
    onStage('ICD registration information required');
  }

  @override
  void onNotifyChipConnectionClosed() {
    onStage('Matter connection closed');
  }

  @override
  void onOpCSRGenerationComplete(Uint8List csr) {
    onStage('Operational CSR generated');
  }

  @override
  void onPairingComplete(int errorCode) {
    if (errorCode != 0) {
      _fail(StateError('Pairing failed with error code $errorCode.'));
    }
  }

  @override
  void onPairingDeleted(int errorCode) {}

  @override
  void onReadCommissioningInfo(
    int vendorId,
    int productId,
    int wifiEndpointId,
    int threadEndpointId,
  ) {
    onStage('Commissioning information received');
  }

  @override
  void onStatusUpdate(int status) => onStage('Controller status $status');

  @override
  void onDeviceAttestationCompleted(
    int devicePtr,
    AttestationInfo? attestationInfo,
    int errorCode,
  ) {
    unawaited(controller.continueCommissioning(devicePtr, true));
  }

  @override
  void onNOCChainGenerationNeeded(
    String? onNOCChainGenerationCompleteHandle,
    CSRInfo csrInfo,
    AttestationInfo attestationInfo,
  ) {
    unawaited(_issueNocChain(onNOCChainGenerationCompleteHandle, csrInfo));
  }

  Future<void> _issueNocChain(String? completeHandle, CSRInfo csrInfo) async {
    try {
      final publicKey = await controller.publicKeyFromCSR(csrInfo.csr);
      final delegate = identity.keypairDelegate;
      final nodeCertificate =
          await ChipDeviceController.createOperationalCertificate(
            delegate,
            identity.rootCertificate,
            publicKey,
            identity.fabricId,
            nodeId,
            null,
          );
      await controller.onNOCChainGeneration(
        ControllerParams(
          rootCertificate: identity.rootCertificate,
          intermediateCertificate: identity.rootCertificate,
          operationalCertificate: nodeCertificate,
          adminSubject: kTestControllerNodeId,
          keypairDelegate: delegate,
          ipk: defaultIpk,
        ),
        onNOCChainGenerationCompleteHandle: completeHandle,
      );
    } catch (error) {
      _fail(error);
    }
  }
}
