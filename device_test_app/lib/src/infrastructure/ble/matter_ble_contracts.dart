import 'dart:async';
import 'dart:typed_data';

/// The Bluetooth SIG base UUID suffix used by Matter GATT services.
const String matterGattServiceUuid = '0000fff6-0000-1000-8000-00805f9b34fb';

/// The 16-bit form of the Matter commissioning service UUID.
const int matterGattServiceShortUuid = 0xfff6;

/// The connection object used by the Android custom BLE transport path.
const int androidMatterBleConnectionId = 0x04;

/// Default budget for a single Matter BLE advertisement scan.
const Duration defaultMatterBleScanTimeout = Duration(seconds: 15);

enum MatterBleFailureCode {
  invalidArgument,
  adapterUnavailable,
  scanFailed,
  discoveryTimeout,
  deviceNotFound,
  connectionFailed,
  serviceNotFound,
  characteristicNotFound,
  operationTimeout,
  unsupportedOperation,
}

class MatterBleException implements Exception {
  MatterBleException(this.code, this.message, [this.cause]);

  final MatterBleFailureCode code;
  final String message;
  final Object? cause;

  @override
  String toString() => 'MatterBleException($code): $message';
}

class MatterBleTimeoutException extends MatterBleException {
  MatterBleTimeoutException(String operation)
    : super(MatterBleFailureCode.operationTimeout, '$operation timed out');
}

class MatterBleDiscoveryRequest {
  MatterBleDiscoveryRequest({
    required this.discriminator,
    required this.hasShortDiscriminator,
    this.timeout = defaultMatterBleScanTimeout,
  }) {
    final maximum = hasShortDiscriminator ? 0x0f : 0x0fff;
    if (discriminator < 0 || discriminator > maximum) {
      throw ArgumentError.value(
        discriminator,
        'discriminator',
        'Value must be between 0 and $maximum',
      );
    }
    if (timeout <= Duration.zero) {
      throw ArgumentError.value(timeout, 'timeout', 'Must be positive');
    }
  }

  final int discriminator;
  final bool hasShortDiscriminator;
  final Duration timeout;
}

class MatterBleAdvertisement {
  MatterBleAdvertisement({
    required this.device,
    required this.serviceData,
    required this.rssi,
    this.advertisedName,
  });

  final MatterBleDevice device;
  final Map<String, Uint8List> serviceData;
  final int rssi;
  final String? advertisedName;

  Uint8List? dataForService(String serviceUuid) {
    final normalized = serviceUuid.toLowerCase();
    for (final entry in serviceData.entries) {
      if (entry.key.toLowerCase() == normalized) {
        return entry.value;
      }
    }
    return null;
  }
}

class MatterBleDiscoveredDevice {
  MatterBleDiscoveredDevice({
    required this.advertisement,
    required this.matterServiceData,
    required this.discriminator,
  });

  final MatterBleAdvertisement advertisement;
  final Uint8List matterServiceData;
  final int discriminator;

  MatterBleDevice get device => advertisement.device;
}

abstract interface class MatterBlePlatform {
  Stream<MatterBleAdvertisement> get advertisements;

  Future<void> ensureAdapterIsOn(Duration timeout);

  Future<void> startScan(Duration timeout);

  Future<void> stopScan();
}

abstract interface class MatterBleDevice {
  String get deviceId;

  bool get isConnected;

  int get mtu;

  Future<void> connect(Duration timeout);

  Future<void> disconnect();

  Future<List<MatterBleGattService>> discoverServices(Duration timeout);
}

class MatterBleGattService {
  MatterBleGattService({required this.uuid, required this.characteristics});

  final String uuid;
  final List<MatterBleGattCharacteristic> characteristics;

  MatterBleGattCharacteristic? characteristic(String characteristicUuid) {
    final normalized = characteristicUuid.toLowerCase();
    for (final entry in characteristics) {
      if (entry.uuid.toLowerCase() == normalized) {
        return entry;
      }
    }
    return null;
  }
}

abstract interface class MatterBleGattCharacteristic {
  String get uuid;

  Stream<Uint8List> get onValueReceived;

  Future<void> write(
    Uint8List value, {
    required bool withoutResponse,
    required Duration timeout,
  });

  Future<bool> setNotify({required bool enabled, required Duration timeout});
}

Future<T> withMatterBleTimeout<T>({
  required Future<T> future,
  required Duration timeout,
  required String operation,
}) async {
  try {
    return await future.timeout(timeout);
  } on TimeoutException {
    throw MatterBleTimeoutException(operation);
  }
}
