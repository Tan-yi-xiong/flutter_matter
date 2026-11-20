/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
 *    Copyright (c) 2019-2023 Google LLC.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

import 'dart:convert';
import 'dart:typed_data';

import 'element.dart';
import 'tag.dart';
import 'tlv_exception.dart';
import 'tlv_types.dart';
import 'utils.dart';
import 'values.dart';

export 'tlv_exception.dart';

/// Reads and iterates over Matter TLV elements.
///
/// The constructor copies the supplied bytes. This prevents later mutation of
/// the caller's buffer from changing a reader that is already in progress.
class TlvReader extends Iterable<Element> {
  final Uint8List bytes;
  int index = 0;

  TlvReader(Uint8List bytes) : bytes = Uint8List.fromList(bytes);

  /// Reads the next element and advances the reader.
  ///
  /// If parsing fails, the reader position is restored so callers can inspect
  /// or retry from the failed element.
  Element nextElement() {
    final startIndex = index;
    try {
      checkSize('controlByte', 1);
      final controlByte = bytes[index];

      final Type elementType;
      try {
        elementType = Type.from(controlByte);
      } catch (error) {
        throw TlvParsingException(
          'Type error at $index for ${byteToBinary(controlByte)}',
          error,
        );
      }
      index++;

      final Tag tag;
      try {
        tag = Tag.from(controlByte, index, bytes);
      } catch (error) {
        throw TlvParsingException(
          'Tag error at $index for ${byteToBinary(controlByte)}',
          error,
        );
      }
      index += tag.size;

      final int valueSize;
      final lengthSize = elementType.lengthSize;
      if (lengthSize > 0) {
        checkSize('length', lengthSize);
        if (lengthSize > 4) {
          throw TlvParsingException('Length $lengthSize at $index too long');
        }
        final decodedLength = fromLittleEndianToBigInt(
          bytes.sublist(index, index + lengthSize),
        );
        if (decodedLength > BigInt.from(bytes.length)) {
          throw TlvParsingException(
            'Invalid length $decodedLength at index $index',
          );
        }
        valueSize = decodedLength.toInt();
        index += lengthSize;
      } else {
        valueSize = elementType.valueSize;
      }

      checkSize('value', valueSize);
      final valueBytes = Uint8List.fromList(
        bytes.sublist(index, index + valueSize),
      );
      index += valueSize;

      return Element(tag, _decodeValue(elementType, valueBytes));
    } catch (error, stackTrace) {
      if (index != startIndex) {
        index = startIndex;
      }
      if (error is TlvParsingException) {
        Error.throwWithStackTrace(error, stackTrace);
      }
      throw TlvParsingException(
        'Unable to parse TLV element at $startIndex',
        error,
      );
    }
  }

  /// Reads the next element without changing the reader position.
  Element peekElement() {
    final currentIndex = index;
    try {
      return nextElement();
    } finally {
      index = currentIndex;
    }
  }

