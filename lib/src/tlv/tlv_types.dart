import 'dart:typed_data';

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

// 此文件由kotlin types.kt 使用ai转成dart

abstract class Type {
  final int lengthSize;
  final int valueSize;

  Type(this.lengthSize, this.valueSize);

  int encode();

  factory Type.from(int controlByte) {
    int modifiedControlByte = (controlByte & MODIFIED_TYPE_MASK);
    if (!(modifiedControlByte == SIGNED_INT_TYPE ||
        modifiedControlByte == UNSIGNED_INT_TYPE ||
        modifiedControlByte == UTF8_STRING_TYPE ||
        modifiedControlByte == BYTE_STRING_TYPE)) {
      modifiedControlByte = controlByte;
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
        throw StateError("Unexpected control byte ${modifiedControlByte.toRadixString(2)}");
    }
  }

  static int extractSize(int byte) {
    switch (byte & int.parse('011', radix: 2)) {
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

int encodeSize(int size) {
  switch (size) {
    case 1:
      return int.parse('000', radix: 2);
    case 2:
      return int.parse('001', radix: 2);
    case 4:
      return int.parse('010', radix: 2);
    case 8:
      return int.parse('011', radix: 2);
    default:
      throw StateError("Unexpected size $size");
  }
}

class SignedIntType extends Type {
  SignedIntType(int valueSize) : super(0, valueSize);

  @override
  int encode() => SIGNED_INT_TYPE | encodeSize(valueSize);
}

class UnsignedIntType extends Type {
  UnsignedIntType(int valueSize) : super(0, valueSize);

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
  Utf8StringType(int lengthSize) : super(lengthSize, 0);

  @override
  int encode() => UTF8_STRING_TYPE | encodeSize(lengthSize);
}

class ByteStringType extends Type {
  ByteStringType(int lengthSize) : super(lengthSize, 0);

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

