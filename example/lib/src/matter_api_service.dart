import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import 'models.dart';

class MatterApiService {
  Future<Object?> connect({
    required ChipDeviceController controller,
    required int nodeId,
    Duration timeout = const Duration(seconds: 30),
  }) async {
    final completer = Completer<Object?>();
    await controller.connectedDevice(
      nodeId,
      _ConnectedCallback(
        onConnectedValue: completer.complete,
        onErrorValue: completer.completeError,
      ),
    );
    return completer.future.timeout(timeout);
  }

  Future<void> releaseContext(
    ChipDeviceController controller,
    Object? context,
  ) async {
    if (context != null) {
      await controller.releaseConnectContext(context);
    }
  }

  Future<InvokeReply> invoke({
    required ChipDeviceController controller,
    required int nodeId,
    required InvokeElement element,
    Object? context,
    int timedRequestTimeoutMs = 0,
    int imTimeoutMs = 0,
    Duration timeout = const Duration(seconds: 15),
  }) async {
    final completer = Completer<InvokeReply>();
    final callback = _InvokeCallback(
      onReplyValue: (reply) {
        if (!completer.isCompleted) {
          completer.complete(reply);
        }
      },
      onErrorValue: (error) {
        if (!completer.isCompleted) {
          completer.completeError(error);
        }
      },
      onDoneValue: () {
        if (!completer.isCompleted) {
          completer.completeError(
            StateError('Invoke completed without a response.'),
          );
        }
      },
    );
    await controller.invoke(
      callback,
      nodeId,
      element,
      connectContext: context,
      timedRequestTimeoutMs: timedRequestTimeoutMs,
      imTimeoutMs: imTimeoutMs,
    );
    return completer.future.timeout(timeout);
  }

  Future<NodeState> read({
    required ChipDeviceController controller,
    required int nodeId,
    required List<ChipAttributePath> attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    Object? context,
    bool isFabricFiltered = false,
    int imTimeoutMs = 0,
    int eventMin = 0,
    Duration timeout = const Duration(seconds: 15),
  }) async {
    final completer = Completer<NodeState>();
    final callback = ReportCallbackWarp(
      onReportFun: (state) {
        if (!completer.isCompleted) {
          completer.complete(state);
        }
      },
      onErrorFun: (_, __, error) {
        if (!completer.isCompleted) {
          completer.completeError(error);
        }
      },
      onDoneFun: () {
        if (!completer.isCompleted) {
          completer.completeError(
            StateError('Read completed without a report.'),
          );
        }
      },
    );
    await controller.read(
      nodeId,
      callback,
      attributePaths,
      eventPaths,
      dataVersionFilters,
      isFabricFiltered,
      5000,
      imTimeoutMs,
      connectContext: context,
    );
    return completer.future.timeout(timeout);
  }

  Future<Status?> write({
    required ChipDeviceController controller,
    required int nodeId,
    required List<AttributeWriteRequest> attributes,
    Object? context,
    int timedRequestTimeoutMs = 5000,
    int imTimeoutMs = 2000,
    Duration timeout = const Duration(seconds: 15),
  }) async {
    final completer = Completer<Status?>();
    final callback = WriteAttributesCallbackWarp(
      onResponseFun: (_, status) {
        if (!completer.isCompleted) {
          completer.complete(status);
        }
      },
      onErrorFun: (_, error) {
        if (!completer.isCompleted) {
          completer.completeError(error);
        }
      },
      onDoneFun: () {
        if (!completer.isCompleted) {
          completer.complete();
        }
      },
    );
    await controller.write(
      nodeId,
      callback,
      attributes,
      timedRequestTimeoutMs,
      imTimeoutMs,
      connectContext: context,
    );
    return completer.future.timeout(timeout);
  }

