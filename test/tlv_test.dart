import 'dart:typed_data';

import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter.dart';

void main() {
  test('TLV structure round-trips supported scalar values', () {
    final writer = TlvWriter();
    writer.startStructure(AnonymousTag.instance);
    writer.put(ContextSpecificTag(1), -42);
    writer.putUnsigned(ContextSpecificTag(2), 255);
    writer.putBool(ContextSpecificTag(3), true);
    writer.putString(ContextSpecificTag(4), 'matter');
    writer.putArray(ContextSpecificTag(5), Uint8List.fromList([1, 2, 3]));
    writer.putDouble(ContextSpecificTag(6), 2.25);
    writer.putNull(ContextSpecificTag(7));
    writer.endStructure();
    writer.validateTlv();

    final reader = TlvReader(writer.getEncoded());
    reader.enterStructure(AnonymousTag.instance);

    expect(reader.getLong(ContextSpecificTag(1)), -42);
    expect(reader.getULong(ContextSpecificTag(2)), 255);
    expect(reader.getBool(ContextSpecificTag(3)), isTrue);
    expect(reader.getUtf8String(ContextSpecificTag(4)), 'matter');
    expect(reader.getByteArray(ContextSpecificTag(5)), [1, 2, 3]);
    expect(reader.getDouble(ContextSpecificTag(6)), 2.25);
    reader.getNull(ContextSpecificTag(7));
    reader.exitContainer();
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('TLV array round-trips anonymous elements', () {
    final writer = TlvWriter();
    writer.startArray(AnonymousTag.instance);
    writer.put(AnonymousTag.instance, 1);
    writer.put(AnonymousTag.instance, 2);
    writer.endArray();
    writer.validateTlv();

    final reader = TlvReader(writer.getEncoded());
    reader.enterArray(AnonymousTag.instance);
    expect(reader.getLong(AnonymousTag.instance), 1);
    expect(reader.getLong(AnonymousTag.instance), 2);
    reader.exitContainer();
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('TLV reader reports truncated input', () {
    expect(
      () => TlvReader(Uint8List(0)).nextElement(),
      throwsA(isA<TlvParsingException>()),
    );
  });

  test('TLV writer rejects a top-level context tag', () {
    expect(
      () => TlvWriter().put(ContextSpecificTag(1), 1),
      throwsArgumentError,
    );
  });

  test('TLV writer reports an unclosed container', () {
    final writer = TlvWriter()..startStructure(AnonymousTag.instance);

    expect(() => writer.validateTlv(), throwsException);
  });
}
