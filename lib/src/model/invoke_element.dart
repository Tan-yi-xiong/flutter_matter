import 'dart:typed_data';

import 'chip_path_id.dart';

class InvokeElement {
    final ChipPathId? endpointId;
    final ChipPathId clusterId;
    final ChipPathId commandId;
    final int groupId;
    final Uint8List? tlv;
    final String? json;

  InvokeElement({this.endpointId, required this.clusterId, required this.commandId, required this.groupId, this.tlv, this.json});

  factory InvokeElement.create(int endpointId, int clusterId, int commandId, Uint8List? tlv, String? json) {
    return InvokeElement(
      endpointId: ChipPathId.forId(endpointId),
      clusterId: ChipPathId.forId(clusterId),
      commandId: ChipPathId.forId(commandId),
      groupId: 0,
      tlv: tlv,
      json: json
    );
  }

  toJson() => {
    "endpointId": endpointId?.toJson(),
    "clusterId": clusterId.toJson(),
    "commandId": commandId.toJson(),
    "groupId": groupId,
    "tlv": tlv == null ? null : List.from(tlv!),
    "json": json
  };

  InvokeElement.fromJson(jsonMap):
    endpointId = jsonMap['endpointId'] == null ? null : ChipPathId.fromJson(jsonMap['endpointId']),
    clusterId = ChipPathId.fromJson(jsonMap['clusterId']),
    commandId = ChipPathId.fromJson(jsonMap['commandId']),
    groupId = jsonMap['groupId'] ?? 0,
    tlv = jsonMap['tlv'] == null ? null : Uint8List.fromList(jsonMap['tlv'].cast<int>()),
    json = jsonMap['json'];
 }