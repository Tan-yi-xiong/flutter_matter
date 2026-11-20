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

const _vendorId = 0xAABB;
const _productId = 0xCCDD;

Uint8List _hex(String text) {
  final normalized = text.replaceAll(RegExp(r'[^0-9a-fA-F]'), '');
  if (normalized.length.isOdd) {
    throw ArgumentError('Hexadecimal input must contain complete bytes');
  }
  return Uint8List.fromList(<int>[
    for (var i = 0; i < normalized.length; i += 2)
      int.parse(normalized.substring(i, i + 2), radix: 16),
  ]);
}

double _float32(double value) {
  final data = ByteData(4)..setFloat32(0, value, Endian.little);
  return data.getFloat32(0, Endian.little);
}

final _testTlvSampleData = _hex('''
  D5 BB AA DD CC 01 00 C9 BB AA DD CC 02 00 88 02
  00 36 00 00 2A 00 EF 02 F0 67 FD FF 07 00 90 2F
  50 09 00 00 00 15 18 17 D4 BB AA DD CC 11 00 B4
  A0 BB 0D 00 14 B5 00 28 6B EE 6D 70 11 01 00 0E
  01 53 54 41 52 54 2E 2E 2E 21 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 40 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 23 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 24 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 25 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 5E 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 26 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 2A 31 32 33 34 35 36
  37 38 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 28 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 29 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 2D 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 3D 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 5B 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 5D 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 3B 39 41 42 43 44 45 46 30 31 32 33 34 35 36
  37 27 39 41 42 43 44 45 46 2E 2E 2E 45 4E 44 18
  18 18 CC BB AA DD CC 05 00 0E 54 68 69 73 20 69
  73 20 61 20 74 65 73 74 8A FF FF 33 33 8F 41 AB
  00 00 01 00 66 66 66 66 66 E6 31 40 18
''');

const _testLargeString = 'START...'
    '!123456789ABCDEF@123456789ABCDEF#123456789ABCDEF\$123456789ABCDEF'
    '%123456789ABCDEF^123456789ABCDEF&123456789ABCDEF*123456789ABCDEF'
    '01234567(9ABCDEF01234567)9ABCDEF01234567-9ABCDEF01234567=9ABCDEF'
    "01234567[9ABCDEF01234567]9ABCDEF01234567;9ABCDEF01234567'9ABCDEF"
    '...END';

