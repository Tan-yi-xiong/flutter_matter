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
  test('encodingFabricConfig_allElements', () {
    final writer = TlvWriter(_fabricConfig.length)
      ..startStructure(FullyQualifiedTag(6, 0, 5, 1))
      ..putUnsigned(
        ContextSpecificTag(1),
        BigInt.parse('7885a14c693bf1cb', radix: 16).toInt(),
      )
      ..startArray(ContextSpecificTag(2))
      ..startStructure(AnonymousTag.instance)
      ..putUnsigned(ContextSpecificTag(1), 0x1001)
      ..putUnsigned(ContextSpecificTag(2), 0x01)
      ..putArray(
        ContextSpecificTag(3),
        _hex('149BF1430B26F5E4BBF380D3DB855BA1'),
      )
      ..putArray(
        ContextSpecificTag(4),
        _hex('E0E8BAA1CAC6E8E7216D720BD13C61C5E0E7B901'),
      )
      ..putUnsigned(ContextSpecificTag(5), 0)
      ..putUnsigned(ContextSpecificTag(6), 0)
      ..endStructure()
      ..endArray()
      ..endStructure()
      ..validateTlv();

    expect(writer.getEncoded(), _fabricConfig);
  });
}
