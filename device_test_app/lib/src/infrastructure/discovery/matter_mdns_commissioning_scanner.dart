import 'dart:async';

import 'package:bonsoir/bonsoir.dart';

const String matterCommissionableServiceType = '_matterc._udp';

class MatterMdnsService {
  const MatterMdnsService({
    required this.name,
    required this.type,
    required this.attributes,
    this.resolve,
  });

  final String name;
  final String type;
  final Map<String, String> attributes;
  final Future<void> Function()? resolve;
}

abstract interface class MatterMdnsBrowser {
  Future<void> start();

  Stream<MatterMdnsService> get services;

  Future<void> stop();
}

class BonsoirMatterMdnsBrowser implements MatterMdnsBrowser {
  BonsoirMatterMdnsBrowser({
    BonsoirDiscovery? discovery,
    this.serviceType = matterCommissionableServiceType,
  }) : _discovery = discovery ?? BonsoirDiscovery(type: serviceType);

  final BonsoirDiscovery _discovery;
  final String serviceType;

  @override
  Future<void> start() async {
    await _discovery.ready;
    await _discovery.start();
  }

  @override
  Stream<MatterMdnsService> get services {
    return (_discovery.eventStream ?? const Stream.empty()).expand((event) {
      final service = event.service;
      if (service == null || service.type != serviceType) {
        return const <MatterMdnsService>[];
      }
      if (event.type == BonsoirDiscoveryEventType.discoveryServiceFound) {
        return <MatterMdnsService>[
          MatterMdnsService(
            name: service.name,
            type: service.type,
            attributes: service.attributes,
            resolve: () => service.resolve(_discovery.serviceResolver),
          ),
        ];
      }
      if (event.type == BonsoirDiscoveryEventType.discoveryServiceResolved) {
        return <MatterMdnsService>[
          MatterMdnsService(
            name: service.name,
            type: service.type,
            attributes: service.attributes,
          ),
        ];
      }
      return const <MatterMdnsService>[];
    });
  }

  @override
  Future<void> stop() async {
    if (!_discovery.isStopped) {
      await _discovery.stop();
    }
  }
}

abstract interface class MatterMdnsCommissioningScannerApi {
  Future<bool> waitForMatch({
    required int discriminator,
    required bool hasShortDiscriminator,
    required Duration timeout,
  });
}

class MatterMdnsCommissioningScanner
    implements MatterMdnsCommissioningScannerApi {
  MatterMdnsCommissioningScanner({
    required MatterMdnsBrowser Function() browserFactory,
    this.serviceType = matterCommissionableServiceType,
  }) : _browserFactory = browserFactory;

  final MatterMdnsBrowser Function() _browserFactory;
  final String serviceType;

  @override
  Future<bool> waitForMatch({
    required int discriminator,
    required bool hasShortDiscriminator,
    required Duration timeout,
  }) async {
    if (timeout <= Duration.zero) {
      throw ArgumentError.value(timeout, 'timeout', 'Must be positive');
    }

    final browser = _browserFactory();
    StreamSubscription<MatterMdnsService>? subscription;
    final matched = Completer<bool>();
    final resolvedNames = <String>{};

    Future<void> resolveIfNeeded(MatterMdnsService service) async {
      if (MatterMdnsDiscriminatorMatcher.matches(
        attributes: service.attributes,
        discriminator: discriminator,
        hasShortDiscriminator: hasShortDiscriminator,
      )) {
        if (!matched.isCompleted) {
          matched.complete(true);
        }
        return;
      }
      final resolve = service.resolve;
      if (resolve != null && resolvedNames.add(service.name)) {
        await resolve();
      }
    }

    try {
      subscription = browser.services.listen(
        (service) {
          unawaited(resolveIfNeeded(service));
        },
        onError: (Object error, StackTrace stackTrace) {
          if (!matched.isCompleted) {
            matched.completeError(error, stackTrace);
          }
        },
      );
      await browser.start();

      return await matched.future.timeout(timeout, onTimeout: () => false);
    } on TimeoutException {
      return false;
    } finally {
      await subscription?.cancel();
      try {
        await browser.stop();
      } on Object {
        // The primary result is already known; cleanup is best effort.
      }
    }
  }
}

abstract final class MatterMdnsDiscriminatorMatcher {
  static bool matches({
    required Map<String, String> attributes,
    required int discriminator,
    required bool hasShortDiscriminator,
  }) {
    final raw = attributes['D'] ?? attributes['d'];
    if (raw == null) {
      return false;
    }
    final observed = _parseDiscriminator(raw);
    if (observed == null) {
      return false;
    }
    if (hasShortDiscriminator) {
      return (observed >> 8) == (discriminator & 0x0f);
    }
    return observed == discriminator;
  }

  static int? _parseDiscriminator(String value) {
    final normalized = value.trim().toLowerCase();
    if (normalized.isEmpty) {
      return null;
    }
    if (normalized.startsWith('0x')) {
      return int.tryParse(normalized.substring(2), radix: 16);
    }
    return int.tryParse(normalized);
  }
}
