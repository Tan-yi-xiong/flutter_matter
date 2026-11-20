import 'dart:async';

import '../controller.dart';
import '../exception.dart';
import '../model/chip_attribute_path.dart';
import '../model/chip_path_id.dart';
import '../tlv/tag.dart';
import '../tlv/tlv_reader.dart';

class DescriptorCluster {
  final ChipDeviceController controller;
  final Object? connContext;
  final int endpointId;
  final int nodeId;
  static const int clusterId = 0x1D;
  static const Duration _readTimeout = Duration(seconds: 15);

  DescriptorCluster({
    required this.controller,
    required this.connContext,
    required this.endpointId,
    required this.nodeId,
  });

  Future<List<int>> readServerListAttribute() {
    return _readAttribute<List<int>>(
      attributeId: 1,
      operation: 'DescriptorCluster.readServerListAttribute',
      decode: (reader) {
        reader.enterArray(AnonymousTag.instance);
        final values = <int>[];
        while (!reader.isEndOfContainer()) {
          values.add(reader.getUInt(AnonymousTag.instance));
        }
        reader.exitContainer();
        return values;
      },
    );
  }

  Future<List<int>> readPartsListAttribute() {
    return _readAttribute<List<int>>(
      attributeId: 3,
      operation: 'DescriptorCluster.readPartsListAttribute',
      decode: (reader) {
        reader.enterArray(AnonymousTag.instance);
        final values = <int>[];
        while (!reader.isEndOfContainer()) {
          values.add(reader.getUShort(AnonymousTag.instance));
        }
        reader.exitContainer();
        return values;
      },
    );
  }

  Future<List<int>> readDeviceTypeListAttribute() {
    return _readAttribute<List<int>>(
      attributeId: 0,
      operation: 'DescriptorCluster.readDeviceTypeListAttribute',
      decode: (reader) {
        reader.enterArray(AnonymousTag.instance);
        final values = <int>[];
        while (!reader.isEndOfContainer()) {
          reader.enterStructure(AnonymousTag.instance);
          values.add(reader.getUInt(AnonymousTag.instance));
          reader.exitContainer();
        }
        reader.exitContainer();
        return values;
      },
    );
  }

  Future<T> _readAttribute<T>({
    required int attributeId,
    required String operation,
    required T Function(TlvReader reader) decode,
  }) {
    final attributePath = ChipAttributePath(
      endpointId: ChipPathId.forId(endpointId),
      attributeId: ChipPathId.forId(attributeId),
      clusterId: ChipPathId.forId(clusterId),
    );
    final completer = Completer<T>();
    Timer? timeoutTimer;

    void completeValue(T value) {
      timeoutTimer?.cancel();
      if (!completer.isCompleted) {
        completer.complete(value);
      }
    }

    void completeError(Object error) {
      timeoutTimer?.cancel();
      _completeError(completer, operation, attributeId, error);
    }

    final callback = ReportCallbackWarp(
      onReportFun: (nodeState) {
        if (completer.isCompleted) {
          return;
        }
        try {
          final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]
              ?.attributes[attributeId]?.tlv;
          if (payload == null) {
            throw StateError('Attribute $attributeId payload is null');
          }
          final value = decode(TlvReader(payload));
          completeValue(value);
        } catch (error) {
          completeError(error);
        }
      },
      onErrorFun: (_, __, error) {
        completeError(error);
      },
      onDoneFun: () {
        completeError(StateError('Read completed without a report'));
      },
    );

    controller
        .read(
      nodeId,
      callback,
      [attributePath],
      null,
      null,
      false,
      2000,
      0,
      connectContext: connContext,
    )
        .then<void>(
      (_) {
        if (completer.isCompleted) {
          return;
        }
        timeoutTimer = Timer(_readTimeout, () {
          completeError(
            TimeoutException(
              '$operation timed out after ${_readTimeout.inSeconds} seconds',
              _readTimeout,
            ),
          );
        });
      },
      onError: (Object error, StackTrace stackTrace) {
        completeError(error);
      },
    );
    return completer.future;
  }

  void _completeError<T>(
    Completer<T> completer,
    String operation,
    int attributeId,
    Object error,
  ) {
    if (completer.isCompleted) {
      return;
    }
    completer.completeError(
      error is CallPlatformException
          ? error
          : CallPlatformException(
              'Failed to decode $operation',
              code: unHandlerException,
              methodName: operation,
              details: <String, Object?>{
                'host': 'cluster',
                'category': 'cluster-report',
                'clusterId': clusterId,
                'attributeId': attributeId,
              },
              cause: error,
            ),
    );
  }
}
