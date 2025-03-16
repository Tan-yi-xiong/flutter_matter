import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter/widgets.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/constant.dart';
import 'package:flutter_matter/src/onboarding.dart';
import 'package:flutter_matter/src/utils.dart';

import 'callback_handler.dart';
import 'exception.dart';

const String bleHostName = "BLE";

const BLE_ERROR_ADAPTER_UNAVAILABLE = 0x01;

// unused                                 =0x02)

///  @def BLE_ERROR_NO_CONNECTION_RECEIVED_CALLBACK
///
///  @brief
///    No callback was registered to receive a BLE Transport Protocol (BTP)
///    connection.
///
const BLE_ERROR_NO_CONNECTION_RECEIVED_CALLBACK = 0x03;

///  @def BLE_ERROR_CENTRAL_UNSUBSCRIBED
///
///  @brief
///    A BLE central device unsubscribed from a peripheral device's BLE
///    Transport Protocol (BTP) transmit characteristic.
///
const BLE_ERROR_CENTRAL_UNSUBSCRIBED = 0x04;

///  @def BLE_ERROR_GATT_SUBSCRIBE_FAILED
///
///  @brief
///    A BLE central device failed to subscribe to a peripheral device's BLE
///    Transport Protocol (BTP) transmit characteristic.
///
const BLE_ERROR_GATT_SUBSCRIBE_FAILED = 0x05;

///  @def BLE_ERROR_GATT_UNSUBSCRIBE_FAILED
///
///  @brief
///    A BLE central device failed to unsubscribe from a peripheral device's
///    BLE Transport Protocol (BTP) transmit characteristic.
///
const BLE_ERROR_GATT_UNSUBSCRIBE_FAILED = 0x06;

///  @def BLE_ERROR_GATT_WRITE_FAILED
///
///  @brief
///    A General Attribute Profile (GATT) write operation failed.
///
const BLE_ERROR_GATT_WRITE_FAILED = 0x07;

///  @def BLE_ERROR_GATT_INDICATE_FAILED
///
///  @brief
///    A General Attribute Profile (GATT) indicate operation failed.
///
const BLE_ERROR_GATT_INDICATE_FAILED = 0x08;

// unused                                 =0x09)
// unused                                 =0x0a)

///  @def BLE_ERROR_CHIPOBLE_PROTOCOL_ABORT
///
///  @brief
///    A BLE Transport Protocol (BTP) error was encountered.
///
const BLE_ERROR_CHIPOBLE_PROTOCOL_ABORT = 0x0b;

///  @def BLE_ERROR_REMOTE_DEVICE_DISCONNECTED
///
///  @brief
///    A remote BLE connection peer disconnected, either actively or due to the
///    expiration of a BLE connection supervision timeout.
///
const BLE_ERROR_REMOTE_DEVICE_DISCONNECTED = 0x0c;

///  @def BLE_ERROR_APP_CLOSED_CONNECTION
///
///  @brief
///    The local application closed a BLE connection, and has informed BleLayer.
///
const BLE_ERROR_APP_CLOSED_CONNECTION = 0x0d;

// unused                                 =0x0e)

///  @def BLE_ERROR_NOT_CHIP_DEVICE
///
///  @brief
///    A BLE peripheral device did not expose the General Attribute Profile
///    (GATT) service required by the Bluetooth Transport Protocol (BTP).
///
const BLE_ERROR_NOT_CHIP_DEVICE = 0x0f;

///  @def BLE_ERROR_INCOMPATIBLE_PROTOCOL_VERSIONS
///
///  @brief
///    A remote device does not offer a compatible version of the Bluetooth
///    Transport Protocol (BTP).
///
const BLE_ERROR_INCOMPATIBLE_PROTOCOL_VERSIONS = 0x10;

// unused                                 =0x11)
// unused                                 =0x12)

///  @def BLE_ERROR_INVALID_FRAGMENT_SIZE
///
///  @brief
///    A remote device selected in invalid Bluetooth Transport Protocol (BTP)
///    fragment size.
///
const BLE_ERROR_INVALID_FRAGMENT_SIZE = 0x13;

///  @def BLE_ERROR_START_TIMER_FAILED
///
///  @brief
///    A timer failed to start within BleLayer.
///
const BLE_ERROR_START_TIMER_FAILED = 0x14;

///  @def BLE_ERROR_CONNECT_TIMED_OUT
///
///  @brief
///    A remote BLE peripheral device's Bluetooth Transport Protocol (BTP)
///    connect handshake response timed out.
///
const BLE_ERROR_CONNECT_TIMED_OUT = 0x15;

