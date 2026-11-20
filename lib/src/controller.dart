import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/foundation.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/platform_transport_types.dart';
import 'package:flutter_matter/src/callback_handler.dart';
import 'package:flutter_matter/src/constant.dart';
import 'package:flutter_matter/src/utils.dart';

import 'exception.dart';
import 'model/icd_device_info.dart';
import 'model/attribute_write_request.dart';
import 'model/chip_attribute_path.dart';
import 'model/chip_event_path.dart';
import 'model/data_version_filter.dart';
import 'model/invoke_element.dart';
import 'model/node_state.dart';
import 'model/status.dart';

export 'exception.dart'
    show ControllerLifecycleException, ControllerLifecycleFailure;

const _hostName = 'devicecontroller';

const kTestControllerNodeId = 112233;

/// Wi-Fi network credentials used during commissioning.
///
/// An empty [password] represents an open network.
class WiFiCredentials {
  final String ssid;
  final String password;

  WiFiCredentials({required this.ssid, required this.password});
}

/// Credentials for a Thread network. The [operationalDataset] is the
/// Thread Active Operational Dataset encoded as a byte array (TLV).
class ThreadCredentials {
  final Uint8List operationalDataset;

  ThreadCredentials({required this.operationalDataset});
}

/// Holds the network credentials for commissioning.
/// Exactly one of [wifiCredentials] or [threadCredentials] must be set.
class NetworkCredentials implements TransportObject {
  final WiFiCredentials? wifiCredentials;
  final ThreadCredentials? threadCredentials;

  NetworkCredentials.wifi(WiFiCredentials wifi)
      : wifiCredentials = wifi,
        threadCredentials = null;

  NetworkCredentials.thread(ThreadCredentials thread)
      : wifiCredentials = null,
        threadCredentials = thread;

  /// Legacy constructor kept for backward compatibility — WiFi only.
  NetworkCredentials({required WiFiCredentials wifiCredentials})
      : wifiCredentials = wifiCredentials,
        threadCredentials = null;

  @override
  String encode() {
    return jsonEncode(toJson());
  }

  toJson() {
    if (threadCredentials != null) {
      return {
        'threadCredentials': {
          'operationalDataset':
              List<int>.from(threadCredentials!.operationalDataset),
        }
      };
    }
    return {
      'wifiCredentials': {
        'ssid': wifiCredentials!.ssid,
        'password': wifiCredentials!.password,
      }
    };
  }
}

/// Device attestation data supplied to [DeviceAttestationDelegate].
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

  AttestationInfo(
      {required this.challenge,
      required this.nonce,
      required this.elements,
      required this.elementsSignature,
      required this.dac,
      required this.pai,
      required this.certificationDeclaration,
      required this.firmwareInfo,
      required this.vendorId,
      required this.productId});

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
        productId: json['productId'] as int);
  }
}

class KeypairDelegateCallbackHandler extends CallbackHandler<KeypairDelegate> {
  KeypairDelegateCallbackHandler() : super();

  @override
  onCallbackMethodCall(String methodName, arguments) {
    final decoded = jsonDecode(arguments);
    if (decoded is! Map) {
      throw ArgumentError.value(
        decoded,
        'arguments',
        'Keypair callback arguments must be a JSON object',
      );
    }
    final decodeArgs = decoded;
    final callbackContext = '$runtimeType.onCallbackMethodCall';
    final handle = checkCallArgNotNull(
      decodeArgs,
      'handle',
      context: callbackContext,
    ).toString();
    KeypairDelegate? kd = handlers[handle];
    if (kd == null) {
      final errorMsg = 'Not found delegate for handle: $handle';
      reportMatterError(callbackContext, StateError(errorMsg));
      return createPlatformCallExceptionResult(argsInvalid, errorMsg);
    }
    matterPrint('$runtimeType $methodName call');
    switch (methodName) {
      case 'GeneratePrivateKey':
        kd.generatePrivateKey();
        return createPlatformCallSuccessResult();
      case 'EcdsaSignMessage':
        final signData =
            kd.ecdsaSignMessage(jsonDecode(arguments)['message'].cast<int>());
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'ecdsaSign': List.from(signData)}));
      case 'GetPublicKey':
        final publicKey = kd.getPublicKey();
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'publicKey': List.from(publicKey)}));
      case 'CreateCertificateSigningRequest':
        final csr = kd.createCertificateSigningRequest();
        return createPlatformCallSuccessResult(
            successMsg:
                jsonEncode({'certificateSigningRequest': List.from(csr)}));
      default:
        return createPlatformCallExceptionResult(
          methodNoFound,
          'Not found method $methodName',
        );
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

  CSRInfo(
      {required this.nonce,
      required this.elements,
      required this.elementsSignature,
      required this.csr});

  factory CSRInfo.decode(Map json) {
    return CSRInfo(
        nonce: Uint8List.fromList((json['nonce'] as List<dynamic>).cast<int>()),
        elements:
            Uint8List.fromList((json['elements'] as List<dynamic>).cast<int>()),
        elementsSignature: Uint8List.fromList(
            (json['elementsSignature'] as List<dynamic>).cast<int>()),
        csr: Uint8List.fromList((json['csr'] as List<dynamic>).cast<int>()));
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

  /// Notifies when the registration flow for the ICD completes (Matter 1.2+).
  ///
  /// [errorCode] is 0 on success, non-zero on failure.
  /// [icdDeviceInfo] contains the ICD device information on success; may be null on error.
  void onICDRegistrationComplete(int errorCode, ICDDeviceInfo? icdDeviceInfo);
}

/// Interface to implement custom operational credentials issuer (NOC chain generation).
abstract class NOCChainIssuer {
  // When a NOCChainIssuer is set for this controller, then onNOCChainGenerationNeeded will be
  // called when the DAC chain must be verified and NOC chain needs to be issued from a CSR. This
  // allows for custom credentials issuer and DAC verifier implementations, for example, when a
  // proprietary cloud API will perform DAC verification and the NOC chain issuance from CSR.
  void onNOCChainGenerationNeeded(String? onNOCChainGenerationCompleteHandle,
      CSRInfo csrInfo, AttestationInfo attestationInfo);
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
  void onDeviceAttestationCompleted(
      int devicePtr, AttestationInfo? attestationInfo, int errorCode);
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

/// Receives the result of [ChipDeviceController.openPairingWindowWithPIN].
abstract class OpenCommissioningCallback {
  void onError(int status, Object? connectContext);

  void onSuccess(
      Object? connectContext, String manualPairingCode, String qrCode);
}

/// Receives subscription establishment and report callbacks.
abstract class SubscriptionCallback implements ReportCallback {
  void onSubscriptionEstablished(int subscriptionId);
}

class SubscriptionCallbackWarp implements SubscriptionCallback {
  final Function(int subscriptionId)? onSubscriptionEstablishedFun;
  final Function(ChipAttributePath? attributePath, ChipEventPath? eventPath,
      Exception e)? onErrorFun;
  final Function()? onDoneFun;
  final Function(NodeState nodeState)? onReportFun;

  SubscriptionCallbackWarp(
      {this.onSubscriptionEstablishedFun,
      this.onErrorFun,
      this.onDoneFun,
      this.onReportFun});

  @override
  void onDone() {
    onDoneFun?.call();
  }

