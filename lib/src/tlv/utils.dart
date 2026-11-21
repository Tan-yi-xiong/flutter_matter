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

import 'dart:typed_data';

/// Converts bytes in little-endian format into a Dart integer.
///
/// For an unsigned eight-byte value above `2^63 - 1`, use
/// [fromLittleEndianToBigInt] to avoid losing the high bit.
int byteArrayFromLittleEndianToInt(Uint8List bytes, {bool isSigned = false}) {
  return _fromLittleEndian(bytes, isSigned: isSigned);
}

int _fromLittleEndian(List<int> bytes, {required bool isSigned}) {
  return fromLittleEndianToLong(bytes, isSigned: isSigned);
}

/// Converts bytes in little-endian format into an exact [BigInt].
BigInt fromLittleEndianToBigInt(List<int> bytes, {bool isSigned = false}) {
  if (bytes.isEmpty) {
    return BigInt.zero;
  }

  var result = BigInt.zero;
  for (var i = 0; i < bytes.length; i++) {
    final byte = bytes[i] & 0xff;
    result |= BigInt.from(byte) << (8 * i);
  }

  if (isSigned && (bytes.last & 0x80) != 0) {
    result -= BigInt.one << (bytes.length * 8);
  }
  return result;
}

/// Converts bytes in little-endian format into a signed or unsigned integer.
int fromLittleEndianToLong(List<int> byteArray, {bool isSigned = false}) {
  final value = fromLittleEndianToBigInt(byteArray, isSigned: isSigned);
  // Preserve the original signed 64-bit two's-complement representation for
  // unsigned eight-byte inputs. BigInt.toInt() saturates on the VM, whereas the
  // original shift-based implementation produced the raw 64-bit bit pattern.
  if (!isSigned && byteArray.length == 8) {
    return value.toSigned(64).toInt();
  }
  return value.toInt();
}

/// Converts a number into a little-endian byte array.
Uint8List numberToByteArrayLittleEndian(num value, int numBytes) {
  return intToLittleEndianBytes(value.toInt(), numBytes);
}

Uint8List uByteToByteArrayLittleEndian(int value, int numBytes) {
  return intToLittleEndianBytes(value, numBytes);
}

Uint8List uShortToByteArrayLittleEndian(int value, int numBytes) {
  return intToLittleEndianBytes(value, numBytes);
}

Uint8List uIntToByteArrayLittleEndian(int value, int numBytes) {
  return intToLittleEndianBytes(value, numBytes);
}

Uint8List uLongToByteArrayLittleEndian(int value, int numBytes) {
  return intToLittleEndianBytes(value, numBytes);
}

/// Converts an integer to exactly [numBytes] little-endian bytes.
Uint8List intToLittleEndianBytes(int value, int numBytes) {
  if (numBytes < 0) {
    throw ArgumentError.value(numBytes, 'numBytes');
  }
  final bytes = Uint8List(numBytes);
  for (var i = 0; i < numBytes; i++) {
    bytes[i] = (value >> (8 * i)) & 0xff;
  }
  return bytes;
}

/// Converts an unsigned [BigInt] to exactly [numBytes] little-endian bytes.
Uint8List bigIntToLittleEndianBytes(BigInt value, int numBytes) {
  if (numBytes < 0) {
    throw ArgumentError.value(numBytes, 'numBytes');
  }
  if (value.isNegative) {
    throw ArgumentError.value(value, 'value', 'must not be negative');
  }
  if (numBytes < 8 && value > (BigInt.one << (numBytes * 8)) - BigInt.one) {
    throw ArgumentError.value(
        value, 'value', 'does not fit in $numBytes bytes');
  }
  if (numBytes == 8 && value > ((BigInt.one << 64) - BigInt.one)) {
    throw ArgumentError.value(value, 'value', 'does not fit in 8 bytes');
  }

  final bytes = Uint8List(numBytes);
  var remaining = value;
  for (var i = 0; i < numBytes; i++) {
    bytes[i] = (remaining & BigInt.from(0xff)).toInt();
    remaining >>= 8;
  }
  return bytes;
}

int signedIntSize(int value) {
  if (value >= -128 && value <= 127) {
    return 1;
  } else if (value >= -32768 && value <= 32767) {
    return 2;
  } else if (value >= -2147483648 && value <= 2147483647) {
    return 4;
  } else {
    return 8;
  }
}

/// Returns the minimum unsigned width for a non-negative Dart integer.
int unsignedIntSize(int value) {
  if (value < 0) {
    throw ArgumentError.value(value, 'value', 'must not be negative');
  }
  if (value <= 255) {
    return 1;
  } else if (value <= 65535) {
    return 2;
  } else if (value <= 4294967295) {
    return 4;
  } else {
    return 8;
  }
}

/// Returns the minimum unsigned width for a [BigInt] ULong value.
int unsignedBigIntSize(BigInt value) {
  if (value.isNegative || value > ((BigInt.one << 64) - BigInt.one)) {
    throw ArgumentError.value(
        value, 'value', 'must fit in an unsigned 64-bit value');
  }
  if (value <= BigInt.from(0xff)) {
    return 1;
  } else if (value <= BigInt.from(0xffff)) {
    return 2;
  } else if (value <= BigInt.from(0xffffffff)) {
    return 4;
  } else {
    return 8;
  }
}

String byteToBinary(int byte) {
  return (byte & 0xff).toRadixString(2).padLeft(8, '0');
}

extension IntExt on int {
  Uint8List toByteArrayLittleEndian(int size) {
    return intToLittleEndianBytes(this, size);
  }
}

extension DoubleExt on double {
  /// Returns the IEEE-754 binary64 bit pattern as a Dart int.
  int toIntBits() {
    return toLongBits();
  }

  /// Returns the IEEE-754 binary64 bit pattern as a Dart int.
  int toLongBits() {
    final buffer = ByteData(8);
    buffer.setFloat64(0, this, Endian.little);
    return buffer.getUint64(0, Endian.little).toInt();
  }
}

/// Encodes a Dart double as an IEEE-754 binary32 value.
Uint8List floatToLittleEndianBytes(double value) {
  final buffer = ByteData(4);
  buffer.setFloat32(0, value, Endian.little);
  return Uint8List.fromList(buffer.buffer.asUint8List());
}

/// Decodes an IEEE-754 binary32 value from exactly four bytes.
double floatFromLittleEndianBytes(Uint8List bytes) {
  if (bytes.length != 4) {
    throw ArgumentError.value(bytes.length, 'bytes.length', 'must be 4');
  }
  return ByteData.sublistView(bytes).getFloat32(0, Endian.little);
}

/// Encodes a Dart double as an IEEE-754 binary64 value.
Uint8List doubleToLittleEndianBytes(double value) {
  final buffer = ByteData(8);
  buffer.setFloat64(0, value, Endian.little);
  return Uint8List.fromList(buffer.buffer.asUint8List());
}

/// Decodes an IEEE-754 binary64 value from exactly eight bytes.
double doubleFromLittleEndianBytes(Uint8List bytes) {
  if (bytes.length != 8) {
    throw ArgumentError.value(bytes.length, 'bytes.length', 'must be 8');
  }
  return ByteData.sublistView(bytes).getFloat64(0, Endian.little);
}
