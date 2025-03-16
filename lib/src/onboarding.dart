
import 'dart:convert';

import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';

import 'exception.dart';

const String onboardingPayloadHost = 'Onboarding';

enum DiscoveryCapability {
  soft_ap,
  ble,
  on_network
}

class OnboardingPayload {
   /// Version info of the OnboardingPayload: version SHALL be 0
  final int version;

  /// The CHIP device vendor ID: Vendor ID SHALL be between 1 and 0xFFF4.
  final int vendorId;

  /// The CHIP device product ID: Product ID SHALL BE greater than 0.
  final int productId;

  /// Commissioning flow: 0 = standard, 1 = requires user action, 2 = custom
  final int commissioningFlow;

  /// The CHIP device supported rendezvous flags: At least one DiscoveryCapability must be included.
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

  OnboardingPayload({required this.version, required this.vendorId, required this.productId, required this.commissioningFlow, required this.discoveryCapabilities, required this.discriminator, required this.hasShortDiscriminator, required this.setupPinCode});

  factory OnboardingPayload.decode(Map json) {
    return OnboardingPayload(
      version: json["version"],
      vendorId: json["vendorId"],
      productId: json["productId"],
      commissioningFlow: json["commissioningFlow"],
      discriminator: json["discriminator"],
      setupPinCode: json["setupPinCode"],
      hasShortDiscriminator: json["hasShortDiscriminator"],
      discoveryCapabilities: (json["discoveryCapabilities"] as List).map((e) => DiscoveryCapability.values[e]).toSet()
    );
  }
}

class OnboardingPayloadParser  {

  late MethodChannelFlutterMatter _channel;

  OnboardingPayloadParser() {
    _channel = FlutterMatterPlatform.instance as MethodChannelFlutterMatter;
  }

  Future<OnboardingPayload> parse(String code) async {
    if (code.startsWith("MT:")) {
      return parseQrCode(code);
    }
    return parseManualPairingCode(code);
  }
  
  Future<OnboardingPayload> parseQrCode(String qrCode) async {
    final result = await _channel.requestPlatform(RequestPlatformParams(
      methodName: createRequestPlatformUrl(onboardingPayloadHost, "parseQrCode"), 
      methodParamsJson: jsonEncode({
        'qrCode': qrCode
      })
    ));
    if (result.code != successCode) {
      throw Exception("Failed to parse QR code: ${result.code}");
    }
    return OnboardingPayload.decode(result.jsonData);
  }

  Future<OnboardingPayload> parseManualPairingCode(String pairingCode) async {
    final result = await _channel.requestPlatform(RequestPlatformParams(
      methodName: createRequestPlatformUrl(onboardingPayloadHost, "parseManualPairingCode"), 
      methodParamsJson: jsonEncode({
        'pairingCode': pairingCode
      })
    ));
    if (result.code != successCode) {
      throw Exception("Failed to parse QR code: ${result.code}");
    }
    return OnboardingPayload.decode(result.jsonData);
  }
}