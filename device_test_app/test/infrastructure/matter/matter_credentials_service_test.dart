import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test(
    'credentials persist the controller identity and certificates',
    () async {
      final storage = _MemoryCredentialStorage();
      final issuer = _CountingCertificateIssuer();
      final identity = MatterControllerIdentity.generate();
      final service = MatterControllerCredentialsService(
        storage: storage,
        certificateIssuer: issuer,
        identityGenerator: () => identity,
      );
      final config = MatterControllerConfig(
        operationTimeout: const Duration(seconds: 1),
        connectTimeout: const Duration(seconds: 1),
        commissioningTimeout: const Duration(seconds: 1),
        subscriptionTimeout: const Duration(seconds: 1),
      );

      final first = await service.loadOrCreate(config);
      final second = await service.loadOrCreate(config);

      expect(second.identity.getPublicKey(), first.identity.getPublicKey());
      expect(second.rootCertificate, first.rootCertificate);
      expect(second.operationalCertificate, first.operationalCertificate);
      expect(issuer.rootCalls, 1);
      expect(issuer.operationalCalls, 1);
      expect(storage.value, isNotNull);
    },
  );

  test(
    'an invalid stored scalar is replaced before certificates are reused',
    () async {
      final storage = _MemoryCredentialStorage();
      final issuer = _CountingCertificateIssuer();
      final config = MatterControllerConfig(
        operationTimeout: const Duration(seconds: 1),
        connectTimeout: const Duration(seconds: 1),
        commissioningTimeout: const Duration(seconds: 1),
        subscriptionTimeout: const Duration(seconds: 1),
      );
      storage.value = jsonEncode(
        MatterStoredControllerCredentials(
          privateKeyScalar: Uint8List(32),
          rootCertificate: Uint8List.fromList([0x30, 0x01]),
          operationalCertificate: Uint8List.fromList([0x30, 0x02]),
          fabricId: config.fabricId,
          controllerNodeId: config.controllerNodeId,
          issuerId: config.issuerId,
        ).toJson(),
      );
      final service = MatterControllerCredentialsService(
        storage: storage,
        certificateIssuer: issuer,
        identityGenerator: MatterControllerIdentity.generate,
      );

      final credentials = await service.loadOrCreate(config);

      expect(credentials.identity.getPublicKey(), hasLength(65));
      expect(issuer.rootCalls, 1);
      expect(issuer.operationalCalls, 1);
    },
  );

  test('changing the fabric reissues certificates but keeps the key', () async {
    final storage = _MemoryCredentialStorage();
    final issuer = _CountingCertificateIssuer();
    final identity = MatterControllerIdentity.generate();
    final service = MatterControllerCredentialsService(
      storage: storage,
      certificateIssuer: issuer,
      identityGenerator: () => identity,
    );
    final first = await service.loadOrCreate(
      MatterControllerConfig(
        fabricId: 1,
        operationTimeout: const Duration(seconds: 1),
        connectTimeout: const Duration(seconds: 1),
        commissioningTimeout: const Duration(seconds: 1),
        subscriptionTimeout: const Duration(seconds: 1),
      ),
    );
    final second = await service.loadOrCreate(
      MatterControllerConfig(
        fabricId: 2,
        operationTimeout: const Duration(seconds: 1),
        connectTimeout: const Duration(seconds: 1),
        commissioningTimeout: const Duration(seconds: 1),
        subscriptionTimeout: const Duration(seconds: 1),
      ),
    );

    expect(second.identity.getPublicKey(), first.identity.getPublicKey());
    expect(issuer.rootCalls, 2);
    expect(issuer.operationalCalls, 2);
  });
}

class _MemoryCredentialStorage implements MatterSecureCredentialStorage {
  String? value;

  @override
  Future<void> delete() async {
    value = null;
  }

  @override
  Future<String?> read() async => value;

  @override
  Future<void> write(String value) async {
    this.value = value;
  }
}

class _CountingCertificateIssuer implements MatterCertificateIssuer {
  int rootCalls = 0;
  int operationalCalls = 0;

  @override
  Future<Uint8List> createRootCertificate({
    required KeypairDelegate keypair,
    required int issuerId,
    required int fabricId,
  }) async {
    rootCalls++;
    return Uint8List.fromList([0x30, rootCalls]);
  }

  @override
  Future<Uint8List> createOperationalCertificate({
    required KeypairDelegate signingKeypair,
    required Uint8List signingCertificate,
    required Uint8List operationalPublicKey,
    required int fabricId,
    required int nodeId,
    List<int>? caseAuthenticatedTags,
  }) async {
    operationalCalls++;
    return Uint8List.fromList([0x30, operationalCalls]);
  }
}
