import 'dart:typed_data';

/// Internal helpers for validating JSON-shaped values from native callbacks.
///
/// These functions intentionally produce contextual [FormatException]s instead
/// of unchecked casts or `int.parse` errors leaking out of model factories.

Map<String, dynamic> decodeJsonObject(Object? value, String field) {
  if (value is Map) {
    final result = <String, dynamic>{};
    for (final entry in value.entries) {
      if (entry.key is! String) {
        throw FormatException(
          '$field must use string keys; got ${_jsonType(entry.key)}',
        );
      }
      result[entry.key as String] = entry.value;
    }
    return result;
  }
  throw FormatException(
      '$field must be a JSON object; got ${_jsonType(value)}');
}

List<dynamic> decodeJsonArray(Object? value, String field) {
  if (value is List) {
    return value;
  }
  throw FormatException('$field must be a JSON array; got ${_jsonType(value)}');
}

int decodeJsonInt(Object? value, String field) {
  if (value is int) {
    return value;
  }
  throw FormatException('$field must be an integer; got ${_jsonType(value)}');
}

int? decodeJsonNullableInt(Object? value, String field) {
  return value == null ? null : decodeJsonInt(value, field);
}

bool decodeJsonBool(Object? value, String field) {
  if (value is bool) {
    return value;
  }
  throw FormatException('$field must be a boolean; got ${_jsonType(value)}');
}

String decodeJsonString(Object? value, String field) {
  if (value is String) {
    return value;
  }
  throw FormatException('$field must be a string; got ${_jsonType(value)}');
}

String? decodeJsonNullableString(Object? value, String field) {
  return value == null ? null : decodeJsonString(value, field);
}

List<int> decodeJsonIntArray(Object? value, String field) {
  final array = decodeJsonArray(value, field);
  return <int>[
    for (var i = 0; i < array.length; i++)
      decodeJsonInt(array[i], '$field[$i]'),
  ];
}

Uint8List decodeJsonBytes(Object? value, String field) {
  final array = decodeJsonArray(value, field);
  final bytes = <int>[];
  for (var i = 0; i < array.length; i++) {
    final item = array[i];
    if (item is! int || item < 0 || item > 0xff) {
      throw FormatException('$field[$i] must be a byte between 0 and 255');
    }
    bytes.add(item);
  }
  return Uint8List.fromList(bytes);
}

int decodeJsonMapKeyInt(Object? key, String field) {
  final text = key is String ? key : key?.toString();
  if (text == null) {
    throw FormatException('$field key must be an integer; got null');
  }
  try {
    return int.parse(text);
  } on FormatException {
    throw FormatException(
        '$field key must be an integer; got ${_jsonType(key)}');
  }
}

String _jsonType(Object? value) {
  if (value == null) {
    return 'null';
  }
  return value.runtimeType.toString();
}
