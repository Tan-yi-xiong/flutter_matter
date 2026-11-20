import 'package:flutter_secure_storage/flutter_secure_storage.dart';

import '../../application/ports.dart';
import '../matter/matter.dart';
import 'matter_controller_api.dart';

/// A controller service and the identity store backing that controller.
class MatterControllerRuntime {
  MatterControllerRuntime({
    required this.purpose,
    required this.config,
    required this.controller,
    required this.identityStore,
  });

  final ControllerIdentityPurpose purpose;
  final MatterControllerConfig config;
  final MatterControllerApi controller;
  final MatterControllerIdentityStoreApi identityStore;
}

abstract interface class MatterControllerRuntimeProvider {
  Future<MatterControllerRuntime> load(ControllerIdentityRequest request);

  /// Returns the live runtime for [request.purpose] so the caller can reload
  /// persisted credentials and reconnect without native controller teardown.
  Future<MatterControllerRuntime> restart(ControllerIdentityRequest request);

  Future<void> reset(ControllerIdentityRequest request);

  Future<void> close();
}

/// Creates one controller runtime per purpose and platform.
///
/// A purpose gets its own secure-storage key, so runtime purposes cannot
/// accidentally reuse each other's credentials. The storage key intentionally
/// excludes the run id: the main identity must survive a run and an app restart.
class FlutterMatterControllerRuntimeProvider
    implements MatterControllerRuntimeProvider {
  FlutterMatterControllerRuntimeProvider({
    MatterControllerConfig? config,
    FlutterSecureStorage? secureStorage,
  }) : _config = config ?? MatterControllerConfig(),
       _secureStorage = secureStorage ?? const FlutterSecureStorage();

  static const String _credentialKeyPrefix =
      'flutter_matter.device_test_app.controller_credentials.v1';

  final MatterControllerConfig _config;
  final FlutterSecureStorage _secureStorage;
  final Map<String, MatterControllerRuntime> _runtimes =
      <String, MatterControllerRuntime>{};

  @override
  Future<MatterControllerRuntime> load(
    ControllerIdentityRequest request,
  ) async {
    final key = _keyFor(request);
    final existing = _runtimes[key];
    if (existing != null) {
      return existing;
    }

    final issuer = const FlutterMatterCertificateIssuer();
    final credentialsService = MatterControllerCredentialsService(
      storage: _PurposeScopedCredentialStorage(
        storage: _secureStorage,
        key:
            '$_credentialKeyPrefix.${request.platform.wireName}.'
            '${request.purpose.wireName}',
      ),
      certificateIssuer: issuer,
    );
    final identityStore = MatterControllerCredentialsStoreApi(
      credentialsService,
    );
    final service = MatterControllerService(
      credentialsService: credentialsService,
      controllerFactory: const FlutterMatterControllerFactory(),
      certificateIssuer: issuer,
      config: _config,
    );
    final runtime = MatterControllerRuntime(
      purpose: request.purpose,
      config: _config,
      controller: MatterControllerServiceApi(service),
      identityStore: identityStore,
    );
    _runtimes[key] = runtime;
    return runtime;
  }

  @override
  Future<MatterControllerRuntime> restart(
    ControllerIdentityRequest request,
  ) async {
    final key = _keyFor(request);
    final existing = _runtimes[key];
    if (existing == null) {
      return load(request);
    }
    // Keep the native controller alive. CHIPController's Android delete path
    // calls PlatformMgr().Shutdown() while its event loop is still running,
    // which aborts the process. The adapter reloads the persisted identity and
    // reconnects CASE without entering that unsupported lifecycle path.
    return existing;
  }

  @override
  Future<void> reset(ControllerIdentityRequest request) async {
    final key = _keyFor(request);
    final runtime = await load(request);
    try {
      await runtime.controller.close();
    } finally {
      try {
        await runtime.identityStore.clear();
      } finally {
        _runtimes.remove(key);
      }
    }
  }

  @override
  Future<void> close() async {
    final runtimes = _runtimes.values.toList(growable: false);
    _runtimes.clear();
    for (final runtime in runtimes) {
      await runtime.controller.close();
    }
  }

  String _keyFor(ControllerIdentityRequest request) =>
      '${request.platform.wireName}:${request.purpose.wireName}';
}

class _PurposeScopedCredentialStorage implements MatterSecureCredentialStorage {
  _PurposeScopedCredentialStorage({
    required FlutterSecureStorage storage,
    required String key,
  }) : _storage = storage,
       _key = key;

  final FlutterSecureStorage _storage;
  final String _key;

  @override
  Future<void> delete() => _storage.delete(key: _key);

  @override
  Future<String?> read() => _storage.read(key: _key);

  @override
  Future<void> write(String value) => _storage.write(key: _key, value: value);
}