  @override
  void onError(
      ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e) {
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

/// Receives reports and errors for a read or subscription.
abstract class ReportCallback {
  void onError(
      ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e);

  void onReport(NodeState nodeState);

  void onDone() {}
}

class ReportCallbackWarp implements ReportCallback {
  final Function(ChipAttributePath? attributePath, ChipEventPath? eventPath,
      Exception e)? onErrorFun;
  final Function()? onDoneFun;
  final Function(NodeState nodeState)? onReportFun;

  ReportCallbackWarp({this.onErrorFun, this.onDoneFun, this.onReportFun});

  @override
  void onDone() {
    onDoneFun?.call();
  }

  @override
  void onError(
      ChipAttributePath? attributePath, ChipEventPath? eventPath, Exception e) {
    onErrorFun?.call(attributePath, eventPath, e);
  }

  @override
  void onReport(NodeState nodeState) {
    onReportFun?.call(nodeState);
  }
}

/// Receives write results and errors for attribute paths.
abstract class WriteAttributesCallback {
  void onError(ChipAttributePath? attributePath, Exception e);

  void onResponse(ChipAttributePath? attributePath, Status? status);

  void onDone() {}
}

class WriteAttributesCallbackWarp implements WriteAttributesCallback {
  final Function(ChipAttributePath? attributePath, Exception e)? onErrorFun;
  final Function()? onDoneFun;
  final Function(ChipAttributePath? attributePath, Status? status)?
      onResponseFun;

  WriteAttributesCallbackWarp(
      {this.onErrorFun, this.onDoneFun, this.onResponseFun});

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

/// Receives the result of a CASE connection request.
abstract class ConnectedDeviceCallback {
  void onError(Exception e);

  void onConnected(Object? context);
}

/// Native controller configuration for one Matter fabric.
///
/// Reuse the same [fabricId] and [rootCertificate] to reuse an existing
/// controller through [ChipDeviceController.newControllerIfNotExist].
///
/// The current JSON payload sets `skipAttestationCertificateValidation` to
/// `true`; review that security-sensitive native-configuration limit before
/// production use.
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
        "nodeId": nodeId,
      };
}

final defaultIpk = Uint8List.fromList([
  't'.codeUnitAt(0),
  'e'.codeUnitAt(0),
  'm'.codeUnitAt(0),
  'p'.codeUnitAt(0),
  'o'.codeUnitAt(0),
  'r'.codeUnitAt(0),
  'a'.codeUnitAt(0),
  'r'.codeUnitAt(0),
  'y'.codeUnitAt(0),
  ' '.codeUnitAt(0),
  'i'.codeUnitAt(0),
  'p'.codeUnitAt(0),
  'k'.codeUnitAt(0),
  ' '.codeUnitAt(0),
  '0'.codeUnitAt(0),
  '1'.codeUnitAt(0)
]);

/// Stateful Matter controller for one fabric.
///
/// A controller owns native commissioning and connection state. Keep it alive
/// for the lifetime of the fabric session. Prefer [close] for balanced release
/// of an acquired controller. [deleteDeviceController] is a compatibility
/// alias, while [destroy] performs local cleanup only.
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
  late FlutterMatterPlatform _channelFlutterMatter;
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
  final Completer<void> _closedCompleter = Completer<void>();
  bool _isClosed = false;

  bool get isRunning => _isRunning;

  /// Completes when this Dart handle is closed, destroyed, or superseded by a
  /// controller switch.
  ///
  /// Completion is independent of native shutdown success. Await the future
  /// returned by [close] or [deleteDeviceController] for that result.
  Future<void> get closed => _closedCompleter.future;

