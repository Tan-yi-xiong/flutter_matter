import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_blue_plus/flutter_blue_plus.dart';

import 'matter_ble_contracts.dart';

final Guid _matterMatterGuid = Guid.fromString(matterGattServiceUuid);

/// FlutterBluePlus-backed implementation of the Matter BLE platform.
class FlutterBluePlusMatterBlePlatform implements MatterBlePlatform {
  @override
  Stream<MatterBleAdvertisement> get advertisements {
    return FlutterBluePlus.onScanResults.expand(
      (results) => results.map(_toAdvertisement),
    );
  }

  @override
  Future<void> ensureAdapterIsOn(Duration timeout) {
    return withMatterBleTimeout<void>(
      future: FlutterBluePlus.adapterState
          .where((state) => state == BluetoothAdapterState.on)
          .first,
      timeout: timeout,
      operation: 'Wait for Bluetooth adapter',
    );
  }

  @override
  Future<void> startScan(Duration timeout) {
    return withMatterBleTimeout<void>(
      future: FlutterBluePlus.startScan(
        withServices: <Guid>[_matterMatterGuid],
        timeout: timeout,
        androidUsesFineLocation: true,
      ),
      timeout: timeout,
      operation: 'Start Matter BLE scan',
    );
  }

  @override
  Future<void> stopScan() {
    return FlutterBluePlus.stopScan();
  }

  MatterBleAdvertisement _toAdvertisement(ScanResult result) {
    final serviceData = <String, Uint8List>{};
    for (final entry in result.advertisementData.serviceData.entries) {
      serviceData[entry.key.str128] = Uint8List.fromList(entry.value);
    }
    return MatterBleAdvertisement(
      device: _FlutterBluePlusMatterBleDevice(result.device),
      serviceData: serviceData,
      rssi: result.rssi,
      advertisedName: result.advertisementData.advName,
    );
  }
}

class _FlutterBluePlusMatterBleDevice implements MatterBleDevice {
  _FlutterBluePlusMatterBleDevice(this._device);

  final BluetoothDevice _device;

  @override
  String get deviceId => _device.remoteId.str;

  @override
  bool get isConnected => _device.isConnected;

  @override
  int get mtu => _device.mtuNow;

  @override
  Future<void> connect(Duration timeout) {
    return _device.connect(timeout: timeout);
  }

  @override
  Future<void> disconnect() {
    return _device.disconnect();
  }

  @override
  Future<List<MatterBleGattService>> discoverServices(Duration timeout) async {
    final services = await _device.discoverServices(timeout: _seconds(timeout));
    return services
        .map(
          (service) => MatterBleGattService(
            uuid: service.serviceUuid.str128,
            characteristics: service.characteristics
                .map<MatterBleGattCharacteristic>(
                  _FlutterBluePlusGattCharacteristic.new,
                )
                .toList(growable: false),
          ),
        )
        .toList(growable: false);
  }

  int _seconds(Duration timeout) {
    if (timeout.inMilliseconds <= 0) {
      return 1;
    }
    return (timeout.inMilliseconds / 1000).ceil();
  }
}

class _FlutterBluePlusGattCharacteristic
    implements MatterBleGattCharacteristic {
  _FlutterBluePlusGattCharacteristic(this._characteristic);

  final BluetoothCharacteristic _characteristic;

  @override
  String get uuid => _characteristic.characteristicUuid.str128;

  @override
  Stream<Uint8List> get onValueReceived {
    return _characteristic.onValueReceived.map(Uint8List.fromList);
  }

  @override
  Future<void> write(
    Uint8List value, {
    required bool withoutResponse,
    required Duration timeout,
  }) {
    return withMatterBleTimeout<void>(
      future: _characteristic.write(
        value,
        withoutResponse: withoutResponse,
        timeout: _seconds(timeout),
      ),
      timeout: timeout,
      operation: 'Write Matter GATT characteristic',
    );
  }

  @override
  Future<bool> setNotify({required bool enabled, required Duration timeout}) {
    return withMatterBleTimeout<bool>(
      future: _characteristic.setNotifyValue(
        enabled,
        timeout: _seconds(timeout),
      ),
      timeout: timeout,
      operation: 'Configure Matter GATT notifications',
    );
  }

  int _seconds(Duration timeout) {
    if (timeout.inMilliseconds <= 0) {
      return 1;
    }
    return (timeout.inMilliseconds / 1000).ceil();
  }
}
