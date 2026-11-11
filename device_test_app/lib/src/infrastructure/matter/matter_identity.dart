import 'dart:math';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:pointycastle/asn1.dart';
import 'package:pointycastle/export.dart';

abstract interface class MatterSecureRandom {
  Uint8List nextBytes(int length);
}

class SystemMatterSecureRandom implements MatterSecureRandom {
  SystemMatterSecureRandom() : _random = Random.secure();

  final Random _random;

  @override
  Uint8List nextBytes(int length) {
    if (length < 0) {
      throw ArgumentError.value(length, 'length', 'Must not be negative');
    }
    return Uint8List.fromList(
      List<int>.generate(length, (_) => _random.nextInt(256)),
    );
  }
}

class MatterControllerIdentity implements KeypairDelegate {
  MatterControllerIdentity._({
    required MatterSecureRandom secureRandom,
    required ECDomainParameters curve,
    required ECPrivateKey privateKey,
    required ECPublicKey publicKey,
  }) : _secureRandom = secureRandom,
       _curve = curve,
       _privateKey = privateKey,
       _publicKey = publicKey;

  factory MatterControllerIdentity.generate({
    MatterSecureRandom? secureRandom,
  }) {
    final random = secureRandom ?? SystemMatterSecureRandom();
    final curve = ECCurve_secp256r1();
    final generator = ECKeyGenerator()
      ..init(
        ParametersWithRandom(ECKeyGeneratorParameters(curve), _fortuna(random)),
      );
    final pair = generator.generateKeyPair();
    return MatterControllerIdentity._(
      secureRandom: random,
      curve: curve,
      privateKey: pair.privateKey as ECPrivateKey,
      publicKey: pair.publicKey as ECPublicKey,
    );
  }

  factory MatterControllerIdentity.fromPrivateScalar(
    Uint8List privateScalar, {
    MatterSecureRandom? secureRandom,
  }) {
    if (privateScalar.length != 32) {
      throw ArgumentError.value(
        privateScalar.length,
        'privateScalar',
        'P-256 private scalar must be 32 bytes',
      );
    }
    final curve = ECCurve_secp256r1();
    final scalar = _decodeBigInt(privateScalar);
    if (scalar <= BigInt.zero || scalar >= curve.n) {
      throw ArgumentError.value(
        'privateScalar',
        'privateScalar',
        'Value is outside the P-256 scalar range',
      );
    }
    final point = curve.G * scalar;
    if (point == null || point.isInfinity) {
      throw ArgumentError.value(
        'privateScalar',
        'privateScalar',
        'Unable to derive a public key',
      );
    }
    return MatterControllerIdentity._(
      secureRandom: secureRandom ?? SystemMatterSecureRandom(),
      curve: curve,
      privateKey: ECPrivateKey(scalar, curve),
      publicKey: ECPublicKey(point, curve),
    );
  }

  final MatterSecureRandom _secureRandom;
  final ECDomainParameters _curve;
  final ECPrivateKey _privateKey;
  final ECPublicKey _publicKey;

  Uint8List exportPrivateScalar() {
    return _encodeFixed(_privateKey.d!, 32);
  }

  Uint8List get publicKeyBytes => getPublicKey();

  @override
  void generatePrivateKey() {
    // The identity is immutable and always contains a private key.
  }

  @override
  Uint8List createCertificateSigningRequest() {
    final publicKeyInfo = ASN1SubjectPublicKeyInfo(
      ASN1AlgorithmIdentifier(
        ASN1ObjectIdentifier.fromName('ecPublicKey'),
        parameters: ASN1ObjectIdentifier.fromName('prime256v1'),
      ),
      ASN1BitString(stringValues: getPublicKey()),
    );
    final requestInfo = ASN1CertificationRequestInfo(
      ASN1Integer.fromtInt(0),
      ASN1Name([]),
      publicKeyInfo,
    );
    final encodedRequestInfo = requestInfo.encode();
    final signature = ecdsaSignMessage(encodedRequestInfo);
    final signatureAlgorithm = ASN1Sequence(
      elements: [ASN1ObjectIdentifier.fromName('ecdsaWithSHA256')],
    );
    return ASN1Sequence(
      elements: [
        requestInfo,
        signatureAlgorithm,
        ASN1BitString(stringValues: signature),
      ],
    ).encode();
  }

  @override
  Uint8List getPublicKey() {
    final point = _publicKey.Q;
    final x = point?.x?.toBigInteger();
    final y = point?.y?.toBigInteger();
    if (x == null || y == null) {
      throw StateError('Controller public key is unavailable');
    }
    final encoded = Uint8List(65);
    encoded[0] = 0x04;
    encoded.setRange(1, 33, _encodeFixed(x, 32));
    encoded.setRange(33, 65, _encodeFixed(y, 32));
    return encoded;
  }

  @override
  Uint8List ecdsaSignMessage(List<int> message) {
    final signer = ECDSASigner(SHA256Digest())
      ..init(
        true,
        ParametersWithRandom(
          PrivateKeyParameter<ECPrivateKey>(_privateKey),
          _fortuna(_secureRandom),
        ),
      );
    final signature =
        signer.generateSignature(Uint8List.fromList(message)) as ECSignature;
    final normalized = signature.normalize(_curve);
    return ASN1Sequence(
      elements: [ASN1Integer(normalized.r), ASN1Integer(normalized.s)],
    ).encode();
  }

  static FortunaRandom _fortuna(MatterSecureRandom random) {
    return FortunaRandom()..seed(KeyParameter(random.nextBytes(32)));
  }

  static BigInt _decodeBigInt(Uint8List bytes) {
    var result = BigInt.zero;
    for (final byte in bytes) {
      result = (result << 8) | BigInt.from(byte);
    }
    return result;
  }

  static Uint8List _encodeFixed(BigInt value, int length) {
    final result = Uint8List(length);
    var remaining = value;
    for (var index = length - 1; index >= 0; index--) {
      result[index] = (remaining & BigInt.from(0xff)).toInt();
      remaining = remaining >> 8;
    }
    if (remaining != BigInt.zero) {
      throw ArgumentError.value(
        value,
        'value',
        'Does not fit in $length bytes',
      );
    }
    return result;
  }
}
