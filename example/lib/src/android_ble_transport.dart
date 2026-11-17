import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:hex/hex.dart';

class AndroidBleTransport implements BlePlatformDelegate {
  static final Guid matterServiceUuid = Guid.fromString(
    '0000fff6-0000-1000-8000-00805f9b34fb',
  );

  BluetoothDevice? _device;
  final List<StreamSubscription<List<int>>> _notificationSubscriptions = [];
  bool _delegateInstalled = false;

  Future<int> connect(
    OnboardingPayload payload, {
    required void Function(String message) onStage,
  }) async {
    onStage('Scanning for the Matter BLE service');
    await FlutterBluePlus.stopScan();
    final adapter = await FlutterBluePlus.adapterState
        .where((state) => state == BluetoothAdapterState.on)
        .first
        .timeout(const Duration(seconds: 8));
    if (adapter != BluetoothAdapterState.on) {
      throw StateError('Bluetooth is not available.');
    }

    final device = await _scan(payload);
    if (device == null) {
      throw StateError('Matter BLE device was not found.');
    }
    onStage('Connecting over BLE');
    _device = device.device;
    await device.device.connect(timeout: const Duration(seconds: 8));
    final services = await device.device.discoverServices();
    final matterService = services.where(
      (service) => service.serviceUuid == matterServiceUuid,
    );
    if (matterService.isEmpty) {
      throw StateError('Matter GATT service was not discovered.');
    }

    for (final characteristic in matterService.first.characteristics) {
      final subscription = characteristic.onValueReceived.listen((event) {
        final connection = _device;
        if (connection == null) {
          return;
        }
        unawaited(
          BLELayerPlatform.handleIndicationReceived(
            0x04,
            Uint8List.fromList(matterServiceUuid.bytes),
            Uint8List.fromList(characteristic.characteristicUuid.bytes),
            Uint8List.fromList(event),
          ),
        );
      });
      device.device.cancelWhenDisconnected(subscription);
      _notificationSubscriptions.add(subscription);
    }

    await BLELayerPlatform.setBlePlatformDelegate(null);
    await BLELayerPlatform.setBlePlatformDelegate(this);
    _delegateInstalled = true;
    onStage('BLE transport ready');
    return 0x04;
  }

  Future<ScanResult?> _scan(OnboardingPayload payload) async {
    final completer = Completer<ScanResult?>();
    final subscription = FlutterBluePlus.onScanResults.listen((results) {
      for (final result in results) {
        final serviceData = result.advertisementData.serviceData;
        final bytes = serviceData[matterServiceUuid];
        if (bytes == null || bytes.length < 3) {
          continue;
        }
        final advertised = bytes.reversed.toList();
        final discriminatorBytes = advertised.sublist(
          0,
          advertised.length < 3 ? advertised.length : 3,
        );
        final shortDiscriminator =
            int.parse(HEX.encode(discriminatorBytes), radix: 16) >> 8;
        final expected = payload.hasShortDiscriminator
            ? payload.discriminator & 0x0F
            : payload.discriminator;
        if (shortDiscriminator == expected && !completer.isCompleted) {
          completer.complete(result);
        }
      }
    });
    await FlutterBluePlus.startScan(timeout: const Duration(seconds: 15));
    try {
      return await completer.future.timeout(const Duration(seconds: 16));
    } on TimeoutException {
      return null;
    } finally {
      await subscription.cancel();
      await FlutterBluePlus.stopScan();
    }
  }

  Future<void> dispose() async {
    for (final subscription in _notificationSubscriptions) {
      await subscription.cancel();
    }
    _notificationSubscriptions.clear();
    if (_delegateInstalled) {
      await BLELayerPlatform.setBlePlatformDelegate(null);
      _delegateInstalled = false;
    }
    final device = _device;
    _device = null;
    if (device != null) {
      await device.disconnect().catchError((_) {});
    }
  }

  @override
  Future<bool> closeConnection(dynamic connObj) async {
    final device = _device;
    if (device == null) {
      return true;
    }
    await device.disconnect().catchError((_) {});
    return true;
  }

  @override
  Future<int> getMTU(dynamic connObj) async => _device?.mtuNow ?? 23;

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
  Future<bool> sendWriteRequest(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
    Uint8List pBuf,
  ) async {
    final characteristic = _findCharacteristic(svcId, charId);
    if (characteristic == null) {
      return false;
    }
    try {
      await characteristic.write(pBuf, withoutResponse: false);
      unawaited(
        BLELayerPlatform.handleWriteConfirmation(connObj, svcId, charId, true),
      );
      return true;
    } catch (_) {
      unawaited(
        BLELayerPlatform.handleWriteConfirmation(connObj, svcId, charId, false),
      );
      return false;
    }
  }

  @override
  Future<bool> subscribeCharacteristic(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
  ) async {
    final characteristic = _findCharacteristic(svcId, charId);
    if (characteristic == null) {
      return false;
    }
    try {
      await characteristic.setNotifyValue(true);
      unawaited(
        BLELayerPlatform.handleSubscribeComplete(connObj, svcId, charId, true),
      );
      return true;
    } catch (_) {
      unawaited(
        BLELayerPlatform.handleSubscribeComplete(connObj, svcId, charId, false),
      );
      return false;
    }
  }

  @override
  Future<bool> unsubscribeCharacteristic(
    dynamic connObj,
    Uint8List svcId,
    Uint8List charId,
  ) async {
    final characteristic = _findCharacteristic(svcId, charId);
    if (characteristic == null) {
      return false;
    }
    await characteristic.setNotifyValue(false);
    return true;
  }

  BluetoothCharacteristic? _findCharacteristic(
    Uint8List serviceId,
    Uint8List characteristicId,
  ) {
    final device = _device;
    if (device == null) {
      return null;
    }
    final serviceGuid = Guid.fromBytes(serviceId);
    final characteristicGuid = Guid.fromBytes(characteristicId);
    for (final service in device.servicesList) {
      if (service.serviceUuid != serviceGuid) {
        continue;
      }
      for (final characteristic in service.characteristics) {
        if (characteristic.characteristicUuid == characteristicGuid) {
          return characteristic;
        }
      }
    }
    return null;
  }
}
