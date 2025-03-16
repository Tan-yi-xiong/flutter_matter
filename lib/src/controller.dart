
import 'dart:convert';
import 'dart:ffi';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/foundation.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/callback_handler.dart';
import 'package:flutter_matter/src/constant.dart';
import 'package:flutter_matter/src/utils.dart';

import 'exception.dart';
import 'model/attribute_write_request.dart';
import 'model/chip_attribute_path.dart';
import 'model/chip_event_path.dart';
import 'model/data_version_filter.dart';
import 'model/invoke_element.dart';
import 'model/node_state.dart';
import 'model/status.dart';

const _hostName = 'devicecontroller';

const kTestControllerNodeId = 112233;

class WiFiCredentials {
  final String ssid;
  final String password;

  WiFiCredentials({required this.ssid, required this.password});

}

class NetworkCredentials implements TransportObject {
  final WiFiCredentials wifiCredentials;

  NetworkCredentials({required this.wifiCredentials});
  
  @override
  String encode() {
    return jsonEncode(toJson());
  }

  toJson() => {
    'wifiCredentials': {
      'ssid': wifiCredentials.ssid,
      'password': wifiCredentials.password
    }
  };
}

class AttestationInfo {

  final Uint8List challenge;
  final Uint8List nonce;
  final Uint8List elements;
  final Uint8List elementsSignature;
  final Uint8List dac;
  final Uint8List pai;
  final Uint8List certificationDeclaration;
  final Uint8List firmwareInfo;
  final int? vendorId;
  final int? productId;

  AttestationInfo({required this.challenge, required this.nonce, required this.elements, required this.elementsSignature, required this.dac, required this.pai, required this.certificationDeclaration, required this.firmwareInfo, required this.vendorId, required this.productId});

  factory AttestationInfo.decode(Map json) {
    return AttestationInfo(
      challenge: toUint8List(json['challenge']), 
      nonce: toUint8List(json['nonce']), 
      elements: toUint8List(json['elements']), 
      elementsSignature: toUint8List(json['elementsSignature']), 
      dac: toUint8List(json['dac']), 
      pai: toUint8List(json['pai']), 
      certificationDeclaration: toUint8List(json['certificationDeclaration']),
      firmwareInfo: toUint8List(json['firmwareInfo']),
      vendorId: json['vendorId'] as int, 
      productId: json['productId'] as int
    );
  }
}

class KeypairDelegateCallbackHandler extends CallbackHandler<KeypairDelegate> {

  KeypairDelegateCallbackHandler() : super();

  @override
  onCallbackMethodCall(String methodName, arguments) {
    matterPrint('$runtimeType onCallbackMethodCall $methodName $arguments');
    final decodeArgs = jsonDecode(arguments);
    KeypairDelegate? kd = handlers[decodeArgs['handle'].toString()];
      if (kd == null) {
        final errorMsg = "Not found delegate for handle: ${decodeArgs['handle']}";
        matterPrint(errorMsg);
        return createPlatformCallExceptionResult(argsInvalid, errorMsg);
      }
      matterPrint("$kd $methodName call");
      switch (methodName) {
        case 'GeneratePrivateKey':
          kd.generatePrivateKey();
          return createPlatformCallSuccessResult();
        case 'EcdsaSignMessage':
          final signData = kd.ecdsaSignMessage(jsonDecode(arguments)['message'].cast<int>());
          return createPlatformCallSuccessResult(successMsg: jsonEncode({
            'ecdsaSign': List.from(signData)
          }));
        case 'GetPublicKey':
          final publicKey = kd.getPublicKey();
          return createPlatformCallSuccessResult(successMsg: jsonEncode({
            'publicKey': List.from(publicKey)
          }));
        case 'CreateCertificateSigningRequest':
          final csr = kd.createCertificateSigningRequest();
          return createPlatformCallSuccessResult(successMsg: jsonEncode({
            'certificateSigningRequest': List.from(csr)
          }));
      }
  }
}

final _keypairDelegateCallbackHandler = KeypairDelegateCallbackHandler();

/** Represents information relating to NOC CSR. */
class CSRInfo {

  final Uint8List nonce;
  final Uint8List elements;
  final Uint8List elementsSignature;
  final Uint8List csr;

  CSRInfo({required this.nonce, required this.elements, required this.elementsSignature, required this.csr});

  factory CSRInfo.decode(Map json) {
    return CSRInfo(
      nonce: Uint8List.fromList((json['nonce'] as List<dynamic>).cast<int>()), 
      elements: Uint8List.fromList((json['elements'] as List<dynamic>).cast<int>()), 
      elementsSignature: Uint8List.fromList((json['elementsSignature'] as List<dynamic>).cast<int>()), 
      csr: Uint8List.fromList((json['csr'] as List<dynamic>).cast<int>())
    );
  }
}

/// Interface to listen for callbacks from CHIPDeviceController.
abstract class CompletionListener {

  /// Notifies the completion of "ConnectDevice" command.
  void onConnectDeviceComplete();

  /// Notifies the pairing status.
  void onStatusUpdate(int status);

  /// Notifies the completion of pairing.
  void onPairingComplete(int errorCode);

  /// Notifies the deletion of pairing session.
  void onPairingDeleted(int errorCode);

  /// Notifies the completion of commissioning.
  void onCommissioningComplete(int? nodeId, int errorCode);

  /// Notifies the completion of each stage of commissioning.
  void onReadCommissioningInfo(
      int vendorId, int productId, int wifiEndpointId, int threadEndpointId);

  /// Notifies the completion of each stage of commissioning.
  void onCommissioningStatusUpdate(int nodeId, String stage, int errorCode);

  /// Notifies that the Chip connection has been closed.
  void onNotifyChipConnectionClosed();

  /// Notifies the completion of the "close BLE connection" command.
  // void onCloseBleComplete();

