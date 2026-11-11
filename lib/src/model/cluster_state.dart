import 'attribute_state.dart';
import 'event_state.dart';
import 'status.dart';

class ClusterState {
  final Map<int, AttributeState> attributes;
  final Map<int, List<EventState>> events;
  final Map<int, Status> attributeStatuses;
  final Map<int, List<Status>> eventStatuses;
  final int? dataVersion;

  ClusterState({
    required this.attributes,
    required this.events,
    required this.attributeStatuses,
    required this.eventStatuses,
    this.dataVersion,
  });

  factory ClusterState.fromJson(Map json) {
    return ClusterState(
      attributes: _decodeMap(json['attributes'], AttributeState.fromJson),
      events: _decodeListMap(json['events'], EventState.fromJson),
      attributeStatuses: _decodeMap(json['attributeStatuses'], Status.fromJson),
      eventStatuses: _decodeListMap(json['eventStatuses'], Status.fromJson),
      dataVersion: json['dataVersion'],
    );
  }

  static Map<int, T> _decodeMap<T>(
    dynamic source,
    T Function(Map json) decode,
  ) {
    if (source == null) {
      return <int, T>{};
    }

    return (source as Map).map<int, T>(
      (key, value) => MapEntry(
        int.parse(key.toString()),
        decode(value as Map),
      ),
    );
  }

  static Map<int, List<T>> _decodeListMap<T>(
    dynamic source,
    T Function(Map json) decode,
  ) {
    if (source == null) {
      return <int, List<T>>{};
    }

    return (source as Map).map<int, List<T>>(
      (key, value) => MapEntry(
        int.parse(key.toString()),
        (value as List)
            .map((item) => decode(item as Map))
            .toList(growable: false),
      ),
    );
  }
}
