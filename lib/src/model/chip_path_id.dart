import 'json_decoding.dart';

enum IdType {
  concrete,
  wildcard,
}

class ChipPathId {
  final int id;
  final IdType type;

  ChipPathId._({required this.id, required this.type});

  ChipPathId.forId(this.id) : type = IdType.concrete;

  ChipPathId.forWildcard()
      : id = -1,
        type = IdType.wildcard;

  ChipPathId.fromJson(jsonMap)
      : this._(
          id: _decodeId(jsonMap),
          type: _decodeType(jsonMap),
        );

  toJson() => {
        'id': id,
        'type': type.name,
      };
}

int _decodeId(Object? jsonMap) {
  final root = decodeJsonObject(jsonMap, 'ChipPathId');
  return decodeJsonInt(root['id'], 'ChipPathId.id');
}

IdType _decodeType(Object? jsonMap) {
  final root = decodeJsonObject(jsonMap, 'ChipPathId');
  final rawType = root['type'];
  if (rawType == null) {
    return IdType.concrete;
  }
  final typeName = decodeJsonString(rawType, 'ChipPathId.type').toLowerCase();
  for (final type in IdType.values) {
    if (type.name == typeName) {
      return type;
    }
  }
  throw FormatException(
    'ChipPathId.type must be "concrete" or "wildcard"; got "${typeName}"',
  );
}
