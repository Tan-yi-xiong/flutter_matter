import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import 'matter_ble_contracts.dart';
import 'matter_ble_gatt_session.dart';

abstract interface class MatterBleLayerBridge {
  Future<void> setDelegate(BlePlatformDelegate? delegate);

  Future<void> handleSubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  });

  Future<void> handleUnsubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  });

  Future<void> handleIndicationReceived({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required Uint8List value,
  });

  Future<void> handleWriteConfirmation({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  });

  Future<void> handleConnectionError({
    required Object? connection,
    required int errorCode,
  });
}

class FlutterMatterBleLayerBridge implements MatterBleLayerBridge {
  FlutterMatterBleLayerBridge({
    this.operationTimeout = const Duration(seconds: 10),
  });

  final Duration operationTimeout;

  @override
  Future<void> setDelegate(BlePlatformDelegate? delegate) {
    return withMatterBleTimeout<void>(
      future: BLELayerPlatform.setBlePlatformDelegate(delegate),
      timeout: operationTimeout,
      operation: 'Set Matter BLE platform delegate',
    );
  }

  @override
  Future<void> handleSubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) {
    return withMatterBleTimeout<void>(
      future: BLELayerPlatform.handleSubscribeComplete(
        connection,
        serviceId,
        characteristicId,
        success,
      ).then<void>((_) {}),
      timeout: operationTimeout,
      operation: 'Report Matter GATT subscription result',
    );
  }

  @override
  Future<void> handleUnsubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) {
    return withMatterBleTimeout<void>(
      future: BLELayerPlatform.handleUnsubscribeComplete(
        connection,
        serviceId,
        characteristicId,
        success,
      ).then<void>((_) {}),
      timeout: operationTimeout,
      operation: 'Report Matter GATT unsubscription result',
    );
  }

  @override
  Future<void> handleIndicationReceived({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required Uint8List value,
  }) {
    return withMatterBleTimeout<void>(
      future: BLELayerPlatform.handleIndicationReceived(
        connection,
        serviceId,
        characteristicId,
        value,
      ).then<void>((_) {}),
      timeout: operationTimeout,
      operation: 'Forward Matter GATT indication',
    );
  }

  @override
  Future<void> handleWriteConfirmation({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) {
    return withMatterBleTimeout<void>(
      future: BLELayerPlatform.handleWriteConfirmation(
        connection,
        serviceId,
        characteristicId,
        success,
      ).then<void>((_) {}),
      timeout: operationTimeout,
      operation: 'Report Matter GATT write result',
    );
  }

  @override
  Future<void> handleConnectionError({
    required Object? connection,
    required int errorCode,
  }) {
    return withMatterBleTimeout<void>(
      future: BLELayerPlatform.handleConnectionError(connection, errorCode),
      timeout: operationTimeout,
      operation: 'Report Matter GATT connection error',
    );
  }
}

class MatterGattBleDelegate implements BlePlatformDelegate {
  MatterGattBleDelegate({
    required MatterBleGattSession session,
    required MatterBleLayerBridge bridge,
    this.operationTimeout = const Duration(seconds: 10),
  }) : _session = session,
       _bridge = bridge;

  final MatterBleGattSession _session;
  final MatterBleLayerBridge _bridge;
  final Duration operationTimeout;
  final Map<String, _NotificationForwarder> _forwarders = {};

  String _key(Uint8List serviceId, Uint8List characteristicId) {
    return '${serviceId.join(':')}/${characteristicId.join(':')}';
  }

  Future<void> _reportConnectionFailure(Object? connection) async {
    try {
      await _bridge.handleConnectionError(
        connection: connection,
        errorCode: BLE_ERROR_REMOTE_DEVICE_DISCONNECTED,
      );
    } catch (_) {
      // The transport is already failing; avoid an unhandled callback error.
    }
  }

  Future<void> _forwardIndication(
    Object? connection,
    Uint8List serviceId,
    Uint8List characteristicId,
    Uint8List value,
  ) async {
    try {
      await _bridge.handleIndicationReceived(
        connection: connection,
        serviceId: serviceId,
        characteristicId: characteristicId,
        value: value,
      );
    } catch (_) {
      await _reportConnectionFailure(connection);
    }
  }

