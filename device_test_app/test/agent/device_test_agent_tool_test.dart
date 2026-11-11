import 'package:flutter_test/flutter_test.dart';

import '../../../tool/device_test_agent.dart';

void main() {
  test('parses adb devices -l rows and attributes', () {
    final rows = parseAdbDeviceLines('''
List of devices attached
192.168.31.157:5555    device product:umi model:Mi_10 device:umi transport_id:16
USB123    unauthorized usb:1-1 transport_id:2
''');

    expect(rows, hasLength(2));
    expect(rows.first.id, '192.168.31.157:5555');
    expect(rows.first.state, 'device');
    expect(rows.first.attributes['model'], 'Mi_10');
    expect(rows.last.state, 'unauthorized');
  });

  test('never selects a device when --device is absent', () {
    final candidates = <DeviceCandidate>[
      _device('android-1', platform: 'android'),
      _device('ios-1', platform: 'ios'),
    ];

    expect(
      () => resolveDeviceSelection(candidates),
      throwsA(
        isA<DeviceSelectionRequired>()
            .having(
              (failure) => failure.code,
              'code',
              'device_selection_required',
            )
            .having(
              (failure) =>
                  (failure.details['candidates']! as List<dynamic>).length,
              'candidate count',
              2,
            ),
      ),
    );
  });

  test('still requires an explicit selection when only one device exists', () {
    expect(
      () => resolveDeviceSelection(<DeviceCandidate>[
        _device('android-1', platform: 'android'),
      ]),
      throwsA(isA<DeviceSelectionRequired>()),
    );
  });

  test(
    'resolves an explicit exact selectors and rejects ambiguous prefixes',
    () {
      final candidates = <DeviceCandidate>[
        _device('phone-abc-1', platform: 'android'),
        _device('phone-abc-2', platform: 'android'),
        _device('ios-1', platform: 'ios'),
      ];

      expect(
        resolveDeviceSelection(candidates, requested: 'ios-1').platform,
        'ios',
      );
      expect(
        () => resolveDeviceSelection(candidates, requested: 'phone-'),
        throwsA(isA<DeviceSelectionRequired>()),
      );
      expect(
        () => resolveDeviceSelection(candidates, requested: 'missing'),
        throwsA(isA<DeviceNotFound>()),
      );
    },
  );

  test(
    'builds Android force-stop and iOS terminate-existing restart commands',
    () {
      final android = buildAndroidRestartArguments(
        deviceId: 'android-1',
        androidPackage: 'com.example.test',
      );
      expect(
        android[0],
        containsAllInOrder(<String>['am', 'force-stop', 'com.example.test']),
      );
      expect(
        android[1],
        containsAllInOrder(<String>['monkey', '-p', 'com.example.test']),
      );

      final ios = buildIosRestartArguments(
        deviceId: 'ios-1',
        bundleId: 'com.example.testApp',
      );
      expect(ios, contains('--terminate-existing'));
      expect(ios, contains('com.example.testApp'));
    },
  );

  test('public candidate JSON omits the internal iOS UDID', () {
    final candidate = _device(
      'ios-uuid',
      platform: 'ios',
      iosUdid: '00008140-000A781C3613001C',
    );

    final json = candidate.toJson();
    expect(json['id'], 'ios-uuid');
    expect(json['short_id'], isNotEmpty);
    expect(json.containsKey('udid'), isFalse);
    expect(json.containsValue('00008140-000A781C3613001C'), isFalse);
  });
}

DeviceCandidate _device(
  String id, {
  required String platform,
  String? iosUdid,
}) {
  return DeviceCandidate(
    id: id,
    platform: platform,
    model: platform == 'ios' ? 'iPhone 16 Pro' : 'PH-1',
    osVersion: platform == 'ios' ? '18.1' : '12',
    name: id,
    state: platform == 'ios' ? 'paired' : 'device',
    connection: 'network',
    usable: true,
    iosUdid: iosUdid,
  );
}
