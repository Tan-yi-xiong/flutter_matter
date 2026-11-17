import 'dart:convert';
import 'dart:math';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:hex/hex.dart';
import 'package:pem/pem.dart';
import 'package:pointycastle/export.dart' hide State;
import 'package:pointycastle/pointycastle.dart';

import 'storage.dart';

class MatterIdentity {
  const MatterIdentity({
    required this.keypair,
    required this.rootCertificate,
    required this.operationalCertificate,
    required this.fabricId,
  });

  final AsymmetricKeyPair<ECPublicKey, ECPrivateKey> keypair;
  final Uint8List rootCertificate;
  final Uint8List operationalCertificate;
  final int fabricId;

  DemoKeypairDelegate get keypairDelegate => DemoKeypairDelegate(
    publicKey: keypair.publicKey,
    privateKey: keypair.privateKey,
  );

  ControllerParams get controllerParams => ControllerParams(
    skipCommissioningComplete: false,
    fabricId: fabricId,
    keypairDelegate: keypairDelegate,
    ipk: defaultIpk,
    rootCertificate: rootCertificate,
    intermediateCertificate: rootCertificate,
    operationalCertificate: operationalCertificate,
  );
}

class MatterIdentityRepository {
  MatterIdentityRepository(this._store);

  final ExampleStore _store;
  MatterIdentity? _cached;

  Future<MatterIdentity> loadOrCreate() async {
    final cached = _cached;
    if (cached != null) {
      return cached;
    }

    final keypairJson = await _store.readKeypairJson();
    final certificateJson = await _store.readCertificateJson();
    if (keypairJson != null && certificateJson != null) {
      final identity = _decodePersisted(keypairJson, certificateJson);
      if (identity != null) {
        _cached = identity;
        return identity;
      }
    }

    final identity = await _createAndPersist();
    _cached = identity;
    return identity;
  }

  Future<MatterIdentity> _createAndPersist() async {
    final keypair = _generateP256KeyPair();
    final delegate = DemoKeypairDelegate(
      publicKey: keypair.publicKey,
      privateKey: keypair.privateKey,
    );
    const fabricId = 709394;
    final rootCertificate = await ChipDeviceController.createRootCertificate(
      delegate,
      0,
      fabricId,
    );
    final operationalCertificate =
        await ChipDeviceController.createOperationalCertificate(
          delegate,
          rootCertificate,
          delegate.getPublicKey(),
          fabricId,
          kTestControllerNodeId,
          null,
        );

    final keypairJson = jsonEncode({
      'publicKey': PemCodec(
        PemLabel.publicKey,
      ).encode(Uint8List.fromList(keypair.publicKey.Q!.getEncoded())),
      'privateKey': PemCodec(
        PemLabel.privateKey,
      ).encode(_bigIntToBytes(keypair.privateKey.d!)),
    });
    final certificateJson = jsonEncode({
      'rcac': rootCertificate,
      'nodeOC': operationalCertificate,
    });
    await _store.saveIdentity(keypairJson, certificateJson);

    return MatterIdentity(
      keypair: keypair,
      rootCertificate: rootCertificate,
      operationalCertificate: operationalCertificate,
      fabricId: fabricId,
    );
  }

  MatterIdentity? _decodePersisted(String keypairJson, String certificateJson) {
    try {
      final keypairData = jsonDecode(keypairJson) as Map<String, dynamic>;
      final certificateData =
          jsonDecode(certificateJson) as Map<String, dynamic>;
      final curve = ECCurve_secp256r1();
      final point = curve.curve.decodePoint(
        PemCodec(PemLabel.publicKey).decode(keypairData['publicKey']),
      );
      final publicKey = ECPublicKey(point, curve);
      final privateBytes = PemCodec(
        PemLabel.privateKey,
      ).decode(keypairData['privateKey']);
      final privateKey = ECPrivateKey(
        BigInt.parse(HEX.encode(privateBytes), radix: 16),
        curve,
      );
      return MatterIdentity(
        keypair: AsymmetricKeyPair(publicKey, privateKey),
        rootCertificate: Uint8List.fromList(
          (certificateData['rcac'] as List).cast<int>(),
        ),
        operationalCertificate: Uint8List.fromList(
          (certificateData['nodeOC'] as List).cast<int>(),
        ),
        fabricId: 709394,
      );
    } catch (_) {
      return null;
    }
  }

  AsymmetricKeyPair<ECPublicKey, ECPrivateKey> _generateP256KeyPair() {
    final parameters = ECKeyGeneratorParameters(ECCurve_secp256r1());
    final secureRandom = FortunaRandom()..seed(KeyParameter(_secureSeed()));
    final generator = ECKeyGenerator()
      ..init(ParametersWithRandom(parameters, secureRandom));
    final pair = generator.generateKeyPair();
    return AsymmetricKeyPair(
      pair.publicKey as ECPublicKey,
      pair.privateKey as ECPrivateKey,
    );
  }
}

class DemoKeypairDelegate implements KeypairDelegate {
  DemoKeypairDelegate({required this.publicKey, required this.privateKey});

  final ECPublicKey publicKey;
  final ECPrivateKey privateKey;

  @override
  Uint8List createCertificateSigningRequest() {
    throw UnimplementedError(
      'The Matter SDK obtains the CSR through publicKeyFromCSR in this demo.',
    );
  }

  @override
  Uint8List ecdsaSignMessage(List<int> message) {
    final random = FortunaRandom()..seed(KeyParameter(_secureSeed()));
    final signer = ECDSASigner(SHA256Digest())
      ..init(
        true,
        ParametersWithRandom(PrivateKeyParameter(privateKey), random),
      );
    final signature =
        signer.generateSignature(Uint8List.fromList(message)) as ECSignature;
    return ASN1Sequence(
      elements: [ASN1Integer(signature.r), ASN1Integer(signature.s)],
    ).encode();
  }

  @override
  void generatePrivateKey() {}

  @override
  Uint8List getPublicKey() {
    final x = publicKey.Q!.x!.toBigInteger()!;
    final y = publicKey.Q!.y!.toBigInteger()!;
    return Uint8List(65)
      ..[0] = 0x04
      ..setRange(1, 33, _coordinateBytes(x))
      ..setRange(33, 65, _coordinateBytes(y));
  }

  Uint8List _coordinateBytes(BigInt coordinate) {
    final encoded = coordinate.toRadixString(16).padLeft(64, '0');
    return Uint8List.fromList(
      List<int>.generate(
        32,
        (index) =>
            int.parse(encoded.substring(index * 2, index * 2 + 2), radix: 16),
      ),
    );
  }
}

Uint8List _secureSeed() {
  final random = Random.secure();
  return Uint8List.fromList(List<int>.generate(32, (_) => random.nextInt(256)));
}

List<int> _bigIntToBytes(BigInt value) {
  var encoded = value.toRadixString(16);
  if (encoded.length.isOdd) {
    encoded = '0$encoded';
  }
  return HEX.decode(encoded);
}
