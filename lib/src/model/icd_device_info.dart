import 'dart:typed_data';

import 'json_decoding.dart';

/// Information about an ICD (Intermittently Connected Device) returned after
/// successful ICD registration during commissioning (Matter 1.2+).
class ICDDeviceInfo {
  /// The 16-byte symmetric key used for ICD check-ins.
  final Uint8List symmetricKey;

  /// Bitmask of trigger hints that describe how to wake up the ICD.
  final List<int> userActiveModeTriggerHint;

  /// Human-readable instruction that accompanies the trigger hint, if any.
  final String userActiveModeTriggerInstruction;

  /// The Node ID of the ICD device on the fabric.
  final int icdNodeId;

  /// The ICD counter value at the time of registration.
  final int icdCounter;

  /// The monitored subject used for check-in messages.
  final int monitoredSubject;

  /// The Fabric ID the ICD was registered on.
  final int fabricId;

  /// The index of the fabric on the commissioner.
  final int fabricIndex;

  ICDDeviceInfo({
    required this.symmetricKey,
    required this.userActiveModeTriggerHint,
    required this.userActiveModeTriggerInstruction,
    required this.icdNodeId,
    required this.icdCounter,
    required this.monitoredSubject,
    required this.fabricId,
    required this.fabricIndex,
  });

  factory ICDDeviceInfo.fromJson(Map<String, dynamic> json) {
    final root = decodeJsonObject(json, 'ICDDeviceInfo');
    final symmetricKey = decodeJsonBytes(
      root['symmetricKey'],
      'ICDDeviceInfo.symmetricKey',
    );
    if (symmetricKey.length != 16) {
      throw FormatException(
        'ICDDeviceInfo.symmetricKey must contain exactly 16 bytes; '
        'got ${symmetricKey.length}',
      );
    }
    return ICDDeviceInfo(
      symmetricKey: symmetricKey,
      userActiveModeTriggerHint: decodeJsonIntArray(
        root['userActiveModeTriggerHint'],
        'ICDDeviceInfo.userActiveModeTriggerHint',
      ),
      userActiveModeTriggerInstruction: decodeJsonNullableString(
            root['userActiveModeTriggerInstruction'],
            'ICDDeviceInfo.userActiveModeTriggerInstruction',
          ) ??
          '',
      icdNodeId: decodeJsonInt(root['icdNodeId'], 'ICDDeviceInfo.icdNodeId'),
      icdCounter: decodeJsonInt(root['icdCounter'], 'ICDDeviceInfo.icdCounter'),
      monitoredSubject: decodeJsonInt(
        root['monitoredSubject'],
        'ICDDeviceInfo.monitoredSubject',
      ),
      fabricId: decodeJsonInt(root['fabricId'], 'ICDDeviceInfo.fabricId'),
      fabricIndex:
          decodeJsonInt(root['fabricIndex'], 'ICDDeviceInfo.fabricIndex'),
    );
  }

  Map<String, dynamic> toJson() => {
        'symmetricKey': List<int>.from(symmetricKey),
        'userActiveModeTriggerHint': userActiveModeTriggerHint,
        'userActiveModeTriggerInstruction': userActiveModeTriggerInstruction,
        'icdNodeId': icdNodeId,
        'icdCounter': icdCounter,
        'monitoredSubject': monitoredSubject,
        'fabricId': fabricId,
        'fabricIndex': fabricIndex,
      };
}
