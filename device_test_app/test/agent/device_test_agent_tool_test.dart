import 'dart:convert';
import 'dart:io';

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

  group('command argument sources', () {
    late Directory tempDir;

    setUp(() {
      tempDir = Directory.systemTemp.createTempSync('fm-agent-args-');
    });

    tearDown(() {
      if (tempDir.existsSync()) {
        tempDir.deleteSync(recursive: true);
      }
    });

    File writeArgsFile(String name, String contents) {
      final file = File('${tempDir.path}/$name');
      file.writeAsStringSync(contents);
      return file;
    }

    test('loads a JSON object from --args-file', () {
      final file = writeArgsFile('args.json', '{"mode":"quick","retries":2}');

      final args = resolveCommandArguments(argsFile: file.path);

      expect(args, <String, Object?>{'mode': 'quick', 'retries': 2});
    });

    test('resolves a relative --args-file path from the working directory', () {
      final name =
          '.fm-agent-args-${DateTime.now().microsecondsSinceEpoch}.json';
      final file = File(name);
      addTearDown(() {
        if (file.existsSync()) {
          file.deleteSync();
        }
      });
      file.writeAsStringSync('{"mode":"full"}');

      final args = resolveCommandArguments(argsFile: name);

      expect(args['mode'], 'full');
    });

    test('rejects --args-json together with --args-file', () {
      expect(
        () => resolveCommandArguments(
          argsJson: '{"mode":"quick"}',
          argsFile: '${tempDir.path}/args.json',
        ),
        throwsA(
          isA<CliFailure>()
              .having((failure) => failure.code, 'code', 'usage')
              .having((failure) => failure.exitCode, 'exit code', 2)
              .having(
                (failure) => failure.message,
                'message',
                allOf(contains('--args-json'), contains('--args-file')),
              ),
        ),
      );
    });

    test('defaults to an empty object when no source is supplied', () {
      expect(resolveCommandArguments(), isEmpty);
    });

    test('keeps --args-json object parsing unchanged', () {
      final args = resolveCommandArguments(argsJson: '{"mode":"full"}');

      expect(args, <String, Object?>{'mode': 'full'});
    });

    test('still rejects a non-object --args-json with a usage error', () {
      expect(
        () => resolveCommandArguments(argsJson: '[1,2,3]'),
        throwsA(
          isA<CliFailure>()
              .having((failure) => failure.code, 'code', 'usage')
              .having((failure) => failure.exitCode, 'exit code', 2)
              .having(
                (failure) => failure.message,
                'message',
                allOf(
                  startsWith('--args-json must be a JSON object.'),
                  contains('--args-file'),
                ),
              ),
        ),
      );
    });

    test('rejects a missing --args-file', () {
      expect(
        () => readCommandArgumentsFile('${tempDir.path}/missing.json'),
        throwsA(
          isA<CliFailure>()
              .having((failure) => failure.code, 'code', 'args_file_not_found')
              .having((failure) => failure.exitCode, 'exit code', 2),
        ),
      );
    });

    test('rejects a directory and a symbolic link as --args-file', () {
      expect(
        () => readCommandArgumentsFile(tempDir.path),
        throwsA(
          isA<CliFailure>().having(
            (failure) => failure.code,
            'code',
            'args_file_not_regular',
          ),
        ),
      );

      final target = writeArgsFile('target.json', '{"mode":"quick"}');
      final link = Link('${tempDir.path}/link.json');
      link.createSync(target.path);
      addTearDown(() {
        if (link.existsSync()) {
          link.deleteSync();
        }
      });

      expect(
        () => readCommandArgumentsFile(link.path),
        throwsA(
          isA<CliFailure>().having(
            (failure) => failure.code,
            'code',
            'args_file_not_regular',
          ),
        ),
      );
    });

    test('rejects invalid UTF-8 without leaking file contents', () {
      const sentinel = 'UTF8-SENTINEL-SECRET-VALUE';
      final bytes = <int>[
        ...utf8.encode('{"setup_code":"$sentinel"}'),
        0xC3,
        0x28,
      ];
      final file = File('${tempDir.path}/invalid-utf8.bin')
        ..writeAsBytesSync(bytes);

      final failure = _captureFailure(
        () => readCommandArgumentsFile(file.path),
      );

      expect(failure.code, 'args_file_encoding');
      expect(failure.exitCode, 2);
      _expectNoSentinel(failure, sentinel);
    });

    test('rejects invalid JSON without leaking file contents', () {
      const sentinel = 'JSON-SENTINEL-SECRET-VALUE';
      final file = writeArgsFile(
        'invalid-json.json',
        '{"setup_code":"$sentinel", oops}',
      );

      final failure = _captureFailure(
        () => readCommandArgumentsFile(file.path),
      );

      expect(failure.code, 'args_file_invalid_json');
      expect(failure.exitCode, 2);
      _expectNoSentinel(failure, sentinel);
    });

    test('rejects non-object JSON in --args-file', () {
      const cases = <String>['[1,2,3]', '"text"', 'null', '42'];
      for (final contents in cases) {
        final file = writeArgsFile('non-object.json', contents);

        expect(
          () => readCommandArgumentsFile(file.path),
          throwsA(
            isA<CliFailure>()
                .having(
                  (failure) => failure.code,
                  'code',
                  'args_file_invalid_json',
                )
                .having((failure) => failure.exitCode, 'exit code', 2),
          ),
          reason: 'contents: $contents',
        );
      }
    });
  });

  group('device test report validator', () {
    const pluginCommit = 'a1b2c3d4e5f6a7b8c9d0e1f2a3b4c5d6e7f8a9b0';

    test('accepts a minimal valid schema 2 report', () {
      final report = _validReport(pluginCommit: pluginCommit);

      expect(
        () => validateDeviceTestReportJson(
          report,
          expectedPluginCommit: pluginCommit,
        ),
        returnsNormally,
      );
    });

    test('rejects schema 1 reports', () {
      final report = _validReport(pluginCommit: pluginCommit)
        ..['schema_version'] = 1;

      final failure = _captureFailure(
        () => validateDeviceTestReportJson(
          report,
          expectedPluginCommit: pluginCommit,
        ),
      );

      expect(failure.code, 'invalid_report');
      expect(failure.message, contains('schema_version must be 2.'));
    });

    test('rejects BLE commissioning transport', () {
      final report = _validReport(pluginCommit: pluginCommit);
      final commissionee = _mutableCommissionee(report);
      commissionee['commissioning_transport'] = 'ble';

      final failure = _captureFailure(
        () => validateDeviceTestReportJson(
          report,
          expectedPluginCommit: pluginCommit,
        ),
      );

      expect(failure.code, 'invalid_report');
      expect(failure.message, contains('commissioning_transport must be ip.'));
    });

    test('rejects non-wifi network transports', () {
      for (final transport in const ['thread', 'unknown']) {
        final report = _validReport(pluginCommit: pluginCommit);
        final commissionee = _mutableCommissionee(report);
        commissionee['network_transport'] = transport;

        final failure = _captureFailure(
          () => validateDeviceTestReportJson(
            report,
            expectedPluginCommit: pluginCommit,
          ),
        );

        expect(failure.code, 'invalid_report', reason: transport);
        expect(
          failure.message,
          contains('network_transport must be wifi.'),
          reason: transport,
        );
      }
    });

    test('rejects virtual commissionees', () {
      final report = _validReport(pluginCommit: pluginCommit);
      final commissionee = _mutableCommissionee(report);
      commissionee['type'] = 'virtual';

      final failure = _captureFailure(
        () => validateDeviceTestReportJson(
          report,
          expectedPluginCommit: pluginCommit,
        ),
      );

      expect(failure.code, 'invalid_report');
      expect(failure.message, contains('commissionee.type must be real.'));
    });

    test('rejects the old BLE test ID set', () {
      const legacyIds = <String>[
        'build_install',
        'ble_discovery',
        'ble_commissioning',
        'operational_connect',
        'onoff_invoke',
        'onoff_subscription',
        'node_label_persistence',
        'app_restart',
        'factory_reset_recommission',
        'invalid_setup_passcode',
        'bluetooth_disabled',
        'invalid_wifi_password',
        'remove_fabric_ui',
      ];

      final report = _validReport(pluginCommit: pluginCommit);
      report['tests'] = <String, Object?>{
        for (final id in legacyIds)
          id: <String, Object?>{'status': 'passed', 'duration_ms': 1},
      };

      final failure = _captureFailure(
        () => validateDeviceTestReportJson(
          report,
          expectedPluginCommit: pluginCommit,
        ),
      );

      expect(failure.code, 'invalid_report');
      expect(
        failure.message,
        contains('tests has unexpected or missing keys.'),
      );
      final expected = failure.details['expected']! as List<dynamic>;
      expect(expected, contains('ip_discovery'));
      expect(expected, contains('ip_commissioning'));
    });
  });
}

