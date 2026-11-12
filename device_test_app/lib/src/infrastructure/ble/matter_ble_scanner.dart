import 'dart:async';
import 'dart:typed_data';

import 'matter_ble_contracts.dart';

/// Parses and compares Matter commissionable-node discriminators.
class MatterDiscriminatorMatcher {
  const MatterDiscriminatorMatcher._();

  /// Extracts the full discriminator from Matter service data.
  ///
  /// Matter service data starts with an opcode byte followed by a
  /// little-endian discriminator. The historical example normalized the data
  /// by reversing it before reading its final three bytes. The equivalent
  /// operation is `(bytes[2] << 8) | bytes[1]`.
  static int? extractDiscriminator(Uint8List serviceData) {
    if (serviceData.length < 3) {
      return null;
    }
    return (serviceData[2] << 8) | serviceData[1];
  }

  static bool matches({
    required Uint8List serviceData,
    required int discriminator,
    required bool hasShortDiscriminator,
  }) {
    final observed = extractDiscriminator(serviceData);
    if (observed == null) {
      return false;
    }
    if (hasShortDiscriminator) {
      return (observed >> 8) == (discriminator & 0x0f);
    }
    return observed == discriminator;
  }
}

class MatterBleScanner implements MatterBleScannerApi {
  MatterBleScanner({
    required MatterBlePlatform platform,
    Duration cleanupTimeout = const Duration(seconds: 5),
  }) : _platform = platform,
       _cleanupTimeout = cleanupTimeout;

  final MatterBlePlatform _platform;
  final Duration _cleanupTimeout;

  @override
  Future<MatterBleDiscoveredDevice> scan(
    MatterBleDiscoveryRequest request,
  ) async {
    try {
      await withMatterBleTimeout<void>(
        future: _platform.stopScan(),
        timeout: _cleanupTimeout,
        operation: 'Stop previous BLE scan',
      );
      await withMatterBleTimeout<void>(
        future: _platform.ensureAdapterIsOn(request.timeout),
        timeout: request.timeout,
        operation: 'Wait for Bluetooth adapter',
      );

      final completer = Completer<MatterBleDiscoveredDevice>();
      StreamSubscription<MatterBleAdvertisement>? subscription;
      try {
        subscription = _platform.advertisements.listen(
          (advertisement) {
            if (completer.isCompleted) {
              return;
            }
            final serviceData = advertisement.dataForService(
              matterGattServiceUuid,
            );
            if (serviceData == null ||
                !MatterDiscriminatorMatcher.matches(
                  serviceData: serviceData,
                  discriminator: request.discriminator,
                  hasShortDiscriminator: request.hasShortDiscriminator,
                )) {
              return;
            }
            final observed = MatterDiscriminatorMatcher.extractDiscriminator(
              serviceData,
            );
            if (observed == null) {
              return;
            }
            completer.complete(
              MatterBleDiscoveredDevice(
                advertisement: advertisement,
                matterServiceData: Uint8List.fromList(serviceData),
                discriminator: observed,
              ),
            );
          },
          onError: (Object error, StackTrace stackTrace) {
            if (!completer.isCompleted) {
              completer.completeError(
                MatterBleException(
                  MatterBleFailureCode.scanFailed,
                  'Matter BLE scan stream failed',
                  error,
                ),
                stackTrace,
              );
            }
          },
        );

        await withMatterBleTimeout<void>(
          future: _platform.startScan(request.timeout),
          timeout: request.timeout,
          operation: 'Start Matter BLE scan',
        );

        try {
          return await completer.future.timeout(request.timeout);
        } on TimeoutException {
          throw MatterBleException(
            MatterBleFailureCode.discoveryTimeout,
            'No Matter BLE advertisement matched the requested discriminator '
            'within ${request.timeout.inSeconds} second(s)',
          );
        }
      } finally {
        await subscription?.cancel();
        try {
          await withMatterBleTimeout<void>(
            future: _platform.stopScan(),
            timeout: _cleanupTimeout,
            operation: 'Stop Matter BLE scan',
          );
        } catch (_) {
          // Cleanup is best effort; the primary scan outcome is already known.
        }
      }
    } on MatterBleException {
      rethrow;
    } catch (error) {
      throw MatterBleException(
        MatterBleFailureCode.scanFailed,
        'Matter BLE scan failed',
        error,
      );
    }
  }
}
