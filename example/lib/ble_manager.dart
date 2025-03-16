import 'dart:async';

import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart' hide ScanResult;
import 'package:hex/hex.dart';
import 'package:collection/collection.dart';

class BleManager {
  static final flutterReactiveBle = FlutterReactiveBle();
  static final connecteds = Map<String, BluetoothDevice>();
  static final matter_uuid = Guid.fromString("0000fff6-0000-1000-8000-00805f9b34fb");

  static Future<ScanResult?> getDevice(OnboardingPayload payload) async {
    Completer<ScanResult?> completer = Completer();
    late StreamSubscription ss;
    await FlutterBluePlus.stopScan();
    await FlutterBluePlus.adapterState.where((val) => val == BluetoothAdapterState.on).first;
    ss = FlutterBluePlus.onScanResults.listen((event) {
      final dev = event.firstWhereOrNull(
        (element) => element.advertisementData.serviceData.containsKey(matter_uuid));
      if (dev != null) {
        final data = dev.advertisementData.serviceData[matter_uuid]!.reversed.toList();
        print('object ${int.parse(HEX.encode(data.sublist(data.length - 3)), radix: 16) >> 8}');
        if (payload.discriminator == int.parse(HEX.encode(data.sublist(data.length - 3)), radix: 16) >> 8) {
          FlutterBluePlus.stopScan();
          ss.cancel();
          completer.complete(dev);
        }
      }
    });

    FlutterBluePlus.cancelWhenScanComplete(ss);
    FlutterBluePlus.startScan(timeout: Duration(seconds: 15));
    return completer.future.timeout(Duration(seconds: 15)).catchError((_) => null).whenComplete(() => ss.cancel());
  }

  static Future<bool> connect(ScanResult result) async {
    Completer<bool> completer = Completer();
    connecteds[result.device.remoteId.toString()] = result.device;
    await result.device.connect(timeout: Duration(seconds: 5)).catchError((_) {
      completer.complete(false);
      
    });
    if (result.device.isConnected) {
      await result.device.discoverServices().then((value) {
        value.forEach((element) {
          print('${element.serviceUuid}: ');
          print("Characteristics: ");
          element.characteristics.forEach((char) {
            print('  ${char.uuid}');
          });
        });
        completer.complete(true);
      });
    }
    return completer.future;
  }

  static BluetoothDevice? getConnDevice() {
    return connecteds.values.firstOrNull;
  }

  static void disconnectAll() {
    connecteds.forEach((key, value) {
      value.disconnect();
    });
    connecteds.clear();
  }
}