CliFailure _captureFailure(Object? Function() action) {
  Object? thrown;
  try {
    action();
  } catch (error) {
    thrown = error;
  }
  expect(thrown, isA<CliFailure>());
  return thrown! as CliFailure;
}

void _expectNoSentinel(CliFailure failure, String sentinel) {
  expect(failure.code, isNot(contains(sentinel)));
  expect(failure.message, isNot(contains(sentinel)));
  expect(failure.toString(), isNot(contains(sentinel)));
  expect(jsonEncode(failure.details), isNot(contains(sentinel)));
  // Mirror the JSON output that _printFailure writes for this failure.
  final output = jsonEncode(<String, Object?>{
    'ok': false,
    'command': 'command',
    'error': <String, Object?>{
      'code': failure.code,
      'message': failure.message,
      'exit_code': failure.exitCode,
      'details': failure.details,
    },
  });
  expect(output, isNot(contains(sentinel)));
}

const List<String> _validReportTestIds = <String>[
  'build_install',
  'ip_discovery',
  'ip_commissioning',
  'operational_connect',
  'onoff_invoke',
  'onoff_subscription',
  'node_label_persistence',
  'app_restart',
  'factory_reset_recommission',
  'invalid_setup_passcode',
  'invalid_wifi_password',
  'remove_fabric_ui',
];

