import 'dart:typed_data';

// 此文件由kotlin tags.kt 使用ai转成dart

const TAG_MASK = 224;
const ANONYMOUS = 0;
const CONTEXT_SPECIFIC = 32;
const COMMON_PROFILE_2 = 64;
const COMMON_PROFILE_4 = 96;
const IMPLICIT_PROFILE_2 = 128;
const IMPLICIT_PROFILE_4 = 160;
const FULLY_QUALIFIED_6 = 192;
const FULLY_QUALIFIED_8 = 224;

abstract class Tag {
  int get size;

  static Tag from(int controlByte, int startIndex, Uint8List bytes) {
    switch (controlByte & TAG_MASK) {
      case ANONYMOUS:
        return AnonymousTag();
      case CONTEXT_SPECIFIC:
        return ContextSpecificTag(checkBytes(startIndex, 1, bytes)[0].toInt());
      case COMMON_PROFILE_2:
        return CommonProfileTag(
          2,
          bytes.buffer.asByteData(startIndex, 2).getUint32(0, Endian.little),
        );
      case COMMON_PROFILE_4:
        return CommonProfileTag(
          4,
          bytes.buffer.asByteData(startIndex, 4).getUint32(0, Endian.little),
        );
      case IMPLICIT_PROFILE_2:
        return ImplicitProfileTag(
          2,
          bytes.buffer.asByteData(startIndex, 2).getUint32(0, Endian.little),
        );
      case IMPLICIT_PROFILE_4:
        return ImplicitProfileTag(
          4,
          bytes.buffer.asByteData(startIndex, 4).getUint32(0, Endian.little),
        );
      case FULLY_QUALIFIED_6:
        return FullyQualifiedTag(
          6,
          bytes.buffer.asByteData(startIndex, 2).getUint16(0, Endian.little),
          bytes.buffer.asByteData(startIndex + 2, 2).getUint16(0, Endian.little),
          bytes.buffer.asByteData(startIndex + 4, 2).getUint32(0, Endian.little),
        );
      case FULLY_QUALIFIED_8:
        return FullyQualifiedTag(
          8,
          bytes.buffer.asByteData(startIndex, 2).getUint16(0, Endian.little),
          bytes.buffer.asByteData(startIndex + 2, 2).getUint16(0, Endian.little),
          bytes.buffer.asByteData(startIndex + 4, 4).getUint32(0, Endian.little),
        );
      default:
        throw ArgumentError('Invalid control byte $controlByte');
    }
  }

  static Uint8List encode(int encodedType, Tag tag) {
    int controlByte = encodedType |
        (tag is AnonymousTag
            ? ANONYMOUS
            : tag is ContextSpecificTag
                ? CONTEXT_SPECIFIC
                : tag is CommonProfileTag
                    ? (tag.size == 2 ? COMMON_PROFILE_2 : COMMON_PROFILE_4)
                    : tag is ImplicitProfileTag
                        ? (tag.size == 2 ? IMPLICIT_PROFILE_2 : IMPLICIT_PROFILE_4)
                        : tag is FullyQualifiedTag
                            ? (tag.size == 6 ? FULLY_QUALIFIED_6 : FULLY_QUALIFIED_8)
                            : 0);

    Uint8List encodedTag = tag is AnonymousTag
        ? Uint8List(0)
        : tag is ContextSpecificTag
            ? Uint8List.fromList([tag.tagNumber])
            : tag is CommonProfileTag
                ? _toByteArrayLittleEndian(tag.tagNumber, tag.size)
                : tag is ImplicitProfileTag
                    ? _toByteArrayLittleEndian(tag.tagNumber, tag.size)
                    : tag is FullyQualifiedTag
                        ? Uint8List.fromList([
                            ..._toByteArrayLittleEndian(tag.vendorId.toInt(), 2),
                            ..._toByteArrayLittleEndian(tag.profileNumber.toInt(), 2),
                            ..._toByteArrayLittleEndian(tag.tagNumber, tag.size - 4)
                          ])
                        : Uint8List(0);

    return Uint8List.fromList([controlByte, ...encodedTag]);
  }

  static Uint8List checkBytes(int startIndex, int expectedBytes, Uint8List actualBytes) {
    int remaining = actualBytes.length - startIndex;
    if (expectedBytes > remaining) {
      throw StateError(
          'Invalid tag: Expected $expectedBytes but only $remaining bytes available at $startIndex');
    }
    return actualBytes.sublist(startIndex, startIndex + expectedBytes);
  }

  static Uint8List _toByteArrayLittleEndian(int value, int size) {
    ByteData byteData = ByteData(size);
    byteData.setUint32(0, value, Endian.little);
    return byteData.buffer.asUint8List();
  }
}

class AnonymousTag implements Tag {
  @override
  int get size => 0;

  static AnonymousTag? _instance;

  static get instance => _instance ??= AnonymousTag();
}

class ContextSpecificTag implements Tag {
  final int tagNumber;

  ContextSpecificTag(this.tagNumber);

  @override
  int get size => 1;
}

class CommonProfileTag implements Tag {
  @override
  final int size;
  final int tagNumber;

  CommonProfileTag(this.size, this.tagNumber);
}

class ImplicitProfileTag implements Tag {
  @override
  final int size;
  final int tagNumber;

  ImplicitProfileTag(this.size, this.tagNumber);
}

class FullyQualifiedTag implements Tag {
  @override
  final int size;
  final int vendorId;
  final int profileNumber;
  final int tagNumber;

  FullyQualifiedTag(this.size, this.vendorId, this.profileNumber, this.tagNumber);
}

