import 'chip_path_id.dart';

class ChipEventPath {
  final ChipPathId endpointId;
  final ChipPathId clusterId;
  final ChipPathId eventId;
  final bool isUrgent;

  ChipEventPath(
      {required this.endpointId,
      required this.clusterId,
      required this.eventId,
      required this.isUrgent});
  
  toJson() => {
    "endpointId": endpointId.toJson(),
    "clusterId": clusterId.toJson(),
    "eventId": eventId.toJson(),
    "isUrgent": isUrgent
  };
}
