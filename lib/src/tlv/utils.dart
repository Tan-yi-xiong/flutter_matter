import 'dart:typed_data';

/// Converts bytes in a Little Endian format into Long integer.
int byteArrayFromLittleEndianToInt(Uint8List bytes, {bool isSigned = false}) {
  int result = 0;
  for (int i = bytes.length - 1; i >= 0; i--) {
    result = (result << 8) | (isSigned && i == bytes.length - 1 ? bytes[i] : bytes[i] & 0xFF);
  }
  return result;
}

/// Converts Number into a byte array in a Little Endian format.
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

Uint8List intToLittleEndianBytes(int value, int numBytes) {
  Uint8List bytes = Uint8List(numBytes);
  for (int i = 0; i < numBytes; i++) {
    bytes[i] = (value >> (8 * i)) & 0xFF;
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

int unsignedIntSize(int value) {
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

String byteToBinary(int byte) {
  return byte.toRadixString(2).padLeft(8, '0');
}

extension IntExt on int {
  Uint8List toByteArrayLittleEndian(int size) {
    final bytes = Uint8List(size);
    for (int i = 0; i < size; i++) {
      bytes[i] = (this >> (i * 8)) & 0xFF;
    }
    return bytes;
  }
}

extension DoubleExt on double {
  int toIntBits() {
    final buffer = ByteData(8);
    buffer.setFloat64(0, this, Endian.little);
    return buffer.getUint64(0, Endian.little).toInt();
  }

  int toLongBits() {
    final buffer = ByteData(8);
    buffer.setFloat64(0, this, Endian.little);
    return buffer.getUint64(0, Endian.little).toInt();
  }
}

int fromLittleEndianToLong(List<int> byteArray, {bool isSigned = false}) {
  int result = 0;

  for (int i = byteArray.length - 1; i >= 0; i--) {
    int value = byteArray[i];
    result = (result << 8) |
        ((i == byteArray.length - 1 && isSigned) ? value : (value & 0xFF));
  }

  return result;
}