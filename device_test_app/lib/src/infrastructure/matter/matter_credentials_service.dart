import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_secure_storage/flutter_secure_storage.dart';

import 'matter_certificate_service.dart';
import 'matter_contracts.dart';
import 'matter_identity.dart';

class MatterControllerCredentials {
  MatterControllerCredentials({
    required this.identity,
    required Uint8List rootCertificate,
    required Uint8List operationalCertificate,
  }) : rootCertificate = Uint8List.fromList(rootCertificate),
       operationalCertificate = Uint8List.fromList(operationalCertificate);

  final MatterControllerIdentity identity;
  final Uint8List rootCertificate;
  final Uint8List operationalCertificate;
}

class MatterStoredControllerCredentials {
  MatterStoredControllerCredentials({
    required Uint8List privateKeyScalar,
    required Uint8List rootCertificate,
    required Uint8List operationalCertificate,
    required this.fabricId,
    required this.controllerNodeId,
    required this.issuerId,
  }) : privateKeyScalar = Uint8List.fromList(privateKeyScalar),
       rootCertificate = Uint8List.fromList(rootCertificate),
       operationalCertificate = Uint8List.fromList(operationalCertificate) {
    if (this.privateKeyScalar.length != 32) {
      throw ArgumentError.value(
        privateKeyScalar.length,
        'privateKeyScalar',
        'P-256 private scalar must be 32 bytes',
      );
    }
    if (this.rootCertificate.isEmpty) {
      throw ArgumentError.value(
        rootCertificate,
        'rootCertificate',
        'Must not be empty',
      );
    }
    if (this.operationalCertificate.isEmpty) {
      throw ArgumentError.value(
        operationalCertificate,
        'operationalCertificate',
        'Must not be empty',
      );
    }
  }

  final Uint8List privateKeyScalar;
  final Uint8List rootCertificate;
  final Uint8List operationalCertificate;
  final int fabricId;
  final int controllerNodeId;
  final int issuerId;

  bool matchesConfig(MatterControllerConfig config) {
    return fabricId == config.fabricId &&
        controllerNodeId == config.controllerNodeId &&
        issuerId == config.issuerId;
  }

  Map<String, Object> toJson() {
    return <String, Object>{
      'version': 1,
      'private_key_scalar': base64Encode(privateKeyScalar),
      'root_certificate': base64Encode(rootCertificate),
      'operational_certificate': base64Encode(operationalCertificate),
      'fabric_id': fabricId,
      'controller_node_id': controllerNodeId,
      'issuer_id': issuerId,
    };
  }

  factory MatterStoredControllerCredentials.fromJson(
    Map<String, dynamic> json,
  ) {
    if (json['version'] != 1) {
      throw const FormatException('Unsupported controller credential version');
    }
    return MatterStoredControllerCredentials(
      privateKeyScalar: _decodeBytes(
        json['private_key_scalar'],
        'private_key_scalar',
      ),
      rootCertificate: _decodeBytes(
        json['root_certificate'],
        'root_certificate',
      ),
      operationalCertificate: _decodeBytes(
        json['operational_certificate'],
        'operational_certificate',
      ),
      fabricId: _readInt(json['fabric_id'], 'fabric_id'),
      controllerNodeId: _readInt(
        json['controller_node_id'],
        'controller_node_id',
      ),
      issuerId: _readInt(json['issuer_id'], 'issuer_id'),
    );
  }

  static Uint8List _decodeBytes(Object? value, String name) {
    if (value is! String || value.isEmpty) {
      throw FormatException('$name must be a base64 string');
    }
    try {
      return Uint8List.fromList(base64Decode(value));
    } on FormatException {
      throw FormatException('$name must be valid base64');
    }
  }

  static int _readInt(Object? value, String name) {
    if (value is int) {
      return value;
    }
    if (value is String) {
      final parsed = int.tryParse(value);
      if (parsed != null) {
        return parsed;
      }
    }
    throw FormatException('$name must be an integer');
  }
}

