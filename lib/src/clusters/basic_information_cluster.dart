import 'dart:async';

import 'package:flutter_matter/src/model/chip_attribute_path.dart';

import '../controller.dart';
import '../exception.dart';
import '../model/chip_path_id.dart';
import '../tlv/tag.dart';
import '../tlv/tlv_reader.dart';

class BasicInformationCluster {
  final ChipDeviceController controller;
  final Object? connContext;
  final int endpointId = 0;
  final int nodeId;
  static const int clusterId = 0x00000028;
  static const Duration _readTimeout = Duration(seconds: 15);

  BasicInformationCluster({
    required this.controller,
    required this.connContext,
    required this.nodeId,
  });

  Future<int> readProductIDAttribute() {
    return _readAttribute<int>(
      attributeId: 4,
      operation: 'BasicInformationCluster.readProductIDAttribute',
      decode: (reader) => reader.getUShort(AnonymousTag.instance),
    );
  }

  Future<int> readVendorIDAttribute() {
    return _readAttribute<int>(
      attributeId: 2,
      operation: 'BasicInformationCluster.readVendorIDAttribute',
      decode: (reader) => reader.getUShort(AnonymousTag.instance),
    );
  }

  Future<int> readSoftwareVersionAttribute() {
    return _readAttribute<int>(
      attributeId: 0x00000009,
      operation: 'BasicInformationCluster.readSoftwareVersionAttribute',
      decode: (reader) => reader.getUInt(AnonymousTag.instance),
    );
  }

  Future<String> readHardwareVersionStringAttribute() {
    return _readAttribute<String>(
      attributeId: 0x00000008,
      operation: 'BasicInformationCluster.readHardwareVersionStringAttribute',
      decode: (reader) => reader.getString(AnonymousTag.instance),
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
