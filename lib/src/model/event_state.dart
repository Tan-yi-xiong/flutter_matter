import 'dart:typed_data';

class EventState {
  final int eventNumber;
  final int priorityLevel;
  final int timestampType;
  final int timestampValue;

  final Uint8List? tlv;
  final String? json;

  factory EventState.fromJson(Map jsonMap) {
    return EventState(
      eventNumber: jsonMap['eventNumber'],
      priorityLevel: jsonMap['priorityLevel'],
      timestampType: jsonMap['timestampType'],
      timestampValue: jsonMap['timestampValue'],
      tlv: jsonMap['tlv'] == null ? null : Uint8List.fromList(jsonMap['tlv']),
      json: jsonMap['json'],
    );
  }

  EventState({required this.eventNumber, required this.priorityLevel, required this.timestampType, required this.timestampValue, this.tlv, this.json});
}