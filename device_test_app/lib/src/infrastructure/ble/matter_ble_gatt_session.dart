import 'dart:async';
import 'dart:typed_data';

import 'matter_ble_contracts.dart';

abstract interface class MatterBleGattSession {
  String get deviceId;

  int get mtu;

  Future<void> setNotify({
    required String serviceUuid,
    required String characteristicUuid,
    required bool enabled,
    required Duration timeout,
  });

  Future<void> write({
    required String serviceUuid,
    required String characteristicUuid,
    required Uint8List value,
    required bool withoutResponse,
    required Duration timeout,
  });

  Stream<Uint8List> notifications({
    required String serviceUuid,
    required String characteristicUuid,
  });

  Future<void> disconnect(Duration timeout);
}

class DefaultMatterBleGattSession implements MatterBleGattSession {
  DefaultMatterBleGattSession._({
    required MatterBleDevice device,
    required MatterBleGattService service,
    required int mtu,
  }) : _device = device,
       _service = service,
       _mtu = mtu;

  final MatterBleDevice _device;
  final MatterBleGattService _service;
  final int _mtu;

  @override
  String get deviceId => _device.deviceId;

  @override
  int get mtu => _mtu;

  MatterBleGattCharacteristic _requireCharacteristic(
    String serviceUuid,
    String characteristicUuid,
  ) {
    if (_service.uuid.toLowerCase() != serviceUuid.toLowerCase()) {
      throw MatterBleException(
        MatterBleFailureCode.serviceNotFound,
        'Matter GATT service was not found',
      );
    }
    final characteristic = _service.characteristic(characteristicUuid);
    if (characteristic == null) {
      throw MatterBleException(
        MatterBleFailureCode.characteristicNotFound,
        'Matter GATT characteristic was not found',
      );
    }
    return characteristic;
  }

  @override
  Future<void> setNotify({
    required String serviceUuid,
    required String characteristicUuid,
    required bool enabled,
    required Duration timeout,
  }) async {
    final characteristic = _requireCharacteristic(
      serviceUuid,
      characteristicUuid,
    );
    final accepted = await characteristic.setNotify(
      enabled: enabled,
      timeout: timeout,
    );
    if (!accepted) {
      throw MatterBleException(
        MatterBleFailureCode.connectionFailed,
        'GATT notification subscription was rejected',
      );
    }
  }

  @override
  Future<void> write({
    required String serviceUuid,
    required String characteristicUuid,
    required Uint8List value,
    required bool withoutResponse,
    required Duration timeout,
  }) async {
    final characteristic = _requireCharacteristic(
      serviceUuid,
      characteristicUuid,
    );
    await characteristic.write(
      value,
      withoutResponse: withoutResponse,
      timeout: timeout,
    );
  }

  @override
  Stream<Uint8List> notifications({
    required String serviceUuid,
    required String characteristicUuid,
  }) {
    final characteristic = _requireCharacteristic(
      serviceUuid,
      characteristicUuid,
    );
    return characteristic.onValueReceived;
  }

  @override
  Future<void> disconnect(Duration timeout) {
    return withMatterBleTimeout<void>(
      future: _device.disconnect(),
      timeout: timeout,
      operation: 'Disconnect from Matter device',
    );
  }
}

abstract interface class MatterBleGattSessionFactory {
  Future<MatterBleGattSession> connect(MatterBleDevice device);
}

class DefaultMatterBleGattSessionFactory
    implements MatterBleGattSessionFactory {
  DefaultMatterBleGattSessionFactory({
    this.connectAttempts = 3,
    this.connectTimeout = const Duration(seconds: 5),
    this.discoveryTimeout = const Duration(seconds: 10),
    this.operationTimeout = const Duration(seconds: 10),
  }) {
    if (connectAttempts < 1) {
      throw ArgumentError.value(
        connectAttempts,
        'connectAttempts',
        'Must be at least one',
      );
    }
  }

  final int connectAttempts;
  final Duration connectTimeout;
  final Duration discoveryTimeout;
  final Duration operationTimeout;

  @override
  Future<MatterBleGattSession> connect(MatterBleDevice device) async {
    Object? lastFailure;
    for (var attempt = 0; attempt < connectAttempts; attempt++) {
      try {
        if (!device.isConnected) {
          await withMatterBleTimeout<void>(
            future: device.connect(connectTimeout),
            timeout: connectTimeout,
            operation: 'Connect to Matter BLE device',
          );
        }

        final services = await withMatterBleTimeout<List<MatterBleGattService>>(
          future: device.discoverServices(discoveryTimeout),
          timeout: discoveryTimeout,
          operation: 'Discover Matter GATT services',
        );
        MatterBleGattService? matterService;
        for (final service in services) {
          if (service.uuid.toLowerCase() ==
              matterGattServiceUuid.toLowerCase()) {
            matterService = service;
            break;
          }
        }
        if (matterService == null) {
          throw MatterBleException(
            MatterBleFailureCode.serviceNotFound,
            'Matter GATT service was not discovered',
          );
        }
        return DefaultMatterBleGattSession._(
          device: device,
          service: matterService,
          mtu: device.mtu,
        );
      } catch (error) {
        lastFailure = error;
        if (device.isConnected) {
          try {
            await withMatterBleTimeout<void>(
              future: device.disconnect(),
              timeout: operationTimeout,
              operation: 'Reset Matter BLE connection',
            );
          } catch (_) {
            // A later attempt may still establish a clean connection.
          }
        }
      }
    }

    throw MatterBleException(
      MatterBleFailureCode.connectionFailed,
      'Unable to connect to the Matter BLE device after '
      '$connectAttempts attempt(s)',
      lastFailure,
    );
  }
}
