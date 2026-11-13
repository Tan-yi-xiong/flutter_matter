import 'dart:typed_data';

import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:pointycastle/asn1.dart';
import 'package:pointycastle/export.dart';

void main() {
  test('identity generates a P-256 public key and verifiable signature', () {
    final identity = MatterControllerIdentity.generate();
    final publicKey = identity.getPublicKey();
    final message = Uint8List.fromList([1, 3, 3, 7]);

    expect(publicKey, hasLength(65));
    expect(publicKey.first, 0x04);

    final signature = identity.ecdsaSignMessage(message);
    final signatureSequence =
        ASN1Parser(signature).nextObject() as ASN1Sequence;
    final r = (signatureSequence.elements![0] as ASN1Integer).integer!;
    final s = (signatureSequence.elements![1] as ASN1Integer).integer!;
    final curve = ECCurve_secp256r1();
    final publicPoint = curve.curve.decodePoint(publicKey)!;
    final verifier = ECDSASigner(SHA256Digest())
      ..init(
        false,
        PublicKeyParameter<ECPublicKey>(ECPublicKey(publicPoint, curve)),
      );

    expect(verifier.verifySignature(message, ECSignature(r, s)), isTrue);
  });

  test('identity can be restored from its private scalar', () {
    final identity = MatterControllerIdentity.generate();
    final restored = MatterControllerIdentity.fromPrivateScalar(
      identity.exportPrivateScalar(),
    );

    expect(restored.getPublicKey(), identity.getPublicKey());
  });

  test('certificate signing copy keeps key material and changes handle', () {
    final identity = MatterControllerIdentity.generate();
    final signingIdentity = identity.copyForCertificateSigning();

    expect(signingIdentity, isNot(same(identity)));
    expect(signingIdentity.hashCode, isNot(identity.hashCode));
    expect(signingIdentity.getPublicKey(), identity.getPublicKey());
    expect(
      signingIdentity.exportPrivateScalar(),
      identity.exportPrivateScalar(),
    );
  });

  test('identity emits a structurally valid PKCS#10 request', () {
    final identity = MatterControllerIdentity.generate();

    final csr = identity.createCertificateSigningRequest();
    final sequence = ASN1Parser(csr).nextObject() as ASN1Sequence;

    expect(sequence.elements, hasLength(3));
    expect(sequence.elements![0], isA<ASN1Sequence>());
    expect(sequence.elements![1], isA<ASN1Sequence>());
    expect(sequence.elements![2], isA<ASN1BitString>());
  });

  test('secure credential JSON round-trips base64 fields', () {
    final record = MatterStoredControllerCredentials(
      privateKeyScalar: Uint8List.fromList(List<int>.generate(32, (i) => i)),
      rootCertificate: Uint8List.fromList([1, 2, 3]),
      operationalCertificate: Uint8List.fromList([4, 5, 6]),
      fabricId: 709394,
      controllerNodeId: 112233,
      issuerId: 0,
    );

    final restored = MatterStoredControllerCredentials.fromJson(
      Map<String, dynamic>.from(record.toJson()),
    );

    expect(restored.privateKeyScalar, record.privateKeyScalar);
    expect(restored.rootCertificate, record.rootCertificate);
    expect(restored.operationalCertificate, record.operationalCertificate);
    expect(restored.fabricId, 709394);
    expect(restored.controllerNodeId, 112233);
  });

  test('secure credential JSON rejects incomplete records', () {
    expect(
      () => MatterStoredControllerCredentials.fromJson(<String, dynamic>{
        'version': 1,
      }),
      throwsFormatException,
    );
  });
}
