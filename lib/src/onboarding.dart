import 'dart:convert';

import 'package:flutter_matter/flutter_matter_platform_interface.dart';

import 'exception.dart';
import 'model/json_decoding.dart';
import 'platform_transport_types.dart';

/// MethodChannel host used by the onboarding parser.
const String onboardingPayloadHost = 'Onboarding';

/// Discovery transports advertised by a Matter onboarding payload.
enum DiscoveryCapability {
  soft_ap(1),
  ble(2),
  on_network(3);

  final int value;

  const DiscoveryCapability(this.value);
}

/// Parsed Matter onboarding payload.
///
/// Contains the commissioning flow, rendezvous capabilities, discriminator,
/// and setup PIN code from a QR code or manual pairing code.
class OnboardingPayload {
  /// Version info of the OnboardingPayload: version SHALL be 0
  final int version;

  /// The CHIP device vendor ID: Vendor ID SHALL be between 1 and 0xFFF4.
  final int vendorId;

  /// The CHIP device product ID: Product ID SHALL BE greater than 0.
  final int productId;

  /// Commissioning flow: 0 = standard, 1 = requires user action, 2 = custom
  final int commissioningFlow;

  /// The CHIP device supported rendezvous flags. This may be empty when the
  /// payload does not expose discovery capabilities, such as a manual pairing
  /// code.
  final Set<DiscoveryCapability> discoveryCapabilities;

  /// The CHIP device discriminator:
  final int discriminator;

  /// If hasShortDiscriminator is true, the discriminator value contains just the high 4 bits of the
  /// full discriminator. For example, if hasShortDiscriminator is true and discriminator is 0xA,
  /// then the full discriminator can be anything in the range 0xA00 to 0xAFF.
  final bool hasShortDiscriminator;

  /// The CHIP device setup PIN code: setupPINCode SHALL be greater than 0. Also invalid setupPINCode
  /// is {000000000, 11111111, 22222222, 33333333, 44444444, 55555555, 66666666, 77777777, 88888888,
  /// 99999999, 12345678, 87654321}.
  final int setupPinCode;

  OnboardingPayload({
    required this.version,
    required this.vendorId,
    required this.productId,
    required this.commissioningFlow,
    required this.discoveryCapabilities,
    required this.discriminator,
    required this.hasShortDiscriminator,
    required this.setupPinCode,
  });

  factory OnboardingPayload.decode(Map json) {
    final root = decodeJsonObject(json, 'OnboardingPayload');
    final rawCapabilities = decodeJsonArray(
      root['discoveryCapabilities'],
      'OnboardingPayload.discoveryCapabilities',
    );
    final capabilities = <DiscoveryCapability>{};
    for (var i = 0; i < rawCapabilities.length; i++) {
      final value = decodeJsonInt(
        rawCapabilities[i],
        'OnboardingPayload.discoveryCapabilities[$i]',
      );
      var matched = false;
      for (final capability in DiscoveryCapability.values) {
        if (capability.value == value) {
          capabilities.add(capability);
          matched = true;
          break;
        }
      }
      if (!matched) {
        throw FormatException(
          'OnboardingPayload.discoveryCapabilities[$i] has unsupported value '
          '$value',
        );
      }
    }

    return OnboardingPayload(
      version: decodeJsonInt(root['version'], 'OnboardingPayload.version'),
      vendorId: decodeJsonInt(root['vendorId'], 'OnboardingPayload.vendorId'),
      productId:
          decodeJsonInt(root['productId'], 'OnboardingPayload.productId'),
      commissioningFlow: decodeJsonInt(
        root['commissioningFlow'],
        'OnboardingPayload.commissioningFlow',
      ),
      discriminator: decodeJsonInt(
        root['discriminator'],
        'OnboardingPayload.discriminator',
      ),
      setupPinCode: decodeJsonInt(
        root['setupPinCode'],
        'OnboardingPayload.setupPinCode',
      ),
      hasShortDiscriminator: decodeJsonBool(
        root['hasShortDiscriminator'],
        'OnboardingPayload.hasShortDiscriminator',
      ),
      discoveryCapabilities: capabilities,
    );
  }
}

/// Parses Matter QR setup codes and manual pairing codes.
///
/// Parsing is optional for commissioning. [ChipDeviceController.pairDevice]
/// accepts the raw onboarding code directly.
class OnboardingPayloadParser {
  late FlutterMatterPlatform _channel;

  OnboardingPayloadParser() {
    _channel = FlutterMatterPlatform.instance;
  }

  /// Parses a QR setup code or manual pairing code, selecting the format by
  /// the `MT:` prefix.
  Future<OnboardingPayload> parse(String code) async {
    _requireNonEmpty(code, 'code');
    if (code.startsWith('MT:')) {
      return parseQrCode(code);
    }
    return parseManualPairingCode(code);
  }

  /// Parses a Matter QR setup code.
  Future<OnboardingPayload> parseQrCode(String qrCode) async {
    _requireNonEmpty(qrCode, 'qrCode');
    return _parse(
      methodName: 'parseQrCode',
      parameterName: 'qrCode',
      value: qrCode,
      displayName: 'QR code',
    );
  }

  /// Parses a Matter manual pairing code.
  Future<OnboardingPayload> parseManualPairingCode(String pairingCode) async {
    _requireNonEmpty(pairingCode, 'pairingCode');
    return _parse(
      methodName: 'parseManualPairingCode',
      parameterName: 'pairingCode',
      value: pairingCode,
      displayName: 'manual pairing code',
    );
  }

  Future<OnboardingPayload> _parse({
    required String methodName,
    required String parameterName,
    required String value,
    required String displayName,
  }) async {
    final result = await _channel.requestPlatform(
      RequestPlatformParams(
        methodName: createRequestPlatformUrl(onboardingPayloadHost, methodName),
        methodParamsJson: jsonEncode({parameterName: value}),
      ),
    );
    if (result.code != successCode) {
      throw CallPlatformException(
        'Failed to parse $displayName with code ${result.code}',
        code: result.code,
        methodName: methodName,
        details: const <String, Object?>{
          'host': onboardingPayloadHost,
          'category': 'platform-error',
        },
      );
    }

    try {
      return OnboardingPayload.decode(result.jsonData);
    } on FormatException catch (error) {
      throw CallPlatformException(
        'Invalid payload returned by $methodName: ${error.message}',
        code: result.code,
        methodName: methodName,
        details: const <String, Object?>{
          'host': onboardingPayloadHost,
          'category': 'invalid-payload',
        },
        cause: error,
      );
    } on ArgumentError catch (error) {
      throw CallPlatformException(
        'Invalid payload returned by $methodName: ${error.message}',
        code: result.code,
        methodName: methodName,
        details: const <String, Object?>{
          'host': onboardingPayloadHost,
          'category': 'invalid-payload',
        },
        cause: error,
      );
    }
  }

  static void _requireNonEmpty(String value, String name) {
    if (value.trim().isEmpty) {
      throw ArgumentError.value(value, name, 'must not be empty');
    }
  }
}
