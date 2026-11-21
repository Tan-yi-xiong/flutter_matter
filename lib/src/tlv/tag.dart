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

const TAG_MASK = 224;
const ANONYMOUS = 0;
const CONTEXT_SPECIFIC = 32;
const COMMON_PROFILE_2 = 64;
const COMMON_PROFILE_4 = 96;
const IMPLICIT_PROFILE_2 = 128;
const IMPLICIT_PROFILE_4 = 160;
const FULLY_QUALIFIED_6 = 192;
const FULLY_QUALIFIED_8 = 224;

/// A Matter TLV tag.
///
/// The tag classes are kept public for compatibility with the original Dart
/// port. New code should normally use [AnonymousTag.instance] or one of the
/// concrete tag constructors.
abstract class Tag {
  /// Number of bytes following the TLV control byte.
  int get size;

  /// Parses a tag from the bytes immediately following a TLV control byte.
  ///
  /// [startIndex] is relative to [bytes] and must be non-negative. Any invalid
  /// or truncated tag data is rejected rather than being interpreted as an
  /// anonymous tag.
  static Tag from(int controlByte, int startIndex, Uint8List bytes) {
    if (controlByte < 0 || controlByte > 0xff) {
      throw ArgumentError.value(controlByte, 'controlByte');
    }
    if (startIndex < 0 || startIndex > bytes.length) {
      throw ArgumentError.value(startIndex, 'startIndex');
    }

    switch (controlByte & TAG_MASK) {
      case ANONYMOUS:
        return AnonymousTag.instance;
      case CONTEXT_SPECIFIC:
        return ContextSpecificTag(_readUnsigned(bytes, startIndex, 1));
      case COMMON_PROFILE_2:
        return CommonProfileTag(
          2,
          _readUnsigned(bytes, startIndex, 2),
        );
      case COMMON_PROFILE_4:
        return CommonProfileTag(
          4,
          _readUnsigned(bytes, startIndex, 4),
        );
      case IMPLICIT_PROFILE_2:
        return ImplicitProfileTag(
          2,
          _readUnsigned(bytes, startIndex, 2),
        );
      case IMPLICIT_PROFILE_4:
        return ImplicitProfileTag(
          4,
          _readUnsigned(bytes, startIndex, 4),
        );
      case FULLY_QUALIFIED_6:
        return FullyQualifiedTag(
          6,
          _readUnsigned(bytes, startIndex, 2),
          _readUnsigned(bytes, startIndex + 2, 2),
          _readUnsigned(bytes, startIndex + 4, 2),
        );
      case FULLY_QUALIFIED_8:
        return FullyQualifiedTag(
          8,
          _readUnsigned(bytes, startIndex, 2),
          _readUnsigned(bytes, startIndex + 2, 2),
          _readUnsigned(bytes, startIndex + 4, 4),
        );
      default:
        // The mask is exhaustive, so this is only reachable if the constants
        // above are changed incorrectly. Fail closed instead of emitting an
        // anonymous tag.
        throw ArgumentError('Invalid control byte $controlByte');
    }
  }

  /// Encodes the control byte and tag data for [tag].
  ///
  /// [encodedType] contains the value type bits and must not contain tag bits.
  /// Unknown [Tag] subclasses are rejected; otherwise they would silently be
  /// encoded as an anonymous tag by the original implementation.
  static Uint8List encode(int encodedType, Tag tag) {
    if (encodedType < 0 || encodedType > 0xff) {
      throw ArgumentError.value(encodedType, 'encodedType');
    }

    final int tagBits;
    final Uint8List encodedTag;
    if (tag is AnonymousTag) {
      tagBits = ANONYMOUS;
      encodedTag = Uint8List(0);
    } else if (tag is ContextSpecificTag) {
      _checkRange(tag.tagNumber, 0, 0xff, 'tagNumber');
      tagBits = CONTEXT_SPECIFIC;
      encodedTag = Uint8List.fromList(<int>[tag.tagNumber]);
    } else if (tag is CommonProfileTag) {
      _checkProfileTagNumber(tag.size, tag.tagNumber);
      tagBits = tag.size == 2 ? COMMON_PROFILE_2 : COMMON_PROFILE_4;
      encodedTag = _toByteArrayLittleEndian(tag.tagNumber, tag.size);
    } else if (tag is ImplicitProfileTag) {
      _checkProfileTagNumber(tag.size, tag.tagNumber);
      tagBits = tag.size == 2 ? IMPLICIT_PROFILE_2 : IMPLICIT_PROFILE_4;
      encodedTag = _toByteArrayLittleEndian(tag.tagNumber, tag.size);
    } else if (tag is FullyQualifiedTag) {
      if (tag.size != 6 && tag.size != 8) {
        throw ArgumentError.value(tag.size, 'tag.size', 'must be 6 or 8');
      }
      _checkRange(tag.vendorId, 0, 0xffff, 'vendorId');
      _checkRange(tag.profileNumber, 0, 0xffff, 'profileNumber');
      _checkRange(tag.tagNumber, 0, _maxForWidth(tag.size - 4), 'tagNumber');
      tagBits = tag.size == 6 ? FULLY_QUALIFIED_6 : FULLY_QUALIFIED_8;
      encodedTag = Uint8List.fromList(<int>[
        ..._toByteArrayLittleEndian(tag.vendorId, 2),
        ..._toByteArrayLittleEndian(tag.profileNumber, 2),
        ..._toByteArrayLittleEndian(tag.tagNumber, tag.size - 4),
      ]);
    } else {
      throw ArgumentError.value(
        tag,
        'tag',
        'Unsupported Tag implementation ${tag.runtimeType}',
      );
    }

    return Uint8List.fromList(<int>[encodedType | tagBits, ...encodedTag]);
  }

