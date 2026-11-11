import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_matter/flutter_matter.dart';

import '../../application/ports.dart';
import '../ble/matter_ble.dart';
import '../matter/matter.dart';
import 'opaque_handle_factory.dart';

abstract interface class MatterOnboardingPayloadResolver {
  Future<OnboardingPayload> resolve(String payload);
}

class FlutterMatterOnboardingPayloadResolver
    implements MatterOnboardingPayloadResolver {
  FlutterMatterOnboardingPayloadResolver({OnboardingPayloadParser? parser})
    : _parser = parser ?? OnboardingPayloadParser();

  final OnboardingPayloadParser _parser;

  @override
  Future<OnboardingPayload> resolve(String payload) {
    return _parser.parse(payload);
  }
}

abstract interface class MatterBleScannerApi {
  Future<MatterBleDiscoveredDevice> scan(MatterBleDiscoveryRequest request);
}

class MatterBleScannerApiAdapter implements MatterBleScannerApi {
  MatterBleScannerApiAdapter(this._scanner);

  final MatterBleScanner _scanner;

  @override
  Future<MatterBleDiscoveredDevice> scan(MatterBleDiscoveryRequest request) {
    return _scanner.scan(request);
  }
}

class MatterBleDiscoveryAdapter implements BleDiscoveryPort {
  MatterBleDiscoveryAdapter({
    required MatterBleScannerApi scanner,
    required MatterOnboardingPayloadResolver payloadResolver,
    MatterBlePlatform? platform,
    OpaqueHandleFactory? handleFactory,
  }) : _scanner = scanner,
       _payloadResolver = payloadResolver,
       _platform = platform,
       _handles = handleFactory ?? OpaqueHandleFactory();

  factory MatterBleDiscoveryAdapter.flutter({
    MatterOnboardingPayloadResolver? payloadResolver,
    OpaqueHandleFactory? handleFactory,
  }) {
    final platform = FlutterBluePlusMatterBlePlatform();
    return MatterBleDiscoveryAdapter(
      scanner: MatterBleScannerApiAdapter(MatterBleScanner(platform: platform)),
      payloadResolver:
          payloadResolver ?? FlutterMatterOnboardingPayloadResolver(),
      platform: platform,
      handleFactory: handleFactory,
    );
  }

  final MatterBleScannerApi _scanner;
  final MatterOnboardingPayloadResolver _payloadResolver;
  final MatterBlePlatform? _platform;
  final OpaqueHandleFactory _handles;

  @override
  Future<BleDiscoveryResult> discover(BleDiscoveryRequest request) async {
    if (request.timeout <= Duration.zero) {
      throw BleDiscoveryException(BleDiscoveryFailureCode.other);
    }
    final payload = request.onboardingPayload?.trim();
    if (payload == null || payload.isEmpty) {
      return const BleDiscoveryResult(candidateCount: 0);
    }

    try {
      final platform = _platform;
      if (platform != null) {
        try {
          await platform.ensureAdapterIsOn(request.timeout);
        } on TimeoutException {
          // The platform wait completed without observing the adapter turn on.
          // That is the application's explicit Bluetooth-unavailable signal.
          throw BleDiscoveryException(
            BleDiscoveryFailureCode.bluetoothUnavailable,
          );
        }
      }
      final onboarding = await _payloadResolver
          .resolve(payload)
          .timeout(request.timeout);
      final discovered = await _scanner.scan(
        MatterBleDiscoveryRequest(
          discriminator: onboarding.discriminator,
          hasShortDiscriminator: onboarding.hasShortDiscriminator,
          timeout: request.timeout,
        ),
      );
      final target = BleCommissionee(
        opaqueId: _handles.next('ble-target'),
        displayName: _displayName(discovered),
      );
      return BleDiscoveryResult(candidateCount: 1, target: target);
    } on BleDiscoveryException {
      rethrow;
    } on TimeoutException {
      throw BleDiscoveryException(BleDiscoveryFailureCode.timeout);
    } on MatterBleException catch (error) {
      throw BleDiscoveryException(_mapMatterBle(error));
    } on PlatformException catch (error) {
      throw BleDiscoveryException(_mapPlatform(error));
    } on FormatException {
      throw BleDiscoveryException(BleDiscoveryFailureCode.other);
    } on ArgumentError {
      throw BleDiscoveryException(BleDiscoveryFailureCode.other);
    } on Object {
      throw BleDiscoveryException(BleDiscoveryFailureCode.other);
    }
  }

  String _displayName(MatterBleDiscoveredDevice discovered) {
    final name = discovered.advertisement.advertisedName?.trim();
    if (name != null && name.isNotEmpty) {
      return name;
    }
    return 'Matter device ${discovered.discriminator.toRadixString(16)}';
  }
}

BleDiscoveryFailureCode _mapMatterBle(MatterBleException error) {
  final platformError = _findCause<PlatformException>(error);
  if (platformError != null) {
    return _mapPlatform(platformError);
  }
  return switch (error.code) {
    MatterBleFailureCode.adapterUnavailable =>
      BleDiscoveryFailureCode.adapterUnavailable,
    MatterBleFailureCode.discoveryTimeout ||
    MatterBleFailureCode.operationTimeout => BleDiscoveryFailureCode.timeout,
    MatterBleFailureCode.invalidArgument => BleDiscoveryFailureCode.other,
    MatterBleFailureCode.scanFailed => BleDiscoveryFailureCode.other,
    MatterBleFailureCode.deviceNotFound => BleDiscoveryFailureCode.other,
    MatterBleFailureCode.connectionFailed => BleDiscoveryFailureCode.other,
    MatterBleFailureCode.serviceNotFound => BleDiscoveryFailureCode.other,
    MatterBleFailureCode.characteristicNotFound =>
      BleDiscoveryFailureCode.other,
    MatterBleFailureCode.unsupportedOperation => BleDiscoveryFailureCode.other,
  };
}

BleDiscoveryFailureCode _mapPlatform(PlatformException error) {
  final code = error.code.toLowerCase();
  if (code.contains('permission') ||
      code.contains('denied') ||
      code.contains('unauthorized')) {
    return BleDiscoveryFailureCode.permissionDenied;
  }
  if (code.contains('bluetooth') ||
      code.contains('adapter') ||
      code.contains('radio')) {
    return BleDiscoveryFailureCode.bluetoothUnavailable;
  }
  return BleDiscoveryFailureCode.other;
}

T? _findCause<T extends Object>(Object? error) {
  Object? current = error;
  final visited = <Object>{};
  while (current != null && visited.add(current)) {
    if (current is T) {
      return current;
    }
    current = switch (current) {
      MatterBleException(:final cause) => cause,
      MatterException(:final cause) => cause,
      _ => null,
    };
  }
  return null;
}