abstract interface class MatterSecureCredentialStorage {
  Future<String?> read();

  Future<void> write(String value);

  Future<void> delete();
}

class FlutterSecureMatterCredentialStorage
    implements MatterSecureCredentialStorage {
  FlutterSecureMatterCredentialStorage({FlutterSecureStorage? storage})
    : _storage = storage ?? const FlutterSecureStorage();

  static const String credentialKey =
      'flutter_matter.device_test_app.controller_credentials.v1';

  final FlutterSecureStorage _storage;

  @override
  Future<String?> read() {
    return _storage.read(key: credentialKey);
  }

  @override
  Future<void> write(String value) {
    return _storage.write(key: credentialKey, value: value);
  }

  @override
  Future<void> delete() {
    return _storage.delete(key: credentialKey);
  }
}

typedef MatterIdentityGenerator = MatterControllerIdentity Function();

class MatterControllerCredentialsService {
  MatterControllerCredentialsService({
    required MatterSecureCredentialStorage storage,
    required MatterCertificateIssuer certificateIssuer,
    MatterIdentityGenerator? identityGenerator,
  }) : _storage = storage,
       _certificateIssuer = certificateIssuer,
       _identityGenerator =
           identityGenerator ?? MatterControllerIdentity.generate;

  final MatterSecureCredentialStorage _storage;
  final MatterCertificateIssuer _certificateIssuer;
  final MatterIdentityGenerator _identityGenerator;

  Future<MatterControllerCredentials> loadOrCreate(
    MatterControllerConfig config,
  ) async {
    final stored = await _readStored();
    MatterControllerIdentity? identity;
    var restoredStoredIdentity = false;
    if (stored != null) {
      try {
        identity = MatterControllerIdentity.fromPrivateScalar(
          stored.privateKeyScalar,
        );
        restoredStoredIdentity = true;
      } catch (_) {
        identity = null;
      }
    }
    identity ??= _identityGenerator();

    if (stored != null &&
        restoredStoredIdentity &&
        stored.matchesConfig(config)) {
      return MatterControllerCredentials(
        identity: identity,
        rootCertificate: stored.rootCertificate,
        operationalCertificate: stored.operationalCertificate,
      );
    }

    final rootCertificate = await _certificateIssuer.createRootCertificate(
      keypair: identity,
      issuerId: config.issuerId,
      fabricId: config.fabricId,
    );
    final operationalCertificate = await _certificateIssuer
        .createOperationalCertificate(
          signingKeypair: identity,
          signingCertificate: rootCertificate,
          operationalPublicKey: identity.publicKeyBytes,
          fabricId: config.fabricId,
          nodeId: config.controllerNodeId,
          caseAuthenticatedTags: null,
        );
    final record = MatterStoredControllerCredentials(
      privateKeyScalar: identity.exportPrivateScalar(),
      rootCertificate: rootCertificate,
      operationalCertificate: operationalCertificate,
      fabricId: config.fabricId,
      controllerNodeId: config.controllerNodeId,
      issuerId: config.issuerId,
    );
    await _storage.write(jsonEncode(record.toJson()));
    return MatterControllerCredentials(
      identity: identity,
      rootCertificate: record.rootCertificate,
      operationalCertificate: record.operationalCertificate,
    );
  }

  Future<void> clear() {
    return _storage.delete();
  }

  Future<MatterStoredControllerCredentials?> _readStored() async {
    final encoded = await _storage.read();
    if (encoded == null || encoded.isEmpty) {
      return null;
    }
    try {
      final json = jsonDecode(encoded);
      if (json is! Map<String, dynamic>) {
        throw const FormatException('Credential record must be an object');
      }
      return MatterStoredControllerCredentials.fromJson(json);
    } catch (_) {
      await _storage.delete();
      return null;
    }
  }
}
