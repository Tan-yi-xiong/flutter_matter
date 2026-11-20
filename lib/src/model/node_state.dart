import 'endpoint_state.dart';
import 'json_decoding.dart';

class NodeState {
  final Map<int, EndpointState> endpoints;

  NodeState({required this.endpoints});

  NodeState.fromJson(Map json) : endpoints = _decodeEndpoints(json);

  static Map<int, EndpointState> _decodeEndpoints(Map json) {
    final root = decodeJsonObject(json, 'NodeState');
    final rawEndpoints = root['endpoints'];
    if (rawEndpoints == null) {
      return <int, EndpointState>{};
    }
    final endpoints = decodeJsonObject(rawEndpoints, 'NodeState.endpoints');
    final result = <int, EndpointState>{};
    for (final entry in endpoints.entries) {
      final field = 'NodeState.endpoints[${entry.key}]';
      result[decodeJsonMapKeyInt(entry.key, 'NodeState.endpoints')] =
          EndpointState.fromJson(decodeJsonObject(entry.value, field));
    }
    return result;
  }
}
