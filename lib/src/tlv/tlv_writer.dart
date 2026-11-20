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

import 'element.dart';
import 'tag.dart';
import 'tlv_reader.dart';
import 'tlv_types.dart';
import 'utils.dart';
import 'values.dart';

export 'tlv_exception.dart';

/// Writes Matter TLV elements incrementally.
///
/// Every write validates its tag/container placement and fully encodes the
/// candidate element before mutating the writer. A failed write therefore
/// leaves the document and container stack unchanged.
class TlvWriter {
  late List<int> _data;
  late List<Type> _containerTypes;

  TlvWriter([int initialCapacity = 32]) {
    if (initialCapacity < 0) {
      throw ArgumentError.value(initialCapacity, 'initialCapacity');
    }
    _data = <int>[];
    _containerTypes = <Type>[];
  }

  TlvWriter _put(Element element) {
    final value = element.value;
    final tag = element.tag;

    final Type type;
    final int encodedType;
    try {
      type = value.toType();
      encodedType = type.encode();
    } catch (error) {
      throw TlvEncodingException(
        'Unable to encode value type at index ${_data.length}',
        error,
      );
    }

    _validatePlacement(tag, type);

    final Uint8List encodedControlAndTag;
    final Uint8List encodedValue;
    try {
      encodedControlAndTag = Tag.encode(encodedType, tag);
    } catch (error) {
      if (error is ArgumentError) {
        rethrow;
      }
      throw TlvEncodingException(
        'Type error at ${_data.length} for '
        '${byteToBinary(encodedType)}',
        error,
      );
    }
    try {
      encodedValue = value.encode();
    } catch (error) {
      throw TlvEncodingException(
        'Unable to encode value at index ${_data.length}',
        error,
      );
    }

    // Do not touch _data or _containerTypes until all validation and encoding
    // has completed successfully.
    _data.addAll(encodedControlAndTag);
    _data.addAll(encodedValue);

    if (value is EndOfContainerValue) {
      _containerTypes.removeLast();
    } else if (value is StructureValue ||
        value is ArrayValue ||
        value is ListValue) {
      _containerTypes.add(type);
    }

    return this;
  }

  void _validatePlacement(Tag tag, Type type) {
    final containerType = _containerTypes.isEmpty ? null : _containerTypes.last;

    if (containerType == null) {
      if (tag is ContextSpecificTag) {
        throw ArgumentError(
          'Invalid use of context tag at index ${_data.length}: can only be '
          'used within a structure or a list',
        );
      }
    } else if (containerType is ArrayType) {
      if (tag is! AnonymousTag) {
        throw ArgumentError(
          'Invalid element tag at index ${_data.length}: elements of an array '
          'SHALL be anonymous',
        );
      }
    } else if (containerType is StructureType && type is! EndOfContainerType) {
      if (tag is AnonymousTag) {
        throw ArgumentError(
          'Invalid element tag at index ${_data.length}: elements of a '
          'structure cannot be anonymous',
        );
      }
    }

    if (tag is ContextSpecificTag) {
      if (tag.tagNumber < 0 || tag.tagNumber > 0xff) {
        throw ArgumentError(
          'Invalid context specific tag value ${tag.tagNumber} at index '
          '${_data.length}',
        );
      }
    }

    if (type is EndOfContainerType && _containerTypes.isEmpty) {
      throw ArgumentError(
        'Cannot close container at index ${_data.length}, which is not in the '
        'open container.',
      );
    }
  }

  TlvWriter put(Tag tag, int value) {
    return _put(Element(tag, IntValue(value)));
  }

  /// Writes an unsigned integer from a Dart [num] without changing the
  /// original public API. Negative values are interpreted as their unsigned
  /// 64-bit two's-complement representation, matching the Kotlin writer's
  /// `ULong.toLong()` bridge.
  TlvWriter putUnsigned(Tag tag, num value) {
    final integer = value.toInt();
    final unsigned = integer < 0
        ? BigInt.from(integer).toUnsigned(64)
        : BigInt.from(integer);
    return putUnsignedBigInt(tag, unsigned);
  }

  /// Writes the complete unsigned 64-bit range.
  TlvWriter putUnsignedBigInt(Tag tag, BigInt value) {
    return _put(Element(tag, UnsignedIntValue.fromBigInt(value)));
  }

  TlvWriter putBool(Tag tag, bool value) {
    return _put(Element(tag, BooleanValue(value)));
  }

  /// Writes a single-precision floating-point value.
  TlvWriter putFloat(Tag tag, double value) {
    return _put(Element(tag, FloatValue(value)));
  }

  TlvWriter putDouble(Tag tag, double value) {
    return _put(Element(tag, DoubleValue(value)));
  }

  TlvWriter putString(Tag tag, String value) {
    return _put(Element(tag, Utf8StringValue(value)));
  }

  /// Writes an octet string. This method name is retained for compatibility.
  TlvWriter putArray(Tag tag, Uint8List value) {
    return _put(Element(tag, ByteStringValue(value)));
  }

  TlvWriter putSignedLongArray(Tag tag, List<int> array) {
    return _withRollback(() {
      startArray(tag);
      for (final value in array) {
        put(AnonymousTag.instance, value);
      }
      return endArray();
    });
  }

