import 'dart:typed_data';

class AttributeState {
  final Uint8List? tlv;
  final String? json;

  AttributeState({this.tlv, this.json});

  factory AttributeState.fromJson(Map jsonMap) {
    return AttributeState(
      tlv: jsonMap['tlv'] == null ? null : Uint8List.fromList(jsonMap['tlv'].cast<int>()),
      json: jsonMap['json'],
    );
  }
}