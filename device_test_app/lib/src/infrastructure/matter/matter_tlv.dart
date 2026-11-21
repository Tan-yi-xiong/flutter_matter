import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

const int matterOnOffClusterId = 0x0006;
const int matterOnOffOffCommandId = 0x00;
const int matterOnOffOnCommandId = 0x01;
const int matterOnOffToggleCommandId = 0x02;
const int matterOnOffAttributeId = 0x0000;

const int matterBasicInformationClusterId = 0x0028;
const int matterNodeLabelAttributeId = 0x0005;

const int matterOperationalCredentialsClusterId = 0x003e;
const int matterCurrentFabricIndexAttributeId = 0x0005;
const int matterRemoveFabricCommandId = 0x000a;

class MatterTlvException implements Exception {
  MatterTlvException(this.message, [this.cause]);

  final String message;
  final Object? cause;

  @override
  String toString() => 'MatterTlvException: $message';
}

Uint8List emptyStructureTlv() {
  final writer = TlvWriter()
    ..startStructure(AnonymousTag.instance)
    ..endStructure();
  return _validated(writer);
}

Uint8List nodeLabelTlv(String label) {
  final writer = TlvWriter().putString(AnonymousTag.instance, label);
  return _validated(writer);
}

Uint8List removeFabricCommandTlv(int fabricIndex) {
  if (fabricIndex < 0 || fabricIndex > 0xff) {
    throw ArgumentError.value(
      fabricIndex,
      'fabricIndex',
      'Must be between 0 and 255',
    );
  }
  final writer = TlvWriter()
    ..startStructure(AnonymousTag.instance)
    ..putUnsigned(ContextSpecificTag(0), fabricIndex)
    ..endStructure();
  return _validated(writer);
}

String decodeMatterString(Uint8List tlv) {
  try {
    return TlvReader(tlv).getString(AnonymousTag.instance);
  } catch (error) {
    throw MatterTlvException('Unable to decode a Matter UTF-8 string', error);
  }
}

bool decodeMatterBool(Uint8List tlv) {
  try {
    return TlvReader(tlv).getBool(AnonymousTag.instance);
  } catch (error) {
    throw MatterTlvException('Unable to decode a Matter boolean', error);
  }
}

int decodeMatterUnsigned(Uint8List tlv) {
  try {
    return TlvReader(tlv).getULong(AnonymousTag.instance);
  } catch (error) {
    throw MatterTlvException(
      'Unable to decode a Matter unsigned integer',
      error,
    );
  }
}

int decodeRemoveFabricIndex(Uint8List tlv) {
  try {
    final reader = TlvReader(tlv)..enterStructure(AnonymousTag.instance);
    return reader.getUByte(ContextSpecificTag(0));
  } catch (error) {
    throw MatterTlvException('Unable to decode RemoveFabric arguments', error);
  }
}

Uint8List _validated(TlvWriter writer) {
  try {
    return writer.validateTlv().getEncoded();
  } catch (error) {
    throw MatterTlvException('Unable to encode Matter TLV', error);
  }
}