  Future<SubscriptionSession> subscribe({
    required ChipDeviceController controller,
    required int nodeId,
    required List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    Object? context,
    int minInterval = 1,
    int maxInterval = 10,
    bool keepSubscriptions = true,
    bool isFabricFiltered = false,
    int imTimeoutMs = 6000,
    int eventMin = 0,
    Duration timeout = const Duration(seconds: 15),
  }) async {
    final established = Completer<int>();
    final updates = StreamController<SubscriptionUpdate>.broadcast();
    final callback = SubscriptionCallbackWarp(
      onSubscriptionEstablishedFun: (id) {
        if (!established.isCompleted) {
          established.complete(id);
        }
      },
      onErrorFun: (_, __, error) {
        if (!established.isCompleted) {
          established.completeError(error);
        }
        updates.add(SubscriptionUpdate(error: error));
      },
      onDoneFun: updates.close,
      onReportFun: (state) {
        updates.add(SubscriptionUpdate(nodeState: state));
      },
    );
    await controller.subscribe(
      nodeId,
      callback,
      attributePaths,
      eventPaths,
      dataVersionFilters,
      minInterval,
      maxInterval,
      keepSubscriptions,
      isFabricFiltered,
      imTimeoutMs,
      eventMin,
      connectContext: context,
    );
    final id = await established.future.timeout(timeout);
    return SubscriptionSession(
      id: id,
      updates: updates.stream,
      cancel: () async {
        final fabricIndex = await controller.getFabricIndex();
        if (fabricIndex == null) {
          return false;
        }
        final result = await controller.unSubscription(fabricIndex, nodeId, id);
        await updates.close();
        return result;
      },
    );
  }

  Future<CommissioningWindowResult> openCommissioningWindow({
    required ChipDeviceController controller,
    required int nodeId,
    required Object context,
    required int durationSeconds,
    required int discriminator,
    required int setupPin,
    Duration timeout = const Duration(seconds: 20),
  }) async {
    // Clear any existing commissioning-window state first so the button can be
    // pressed repeatedly. When no window is open the device answers
    // WindowNotOpen (cluster-status 0x04); that failure is expected and must
    // not block opening a fresh window below.
    final revokeWriter = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..endStructure();
    try {
      await invoke(
        controller: controller,
        nodeId: nodeId,
        context: context,
        timedRequestTimeoutMs: 5000,
        element: InvokeElement.create(
          0,
          0x003C,
          0x0002,
          revokeWriter.getEncoded(),
          null,
        ),
      );
    } catch (error) {
      // Revoke may legitimately fail when no window is open; proceed.
    }
    final completer = Completer<CommissioningWindowResult>();
    final callback = _OpenCommissioningCallback(
      onSuccessValue: (manualPairingCode, qrCode) {
        if (!completer.isCompleted) {
          completer.complete(
            CommissioningWindowResult(
              manualPairingCode: manualPairingCode,
              qrCode: qrCode,
            ),
          );
        }
      },
      onErrorValue: (error) {
        if (!completer.isCompleted) {
          completer.completeError(error);
        }
      },
    );
    final started = await controller.openPairingWindowWithPIN(
      context,
      durationSeconds,
      discriminator,
      setupPin,
      callback,
    );
    if (!started) {
      throw StateError('The device rejected the commissioning window request.');
    }
    return completer.future.timeout(timeout);
  }

  Future<FabricSnapshot> readFabrics({
    required ChipDeviceController controller,
    required int nodeId,
    Object? context,
  }) async {
    final state = await read(
      controller: controller,
      nodeId: nodeId,
      context: context,
      attributePaths: [
        ChipAttributePath(
          endpointId: ChipPathId.forId(0),
          clusterId: ChipPathId.forId(0x003E),
          attributeId: ChipPathId.forId(0x0005),
        ),
      ],
    );
    final rawTlv =
        state.endpoints[0]?.clusters[0x003E]?.attributes[0x0005]?.tlv;
    return FabricSnapshot(
      currentFabricIndex: await controller.getFabricIndex(),
      rawNodeState: state,
      rawTlv: rawTlv,
    );
  }

  Future<InvokeReply> removeFabric({
    required ChipDeviceController controller,
    required int nodeId,
    required int fabricIndex,
    Object? context,
  }) {
    final writer = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..putUnsigned(ContextSpecificTag(0), fabricIndex)
      ..endStructure();
    return invoke(
      controller: controller,
      nodeId: nodeId,
      context: context,
      element: InvokeElement.create(
        0,
        0x003E,
        0x000A,
        writer.getEncoded(),
        null,
      ),
    );
  }
}

