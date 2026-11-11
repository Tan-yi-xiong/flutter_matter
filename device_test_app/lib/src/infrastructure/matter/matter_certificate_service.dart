import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

abstract interface class MatterCertificateIssuer {
  Future<Uint8List> createRootCertificate({
    required KeypairDelegate keypair,
    required int issuerId,
    required int fabricId,
  });

  Future<Uint8List> createOperationalCertificate({
    required KeypairDelegate signingKeypair,
    required Uint8List signingCertificate,
    required Uint8List operationalPublicKey,
    required int fabricId,
    required int nodeId,
    List<int>? caseAuthenticatedTags,
  });
}

class FlutterMatterCertificateIssuer implements MatterCertificateIssuer {
  const FlutterMatterCertificateIssuer();

  @override
  Future<Uint8List> createRootCertificate({
    required KeypairDelegate keypair,
    required int issuerId,
    required int fabricId,
  }) {
    return ChipDeviceController.createRootCertificate(
      keypair,
      issuerId,
      fabricId,
    );
  }

  @override
  Future<Uint8List> createOperationalCertificate({
    required KeypairDelegate signingKeypair,
    required Uint8List signingCertificate,
    required Uint8List operationalPublicKey,
    required int fabricId,
    required int nodeId,
    List<int>? caseAuthenticatedTags,
  }) {
    return ChipDeviceController.createOperationalCertificate(
      signingKeypair,
      signingCertificate,
      operationalPublicKey,
      fabricId,
      nodeId,
      caseAuthenticatedTags,
    );
  }
}
