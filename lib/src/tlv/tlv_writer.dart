import 'dart:typed_data';

import 'element.dart';
import 'tag.dart';
import 'tlv_types.dart';
import 'values.dart';

// 此文件由kotlin TlvWriter.kt 使用ai转成dart

class TlvWriter {
  late List<int> _data;
  late int _containerDepth;
  late List<Type> _containerType;

  Uint8List get _bytes => Uint8List.fromList(_data);

  TlvWriter([int initialCapacity = 32]) {
    _data = [];
    _containerDepth = 0;
    _containerType = List<Type>.filled(4, NullType());
  }

  TlvWriter _put(Element element) {
    var value = element.value;
    var tag = element.tag;
    var type = value.toType();
    var encodedType = type.encode();

    if (_containerDepth == 0) {
      if (tag is ContextSpecificTag) {
        throw ArgumentError(
            "Invalid use of context tag at index ${_bytes.lengthInBytes}: can only be used within a structure or a list");
      }
    } else if (_containerType[_containerDepth - 1] is ArrayType) {
      if (tag is! AnonymousTag) {
        throw ArgumentError(
            "Invalid element tag at index ${_bytes.lengthInBytes}: elements of an array SHALL be anonymous");
      }
    } else if (_containerType[_containerDepth - 1] is StructureType && type is! EndOfContainerType) {
      if (tag is AnonymousTag) {
        throw ArgumentError(
            "Invalid element tag at index ${_bytes.lengthInBytes}: elements of a structure cannot be anonymous");
      }
    }

    if (tag is ContextSpecificTag) {
      if (tag.tagNumber > 255) {
        throw ArgumentError(
            "Invalid context specific tag value ${tag.tagNumber} at index ${_bytes.lengthInBytes}");
      }
    }

    if (value is EndOfContainerValue) {
      if (_containerDepth == 0) {
        throw ArgumentError(
            "Cannot close container at index ${_bytes.lengthInBytes}, which is not in the open container.");
      }
      _containerDepth--;
    }

    var encodedControlAndTag = Tag.encode(encodedType, tag);
    _data.addAll(encodedControlAndTag);

    _data.addAll(value.encode());

    if (value is StructureValue || value is ArrayValue || value is ListValue) {
      if (_containerType.length == _containerDepth) {
        _containerType.add(type);
      } else {
        _containerType[_containerDepth] = type;
      }
      _containerDepth++;
    }

    return this;
  }

  TlvWriter put(Tag tag, int value) {
    return _put(Element(tag, IntValue(value)));
  }

  TlvWriter putUnsigned(Tag tag, num value) {
    return _put(Element(tag, UnsignedIntValue(value.toInt())));
  }

  TlvWriter putBool(Tag tag, bool value) {
    return _put(Element(tag, BooleanValue(value)));
  }

  TlvWriter putDouble(Tag tag, double value) {
    return _put(Element(tag, DoubleValue(value)));
  }

  TlvWriter putString(Tag tag, String value) {
    return _put(Element(tag, Utf8StringValue(value)));
  }

  TlvWriter putArray(Tag tag, Uint8List value) {
    return _put(Element(tag, ByteStringValue(value)));
  }

  TlvWriter putSignedLongArray(Tag tag, List<int> array) {
    startArray(tag);
    array.forEach((it) => put(AnonymousTag.instance, it));
    return endArray();
  }

  TlvWriter putByteStringArray(Tag tag, List<int> array) {
    startArray(tag);
    array.forEach((it) => put(AnonymousTag.instance, it));
    return endArray();
  }

  TlvWriter putNull(Tag tag) {
    return _put(Element(tag, NullValue.instance));
  }

  TlvWriter startStructure(Tag tag) {
    return _put(Element(tag, StructureValue.instance));
  }

  TlvWriter startArray(Tag tag) {
    return _put(Element(tag, ArrayValue.instance));
  }

  TlvWriter startList(Tag tag) {
    return _put(Element(tag, ListValue.instance));
  }

  TlvWriter endStructure() {
    if (_containerDepth == 0 || _containerType[_containerDepth - 1] is! StructureType) {
      throw ArgumentError(
          "Error closing structure at index ${_bytes.lengthInBytes} as currently opened container is not a structure");
    }
    return _put(Element(AnonymousTag.instance, EndOfContainerValue.instance));
  }

  TlvWriter endArray() {
    if (_containerDepth == 0 || _containerType[_containerDepth - 1] is! ArrayType) {
      throw ArgumentError(
          "Error closing array at index ${_bytes.lengthInBytes} as currently opened container is not an array");
    }
    return _put(Element(AnonymousTag.instance, EndOfContainerValue.instance));
  }

  TlvWriter endList() {
    if (_containerDepth == 0 || _containerType[_containerDepth - 1] is! ListType) {
      throw ArgumentError(
          "Error closing list at index ${_bytes.lengthInBytes} as currently opened container is not a list");
    }
    return _put(Element(AnonymousTag.instance, EndOfContainerValue.instance));
  }

  int getLengthWritten() {
    return _bytes.lengthInBytes;
  }

  TlvWriter validateTlv() {
    if (_containerDepth > 0) {
      throw Exception("Invalid Tlv data: $_containerDepth containers are not closed");
    }
    return this;
  }

  Uint8List getEncoded() {
    return _bytes.buffer.asUint8List();
  }

  void reset() {
    _bytes.clear();
    _containerDepth = 0;
    _containerType = List<Type>.filled(4, NullType());
  }
}

class TlvEncodingException implements Exception {
  final String message;
  final dynamic cause;

  TlvEncodingException(this.message, [this.cause]);

  @override
  String toString() {
    return 'TlvEncodingException: $message${cause != null ? ', cause: $cause' : ''}';
  }
}

