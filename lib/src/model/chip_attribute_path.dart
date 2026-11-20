import 'chip_path_id.dart';
import 'json_decoding.dart';

class ChipAttributePath {
  final ChipPathId endpointId;
  final ChipPathId clusterId;
  final ChipPathId attributeId;

  ChipAttributePath({
    required this.endpointId,
    required this.clusterId,
    required this.attributeId,
  });

  toJson() => {
        'endpointId': endpointId.toJson(),
        'clusterId': clusterId.toJson(),
        'attributeId': attributeId.toJson(),
      };

  factory ChipAttributePath.fromJson(Map<String, dynamic> json) {
    final root = decodeJsonObject(json, 'ChipAttributePath');
    return ChipAttributePath(
      endpointId: ChipPathId.fromJson(
        decodeJsonObject(root['endpointId'], 'ChipAttributePath.endpointId'),
      ),
      clusterId: ChipPathId.fromJson(
        decodeJsonObject(root['clusterId'], 'ChipAttributePath.clusterId'),
      ),
      attributeId: ChipPathId.fromJson(
        decodeJsonObject(root['attributeId'], 'ChipAttributePath.attributeId'),
      ),
    );
  }
}