///  @def BLE_ERROR_RECEIVE_TIMED_OUT
///
///  @brief
///    A remote BLE central device's Bluetooth Transport Protocol (BTP) connect
///    handshake timed out.
///
const BLE_ERROR_RECEIVE_TIMED_OUT = 0x16;

///  @def BLE_ERROR_INVALID_MESSAGE
///
///  @brief
///    An invalid Bluetooth Transport Protocol (BTP) message was received.
///
const BLE_ERROR_INVALID_MESSAGE = 0x17;

///  @def BLE_ERROR_FRAGMENT_ACK_TIMED_OUT
///
///  @brief
///    Receipt of an expected Bluetooth Transport Protocol (BTP) fragment
///    acknowledgement timed out.
///
const BLE_ERROR_FRAGMENT_ACK_TIMED_OUT = 0x18;

///  @def BLE_ERROR_KEEP_ALIVE_TIMED_OUT
///
///  @brief
///    Receipt of an expected Bluetooth Transport Protocol (BTP) keep-alive
///    fragment timed out.
///
const BLE_ERROR_KEEP_ALIVE_TIMED_OUT = 0x19;

///  @def BLE_ERROR_NO_CONNECT_COMPLETE_CALLBACK
///
///  @brief
///    No callback was registered to handle Bluetooth Transport Protocol (BTP)
///    connect completion.
///
const BLE_ERROR_NO_CONNECT_COMPLETE_CALLBACK = 0x1a;

///  @def BLE_ERROR_INVALID_ACK
///
///  @brief
///    A Bluetooth Transport Protcol (BTP) fragment acknowledgement was invalid.
///
const BLE_ERROR_INVALID_ACK = 0x1b;

///  @def BLE_ERROR_REASSEMBLER_MISSING_DATA
///
///  @brief
///    A Bluetooth Transport Protocol (BTP) end-of-message fragment was
///    received, but the total size of the received fragments is less than
///    the indicated size of the original fragmented message.
///
const BLE_ERROR_REASSEMBLER_MISSING_DATA = 0x1c;

///  @def BLE_ERROR_INVALID_BTP_HEADER_FLAGS
///
///  @brief
///    A set of Bluetooth Transport Protocol (BTP) header flags is invalid.
///
const BLE_ERROR_INVALID_BTP_HEADER_FLAGS = 0x1d;

///  @def BLE_ERROR_INVALID_BTP_SEQUENCE_NUMBER
///
///  @brief
///    A Bluetooth Transport Protocol (BTP) fragment sequence number is invalid.
///
const BLE_ERROR_INVALID_BTP_SEQUENCE_NUMBER = 0x1e;

///  @def BLE_ERROR_REASSEMBLER_INCORRECT_STATE
///
///  @brief
///    The Bluetooth Transport Protocol (BTP) message reassembly engine
///    encountered an unexpected state.
///
const BLE_ERROR_REASSEMBLER_INCORRECT_STATE = 0x1f;

abstract class BlePlatformDelegate {
  Future<bool> subscribeCharacteristic(
      dynamic connObj, Uint8List svcId, Uint8List charId);
  Future<bool> unsubscribeCharacteristic(
      dynamic connObj, Uint8List svcId, Uint8List charId);
  Future<bool> closeConnection(dynamic connObj);
  Future<int> getMTU(dynamic connObj);
  Future<bool> sendIndication(
      dynamic connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf);
  Future<bool> sendWriteRequest(
      dynamic connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf);
  Future<bool> sendReadRequest(
      dynamic connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf);
  Future<bool> sendReadResponse(dynamic connObj, dynamic requestContext,
      Uint8List svcId, Uint8List charId);
}