void main() {
  test('testTlvSampleData_write', () {
    final writer = TlvWriter()
      ..startStructure(FullyQualifiedTag(6, _vendorId, _productId, 1))
      ..putBool(FullyQualifiedTag(6, _vendorId, _productId, 2), true)
      ..putBool(ImplicitProfileTag(2, 2), false)
      ..startArray(ContextSpecificTag(0))
      ..put(AnonymousTag.instance, 42)
      ..put(AnonymousTag.instance, -17)
      ..put(AnonymousTag.instance, -170000)
      ..putUnsigned(AnonymousTag.instance, 40000000000)
      ..startStructure(AnonymousTag.instance)
      ..endStructure()
      ..startList(AnonymousTag.instance)
      ..putNull(FullyQualifiedTag(6, _vendorId, _productId, 17))
      ..putNull(ImplicitProfileTag(4, 900000))
      ..putNull(AnonymousTag.instance)
      ..startStructure(ImplicitProfileTag(4, 4000000000))
      ..putString(CommonProfileTag(4, 70000), _testLargeString)
      ..endStructure()
      ..endList()
      ..endArray()
      ..putString(
        FullyQualifiedTag(6, _vendorId, _productId, 5),
        'This is a test',
      )
      ..putFloat(ImplicitProfileTag(2, 65535), 17.9)
      ..putDouble(ImplicitProfileTag(4, 65536), 17.9)
      ..endStructure()
      ..validateTlv();

    expect(writer.getEncoded(), _testTlvSampleData);
  });

  test('testTlvSampleData_read', () {
    final reader = TlvReader(_testTlvSampleData)
      ..enterStructure(FullyQualifiedTag(6, _vendorId, _productId, 1));
    expect(
      reader.getBool(FullyQualifiedTag(6, _vendorId, _productId, 2)),
      isTrue,
    );
    expect(reader.getBool(ImplicitProfileTag(2, 2)), isFalse);
    reader.enterArray(ContextSpecificTag(0));
    expect(reader.getInt(AnonymousTag.instance), 42);
    expect(reader.getInt(AnonymousTag.instance), -17);
    expect(reader.getInt(AnonymousTag.instance), -170000);
    expect(reader.getULong(AnonymousTag.instance), 40000000000);
    reader.enterStructure(AnonymousTag.instance);
    reader.exitContainer();
    reader.enterList(AnonymousTag.instance);
    reader.getNull(FullyQualifiedTag(6, _vendorId, _productId, 17));
    reader.getNull(ImplicitProfileTag(4, 900000));
    reader.getNull(AnonymousTag.instance);
    reader.enterStructure(ImplicitProfileTag(4, 4000000000));
    expect(reader.getUtf8String(CommonProfileTag(4, 70000)), _testLargeString);
    reader.exitContainer();
    reader.exitContainer();
    reader.exitContainer();
    expect(
      reader.getUtf8String(FullyQualifiedTag(6, _vendorId, _productId, 5)),
      'This is a test',
    );
    expect(reader.getFloat(ImplicitProfileTag(2, 65535)), _float32(17.9));
    expect(reader.getDouble(ImplicitProfileTag(4, 65536)), 17.9);
    reader.exitContainer();
    expect(reader.getLengthRead(), _testTlvSampleData.length);
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('testTlvSampleData_read_useSkipElementAndExitContinerInTheMiddle', () {
    final reader = TlvReader(_testTlvSampleData)
      ..enterStructure(FullyQualifiedTag(6, _vendorId, _productId, 1))
      ..skipElement();
    expect(reader.getBool(ImplicitProfileTag(2, 2)), isFalse);
    reader.enterArray(ContextSpecificTag(0));
    expect(reader.getInt(AnonymousTag.instance), 42);
    reader.exitContainer();
    expect(
      reader.getUtf8String(FullyQualifiedTag(6, _vendorId, _productId, 5)),
      'This is a test',
    );
    expect(reader.getFloat(ImplicitProfileTag(2, 65535)), _float32(17.9));
    expect(reader.getDouble(ImplicitProfileTag(4, 65536)), 17.9);
    reader.exitContainer();
    expect(reader.getLengthRead(), _testTlvSampleData.length);
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('testTlvSampleData_copyElement', () {
    final writer = TlvWriter()..copyElement(TlvReader(_testTlvSampleData));
    expect(writer.validateTlv().getEncoded(), _testTlvSampleData);
  });

  test('testTlvSampleData_copyElementWithTag', () {
    final writer = TlvWriter()
      ..copyElement(
        FullyQualifiedTag(6, _vendorId, _productId, 1),
        TlvReader(_testTlvSampleData),
      );
    expect(writer.validateTlv().getEncoded(), _testTlvSampleData);
  });

  test('testCopyElement_throwsIllegalArgumentException', () {
    final encoding = (TlvWriter()
          ..startStructure(AnonymousTag.instance)
          ..endStructure())
        .validateTlv()
        .getEncoded();
    final reader = TlvReader(encoding)..skipElement();
    expect(() => TlvWriter().copyElement(reader), throwsArgumentError);
  });

  test('testCopyElement_replaceTag', () {
    final tag = CommonProfileTag(2, 1000);
    final encoding = (TlvWriter()
          ..startStructure(AnonymousTag.instance)
          ..endStructure())
        .validateTlv()
        .getEncoded();
    final expected = (TlvWriter()
          ..startStructure(tag)
          ..endStructure())
        .validateTlv()
        .getEncoded();
    expect(
      (TlvWriter()..copyElement(tag, TlvReader(encoding)))
          .validateTlv()
          .getEncoded(),
      expected,
    );
  });

  test('testCopyElementUInt_replaceTag', () {
    final tag1 = CommonProfileTag(2, 1);
    final tag2 = CommonProfileTag(2, 2);
    final encoding =
        (TlvWriter()..putUnsigned(tag1, 42)).validateTlv().getEncoded();
    final expected =
        (TlvWriter()..putUnsigned(tag2, 42)).validateTlv().getEncoded();
    expect(
      (TlvWriter()..copyElement(tag2, TlvReader(encoding)))
          .validateTlv()
          .getEncoded(),
      expected,
    );
  });

  test('testTlvSampleData_copyElementsOneByOne', () {
    final reader = TlvReader(_testTlvSampleData)..skipElement();
    final writer = TlvWriter()
      ..startStructure(FullyQualifiedTag(6, _vendorId, _productId, 1))
      ..copyElement(reader)
      ..copyElement(reader)
      ..copyElement(reader)
      ..copyElement(
        FullyQualifiedTag(6, _vendorId, _productId, 5),
        reader,
      )
      ..copyElement(reader)
      ..copyElement(reader)
      ..endStructure()
      ..validateTlv();
    expect(writer.getEncoded(), _testTlvSampleData);
  });

  test('testData_IntMinMax', () {
    final writer = TlvWriter()
      ..put(AnonymousTag.instance, -128)
      ..put(AnonymousTag.instance, 127)
      ..put(AnonymousTag.instance, -32768)
      ..put(AnonymousTag.instance, 32767)
      ..put(AnonymousTag.instance, -2147483648)
      ..put(AnonymousTag.instance, 2147483647)
      ..put(AnonymousTag.instance, -9223372036854775808)
      ..put(AnonymousTag.instance, 9223372036854775807)
      ..putUnsigned(AnonymousTag.instance, 255)
      ..putUnsigned(AnonymousTag.instance, 65535)
      ..putUnsigned(AnonymousTag.instance, 4294967295)
      ..putUnsignedBigInt(
        AnonymousTag.instance,
        (BigInt.one << 64) - BigInt.one,
      )
      ..validateTlv();
    final reader = TlvReader(writer.getEncoded());
    expect(reader.getByte(AnonymousTag.instance), -128);
    expect(reader.getByte(AnonymousTag.instance), 127);
    expect(reader.getShort(AnonymousTag.instance), -32768);
    expect(reader.getShort(AnonymousTag.instance), 32767);
    expect(reader.getInt(AnonymousTag.instance), -2147483648);
    expect(reader.getInt(AnonymousTag.instance), 2147483647);
    expect(reader.getLong(AnonymousTag.instance), -9223372036854775808);
    expect(reader.getLong(AnonymousTag.instance), 9223372036854775807);
    expect(reader.getUByte(AnonymousTag.instance), 255);
    expect(reader.getUShort(AnonymousTag.instance), 65535);
    expect(reader.getUInt(AnonymousTag.instance), 4294967295);
    expect(
      reader.getULongBigInt(AnonymousTag.instance),
      (BigInt.one << 64) - BigInt.one,
    );
  });

  test('encodeBoolean_false', () {
    const value = false;
    final encoding = _hex('08');
    final writer = TlvWriter()..putBool(AnonymousTag.instance, value);
    expect(writer.getEncoded(), encoding);
    expect(TlvReader(encoding).getBool(AnonymousTag.instance), value);
  });

  test('encodeBoolean_true', () {
    const value = true;
    final encoding = _hex('09');
    final writer = TlvWriter()..putBool(AnonymousTag.instance, value);
    expect(writer.getEncoded(), encoding);
    expect(TlvReader(encoding).getBool(AnonymousTag.instance), value);
  });

  test('encodeSignedInt_1BytePositive', () {
    final writer = TlvWriter()..put(AnonymousTag.instance, 42);
    expect(writer.getEncoded(), _hex('00 2A'));
    expect(TlvReader(_hex('00 2A')).getInt(AnonymousTag.instance), 42);
  });

  test('encodeSignedInt_1ByteNegative', () {
    final writer = TlvWriter()..put(AnonymousTag.instance, -17);
    expect(writer.getEncoded(), _hex('00 EF'));
    expect(TlvReader(_hex('00 EF')).getInt(AnonymousTag.instance), -17);
  });

  test('encodeUnsignedInt_1Byte', () {
    final writer = TlvWriter()..putUnsigned(AnonymousTag.instance, 42);
    expect(writer.getEncoded(), _hex('04 2A'));
    expect(TlvReader(_hex('04 2A')).getUInt(AnonymousTag.instance), 42);
  });

  test('encodeUnsignedInt_1Byte_usePutUnsigned', () {
    final writer = TlvWriter()..putUnsigned(AnonymousTag.instance, 42);
    expect(writer.getEncoded(), _hex('04 2A'));
  });

  test('encodeSignedInt_1Byte2octet', () {
    expect(TlvReader(_hex('01 2A 00')).getInt(AnonymousTag.instance), 42);
  });

  test('encodeSignedInt_2Bytes', () {
    final writer = TlvWriter()..put(AnonymousTag.instance, 4242);
    expect(writer.getEncoded(), _hex('01 92 10'));
    expect(TlvReader(_hex('01 92 10')).getInt(AnonymousTag.instance), 4242);
  });

  test('encodeSignedInt_4Bytes', () {
    final writer = TlvWriter()..put(AnonymousTag.instance, -170000);
    expect(writer.getEncoded(), _hex('02 F0 67 FD FF'));
    expect(
      TlvReader(_hex('02 F0 67 FD FF')).getInt(AnonymousTag.instance),
      -170000,
    );
  });

  test('encodeSignedInt_8Bytes', () {
    final writer = TlvWriter()..put(AnonymousTag.instance, 40000000000);
    expect(writer.getEncoded(), _hex('03 00 90 2F 50 09 00 00 00'));
    expect(
      TlvReader(_hex('03 00 90 2F 50 09 00 00 00'))
          .getLong(AnonymousTag.instance),
      40000000000,
    );
  });

  test('encodeUnsignedInt_8Bytes_usePutUnsigned', () {
    final writer = TlvWriter()..putUnsigned(AnonymousTag.instance, 40000000000);
    expect(writer.getEncoded(), _hex('07 00 90 2F 50 09 00 00 00'));
    expect(
      TlvReader(_hex('07 00 90 2F 50 09 00 00 00'))
          .getULong(AnonymousTag.instance),
      40000000000,
    );
  });

  test('encodeSignedInt_8Bytes_useGetULong_throwsIllegalArgumentException', () {
    expect(
      () => TlvReader(_hex('03 00 90 2F 50 09 00 00 00'))
          .getULong(AnonymousTag.instance),
      throwsArgumentError,
    );
  });

  test('encodeSignedInt_8Bytes_useGetInt_throwsTlvParsingException', () {
    expect(
      () => TlvReader(_hex('03 00 90 2F 50 09 00 00 00'))
          .getInt(AnonymousTag.instance),
      throwsA(isA<TlvParsingException>()),
    );
  });

  test(
      'encodeSignedInt_8Bytes_getFullyQualifiedTag_throwsIllegalArgumentException',
      () {
    expect(
      () => TlvReader(_hex('03 00 90 2F 50 09 00 00 00'))
          .getLong(FullyQualifiedTag(6, _vendorId, _productId, 5)),
      throwsArgumentError,
    );
  });

  test('encodeUtf8String_hello', () {
    final writer = TlvWriter()..putString(AnonymousTag.instance, 'Hello!');
    expect(writer.getEncoded(), _hex('0C 06 48 65 6C 6C 6F 21'));
    expect(
      TlvReader(_hex('0C 06 48 65 6C 6C 6F 21'))
          .getUtf8String(AnonymousTag.instance),
      'Hello!',
    );
  });

  test('encodeUtf8String_tschuh', () {
    final writer = TlvWriter()..putString(AnonymousTag.instance, 'Tschüs');
    expect(writer.getEncoded(), _hex('0C 07 54 73 63 68 C3 BC 73'));
    expect(
      TlvReader(_hex('0C 07 54 73 63 68 C3 BC 73'))
          .getUtf8String(AnonymousTag.instance),
      'Tschüs',
    );
  });

  test('encodeOctetString', () {
    final value = _hex('00 01 02 03 04');
    final encoding = _hex('10 05 00 01 02 03 04');
    final writer = TlvWriter()..putArray(AnonymousTag.instance, value);
    expect(writer.getEncoded(), encoding);
    expect(TlvReader(encoding).getByteString(AnonymousTag.instance), value);
  });

  test('encodeNull', () {
    final writer = TlvWriter()..putNull(AnonymousTag.instance);
    expect(writer.getEncoded(), _hex('14'));
    TlvReader(_hex('14')).getNull(AnonymousTag.instance);
  });

  test('encodeFloat_0', () {
    final writer = TlvWriter()..putFloat(AnonymousTag.instance, 0);
    expect(writer.getEncoded(), _hex('0A 00 00 00 00'));
    expect(
        TlvReader(_hex('0A 00 00 00 00')).getFloat(AnonymousTag.instance), 0);
  });

  test('encodeFloat_1third', () {
    const value = 1 / 3;
    final writer = TlvWriter()..putFloat(AnonymousTag.instance, value);
    expect(writer.getEncoded(), _hex('0A AB AA AA 3E'));
    expect(
      TlvReader(_hex('0A AB AA AA 3E')).getFloat(AnonymousTag.instance),
      _float32(value),
    );
  });

  test('encodeFloat_17_9', () {
    final writer = TlvWriter()..putFloat(AnonymousTag.instance, 17.9);
    expect(writer.getEncoded(), _hex('0A 33 33 8F 41'));
    expect(
      TlvReader(_hex('0A 33 33 8F 41')).getFloat(AnonymousTag.instance),
      _float32(17.9),
    );
  });

  test('encodeFloat_positiveInfinity', () {
    final writer = TlvWriter()
      ..putFloat(AnonymousTag.instance, double.infinity);
    expect(writer.getEncoded(), _hex('0A 00 00 80 7F'));
    expect(
      TlvReader(_hex('0A 00 00 80 7F')).getFloat(AnonymousTag.instance),
      double.infinity,
    );
  });

  test('encodeFloat_negativeInfinity', () {
    final writer = TlvWriter()
      ..putFloat(AnonymousTag.instance, double.negativeInfinity);
    expect(writer.getEncoded(), _hex('0A 00 00 80 FF'));
  });

  test('encodeDouble_0', () {
    final writer = TlvWriter()..putDouble(AnonymousTag.instance, 0);
    expect(writer.getEncoded(), _hex('0B 00 00 00 00 00 00 00 00'));
    expect(
        TlvReader(_hex('0B 00 00 00 00 00 00 00 00'))
            .getDouble(AnonymousTag.instance),
        0);
  });

  test('encodeDouble_1third', () {
    const value = 1 / 3;
    final writer = TlvWriter()..putDouble(AnonymousTag.instance, value);
    expect(writer.getEncoded(), _hex('0B 55 55 55 55 55 55 D5 3F'));
    expect(
      TlvReader(_hex('0B 55 55 55 55 55 55 D5 3F'))
          .getDouble(AnonymousTag.instance),
      value,
    );
  });

  test('encodeDouble_17_9', () {
    final writer = TlvWriter()..putDouble(AnonymousTag.instance, 17.9);
    expect(writer.getEncoded(), _hex('0B 66 66 66 66 66 E6 31 40'));
    expect(
      TlvReader(_hex('0B 66 66 66 66 66 E6 31 40'))
          .getDouble(AnonymousTag.instance),
      17.9,
    );
  });

  test('encodeDouble_positiveInfinity', () {
    final writer = TlvWriter()
      ..putDouble(AnonymousTag.instance, double.infinity);
    expect(writer.getEncoded(), _hex('0B 00 00 00 00 00 00 F0 7F'));
    expect(
      TlvReader(_hex('0B 00 00 00 00 00 00 F0 7F'))
          .getDouble(AnonymousTag.instance),
      double.infinity,
    );
  });

  test('encodeDouble_negativeInfinity', () {
    final writer = TlvWriter()
      ..putDouble(AnonymousTag.instance, double.negativeInfinity);
    expect(writer.getEncoded(), _hex('0B 00 00 00 00 00 00 F0 FF'));
  });

  test('encodeStructure_empty', () {
    final writer = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..endStructure();
    expect(writer.getEncoded(), _hex('15 18'));
    final reader = TlvReader(_hex('15 18'))
      ..enterStructure(AnonymousTag.instance)
      ..exitContainer();
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('encodeStructure_empty_testEndOfContainer', () {
    final reader = TlvReader(_hex('15 18'));
    expect(reader.isEndOfContainer(), isFalse);
    reader.enterStructure(AnonymousTag.instance);
    expect(reader.isEndOfContainer(), isTrue);
    reader.exitContainer();
    expect(
        () => reader.isEndOfContainer(), throwsA(isA<TlvParsingException>()));
  });

  test('encodeStructure_notClosed_throwsTlvEncodingException', () {
    final writer = TlvWriter()..startStructure(AnonymousTag.instance);
    expect(() => writer.validateTlv(), throwsA(isA<TlvEncodingException>()));
  });

  test('encodeArray_empty', () {
    final writer = TlvWriter()
      ..startArray(AnonymousTag.instance)
      ..endArray();
    expect(writer.getEncoded(), _hex('16 18'));
    TlvReader(_hex('16 18'))
      ..enterArray(AnonymousTag.instance)
      ..exitContainer();
  });

  test('encodeArray_empty_closeUnopennedArray_throwsIllegalArgumentException',
      () {
    final writer = TlvWriter()
      ..startArray(AnonymousTag.instance)
      ..endArray();
    expect(() => writer.endArray(), throwsArgumentError);
  });

  test('encodeList_empty', () {
    final writer = TlvWriter()
      ..startList(AnonymousTag.instance)
      ..endList();
    expect(writer.getEncoded(), _hex('17 18'));
    TlvReader(_hex('17 18'))
      ..enterList(AnonymousTag.instance)
      ..exitContainer();
  });

  test('encodeStructure_intsWithContextTags', () {
    final writer = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..put(ContextSpecificTag(0), 42)
      ..put(ContextSpecificTag(1), -17)
      ..endStructure();
    final expected = _hex('15 20 00 2A 20 01 EF 18');
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterStructure(AnonymousTag.instance);
    expect(reader.getByte(ContextSpecificTag(0)), 42);
    expect(reader.getByte(ContextSpecificTag(1)), -17);
    reader.exitContainer();
  });

  test('encodeArray_ints', () {
    final writer = TlvWriter()
      ..startArray(AnonymousTag.instance)
      ..put(AnonymousTag.instance, 0)
      ..put(AnonymousTag.instance, 1)
      ..put(AnonymousTag.instance, 2)
      ..put(AnonymousTag.instance, 3)
      ..put(AnonymousTag.instance, 4)
      ..endArray();
    final expected = _hex('16 00 00 00 01 00 02 00 03 00 04 18');
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterArray(AnonymousTag.instance);
    for (var i = 0; i < 5; i++) {
      expect(reader.getInt(AnonymousTag.instance), i);
    }
    reader.exitContainer();
  });

  test('encodeList_mixedInts', () {
    final writer = TlvWriter()
      ..startList(AnonymousTag.instance)
      ..put(AnonymousTag.instance, 1)
      ..put(ContextSpecificTag(0), 42)
      ..put(AnonymousTag.instance, 2)
      ..put(AnonymousTag.instance, 3)
      ..put(ContextSpecificTag(0), -17)
      ..endList();
    final expected = _hex('17 00 01 20 00 2A 00 02 00 03 20 00 EF 18');
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterList(AnonymousTag.instance);
    expect(reader.getInt(AnonymousTag.instance), 1);
    expect(reader.getInt(ContextSpecificTag(0)), 42);
    expect(reader.getInt(AnonymousTag.instance), 2);
    expect(reader.getInt(AnonymousTag.instance), 3);
    expect(reader.getInt(ContextSpecificTag(0)), -17);
    reader.exitContainer();
  });

  test('encodeArray_mixedValues', () {
    final writer = TlvWriter()
      ..startArray(AnonymousTag.instance)
      ..put(AnonymousTag.instance, 42)
      ..put(AnonymousTag.instance, -170000)
      ..startStructure(AnonymousTag.instance)
      ..endStructure()
      ..putFloat(AnonymousTag.instance, 17.9)
      ..putString(AnonymousTag.instance, 'Hello!')
      ..endArray();
    final expected = _hex(
      '16 00 2A 02 F0 67 FD FF 15 18 0A 33 33 8F 41 0C 06 48 65 6C 6C 6F 21 18',
    );
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterArray(AnonymousTag.instance);
    expect(reader.getInt(AnonymousTag.instance), 42);
    expect(reader.getInt(AnonymousTag.instance), -170000);
    reader.enterStructure(AnonymousTag.instance);
    reader.exitContainer();
    expect(reader.getFloat(AnonymousTag.instance), _float32(17.9));
    expect(reader.getUtf8String(AnonymousTag.instance), 'Hello!');
    reader.exitContainer();
  });

  test('encodeAanonymousTag', () {
    final writer = TlvWriter()..putUnsigned(AnonymousTag.instance, 42);
    expect(writer.getEncoded(), _hex('04 2A'));
    expect(TlvReader(_hex('04 2A')).getUInt(AnonymousTag.instance), 42);
  });

  test('encodeContextTag_withinStructure', () {
    final tag = ContextSpecificTag(1);
    final writer = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..putUnsigned(tag, 42)
      ..endStructure();
    final expected = _hex('15 24 01 2A 18');
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterStructure(AnonymousTag.instance);
    expect(reader.getUInt(tag), 42);
    reader.exitContainer();
  });

  test('encodeContextTag_invalidContextTag_throwsIllegalArgumentException', () {
    final writer = TlvWriter()..startStructure(AnonymousTag.instance);
    writer.putUnsigned(ContextSpecificTag(255), 42);
    expect(
      () => writer.putUnsigned(ContextSpecificTag(256), 17000),
      throwsArgumentError,
    );
  });

  test('encodeAnonymousTagInStructure_throwsIllegalArgumentException', () {
    final writer = TlvWriter()..startStructure(AnonymousTag.instance);
    expect(
      () => writer.putUnsigned(AnonymousTag.instance, 42),
      throwsArgumentError,
    );
  });

  test('encodeContextTag_withinList', () {
    final tag = ContextSpecificTag(1);
    final writer = TlvWriter()
      ..startList(AnonymousTag.instance)
      ..putUnsigned(tag, 42)
      ..endList();
    final expected = _hex('17 24 01 2A 18');
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterList(AnonymousTag.instance);
    expect(reader.getUInt(tag), 42);
    reader.exitContainer();
  });

  test('encodeContextTag_withinArray_throwsIllegalArgumentException', () {
    final writer = TlvWriter()..startArray(AnonymousTag.instance);
    expect(
      () => writer.putUnsigned(ContextSpecificTag(1), 42),
      throwsArgumentError,
    );
  });

  test('encodeContextTag_notInContainer_throwsIllegalArgumentException', () {
    expect(
      () => TlvWriter().putUnsigned(ContextSpecificTag(1), 42),
      throwsArgumentError,
    );
  });

  test('encodeCommonProfileTag2', () {
    final tag = CommonProfileTag(2, 1);
    final writer = TlvWriter()..putUnsigned(tag, 42);
    expect(writer.getEncoded(), _hex('44 01 00 2A'));
  });

  test('encodeCommonProfileTag4', () {
    final tag = CommonProfileTag(4, 100000);
    final writer = TlvWriter()..putUnsigned(tag, 42);
    expect(writer.getEncoded(), _hex('64 A0 86 01 00 2A'));
  });

  test('encodeFullyQualifiedTag6', () {
    final tag = FullyQualifiedTag(6, 0xFFF1, 0xDEED, 1);
    final writer = TlvWriter()..putUnsigned(tag, 42);
    expect(writer.getEncoded(), _hex('C4 F1 FF ED DE 01 00 2A'));
  });

  test('encodeFullyQualifiedTag8', () {
    final tag = FullyQualifiedTag(8, 0xFFF1, 0xDEED, 0xAA55FEED);
    final writer = TlvWriter()..putUnsigned(tag, 42);
    expect(writer.getEncoded(), _hex('E4 F1 FF ED DE ED FE 55 AA 2A'));
  });

  test('encodeFullyQualifiedTags_withStructure', () {
    final structTag = FullyQualifiedTag(6, 0xFFF1, 0xDEED, 1);
    final valueTag = FullyQualifiedTag(6, 0xFFF1, 57069, 43605);
    final writer = TlvWriter()
      ..startStructure(structTag)
      ..putUnsigned(valueTag, 42)
      ..endStructure();
    final expected = _hex('D5 F1 FF ED DE 01 00 C4 F1 FF ED DE 55 AA 2A 18');
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterStructure(structTag);
    expect(reader.getUInt(valueTag), 42);
    reader.exitContainer();
  });

  test('encodeArray_empty_useputSignedLongArray', () {
    final writer = TlvWriter()..putSignedLongArray(AnonymousTag.instance, []);
    expect(writer.getEncoded(), _hex('16 18'));
  });

  test('putSignedLongArray', () {
    final values = <int>[42, -17, -170000, 40000000000];
    final writer = TlvWriter()
      ..putSignedLongArray(AnonymousTag.instance, values);
    final expected = _hex(
      '16 00 2A 00 EF 02 F0 67 FD FF 03 00 90 2F 50 09 00 00 00 18',
    );
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterArray(AnonymousTag.instance);
    for (final value in values) {
      expect(reader.getLong(AnonymousTag.instance), value);
    }
    reader.exitContainer();
  });

  test('putUnsignedLongArray', () {
    final values = <int>[42, 170000, 40000000000];
    final writer = TlvWriter()
      ..putUnsignedLongArray(AnonymousTag.instance, values);
    final expected = _hex(
      '16 04 2A 06 10 98 02 00 07 00 90 2F 50 09 00 00 00 18',
    );
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterArray(AnonymousTag.instance);
    expect(reader.getULong(AnonymousTag.instance), 42);
    expect(reader.getULong(AnonymousTag.instance), 170000);
    expect(reader.isEndOfContainer(), isFalse);
    expect(reader.getULong(AnonymousTag.instance), 40000000000);
    expect(reader.isEndOfContainer(), isTrue);
    expect(reader.isEndOfTlv(), isFalse);
    reader.exitContainer();
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('putByteStringArray', () {
    final values = <Uint8List>[
      _hex('00 01 02 03 04'),
      _hex('FF'),
      _hex('4A EF 88'),
    ];
    final writer = TlvWriter()
      ..putByteStringArrayValues(AnonymousTag.instance, values);
    final expected = _hex(
      '16 10 05 00 01 02 03 04 10 01 FF 10 03 4A EF 88 18',
    );
    expect(writer.getEncoded(), expected);
    final reader = TlvReader(expected)..enterArray(AnonymousTag.instance);
    expect(reader.getByteString(AnonymousTag.instance), values[0]);
    expect(reader.getByteString(AnonymousTag.instance), values[1]);
    expect(reader.getByteString(AnonymousTag.instance), values[2]);
    reader.exitContainer();
  });
}
