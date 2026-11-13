import 'package:flutter_matter_device_test_app/src/application/matter_manual_pairing_code.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('buildMatterManualPairingCode', () {
    test('matches the Matter SDK standard-flow vector', () {
      expect(
        buildMatterManualPairingCode(
          discriminator: 2560,
          hasShortDiscriminator: false,
          setupPinCode: 12345679,
          commissioningFlow: 0,
          vendorId: 45367,
          productId: 14526,
        ),
        '24129507533',
      );
    });

    test('matches the Matter SDK custom-flow long-code vector', () {
      expect(
        buildMatterManualPairingCode(
          discriminator: 2560,
          hasShortDiscriminator: false,
          setupPinCode: 12345679,
          commissioningFlow: 2,
          vendorId: 45367,
          productId: 14526,
        ),
        '641295075345367145262',
      );
    });

    test('uses the short discriminator encoded by a manual setup code', () {
      expect(
        buildMatterManualPairingCode(
          discriminator: 0xA,
          hasShortDiscriminator: true,
          setupPinCode: 12345679,
          commissioningFlow: 0,
          vendorId: 0,
          productId: 0,
        ),
        '24129507533',
      );
    });

    test('rejects a long discriminator when short form is requested', () {
      expect(
        () => buildMatterManualPairingCode(
          discriminator: 0x1F,
          hasShortDiscriminator: true,
          setupPinCode: 12345679,
          commissioningFlow: 0,
          vendorId: 0,
          productId: 0,
        ),
        throwsArgumentError,
      );
    });

    test('rejects reserved setup passcodes', () {
      expect(
        () => buildMatterManualPairingCode(
          discriminator: 1,
          hasShortDiscriminator: false,
          setupPinCode: 11111111,
          commissioningFlow: 0,
          vendorId: 0,
          productId: 0,
        ),
        throwsArgumentError,
      );
    });
  });

  group('invalidMatterSetupPinCodeFor', () {
    test('returns a different non-reserved passcode', () {
      expect(invalidMatterSetupPinCodeFor(20202021), 20202022);
    });

    test('skips reserved passcodes', () {
      expect(invalidMatterSetupPinCodeFor(11111110), 11111112);
      expect(invalidMatterSetupPinCodeFor(12345677), 12345679);
    });

    test('wraps within the valid setup passcode range', () {
      expect(invalidMatterSetupPinCodeFor(99999998), 1);
    });
  });
}
