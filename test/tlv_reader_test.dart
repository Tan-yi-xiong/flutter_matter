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
import 'package:flutter_test/flutter_test.dart';

Uint8List _hex(String text) {
  final normalized = text.replaceAll(RegExp(r'[^0-9a-fA-F]'), '');
  return Uint8List.fromList(<int>[
    for (var i = 0; i < normalized.length; i += 2)
      int.parse(normalized.substring(i, i + 2), radix: 16),
  ]);
}

final _fabricConfig = _hex('''
  D5 00 00 05 00 01 00 27 01 CB F1 3B 69 4C A1 85
  78 36 02 15 25 01 01 10 24 02 01 30 03 10 14 9B
  F1 43 0B 26 F5 E4 BB F3 80 D3 DB 85 5B A1 30 04
  14 E0 E8 BA A1 CA C6 E8 E7 21 6D 72 0B D1 3C 61
  C5 E0 E7 B9 01 24 05 00 24 06 00 18 18 18
''');

void main() {
  test('parsingFabricConfig_extractsFabricId', () {
    final reader = TlvReader(_fabricConfig);
    expect(reader.nextElement().value, isA<StructureValue>());

    var element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(1));
    expect(element.value, isA<UnsignedIntValue>());
    expect(
      (element.value as UnsignedIntValue).value,
      BigInt.parse('7885a14c693bf1cb', radix: 16).toInt(),
    );

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(2));
    expect(element.value, isA<ArrayValue>());

    element = reader.nextElement();
    expect(element.tag, AnonymousTag.instance);
    expect(element.value, isA<StructureValue>());

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(1));
    expect((element.value as UnsignedIntValue).value, 0x1001);

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(2));
    expect((element.value as UnsignedIntValue).value, 0x01);

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(3));
    expect(
      (element.value as ByteStringValue).value,
      _hex('149BF1430B26F5E4BBF380D3DB855BA1'),
    );

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(4));
    expect(
      (element.value as ByteStringValue).value,
      _hex('E0E8BAA1CAC6E8E7216D720BD13C61C5E0E7B901'),
    );

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(5));
    expect((element.value as UnsignedIntValue).value, 0);

    element = reader.nextElement();
    expect(element.tag, ContextSpecificTag(6));
    expect((element.value as UnsignedIntValue).value, 0);

    expect(reader.nextElement().value, isA<EndOfContainerValue>());
    expect(reader.nextElement().value, isA<EndOfContainerValue>());
    expect(reader.nextElement().value, isA<EndOfContainerValue>());
  });

  test('parsingContextSpecificTagWithUnsignedIntMsbSet_extractsUnsignedInt',
      () {
    final element = TlvReader(_hex('25 00 F2 FF')).nextElement();
    expect(element.tag, ContextSpecificTag(0));
    expect(element.value, isA<UnsignedIntValue>());
    expect((element.value as UnsignedIntValue).value, 65522);
  });

  test('iterator_overAllElements_returnsExpectedNumberOfElements', () {
    expect(TlvReader(_fabricConfig).toList(), hasLength(13));
  });

  test('onReset_readerStartsAtBeginning', () {
    final reader = TlvReader(_fabricConfig);
    final initialElements = reader.take(3).toList();
    reader.reset();
    expect(reader.take(3).toList(), initialElements);
  });

  test('onInvalidData_throwsTlvParsingException', () {
    expect(
      () => TlvReader(_hex('05')).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
  });

  test('parseByteArray_extractsUtf8String', () {
    final bytes = Uint8List.fromList(<int>[
      0x4C,
      0x00,
      0x00,
      0x05,
      ...utf8.encode('value'),
    ]);
    final element = TlvReader(bytes).nextElement();
    expect(element.tag, CommonProfileTag(2, 0));
    expect(element.value, isA<Utf8StringValue>());
    expect((element.value as Utf8StringValue).value, 'value');
  });

  test('parseByteArray_extractsByteString', () {
    final value = utf8.encode('byte_string_utf8');
    expect(value.length, 16);
    final bytes = Uint8List.fromList(<int>[
      0x50,
      0x00,
      0x00,
      value.length,
      ...value,
    ]);
    final element = TlvReader(bytes).nextElement();
    expect(element.tag, CommonProfileTag(2, 0));
    expect(element.value, isA<ByteStringValue>());
    expect((element.value as ByteStringValue).value, value);
  });

  test('parseByteArray_extractsArray', () {
    final stringBytes = <int>[
      0x4C,
      0x00,
      0x00,
      0x05,
      ...utf8.encode('value'),
    ];
    final arrayBytes = <int>[
      0x56,
      0x00,
      0x00,
      0x0D,
      0x06,
      0x00,
      ...utf8.encode('value2'),
      0x0C,
      0x06,
      ...utf8.encode('value3'),
      0x18,
    ];
    final string4Bytes = <int>[
      0x4C,
      0x00,
      0x00,
      0x06,
      ...utf8.encode('value4'),
    ];
    final reader = TlvReader(
      Uint8List.fromList(<int>[
        ...stringBytes,
        ...arrayBytes,
        ...string4Bytes,
      ]),
    );

    var element = reader.nextElement();
    expect(element.tag, CommonProfileTag(2, 0));
    expect(element.value, isA<Utf8StringValue>());
    expect((element.value as Utf8StringValue).value, 'value');

    element = reader.nextElement();
    expect(element.tag, CommonProfileTag(2, 0));
    expect(element.value, isA<ArrayValue>());

    element = reader.nextElement();
    expect(element.tag, AnonymousTag.instance);
    expect(element.value, isA<Utf8StringValue>());
    expect((element.value as Utf8StringValue).value, 'value2');

    element = reader.nextElement();
    expect(element.tag, AnonymousTag.instance);
    expect(element.value, isA<Utf8StringValue>());
    expect((element.value as Utf8StringValue).value, 'value3');

    expect(reader.nextElement().value, isA<EndOfContainerValue>());
    element = reader.nextElement();
    expect(element.tag, CommonProfileTag(2, 0));
    expect(element.value, isA<Utf8StringValue>());
    expect((element.value as Utf8StringValue).value, 'value4');
  });

  test('contextSpecificTag_parsesUnsignedByte', () {
    final tag = TlvReader(_hex('24 FE 02')).nextElement().tag;
    expect(tag, ContextSpecificTag(0xFE));
    expect((tag as ContextSpecificTag).tagNumber, 0xFE);
  });
}
