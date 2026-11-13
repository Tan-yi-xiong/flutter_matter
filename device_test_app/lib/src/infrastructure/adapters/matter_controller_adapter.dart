import 'dart:async';

import 'package:flutter/services.dart';

import '../../application/ports.dart';
import '../../domain/domain.dart';
import '../matter/matter.dart';
import 'matter_controller_api.dart';
import 'opaque_handle_factory.dart';
import 'purpose_scoped_runtime.dart';

/// Connects application hardware ports to the committed Matter controller
/// service. Matter SDK calls and credential details remain inside this adapter.
class MatterControllerAdapter
    implements
        ControllerIdentityPort,
        CommissioningPort,
        OperationalConnectionPort,
        OnOffPort,
        NodeLabelPort,
        FabricPort {
  MatterControllerAdapter({
    required MatterControllerRuntimeProvider runtimeProvider,
    required ControllerPlatform platform,
    OpaqueHandleFactory? handleFactory,
  }) : _runtimeProvider = runtimeProvider,
       _platform = platform,
       _handles = handleFactory ?? OpaqueHandleFactory();

  final MatterControllerRuntimeProvider _runtimeProvider;
  final ControllerPlatform _platform;
  final OpaqueHandleFactory _handles;
  final Map<String, MatterControllerRuntime> _runtimesByIdentity =
      <String, MatterControllerRuntime>{};
  final Map<String, _ConnectionHandle> _connections =
      <String, _ConnectionHandle>{};
  final List<_SubscriptionCancellation> _activeSubscriptions =
      <_SubscriptionCancellation>[];

  @override
  Future<ControllerIdentity> loadOrCreate(
    ControllerIdentityRequest request,
  ) async {
    try {
      final runtime = await _runtimeProvider.load(request);
      final credentials = await runtime.identityStore.loadOrCreate(
        runtime.config,
      );
      final identity = ControllerIdentity(
        opaqueId: matterIdentityOpaqueId(
          purpose: request.purpose,
          publicKey: credentials.identity.publicKeyBytes,
        ),
        purpose: request.purpose,
      );
      _runtimesByIdentity[identity.opaqueId] = runtime;
      return identity;
    } on MatterException catch (error) {
      throw StateError('Unable to load controller identity: ${error.code}');
    } on Object catch (error) {
      throw StateError(
        'Unable to load controller identity: ${error.runtimeType}',
      );
    }
  }

  @override
  Future<ControllerIdentity> restart(ControllerIdentityRequest request) async {
    final removedIdentities = _runtimesByIdentity.entries
        .where((entry) => entry.value.purpose == request.purpose)
        .map((entry) => entry.key)
        .toSet();
    await _cancelSubscriptionsForIdentities(removedIdentities);
    try {
      final runtime = await _runtimeProvider.restart(request);
      final credentials = await runtime.identityStore.loadOrCreate(
        runtime.config,
      );
      final identity = ControllerIdentity(
        opaqueId: matterIdentityOpaqueId(
          purpose: request.purpose,
          publicKey: credentials.identity.publicKeyBytes,
        ),
        purpose: request.purpose,
      );
      _runtimesByIdentity.removeWhere(
        (opaqueId, entryRuntime) => entryRuntime.purpose == request.purpose,
      );
      _runtimesByIdentity[identity.opaqueId] = runtime;
      _connections.removeWhere(
        (_, connection) =>
            removedIdentities.contains(connection.identityOpaqueId),
      );
      return identity;
    } on MatterException catch (error) {
      throw StateError('Unable to restart controller runtime: ${error.code}');
    } on Object catch (error) {
      throw StateError(
        'Unable to restart controller runtime: ${error.runtimeType}',
      );
    }
  }

  @override
  Future<void> reset(ControllerIdentityRequest request) async {
    final removedIdentities = _runtimesByIdentity.entries
        .where((entry) => entry.value.purpose == request.purpose)
        .map((entry) => entry.key)
        .toSet();
    await _cancelSubscriptionsForIdentities(removedIdentities);
    try {
      await _runtimeProvider.reset(request);
    } finally {
      final removed = <String>{};
      _runtimesByIdentity.removeWhere((opaqueId, runtime) {
        final shouldRemove = runtime.purpose == request.purpose;
        if (shouldRemove) {
          removed.add(opaqueId);
        }
        return shouldRemove;
      });
      _connections.removeWhere(
        (_, connection) => removed.contains(connection.identityOpaqueId),
      );
    }
  }

  @override
  Future<CommissioningResult> commission(CommissioningRequest request) async {
    try {
      final runtime = await _runtimeFor(request.identity);
      final network = _toMatterNetwork(request.network);
      final result = await runtime.controller.commission(
        MatterCommissionRequest(
          onboardingPayload: request.onboardingPayload,
          setupPinCode: request.setupPinCode,
          nodeId: request.targetNodeId,
          networkCredentials: network,
          discriminator: request.setupDiscriminator,
          onNetworkAddress: request.onNetworkEndpoint?.address,
          onNetworkPort: request.onNetworkEndpoint?.port,
          timeout: request.timeout,
        ),
      );
      return CommissioningResult(
        errorCode: 0,
        nodeId: result.nodeId,
        networkTransport: request.network.transport,
      );
    } on CommissioningException {
      rethrow;
    } on TimeoutException {
      throw CommissioningException(CommissioningFailureCode.timeout);
    } on MatterException catch (error) {
      throw _mapCommissioningError(error);
    } on PlatformException catch (error) {
      throw _mapCommissioningPlatformError(error);
    } on StateError {
      throw CommissioningException(CommissioningFailureCode.other);
    } on FormatException {
      throw CommissioningException(CommissioningFailureCode.invalidSetupCode);
    } on ArgumentError {
      throw CommissioningException(CommissioningFailureCode.other);
    } on Object {
      throw CommissioningException(CommissioningFailureCode.other);
    }
  }

  @override
  Future<OperationalConnectionLease> connect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  }) {
    return _connect(identity: identity, nodeId: nodeId, timeout: timeout);
  }

  @override
  Future<OperationalConnectionLease> reconnect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  }) async {
    await _releaseConnectionsFor(identity.opaqueId, nodeId, ignoreErrors: true);
    return _connect(identity: identity, nodeId: nodeId, timeout: timeout);
  }

  Future<OperationalConnectionLease> _connect({
    required ControllerIdentity identity,
    required int nodeId,
    required Duration timeout,
  }) async {
    final runtime = await _runtimeFor(identity);
    try {
      final matterConnection = await _withTimeout(
        runtime.controller.connect(
          MatterConnectRequest(nodeId: nodeId, timeout: timeout),
        ),
        timeout,
      );
      final lease = OperationalConnectionLease(
        opaqueId: _handles.next('connection'),
        nodeId: nodeId,
        isValid: matterConnection.context != null,
      );
      _connections[lease.opaqueId] = _ConnectionHandle(
        lease: lease,
        identityOpaqueId: identity.opaqueId,
        runtime: runtime,
        matterConnection: matterConnection,
      );
      return lease;
    } on TimeoutException {
      throw TimeoutException('Operational connection timed out', timeout);
    } on MatterException {
      throw StateError('Operational connection failed');
    } on Object {
      throw StateError('Operational connection failed');
    }
  }

  @override
  Future<void> disconnect(OperationalConnectionLease connection) async {
    await _cancelSubscriptionsForConnection(connection.opaqueId);
    final handle = _connections[connection.opaqueId];
    if (handle == null) {
      return;
    }
    try {
      await _withTimeout(
        handle.runtime.controller.releaseConnection(handle.matterConnection),
        connection.isValid
            ? const Duration(seconds: 30)
            : const Duration(seconds: 1),
      );
    } on TimeoutException {
      throw TimeoutException('Operational connection release timed out');
    } on MatterException {
      throw StateError('Operational connection release failed');
    } finally {
      _connections.remove(connection.opaqueId);
    }
  }

  @override
  Future<OnOffState> readState({
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    final handle = _requireConnection(
      connection,
      failure: OnOffException(OnOffFailureCode.notConnected),
    );
    try {
      final value = await _withTimeout(
        handle.runtime.controller.readAttribute(
          MatterReadAttributeRequest(
            nodeId: connection.nodeId,
            endpointId: 1,
            clusterId: matterOnOffClusterId,
            attributeId: matterOnOffAttributeId,
            connection: handle.matterConnection,
          ),
        ),
        timeout,
      );
      return _decodeOnOff(value);
    } on OnOffException {
      rethrow;
    } on MatterException catch (error) {
      throw OnOffException(_mapOnOffMatter(error));
    } on MatterTlvException {
      throw OnOffException(OnOffFailureCode.readFailed);
    } on TimeoutException {
      throw OnOffException(OnOffFailureCode.timeout);
    } on Object {
      throw OnOffException(OnOffFailureCode.other);
    }
  }

  @override
  Future<OnOffInvocation> invoke({
    required OperationalConnectionLease connection,
    required OnOffCommand command,
    required Duration timeout,
  }) async {
    final previous = await readState(connection: connection, timeout: timeout);
    final handle = _requireConnection(
      connection,
      failure: OnOffException(OnOffFailureCode.notConnected),
    );
    try {
      final result = await _withTimeout(
        handle.runtime.controller.invokeOnOff(
          MatterOnOffRequest(
            nodeId: connection.nodeId,
            endpointId: 1,
            command: _toMatterCommand(command),
            connection: handle.matterConnection,
            timedRequestTimeoutMs: _milliseconds(timeout),
          ),
        ),
        timeout,
      );
      if (!result.isSuccess) {
        throw OnOffException(OnOffFailureCode.invokeRejected);
      }
      final current = await readState(connection: connection, timeout: timeout);
      return OnOffInvocation(previousState: previous, currentState: current);
    } on OnOffException {
      rethrow;
    } on MatterException catch (error) {
      throw OnOffException(_mapOnOffMatter(error));
    } on TimeoutException {
      throw OnOffException(OnOffFailureCode.timeout);
    } on Object {
      throw OnOffException(OnOffFailureCode.other);
    }
  }

  @override
  Future<OnOffSubscription> subscribe({
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    final initial = await readState(connection: connection, timeout: timeout);
    final handle = _requireConnection(
      connection,
      failure: OnOffException(OnOffFailureCode.notConnected),
    );
    final MatterSubscription subscription;
    try {
      subscription = await _withTimeout(
        handle.runtime.controller.subscribeOnOff(
          nodeId: connection.nodeId,
          connection: handle.matterConnection,
        ),
        timeout,
      );
    } on MatterException catch (error) {
      throw OnOffException(_mapOnOffMatter(error));
    } on TimeoutException {
      throw OnOffException(OnOffFailureCode.timeout);
    } on Object {
      throw OnOffException(OnOffFailureCode.other);
    }

    final updates = StreamController<OnOffState>.broadcast();
    var current = initial;
    var firstReport = true;
    _SubscriptionCancellation? activeCancellation;
    Future<void>? cancellationFuture;
    final reportSubscription = subscription.reports.listen(
      (value) {
        try {
          final next = _decodeOnOff(value);
          if (firstReport && next == initial) {
            firstReport = false;
            return;
          }
          firstReport = false;
          if (next == current) {
            return;
          }
          current = next;
          if (!updates.isClosed) {
            updates.add(next);
          }
        } on Object {
          if (!updates.isClosed) {
            updates.addError(OnOffException(OnOffFailureCode.readFailed));
          }
        }
      },
      onError: (Object error, StackTrace stackTrace) {
        if (!updates.isClosed) {
          updates.addError(
            error is MatterException
                ? OnOffException(_mapOnOffMatter(error))
                : OnOffException(OnOffFailureCode.subscribeFailed),
            stackTrace,
          );
        }
      },
      onDone: () {
        final cancellation = activeCancellation;
        if (cancellation != null) {
          _activeSubscriptions.remove(cancellation);
        }
        cancellationFuture ??= Future<void>.value();
        if (!updates.isClosed) {
          unawaited(updates.close());
        }
      },
    );
    final errorSubscription = subscription.errors.listen(
      (error) {
        if (!updates.isClosed) {
          updates.addError(OnOffException(_mapOnOffMatter(error)));
        }
      },
      onError: (Object error, StackTrace stackTrace) {
        if (!updates.isClosed) {
          updates.addError(
            OnOffException(OnOffFailureCode.subscribeFailed),
            stackTrace,
          );
        }
      },
    );

    Future<void> cancelSubscription() {
      final existing = cancellationFuture;
      if (existing != null) {
        return existing;
      }
      final pending = _cancelSubscription(
        reportSubscription: reportSubscription,
        errorSubscription: errorSubscription,
        subscription: subscription,
        updates: updates,
      );
      cancellationFuture = pending;
      return pending;
    }

    final cancellation = _SubscriptionCancellation(
      identityOpaqueId: handle.identityOpaqueId,
      connectionOpaqueId: connection.opaqueId,
      cancel: cancelSubscription,
    );
    activeCancellation = cancellation;
    _activeSubscriptions.add(cancellation);

    return OnOffSubscription(
      initialState: initial,
      updates: updates.stream,
      cancel: () {
        _activeSubscriptions.remove(cancellation);
        return cancelSubscription();
      },
    );
  }

  @override
  Future<String> read({
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    final handle = _requireConnection(
      connection,
      failure: NodeLabelException(NodeLabelFailureCode.notConnected),
    );
    try {
      return await _withTimeout(
        handle.runtime.controller.readNodeLabel(
          nodeId: connection.nodeId,
          connection: handle.matterConnection,
        ),
        timeout,
      );
    } on MatterException catch (error) {
      throw NodeLabelException(_mapNodeLabelMatter(error));
    } on TimeoutException {
      throw NodeLabelException(NodeLabelFailureCode.timeout);
    } on Object {
      throw NodeLabelException(NodeLabelFailureCode.other);
    }
  }

  @override
  Future<void> write({
    required OperationalConnectionLease connection,
    required String value,
    required Duration timeout,
  }) async {
    final handle = _requireConnection(
      connection,
      failure: NodeLabelException(NodeLabelFailureCode.notConnected),
    );
    try {
      final result = await _withTimeout(
        handle.runtime.controller.writeNodeLabel(
          MatterWriteNodeLabelRequest(
            nodeId: connection.nodeId,
            label: value,
            connection: handle.matterConnection,
            timedRequestTimeoutMs: _milliseconds(timeout),
          ),
        ),
        timeout,
      );
      if (!result.isSuccess) {
        throw NodeLabelException(NodeLabelFailureCode.writeFailed);
      }
    } on NodeLabelException {
      rethrow;
    } on MatterException catch (error) {
      throw NodeLabelException(_mapNodeLabelMatter(error));
    } on TimeoutException {
      throw NodeLabelException(NodeLabelFailureCode.timeout);
    } on Object {
      throw NodeLabelException(NodeLabelFailureCode.other);
    }
  }

  @override
  Future<FabricStatus> inspect({
    required ControllerIdentity identity,
    required int nodeId,
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    final handle = _requireConnection(
      connection,
      failure: FabricException(FabricFailureCode.notConnected),
    );
    try {
      final value = await _withTimeout(
        handle.runtime.controller.readAttribute(
          MatterReadAttributeRequest(
            nodeId: nodeId,
            endpointId: 0,
            clusterId: matterOperationalCredentialsClusterId,
            attributeId: matterCurrentFabricIndexAttributeId,
            connection: handle.matterConnection,
          ),
        ),
        timeout,
      );
      return FabricStatus(present: true, fabricIndex: value.decodeUnsigned());
    } on MatterException catch (error) {
      throw FabricException(_mapFabricMatter(error, removing: false));
    } on MatterTlvException {
      throw FabricException(FabricFailureCode.inspectFailed);
    } on TimeoutException {
      throw FabricException(FabricFailureCode.timeout);
    } on Object {
      throw FabricException(FabricFailureCode.other);
    }
  }

  @override
  Future<void> remove({
    required ControllerIdentity identity,
    required int nodeId,
    required OperationalConnectionLease connection,
    required Duration timeout,
  }) async {
    final handle = _requireConnection(
      connection,
      failure: FabricException(FabricFailureCode.notConnected),
    );
    try {
      final result = await _withTimeout(
        handle.runtime.controller.removeFabric(
          MatterRemoveFabricRequest(
            nodeId: nodeId,
            connection: handle.matterConnection,
            timedRequestTimeoutMs: _milliseconds(timeout),
          ),
        ),
        timeout,
      );
      if (!result.isSuccess) {
        throw FabricException(FabricFailureCode.removeFailed);
      }
    } on FabricException {
      rethrow;
    } on MatterException catch (error) {
      throw FabricException(_mapFabricMatter(error, removing: true));
    } on TimeoutException {
      throw FabricException(FabricFailureCode.timeout);
    } on Object {
      throw FabricException(FabricFailureCode.other);
    }
  }

  Future<void> close() async {
    await _cancelAllSubscriptions();
    for (final handle in _connections.values.toList(growable: false)) {
      try {
        await handle.runtime.controller.releaseConnection(
          handle.matterConnection,
        );
      } on Object {
        // Closing the adapter must not mask a previous test result.
      }
    }
    _connections.clear();
    _runtimesByIdentity.clear();
    await _runtimeProvider.close();
  }

  Future<MatterControllerRuntime> _runtimeFor(
    ControllerIdentity identity,
  ) async {
    final existing = _runtimesByIdentity[identity.opaqueId];
    if (existing != null) {
      return existing;
    }
    final request = ControllerIdentityRequest(
      runId: 'restored',
      purpose: identity.purpose,
      platform: _platform,
    );
    final runtime = await _runtimeProvider.load(request);
    final credentials = await runtime.identityStore.loadOrCreate(
      runtime.config,
    );
    final expected = matterIdentityOpaqueId(
      purpose: identity.purpose,
      publicKey: credentials.identity.publicKeyBytes,
    );
    if (expected != identity.opaqueId) {
      throw StateError('The controller identity is no longer available');
    }
    _runtimesByIdentity[identity.opaqueId] = runtime;
    return runtime;
  }

  _ConnectionHandle _requireConnection(
    OperationalConnectionLease connection, {
    required Object failure,
  }) {
    if (!connection.isValid) {
      throw failure;
    }
    final handle = _connections[connection.opaqueId];
    if (handle == null) {
      throw failure;
    }
    return handle;
  }

  Future<void> _releaseConnectionsFor(
    String identityOpaqueId,
    int nodeId, {
    required bool ignoreErrors,
  }) async {
    final matching = _connections.values
        .where(
          (handle) =>
              handle.identityOpaqueId == identityOpaqueId &&
              handle.lease.nodeId == nodeId,
        )
        .toList(growable: false);
    await _cancelSubscriptionsForConnections(
      matching.map((handle) => handle.lease.opaqueId).toSet(),
    );
    for (final handle in matching) {
      try {
        await handle.runtime.controller.releaseConnection(
          handle.matterConnection,
        );
      } on Object {
        if (!ignoreErrors) {
          rethrow;
        }
      } finally {
        _connections.remove(handle.lease.opaqueId);
      }
    }
  }

  Future<void> _cancelSubscriptionsForConnection(
    String connectionOpaqueId,
  ) async {
    final matching = _activeSubscriptions
        .where(
          (cancellation) =>
              cancellation.connectionOpaqueId == connectionOpaqueId,
        )
        .toList(growable: false);
    _activeSubscriptions.removeWhere(
      (cancellation) => matching.contains(cancellation),
    );
    await _cancelSubscriptions(matching);
  }

  Future<void> _cancelSubscriptionsForConnections(
    Set<String> connectionOpaqueIds,
  ) async {
    if (connectionOpaqueIds.isEmpty) {
      return;
    }
    final matching = _activeSubscriptions
        .where(
          (cancellation) =>
              connectionOpaqueIds.contains(cancellation.connectionOpaqueId),
        )
        .toList(growable: false);
    _activeSubscriptions.removeWhere(
      (cancellation) => matching.contains(cancellation),
    );
    await _cancelSubscriptions(matching);
  }

  Future<void> _cancelSubscriptionsForIdentities(
    Set<String> identityOpaqueIds,
  ) async {
    if (identityOpaqueIds.isEmpty) {
      return;
    }
    final matching = _activeSubscriptions
        .where(
          (cancellation) =>
              identityOpaqueIds.contains(cancellation.identityOpaqueId),
        )
        .toList(growable: false);
    _activeSubscriptions.removeWhere(
      (cancellation) => matching.contains(cancellation),
    );
    await _cancelSubscriptions(matching);
  }

  Future<void> _cancelAllSubscriptions() async {
    final matching = _activeSubscriptions.toList(growable: false);
    _activeSubscriptions.clear();
    await _cancelSubscriptions(matching);
  }

  Future<void> _cancelSubscriptions(
    List<_SubscriptionCancellation> cancellations,
  ) async {
    for (final cancellation in cancellations) {
      try {
        await cancellation.cancel();
      } on Object {
        // Adapter teardown must continue cleaning up remaining subscriptions.
      }
    }
  }

  Future<T> _withTimeout<T>(Future<T> future, Duration timeout) {
    if (timeout <= Duration.zero) {
      throw TimeoutException('The operation timeout must be positive', timeout);
    }
    return future.timeout(timeout);
  }
}

class _ConnectionHandle {
  const _ConnectionHandle({
    required this.lease,
    required this.identityOpaqueId,
    required this.runtime,
    required this.matterConnection,
  });

  final OperationalConnectionLease lease;
  final String identityOpaqueId;
  final MatterControllerRuntime runtime;
  final MatterConnection matterConnection;
}

class _SubscriptionCancellation {
  const _SubscriptionCancellation({
    required this.identityOpaqueId,
    required this.connectionOpaqueId,
    required this.cancel,
  });

  final String identityOpaqueId;
  final String connectionOpaqueId;
  final Future<void> Function() cancel;
}

Future<void> _cancelSubscription({
  required StreamSubscription<MatterAttributeValue> reportSubscription,
  required StreamSubscription<MatterException> errorSubscription,
  required MatterSubscription subscription,
  required StreamController<OnOffState> updates,
}) async {
  try {
    await reportSubscription.cancel();
  } finally {
    try {
      await errorSubscription.cancel();
    } finally {
      try {
        final closed = await subscription.close();
        if (!closed) {
          throw OnOffException(OnOffFailureCode.subscribeFailed);
        }
      } on MatterException catch (error) {
        throw OnOffException(_mapOnOffMatter(error));
      } on TimeoutException {
        throw OnOffException(OnOffFailureCode.timeout);
      } finally {
        if (!updates.isClosed) {
          await updates.close();
        }
      }
    }
  }
}

OnOffState _decodeOnOff(MatterAttributeValue value) {
  return value.decodeBool() ? OnOffState.on : OnOffState.off;
}

MatterOnOffCommand _toMatterCommand(OnOffCommand command) {
  return switch (command) {
    OnOffCommand.off => MatterOnOffCommand.off,
    OnOffCommand.on => MatterOnOffCommand.on,
    OnOffCommand.toggle => MatterOnOffCommand.toggle,
  };
}

MatterNetworkCredentials _toMatterNetwork(ProvisioningNetworkSecret network) {
  return switch (network) {
    WifiProvisioningSecret(:final ssid, :final password) =>
      MatterWifiNetworkCredentials(
        MatterWifiCredentials(ssid: ssid, password: password),
      ),
    ThreadProvisioningSecret(:final operationalDataset) =>
      MatterThreadNetworkCredentials(
        MatterThreadCredentials(operationalDataset: operationalDataset),
      ),
  };
}

int _milliseconds(Duration timeout) {
  final value = timeout.inMilliseconds;
  return value > 0 ? value : 1;
}

CommissioningException _mapCommissioningError(MatterException error) {
  final platformError = _findCause<PlatformException>(error);
  if (platformError != null) {
    return _mapCommissioningPlatformError(platformError);
  }
  return switch (error.code) {
    MatterFailureCode.invalidArgument => CommissioningException(
      CommissioningFailureCode.invalidSetupCode,
    ),
    MatterFailureCode.callbackTimeout => CommissioningException(
      CommissioningFailureCode.timeout,
    ),
    MatterFailureCode.pairingFailed ||
    MatterFailureCode.commissioningFailed => CommissioningException(
      CommissioningFailureCode.commissioningFailed,
      errorCode: _errorCodeFromMessage(error.message),
    ),
    MatterFailureCode.notInitialized ||
    MatterFailureCode.initializationFailed ||
    MatterFailureCode.connectFailed ||
    MatterFailureCode.invokeFailed ||
    MatterFailureCode.readFailed ||
    MatterFailureCode.writeFailed ||
    MatterFailureCode.subscribeFailed ||
    MatterFailureCode.unsubscribeFailed ||
    MatterFailureCode.unsupportedOperation => CommissioningException(
      CommissioningFailureCode.other,
    ),
  };
}

CommissioningException _mapCommissioningPlatformError(PlatformException error) {
  final code = error.code.toLowerCase();
  if (code.contains('permission') ||
      code.contains('denied') ||
      code.contains('unauthorized')) {
    return CommissioningException(CommissioningFailureCode.permissionDenied);
  }
  if (code.contains('bluetooth') ||
      code.contains('adapter') ||
      code.contains('radio')) {
    return CommissioningException(
      CommissioningFailureCode.bluetoothUnavailable,
    );
  }
  return CommissioningException(CommissioningFailureCode.other);
}

OnOffFailureCode _mapOnOffMatter(MatterException error) {
  return switch (error.code) {
    MatterFailureCode.callbackTimeout => OnOffFailureCode.timeout,
    MatterFailureCode.invokeFailed => OnOffFailureCode.invokeRejected,
    MatterFailureCode.readFailed => OnOffFailureCode.readFailed,
    MatterFailureCode.subscribeFailed ||
    MatterFailureCode.unsubscribeFailed => OnOffFailureCode.subscribeFailed,
    MatterFailureCode.notInitialized ||
    MatterFailureCode.connectFailed => OnOffFailureCode.notConnected,
    MatterFailureCode.invalidArgument ||
    MatterFailureCode.initializationFailed ||
    MatterFailureCode.pairingFailed ||
    MatterFailureCode.commissioningFailed ||
    MatterFailureCode.writeFailed ||
    MatterFailureCode.unsupportedOperation => OnOffFailureCode.other,
  };
}

NodeLabelFailureCode _mapNodeLabelMatter(MatterException error) {
  return switch (error.code) {
    MatterFailureCode.callbackTimeout => NodeLabelFailureCode.timeout,
    MatterFailureCode.readFailed => NodeLabelFailureCode.readFailed,
    MatterFailureCode.writeFailed => NodeLabelFailureCode.writeFailed,
    MatterFailureCode.notInitialized ||
    MatterFailureCode.connectFailed => NodeLabelFailureCode.notConnected,
    MatterFailureCode.invalidArgument ||
    MatterFailureCode.initializationFailed ||
    MatterFailureCode.pairingFailed ||
    MatterFailureCode.commissioningFailed ||
    MatterFailureCode.invokeFailed ||
    MatterFailureCode.subscribeFailed ||
    MatterFailureCode.unsubscribeFailed ||
    MatterFailureCode.unsupportedOperation => NodeLabelFailureCode.other,
  };
}

FabricFailureCode _mapFabricMatter(
  MatterException error, {
  required bool removing,
}) {
  if (removing &&
      (error.code == MatterFailureCode.invokeFailed ||
          error.code == MatterFailureCode.commissioningFailed)) {
    return FabricFailureCode.removeFailed;
  }
  return switch (error.code) {
    MatterFailureCode.callbackTimeout => FabricFailureCode.timeout,
    MatterFailureCode.invokeFailed => FabricFailureCode.other,
    MatterFailureCode.readFailed => FabricFailureCode.inspectFailed,
    MatterFailureCode.notInitialized ||
    MatterFailureCode.connectFailed => FabricFailureCode.notConnected,
    MatterFailureCode.invalidArgument ||
    MatterFailureCode.initializationFailed ||
    MatterFailureCode.pairingFailed ||
    MatterFailureCode.commissioningFailed ||
    MatterFailureCode.writeFailed ||
    MatterFailureCode.subscribeFailed ||
    MatterFailureCode.unsubscribeFailed ||
    MatterFailureCode.unsupportedOperation => FabricFailureCode.other,
  };
}

int? _errorCodeFromMessage(String message) {
  final match = RegExp(r'error code (\d+)').firstMatch(message);
  return match == null ? null : int.tryParse(match.group(1)!);
}

T? _findCause<T extends Object>(Object? error) {
  Object? current = error;
  final visited = <Object>{};
  while (current != null && visited.add(current)) {
    if (current is T) {
      return current;
    }
    current = switch (current) {
      MatterException(:final cause) => cause,
      _ => null,
    };
  }
  return null;
}
