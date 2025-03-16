enum IdType {
  concrete,
  wildcard,
}

class ChipPathId {
  final int id;
  final IdType type;

  ChipPathId._({required this.id, required this.type});

  ChipPathId.forId(this.id) :
    type = IdType.concrete;
  
  ChipPathId.forWildcard():
    id = -1,
    type = IdType.wildcard;

  toJson() => {
    "id": id,
    "type": type.name,
  };

  ChipPathId.fromJson(jsonMap): 
    id = jsonMap["id"],
    type = jsonMap["type"] == null ? IdType.concrete : IdType.values.firstWhere((element) => element.name.toLowerCase() == jsonMap["type"].toString().toLowerCase());
}
