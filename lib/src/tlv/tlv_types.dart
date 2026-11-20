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

import 'utils.dart';

const MODIFIED_TYPE_MASK = 28;
const ELEMENT_TYPE_MASK = 31;
const SIGNED_INT_TYPE = 0;
const UNSIGNED_INT_TYPE = 4;
const UTF8_STRING_TYPE = 12;
const BYTE_STRING_TYPE = 16;
const BOOLEAN_FALSE = 8;
const BOOLEAN_TRUE = 9;
const FLOATING_POINT_4 = 10;
const FLOATING_POINT_8 = 11;
const NULL = 20;
const STRUCTURE = 21;
const ARRAY = 22;
const LIST = 23;
const END_OF_CONTAINER = 24;

/// Describes the type and encoded value/length width of a TLV element.
abstract class Type {
  final int lengthSize;
  final int valueSize;

  Type(this.lengthSize, this.valueSize);

  /// Returns the value-type bits without any tag bits.
  int encode();

  factory Type.from(int controlByte) {
    if (controlByte < 0 || controlByte > 0xff) {
      throw ArgumentError.value(controlByte, 'controlByte');
    }

    var modifiedControlByte = controlByte & MODIFIED_TYPE_MASK;
    if (modifiedControlByte != SIGNED_INT_TYPE &&
        modifiedControlByte != UNSIGNED_INT_TYPE &&
        modifiedControlByte != UTF8_STRING_TYPE &&
        modifiedControlByte != BYTE_STRING_TYPE) {
      modifiedControlByte = controlByte & ELEMENT_TYPE_MASK;
    }

    switch (modifiedControlByte) {
      case SIGNED_INT_TYPE:
        return SignedIntType(extractSize(controlByte));
      case UNSIGNED_INT_TYPE:
        return UnsignedIntType(extractSize(controlByte));
      case UTF8_STRING_TYPE:
        return Utf8StringType(extractSize(controlByte));
      case BYTE_STRING_TYPE:
        return ByteStringType(extractSize(controlByte));
      case BOOLEAN_FALSE:
        return BooleanType(false);
      case BOOLEAN_TRUE:
        return BooleanType(true);
      case FLOATING_POINT_4:
        return FloatType();
      case FLOATING_POINT_8:
        return DoubleType();
      case NULL:
        return NullType();
      case STRUCTURE:
        return StructureType();
      case ARRAY:
        return ArrayType();
      case LIST:
        return ListType();
      case END_OF_CONTAINER:
        return EndOfContainerType();
      default:
        throw FormatException(
          'Unexpected control byte '
          '${byteToBinary(controlByte)}',
        );
    }
  }

  /// Extracts the little-endian length/value width encoded by the low bits.
  static int extractSize(int byte) {
    switch (byte & 0x3) {
      case 0:
        return 1;
      case 1:
        return 2;
      case 2:
        return 4;
      default:
        return 8;
    }
  }
}

/// Converts a supported 1/2/4/8-byte width into its two-bit encoding.
int encodeSize(int size) {
  switch (size) {
    case 1:
      return 0;
    case 2:
      return 1;
    case 4:
      return 2;
    case 8:
      return 3;
    default:
      throw ArgumentError.value(size, 'size', 'must be 1, 2, 4 or 8');
  }
}

class SignedIntType extends Type {
  SignedIntType(int valueSize) : super(0, _validateFixedSize(valueSize));

  @override
  int encode() => SIGNED_INT_TYPE | encodeSize(valueSize);
}

class UnsignedIntType extends Type {
  UnsignedIntType(int valueSize) : super(0, _validateFixedSize(valueSize));

  @override
  int encode() => UNSIGNED_INT_TYPE | encodeSize(valueSize);
}

class BooleanType extends Type {
  final bool value;

  BooleanType(this.value) : super(0, 0);

  @override
  int encode() => value ? BOOLEAN_TRUE : BOOLEAN_FALSE;
}

class FloatType extends Type {
  FloatType() : super(0, 4);

  @override
  int encode() => FLOATING_POINT_4;
}

class DoubleType extends Type {
  DoubleType() : super(0, 8);

  @override
  int encode() => FLOATING_POINT_8;
}

class Utf8StringType extends Type {
  Utf8StringType(int lengthSize) : super(_validateLengthSize(lengthSize), 0);

  @override
  int encode() => UTF8_STRING_TYPE | encodeSize(lengthSize);
}

class ByteStringType extends Type {
  ByteStringType(int lengthSize) : super(_validateLengthSize(lengthSize), 0);

  @override
  int encode() => BYTE_STRING_TYPE | encodeSize(lengthSize);
}

class NullType extends Type {
  NullType() : super(0, 0);

  @override
  int encode() => NULL;
}

class StructureType extends Type {
  StructureType() : super(0, 0);

  @override
  int encode() => STRUCTURE;
}

class ArrayType extends Type {
  ArrayType() : super(0, 0);

  @override
  int encode() => ARRAY;
}

class ListType extends Type {
  ListType() : super(0, 0);

  @override
  int encode() => LIST;
}

class EndOfContainerType extends Type {
  EndOfContainerType() : super(0, 0);

  @override
  int encode() => END_OF_CONTAINER;
}

int _validateFixedSize(int size) {
  if (size != 1 && size != 2 && size != 4 && size != 8) {
    throw ArgumentError.value(size, 'size', 'must be 1, 2, 4 or 8');
  }
  return size;
}

int _validateLengthSize(int size) {
  if (size != 1 && size != 2 && size != 4 && size != 8) {
    throw ArgumentError.value(size, 'size', 'must be 1, 2, 4 or 8');
  }
  return size;
}
