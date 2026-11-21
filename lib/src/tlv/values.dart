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

import 'tlv_types.dart';
import 'utils.dart';

/// Base class for a decoded or to-be-encoded TLV value.
abstract class Value {
  Type toType();
  Uint8List encode();
  dynamic toAny();
}

/// A signed integer value.
class IntValue extends Value {
  final int value;

  IntValue(this.value);

  @override
  Type toType() => SignedIntType(signedIntSize(value));

  @override
  Uint8List encode() => intToLittleEndianBytes(value, toType().valueSize);

  @override
  dynamic toAny() => value;

  @override
  bool operator ==(Object other) => other is IntValue && other.value == value;

  @override
  int get hashCode => Object.hash(IntValue, value);

  @override
  String toString() => 'IntValue($value)';
}

/// An unsigned integer value.
///
/// [value] is retained as the signed Dart representation used by the original
/// API. For values above `2^63 - 1`, that representation is the two's
/// complement bit pattern and callers should use [unsignedValue] or
/// `TlvReader.getULongBigInt` when the exact unsigned value is required.
class UnsignedIntValue extends Value {
  final int value;
  final BigInt _unsignedValue;

  UnsignedIntValue(int value)
      : value = _rawSignedInt64(value),
        _unsignedValue = _toUnsigned64(BigInt.from(value));

  UnsignedIntValue._(this.value, this._unsignedValue);

  /// Creates a value from an exact unsigned 64-bit integer.
  factory UnsignedIntValue.fromBigInt(BigInt unsignedValue) {
    if (unsignedValue.isNegative ||
        unsignedValue > ((BigInt.one << 64) - BigInt.one)) {
      throw ArgumentError.value(
        unsignedValue,
        'unsignedValue',
        'must fit in an unsigned 64-bit integer',
      );
    }
    return UnsignedIntValue._(
      _rawSignedInt64FromBig(unsignedValue),
      unsignedValue,
    );
  }

  /// Exact unsigned value, including the range above `2^63 - 1`.
  BigInt get unsignedValue => _unsignedValue;

  @override
  Type toType() => UnsignedIntType(unsignedBigIntSize(_unsignedValue));

  @override
  Uint8List encode() =>
      bigIntToLittleEndianBytes(_unsignedValue, toType().valueSize);

  @override
  dynamic toAny() => value;

  @override
  bool operator ==(Object other) =>
      other is UnsignedIntValue && other.unsignedValue == unsignedValue;

  @override
  int get hashCode => Object.hash(UnsignedIntValue, unsignedValue);

  @override
  String toString() => 'UnsignedIntValue($unsignedValue)';
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

  @override
  bool operator ==(Object other) =>
      other is BooleanValue && other.value == value;

  @override
  int get hashCode => Object.hash(BooleanValue, value);

  @override
  String toString() => 'BooleanValue($value)';
}

/// A single-precision floating-point value.
class FloatValue extends Value {
  final double value;

  FloatValue(this.value);

  @override
  Type toType() => FloatType();

  @override
  Uint8List encode() => floatToLittleEndianBytes(value);

  @override
  dynamic toAny() => value;

  @override
  bool operator ==(Object other) => other is FloatValue && other.value == value;

  @override
  int get hashCode => Object.hash(FloatValue, value);

  @override
  String toString() => 'FloatValue($value)';
}

/// A double-precision floating-point value.
class DoubleValue extends Value {
  final double value;

  DoubleValue(this.value);

  @override
  Type toType() => DoubleType();

  @override
  Uint8List encode() => doubleToLittleEndianBytes(value);

  @override
  dynamic toAny() => value;

  @override
  bool operator ==(Object other) =>
      other is DoubleValue && other.value == value;

  @override
  int get hashCode => Object.hash(DoubleValue, value);

  @override
  String toString() => 'DoubleValue($value)';
}

/// A UTF-8 string value.
class Utf8StringValue extends Value {
  final String value;

  Utf8StringValue(this.value);

  @override
  Type toType() => Utf8StringType(unsignedIntSize(utf8.encode(value).length));

  @override
  Uint8List encode() {
    final encoded = utf8.encode(value);
    return Uint8List.fromList(<int>[
      ...intToLittleEndianBytes(encoded.length, toType().lengthSize),
      ...encoded,
    ]);
  }

  @override
  dynamic toAny() => value;

  @override
  bool operator ==(Object other) =>
      other is Utf8StringValue && other.value == value;

  @override
  int get hashCode => Object.hash(Utf8StringValue, value);

  @override
  String toString() => 'Utf8StringValue($value)';
}

/// An octet string value.
class ByteStringValue extends Value {
  final Uint8List value;

  ByteStringValue(this.value);

  @override
  Type toType() => ByteStringType(unsignedIntSize(value.length));

  @override
  Uint8List encode() {
    final encoded = Uint8List.fromList(value);
    return Uint8List.fromList(<int>[
      ...intToLittleEndianBytes(encoded.length, toType().lengthSize),
      ...encoded,
    ]);
  }

  @override
  dynamic toAny() => value;

  @override
  bool operator ==(Object other) =>
      other is ByteStringValue && _bytesEqual(other.value, value);

  @override
  int get hashCode => Object.hash(ByteStringValue, Object.hashAll(value));

  @override
  String toString() => 'ByteStringValue($value)';
}

class NullValue extends Value {
  @override
  Type toType() => NullType();

  @override
  Uint8List encode() => Uint8List(0);

  @override
  dynamic toAny() => null;

  @override
  bool operator ==(Object other) => other is NullValue;

  @override
  int get hashCode => 20;

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

  @override
  bool operator ==(Object other) => other is StructureValue;

  @override
  int get hashCode => 21;

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

  @override
  bool operator ==(Object other) => other is ArrayValue;

  @override
  int get hashCode => 22;

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

  @override
  bool operator ==(Object other) => other is ListValue;

  @override
  int get hashCode => 23;

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

  @override
  bool operator ==(Object other) => other is EndOfContainerValue;

  @override
  int get hashCode => 24;

  static EndOfContainerValue? _instance;

  static EndOfContainerValue get instance =>
      _instance ??= EndOfContainerValue();
}

int _rawSignedInt64(int value) => _rawSignedInt64FromBig(BigInt.from(value));

int _rawSignedInt64FromBig(BigInt value) => value.toSigned(64).toInt();

BigInt _toUnsigned64(BigInt value) {
  if (value.isNegative) {
    return value & ((BigInt.one << 64) - BigInt.one);
  }
  return value;
}

bool _bytesEqual(List<int> a, List<int> b) {
  if (a.length != b.length) return false;
  for (var i = 0; i < a.length; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}
