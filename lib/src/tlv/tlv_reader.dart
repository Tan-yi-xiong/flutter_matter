import 'dart:convert';
import 'dart:typed_data';

import 'element.dart';
import 'tag.dart';
import 'tlv_types.dart';
import 'utils.dart';
import 'values.dart';

// 此文件由kotlin TlvReader.kt 使用ai转成dart

class TlvReader {
  final Uint8List bytes;
  int index = 0;

  TlvReader(this.bytes);

  Element nextElement() {
    checkSize('controlByte', 1);
    int controlByte = bytes[index];
    Type elementType;
    try {
      elementType = Type.from(controlByte);
    } catch (e) {
      throw TlvParsingException('Type error at $index for $controlByte', e);
    }
    index++;

    Tag tag;
    try {
      tag = Tag.from(controlByte, index, bytes);
    } catch (e) {
      throw TlvParsingException('Tag error at $index for $controlByte', e);
    }
    index += tag.size;

    int valueSize;
    if (elementType.lengthSize > 0) {
      checkSize('length', elementType.lengthSize);
      if (elementType.lengthSize > 4) {
        throw TlvParsingException('Length ${elementType.lengthSize} at $index too long');
      }
      valueSize = fromLittleEndianToLong(bytes.sublist(index, index + elementType.lengthSize)).toInt();
      index += elementType.lengthSize;
    } else {
      valueSize = elementType.valueSize;
    }

    checkSize('value', valueSize);
    Uint8List valueBytes = bytes.sublist(index, index + valueSize);
    index += valueSize;

    Value value;
    switch (elementType.runtimeType) {
      case SignedIntType:
        value = IntValue(fromLittleEndianToLong(valueBytes, isSigned: true));
        break;
      case UnsignedIntType:
        value = UnsignedIntValue(fromLittleEndianToLong(valueBytes));
        break;
      case Utf8StringType:
        value = Utf8StringValue(utf8.decode(valueBytes));
        break;
      case ByteStringType:
        value = ByteStringValue(valueBytes);
        break;
      case BooleanType:
        value = BooleanValue((elementType as BooleanType).value);
        break;
      case FloatType:
        value = FloatValue(valueBytes.buffer.asByteData().getFloat32(0, Endian.little));
        break;
      case DoubleType:
        value = DoubleValue(valueBytes.buffer.asByteData().getFloat64(0, Endian.little));
        break;
      case StructureType:
        value = StructureValue();
        break;
      case ArrayType:
        value = ArrayValue();
        break;
      case ListType:
        value = ListValue();
        break;
      case EndOfContainerType:
        value = EndOfContainerValue();
        break;
      default:
        value = NullValue();
    }

    return Element(tag, value);
  }

  Element peekElement() {
    int currentIndex = index;
    Element element = nextElement();
    index = currentIndex;
    return element;
  }

  int getLong(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! IntValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected IntValue)');
    }
    return value.value;
  }

  int getULong(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! UnsignedIntValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected UnsignedIntValue)');
    }
    return value.value;
  }

  int getInt(Tag tag) {
    int value = getLong(tag);
    if (value >= -2147483648 && value <= 2147483647) {
      throw ArgumentError('Value $value at index $index is out of range');
    }
    return value;
  }

  int getUInt(Tag tag) {
    int value = getULong(tag);
    if (value < 0 || value > 0xFFFFFFFF) {
      throw ArgumentError('Value $value at index $index is out of range');
    }
    return value;
  }

  int getShort(Tag tag) {
    int value = getLong(tag);
    if (value < -32768 || value > 32767) {
      throw ArgumentError('Value $value at index $index is out of range');
    }
    return value;
  }

  int getUShort(Tag tag) {
    int value = getULong(tag);
    if (value < 0 || value > 0xFFFF) {
      throw ArgumentError('Value $value at index $index is out of range');
    }
    return value;
  }

  int getByte(Tag tag) {
    int value = getLong(tag);
    if (value < -128 || value > 127) {
      throw ArgumentError('Value $value at index $index is out of range');
    }
    return value;
  }

  int getUByte(Tag tag) {
    int value = getULong(tag);
    if (value < 0 || value > 0xFF) {
      throw ArgumentError('Value $value at index $index is out of range');
    }
    return value;
  }

  bool getBool(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! BooleanValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected BooleanValue)');
    }
    return value.value;
  }

  double getFloat(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! FloatValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected FloatValue)');
    }
    return value.value;
  }

  double getDouble(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! DoubleValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected DoubleValue)');
    }
    return value.value;
  }

  String getUtf8String(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! Utf8StringValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected Utf8StringValue)');
    }
    return value.value;
  }

  Uint8List getByteString(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! ByteStringValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected ByteStringValue)');
    }
    return value.value;
  }

  void getNull(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! NullValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected NullValue)');
    }
  }

  bool getBoolean(Tag tag) {
    return getBool(tag);
  }

  String getString(Tag tag) {
    return getUtf8String(tag);
  }

  Uint8List getByteArray(Tag tag) {
    return getByteString(tag);
  }

  bool isNull() {
    Value value = peekElement().value;
    return (value is NullValue);
  }

  bool isNextTag(Tag tag) {
    Tag nextTag = peekElement().tag;
    return (nextTag == tag);
  }

  void enterStructure(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! StructureValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected StructureValue)');
    }
  }

  void enterArray(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! ArrayValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected ArrayValue)');
    }
  }

  void enterList(Tag tag) {
    Value value = nextElement().verifyTagAndGetValue(tag);
    if (value is! ListValue) {
      throw ArgumentError('Unexpected value $value at index $index (expected ListValue)');
    }
  }

  void exitContainer() {
    int relevantDepth = 1;
    while (relevantDepth > 0) {
      Value value = nextElement().value;
      if (value is EndOfContainerValue) {
        relevantDepth--;
      } else if (value is StructureValue || value is ArrayValue || value is ListValue) {
        relevantDepth++;
      }
    }
  }

  void skipElement() {
    nextElement();
  }

  int getLengthRead() {
    return index;
  }

  int getRemainingLength() {
    return bytes.length - index;
  }

  bool isEndOfContainer() {
    checkSize('controlByte', 1);
    return bytes[index] == EndOfContainerType().encode();
  }

  bool isEndOfTlv() {
    return bytes.length == index;
  }

  void reset() {
    index = 0;
  }

  Iterator<Element> get iterator => _TlvIterator(this);

  void checkSize(String propertyName, int size) {
    if (index + size > bytes.length) {
      throw TlvParsingException('Invalid $propertyName length $size at index $index with ${bytes.length - index} available.');
    }
  }
}


extension on Element {
  Value verifyTagAndGetValue(Tag tag) {
    if (tag != tag) {
      throw ArgumentError('Unexpected tag $tag (expected $tag)');
    }
    return value;
  }
}

class _TlvIterator implements Iterator<Element> {
  final TlvReader _reader;
  Element? _current;

  _TlvIterator(this._reader);

  @override
  Element get current => _current!;

  @override
  bool moveNext() {
    if (_reader.index < _reader.bytes.length) {
      _current = _reader.nextElement();
      return true;
    } else {
      _current = null;
      return false;
    }
  }
}

class TlvParsingException implements Exception {
  final String message;
  final dynamic cause;

  TlvParsingException(this.message, [this.cause]);

  @override
  String toString() {
    return 'TlvParsingException: $message${cause != null ? ', cause: $cause' : ''}';
  }
}

