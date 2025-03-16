import 'chip_path_id.dart';

class DataVersionFilter {
  final ChipPathId endpointId;
  final ChipPathId clusterId;
  final int dataVersion;

  DataVersionFilter({required this.endpointId, required this.clusterId, required this.dataVersion});

  toJson() {
    return {
      'endpointId': endpointId.toJson(),
      'clusterId': clusterId.toJson(),
      'dataVersion': dataVersion,
    };
  }
}
