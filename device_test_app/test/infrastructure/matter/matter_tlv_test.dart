import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('NodeLabel TLV round-trips as a UTF-8 string', () {
    final encoded = nodeLabelTlv('Lab lamp');

    expect(decodeMatterString(encoded), 'Lab lamp');
  });

  test('RemoveFabric TLV contains fabric index at context tag zero', () {
    final encoded = removeFabricCommandTlv(7);

    expect(decodeRemoveFabricIndex(encoded), 7);
    final reader = TlvReader(encoded)..enterStructure(AnonymousTag.instance);
    expect(reader.getUByte(ContextSpecificTag(0)), 7);
    expect(reader.isEndOfContainer(), isTrue);
  });

  test('OnOff TLV is an empty command structure', () {
    final encoded = emptyStructureTlv();
    final reader = TlvReader(encoded)..enterStructure(AnonymousTag.instance);

    expect(reader.isEndOfContainer(), isTrue);
    reader.exitContainer();
    expect(reader.isEndOfTlv(), isTrue);
  });

  test('malformed attribute TLV is wrapped in a typed error', () {
    expect(
      () => decodeMatterString(Uint8List.fromList([0x00])),
      throwsA(isA<MatterTlvException>()),
    );
  });
}
