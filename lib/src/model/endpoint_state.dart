import 'cluster_state.dart';

class EndpointState {
  final Map<int, ClusterState> clusters;

  EndpointState(this.clusters);

  factory EndpointState.fromJson(Map json) {
    return EndpointState((json['clusters']  as  Map?)?.map((key, value) => MapEntry(int.parse(key.toString()), ClusterState.fromJson(value))).cast() ?? {});
  }
}