import 'cluster_state.dart';
import 'json_decoding.dart';

class EndpointState {
  final Map<int, ClusterState> clusters;

  EndpointState(this.clusters);

  factory EndpointState.fromJson(Map json) {
    final root = decodeJsonObject(json, 'EndpointState');
    final rawClusters = root['clusters'];
    if (rawClusters == null) {
      return EndpointState(<int, ClusterState>{});
    }
    final clusters = decodeJsonObject(rawClusters, 'EndpointState.clusters');
    final result = <int, ClusterState>{};
    for (final entry in clusters.entries) {
      final field = 'EndpointState.clusters[${entry.key}]';
      result[decodeJsonMapKeyInt(entry.key, 'EndpointState.clusters')] =
          ClusterState.fromJson(decodeJsonObject(entry.value, field));
    }
    return EndpointState(result);
  }
}
