import 'dart:async';

import 'package:flutter_matter/flutter_matter.dart';

class DescriptorCluster {
  final ChipDeviceController controller;
  final Object? connContext;
  final int endpointId;
  final int nodeId;
  static const int clusterId = 0x1D;

  DescriptorCluster({required this.controller, required this.connContext, required this.endpointId, required this.nodeId});

  Future<List<int>> readServerListAttribute() {
    const attributeId = 1;
    ChipAttributePath attributePath = ChipAttributePath(
      endpointId: ChipPathId.forId(endpointId),
      attributeId: ChipPathId.forId(attributeId),
      clusterId: ChipPathId.forId(clusterId)
    );
    Completer<List<int>> completer = Completer();
    controller.read(
      nodeId, 
      ReportCallbackWarp(
        onReportFun: (nodeState) {
          final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]?.attributes[attributeId]?.tlv;
          if (payload == null) {
            completer.completeError(Exception("payload is null"));
            return;
          }
          final reader = TlvReader(payload);
          List<int> partsList = [];
          reader.enterArray(AnonymousTag.instance);
          while (!reader.isEndOfContainer()) {
            partsList.add(reader.getUInt(AnonymousTag.instance));
          }
          reader.exitContainer();
          completer.complete(partsList);
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
      connectContext: connContext
    );
    return completer.future;
  }

  Future<List<int>>  readPartsListAttribute() {
    const attributeId = 3;
    ChipAttributePath attributePath = ChipAttributePath(
      endpointId: ChipPathId.forId(endpointId),
      attributeId: ChipPathId.forId(attributeId),
      clusterId: ChipPathId.forId(clusterId)
    );
    Completer<List<int>> completer = Completer();
    controller.read(
      nodeId, 
      ReportCallbackWarp(
        onReportFun: (nodeState) {
          final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]?.attributes[attributeId]?.tlv;
          if (payload == null) {
            completer.completeError(Exception("payload is null"));
            return;
          }
          final reader = TlvReader(payload);
          List<int> partsList = [];
          reader.enterArray(AnonymousTag.instance);
          while (!reader.isEndOfContainer()) {
            partsList.add(reader.getUShort(AnonymousTag.instance));
          }
          reader.exitContainer();
          completer.complete(partsList);
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
      connectContext: connContext
    );
    return completer.future;
  }

  Future<List<int>> readDeviceTypeListAttribute() {
    const attributeId = 0;
    ChipAttributePath attributePath = ChipAttributePath(
      endpointId: ChipPathId.forId(endpointId),
      attributeId: ChipPathId.forId(attributeId),
      clusterId: ChipPathId.forId(clusterId)
    );
    Completer<List<int>> completer = Completer();
    controller.read(
      nodeId, 
      ReportCallbackWarp(
        onReportFun: (nodeState) {
          final payload = nodeState.endpoints[endpointId]?.clusters[clusterId]?.attributes[attributeId]?.tlv;
          if (payload == null) {
            completer.completeError(Exception("payload is null"));
            return;
          }
          final reader = TlvReader(payload);
          List<int> deviceTypeList = [];
          reader.enterArray(AnonymousTag.instance);
          while (!reader.isEndOfContainer()) {
            reader.enterStructure(AnonymousTag.instance);
            deviceTypeList.add(reader.getUInt(AnonymousTag.instance));
            reader.exitContainer();
          }
          reader.exitContainer();
          completer.complete(deviceTypeList);
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
      connectContext: connContext
    );
    return completer.future;
  }
}