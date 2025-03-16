import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_example/ble_manager.dart';
import 'package:flutter_matter_example/data.dart';
import 'package:hex/hex.dart';
import 'package:collection/collection.dart';
import 'package:pointycastle/export.dart' hide State;

class DeviceProvisioningPage extends StatefulWidget {
  final OnboardingPayload payload;
  final String onboardingPayload;
  final WiFiCredentials wiFiCredentials;

  const DeviceProvisioningPage({super.key, required this.payload, required this.wiFiCredentials, required this.onboardingPayload});

  @override
  State<DeviceProvisioningPage> createState() => _DeviceProvisioningPageState();
  
 
}

class _DeviceProvisioningPageState extends State<DeviceProvisioningPage> implements NOCChainIssuer, BlePlatformDelegate, CompletionListener, DeviceAttestationDelegate {
  
  BLEManager? bleManager;
  int? connectId;
  bool isProvisioning = false;
  bool isFinish = false;
  String? stage;
  int? errorCode;
  int? nodeId;
  int? fabricId;
  ChipDeviceController? deviceController;
  late AsymmetricKeyPair<ECPublicKey, ECPrivateKey> keypair;
  late List<Uint8List> cert;
  
  @override
  void dispose() {
    super.dispose();
    BleManager.disconnectAll();
    if (nodeId != null) {
      deviceController?.stopDevicePairing(nodeId!).whenComplete(() => deviceController?.deleteDeviceController());
    }
    if (connectId != null) {
      bleManager?.disconnect(connectId!);
    }
  }
  
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text(isProvisioning ? 'Provisioning...' : "PairDevice")),
      body: Builder(builder: (_) {
        if (!isProvisioning && !isFinish) {
        return Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Text('Vendor: ${widget.payload.vendorId.toRadixString(16)}\nProduct: ${widget.payload.productId.toRadixString(16)}\nSetup code: ${widget.payload.setupPinCode.toRadixString(16)}'),
            SizedBox(height: 16,),
            Align(
              alignment: Alignment.center,
              child: ElevatedButton(
                onPressed: () async {
                  startProvisioning();
                },
                child: const Text('Start provisioning'),
              ),
            )
          ],
        );
      }
      return Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            if (!isFinish)
              Text('Current Step: ${stage}', style: TextStyle(fontSize: 20),),
            if (isFinish)
              Text('Provisioning${errorCode == 0 ? 'success' : 'fail'} code $errorCode', style: TextStyle(fontSize: 20),),
            if (isFinish)
              ElevatedButton(onPressed: () {
                Navigator.pop(context);
              }, child: Text('Back')),
          ],
        ),
      );
    }),
    );
  }

  void startProvisioning() async {
    setState(() {
      isProvisioning = true;
      stage = 'Connecting to the device....';
    });
    
    // vendorId and productId are all 0, it's a share code 
    bool isShare = widget.payload.vendorId == 0 && widget.payload.productId == 0x00;
    // Onlay Android can use custom ble stack
    // if you not use custom ble stack, unnecessary care about the ble code
    if (Platform.isAndroid && !isShare) { 
      final device = await BleManager.getDevice(widget.payload);
      print("find device $device");
      if (device != null) {
        for (var i = 0; i < 3; i++) {
          final success = await BleManager.connect(device);
          if (success) {
            connectId = 0x04;
          }
          if (connectId != null || !context.mounted) {
            break;
          }
        }
      }

      if (connectId == null) {
        setState(() {
          errorCode = -1;
          isFinish = true;
        });
        return;
      }

      final service = BleManager.getConnDevice()!.servicesList.firstWhereOrNull(
        (element) => element.serviceUuid == BleManager.matter_uuid);
      service!.characteristics.forEach((chr) {
        final ss = chr.onValueReceived.listen((event) {
          print('onValueReceived ${chr.characteristicUuid} ${event}');
          BLELayerPlatform.handleIndicationReceived(connectId, Uint8List.fromList(BleManager.matter_uuid.bytes), Uint8List.fromList(chr.characteristicUuid.bytes), Uint8List.fromList(event)).then((value) {
            print('handleIndicationReceived $value');
          });
        });
        BleManager.getConnDevice()!.cancelWhenDisconnected(ss);
      });
      await BLELayerPlatform.setBlePlatformDelegate(null);
      await BLELayerPlatform.setBlePlatformDelegate(this);
    }

    keypair = await genAsymmetricKeyPair();
    final kp = keypair;
    cert = await getX509Certificate();
    this.fabricId = await getFabricId();
    final cp = ControllerParams(
      skipCommissioningComplete: false,
      fabricId: fabricId!,
      keypairDelegate: MyKeypairDelegate(publicKey: kp.publicKey, privateKey: kp.privateKey),
      ipk: defaultIpk,
      rootCertificate: cert[0],
      intermediateCertificate: cert[0],
      operationalCertificate: cert[1]
    );
    
    deviceController = await ChipDeviceController.newControllerIfNotExist(cp);
    deviceController!.setNocChainIssuer(this);
    setState(() {
      stage = 'startProvisioning';
    });
    nodeId = await nextNodeId();
    await deviceController!.pairDevice(
      nodeId!, 
      connectId, 
      widget.payload.setupPinCode, 
      widget.onboardingPayload,
      null,
      NetworkCredentials(wifiCredentials: widget.wiFiCredentials),
      attestationDelegate: this,
      completionListener: this
    ).catchError((e,s) {
      print('pairDevice error $e $s');
      setState(() {
        errorCode = -2;
        isFinish = true;
      });
    });
  }

  /// CompletionListener callback start ==================================

   @override
  void onCloseBleComplete() {
    print('onCloseBleComplete');
  }
  
  @override
  void onCommissioningComplete(int? nodeId, int errorCode) {
    print('onCommissioningComplete $nodeId $errorCode');
    setState(() {
      saveDevice(Device(nodeId!));
      this.errorCode = errorCode;
      isProvisioning = false;
      isFinish = true;
    });
  }
  
  @override
  void onCommissioningStatusUpdate(int nodeId, String stage, int errorCode) {
    print('onCommissioningStatusUpdate $nodeId $stage $errorCode');
     setState(() {
      this.stage = stage;
     });
  }
  
  @override
  void onConnectDeviceComplete() {
    print('onConnectDeviceComplete');
  }
  
  @override
  void onError(Exception error) {
    print('onError $error');
  }
  
  @override
  void onICDRegistrationInfoRequired() {
    print('onICDRegistrationInfoRequired');
  }
  
  @override
  void onNotifyChipConnectionClosed() {
    print('onNotifyChipConnectionClosed');
  }
  
  @override
  void onOpCSRGenerationComplete(Uint8List csr) {
    print('onOpCSRGenerationComplete ${base64.encode(csr)}');
  }
  
  @override
  void onPairingComplete(int errorCode) {
    print('onPairingComplete $errorCode');
    if (errorCode != 0) {
      setState(() {
        this.errorCode = errorCode;
        isProvisioning = false;
        isFinish = true;
      });
    }
  }
  
  @override
  void onPairingDeleted(int errorCode) {
    print('onPairingDeleted $errorCode');
  }
  
  @override
  void onReadCommissioningInfo(int vendorId, int productId, int wifiEndpointId, int threadEndpointId) {
    print('onReadCommissioningInfo $vendorId $productId $wifiEndpointId $threadEndpointId');
  }
  
  @override
  void onStatusUpdate(int status) {
    print('onStatusUpdate $status');
  }

  /// CompletionListener callback end ==================================




  /// DeviceAttestationDelegate callback start ==================================
  
  @override
  void onDeviceAttestationCompleted(int devicePtr, AttestationInfo? attestationInfo, int errorCode) {
    print('onDeviceAttestationCompleted $errorCode');
    deviceController!.continueCommissioning(devicePtr, true);
  }

  /// DeviceAttestationDelegate callback end ==================================
  


  /// BlePlatformDelegate callback start ==================================

  @override
  Future<bool> closeConnection(connObj) async {
    await BleManager.getConnDevice()!.disconnect();
    return true;
  }
  
  @override
  Future<int> getMTU(connObj) async {
    print('getMTU $connObj -> ${BleManager.getConnDevice()!.mtuNow}');
    return BleManager.getConnDevice()!.mtuNow;
  }
  
  @override
  Future<bool> sendIndication(connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf) {
    // TODO: implement sendIndication
    throw UnimplementedError();
  }
  
  @override
  Future<bool> sendReadRequest(connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf) {
    // TODO: implement sendReadRequest
    throw UnimplementedError();
  }
  
  @override
  Future<bool> sendReadResponse(connObj, requestContext, Uint8List svcId, Uint8List charId) {
    // TODO: implement sendReadResponse
    throw UnimplementedError();
  }
  
  @override
  Future<bool> sendWriteRequest(connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf) async {
    print("sendWriteRequest $connObj ${HEX.encode(svcId)} ${HEX.encode(charId)} ${HEX.encode(pBuf)}");
    bool writeSuccess = false;
    final service = BleManager.getConnDevice()!.servicesList.firstWhereOrNull((element) => element.serviceUuid == Guid.fromBytes(svcId));
    final char = service?.characteristics.firstWhereOrNull((element) => element.characteristicUuid == Guid.fromBytes(charId));
    if (char != null) {
      await char.write(pBuf, withoutResponse: false)
        .then((value) {
          writeSuccess = true;
          Future(() {
            BLELayerPlatform.handleWriteConfirmation(connObj, svcId, charId, true);
          });
          return value;
        })
        .catchError((_) {
          writeSuccess = false;
          Future(() {
            BLELayerPlatform.handleWriteConfirmation(connObj, svcId, charId, false);
          });
        });
    }
    return writeSuccess;
  }
  
  @override
  Future<bool> subscribeCharacteristic(connObj, Uint8List svcId, Uint8List charId) async {
    print("subscribeCharacteristic $connObj ${HEX.encode(svcId)} ${HEX.encode(charId)}");
    final service = BleManager.getConnDevice()!.servicesList.firstWhereOrNull((element) => element.serviceUuid == Guid.fromBytes(svcId));
    final char = service?.characteristics.firstWhereOrNull((element) => element.characteristicUuid == Guid.fromBytes(charId));
    return await char?.setNotifyValue(true).catchError((e) => false).then((v) {
      Future(() {
        BLELayerPlatform.handleSubscribeComplete(connObj, svcId, charId, v);
      });
      return v;
    }) ?? false;
  }
  
  @override
  Future<bool> unsubscribeCharacteristic(connObj, Uint8List svcId, Uint8List charId) async {
    final service = BleManager.getConnDevice()!.servicesList.firstWhereOrNull((element) => element.serviceUuid == Guid.fromBytes(svcId));
    final char = service?.characteristics.firstWhereOrNull((element) => element.characteristicUuid == Guid.fromBytes(charId));
    return await char?.setNotifyValue(false).catchError((e) => false) ?? false;
  }

  /// BlePlatformDelegate callback end ==================================




  /// NOCChainIssuer callback start ================================== 
  @override
  void onNOCChainGenerationNeeded(onNOCChainGenerationCompleteHandle, CSRInfo csrInfo, AttestationInfo attestationInfo) async {
    final pubKey = await deviceController!.publicKeyFromCSR(csrInfo.csr);
    final kpd = MyKeypairDelegate(publicKey: keypair.publicKey, privateKey: keypair.privateKey);
    /// generateNOCChain
    final deviceNOC = await ChipDeviceController.createOperationalCertificate(
      kpd, 
      cert[0], 
      pubKey, 
      fabricId!, 
      nodeId!, 
      null
    );
    deviceController!.onNOCChainGeneration(ControllerParams(
      rootCertificate: cert[0],
      intermediateCertificate: cert[0],
      operationalCertificate: deviceNOC,
      adminSubject: kTestControllerNodeId,
      keypairDelegate: kpd,
      ipk: getDefaultIpk(),
    ), onNOCChainGenerationCompleteHandle: onNOCChainGenerationCompleteHandle);
  }
}

Uint8List getDefaultIpk() {
  List<int> mDefaultIpk = [
    't'.codeUnitAt(0), 'e'.codeUnitAt(0), 'm'.codeUnitAt(0), 'p'.codeUnitAt(0),
    'o'.codeUnitAt(0), 'r'.codeUnitAt(0), 'a'.codeUnitAt(0), 'r'.codeUnitAt(0),
    'y'.codeUnitAt(0), ' '.codeUnitAt(0), 'i'.codeUnitAt(0), 'p'.codeUnitAt(0),
    'k'.codeUnitAt(0), ' '.codeUnitAt(0), '0'.codeUnitAt(0), '1'.codeUnitAt(0)
  ];
  return Uint8List.fromList(mDefaultIpk);
}