  /// Writes an array of unsigned integers.
  TlvWriter putUnsignedLongArray(Tag tag, List<int> array) {
    return _withRollback(() {
      startArray(tag);
      for (final value in array) {
        putUnsigned(AnonymousTag.instance, value);
      }
      return endArray();
    });
  }

  /// Writes an array of signed integers.
  ///
  /// This legacy method intentionally keeps the original `List<int>`
  /// signature. Use [putByteStringArrayValues] to write octet strings.
  @Deprecated('Use putByteStringArrayValues for octet-string arrays')
  TlvWriter putByteStringArray(Tag tag, List<int> array) {
    return _withRollback(() {
      startArray(tag);
      for (final value in array) {
        put(AnonymousTag.instance, value);
      }
      return endArray();
    });
  }

  /// Writes an array of octet strings with anonymous array-member tags.
  TlvWriter putByteStringArrayValues(Tag tag, List<Uint8List> array) {
    return _withRollback(() {
      startArray(tag);
      for (final value in array) {
        _put(Element(AnonymousTag.instance, ByteStringValue(value)));
      }
      return endArray();
    });
  }

  TlvWriter putNull(Tag tag) {
    return _put(Element(tag, NullValue.instance));
  }

  TlvWriter startStructure(Tag tag) {
    return _put(Element(tag, StructureValue.instance));
  }

  TlvWriter startArray(Tag tag) {
    return _put(Element(tag, ArrayValue.instance));
  }

  TlvWriter startList(Tag tag) {
    return _put(Element(tag, ListValue.instance));
  }

  TlvWriter endStructure() {
    if (_containerTypes.isEmpty || _containerTypes.last is! StructureType) {
      throw ArgumentError(
        'Error closing structure at index ${_data.length} as currently '
        'opened container is not a structure',
      );
    }
    return _put(Element(AnonymousTag.instance, EndOfContainerValue.instance));
  }

  TlvWriter endArray() {
    if (_containerTypes.isEmpty || _containerTypes.last is! ArrayType) {
      throw ArgumentError(
        'Error closing array at index ${_data.length} as currently opened '
        'container is not an array',
      );
    }
    return _put(Element(AnonymousTag.instance, EndOfContainerValue.instance));
  }

  TlvWriter endList() {
    if (_containerTypes.isEmpty || _containerTypes.last is! ListType) {
      throw ArgumentError(
        'Error closing list at index ${_data.length} as currently opened '
        'container is not a list',
      );
    }
    return _put(Element(AnonymousTag.instance, EndOfContainerValue.instance));
  }

  /// Copies the next TLV element, or the whole container, from [reader].
  ///
  /// The optional [tag] preserves the Kotlin two-argument form:
  /// `copyElement(tag, reader)`. Dart does not support overloads, so the first
  /// positional argument accepts either a [TlvReader] or a [Tag].
  TlvWriter copyElement(Object tagOrReader, [TlvReader? reader]) {
    final TlvReader source;
    final Tag tag;
    if (tagOrReader is TlvReader) {
      if (reader != null) {
        throw ArgumentError('Pass either a reader or a tag and reader');
      }
      source = tagOrReader;
      tag = source.peekElement().tag;
    } else if (tagOrReader is Tag && reader != null) {
      source = reader;
      tag = tagOrReader;
    } else {
      throw ArgumentError(
          'copyElement expects a TlvReader or (Tag, TlvReader)');
    }
    return _copyElement(tag, source);
  }

  TlvWriter _copyElement(Tag tag, TlvReader reader) {
    final dataSnapshot = List<int>.from(_data);
    final containerSnapshot = List<Type>.from(_containerTypes);
    final readerSnapshot = reader.index;

    try {
      var depth = 0;
      var first = true;
      do {
        final element = reader.nextElement();
        if (first) {
          if (element.value is EndOfContainerValue) {
            throw ArgumentError(
              'The TlvReader is positioned at invalid element: '
              'EndOfContainer',
            );
          }
          _put(Element(tag, element.value));
          first = false;
        } else {
          _put(element);
        }

        if (element.value is EndOfContainerValue) {
          depth--;
        } else if (element.value is StructureValue ||
            element.value is ArrayValue ||
            element.value is ListValue) {
          depth++;
        }
      } while (depth > 0);
      return this;
    } catch (_) {
      _data = dataSnapshot;
      _containerTypes = containerSnapshot;
      reader.index = readerSnapshot;
      rethrow;
    }
  }

  int getLengthWritten() => _data.length;

  /// Verifies that every opened container has been closed.
  TlvWriter validateTlv() {
    if (_containerTypes.isNotEmpty) {
      throw TlvEncodingException(
        'Invalid Tlv data: ${_containerTypes.length} containers are not closed',
      );
    }
    return this;
  }

  Uint8List getEncoded() => Uint8List.fromList(_data);

  void reset() {
    _data = <int>[];
    _containerTypes = <Type>[];
  }

  TlvWriter _withRollback(TlvWriter Function() action) {
    final dataSnapshot = List<int>.from(_data);
    final containerSnapshot = List<Type>.from(_containerTypes);
    try {
      return action();
    } catch (_) {
      _data = dataSnapshot;
      _containerTypes = containerSnapshot;
      rethrow;
    }
  }
}
