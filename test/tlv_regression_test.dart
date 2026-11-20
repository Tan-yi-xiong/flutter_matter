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

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/src/tlv/utils.dart';
import 'package:flutter_test/flutter_test.dart';

Uint8List _hex(String text) {
  final normalized = text.replaceAll(RegExp(r'[^0-9a-fA-F]'), '');
  return Uint8List.fromList(<int>[
    for (var i = 0; i < normalized.length; i += 2)
      int.parse(normalized.substring(i, i + 2), radix: 16),
  ]);
}

void _expectBytes(Uint8List actual, List<int> expected) {
  expect(actual, expected);
}

void main() {
  test('Tag equality and hash code compare values not object identity', () {
    final tags = <Tag>[
      ContextSpecificTag(7),
      CommonProfileTag(2, 0x1234),
      CommonProfileTag(4, 0x12345678),
      ImplicitProfileTag(2, 0x5678),
      ImplicitProfileTag(4, 0x87654321),
      FullyQualifiedTag(6, 0xFFF1, 0xDEED, 0xAA55),
      FullyQualifiedTag(8, 0xFFF1, 0xDEED, 0xAA55FEED),
    ];
    final copies = <Tag>[
      ContextSpecificTag(7),
      CommonProfileTag(2, 0x1234),
      CommonProfileTag(4, 0x12345678),
      ImplicitProfileTag(2, 0x5678),
      ImplicitProfileTag(4, 0x87654321),
      FullyQualifiedTag(6, 0xFFF1, 0xDEED, 0xAA55),
      FullyQualifiedTag(8, 0xFFF1, 0xDEED, 0xAA55FEED),
    ];

    for (var i = 0; i < tags.length; i++) {
      expect(tags[i], copies[i]);
      expect(tags[i].hashCode, copies[i].hashCode);
    }
    expect(AnonymousTag.instance, AnonymousTag());
    expect(AnonymousTag.instance.hashCode, AnonymousTag().hashCode);
    expect(AnonymousTag.instance, isNot(ContextSpecificTag(0)));
  });

  test('Tag.encode covers every tag width and uses the correct field widths',
      () {
    _expectBytes(
      Tag.encode(0x04, AnonymousTag.instance),
      <int>[0x04],
    );
    _expectBytes(
      Tag.encode(0x04, ContextSpecificTag(0x7F)),
      <int>[0x24, 0x7F],
    );
    _expectBytes(
      Tag.encode(0x04, CommonProfileTag(2, 0x1234)),
      <int>[0x44, 0x34, 0x12],
    );
    _expectBytes(
      Tag.encode(0x04, CommonProfileTag(4, 0x12345678)),
      <int>[0x64, 0x78, 0x56, 0x34, 0x12],
    );
    _expectBytes(
      Tag.encode(0x04, ImplicitProfileTag(2, 0x1234)),
      <int>[0x84, 0x34, 0x12],
    );
    _expectBytes(
      Tag.encode(0x04, ImplicitProfileTag(4, 0x12345678)),
      <int>[0xA4, 0x78, 0x56, 0x34, 0x12],
    );
    _expectBytes(
      Tag.encode(0x04, FullyQualifiedTag(6, 0xFFF1, 0xDEED, 0xAA55)),
      <int>[0xC4, 0xF1, 0xFF, 0xED, 0xDE, 0x55, 0xAA],
    );
    _expectBytes(
      Tag.encode(
        0x04,
        FullyQualifiedTag(8, 0xFFF1, 0xDEED, 0xAA55FEED),
      ),
      <int>[0xE4, 0xF1, 0xFF, 0xED, 0xDE, 0xED, 0xFE, 0x55, 0xAA],
    );
  });

  test('Tag.from round-trips all forms through a byte view', () {
    final forms = <(Tag, int)>[
      (AnonymousTag.instance, 0x04),
      (ContextSpecificTag(0xFE), 0x24),
      (CommonProfileTag(2, 0x1234), 0x44),
      (CommonProfileTag(4, 0x12345678), 0x64),
      (ImplicitProfileTag(2, 0x1234), 0x84),
      (ImplicitProfileTag(4, 0x12345678), 0xA4),
      (FullyQualifiedTag(6, 0xFFF1, 0xDEED, 0xAA55), 0xC4),
      (FullyQualifiedTag(8, 0xFFF1, 0xDEED, 0xAA55FEED), 0xE4),
    ];

    for (final (tag, encodedType) in forms) {
      final encoded = Tag.encode(encodedType, tag);
      final backing = Uint8List.fromList(<int>[0xAA, 0xBB, ...encoded, 0xCC]);
      final view = Uint8List.sublistView(backing, 2, backing.length - 1);
      expect(Tag.from(view[0], 1, view), tag);
    }
  });

  test('byte reads honor Uint8List.offsetInBytes', () {
    final payload = _hex('0C 05 76 61 6C 75 65');
    final backing = Uint8List.fromList(<int>[0xAA, 0xBB, ...payload, 0xCC]);
    final view = Uint8List.sublistView(backing, 2, 2 + payload.length);
    expect(TlvReader(view).getUtf8String(AnonymousTag.instance), 'value');
  });

  test('truncated tags and bad control bytes are parsing errors', () {
    expect(
      () => Tag.from(0x44, 0, Uint8List.fromList(<int>[0x01])),
      throwsArgumentError,
    );
    expect(
      () => TlvReader(_hex('44 01')).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
    expect(
      () => TlvReader(_hex('C4 01 00')).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
    expect(
      () => TlvReader(_hex('1F')).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
  });

  test('malformed lengths and invalid UTF-8 fail closed', () {
    expect(
      () => TlvReader(_hex('0C 05 61')).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
    expect(
      () => TlvReader(_hex('0C 01 FF')).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
  });

  test('UTF-8 uses encoded byte lengths, including CJK and emoji', () {
    final values = <String>['ASCII', 'Tschüs', '你好', '😀'];
    for (final value in values) {
      final encoded = utf8.encode(value);
      final writer = TlvWriter()..putString(AnonymousTag.instance, value);
      expect(writer.getEncoded().sublist(2, 2 + encoded.length), encoded);
      expect(
        TlvReader(writer.getEncoded()).getUtf8String(AnonymousTag.instance),
        value,
      );
    }

    _expectBytes(
      (TlvWriter()..putString(AnonymousTag.instance, 'Tschüs')).getEncoded(),
      _hex('0C 07 54 73 63 68 C3 BC 73'),
    );
    _expectBytes(
      (TlvWriter()..putString(AnonymousTag.instance, '你好')).getEncoded(),
      _hex('0C 06 E4 BD A0 E5 A5 BD'),
    );
    _expectBytes(
      (TlvWriter()..putString(AnonymousTag.instance, '😀')).getEncoded(),
      _hex('0C 04 F0 9F 98 80'),
    );
  });

  test('getInt boundaries are inclusive and out-of-range is parsing error', () {
    Uint8List encode(int value) =>
        (TlvWriter()..put(AnonymousTag.instance, value)).getEncoded();

    expect(
      TlvReader(encode(-2147483648)).getInt(AnonymousTag.instance),
      -2147483648,
    );
    expect(
      TlvReader(encode(2147483647)).getInt(AnonymousTag.instance),
      2147483647,
    );
    expect(
      () => TlvReader(encode(-2147483649)).getInt(AnonymousTag.instance),
      throwsA(isA<TlvParsingException>()),
    );
    expect(
      () => TlvReader(encode(2147483648)).getInt(AnonymousTag.instance),
      throwsA(isA<TlvParsingException>()),
    );
  });

  test('ULong max is available through BigInt without unsafe int conversion',
      () {
    final max = (BigInt.one << 64) - BigInt.one;
    final signedMax = (BigInt.one << 63) - BigInt.one;
    final signedMaxEncoding = (TlvWriter()
          ..putUnsignedBigInt(AnonymousTag.instance, signedMax))
        .getEncoded();
    expect(TlvReader(signedMaxEncoding).getULong(AnonymousTag.instance),
        signedMax.toInt());

    final maxEncoding = (TlvWriter()
          ..putUnsignedBigInt(AnonymousTag.instance, max))
        .getEncoded();
    expect(
      TlvReader(maxEncoding).getULongBigInt(AnonymousTag.instance),
      max,
    );
    expect(
      () => TlvReader(maxEncoding).getULong(AnonymousTag.instance),
      throwsA(isA<TlvParsingException>()),
    );
    expect(() => unsignedIntSize(-1), throwsArgumentError);
  });

  test('reader copies input bytes and supports peek/iterator/reset', () {
    final input =
        (TlvWriter()..putString(AnonymousTag.instance, 'copy')).getEncoded();
    final reader = TlvReader(input);
    input.fillRange(0, input.length, 0xFF);

    expect(reader.peekElement().value, isA<Utf8StringValue>());
    expect(reader.getLengthRead(), 0);
    final elements = reader.toList();
    expect(elements, hasLength(1));
    expect((elements.single.value as Utf8StringValue).value, 'copy');
    expect(reader.isEndOfTlv(), isTrue);
    expect(reader.getRemainingLength(), 0);

    reader.reset();
    expect(reader.toList(), elements);
  });

  test('legacy putByteStringArray keeps signed-integer behavior', () {
    final writer = TlvWriter()
      ..putByteStringArray(AnonymousTag.instance, <int>[1, 255]);
    _expectBytes(
      writer.getEncoded(),
      _hex('16 00 01 01 FF 00 18'),
    );
    final reader = TlvReader(writer.getEncoded())
      ..enterArray(AnonymousTag.instance);
    expect(reader.getLong(AnonymousTag.instance), 1);
    expect(reader.getLong(AnonymousTag.instance), 255);
    reader.exitContainer();
  });

  test('putByteStringArrayValues writes octet strings with anonymous tags', () {
    final writer = TlvWriter()
      ..putByteStringArrayValues(AnonymousTag.instance, <Uint8List>[
        _hex('00 01 02'),
        _hex('FF'),
      ]);
    _expectBytes(
      writer.getEncoded(),
      _hex('16 10 03 00 01 02 10 01 FF 18'),
    );
    final reader = TlvReader(writer.getEncoded())
      ..enterArray(AnonymousTag.instance);
    expect(reader.getByteString(AnonymousTag.instance), _hex('00 01 02'));
    expect(reader.getByteString(AnonymousTag.instance), _hex('FF'));
    reader.exitContainer();
  });

  test('writer rejects invalid container transitions without corrupting state',
      () {
    final writer = TlvWriter()..startArray(AnonymousTag.instance);
    expect(
      () => writer.putUnsigned(ContextSpecificTag(1), 1),
      throwsArgumentError,
    );
    expect(writer.getEncoded(), _hex('16'));
    writer.put(AnonymousTag.instance, 1).endArray();
    _expectBytes(
      writer.getEncoded(),
      _hex('16 00 01 18'),
    );

    final root = TlvWriter();
    expect(
      () => root.putUnsigned(ContextSpecificTag(1), 1),
      throwsArgumentError,
    );
    expect(root.getEncoded(), isEmpty);

    final structure = TlvWriter()..startStructure(AnonymousTag.instance);
    expect(
      () => structure.putUnsigned(AnonymousTag.instance, 1),
      throwsArgumentError,
    );
    structure.putUnsigned(ContextSpecificTag(1), 1).endStructure();
    _expectBytes(
      structure.getEncoded(),
      _hex('15 24 01 01 18'),
    );
  });

  test('writer supports dynamic nesting beyond four containers', () {
    final writer = TlvWriter();
    const depth = 32;
    for (var i = 0; i < depth; i++) {
      writer.startArray(AnonymousTag.instance);
    }
    writer.put(AnonymousTag.instance, 1);
    for (var i = 0; i < depth; i++) {
      writer.endArray();
    }
    writer.validateTlv();

    final elements = TlvReader(writer.getEncoded()).toList();
    expect(elements.whereType<Element>(), hasLength(depth + 1 + depth));
    expect(
      elements.where((element) => element.value is ArrayValue),
      hasLength(depth),
    );
    expect(
      elements.where((element) => element.value is EndOfContainerValue),
      hasLength(depth),
    );
  });

  test('copyElement supports whole containers and tag replacement', () {
    final source = (TlvWriter()
          ..startStructure(AnonymousTag.instance)
          ..putString(ContextSpecificTag(1), 'nested')
          ..endStructure())
        .validateTlv()
        .getEncoded();
    final reader = TlvReader(source);
    final writer = TlvWriter()
      ..copyElement(CommonProfileTag(2, 7), reader)
      ..validateTlv();
    final expected = (TlvWriter()
          ..startStructure(CommonProfileTag(2, 7))
          ..putString(ContextSpecificTag(1), 'nested')
          ..endStructure())
        .validateTlv()
        .getEncoded();
    expect(writer.getEncoded(), expected);
  });

  test('copyElement failure restores writer and reader state', () {
    final source = (TlvWriter()
          ..startStructure(AnonymousTag.instance)
          ..endStructure())
        .getEncoded();
    final reader = TlvReader(source)..skipElement();
    final readerIndex = reader.index;
    final writer = TlvWriter()..put(AnonymousTag.instance, 7);
    final before = writer.getEncoded();

    expect(() => writer.copyElement(reader), throwsArgumentError);
    expect(writer.getEncoded(), before);
    expect(reader.index, readerIndex);
  });

  test('unknown Tag subclasses fail closed before writing', () {
    final writer = TlvWriter();
    expect(
      () => writer.put(_UnknownTag(), 1),
      throwsArgumentError,
    );
    expect(writer.getEncoded(), isEmpty);
  });

  test('context-specific boundary 255 is accepted and 256 is rejected', () {
    final accepted = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..putUnsigned(ContextSpecificTag(255), 1)
      ..endStructure();
    expect(accepted.getEncoded(), _hex('15 24 FF 01 18'));
    expect(
      () => TlvWriter().putUnsigned(ContextSpecificTag(256), 1),
      throwsArgumentError,
    );
  });
}

class _UnknownTag implements Tag {
  @override
  int get size => 0;
}