  /// Notifies the listener of the error.
  void onError(Exception error);

  /// Notifies the Commissioner when the OpCSR for the Comissionee is generated.
  void onOpCSRGenerationComplete(Uint8List csr);

  /// Notifies when the ICD registration information (ICD symmetric key, check-in node ID and
  /// monitored subject) is required.
  void onICDRegistrationInfoRequired();

  /// Notifies when the registration flow for the ICD completes
  // TODO: implement
  // void onICDRegistrationComplete(int errorCode, ICDDeviceInfo icdDeviceInfo);
}


/// Interface to implement custom operational credentials issuer (NOC chain generation).
abstract class NOCChainIssuer {
    // When a NOCChainIssuer is set for this controller, then onNOCChainGenerationNeeded will be
    // called when the DAC chain must be verified and NOC chain needs to be issued from a CSR. This
    // allows for custom credentials issuer and DAC verifier implementations, for example, when a
    // proprietary cloud API will perform DAC verification and the NOC chain issuance from CSR.
    void onNOCChainGenerationNeeded(String? onNOCChainGenerationCompleteHandle, CSRInfo csrInfo, AttestationInfo attestationInfo);
}

/// Delegate for device attestation verifiers.
///
/// <p>If DeviceAttestationDelegate is implemented, then onDeviceAttestationCompleted will always be
/// called when device attestation completes.
///
/// <p>If device attestation fails, {@link ChipDeviceController#continueCommissioning(long, boolean)}
/// is expected to be called to continue or stop the commissioning.
///
/// <p>For example:
///
/// <pre>
/// // Continue commissioning
/// deviceController.continueCommissioning(devicePtr, true)
///
/// // Stop commissioning
/// deviceController.continueCommissioning(devicePtr, false)
/// </pre>
abstract class DeviceAttestationDelegate {
  /// The callback will be invoked when device attestation completed with device info for additional
  /// verification.
  ///
  /// <p>This allows the callback to stop commissioning after examining the device info (DAC, PAI,
  /// CD).
  ///
  /// @param devicePtr Handle of device being commissioned
  /// @param attestationInfo Attestation information for the device, null is errorCode is 0.
  /// @param errorCode Error code on attestation failure. 0 if succeed.
  void onDeviceAttestationCompleted(int devicePtr, AttestationInfo? attestationInfo, int errorCode);
}

abstract class KeypairDelegate {
   // Ensure that a private key is generated when this method returns.
   //
   // @throws KeypairException if a private key could not be generated or resolved
   //
  void generatePrivateKey();

   //
   // Returns an operational PKCS#10 CSR in DER-encoded form, signed by the underlying private key.
   //
   // @throws KeypairException if the CSR could not be generated
   //
  Uint8List createCertificateSigningRequest();

   //
   // Returns the DER-encoded X.509 public key, generating a new private key if one has not already
   // been created.
   //
   // @throws KeypairException if a private key could not be resolved
   //
  Uint8List getPublicKey();

   //
   // Signs the given message with the private key (generating one if it has not yet been created)
   // using ECDSA and returns a DER-encoded signature.
   //
   // @throws KeypairException if a private key could not be resolved, or the message could not be
   //     signed
   //
  Uint8List ecdsaSignMessage(List<int> message);
}


/// An interface for receiving invoke response.
abstract class InvokeCallback {

  /// OnError will be called when an error occurs after failing to call
  ///
  /// @param Exception The IllegalStateException which encapsulated the error message, the possible
  ///     chip error could be - CHIP_ERROR_TIMEOUT: A response was not received within the expected
  ///     response timeout. - CHIP_ERROR_*TLV*: A malformed, non-compliant response was received from
  ///     the server. - CHIP_ERROR encapsulating the converted error from the StatusIB: If we got a
  ///     non-path-specific status response from the server. - CHIP_ERROR*: All other cases.
  void onError(Exception e);

  /// OnResponse will be called when a invoke response has been received and processed for the given
  /// path.
  ///
  /// @param invokeElement The invoke element in invoke response that could have null or nonNull tlv
  ///     data
  /// @param successCode If data in InvokeElment is null, successCode can be any success status,
  ///     including possibly a cluster-specific one. If data in InvokeElement is not null,
  ///     successCode will always be a generic SUCCESS(0) with no-cluster specific information
  void onResponse(InvokeElement invokeElement, int successCode);

  void onDone() {}
}

abstract class OpenCommissioningCallback {
  void onError(int status, Object? connectContext);

  void onSuccess(Object? connectContext, String manualPairingCode, String qrCode);
}

abstract class SubscriptionCallback implements ReportCallback {
  void onSubscriptionEstablished(int subscriptionId);
}

class SubscriptionCallbackWarp implements SubscriptionCallback {
  final Function(int subscriptionId)? onSubscriptionEstablishedFun;
  final Function(ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e)? onErrorFun;
  final Function()? onDoneFun;
  final Function(NodeState nodeState)? onReportFun;

  SubscriptionCallbackWarp({this.onSubscriptionEstablishedFun, this.onErrorFun, this.onDoneFun, this.onReportFun});
  
  @override
  void onDone() {
    onDoneFun?.call();
  }
  
  @override
  void onError(ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e) {
    onErrorFun?.call(attributePath, eventPath, e);
  }
  
  @override
  void onReport(NodeState nodeState) {
    onReportFun?.call(nodeState);
  }
  
  @override
  void onSubscriptionEstablished(int subscriptionId) {
    onSubscriptionEstablishedFun?.call(subscriptionId);
  }

}

abstract class ReportCallback {
    void onError(ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e);

    void onReport(NodeState nodeState);

    void onDone() {
    }
}

class ReportCallbackWarp implements ReportCallback {
  final Function(ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e)? onErrorFun;
  final Function()? onDoneFun;
  final Function(NodeState nodeState)? onReportFun;