class BlePlatformDelegateCallbackHandler
    extends CallbackHandler<BlePlatformDelegate> {
  @override
  onCallbackMethodCall(String methodName, arguments) async {
    final decodeArgs = jsonDecode(arguments);
    BlePlatformDelegate? delegate =
        handlers[checkCallArgNotNull(decodeArgs, jsonKeyHandle).toString()];
    if (delegate == null) {
      return createPlatformCallExceptionResult(
          argsInvalid, "Not found BlePlatformDelegate handle");
    }
    switch (methodName) {
      case 'subscribeCharacteristic':
        final result = await delegate.subscribeCharacteristic(
            checkCallArgNotNull(decodeArgs, 'connObj'),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'svcId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'charId').cast<int>()));
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'sendReadResponse':
        final result = await delegate.sendReadResponse(
            checkCallArgNotNull(decodeArgs, 'connObj'),
            checkCallArgNotNull(decodeArgs, 'requestContext'),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'svcId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'charId').cast<int>()));
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'sendWriteRequest':
        final result = await delegate.sendWriteRequest(
            checkCallArgNotNull(decodeArgs, 'connObj'),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'svcId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'charId').cast<int>()),
            Uint8List.fromList(
              checkCallArgNotNull(decodeArgs, 'data').cast<int>()));
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'sendReadRequest':
        final result = await delegate.sendReadRequest(
            checkCallArgNotNull(decodeArgs, 'connObj'),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'svcId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'charId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'data').cast<int>()));
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'sendIndication':
        final result = await delegate.sendIndication(
            checkCallArgNotNull(decodeArgs, 'connObj'),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'svcId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'charId').cast<int>()),
            Uint8List.fromList(
                checkCallArgNotNull(decodeArgs, 'data').cast<int>()));
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'unsubscribeCharacteristic':
        final result = await delegate.unsubscribeCharacteristic(
          checkCallArgNotNull(decodeArgs, 'connObj'),
          Uint8List.fromList(
              checkCallArgNotNull(decodeArgs, 'svcId').cast<int>()),
          Uint8List.fromList(
              checkCallArgNotNull(decodeArgs, 'charId').cast<int>()),
        );
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'closeConnection':
        final result = await delegate.closeConnection(
          checkCallArgNotNull(decodeArgs, 'connObj'),
        );
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
      case 'getMTU':
        final result = await delegate.getMTU(checkCallArgNotNull(decodeArgs, 'connObj'));
        return createPlatformCallSuccessResult(
            successMsg: jsonEncode({'data': result}));
    }
    return createPlatformCallExceptionResult(
        methodNoFound, 'Not found method $methodName');
  }
}

final BlePlatformDelegateCallbackHandler _blePlatformDelegateCallbackHandler =
    BlePlatformDelegateCallbackHandler();

class BLELayerPlatform {

  static Future<Map<String, dynamic>?> _requestPlatform(String methodName, String methodParamsJson) async {
    final channelFlutterMatter = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
    final result = await channelFlutterMatter.requestPlatform(
      RequestPlatformParams(methodName: createRequestPlatformUrl(bleHostName, methodName), methodParamsJson: methodParamsJson));
    if (result.code == 0) {
      return result.jsonData;
    }
    throw CallPlatformException("[${result.code}] Call $methodName params $methodParamsJson failed");
  }

  static Future<void> setBlePlatformDelegate(
      BlePlatformDelegate? delegate) async {
    if (delegate != null && _blePlatformDelegateCallbackHandler.handlers.isNotEmpty) {
      throw Exception("Already set delegate");
    }
    final channel =
        FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
    final String? id;
    if (delegate == null) {
      id = null;
      for (var element in _blePlatformDelegateCallbackHandler.handlers.keys.toList()) {
        _blePlatformDelegateCallbackHandler.removeHandler(element);
      }
    } else {
      id = _blePlatformDelegateCallbackHandler.addHandler(delegate);
    }
    final result = await channel.requestPlatform(RequestPlatformParams(
        methodName:
            createRequestPlatformUrl(bleHostName, 'setBlePlatformDelegate'),
        methodParamsJson: jsonEncode({jsonKeyHandle: id})));
    if (result.code != 0) {
      throw Exception("setBlePlatformDelegate failed ${result.code}");
    }
  }

  static Future<bool> handleSubscribeReceived(
      dynamic connObj, Uint8List svcId, Uint8List charId) async {
        final result = await _requestPlatform(
          'handleSubscribeReceived', jsonEncode({
            'connObj': connObj,
            'svcId': List.from(svcId),
            'charId': List.from(charId),
          })
        );
        return true;
  }

  static Future<bool> handleSubscribeComplete(
      dynamic connObj, Uint8List svcId, Uint8List charId, bool success) async {
        
        final result = await _requestPlatform(
          'handleSubscribeComplete', jsonEncode({
            'connObj': connObj,
            'svcId': List.from(svcId),
            'charId': List.from(charId),
            'success': success,
          })
        );
        return true;
      }

  /// < Platform must call this function when a GATT unsubscribe is requested on any CHIP
  ///   service charateristic, that is, when an existing GATT subscription on a CHIP service
  ///   characteristic is canceled.
  static Future<bool> handleUnsubscribeReceived(
      dynamic connObj, Uint8List svcId, Uint8List charId) async {
      final result = await _requestPlatform(
        'handleUnsubscribeReceived', jsonEncode({
          'connObj': connObj,
          'svcId': List.from(svcId),
          'charId': List.from(charId),
        })
      );
      return true;
  }