  @override
  Future<bool> subscribeCharacteristic(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
  ) async {
    final key = _key(svcId, charId);
    await _forwarders.remove(key)?.cancel();
    final forwarder = _NotificationForwarder();
    _forwarders[key] = forwarder;
    forwarder.subscription = _session
        .notifications(
          serviceUuid: _uuid(svcId),
          characteristicUuid: _uuid(charId),
        )
        .listen((value) {
          unawaited(_forwardIndication(connObj, svcId, charId, value));
        });

    var success = false;
    try {
      await _session.setNotify(
        serviceUuid: _uuid(svcId),
        characteristicUuid: _uuid(charId),
        enabled: true,
        timeout: operationTimeout,
      );
      success = true;
      await _bridge.handleSubscribeComplete(
        connection: connObj,
        serviceId: svcId,
        characteristicId: charId,
        success: true,
      );
      return true;
    } catch (_) {
      await _forwarders.remove(key)?.cancel();
      try {
        await _bridge.handleSubscribeComplete(
          connection: connObj,
          serviceId: svcId,
          characteristicId: charId,
          success: false,
        );
      } catch (_) {
        await _reportConnectionFailure(connObj);
      }
      return success;
    }
  }

  @override
  Future<bool> unsubscribeCharacteristic(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
  ) async {
    final key = _key(svcId, charId);
    await _forwarders.remove(key)?.cancel();
    var success = false;
    try {
      await _session.setNotify(
        serviceUuid: _uuid(svcId),
        characteristicUuid: _uuid(charId),
        enabled: false,
        timeout: operationTimeout,
      );
      success = true;
    } catch (_) {
      success = false;
    }
    try {
      await _bridge.handleUnsubscribeComplete(
        connection: connObj,
        serviceId: svcId,
        characteristicId: charId,
        success: success,
      );
    } catch (_) {
      await _reportConnectionFailure(connObj);
    }
    return success;
  }

  @override
  Future<bool> sendWriteRequest(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
    Uint8List pBuf,
  ) async {
    // CHIP invokes this callback synchronously and keeps its BLE endpoint
    // locked until the boolean result returns. The write confirmation must be
    // delivered only after that return, otherwise CHIP's subscribe callback
    // re-enters Flutter while this method is still awaiting the write.
    unawaited(
      Future<void>.delayed(Duration.zero, () async {
        var success = false;
        try {
          await _session.write(
            serviceUuid: _uuid(svcId),
            characteristicUuid: _uuid(charId),
            value: pBuf,
            withoutResponse: false,
            timeout: operationTimeout,
          );
          success = true;
        } catch (_) {
          success = false;
        }

        try {
          await _bridge.handleWriteConfirmation(
            connection: connObj,
            serviceId: svcId,
            characteristicId: charId,
            success: success,
          );
        } catch (_) {
          await _reportConnectionFailure(connObj);
        }
      }),
    );
    return true;
  }

  @override
  Future<bool> sendIndication(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
    Uint8List pBuf,
  ) async {
    return false;
  }

  @override
  Future<bool> sendReadRequest(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
    Uint8List pBuf,
  ) async {
    return false;
  }

  @override
  Future<bool> sendReadResponse(
    dynamic connObj,
    dynamic requestContext,
    Uint8List svcId,
    Uint8List charId,
  ) async {
    return false;
  }

  @override
  Future<bool> closeConnection(dynamic connObj) async {
    for (final forwarder in _forwarders.values) {
      await forwarder.cancel();
    }
    _forwarders.clear();
    try {
      await _session.disconnect(operationTimeout);
      return true;
    } catch (_) {
      await _reportConnectionFailure(connObj);
      return false;
    }
  }

  @override
  Future<int> getMTU(dynamic connObj) async {
    return _session.mtu;
  }

  String _uuid(Uint8List bytes) {
    final hex = bytes
        .map((value) => value.toRadixString(16).padLeft(2, '0'))
        .join();
    if (hex.length == 4) {
      return '0000$hex-0000-1000-8000-00805f9b34fb';
    }
    if (hex.length == 8) {
      return '$hex-0000-1000-8000-00805f9b34fb';
    }
    return '${hex.substring(0, 8)}-'
        '${hex.substring(8, 12)}-'
        '${hex.substring(12, 16)}-'
        '${hex.substring(16, 20)}-'
        '${hex.substring(20)}';
  }
}

class _NotificationForwarder {
  StreamSubscription<Uint8List>? subscription;

  Future<void> cancel() async {
    await subscription?.cancel();
    subscription = null;
  }
}