  ReportCallbackWarp({this.onErrorFun, this.onDoneFun, this.onReportFun});
  
  @override
  void onDone() {
    onDoneFun?.call();
  }
  
  @override
  void onError(ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e) {
    onErrorFun?.call(attributePath, eventPath, e);
  }
  
  @override
  void onReport(NodeState nodeState) {
    onReportFun?.call(nodeState);
  }
}

abstract class WriteAttributesCallback {
    void onError(ChipAttributePath? attributePath, Exception e);

    void onResponse(ChipAttributePath? attributePath, Status? status);

    void onDone() {
    }
}

class WriteAttributesCallbackWarp implements WriteAttributesCallback {
  final Function(ChipAttributePath? attributePath, Exception e)? onErrorFun;
  final Function()? onDoneFun;
  final Function(ChipAttributePath? attributePath, Status? status)? onResponseFun;

  WriteAttributesCallbackWarp({this.onErrorFun, this.onDoneFun, this.onResponseFun});
  
  @override
  void onDone() {
    onDoneFun?.call();
  }
  
  @override
  void onError(ChipAttributePath? attributePath, Exception e) {
    onErrorFun?.call(attributePath, e);
  }
  
  @override
  void onResponse(ChipAttributePath? attributePath, Status? status) {
    onResponseFun?.call(attributePath, status);
  }
}

abstract class ConnectedDeviceCallback {
  void onError(Exception e);

  void onConnected(Object? context);
}

final List<ChipDeviceController> _controls = [];

ChipDeviceController? _findSameFarbicControl(ControllerParams params) {
  for (var control in _controls) {
    if (control.params.fabricId == params.fabricId &&
        listEquals(control.params.rootCertificate, params.rootCertificate)) {
      return control;
    }
  }
  return null;
}

_saveControl(ChipDeviceController control) {
  _controls.add(control);
}

_removeControl(ChipDeviceController control) {
  _controls.remove(control);
}

class ControllerParams extends TransportObject {
  final int fabricId;
  final int udpListenPort;
  final int controllerVendorId;
  final int failsafeTimerSeconds;
  final int caseFailsafeTimerSeconds;
  final bool attemptNetworkScanWiFi;
  final bool attemptNetworkScanThread;
  final bool skipCommissioningComplete;
  // final bool skipAttestationCertificateValidation;
  final String countryCode;
  final int regulatoryLocationType;
  final KeypairDelegate? keypairDelegate;
  final Uint8List? rootCertificate;
  final Uint8List? intermediateCertificate;
  final Uint8List? operationalCertificate;
  final Uint8List? ipk;
  final int adminSubject;
  final bool enableServerInteractions;
  final String setupURL;
  final int nodeId;

  ControllerParams({
    this.fabricId = 1,
    this.udpListenPort = 0,
    this.controllerVendorId = 0xFFF4,
    this.failsafeTimerSeconds = 30,
    this.caseFailsafeTimerSeconds = 30,
    this.attemptNetworkScanWiFi = false,
    this.attemptNetworkScanThread = false,
    this.skipCommissioningComplete = false,
    // this.skipAttestationCertificateValidation = false,
    this.countryCode = "",
    this.regulatoryLocationType = 0,
    this.keypairDelegate,
    this.rootCertificate,
    this.intermediateCertificate,
    this.operationalCertificate,
    this.ipk,
    this.adminSubject = 0,
    this.enableServerInteractions = false,
    this.setupURL = "",
    this.nodeId = kTestControllerNodeId,
  });
  
  @override
  String encode() {
    return jsonEncode(toJson());
  }

  toJson() => {
    "fabricId": fabricId,
    "udpListenPort": udpListenPort,
    "controllerVendorId": controllerVendorId,
    "failsafeTimerSeconds": failsafeTimerSeconds,
    "caseFailsafeTimerSeconds": caseFailsafeTimerSeconds,
    "attemptNetworkScanWiFi": attemptNetworkScanWiFi,
    "attemptNetworkScanThread": attemptNetworkScanThread,
    "skipCommissioningComplete": skipCommissioningComplete,
    "skipAttestationCertificateValidation": true,
    "countryCode": countryCode,
    "regulatoryLocationType": regulatoryLocationType,
    "keypairDelegateHandle": keypairDelegate?.hashCode.toString(),
    "rootCertificate": rootCertificate,
    "intermediateCertificate": intermediateCertificate,
    "operationalCertificate": operationalCertificate,
    "ipk": ipk,
    "adminSubject": adminSubject,
    "enableServerInteractions": enableServerInteractions,
    "setupURL": setupURL,
    "nodeId": nodeId,
  };
}

final defaultIpk = Uint8List.fromList(
  [
    't'.codeUnitAt(0), 'e'.codeUnitAt(0), 'm'.codeUnitAt(0), 'p'.codeUnitAt(0),
    'o'.codeUnitAt(0), 'r'.codeUnitAt(0), 'a'.codeUnitAt(0), 'r'.codeUnitAt(0),
    'y'.codeUnitAt(0), ' '.codeUnitAt(0), 'i'.codeUnitAt(0), 'p'.codeUnitAt(0),
    'k'.codeUnitAt(0), ' '.codeUnitAt(0), '0'.codeUnitAt(0), '1'.codeUnitAt(0)
  ]
);

class ChipDeviceController implements MethodCallHandler {

  static const matchPathList = [
    'NOCChainIssuer',
    'CompletionListener',
    'DeviceAttestationDelegate',
    'InvokeCallback',
    'SubscriptionCallback',
    'ReportCallback',
    'WriteAttributesCallback',
    'ConnectedDeviceCallback',
    'OpenCommissioningCallback'
  ];

