import 'json_decoding.dart';

class Status {
  final int status;
  final int? clusterStatus;

  Status({required this.status, this.clusterStatus});

  factory Status.fromJson(Map json) {
    final root = decodeJsonObject(json, 'Status');
    return Status(
      status: decodeJsonInt(root['status'], 'Status.status'),
      clusterStatus: decodeJsonNullableInt(
        root['clusterStatus'],
        'Status.clusterStatus',
      ),
    );
  }
}