class _ConnectedCallback implements ConnectedDeviceCallback {
  _ConnectedCallback({
    required this.onConnectedValue,
    required this.onErrorValue,
  });

  final void Function(Object? context) onConnectedValue;
  final void Function(Exception error) onErrorValue;

  @override
  void onConnected(Object? context) => onConnectedValue(context);

  @override
  void onError(Exception error) => onErrorValue(error);
}

class _InvokeCallback implements InvokeCallback {
  _InvokeCallback({
    required this.onReplyValue,
    required this.onErrorValue,
    required this.onDoneValue,
  });

  final void Function(InvokeReply reply) onReplyValue;
  final void Function(Exception error) onErrorValue;
  final void Function() onDoneValue;

  @override
  void onDone() => onDoneValue();

  @override
  void onError(Exception e) => onErrorValue(e);

  @override
  void onResponse(InvokeElement invokeElement, int successCode) {
    onReplyValue(InvokeReply(element: invokeElement, successCode: successCode));
  }
}

class _OpenCommissioningCallback implements OpenCommissioningCallback {
  _OpenCommissioningCallback({
    required this.onSuccessValue,
    required this.onErrorValue,
  });

  final void Function(String manualPairingCode, String qrCode) onSuccessValue;
  final void Function(Exception error) onErrorValue;

  @override
  void onError(int status, Object? connectContext) {
    onErrorValue(Exception('Commissioning window failed with status $status.'));
  }

  @override
  void onSuccess(
    Object? connectContext,
    String manualPairingCode,
    String qrCode,
  ) {
    onSuccessValue(manualPairingCode, qrCode);
  }
}

String describeNodeState(NodeState state) {
  final lines = <String>[];
  final endpoints = state.endpoints.keys.toList()..sort();
  for (final endpoint in endpoints) {
    lines.add('Endpoint ${formatId(endpoint)}');
    final clusters = state.endpoints[endpoint]?.clusters ?? const {};
    final clusterIds = clusters.keys.toList()..sort();
    for (final cluster in clusterIds) {
      lines.add('  Cluster ${formatId(cluster)}');
      final clusterState = clusters[cluster];
      final attributes = clusterState?.attributes ?? const {};
      final attributeIds = attributes.keys.toList()..sort();
      for (final attribute in attributeIds) {
        lines.add(
          '    Attribute ${formatId(attribute)}: '
          '${formatBytes(attributes[attribute]?.tlv)}',
        );
      }
      final events = clusterState?.events ?? const {};
      for (final event in events.keys.toList()..sort()) {
        lines.add('    Events ${formatId(event)}: ${events[event]!.length}');
      }
    }
  }
  return lines.isEmpty
      ? 'No attribute or event data returned.'
      : lines.join('\n');
}

NodeState emptyNodeState() => NodeState(endpoints: const {});

Uint8List encodeHex(String source) {
  final withoutPrefix = source.replaceAll(
    RegExp('0x', caseSensitive: false),
    '',
  );
  final normalized = withoutPrefix.replaceAll(RegExp(r'[^0-9a-fA-F]'), '');
  if (normalized.isEmpty) {
    return Uint8List(0);
  }
  if (normalized.length.isOdd) {
    throw const FormatException(
      'TLV hex must contain an even number of digits.',
    );
  }
  return Uint8List.fromList(
    List<int>.generate(
      normalized.length ~/ 2,
      (index) =>
          int.parse(normalized.substring(index * 2, index * 2 + 2), radix: 16),
    ),
  );
}

int parseMatterId(String source, {bool allowWildcard = false}) {
  final value = source.trim().toLowerCase();
  if (allowWildcard && (value == '*' || value == 'wildcard')) {
    return -1;
  }
  final parsed = value.startsWith('0x')
      ? int.tryParse(value.substring(2), radix: 16)
      : int.tryParse(value);
  if (parsed == null || parsed < 0) {
    throw FormatException('Invalid Matter ID: $source');
  }
  return parsed;
}

ChipPathId parsePathId(String source, {bool allowWildcard = false}) {
  final parsed = parseMatterId(source, allowWildcard: allowWildcard);
  return parsed == -1 ? ChipPathId.forWildcard() : ChipPathId.forId(parsed);
}
