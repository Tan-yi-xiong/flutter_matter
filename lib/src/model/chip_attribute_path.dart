import 'chip_path_id.dart';

class ChipAttributePath {
    final ChipPathId endpointId;
    final ChipPathId clusterId;
    final ChipPathId attributeId;

  ChipAttributePath({required this.endpointId, required this.clusterId, required this.attributeId});

  toJson() => {
    'endpointId': endpointId.toJson(),
    'clusterId': clusterId.toJson(),
    'attributeId': attributeId.toJson(),
  };

  factory ChipAttributePath.fromJson(Map<String, dynamic> json) {
    return ChipAttributePath(
      endpointId: ChipPathId.fromJson(json['endpointId']),
      clusterId: ChipPathId.fromJson(json['clusterId']),
      attributeId: ChipPathId.fromJson(json['attributeId']),
    );
  }
}