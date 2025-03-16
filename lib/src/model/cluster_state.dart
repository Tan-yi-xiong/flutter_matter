import 'attribute_state.dart';
import 'event_state.dart';
import 'status.dart';

class ClusterState {
  final Map<int, AttributeState> attributes;
  final Map<int, List<EventState>> events;
  final Map<int, Status> attributeStatuses;
  final Map<int, List<Status>> eventStatuses;
  final int? dataVersion;

  ClusterState({required this.attributes, required this.events, required this.attributeStatuses, required this.eventStatuses, this.dataVersion});

  factory ClusterState.fromJson(Map json) {
    return ClusterState(
      attributes: json['attributes'] == null 
          ? {} 
          : Map<int, AttributeState>.from((json['attributes'] as Map).map((key, value) => MapEntry(int.parse(key.toString()), AttributeState.fromJson(value)))).cast(),
      events: json['events'] == null 
          ? {} 
          : Map<int, List<EventState>>.from((json['events'] as Map).map((key, value) => MapEntry(int.parse(key.toString()), List<EventState>.from(value.map((e) => EventState.fromJson(e))).cast()))).cast(),
      attributeStatuses: json['attributeStatuses'] == null 
          ? {} 
          : Map<int, Status>.from((json['attributeStatuses'] as Map).map((key, value) => MapEntry(int.parse(key.toString()), Status.fromJson(value)))).cast(),
      eventStatuses: json['eventStatuses'] == null 
          ? {} 
          : Map<int, List<Status>>.from((json['eventStatuses'] as Map).map((key, value) => MapEntry(int.parse(key.toString()), List<Status>.from(value.map((e) => Status.fromJson(e))).cast()))).cast(),
      dataVersion: json['dataVersion'],
    );
  }
}