  /// Call when a GATT unsubscribe request succeeds.
  static Future<bool> handleUnsubscribeComplete(
      dynamic connObj, Uint8List svcId, Uint8List charId, bool success) async {
    final result = await _requestPlatform(
      'handleUnsubscribeComplete', jsonEncode({
        'connObj': connObj,
        'svcId': List.from(svcId),
        'charId': List.from(charId),
        'success': success,
      })
    );
    return true;
  }

  /// Call when a GATT write request is received.
  static Future<bool> handleWriteReceived(
      dynamic connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf) async {
    final result = await _requestPlatform(
      'handleWriteReceived', jsonEncode({
        'connObj': connObj,
        'svcId': List.from(svcId),
        'charId': List.from(charId),
        'pBuf': List.from(pBuf),
      })
    );
    return result!['data'] == true;
  }

  /// Call when a GATT indication is received.
  static Future<bool> handleIndicationReceived(
      dynamic connObj, Uint8List svcId, Uint8List charId, Uint8List pBuf) async {
    final result = await _requestPlatform(
      'handleIndicationReceived', jsonEncode({
        'connObj': connObj,
        'svcId': List.from(svcId),
        'charId': List.from(charId),
        'pBuf': List.from(pBuf),
      })
    );
    return true;
  }

  /// Call when an outstanding GATT write request receives a positive receipt confirmation.
  static Future<bool> handleWriteConfirmation(
      dynamic connObj, Uint8List svcId, Uint8List charId, bool success) async {
    final result = await _requestPlatform(
      'handleWriteConfirmation', jsonEncode({
        'connObj': connObj,
        'svcId': List.from(svcId),
        'charId': List.from(charId),
        'success': success,
      })
    );
    return true;
  }

  /// Call when an outstanding GATT indication receives a positive receipt confirmation.
  static Future<bool> handleIndicationConfirmation(
      dynamic connObj, Uint8List svcId, Uint8List charId, bool success) async {
    final result = await _requestPlatform(
      'handleIndicationConfirmation', jsonEncode({
        'connObj': connObj,
        'svcId': List.from(svcId),
        'charId': List.from(charId),
        'success': success
      })
    );
    return true;
  }

  // /// Call when a GATT read request is received.
  // Future<bool> handleReadReceived(dynamic connObj, BLE_READ_REQUEST_CONTEXT requestContext, Uint8List svcId,
  //                         Uint8List charId);

  /// < Platform must call this function when any previous operation undertaken by the BleLayer via BleAdapter
  ///   fails, such as a characteristic write request or subscribe attempt, or when a BLE connection is closed.
  ///
  ///   In most cases, this will prompt CHIP to close the associated chipConnection and notify that platform that
  ///   it has abandoned the underlying BLE connection.
  ///
  ///   NOTE: if the application explicitly closes a BLE connection with an associated chipConnection such that
  ///   the BLE connection close will not generate an upcall to CHIP, HandleConnectionError must be called with
  ///   err = BLE_ERROR_APP_CLOSED_CONNECTION to prevent the leak of this chipConnection and its end point object.
  static Future<void> handleConnectionError(dynamic connObj, int err) async {
    await _requestPlatform(
      'handleConnectionError',
      jsonEncode({
        'connObj': connObj,
        'err': err,
      })
    );
  }
}

class BLEManager {
  late MethodChannelFlutterMatter _channel;

  BLEManager() {
    _channel = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
  }

  Future<int?> connect(OnboardingPayload onboardingPayload) async {
    final result = await _channel.requestPlatform(RequestPlatformParams(
        methodName: createRequestPlatformUrl(bleHostName, 'connectDevice'),
        methodParamsJson: jsonEncode({
          'isShortDiscriminator': onboardingPayload.hasShortDiscriminator,
          'discriminator': onboardingPayload.discriminator,
        })));
    if (result.code != successCode) {
      matterPrint('BLE connect failed code: ${result.code}');
      return null;
    }
    final connectId = result.jsonData['data'];
    return connectId >= 0 ? connectId : null;
  }

  Future<void> disconnect(int connectId) async {
    final result = await _channel.requestPlatform(RequestPlatformParams(
        methodName: createRequestPlatformUrl(bleHostName, 'disconnect'),
        methodParamsJson: jsonEncode({"connectId": connectId})));
    if (result.code != successCode) {
      matterPrint('BLE disconnect failed code: ${result.code}');
      throw Exception("BLE disconnect failed ${result.code}");
    }
  }
}