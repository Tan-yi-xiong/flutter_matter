import 'dart:async';

import 'package:flutter_matter/src/model/chip_attribute_path.dart';

import '../controller.dart';
import '../model/chip_path_id.dart';
import '../tlv/tag.dart';
import '../tlv/tlv_reader.dart';

class BasicInformationCluster {
  final ChipDeviceController controller;
  final Object? connContext;
  final int endpointId = 0;
  final int nodeId;
  static const int clusterId = 0x00000028;

  BasicInformationCluster(
      {required this.controller,
      required this.connContext,
      required this.nodeId});

  Future<int> readProductIDAttribute() async {
    const attributeId = 4;
    ChipAttributePath attributePath = ChipAttributePath(
        endpointId: ChipPathId.forId(endpointId),
        attributeId: ChipPathId.forId(attributeId),
        clusterId: ChipPathId.forId(clusterId));
    Completer<int> completer = Completer();
    controller.read(
        nodeId,
        ReportCallbackWarp(
          onReportFun: (nodeState) {
            final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]
                ?.attributes[attributeId]?.tlv;
            if (payload == null) {
              completer.completeError(Exception("payload is null"));
              return;
            }
            final reader = TlvReader(payload);
            completer.complete(reader.getUShort(AnonymousTag.instance));
          },
          onErrorFun: (_, __, e) {
            completer.completeError(e);
          },
        ),
        [attributePath],
        null,
        null,
        false,
        2000,
        0,
        connectContext: connContext);
    return completer.future;
  }

  Future<int> readVendorIDAttribute() async {
    const attributeId = 2;
    ChipAttributePath attributePath = ChipAttributePath(
        endpointId: ChipPathId.forId(endpointId),
        attributeId: ChipPathId.forId(attributeId),
        clusterId: ChipPathId.forId(clusterId));
    Completer<int> completer = Completer();
    controller.read(
        nodeId,
        ReportCallbackWarp(
          onReportFun: (nodeState) {
            final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]
                ?.attributes[attributeId]?.tlv;
            if (payload == null) {
              completer.completeError(Exception("payload is null"));
              return;
            }
            final reader = TlvReader(payload);
            completer.complete(reader.getUShort(AnonymousTag.instance));
          },
          onErrorFun: (_, __, e) {
            completer.completeError(e);
          },
        ),
        [attributePath],
        null,
        null,
        false,
        2000,
        0,
        connectContext: connContext);
    return completer.future;
  }

  Future<int> readSoftwareVersionAttribute() async {
    const attributeId = 0x00000009;
    ChipAttributePath attributePath = ChipAttributePath(
        endpointId: ChipPathId.forId(endpointId),
        attributeId: ChipPathId.forId(attributeId),
        clusterId: ChipPathId.forId(clusterId));
    Completer<int> completer = Completer();
    controller.read(
        nodeId,
        ReportCallbackWarp(
          onReportFun: (nodeState) {
            final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]
                ?.attributes[attributeId]?.tlv;
            if (payload == null) {
              completer.completeError(Exception("payload is null"));
              return;
            }
            final reader = TlvReader(payload);
            completer.complete(reader.getUInt(AnonymousTag.instance));
          },
          onErrorFun: (_, __, e) {
            completer.completeError(e);
          },
        ),
        [attributePath],
        null,
        null,
        false,
        2000,
        0,
        connectContext: connContext);
    return completer.future;
  }

  Future<String> readHardwareVersionStringAttribute() async {
    const attributeId = 0x00000008;
    ChipAttributePath attributePath = ChipAttributePath(
        endpointId: ChipPathId.forId(endpointId),
        attributeId: ChipPathId.forId(attributeId),
        clusterId: ChipPathId.forId(clusterId));
    Completer<String> completer = Completer();
    controller.read(
        nodeId,
        ReportCallbackWarp(
          onReportFun: (nodeState) {
            final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]
                ?.attributes[attributeId]?.tlv;
            if (payload == null) {
              completer.completeError(Exception("payload is null"));
              return;
            }
            final reader = TlvReader(payload);
            completer.complete(reader.getString(AnonymousTag.instance));
          },
          onErrorFun: (_, __, e) {
            completer.completeError(e);
          },
        ),
        [attributePath],
        null,
        null,
        false,
        2000,
        0,
        connectContext: connContext);
    return completer.future;
  }
}
