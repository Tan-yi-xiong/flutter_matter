/// Builds a Matter manual pairing code for setup-payload test scenarios.
///
/// This is intentionally local to the device-test app. Production consumers
/// should pass the original onboarding payload directly to the Matter SDK.
String buildMatterManualPairingCode({
  required int discriminator,
  required bool hasShortDiscriminator,
  required int setupPinCode,
  required int commissioningFlow,
  required int vendorId,
  required int productId,
}) {
  _checkRange(
    discriminator,
    0,
    hasShortDiscriminator ? 0xF : 0xFFF,
    'discriminator',
  );
  _checkRange(setupPinCode, 1, 99999998, 'setupPinCode');
  _checkRange(commissioningFlow, 0, 2, 'commissioningFlow');
  _checkRange(vendorId, 0, 0xFFFF, 'vendorId');
  _checkRange(productId, 0, 0xFFFF, 'productId');
  if (invalidMatterSetupPinCodes.contains(setupPinCode)) {
    throw ArgumentError.value(
      setupPinCode,
      'setupPinCode',
      'Must not be a reserved Matter setup passcode',
    );
  }

  final shortDiscriminator = hasShortDiscriminator
      ? discriminator
      : discriminator >> 8;
  final discriminatorMsb = (shortDiscriminator >> 2) & 0x3;
  final discriminatorLsb = shortDiscriminator & 0x3;
  final hasVendorProduct = commissioningFlow != 0;

  final chunk1 = discriminatorMsb | (hasVendorProduct ? 1 << 2 : 0);
  final chunk2 = (setupPinCode & 0x3FFF) | (discriminatorLsb << 14);
  final chunk3 = (setupPinCode >> 14) & 0x1FFF;

  final representation = StringBuffer()
    ..write(chunk1)
    ..write(chunk2.toString().padLeft(5, '0'))
    ..write(chunk3.toString().padLeft(4, '0'));
  if (hasVendorProduct) {
    representation
      ..write(vendorId.toString().padLeft(5, '0'))
      ..write(productId.toString().padLeft(5, '0'));
  }

  final value = representation.toString();
  return '$value${_verhoeffCheckDigit(value)}';
}

/// Returns a valid passcode that is intentionally different from [setupPinCode].
///
/// The result is used with an otherwise matching manual pairing code. The
/// commissionee therefore sees a well-formed payload with the wrong PASE
/// passcode instead of a malformed setup-code failure before commissioning.
int invalidMatterSetupPinCodeFor(int setupPinCode) {
  _checkRange(setupPinCode, 1, 99999998, 'setupPinCode');
  for (var offset = 1; offset <= 99999998; offset++) {
    final candidate = setupPinCode + offset > 99999998
        ? setupPinCode + offset - 99999998
        : setupPinCode + offset;
    if (candidate >= 1 && !invalidMatterSetupPinCodes.contains(candidate)) {
      return candidate;
    }
  }
  throw StateError('Unable to select an alternate Matter setup passcode');
}

const Set<int> invalidMatterSetupPinCodes = <int>{
  0,
  11111111,
  22222222,
  33333333,
  44444444,
  55555555,
  66666666,
  77777777,
  88888888,
  12345678,
  87654321,
};

void _checkRange(int value, int minimum, int maximum, String name) {
  if (value < minimum || value > maximum) {
    throw ArgumentError.value(
      value,
      name,
      'Must be between $minimum and $maximum',
    );
  }
}

String _verhoeffCheckDigit(String value) {
  var checksum = 0;
  final reversed = value.codeUnits.reversed.toList(growable: false);
  for (var index = 0; index < reversed.length; index++) {
    final digit = reversed[index] - 0x30;
    if (digit < 0 || digit > 9) {
      throw ArgumentError.value(value, 'value', 'Must contain only digits');
    }
    var permuted = digit;
    for (var iteration = 0; iteration < index + 1; iteration++) {
      permuted = _verhoeffPermutation[permuted];
    }
    checksum = _verhoeffMultiplication[checksum * 10 + permuted];
  }
  return '${_verhoeffInverse(checksum)}';
}

int _verhoeffInverse(int value) => value > 0 && value < 5 ? 5 - value : value;

const List<int> _verhoeffPermutation = <int>[1, 5, 7, 6, 2, 8, 3, 0, 9, 4];

const List<int> _verhoeffMultiplication = <int>[
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  1,
  2,
  3,
  4,
  0,
  6,
  7,
  8,
  9,
  5,
  2,
  3,
  4,
  0,
  1,
  7,
  8,
  9,
  5,
  6,
  3,
  4,
  0,
  1,
  2,
  8,
  9,
  5,
  6,
  7,
  4,
  0,
  1,
  2,
  3,
  9,
  5,
  6,
  7,
  8,
  5,
  9,
  8,
  7,
  6,
  0,
  4,
  3,
  2,
  1,
  6,
  5,
  9,
  8,
  7,
  1,
  0,
  4,
  3,
  2,
  7,
  6,
  5,
  9,
  8,
  2,
  1,
  0,
  4,
  3,
  8,
  7,
  6,
  5,
  9,
  3,
  2,
  1,
  0,
  4,
  9,
  8,
  7,
  6,
  5,
  4,
  3,
  2,
  1,
  0,
];
