import 'dart:typed_data';

import 'chip_path_id.dart';
import 'json_decoding.dart';

class InvokeElement {
  final ChipPathId? endpointId;
  final ChipPathId clusterId;
  final ChipPathId commandId;
  final int groupId;
  final Uint8List? tlv;
  final String? json;

  InvokeElement({
    this.endpointId,
    required this.clusterId,
    required this.commandId,
    required this.groupId,
    this.tlv,
    this.json,
  });

  InvokeElement._({
    this.endpointId,
    required this.clusterId,
    required this.commandId,
    required this.groupId,
    this.tlv,
    this.json,
  });

  factory InvokeElement.create(
    int endpointId,
    int clusterId,
    int commandId,
    Uint8List? tlv,
    String? json,
  ) {
    return InvokeElement(
      endpointId: ChipPathId.forId(endpointId),
      clusterId: ChipPathId.forId(clusterId),
      commandId: ChipPathId.forId(commandId),
      groupId: 0,
      tlv: tlv,
      json: json,
    );
  }

  InvokeElement.fromJson(jsonMap)
      : this._(
          endpointId: _decodeEndpointId(jsonMap),
          clusterId: _decodePath(jsonMap, 'clusterId'),
          commandId: _decodePath(jsonMap, 'commandId'),
          groupId: _decodeGroupId(jsonMap),
          tlv: _decodeTlv(jsonMap),
          json: _decodeJsonStringField(jsonMap),
        );

  toJson() => {
        'endpointId': endpointId?.toJson(),
        'clusterId': clusterId.toJson(),
        'commandId': commandId.toJson(),
        'groupId': groupId,
        'tlv': tlv == null ? null : List.from(tlv!),
        'json': json,
      };
}

ChipPathId? _decodeEndpointId(Object? jsonMap) {
  final root = decodeJsonObject(jsonMap, 'InvokeElement');
  final endpoint = root['endpointId'];
  if (endpoint == null) {
    return null;
  }
  return ChipPathId.fromJson(
    decodeJsonObject(endpoint, 'InvokeElement.endpointId'),
  );
}

ChipPathId _decodePath(Object? jsonMap, String field) {
  final root = decodeJsonObject(jsonMap, 'InvokeElement');
  return ChipPathId.fromJson(
    decodeJsonObject(root[field], 'InvokeElement.$field'),
  );
}

int _decodeGroupId(Object? jsonMap) {
  final root = decodeJsonObject(jsonMap, 'InvokeElement');
  return root['groupId'] == null
      ? 0
      : decodeJsonInt(root['groupId'], 'InvokeElement.groupId');
}

Uint8List? _decodeTlv(Object? jsonMap) {
  final root = decodeJsonObject(jsonMap, 'InvokeElement');
  return root['tlv'] == null
      ? null
      : decodeJsonBytes(root['tlv'], 'InvokeElement.tlv');
}

String? _decodeJsonStringField(Object? jsonMap) {
  final root = decodeJsonObject(jsonMap, 'InvokeElement');
  return decodeJsonNullableString(root['json'], 'InvokeElement.json');
}
