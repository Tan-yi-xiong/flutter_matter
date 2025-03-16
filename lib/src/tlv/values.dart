import 'dart:typed_data';

import 'tlv_types.dart';
import 'utils.dart';

abstract class Value {
  Type toType();
  Uint8List encode();
  dynamic toAny();
}

class IntValue extends Value {
  final int value;

  IntValue(this.value);

  @override
  Type toType() => SignedIntType(signedIntSize(value));

  @override
  Uint8List encode() => value.toByteArrayLittleEndian(toType().valueSize);

  @override
  dynamic toAny() => value;
}

class UnsignedIntValue extends Value {
  final int value;

  UnsignedIntValue(this.value);

  @override
  Type toType() => UnsignedIntType(unsignedIntSize(value));

  @override
  Uint8List encode() => value.toByteArrayLittleEndian(toType().valueSize);

  @override
  dynamic toAny() => value;

}

class BooleanValue extends Value {
  final bool value;

  BooleanValue(this.value);

  @override
  Type toType() => BooleanType(value);

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => value;

}

class FloatValue extends Value {
  final double value;

  FloatValue(this.value);

  @override
  Type toType() => FloatType();

  @override
  Uint8List encode() => value.toIntBits().toByteArrayLittleEndian(4);

  @override
  dynamic toAny() => value;

}

class DoubleValue extends Value {
  final double value;

  DoubleValue(this.value);

  @override
  Type toType() => DoubleType();

  @override
  Uint8List encode() => value.toLongBits().toByteArrayLittleEndian(8);

  @override
  dynamic toAny() => value;

}

class Utf8StringValue extends Value {
  final String value;

  Utf8StringValue(this.value);

  @override
  Type toType() => Utf8StringType(unsignedIntSize(value.codeUnits.length));

  @override
  Uint8List encode() {
    final bytes = value.codeUnits;
    return Uint8List.fromList(bytes.length.toByteArrayLittleEndian(toType().lengthSize) + Uint8List.fromList(bytes));
  }

  @override
  dynamic toAny() => value;
}

class ByteStringValue extends Value {
  final Uint8List value;

  ByteStringValue(this.value);

  @override
  Type toType() => ByteStringType(unsignedIntSize(value.length));

  @override
  Uint8List encode() => Uint8List.fromList(value.length.toByteArrayLittleEndian(toType().lengthSize) + value);

  @override
  dynamic toAny() => value;

}

class NullValue extends Value {
  @override
  Type toType() => NullType();

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => null;

  static NullValue? _instance;

  static NullValue get instance => _instance ??= NullValue();
}

class StructureValue extends Value {
  @override
  Type toType() => StructureType();

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => null;

  static StructureValue? _instance;

  static StructureValue get instance => _instance ??= StructureValue();
}

class ArrayValue extends Value {
  @override
  Type toType() => ArrayType();

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => null;

  static ArrayValue? _instance;

  static ArrayValue get instance => _instance ??= ArrayValue();
}

class ListValue extends Value {
  @override
  Type toType() => ListType();

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => null;

  static ListValue? _instance;

  static ListValue get instance => _instance ??= ListValue();
}

class EndOfContainerValue extends Value {
  @override
  Type toType() => EndOfContainerType();

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => null;

  static EndOfContainerValue? _instance;

  static EndOfContainerValue get instance => _instance ??= EndOfContainerValue();
}