  @override
  call(String method, arguments) {
    if (_isClosed) {
      return createPlatformCallExceptionResult(
        argsInvalid,
        'Controller is closed',
      );
    }
    matterPrint('DeviceController call: $method');
    final uri = Uri.parse(method);
    final splitPaths = uri.path
        .split('/')
        .where((element) => element.trim().isNotEmpty)
        .toList();
    if (splitPaths.length < 2) {
      return createPlatformCallExceptionResult(
        methodNoFound,
        'Device controller callback path must include a callback type and method',
      );
    }
    final decoded = jsonDecode(arguments);
    if (decoded is! Map) {
      throw ArgumentError.value(
        decoded,
        'arguments',
        'Device controller callback arguments must be a JSON object',
      );
    }
    final decodeArgs = decoded;
    final callbackContext = '$runtimeType ${splitPaths.join('/')}';
    matterPrint("$runtimeType ${splitPaths.join('/')} call");
    ////// NOCChainIssuer //////
    if (splitPaths.firstOrNull == 'NOCChainIssuer') {
      if (_nocChainIssuer == null) {
        return createPlatformCallExceptionResult(
            argsInvalid, 'NocChainIssuer not set!');
      }
      switch (splitPaths[1]) {
        case "onNOCChainGenerationNeeded":
          final csrInfoJson = checkCallArgNotNull(decodeArgs, 'csrInfo',
              context: callbackContext);
          final attestationInfoJson = checkCallArgNotNull(
              decodeArgs, 'attestationInfo',
              context: callbackContext);
          _nocChainIssuer!.onNOCChainGenerationNeeded(
              decodeArgs['onNOCChainGenerationCompleteHandle'],
              CSRInfo.decode(csrInfoJson),
              AttestationInfo.decode(attestationInfoJson));
          return createPlatformCallSuccessResult();
      }
      return createPlatformCallExceptionResult(
          methodNoFound, 'Not found $method');
    }
    ////// CompletionListener //////
    else if (splitPaths.firstOrNull == 'CompletionListener') {
      if (_completionListener == null) {
        return createPlatformCallExceptionResult(
            argsInvalid, "CompletionListener not set");
      }
      switch (splitPaths[1]) {
        case 'onConnectDeviceComplete':
          _completionListener!.onConnectDeviceComplete();
          return createPlatformCallSuccessResult();
        case 'onStatusUpdate':
          _completionListener!.onStatusUpdate(checkCallArgNotNull(
              decodeArgs, 'status',
              context: callbackContext));
          return createPlatformCallSuccessResult();
        case 'onPairingComplete':
          _completionListener!.onPairingComplete(checkCallArgNotNull(
              decodeArgs, 'errorCode',
              context: callbackContext));
          return createPlatformCallSuccessResult();
        case 'onPairingDeleted':
          _completionListener!.onPairingDeleted(checkCallArgNotNull(
              decodeArgs, 'errorCode',
              context: callbackContext));
          return createPlatformCallSuccessResult();
        case 'onCommissioningComplete':
          _completionListener!.onCommissioningComplete(
              decodeArgs["nodeId"],
              checkCallArgNotNull(decodeArgs, 'errorCode',
                  context: callbackContext));
          return createPlatformCallSuccessResult();
        case 'onReadCommissioningInfo':
          _completionListener!.onReadCommissioningInfo(
            checkCallArgNotNull(decodeArgs, 'vendorId',
                context: callbackContext),
            checkCallArgNotNull(decodeArgs, 'productId',
                context: callbackContext),
            checkCallArgNotNull(decodeArgs, 'wifiEndpointId',
                context: callbackContext),
            checkCallArgNotNull(decodeArgs, 'threadEndpointId',
                context: callbackContext),
          );
          return createPlatformCallSuccessResult();
        case 'onCommissioningStatusUpdate':
          _completionListener!.onCommissioningStatusUpdate(
            checkCallArgNotNull(decodeArgs, 'nodeId', context: callbackContext),
            checkCallArgNotNull(decodeArgs, 'stage', context: callbackContext),
            checkCallArgNotNull(decodeArgs, 'errorCode',
                context: callbackContext),
          );
          return createPlatformCallSuccessResult();
        case 'onNotifyChipConnectionClosed':
          _completionListener!.onNotifyChipConnectionClosed();
          return createPlatformCallSuccessResult();
        case 'onCloseBleComplete':
          // _completionListener!.onCloseBleComplete();
          return createPlatformCallSuccessResult();
        case 'onError':
          _completionListener!.onError(Exception(checkCallArgNotNull(
              decodeArgs, 'error',
              context: callbackContext)));
          return createPlatformCallSuccessResult();
        case 'onOpCSRGenerationComplete':
          _completionListener!.onOpCSRGenerationComplete(
            toUint8List(checkCallArgNotNull(decodeArgs, 'csr',
                context: callbackContext)),
          );
          return createPlatformCallSuccessResult();
        case 'onICDRegistrationInfoRequired':
          _completionListener!.onICDRegistrationInfoRequired();
          return createPlatformCallSuccessResult();
        case 'onICDRegistrationComplete':
          _completionListener!.onICDRegistrationComplete(
            checkCallArgNotNull(decodeArgs, 'errorCode',
                context: callbackContext),
            decodeArgs['icdDeviceInfo'] == null
                ? null
                : ICDDeviceInfo.fromJson((decodeArgs['icdDeviceInfo'] as Map)
                    .cast<String, dynamic>()),
          );
          return createPlatformCallSuccessResult();
      }
    }
    ////// DeviceAttestationDelegate //////
    else if (splitPaths.firstOrNull == 'DeviceAttestationDelegate') {
      switch (splitPaths[1]) {
        case "onDeviceAttestationCompleted":
          deviceAttestationDelegate?.onDeviceAttestationCompleted(
              checkCallArgNotNull(decodeArgs, "devicePtr",
                  context: callbackContext),
              decodeArgs["attestationInfo"] == null
                  ? null
                  : AttestationInfo.decode(decodeArgs["attestationInfo"]),
              checkCallArgNotNull(decodeArgs, "errorCode",
                  context: callbackContext));
          return createPlatformCallSuccessResult();
      }
    }
    ////// InvokeCallback //////
    else if (splitPaths.firstOrNull == 'InvokeCallback') {
      String invokeCallbackPoint = checkCallArgNotNull(
          decodeArgs, 'invokeCallbackPoint',
          context: callbackContext);
      final callback = _invokeCallbacks[invokeCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid,
            "Not found invoke callback by point $invokeCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onDone":
          try {
            callback.onDone();
          } catch (e, s) {
            reportMatterError('$runtimeType InvokeCallback.onDone', e, s);
          }
          _invokeCallbacks.remove(invokeCallbackPoint);
          return createPlatformCallSuccessResult();
        case "onResponse":
          try {
            callback.onResponse(
                InvokeElement.fromJson(checkCallArgNotNull(
                    decodeArgs, "invokeElement", context: callbackContext)),
                checkCallArgNotNull(decodeArgs, "successCode",
                    context: callbackContext));
          } catch (e, s) {
            reportMatterError('$runtimeType InvokeCallback.onResponse', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(Exception(checkCallArgNotNull(decodeArgs, "error",
                context: callbackContext)));
          } catch (e, s) {
            reportMatterError('$runtimeType InvokeCallback.onError', e, s);
          }
          return createPlatformCallSuccessResult();
      }
    }
    ///// SubscriptionCallback //////
    else if (splitPaths.firstOrNull == 'SubscriptionCallback') {
      String subscriptionCallbackPoint = checkCallArgNotNull(
          decodeArgs, 'subscriptionCallbackPoint',
          context: callbackContext);
      final callback = _subscriptionCallbacks[subscriptionCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid,
            "Not found invoke callback by point $subscriptionCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onSubscriptionEstablished":
          try {
            callback.onSubscriptionEstablished(checkCallArgNotNull(
                decodeArgs, 'subscriptionId',
                context: callbackContext));
          } catch (e, s) {
            reportMatterError(
              '$runtimeType SubscriptionCallback.onSubscriptionEstablished',
              e,
              s,
            );
            return createPlatformCallExceptionResult(
                argsInvalid, 'Subscription callback failed');
          }
          return createPlatformCallSuccessResult();
        case "onReport":
          try {
            callback.onReport(NodeState.fromJson(checkCallArgNotNull(
                decodeArgs, "nodeState",
                context: callbackContext)));
          } catch (e, s) {
            reportMatterError(
                '$runtimeType SubscriptionCallback.onReport', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
                null,
                null,
                Exception(checkCallArgNotNull(decodeArgs, "error",
                    context: callbackContext)));
          } catch (e, s) {
            reportMatterError(
                '$runtimeType SubscriptionCallback.onError', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onDone":
          try {
            callback.onDone();
          } catch (e, s) {
            reportMatterError('$runtimeType SubscriptionCallback.onDone', e, s);
          }
          _subscriptionCallbacks.remove(subscriptionCallbackPoint);
          return createPlatformCallSuccessResult();
      }
    }
    ///// ReportCallback //////
    else if (splitPaths.firstOrNull == 'ReportCallback') {
      String reportCallbackPoint = checkCallArgNotNull(
          decodeArgs, 'reportCallbackPoint',
          context: callbackContext);
      final callback = _reportCallbacks[reportCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid,
            "Not found invoke callback by point $reportCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onReport":
          try {
            callback.onReport(NodeState.fromJson(checkCallArgNotNull(
                decodeArgs, "nodeState",
                context: callbackContext)));
          } catch (e, s) {
            reportMatterError('$runtimeType ReportCallback.onReport', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
                null,
                null,
                Exception(checkCallArgNotNull(decodeArgs, "error",
                    context: callbackContext)));
          } catch (e, s) {
            reportMatterError('$runtimeType ReportCallback.onError', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onDone":
          try {
            callback.onDone();
          } catch (e, s) {
            reportMatterError('$runtimeType ReportCallback.onDone', e, s);
          }
          _reportCallbacks.remove(reportCallbackPoint);
          return createPlatformCallSuccessResult();
      }
    }
    ///// WriteAttributesCallback //////
    else if (splitPaths.firstOrNull == 'WriteAttributesCallback') {
      String writeAttributesCallbackPoint = checkCallArgNotNull(
          decodeArgs, 'writeAttributesCallbackPoint',
          context: callbackContext);
      final callback = _writeAttributesCallback[writeAttributesCallbackPoint];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid,
            "Not found invoke callback by point $writeAttributesCallbackPoint");
      }
      switch (splitPaths[1]) {
        case "onResponse":
          try {
            callback.onResponse(
                decodeArgs["attributePath"] == null
                    ? null
                    : ChipAttributePath.fromJson(decodeArgs["attributePath"]),
                decodeArgs["status"] == null
                    ? null
                    : Status.fromJson(decodeArgs["status"]));
          } catch (e, s) {
            reportMatterError(
                '$runtimeType WriteAttributesCallback.onResponse', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
                decodeArgs["attributePath"] == null
                    ? null
                    : ChipAttributePath.fromJson(decodeArgs["attributePath"]),
                Exception(decodeArgs['error'] ?? 'Unknown Error'));
          } catch (e, s) {
            reportMatterError(
                '$runtimeType WriteAttributesCallback.onError', e, s);
          }
          return createPlatformCallSuccessResult();
        case "onDone":
          try {
            callback.onDone();
          } catch (e, s) {
            reportMatterError(
                '$runtimeType WriteAttributesCallback.onDone', e, s);
          }
          _writeAttributesCallback.remove(writeAttributesCallbackPoint);
          return createPlatformCallSuccessResult();
      }
    }
    ///// ConnectedDeviceCallback /////
    else if (splitPaths.firstOrNull == "ConnectedDeviceCallback") {
      String callbackHandle = checkCallArgNotNull(decodeArgs, 'callbackHandle',
          context: callbackContext);
      final callback = _connectedDeviceCallback[callbackHandle];
      if (callback == null) {
        return createPlatformCallExceptionResult(
            argsInvalid, "Not found invoke callback by point $callbackHandle");
      }
      switch (splitPaths[1]) {
        case "onDeviceConnected":
          try {
            callback.onConnected(decodeArgs['context']);
          } catch (e, s) {
            reportMatterError(
              '$runtimeType ConnectedDeviceCallback.onDeviceConnected',
              e,
              s,
            );
          }
          _connectedDeviceCallback.remove(callbackHandle);
          return createPlatformCallSuccessResult();
        case "onConnectionFailure":
          try {
            callback.onError(Exception(decodeArgs['error'] ?? "Unknown error"));
          } catch (e, s) {
            reportMatterError(
              '$runtimeType ConnectedDeviceCallback.onConnectionFailure',
              e,
              s,
            );
          }
          _connectedDeviceCallback.remove(callbackHandle);
          return createPlatformCallSuccessResult();
      }
    }

    ///// OpenCommissioningCallback /////
    else if (splitPaths.firstOrNull == "OpenCommissioningCallback") {
      String callbackHandle = checkCallArgNotNull(decodeArgs, 'callbackHandle',
          context: callbackContext);
      final callback = _openCommissioningCallbacks[callbackHandle];
      if (callback == null) {
        return createPlatformCallExceptionResult(argsInvalid,
            "Not found invoke callback by callbackHandle $callbackHandle");
      }
      switch (splitPaths[1]) {
        case "onSuccess":
          try {
            callback.onSuccess(
              decodeArgs['connectContext'],
              checkCallArgNotNull(decodeArgs, 'manualPairingCode',
                  context: callbackContext),
              checkCallArgNotNull(decodeArgs, 'qrCode',
                  context: callbackContext),
            );
          } catch (e, s) {
            reportMatterError(
              '$runtimeType OpenCommissioningCallback.onSuccess',
              e,
              s,
            );
          }
          _openCommissioningCallbacks.remove(callbackHandle);
          return createPlatformCallSuccessResult();
        case "onError":
          try {
            callback.onError(
                checkCallArgNotNull(decodeArgs, "status",
                    context: callbackContext) as int,
                decodeArgs['connectContext']);
          } catch (e, s) {
            reportMatterError(
              '$runtimeType OpenCommissioningCallback.onError',
              e,
              s,
            );
          }
          _openCommissioningCallbacks.remove(callbackHandle);
          return createPlatformCallSuccessResult();
      }
    }

    return PlatformCallResult(
        code: methodNoFound,
        resultJson: jsonEncode({"msg": 'Not found method $uri'}));
  }

  @override
  bool match(String method, arguments) {
    if (_isClosed) {
      return false;
    }
    try {
      final uri = Uri.parse(method);
      final splitPaths = uri.path
          .split('/')
          .where((element) => element.trim().isNotEmpty)
          .toList();
      final handleId = jsonDecode(arguments)[jsonKeyHandle];
      final isMatch = handleId == _platformDeviceControllerHandle &&
          uri.host == _hostName &&
          matchPathList.contains(splitPaths.firstOrNull);
      matterPrint('$runtimeType match $isMatch');
      return isMatch;
    } catch (e, s) {
      reportMatterError('$runtimeType match', e, s);
    }
    return false;
  }

  ChipDeviceController._(this.params, this._platformDeviceControllerHandle,
      this._keypairDelegateHandleId) {
    _channelFlutterMatter = FlutterMatterPlatform.instance;
    _channelFlutterMatter.addHandler(this);
    _isRunning = true;
  }

  /// Creates a controller or returns the existing controller for the same
  /// [ControllerParams.fabricId] and [ControllerParams.rootCertificate].
  ///
  /// The returned controller must remain alive while native operations or
  /// callbacks are in flight.
  static Future<ChipDeviceController> newControllerIfNotExist(
      ControllerParams params) async {
    return ChipDeviceControllerManager.instance.acquire(params);
  }

  static Future<ChipDeviceController> _create(ControllerParams params) async {
    final channelFlutterMatter = FlutterMatterPlatform.instance;
    String? keypairDelegateHandleId;
    if (params.keypairDelegate != null) {
      keypairDelegateHandleId =
          _keypairDelegateCallbackHandler.addHandler(params.keypairDelegate!);
    }
    try {
      final result = await channelFlutterMatter.requestPlatform(
          RequestPlatformParams(
              methodName: createRequestPlatformUrl(_hostName, 'new').toString(),
              methodParamsJson: params.encode()));
      if (result.code != 0) {
        throw CallPlatformException(
          'newDeviceController failed with code ${result.code}',
          code: result.code,
          methodName: 'new',
          details: const <String, Object?>{
            'host': 'devicecontroller',
            'category': 'platform-error',
          },
        );
      }
      final handle = result.jsonData[jsonKeyHandle];
      if (handle is! String || handle.trim().isEmpty) {
        throw ControllerLifecycleException(
          ControllerLifecycleFailure.nativeStateConflict,
          'Native controller creation succeeded without a usable handle',
          methodName: 'new',
        );
      }
      return ChipDeviceController._(params, handle, keypairDelegateHandleId);
    } catch (e, s) {
      // The native controller is not usable when creation fails. Remove only
      // the handle registered for this attempt; the hashCode-based ID scheme
      // itself remains unchanged.
      if (keypairDelegateHandleId != null) {
        _keypairDelegateCallbackHandler.removeHandler(keypairDelegateHandleId);
      }
      reportMatterError(
        'ChipDeviceController.newControllerIfNotExist',
        e,
        s,
      );
      rethrow;
    }
  }

  /// Releases one acquisition of this controller.
  ///
  /// Repeated acquires for the same fabric identity return this object and
  /// increment a manager-owned acquisition count. Each close releases exactly
  /// one acquisition; only the final release invalidates this handle and asks
  /// native code to delete the controller. Closing an already closed or
  /// superseded handle throws [ControllerLifecycleFailure.closed].
  Future<void> close() {
    return ChipDeviceControllerManager.instance.release(this);
  }

  /// Removes Dart-side handlers and callback state without requesting native
  /// controller deletion.
  ///
  /// The manager remembers the abandoned native handle. The next acquire first
  /// deletes that abandoned handle and then creates a fresh controller. Use
  /// [close] or [deleteDeviceController] when a balanced release should perform
  /// native deletion immediately.
  void destroy() {
    if (_isClosed) {
      return;
    }
    _markClosed();
    ChipDeviceControllerManager.instance._controllerDestroyed(this);
  }

  Future<Map<String, dynamic>> _requestPlatform(
      String methodName, String methodParamsJson) async {
    _ensureOpen(methodName);
    final result = await _channelFlutterMatter.requestPlatform(
        RequestPlatformParams(
            methodName: createRequestPlatformUrl(_hostName, methodName),
            methodParamsJson: methodParamsJson));
    _ensureOpen(methodName);
    if (result.code == 0) {
      return result.jsonData;
    }
    throw CallPlatformException(
      'Call $methodName failed with code ${result.code}',
      code: result.code,
      methodName: methodName,
      details: const <String, Object?>{
        'host': 'devicecontroller',
        'category': 'platform-error',
      },
    );
  }

  Future<Map<String, dynamic>> _requestPlatformUnchecked(
      String methodName, String methodParamsJson) async {
    final result = await _channelFlutterMatter.requestPlatform(
        RequestPlatformParams(
            methodName: createRequestPlatformUrl(_hostName, methodName),
            methodParamsJson: methodParamsJson));
    if (result.code == 0) {
      return result.jsonData;
    }
    throw CallPlatformException(
      'Call $methodName failed with code ${result.code}',
      code: result.code,
      methodName: methodName,
      details: const <String, Object?>{
        'host': 'devicecontroller',
        'category': 'platform-error',
      },
    );
  }

  void _ensureOpen(String operation) {
    if (_isClosed) {
      throw ControllerLifecycleException(
        ControllerLifecycleFailure.closed,
        'Controller is closed; cannot perform $operation',
        methodName: operation,
      );
    }
  }

  void _markClosed() {
    if (_isClosed) {
      return;
    }
    _isClosed = true;
    _isRunning = false;
    _channelFlutterMatter.removeHandler(this);
    if (_keypairDelegateHandleId != null) {
      _keypairDelegateCallbackHandler.removeHandler(_keypairDelegateHandleId!);
    }
    _nocChainIssuer = null;
    _completionListener = null;
    deviceAttestationDelegate = null;
    _invokeCallbacks.clear();
    _subscriptionCallbacks.clear();
    _reportCallbacks.clear();
    _writeAttributesCallback.clear();
    _connectedDeviceCallback.clear();
    _openCommissioningCallbacks.clear();
    if (!_closedCompleter.isCompleted) {
      _closedCompleter.complete();
    }
  }

  /// Handles a native request rejection and removes its pending callback.
  ///
  /// Cleanup is intentionally limited to the rejection path. A successful
  /// response means native accepted an asynchronous operation and may still
  /// invoke the callback later, so this must not run in `finally`.
  void _handleRejectedRequest<T>(
    Map<String, T> callbacks,
    String callbackHandle,
    String operation,
    Object error,
    StackTrace stackTrace,
  ) {
    reportMatterError(operation, error, stackTrace);
    callbacks.remove(callbackHandle);
  }

  /// Sets this DeviceController to use the given issuer for issuing operational certs and verifying
  /// the DAC. By default, the DeviceController uses an internal, OperationalCredentialsDelegate
  Future<void> setNocChainIssuer(NOCChainIssuer nocChainIssuer) async {
    _ensureOpen('setNocChainIssuer');
    _nocChainIssuer = nocChainIssuer;
    await _requestPlatform('setNocChainIssuer',
        jsonEncode({jsonKeyHandle: _platformDeviceControllerHandle}));
  }

  /// Sets a [CompletionListener] to receive provisioning lifecycle callbacks.
  ///
  /// Prefer passing the listener directly to [pairDevice] when you have it
  /// available; use this method if you need to update the listener separately.
  Future<void> setCompletionListener(CompletionListener listener) async {
    _ensureOpen('setCompletionListener');
    _completionListener = listener;
    await _requestPlatform('setCompletionListener',
        jsonEncode({jsonKeyHandle: _platformDeviceControllerHandle}));
  }

  /// Starts commissioning through the native Matter discovery and pairing flow.
  ///
  /// [deviceId] is the node ID requested for the commissionee. Supply either
  /// [setupPincode] or [onboardingPayload] on Android; iOS requires
  /// [onboardingPayload]. [networkCredentials] contains the Wi-Fi or Thread
  /// credentials that the commissionee should join.
  ///
  /// This method starts the asynchronous operation. Completion is delivered to
  /// [completionListener] through [CompletionListener.onCommissioningComplete].
  /// Keep the listener and [attestationDelegate] alive until that callback fires.
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
    _ensureOpen('pairDevice');
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
    await _requestPlatform(
        'pairDevice',
        jsonEncode({
          jsonKeyHandle: _platformDeviceControllerHandle,
          'connId': connId,
          'deviceId': deviceId,
          'setupPincode': setupPincode,
          'csrNonce': csrNonce == null ? null : List.from(csrNonce),
          'networkCredentials': networkCredentials.toJson(),
          'attestationDelegate': attestationDelegate?.hashCode.toString(),
          'failSafeExpiryTimeoutSecs': failSafeExpiryTimeoutSecs,
          'completionListener': completionListener?.hashCode.toString(),
          'onboardingPayload': onboardingPayload,
          'displayName': displayName,
          'ecosystemName': ecosystemName,
        }));
  }

  /// Commissions a commissionee that is already reachable on the local network.
  ///
  /// This bypasses commissionee discovery and uses the supplied address and
  /// port for PASE. It is intended for controllers whose platform discovery
  /// stack is unavailable or unreliable. The method is implemented on Android;
  /// iOS continues to use [pairDevice] with the onboarding payload.
  Future<void> pairDeviceWithAddress({
    required int deviceId,
    required String address,
    required int port,
    required int discriminator,
    required int setupPincode,
    Uint8List? csrNonce,
    DeviceAttestationDelegate? attestationDelegate,
    CompletionListener? completionListener,
    int failSafeExpiryTimeoutSecs = 60,
  }) async {
    _ensureOpen('pairDeviceWithAddress');
    if (address.trim().isEmpty) {
      throw ArgumentError.value(address, 'address', 'Must not be empty');
    }
    if (port < 1 || port > 65535) {
      throw ArgumentError.value(port, 'port', 'Must be between 1 and 65535');
    }
    if (discriminator < 0 || discriminator > 0x0fff) {
      throw ArgumentError.value(
        discriminator,
        'discriminator',
        'Must be between 0 and 4095',
      );
    }
    if (setupPincode < 1 || setupPincode > 99999998) {
      throw ArgumentError.value(
        setupPincode,
        'setupPincode',
        'Must be a valid Matter setup passcode',
      );
    }

    this.deviceAttestationDelegate = attestationDelegate;
    this._completionListener = completionListener;
    await _requestPlatform(
      'pairDeviceWithAddress',
      jsonEncode({
        jsonKeyHandle: _platformDeviceControllerHandle,
        'deviceId': deviceId,
        'address': address.trim(),
        'port': port,
        'discriminator': discriminator,
        'setupPincode': setupPincode,
        'csrNonce': csrNonce == null ? null : List.from(csrNonce),
        'attestationDelegate': attestationDelegate?.hashCode.toString(),
        'failSafeExpiryTimeoutSecs': failSafeExpiryTimeoutSecs,
        'completionListener': completionListener?.hashCode.toString(),
      }),
    );
  }

  /// Stops an in-progress commissioning attempt for [deviceId].
  ///
  /// This does not remove a device that has already been commissioned.
  Future<void> stopDevicePairing(int deviceId) async {
    await _requestPlatform(
        'stopDevicePairing',
        jsonEncode({
          jsonKeyHandle: _platformDeviceControllerHandle,
          "deviceId": deviceId
        }));
  }

  /// Create a root (self-signed) X.509 DER encoded certificate
  static Future<Uint8List> createRootCertificate(
      KeypairDelegate keypair, int issuerId, int? fabricId) async {
    final id = _keypairDelegateCallbackHandler.addHandler(keypair);
    final channel = FlutterMatterPlatform.instance;
    final result = await channel
        .requestPlatform(RequestPlatformParams(
            methodName:
                createRequestPlatformUrl(_hostName, 'createRootCertificate'),
            methodParamsJson: jsonEncode({
              // jsonKeyHandle: _platformDeviceControllerHandle,
              'keypairHandle': id,
              'issuerId': issuerId,
              'fabricId': fabricId
            })))
        .whenComplete(() {
      _keypairDelegateCallbackHandler.removeHandler(id);
    });
    if (result.code != 0) {
      throw CallPlatformException(
        'createRootCertificate failed with code ${result.code}',
        code: result.code,
        methodName: 'createRootCertificate',
        details: const <String, Object?>{
          'host': 'devicecontroller',
          'category': 'platform-error',
        },
      );
    }
    return _platformBytesOrThrow(result.jsonData, 'createRootCertificate');
  }

  /// Create an X.509 DER encoded certificate that has the right fields to be a valid Matter
  /// operational certificate.
  static Future<Uint8List> createOperationalCertificate(
      KeypairDelegate signingKeypair,
      Uint8List signingCertificate,
      Uint8List operationalPublicKey,
      int fabricId,
      int nodeId,
      List<int>? caseAuthenticatedTags) async {
    final id = _keypairDelegateCallbackHandler.addHandler(signingKeypair);
    final channel = FlutterMatterPlatform.instance;
    final result = await channel
        .requestPlatform(RequestPlatformParams(
            methodName: createRequestPlatformUrl(
                _hostName, 'createOperationalCertificate'),
            methodParamsJson: jsonEncode({
              // jsonKeyHandle: id,
              'signingCertificate': List.from(signingCertificate),
              'keypairHandle': id,
              'operationalPublicKey': List.from(operationalPublicKey),
              'fabricId': fabricId,
              'nodeId': nodeId,
              'caseAuthenticatedTags': caseAuthenticatedTags == null
                  ? null
                  : List.from(caseAuthenticatedTags),
            })))
        .whenComplete(() {
      _keypairDelegateCallbackHandler.removeHandler(id);
    });
    if (result.code != 0) {
      throw CallPlatformException(
        'createOperationalCertificate failed with code ${result.code}',
        code: result.code,
        methodName: 'createOperationalCertificate',
        details: const <String, Object?>{
          'host': 'devicecontroller',
          'category': 'platform-error',
        },
      );
    }
    return _platformBytesOrThrow(
        result.jsonData, 'createOperationalCertificate');
  }

  /// Extract the public key from the given PKCS#10 certificate signing request. This is the public
  /// key that a certificate issued in response to the request would need to have.
  Future<Uint8List> publicKeyFromCSR(Uint8List csr) async {
    final result = await _requestPlatform(
        'publicKeyFromCSR',
        jsonEncode({
          jsonKeyHandle: _platformDeviceControllerHandle,
          'csr': List.from(csr)
        }));
    return _platformBytesOrThrow(result, 'publicKeyFromCSR');
  }

  /// When a NOCChainIssuer is set for this controller, then onNOCChainGenerationNeeded will be
  /// called when the NOC CSR needs to be signed. This allows for custom credentials issuer
  /// implementations, for example, when a proprietary cloud API will perform the CSR signing.
  Future<int> onNOCChainGeneration(ControllerParams params,
      {String? onNOCChainGenerationCompleteHandle}) async {
    final result = await _requestPlatform(
        'onNOCChainGeneration',
        jsonEncode({
          jsonKeyHandle: _platformDeviceControllerHandle,
          'params': params.toJson(),
          'onNOCChainGenerationCompleteHandle':
              onNOCChainGenerationCompleteHandle
        }));
    final data = result['data'];
    if (data is! int) {
      throw PlatformProtocolException(
        'data must be an integer',
        code: unHandlerException,
        methodName: 'onNOCChainGeneration',
      );
    }
    return data;
  }

  /// This function instructs the commissioner to proceed to the next stage of commissioning after
  /// attestation is reported.
  ///
  /// @param devicePtr a pointer to the device which is being commissioned.
  /// @param ignoreAttestationFailure whether to ignore device attestation failure.
  Future<void> continueCommissioning(
      int devicePtr, bool ignoreAttestationFailure) async {
    await _requestPlatform(
        'continueCommissioning',
        jsonEncode({
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

  /// Compatibility alias for [close].
  ///
  /// The final acquisition release deletes the native controller and clears
  /// this handle. Earlier releases only decrement the acquisition count.
  Future<void> deleteDeviceController() async {
    await close();
  }

  /// Sends an Interaction Model command to [nodeId].
  ///
  /// Responses and failures are delivered to [callback]. Pass
  /// [connectContext] from [connectedDevice] to reuse an existing CASE
  /// connection. `timedRequestTimeoutMs` and `imTimeoutMs` use the native
  /// defaults when set to zero.
  Future<void> invoke(
      InvokeCallback callback, int nodeId, InvokeElement invokeElement,
      {Object? connectContext,
      int timedRequestTimeoutMs = 0,
      int imTimeoutMs = 0}) async {
    _ensureOpen('invoke');
    String callbackId = callback.hashCode.toString();
    _invokeCallbacks[callbackId] = callback;
    try {
      await _requestPlatform(
          "invoke",
          jsonEncode({
            jsonKeyHandle: _platformDeviceControllerHandle,
            'callback': callbackId,
            'nodeId': nodeId,
            'invokeElement': invokeElement.toJson(),
            'timedRequestTimeoutMs': timedRequestTimeoutMs,
            'imTimeoutMs': imTimeoutMs,
            'connectContext': connectContext
          }));
    } catch (e, s) {
      _handleRejectedRequest(
          _invokeCallbacks, callbackId, '$runtimeType invoke', e, s);
      rethrow;
    }
  }

  /// Subscribes to the given attribute and/or event paths.
  ///
  /// This sets up an auto-resubscribing interaction for the specified paths.
  /// Reports are delivered to [callback] as data is received and processed.
  ///
  /// [nodeId] is the target device node ID.
  ///
  /// [attributePaths] is the list of attribute paths to subscribe to.
  ///
  /// [eventPaths] is the list of event paths to subscribe to.
  ///
  /// [dataVersionFilters] is the list of data version filters used to suppress
  /// unchanged cluster data. Currently this is supported on Android only.
  ///
  /// [minInterval] is the requested minimum reporting interval floor, in seconds.
  ///
  /// [maxInterval] is the requested maximum reporting interval ceiling, in seconds.
  ///
  /// If [keepSubscriptions] is `false`, all existing or pending subscriptions
  /// on the publisher for this subscriber should be terminated.
  ///
  /// If [isFabricFiltered] is `true`, data inside fabric-scoped lists is limited
  /// to the accessing fabric.
  ///
  /// [imTimeoutMs] overrides the default Interaction Model timeout in the native
  /// layer when non-zero.
  ///
  /// [eventMin] filters queued events so only events with event numbers greater
  /// than or equal to this value are reported.
  ///
  /// If provided, [connectContext] reuses an existing connected-device context
  /// instead of resolving a new one for [nodeId].
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
      int eventMin,
      {Object? connectContext}) async {
    _ensureOpen('subscribe');
    String callbackHandle = callback.hashCode.toString();
    _subscriptionCallbacks[callbackHandle] = callback;
    try {
      await _requestPlatform(
          'subscribe',
          jsonEncode({
            jsonKeyHandle: _platformDeviceControllerHandle,
            'nodeId': nodeId,
            'callbackHandle': callbackHandle,
            'attributePaths': attributePaths?.map((e) => e.toJson()).toList(),
            'eventPaths': eventPaths?.map((e) => e.toJson()).toList(),
            'dataVersionFilters':
                dataVersionFilters?.map((e) => e.toJson()).toList(),
            'minInterval': minInterval,
            'maxInterval': maxInterval,
            'keepSubscriptions': keepSubscriptions,
            'isFabricFiltered': isFabricFiltered,
            'imTimeoutMs': imTimeoutMs,
            'eventMin': eventMin,
            'connectContext': connectContext
          }));
    } catch (e, s) {
      _handleRejectedRequest(_subscriptionCallbacks, callbackHandle,
          '$runtimeType subscribe', e, s);
      rethrow;
    }
  }

  /// Reads the given attribute and/or event paths.
  ///
  /// Reports are delivered to [callback] once the read response has been
  /// received and processed.
  ///
  /// [nodeId] is the target device node ID.
  ///
  /// [attributePaths] is the list of attribute paths to read.
  ///
  /// [eventPaths] is the list of event paths to read.
  ///
  /// [dataVersionFilters] is the list of data version filters used to suppress
  /// unchanged cluster data. Currently this is supported on Android only.
  ///
  /// If [isFabricFiltered] is `true`, data inside fabric-scoped lists is limited
  /// to the accessing fabric.
  ///
  /// [imTimeoutMs] overrides the default Interaction Model timeout in the native
  /// layer when non-zero.
  ///
  /// [eventMin] filters queued events so only events with event numbers greater
  /// than or equal to this value are returned.
  ///
  /// If provided, [connectContext] reuses an existing connected-device context
  /// instead of resolving a new one for [nodeId].
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
    _ensureOpen('read');
    String callbackHandle = callback.hashCode.toString();
    _reportCallbacks[callbackHandle] = callback;
    try {
      await _requestPlatform(
          'read',
          jsonEncode({
            jsonKeyHandle: _platformDeviceControllerHandle,
            'nodeId': nodeId,
            'callbackHandle': callbackHandle,
            'attributePaths': attributePaths?.map((e) => e.toJson()).toList(),
            'eventPaths': eventPaths?.map((e) => e.toJson()).toList(),
            'dataVersionFilters':
                dataVersionFilters?.map((e) => e.toJson()).toList(),
            'isFabricFiltered': isFabricFiltered,
            'imTimeoutMs': imTimeoutMs,
            'eventMin': eventMin,
            'connectContext': connectContext,
          }));
    } catch (e, s) {
      _handleRejectedRequest(
          _reportCallbacks, callbackHandle, '$runtimeType read', e, s);
      rethrow;
    }
  }

  /// Writes attributes on [nodeId].
  ///
  /// [attributeList] contains the requested paths and values. Results and
  /// failures are delivered to [callback]. Pass [connectContext] from
  /// [connectedDevice] to reuse an existing CASE connection.
  Future<void> write(
      int nodeId,
      WriteAttributesCallback callback,
      // int devicePtr,
      List<AttributeWriteRequest> attributeList,
      int timedRequestTimeoutMs,
      int imTimeoutMs,
      {Object? connectContext}) async {
    _ensureOpen('write');
    String callbackHandle = callback.hashCode.toString();
    _writeAttributesCallback[callbackHandle] = callback;
    try {
      await _requestPlatform(
          'write',
          jsonEncode({
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
      _handleRejectedRequest(
          _writeAttributesCallback, callbackHandle, '$runtimeType write', e, s);
      rethrow;
    }
  }

  /// Establishes or reuses a CASE connection to [nodeId].
  ///
  /// [ConnectedDeviceCallback.onConnected] receives the opaque connection
  /// context to pass to operation methods. The caller should release that
  /// context with [releaseConnectContext] when the session ends.
  Future<void> connectedDevice(int nodeId, ConnectedDeviceCallback callback,
      {Object? connectContext}) async {
    _ensureOpen('connectedDevice');
    String callbackHandle = callback.hashCode.toString();
    _connectedDeviceCallback[callbackHandle] = callback;
    try {
      await _requestPlatform(
          'connectedDevice',
          jsonEncode({
            'nodeId': nodeId,
            jsonKeyHandle: _platformDeviceControllerHandle,
            'callbackHandle': callbackHandle,
            'connectContext': connectContext,
          }));
    } catch (e, s) {
      _handleRejectedRequest(_connectedDeviceCallback, callbackHandle,
          '$runtimeType connectedDevice', e, s);
      rethrow;
    }
  }

  /// Releases a connection context returned by [connectedDevice].
  Future<void> releaseConnectContext(Object connectContext) async {
    await _requestPlatform(
        'releaseConnectContext',
        jsonEncode({
          jsonKeyHandle: _platformDeviceControllerHandle,
          'connectContext': connectContext,
        }));
  }

  /// Opens a device pairing window and returns whether the native request was
  /// accepted.
  ///
  /// The pairing codes are delivered through [callback]. [duration] is in
  /// seconds. Callers must keep [callback] alive until it completes.
  ///
  /// This API is deprecated because platform implementations may not match the
  /// expected commissioning-window semantics. Verify the behavior on each
  /// target platform before relying on it.
  @Deprecated(
    'Platform-specific behavior may not match the expected commissioning-window '
    'semantics; verify each target platform before use.',
  )
  Future<bool> openPairingWindowWithPIN(
      Object connectContext,
      int duration,
      int discriminator,
      int setupPIN,
      OpenCommissioningCallback callback) async {
    _ensureOpen('openPairingWindowWithPIN');
    final callbackId = callback.hashCode.toString();
    _openCommissioningCallbacks[callbackId] = callback;
    try {
      final result = await _requestPlatform(
          'openPairingWindowWithPIN',
          jsonEncode({
            jsonKeyHandle: _platformDeviceControllerHandle,
            'connectContext': connectContext,
            'duration': duration,
            'discriminator': discriminator,
            'setupPIN': setupPIN,
            'callbackHandle': callbackId
          }));
      return result['data'] == true;
    } on ControllerLifecycleException {
      rethrow;
    } catch (e, s) {
      reportMatterError('$runtimeType openPairingWindowWithPIN', e, s);
      _openCommissioningCallbacks.remove(callbackId);
    }
    return false;
  }

  /// Returns the active fabric index for this controller, or `null` when the
  /// native controller does not expose one.
  Future<int?> getFabricIndex() async {
    try {
      final result = await _requestPlatform(
          'getFabricIndex',
          jsonEncode({
            jsonKeyHandle: _platformDeviceControllerHandle,
          }));
      return result['data'];
    } on ControllerLifecycleException {
      rethrow;
    } catch (e, s) {
      reportMatterError('$runtimeType getFabricIndex', e, s);
      return null;
    }
  }

  /// Cancels the subscription identified by [fabricIndex], [nodeId], and
  /// [subscriptionId].
  ///
  /// Returns `true` when the native subscription was removed.
  Future<bool> unSubscription(
      int fabricIndex, int nodeId, int subscriptionId) async {
    try {
      final result = await _requestPlatform(
          'unSubscribe',
          jsonEncode({
            jsonKeyHandle: _platformDeviceControllerHandle,
            "fabricIndex": fabricIndex,
            "nodeId": nodeId,
            "subscriptionId": subscriptionId,
          }));
      return result['data'] == true;
    } on ControllerLifecycleException {
      rethrow;
    } catch (e, s) {
      reportMatterError('$runtimeType unSubscription', e, s);
      return false;
    }
  }
}

enum _ControllerManagerPhase {
  idle,
  active,
  switching,
  shuttingDown,
  poisoned,
}

/// Process-wide owner of the single active native Matter controller.
///
/// The manager serializes acquisition and shutdown so two controller
/// constructions can never overlap. Repeating [acquire] for the same
/// [ControllerParams.fabricId] and [ControllerParams.rootCertificate] returns
/// the same [ChipDeviceController] and increments its acquisition count.
/// Requesting a different identity closes the old handle, performs native
/// deletion, and only then creates the replacement.
///
/// Queued acquire, release, and close operations execute in invocation order.
/// Switching or closing a handle invalidates every outstanding acquisition of
/// that object; a later acquire for the old identity creates a new object with
/// a fresh count. [ChipDeviceController.destroy] is synchronous and local-only,
/// so it invalidates immediately: a release queued before it then fails as
/// closed, while a queued acquire cleans up the abandoned native handle.
class ChipDeviceControllerManager {
  ChipDeviceControllerManager._();

  /// The process-wide controller lifecycle manager.
  static final ChipDeviceControllerManager instance =
      ChipDeviceControllerManager._();

  ChipDeviceController? _active;
  ChipDeviceController? _abandoned;
  int _acquisitionCount = 0;
  _ControllerManagerPhase _phase = _ControllerManagerPhase.idle;
  ControllerLifecycleException? _poison;
  Future<void> _operationTail = Future<void>.value();

  /// The controller currently owning the native slot.
  ///
  /// Returns `null` while creating, switching, shutting down, poisoned, or
  /// after the active handle has closed.
  ChipDeviceController? get activeController {
    final controller = _active;
    if (_phase != _ControllerManagerPhase.active ||
        controller == null ||
        controller._isClosed) {
      return null;
    }
    return controller;
  }

  /// Whether a live controller currently owns the native controller slot.
  bool get hasActiveController => activeController != null;

  /// Acquires the controller for [params], creating or switching when needed.
  ///
  /// Identical fabric identity requests share one Dart object. A different
  /// identity immediately invalidates and closes the old handle before native
  /// deletion starts, then creates the replacement after deletion succeeds.
  Future<ChipDeviceController> acquire(ControllerParams params) {
    return _serialize(() async {
      _throwIfPoisoned('acquire');

      final current = _active;
      if (current != null &&
          !current._isClosed &&
          _sameIdentity(current.params, params)) {
        _acquisitionCount++;
        return current;
      }

      if (current != null) {
        await _shutdownActive(current, _ControllerManagerPhase.switching);
      } else if (_abandoned != null) {
        await _shutdownAbandoned(_ControllerManagerPhase.switching);
      }

      _throwIfPoisoned('acquire');
      _phase = _ControllerManagerPhase.switching;
      try {
        final controller = await ChipDeviceController._create(params);
        _active = controller;
        _acquisitionCount = 1;
        _phase = _ControllerManagerPhase.active;
        return controller;
      } on ControllerLifecycleException catch (error, stackTrace) {
        if (error.reason == ControllerLifecycleFailure.nativeStateConflict) {
          _poisonControllerManager(
            reason: ControllerLifecycleFailure.nativeStateConflict,
            message: error.message,
            operation: 'new',
            error: error,
            stackTrace: stackTrace,
          );
          throw _poison!;
        }
        _phase = _ControllerManagerPhase.idle;
        rethrow;
      } catch (_) {
        _phase = _ControllerManagerPhase.idle;
        rethrow;
      }
    });
  }

  /// Releases one acquisition of [controller].
  ///
  /// Only the final release invalidates the handle and requests native
  /// deletion. Releasing a closed, superseded, or non-active controller throws
  /// [ControllerLifecycleFailure.closed]. Each successful [acquire] must have
  /// exactly one matching release or [ChipDeviceController.close] call.
  Future<void> release(ChipDeviceController controller) {
    return _serialize(() async {
      _throwIfPoisoned('release');
      final current = _active;
      if (current == null ||
          !identical(current, controller) ||
          controller._isClosed) {
        throw ControllerLifecycleException(
          ControllerLifecycleFailure.closed,
          'Controller is no longer active; cannot release it',
          methodName: 'release',
        );
      }
      if (_acquisitionCount <= 0) {
        throw ControllerLifecycleException(
          ControllerLifecycleFailure.nativeStateConflict,
          'Controller acquisition count is invalid',
          methodName: 'release',
        );
      }

      _acquisitionCount--;
      if (_acquisitionCount > 0) {
        return;
      }
      await _shutdownActive(
        controller,
        _ControllerManagerPhase.shuttingDown,
      );
    });
  }

  /// Force-closes the active or abandoned controller and clears acquisitions.
  ///
  /// A successful call leaves the manager idle and reusable. Native shutdown
  /// failure poisons the manager until process restart.
  Future<void> closeAll() {
    return _serialize(() async {
      _throwIfPoisoned('closeAll');
      _phase = _ControllerManagerPhase.shuttingDown;
      final current = _active;
      if (current != null) {
        await _shutdownActive(current, _ControllerManagerPhase.shuttingDown);
      } else if (_abandoned != null) {
        await _shutdownAbandoned(_ControllerManagerPhase.shuttingDown);
      }
      if (_phase != _ControllerManagerPhase.poisoned) {
        _phase = _ControllerManagerPhase.idle;
      }
    });
  }

  /// Records a local-only destroy so the next acquire can clean up native state.
  void _controllerDestroyed(ChipDeviceController controller) {
    if (identical(_active, controller)) {
      _active = null;
      _acquisitionCount = 0;
      _abandoned = controller;
      _phase = _ControllerManagerPhase.idle;
      return;
    }
    if (identical(_abandoned, controller)) {
      _acquisitionCount = 0;
    }
  }

  Future<void> _shutdownActive(
    ChipDeviceController controller,
    _ControllerManagerPhase phase,
  ) async {
    _phase = phase;
    _active = null;
    _acquisitionCount = 0;
    controller._markClosed();
    try {
      await controller._requestPlatformUnchecked(
        'deleteDeviceController',
        jsonEncode({jsonKeyHandle: controller._platformDeviceControllerHandle}),
      );
      _phase = _ControllerManagerPhase.idle;
    } catch (error, stackTrace) {
      _poisonControllerManager(
        reason: ControllerLifecycleFailure.shutdownFailed,
        message: 'Native controller shutdown failed; restart the process '
            'before creating another controller',
        operation: 'deleteDeviceController',
        error: error,
        stackTrace: stackTrace,
      );
      throw _poison!;
    }
  }

  Future<void> _shutdownAbandoned(_ControllerManagerPhase phase) async {
    final controller = _abandoned!;
    _abandoned = null;
    _phase = phase;
    try {
      await controller._requestPlatformUnchecked(
        'deleteDeviceController',
        jsonEncode({jsonKeyHandle: controller._platformDeviceControllerHandle}),
      );
      _phase = _ControllerManagerPhase.idle;
    } catch (error, stackTrace) {
      _poisonControllerManager(
        reason: ControllerLifecycleFailure.shutdownFailed,
        message: 'Native controller shutdown failed; restart the process '
            'before creating another controller',
        operation: 'deleteDeviceController',
        error: error,
        stackTrace: stackTrace,
      );
      throw _poison!;
    }
  }

  void _poisonControllerManager({
    required ControllerLifecycleFailure reason,
    required String message,
    required String operation,
    required Object error,
    required StackTrace stackTrace,
  }) {
    _active = null;
    _abandoned = null;
    _acquisitionCount = 0;
    _phase = _ControllerManagerPhase.poisoned;
    _poison = ControllerLifecycleException(
      reason,
      message,
      methodName: operation,
      cause: error,
    );
    reportMatterError(
        'ChipDeviceControllerManager.$operation', error, stackTrace);
  }

  void _throwIfPoisoned(String operation) {
    final poison = _poison;
    if (poison == null) {
      return;
    }
    throw ControllerLifecycleException(
      poison.reason,
      'Controller manager is poisoned by an earlier shutdown failure; cannot '
      'perform $operation',
      methodName: operation,
      cause: poison.cause,
    );
  }

  Future<T> _serialize<T>(Future<T> Function() operation) {
    final completer = Completer<T>();
    _operationTail = _operationTail.then((_) async {
      try {
        completer.complete(await operation());
      } catch (error, stackTrace) {
        completer.completeError(error, stackTrace);
      }
    });
    return completer.future;
  }

  bool _sameIdentity(ControllerParams left, ControllerParams right) {
    return left.fabricId == right.fabricId &&
        listEquals(left.rootCertificate, right.rootCertificate);
  }

  /// Clears in-memory lifecycle state without issuing a native request.
  ///
  /// This is intentionally limited to tests that swap platform transports.
  @visibleForTesting
  void resetForTesting() {
    _active?._markClosed();
    _abandoned?._markClosed();
    _active = null;
    _abandoned = null;
    _acquisitionCount = 0;
    _phase = _ControllerManagerPhase.idle;
    _poison = null;
    _operationTail = Future<void>.value();
  }
}

Uint8List _platformBytesOrThrow(
  Map<String, dynamic> jsonData,
  String methodName,
) {
  try {
    final data = jsonData['data'];
    if (data is! List) {
      throw const FormatException('data must be a byte array');
    }
    return toUint8List(data);
  } catch (error) {
    throw PlatformProtocolException(
      'data must be a byte array',
      code: unHandlerException,
      methodName: methodName,
      cause: error,
    );
  }
}
