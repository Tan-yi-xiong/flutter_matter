import 'dart:collection';

import 'endpoint_state.dart';

class NodeState {
  final Map<int, EndpointState> endpoints;

  NodeState({required this.endpoints});

  NodeState.fromJson(Map json)
      : endpoints = json['endpoints'] != null
            ? (json['endpoints'] as Map).map((k, v) =>
                MapEntry(int.parse(k.toString()), EndpointState.fromJson(v))).cast()
            : <int, EndpointState>{};
}
