import 'dart:typed_data';

import 'json_decoding.dart';

class AttributeState {
  final Uint8List? tlv;
  final String? json;

  AttributeState({this.tlv, this.json});

  factory AttributeState.fromJson(Map jsonMap) {
    final root = decodeJsonObject(jsonMap, 'AttributeState');
    return AttributeState(
      tlv: root['tlv'] == null
          ? null
          : decodeJsonBytes(root['tlv'], 'AttributeState.tlv'),
      json: decodeJsonNullableString(root['json'], 'AttributeState.json'),
    );
  }
}