  final ControllerParams params;
  NOCChainIssuer? _nocChainIssuer;
  CompletionListener? _completionListener;
  late MethodChannelFlutterMatter _channelFlutterMatter;
  final String? _platformDeviceControllerHandle;
  DeviceAttestationDelegate? deviceAttestationDelegate;
  String? _keypairDelegateHandleId;
  bool _isRunning = false;
  final Map<String, OpenCommissioningCallback> _openCommissioningCallbacks = {};
  final Map<String, InvokeCallback> _invokeCallbacks = {};
  final Map<String, SubscriptionCallback> _subscriptionCallbacks = {};
  final Map<String, ReportCallback> _reportCallbacks = {};
  final Map<String, WriteAttributesCallback> _writeAttributesCallback = {};
  final Map<String, ConnectedDeviceCallback> _connectedDeviceCallback = {};

  bool get isRunning => _isRunning;
  
  @override
  call(String method, arguments) {
    matterPrint('DeviceController call: $method, arguments: $arguments');
    final uri = Uri.parse(method);
    final splitPaths = uri.path.split('/').where((element) => element.trim().isNotEmpty).toList();
    final decodeArgs = jsonDecode(arguments);
    matterPrint("$runtimeType ${splitPaths.join('/')} call");
    ////// NOCChainIssuer //////
    if (splitPaths.firstOrNull == 'NOCChainIssuer') { 
      if (_nocChainIssuer == null) {
        return createPlatformCallExceptionResult(argsInvalid, 'NocChainIssuer not set!');
      }
      switch (splitPaths[1]) {
        case "onNOCChainGenerationNeeded":
          final csrInfoJson = checkCallArgNotNull(decodeArgs, 'csrInfo');
          final attestationInfoJson = checkCallArgNotNull(decodeArgs, 'attestationInfo');
          _nocChainIssuer!.onNOCChainGenerationNeeded(
            decodeArgs['onNOCChainGenerationCompleteHandle'],
            CSRInfo.decode(csrInfoJson), 
            AttestationInfo.decode(attestationInfoJson)
          );
          return createPlatformCallSuccessResult();
      }
      return createPlatformCallExceptionResult(methodNoFound, 'Not found $method');
    } 
    ////// CompletionListener //////
    else if (splitPaths.firstOrNull == 'CompletionListener') {
      if (_completionListener == null) {
        return createPlatformCallExceptionResult(argsInvalid, "CompletionListener not set");
      }
      switch (splitPaths[1]) {
        case 'onConnectDeviceComplete':
          _completionListener!.onConnectDeviceComplete();
          return createPlatformCallSuccessResult();
        case 'onStatusUpdate':
          _completionListener!.onStatusUpdate(checkCallArgNotNull(decodeArgs, 'status'));
          return createPlatformCallSuccessResult();
        case 'onPairingComplete':
          _completionListener!.onPairingComplete(checkCallArgNotNull(decodeArgs, 'errorCode'));
          return createPlatformCallSuccessResult();
        case 'onPairingDeleted':
          _completionListener!.onPairingDeleted(checkCallArgNotNull(decodeArgs, 'errorCode'));
          return createPlatformCallSuccessResult();
        case 'onCommissioningComplete':
          _completionListener!.onCommissioningComplete(decodeArgs["nodeId"], checkCallArgNotNull(decodeArgs, 'errorCode'));
          return createPlatformCallSuccessResult();
        case 'onReadCommissioningInfo': 
          _completionListener!.onReadCommissioningInfo(
            checkCallArgNotNull(decodeArgs, 'vendorId'),
             checkCallArgNotNull(decodeArgs, 'productId'),
             checkCallArgNotNull(decodeArgs, 'wifiEndpointId'),
             checkCallArgNotNull(decodeArgs, 'threadEndpointId'),
          );
          return createPlatformCallSuccessResult();
        case 'onCommissioningStatusUpdate':
          _completionListener!.onCommissioningStatusUpdate(
            checkCallArgNotNull(decodeArgs, 'nodeId'),
            checkCallArgNotNull(decodeArgs, 'stage'),
            checkCallArgNotNull(decodeArgs, 'errorCode'),
          );
          return createPlatformCallSuccessResult();
        case 'onNotifyChipConnectionClosed':
          _completionListener!.onNotifyChipConnectionClosed();
          return createPlatformCallSuccessResult();
        case 'onCloseBleComplete':
          // _completionListener!.onCloseBleComplete();
          return createPlatformCallSuccessResult();
        case 'onError':
          _completionListener!.onError(Exception(checkCallArgNotNull(decodeArgs, 'error')));
          return createPlatformCallSuccessResult();
        case 'onOpCSRGenerationComplete':
          _completionListener!.onOpCSRGenerationComplete(
              toUint8List(checkCallArgNotNull(decodeArgs, 'csr')),
          );
          return createPlatformCallSuccessResult();
        case 'onICDRegistrationInfoRequired':
          _completionListener!.onICDRegistrationInfoRequired();
          return createPlatformCallSuccessResult();
      }
    } 
    ////// DeviceAttestationDelegate //////
    else if (splitPaths.firstOrNull == 'DeviceAttestationDelegate') {
      switch (splitPaths[1]) {
        case "onDeviceAttestationCompleted":
          deviceAttestationDelegate?.onDeviceAttestationCompleted(
            checkCallArgNotNull(decodeArgs, "devicePtr"),
            decodeArgs["attestationInfo"] == null ? null : AttestationInfo.decode(decodeArgs["attestationInfo"]),
            checkCallArgNotNull(decodeArgs, "errorCode")
          );
          return createPlatformCallSuccessResult();
      }
    } 
    ////// InvokeCallback //////
    else if (splitPaths.firstOrNull == 'InvokeCallback') {
      String invokeCallbackPoint = checkCallArgNotNull(decodeArgs, 'invokeCallbackPoint');
      final callback = _invokeCallbacks[invokeCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid, "Not found invoke callback by point $invokeCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onDone":
          try {
            callback.onDone();
          } catch (e) {
            matterPrint('$runtimeType invoke callback onDone error $e');
          }          
          return createPlatformCallSuccessResult();
        case "onResponse":
          try {
            callback.onResponse(
              InvokeElement.fromJson(checkCallArgNotNull(decodeArgs, "invokeElement")),
              checkCallArgNotNull(decodeArgs, "successCode")
            );
          } catch (e) {
            matterPrint('$runtimeType invoke callback onResponse error $e');
          } 
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
              Exception(checkCallArgNotNull(decodeArgs, "error"))
            );
          } catch (e) {
            matterPrint('$runtimeType invoke callback onError error $e');
          } 
          return createPlatformCallSuccessResult();
      }
    }
    ///// SubscriptionCallback //////
    else if (splitPaths.firstOrNull == 'SubscriptionCallback') {
      String subscriptionCallbackPoint = checkCallArgNotNull(decodeArgs, 'subscriptionCallbackPoint');
      final callback = _subscriptionCallbacks[subscriptionCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid, "Not found invoke callback by point $subscriptionCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onSubscriptionEstablished":
          try {
            callback.onSubscriptionEstablished(
              checkCallArgNotNull(decodeArgs, 'subscriptionId')
            );
          } catch (e) {
            return createPlatformCallExceptionResult(argsInvalid, "Error in callback: $e");
          }
          break;
        case "onReport":
          try {
            callback.onReport(
              NodeState.fromJson(checkCallArgNotNull(decodeArgs, "nodeState"))
            );
          } catch (e) {
            matterPrint('subscription callback onReport error $e');
          } 
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
              null, null,
              Exception(checkCallArgNotNull(decodeArgs, "error"))
            );
          } catch(e) {
            matterPrint('subscription callback onError error $e');
          }
          return createPlatformCallSuccessResult();
        case "onDone":
          try {
            callback.onDone();
          } catch(e) {
            matterPrint('subscription callback onDone error $e');
          }
          _subscriptionCallbacks.remove(subscriptionCallbackPoint);
          return createPlatformCallSuccessResult();
      }
    }
    ///// ReportCallback //////
    else if (splitPaths.firstOrNull == 'ReportCallback') {
      String reportCallbackPoint = checkCallArgNotNull(decodeArgs, 'reportCallbackPoint');
      final callback = _reportCallbacks[reportCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid, "Not found invoke callback by point $reportCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onReport":
          try {
            callback.onReport(
              NodeState.fromJson(checkCallArgNotNull(decodeArgs, "nodeState"))
            );
          } catch (e, s) {
            matterPrint('ReportCallback onReport error $e');
            print(s);
          } 
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
              null, null,
              Exception(checkCallArgNotNull(decodeArgs, "error"))
            );
          } catch(e) {
            matterPrint('ReportCallback onError error $e');
          }
          return createPlatformCallSuccessResult();
        case "onDone":
          try {
            callback.onDone();
          } catch(e) {
            matterPrint('ReportCallback onDone error $e');
          }
          _reportCallbacks.remove(reportCallbackPoint);
          return createPlatformCallSuccessResult();
      }
    }
    ///// WriteAttributesCallback //////
    else if (splitPaths.firstOrNull == 'WriteAttributesCallback') {
      String writeAttributesCallbackPoint = checkCallArgNotNull(decodeArgs, 'writeAttributesCallbackPoint');
      final callback = _writeAttributesCallback[writeAttributesCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid, "Not found invoke callback by point $writeAttributesCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onResponse":
          try {
            callback.onResponse(
              decodeArgs["attributePath"] == null ? null : ChipAttributePath.fromJson(decodeArgs["attributePath"]),
              decodeArgs["status"] == null ? null : Status.fromJson(decodeArgs["status"])
            );
          } catch (e) {
            matterPrint('WriteAttributesCallback onReport error $e');
          } 
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
              decodeArgs["attributePath"] == null ? null : ChipAttributePath.fromJson(decodeArgs["attributePath"]),
              Exception(decodeArgs['error'] ?? 'Unknown Error')
            );
          } catch(e) {
            matterPrint('WriteAttributesCallback onError error $e');
          }
          return createPlatformCallSuccessResult();
        case "onDone":
          try {
            callback.onDone();
          } catch(e) {
            matterPrint('WriteAttributesCallback onDone error $e');
          }
          _writeAttributesCallback.remove(writeAttributesCallbackPoint);
          return createPlatformCallSuccessResult();
      }
    }
    ///// ConnectedDeviceCallback /////
    else if (splitPaths.firstOrNull == "ConnectedDeviceCallback") {
      String callbackHandle = checkCallArgNotNull(decodeArgs, 'callbackHandle');
      final callback = _connectedDeviceCallback[callbackHandle];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid, "Not found invoke callback by point $callbackHandle");
      }
      switch (splitPaths[1]) {
        case "onDeviceConnected":
          try {
            callback.onConnected(decodeArgs['context']);
          } catch(e) {
            matterPrint('connected device callback onConnectionClosed error $e');
          }
          _connectedDeviceCallback.remove(callbackHandle);
          return createPlatformCallSuccessResult();
        case "onConnectionFailure":
          try {
            callback.onError(Exception(decodeArgs['error'] ?? "Unknown error"));
          } catch(e) {
            matterPrint('connected device callback onDisconnectionError error $e');
          }
          _connectedDeviceCallback.remove(callbackHandle);
          return createPlatformCallSuccessResult();
      }
    }

    ///// OpenCommissioningCallback ///// 
    else if (splitPaths.firstOrNull == "OpenCommissioningCallback") {
      String callbackHandle = checkCallArgNotNull(decodeArgs, 'callbackHandle');
      final callback = _openCommissioningCallbacks[callbackHandle]; 
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid, "Not found invoke callback by callbackHandle $callbackHandle");
      }
      switch (splitPaths[1]) {
        case "onSuccess":
          try {
            callback.onSuccess(
              decodeArgs['connectContext'],
              checkCallArgNotNull(decodeArgs, 'manualPairingCode'), 
              checkCallArgNotNull(decodeArgs, 'qrCode'), 
            );
          } catch(e) {
            matterPrint('open commissioning callback onOpenCommissioningWindow error $e');
          }
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
              checkCallArgNotNull(decodeArgs, "status") as int,
              decodeArgs['connectContext']
            );
          } catch(e) {
            matterPrint('open commissioning callback onOpenCommissioningWindow error $e');
          }
          return createPlatformCallSuccessResult();
      }
    }

    return PlatformCallResult(code: methodNoFound, resultJson: jsonEncode({"msg": 'Not found method $uri'})); 
  }
  
  @override
  bool match(String method, arguments) {
    try {
      final uri = Uri.parse(method);
      final splitPaths = uri.path.split('/').where((element) => element.trim().isNotEmpty).toList();
      final handleId = jsonDecode(arguments)[jsonKeyHandle];
      final isMatch = handleId == _platformDeviceControllerHandle && uri.host == _hostName && matchPathList.contains(splitPaths.firstOrNull);
      matterPrint('ChipDeviceController($_platformDeviceControllerHandle) match $isMatch');
      return isMatch;
    } catch (e, s) {
      matterPrint('$runtimeType match error $s') ;
    }
    return false;
  }

  ChipDeviceController._(this.params, this._platformDeviceControllerHandle, this._keypairDelegateHandleId) {
    _channelFlutterMatter = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
    _channelFlutterMatter.addHandler(this);
    _isRunning = true;
  }

  /// Create a [ChipDeviceController]; if exist return the exist one or create a new one.
  static Future<ChipDeviceController> newControllerIfNotExist(ControllerParams params) async {
    ChipDeviceController? controller = _findSameFarbicControl(params);
    if (controller != null) {
      return controller;
    }

    final channelFlutterMatter = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
    String? keypairDelegateHandleId;
    if (params.keypairDelegate != null) {
      keypairDelegateHandleId = _keypairDelegateCallbackHandler.addHandler(params.keypairDelegate!);
    }
    final result = await channelFlutterMatter.requestPlatform(
      RequestPlatformParams(methodName: createRequestPlatformUrl(_hostName, 'new').toString(), methodParamsJson: params.encode()));
    if (result.code != 0) {
      throw Exception("newDeviceController failed(${result.code})");
    }
    matterPrint('newController ${result.jsonData}');
    controller = ChipDeviceController._(params, result.jsonData[jsonKeyHandle], keypairDelegateHandleId);
    _saveControl(controller);
    return controller;
  }

  void destroy() {
    _channelFlutterMatter.removeHandler(this);
    if (_keypairDelegateHandleId != null) {
      _keypairDelegateCallbackHandler.removeHandler(_keypairDelegateHandleId!);
    }
    _invokeCallbacks.clear();
    _subscriptionCallbacks.clear();
    _reportCallbacks.clear();
    _writeAttributesCallback.clear();
    _removeControl(this);
    _isRunning = false;
  }

  Future<Map<String, dynamic>?> _requestPlatform(String methodName, String methodParamsJson) async {
    final result = await _channelFlutterMatter.requestPlatform(
      RequestPlatformParams(methodName: createRequestPlatformUrl(_hostName, methodName), methodParamsJson: methodParamsJson));
    if (result.code == 0) {
      return result.jsonData;
    }
    throw CallPlatformException("[${result.code}] Call $methodName params $methodParamsJson failed");
  }


  /// Sets this DeviceController to use the given issuer for issuing operational certs and verifying
  /// the DAC. By default, the DeviceController uses an internal, OperationalCredentialsDelegate
  Future<void> setNocChainIssuer(NOCChainIssuer nocChainIssuer) async {
    _nocChainIssuer = nocChainIssuer;
    await _requestPlatform('setNocChainIssuer', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle
    }));
  }

  // Future<void> setCompletionListener(CompletionListener listener) async {
  //   _completionListener = listener;
  //   await _requestPlatform('setCompletionListener', jsonEncode({
  //     jsonKeyHandle: _platformDeviceControllerHandle
  //   }));
  // }


  /// when [attestationDelegate] notnull, [failSafeExpiryTimeoutSecs] efficient 
  /// IOS must use onboardingPayload
  Future<void> pairDevice(
      int deviceId,
      int? connId,
      int? setupPincode,
      String? onboardingPayload,
      Uint8List? csrNonce,
      NetworkCredentials networkCredentials,
      {DeviceAttestationDelegate? attestationDelegate,
      CompletionListener? completionListener,
      int failSafeExpiryTimeoutSecs = 60,
      String displayName = 'Flutter Matter', //only for iOS
      String ecosystemName = 'FlutterEcosystem' //only for iOS
    }) async {

      if (setupPincode == null && onboardingPayload == null) {
        throw Exception("setupPincode or onboardingPayload must be provided");
      }

      if (Platform.isIOS && onboardingPayload == null) {
        throw Exception("onboardingPayload must be provided on iOS");
      }
      
    // if (attestationDelegate != null) {
      this.deviceAttestationDelegate = attestationDelegate;
    // }
    // if (completionListener != null) {
      this._completionListener = completionListener;
    // }
    await _requestPlatform('pairDevice', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
      'connId': connId,
      'deviceId': deviceId,
      'setupPincode': setupPincode,
      'csrNonce': csrNonce == null ? null : List.from(csrNonce),
      'networkCredentials': networkCredentials.toJson(),
      'attestationDelegate': attestationDelegate.hashCode.toString(),
      'failSafeExpiryTimeoutSecs': failSafeExpiryTimeoutSecs,
      'completionListener': completionListener?.hashCode.toString(),
      'onboardingPayload': onboardingPayload,
      'displayName': displayName,
      'ecosystemName': ecosystemName,
    }));
  }

  Future<void> stopDevicePairing(int deviceId) async {
    await _requestPlatform('stopDevicePairing', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
      "deviceId": deviceId
    }));
  }

  /// Create a root (self-signed) X.509 DER encoded certificate
  static Future<Uint8List> createRootCertificate(
    KeypairDelegate keypair, int issuerId, int? fabricId) async {
      final id = _keypairDelegateCallbackHandler.addHandler(keypair);
      final channel = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
      final result = await channel.requestPlatform(
        RequestPlatformParams(
          methodName: createRequestPlatformUrl(_hostName, 'createRootCertificate'), 
          methodParamsJson: jsonEncode({
            // jsonKeyHandle: _platformDeviceControllerHandle,
            'keypairHandle': id,
            'issuerId': issuerId,
            'fabricId': fabricId
          })
        )
      ).whenComplete(() {
        _keypairDelegateCallbackHandler.removeHandler(id);
      });
      if (result.code != 0) {
        throw Exception("createRootCertificate failed(${result.code})");
      }
    return toUint8List(result.jsonData['data']);
  }


  /// Create an X.509 DER encoded certificate that has the right fields to be a valid Matter
  /// operational certificate.
  static Future<Uint8List>  createOperationalCertificate(
      KeypairDelegate signingKeypair,
      Uint8List signingCertificate,
      Uint8List operationalPublicKey,
      int fabricId,
      int nodeId,
      List<int>? caseAuthenticatedTags) async {
        final id = _keypairDelegateCallbackHandler.addHandler(signingKeypair);
        final channel = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
        final result = await channel.requestPlatform(
          RequestPlatformParams(
            methodName: createRequestPlatformUrl(_hostName, 'createOperationalCertificate'), 
            methodParamsJson: jsonEncode({
          // jsonKeyHandle: id,
          'signingCertificate': List.from(signingCertificate),
          'keypairHandle': id,
          'operationalPublicKey': List.from(operationalPublicKey),
          'fabricId': fabricId,
          'nodeId': nodeId,
          'caseAuthenticatedTags': caseAuthenticatedTags == null ? null : List.from(caseAuthenticatedTags),
        }))).whenComplete(() {
          _keypairDelegateCallbackHandler.removeHandler(id);
        });
        if (result.code != 0) {
        throw Exception("createOperationalCertificate failed(${result.code})");
      }
        return toUint8List(result.jsonData['data']);
  }

  /// Extract the public key from the given PKCS#10 certificate signing request. This is the public
  /// key that a certificate issued in response to the request would need to have.
  Future<Uint8List> publicKeyFromCSR(Uint8List csr) async {
    final result = await _requestPlatform('publicKeyFromCSR', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
      'csr': List.from(csr)
    }));
    return toUint8List(result!['data']);
  }

  /// When a NOCChainIssuer is set for this controller, then onNOCChainGenerationNeeded will be
  /// called when the NOC CSR needs to be signed. This allows for custom credentials issuer
  /// implementations, for example, when a proprietary cloud API will perform the CSR signing.
  Future<int> onNOCChainGeneration(ControllerParams params, {String? onNOCChainGenerationCompleteHandle}) async {
    final result = await _requestPlatform('onNOCChainGeneration', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
      'params': params.toJson(),
      'onNOCChainGenerationCompleteHandle': onNOCChainGenerationCompleteHandle
    }));
    return result!['data'] as int;
  }

  /// This function instructs the commissioner to proceed to the next stage of commissioning after
  /// attestation is reported.
  ///
  /// @param devicePtr a pointer to the device which is being commissioned.
  /// @param ignoreAttestationFailure whether to ignore device attestation failure.
  Future<void> continueCommissioning(int devicePtr, bool ignoreAttestationFailure) async {
    await _requestPlatform('continueCommissioning', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
      'devicePtr': devicePtr,
      'ignoreAttestationFailure': ignoreAttestationFailure
    }));
  }

  // Future<void> setDeviceAttestationDelegate(int failSafeExpiryTimeoutSecs, DeviceAttestationDelegate deviceAttestationDelegate) async {
  //   if (this.deviceAttestationDelegate != null) {
  //     throw Exception("deviceAttestationDelegate already set");
  //   }
  //   this.deviceAttestationDelegate = deviceAttestationDelegate;
  //   await _requestPlatform('setDeviceAttestationDelegate', jsonEncode({
  //     jsonKeyHandle: _platformDeviceControllerHandle,
  //     'failSafeExpiryTimeoutSecs': failSafeExpiryTimeoutSecs,
  //   }));
  // }

  Future<void> deleteDeviceController() async {
    await _requestPlatform('deleteDeviceController', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
    }));
    destroy();
  }

  Future<void> invoke(InvokeCallback callback, int nodeId, InvokeElement invokeElement, {Object? connectContext, int timedRequestTimeoutMs = 0, int imTimeoutMs = 0}) async {
    String callbackId = callback.hashCode.toString();
    _invokeCallbacks[callbackId] = callback;
    try {
      await _requestPlatform("invoke", jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
        'callback': callbackId,
        'nodeId': nodeId,
        'invokeElement': invokeElement.toJson(),
        'timedRequestTimeoutMs': timedRequestTimeoutMs,
        'imTimeoutMs': imTimeoutMs,
        'connectContext': connectContext
      }));
    } catch (e) {
      _invokeCallbacks.remove(callbackId);
    }
  }

  Future<void> subscribe(
    int nodeId, 
    SubscriptionCallback callback, 
    // int devicePtr, 
    List<ChipAttributePath>? attributePaths, 
    List<ChipEventPath>? eventPaths, 
    // List<DataVersionFilter>? dataVersionFilters, 
    int minInterval, 
    int maxInterval, 
    bool keepSubscriptions, 
    bool isFabricFiltered, 
    int imTimeoutMs, 
    int eventMin,
    {Object? connectContext}
  ) async {
    String callbackHandle = callback.hashCode.toString();
    _subscriptionCallbacks[callbackHandle] = callback;
    try {
      await _requestPlatform('subscribe', jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
        'nodeId': nodeId,
        // 'devicePtr': devicePtr,
        'callbackHandle': callbackHandle,
        'attributePaths': attributePaths?.map((e) => e.toJson()).toList(),
        'eventPaths': eventPaths?.map((e) => e.toJson()).toList(),
        // 'dataVersionFilters': dataVersionFilters?.map((e) => e.toJson()).toList(),
        'minInterval': minInterval,
        'maxInterval': maxInterval,
        'keepSubscriptions': keepSubscriptions,
        'isFabricFiltered': isFabricFiltered,
        'imTimeoutMs': imTimeoutMs,
        'eventMin': eventMin,
        'connectContext': connectContext
      })); 
    } catch(e, s) {
      print(s);
      _subscriptionCallbacks.remove(callbackHandle);
    }
  }

  Future<void> read(
    int nodeId, 
    ReportCallback callback, 
    // int devicePtr, 
    List<ChipAttributePath>? attributePaths, 
    List<ChipEventPath>? eventPaths, 
    List<DataVersionFilter>? dataVersionFilters, 
    bool isFabricFiltered, 
    int imTimeoutMs, 
    int eventMin,
    {Object? connectContext}) async {
      String callbackHandle = callback.hashCode.toString();
      _reportCallbacks[callbackHandle] = callback;
      try {
        await _requestPlatform('read', jsonEncode({
          jsonKeyHandle: _platformDeviceControllerHandle,
          'nodeId': nodeId,
          'callbackHandle': callbackHandle,
          'attributePaths': attributePaths?.map((e) => e.toJson()).toList(),
          'eventPaths': eventPaths?.map((e) => e.toJson()).toList(),
          'dataVersionFilters': dataVersionFilters?.map((e) => e.toJson()).toList(),
          'isFabricFiltered': isFabricFiltered,
          'imTimeoutMs': imTimeoutMs,
          'eventMin': eventMin,
          'connectContext': connectContext,
        }));
      } catch(e, s) {
        print(s);
        _reportCallbacks.remove(callbackHandle);
      }
    }

  Future<void> write(
    int nodeId,
    WriteAttributesCallback callback, 
    // int devicePtr, 
    List<AttributeWriteRequest> attributeList, 
    int timedRequestTimeoutMs, 
    int imTimeoutMs,
    {Object? connectContext}
  ) async {
    String callbackHandle = callback.hashCode.toString();
    _writeAttributesCallback[callbackHandle] = callback;
    try {
      await _requestPlatform('write', jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
        'nodeId': nodeId,
        'callbackHandle': callbackHandle,
        // 'devicePtr': devicePtr,
        'attributeList': attributeList.map((e) => e.toJson()).toList(),
        'timedRequestTimeoutMs': timedRequestTimeoutMs,
        'imTimeoutMs': imTimeoutMs,
        'connectContext': connectContext,
      }));
    } catch (e, s) {
      print(s);
      _writeAttributesCallback.remove(callbackHandle);
    }
  }

  Future<void> connectedDevice(int nodeId, ConnectedDeviceCallback callback, {Object? connectContext}) async {
    String callbackHandle = callback.hashCode.toString();
    _connectedDeviceCallback[callbackHandle] = callback;
    try {
      await _requestPlatform('connectedDevice', jsonEncode({
        'nodeId': nodeId,
        jsonKeyHandle: _platformDeviceControllerHandle,
        'callbackHandle': callbackHandle,
        'connectContext': connectContext,
      }));
    } catch (e) {
      matterPrint('$e');
      _connectedDeviceCallback.remove(callbackHandle);
    }
  }

  Future<void> releaseConnectContext(Object connectContext) async {
    await _requestPlatform('releaseConnectContext', jsonEncode({
      jsonKeyHandle: _platformDeviceControllerHandle,
      'connectContext': connectContext,
    }));
  }

  Future<bool> openPairingWindowWithPIN(
          Object connectContext,
          int duration,
          int discriminator,
          int setupPIN,
          OpenCommissioningCallback callback
  ) async {
    final callbackId = callback.hashCode.toString();
    _openCommissioningCallbacks[callbackId] = callback;
    try {  
      final result = await _requestPlatform('openPairingWindowWithPIN', jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
        'connectContext': connectContext,
        'duration': duration,
        'discriminator': discriminator,
        'setupPIN': setupPIN,
        'callbackHandle': callbackId
      }));
      return result?['data'] == true;
    } catch (e) {
      _openCommissioningCallbacks.remove(callbackId);
    }
    return false;
  }

  // Future<bool> unPairDevice(int nodeId) async {
  //   try {  
  //     final result = await _requestPlatform('unPairDevice', jsonEncode({
  //       jsonKeyHandle: _platformDeviceControllerHandle,
  //       'nodeId': nodeId,
  //     }));
  //     return result?['data'] == true;
  //   } catch (e) {
  //     return false;
  //   }
  // }

  Future<int?> getFabricIndex() async {
    try {
      final result = await _requestPlatform('getFabricIndex', jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
      }));
      return result?['data'];
    } catch (e) {
      return null;
    }
  }

  Future<bool> unSubscription(int fabricIndex, int nodeId, int subscriptionId) async {
    try {
      final result = await _requestPlatform('unSubscribe', jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
        "fabricIndex": fabricIndex,
        "nodeId": nodeId,
        "subscriptionId": subscriptionId,
      }));
      return result?['data'] == true;
    } catch (e) {
      return false;
    }
  }
}