  /// Checks that [actualBytes] contains [expectedBytes] bytes at [startIndex].
  ///
  /// This method is public for compatibility with the original port. It copies
  /// the returned range and therefore works correctly with `Uint8List` views.
  static Uint8List checkBytes(
    int startIndex,
    int expectedBytes,
    Uint8List actualBytes,
  ) {
    if (expectedBytes < 0) {
      throw ArgumentError.value(expectedBytes, 'expectedBytes');
    }
    if (startIndex < 0 || startIndex > actualBytes.length) {
      throw ArgumentError.value(startIndex, 'startIndex');
    }
    final remaining = actualBytes.length - startIndex;
    if (expectedBytes > remaining) {
      throw ArgumentError(
        'Invalid tag: Expected $expectedBytes but only $remaining bytes '
        'available at $startIndex',
      );
    }
    return Uint8List.fromList(
      actualBytes.sublist(startIndex, startIndex + expectedBytes),
    );
  }

  static Uint8List _toByteArrayLittleEndian(int value, int size) {
    if (size <= 0 || size > 8) {
      throw ArgumentError.value(size, 'size', 'must be between 1 and 8');
    }
    if (value < 0 || value > _maxForWidth(size)) {
      throw ArgumentError.value(value, 'value', 'does not fit in $size bytes');
    }
    final result = Uint8List(size);
    var remaining = value;
    for (var i = 0; i < size; i++) {
      result[i] = remaining & 0xff;
      remaining >>= 8;
    }
    return result;
  }

  static int _readUnsigned(Uint8List bytes, int startIndex, int size) {
    final checked = checkBytes(startIndex, size, bytes);
    var result = 0;
    for (var i = 0; i < checked.length; i++) {
      result |= checked[i] << (8 * i);
    }
    return result;
  }

  static int _maxForWidth(int size) {
    if (size < 1 || size > 8) {
      throw ArgumentError.value(size, 'size');
    }
    if (size == 8) {
      // Tags in the supported Matter tag forms are at most four bytes for a
      // tag number. Keep this helper general but avoid an oversized shift on
      // platforms with bounded integers.
      return 0x7fffffffffffffff;
    }
    return (1 << (size * 8)) - 1;
  }

  static void _checkProfileTagNumber(int size, int tagNumber) {
    if (size != 2 && size != 4) {
      throw ArgumentError.value(size, 'size', 'must be 2 or 4');
    }
    _checkRange(tagNumber, 0, _maxForWidth(size), 'tagNumber');
  }

  static void _checkRange(int value, int min, int max, String name) {
    if (value < min || value > max) {
      throw ArgumentError.value(value, name, 'must be between $min and $max');
    }
  }
}

/// A tag that carries no tag number.
class AnonymousTag implements Tag {
  @override
  int get size => 0;

  static AnonymousTag? _instance;

  static AnonymousTag get instance => _instance ??= AnonymousTag();

  @override
  bool operator ==(Object other) => other is AnonymousTag;

  @override
  int get hashCode => 0;

  @override
  String toString() => 'AnonymousTag()';
}

/// A context-specific tag, valid inside structures and lists.
class ContextSpecificTag implements Tag {
  final int tagNumber;

  ContextSpecificTag(this.tagNumber);

  @override
  int get size => 1;

  @override
  bool operator ==(Object other) =>
      other is ContextSpecificTag && other.tagNumber == tagNumber;

  @override
  int get hashCode => Object.hash(ContextSpecificTag, tagNumber);

  @override
  String toString() => 'ContextSpecificTag($tagNumber)';
}

/// A common-profile tag.
class CommonProfileTag implements Tag {
  @override
  final int size;
  final int tagNumber;

  CommonProfileTag(this.size, this.tagNumber);

  @override
  bool operator ==(Object other) =>
      other is CommonProfileTag &&
      other.size == size &&
      other.tagNumber == tagNumber;

  @override
  int get hashCode => Object.hash(CommonProfileTag, size, tagNumber);

  @override
  String toString() => 'CommonProfileTag($size, $tagNumber)';
}

/// An implicit-profile tag.
class ImplicitProfileTag implements Tag {
  @override
  final int size;
  final int tagNumber;

  ImplicitProfileTag(this.size, this.tagNumber);

  @override
  bool operator ==(Object other) =>
      other is ImplicitProfileTag &&
      other.size == size &&
      other.tagNumber == tagNumber;

  @override
  int get hashCode => Object.hash(ImplicitProfileTag, size, tagNumber);

  @override
  String toString() => 'ImplicitProfileTag($size, $tagNumber)';
}

/// A fully-qualified tag containing a vendor ID, profile number and tag number.
class FullyQualifiedTag implements Tag {
  @override
  final int size;
  final int vendorId;
  final int profileNumber;
  final int tagNumber;

  FullyQualifiedTag(
    this.size,
    this.vendorId,
    this.profileNumber,
    this.tagNumber,
  );

  @override
  bool operator ==(Object other) =>
      other is FullyQualifiedTag &&
      other.size == size &&
      other.vendorId == vendorId &&
      other.profileNumber == profileNumber &&
      other.tagNumber == tagNumber;

  @override
  int get hashCode =>
      Object.hash(FullyQualifiedTag, size, vendorId, profileNumber, tagNumber);

  @override
  String toString() =>
      'FullyQualifiedTag($size, $vendorId, $profileNumber, $tagNumber)';
}