Map<String, Object?> _validReport({required String pluginCommit}) {
  return <String, Object?>{
    'schema_version': 2,
    'generated_at': '2026-01-01T00:00:00.000Z',
    'test_app': <String, Object?>{
      'name': 'flutter_matter_device_test_app',
      'version': '0.0.1',
      'commit': pluginCommit,
    },
    'plugin_commit': pluginCommit,
    'controller': <String, Object?>{
      'platform': 'android',
      'device_model': 'Test Phone',
      'os_version': '14',
      'app_build': 'debug',
    },
    'commissionee': <String, Object?>{
      'type': 'real',
      'model': 'Test Light',
      'firmware': '1.0.0',
      'commissioning_transport': 'ip',
      'network_transport': 'wifi',
      'state_change_method': 'commissionee_ui',
    },
    'summary': <String, Object?>{
      'result': 'passed',
      'passed': _validReportTestIds.length,
      'failed': 0,
      'not_run': 0,
    },
    'tests': <String, Object?>{
      for (final id in _validReportTestIds)
        id: <String, Object?>{'status': 'passed', 'duration_ms': 1},
    },
    'sanitization': <String, Object?>{'reviewed': true, 'policy_version': 1},
  };
}

Map<String, Object?> _mutableCommissionee(Map<String, Object?> report) {
  final commissionee = Map<String, Object?>.from(
    report['commissionee']! as Map<dynamic, dynamic>,
  );
  report['commissionee'] = commissionee;
  return commissionee;
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