  /// Reads a signed integer and advances the reader.
  int getLong(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! IntValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected IntValue)',
      );
    }
    return value.value;
  }

  /// Reads an unsigned integer as a Dart integer.
  ///
  /// Values above `2^63 - 1` cannot be represented safely by [int] on all Dart
  /// runtimes. They raise [TlvParsingException]; use [getULongBigInt] for the
  /// full ULong range.
  int getULong(Tag tag) {
    final value = getULongBigInt(tag);
    if (value > BigInt.from(0x7fffffffffffffff)) {
      throw TlvParsingException(
        'Unsigned value $value at index $index exceeds the safe Dart int '
        'range; use getULongBigInt()',
      );
    }
    return value.toInt();
  }

  /// Reads the exact unsigned 64-bit integer representation.
  BigInt getULongBigInt(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! UnsignedIntValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index '
        '(expected UnsignedIntValue)',
      );
    }
    return value.unsignedValue;
  }

  int getInt(Tag tag) {
    return _signedRange(getLong(tag), -2147483648, 2147483647);
  }

  int getUInt(Tag tag) {
    return _unsignedRange(getULongBigInt(tag), BigInt.from(0xffffffff));
  }

  int getShort(Tag tag) {
    return _signedRange(getLong(tag), -32768, 32767);
  }

  int getUShort(Tag tag) {
    return _unsignedRange(getULongBigInt(tag), BigInt.from(0xffff));
  }

  int getByte(Tag tag) {
    return _signedRange(getLong(tag), -128, 127);
  }

  int getUByte(Tag tag) {
    return _unsignedRange(getULongBigInt(tag), BigInt.from(0xff));
  }

  bool getBool(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! BooleanValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected BooleanValue)',
      );
    }
    return value.value;
  }

  double getFloat(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! FloatValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected FloatValue)',
      );
    }
    return value.value;
  }

  double getDouble(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! DoubleValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected DoubleValue)',
      );
    }
    return value.value;
  }

  String getUtf8String(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! Utf8StringValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected Utf8StringValue)',
      );
    }
    return value.value;
  }

  Uint8List getByteString(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! ByteStringValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected ByteStringValue)',
      );
    }
    return Uint8List.fromList(value.value);
  }

  void getNull(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! NullValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected NullValue)',
      );
    }
  }

  bool getBoolean(Tag tag) => getBool(tag);

  String getString(Tag tag) => getUtf8String(tag);

  Uint8List getByteArray(Tag tag) => getByteString(tag);

  bool isNull() => peekElement().value is NullValue;

  bool isNextTag(Tag tag) => peekElement().tag == tag;

  void enterStructure(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! StructureValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected StructureValue)',
      );
    }
  }

  void enterArray(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! ArrayValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected ArrayValue)',
      );
    }
  }

  void enterList(Tag tag) {
    final value = _verifyTagAndGetValue(nextElement(), tag);
    if (value is! ListValue) {
      throw ArgumentError(
        'Unexpected value $value at index $index (expected ListValue)',
      );
    }
  }

  /// Reads through the current container, including nested containers.
  void exitContainer() {
    var relevantDepth = 1;
    while (relevantDepth > 0) {
      final value = nextElement().value;
      if (value is EndOfContainerValue) {
        relevantDepth--;
      } else if (value is StructureValue ||
          value is ArrayValue ||
          value is ListValue) {
        relevantDepth++;
      }
    }
  }

  /// Skips exactly one encoded element, matching the Kotlin reference.
  void skipElement() {
    nextElement();
  }

  int getLengthRead() => index;

  int getRemainingLength() => bytes.length - index;

  bool isEndOfContainer() {
    checkSize('controlByte', 1);
    return bytes[index] == END_OF_CONTAINER;
  }

  bool isEndOfTlv() => bytes.length == index;

  void reset() {
    index = 0;
  }

  @override
  Iterator<Element> get iterator => _TlvIterator(this);

  void checkSize(String propertyName, int size) {
    if (size < 0) {
      throw ArgumentError.value(size, 'size');
    }
    if (index < 0 || index + size > bytes.length) {
      throw TlvParsingException(
        'Invalid $propertyName length $size at index $index '
        'with ${bytes.length - index} available.',
      );
    }
  }

  Value _decodeValue(Type elementType, Uint8List valueBytes) {
    if (elementType is SignedIntType) {
      return IntValue(fromLittleEndianToLong(valueBytes, isSigned: true));
    }
    if (elementType is UnsignedIntType) {
      return UnsignedIntValue.fromBigInt(
        fromLittleEndianToBigInt(valueBytes),
      );
    }
    if (elementType is Utf8StringType) {
      try {
        return Utf8StringValue(utf8.decode(valueBytes));
      } on FormatException catch (error) {
        throw TlvParsingException(
            'Invalid UTF-8 string at index $index', error);
      }
    }
    if (elementType is ByteStringType) {
      return ByteStringValue(Uint8List.fromList(valueBytes));
    }
    if (elementType is BooleanType) {
      return BooleanValue(elementType.value);
    }
    if (elementType is FloatType) {
      return FloatValue(floatFromLittleEndianBytes(valueBytes));
    }
    if (elementType is DoubleType) {
      return DoubleValue(doubleFromLittleEndianBytes(valueBytes));
    }
    if (elementType is StructureType) {
      return StructureValue.instance;
    }
    if (elementType is ArrayType) {
      return ArrayValue.instance;
    }
    if (elementType is ListType) {
      return ListValue.instance;
    }
    if (elementType is EndOfContainerType) {
      return EndOfContainerValue.instance;
    }
    return NullValue.instance;
  }

  int _signedRange(int value, int min, int max) {
    if (value < min || value > max) {
      throw TlvParsingException(
        'Value $value at index $index is out of range $min..$max',
      );
    }
    return value;
  }

  int _unsignedRange(BigInt value, BigInt max) {
    if (value.isNegative || value > max) {
      throw TlvParsingException(
        'Value $value at index $index is out of range 0..$max',
      );
    }
    return value.toInt();
  }
}

Value _verifyTagAndGetValue(Element element, Tag expectedTag) {
  if (element.tag != expectedTag) {
    throw ArgumentError(
      'Unexpected tag ${element.tag} (expected $expectedTag)',
    );
  }
  return element.value;
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
    }
    _current = null;
    return false;
  }
}
