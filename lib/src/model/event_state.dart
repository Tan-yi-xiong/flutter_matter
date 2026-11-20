import 'dart:typed_data';

import 'json_decoding.dart';

class EventState {
  final int eventNumber;
  final int priorityLevel;
  final int timestampType;
  final int timestampValue;

  final Uint8List? tlv;
  final String? json;

  EventState({
    required this.eventNumber,
    required this.priorityLevel,
    required this.timestampType,
    required this.timestampValue,
    this.tlv,
    this.json,
  });

  factory EventState.fromJson(Map jsonMap) {
    final root = decodeJsonObject(jsonMap, 'EventState');
    return EventState(
      eventNumber: decodeJsonInt(
        root['eventNumber'],
        'EventState.eventNumber',
      ),
      priorityLevel: decodeJsonInt(
        root['priorityLevel'],
        'EventState.priorityLevel',
      ),
      timestampType: decodeJsonInt(
        root['timestampType'],
        'EventState.timestampType',
      ),
      timestampValue: decodeJsonInt(
        root['timestampValue'],
        'EventState.timestampValue',
      ),
      tlv: root['tlv'] == null
          ? null
          : decodeJsonBytes(root['tlv'], 'EventState.tlv'),
      json: decodeJsonNullableString(root['json'], 'EventState.json'),
    );
  }
}
