class Status {
  final int status;
  final int? clusterStatus;

  Status({required this.status, this.clusterStatus});

  factory Status.fromJson(Map json) {
    return Status(
      status: json['status'],
      clusterStatus: json['clusterStatus'],
    );
  }
}