import 'dart:typed_data';

import 'chip_path_id.dart';

class AttributeWriteRequest {
  final ChipPathId endpointId;
  final ChipPathId clusterId;
  final ChipPathId attributeId;
  final int dataVersion;

  final Uint8List? tlv;

  final String? json;

  AttributeWriteRequest(
      {required this.endpointId,
      required this.clusterId,
      required this.attributeId,
      required this.dataVersion,
      this.tlv,
      this.json});
  
  toJson() => {
    "endpointId": endpointId.toJson(),
    "clusterId": clusterId.toJson(),
    "attributeId": attributeId.toJson(),
    "dataVersion": dataVersion,
    "tlv": tlv?.toList(),
    "json": json
  };
}
