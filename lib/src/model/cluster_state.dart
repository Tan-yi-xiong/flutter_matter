import 'attribute_state.dart';
import 'event_state.dart';
import 'json_decoding.dart';
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
    final root = decodeJsonObject(json, 'ClusterState');
    return ClusterState(
      attributes: _decodeMap(
        root['attributes'],
        'ClusterState.attributes',
        AttributeState.fromJson,
      ),
      events: _decodeListMap(
        root['events'],
        'ClusterState.events',
        EventState.fromJson,
      ),
      attributeStatuses: _decodeMap(
        root['attributeStatuses'],
        'ClusterState.attributeStatuses',
        Status.fromJson,
      ),
      eventStatuses: _decodeListMap(
        root['eventStatuses'],
        'ClusterState.eventStatuses',
        Status.fromJson,
      ),
      dataVersion: root['dataVersion'] == null
          ? null
          : decodeJsonInt(root['dataVersion'], 'ClusterState.dataVersion'),
    );
  }

  static Map<int, T> _decodeMap<T>(
    Object? source,
    String field,
    T Function(Map json) decode,
  ) {
    if (source == null) {
      return <int, T>{};
    }

    final map = decodeJsonObject(source, field);
    final result = <int, T>{};
    for (final entry in map.entries) {
      final itemField = '$field[${entry.key}]';
      result[decodeJsonMapKeyInt(entry.key, field)] = decode(
        decodeJsonObject(entry.value, itemField),
      );
    }
    return result;
  }

  static Map<int, List<T>> _decodeListMap<T>(
    Object? source,
    String field,
    T Function(Map json) decode,
  ) {
    if (source == null) {
      return <int, List<T>>{};
    }

    final map = decodeJsonObject(source, field);
    final result = <int, List<T>>{};
    for (final entry in map.entries) {
      final itemField = '$field[${entry.key}]';
      final rawList = decodeJsonArray(entry.value, itemField);
      result[decodeJsonMapKeyInt(entry.key, field)] = <T>[
        for (var i = 0; i < rawList.length; i++)
          decode(
            decodeJsonObject(rawList[i], '$itemField[$i]'),
          ),
      ];
    }
    return result;
  }
}
