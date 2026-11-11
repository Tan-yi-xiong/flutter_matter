/// JSON CLI for Agent-driven flutter_matter device validation.
///
/// This file intentionally depends only on Dart SDK libraries. External
/// platform tools such as adb, xcrun, and libimobiledevice are invoked through
/// Process APIs when a command needs them.
library;

import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:math';

const String _protocolName = 'flutter_matter.device_test_agent';
const int _protocolVersion = 1;
const String defaultAndroidDeviceTestPackage = 'com.fluttermatter.devicetest';
const String defaultIosDeviceTestBundleId = 'com.fluttermatter.devicetest';
const int _defaultWebSocketPort = 8765;
const String _controlPath = '/control';
const String _agentPath = '/agent';
const List<String> _reportTestIds = <String>[
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

/// A CLI error that can be represented as structured JSON.
class CliFailure implements Exception {
  const CliFailure({
    required this.code,
    required this.message,
    this.exitCode = 1,
    this.details = const <String, Object?>{},
  });

  final String code;
  final String message;
  final int exitCode;
  final Map<String, Object?> details;

  @override
  String toString() => message;
}

/// The user must explicitly choose one connected device.
class DeviceSelectionRequired extends CliFailure {
  DeviceSelectionRequired({
    required super.message,
    required List<DeviceCandidate> candidates,
  }) : super(
          code: 'device_selection_required',
          exitCode: 3,
          details: <String, Object?>{
            'candidates': <Map<String, Object?>>[
              for (final candidate in candidates) candidate.toJson(),
            ],
          },
        );
}

/// An explicit device selector did not match a connected device.
class DeviceNotFound extends CliFailure {
  DeviceNotFound({
    required String requested,
    required List<DeviceCandidate> candidates,
  }) : super(
          code: 'device_not_found',
          message: 'No connected device matched "$requested".',
          exitCode: 3,
          details: <String, Object?>{
            'requested': requested,
            'candidates': <Map<String, Object?>>[
              for (final candidate in candidates) candidate.toJson(),
            ],
          },
        );
}

/// A connected, normalized device candidate.
class DeviceCandidate {
  const DeviceCandidate({
    required this.id,
    required this.platform,
    required this.model,
    required this.osVersion,
    required this.name,
    required this.state,
    required this.connection,
    required this.usable,
    this.iosUdid,
  });

  final String id;
  final String platform;
  final String model;
  final String osVersion;
  final String name;
  final String state;
  final String connection;
  final bool usable;

  /// Internal iOS UDID used by libimobiledevice. Never include in public JSON.
  final String? iosUdid;

  String get shortId {
    if (id.length <= 12) {
      return id;
    }
    return '${id.substring(0, 6)}...${id.substring(id.length - 4)}';
  }

  Map<String, Object?> toJson() => <String, Object?>{
        'id': id,
        'short_id': shortId,
        'platform': platform,
        'model': model,
        'os_version': osVersion,
        'name': name,
        'state': state,
        'connection': connection,
        'usable': usable,
      };
}

/// Arguments for the two Android process-restart steps.
List<List<String>> buildAndroidRestartArguments({
  required String deviceId,
  required String androidPackage,
}) {
  return <List<String>>[
    <String>['-s', deviceId, 'shell', 'am', 'force-stop', androidPackage],
    <String>[
      '-s',
      deviceId,
      'shell',
      'monkey',
      '-p',
      androidPackage,
      '-c',
      'android.intent.category.LAUNCHER',
      '1',
    ],
  ];
}

/// Arguments passed to `xcrun devicectl` for an iOS restart.
List<String> buildIosRestartArguments({
  required String deviceId,
  required String bundleId,
}) {
  return <String>[
    'devicectl',
    'device',
    'process',
    'launch',
    '--device',
    deviceId,
    '--terminate-existing',
    bundleId,
  ];
}

/// Result of discovering every supported device family.
class DeviceInventory {
  const DeviceInventory(
      {required this.devices, this.warnings = const <String>[]});

  final List<DeviceCandidate> devices;
  final List<String> warnings;
}

/// Injectable device discovery used by tests.
abstract interface class DeviceDiscovery {
  Future<DeviceInventory> discover();
}

/// Runs Android and iOS discovery independently so one tool failure does not
/// hide devices from the other platform.
class CompositeDeviceDiscovery implements DeviceDiscovery {
  CompositeDeviceDiscovery(this.discoveries);

  final List<DeviceDiscovery> discoveries;

  @override
  Future<DeviceInventory> discover() async {
    final results = await Future.wait<DeviceInventory>(
      discoveries.map((discovery) async {
        try {
          return await discovery.discover();
        } on Object catch (error) {
          return DeviceInventory(
            devices: const <DeviceCandidate>[],
            warnings: <String>['${discovery.runtimeType}: $error'],
          );
        }
      }),
    );
    final devices = <DeviceCandidate>[
      for (final result in results) ...result.devices,
    ]..sort((a, b) {
        final platform = a.platform.compareTo(b.platform);
        return platform != 0 ? platform : a.id.compareTo(b.id);
      });
    return DeviceInventory(
      devices: devices,
      warnings: <String>[for (final result in results) ...result.warnings],
    );
  }
}

/// One parsed row from `adb devices -l`.
class AdbDeviceRow {
  const AdbDeviceRow(
      {required this.id, required this.state, required this.attributes});

  final String id;
  final String state;
  final Map<String, String> attributes;
}

/// Parses `adb devices -l` output. Exposed for deterministic unit tests.
List<AdbDeviceRow> parseAdbDeviceLines(String output) {
  final rows = <AdbDeviceRow>[];
  for (final rawLine in const LineSplitter().convert(output)) {
    final line = rawLine.trim();
    if (line.isEmpty || line == 'List of devices attached') {
      continue;
    }
    final fields = line.split(RegExp(r'\s+'));
    if (fields.length < 2) {
      continue;
    }
    final attributes = <String, String>{};
    for (final field in fields.skip(2)) {
      final separator = field.indexOf(':');
      if (separator > 0) {
        attributes[field.substring(0, separator)] =
            field.substring(separator + 1);
      }
    }
    rows.add(AdbDeviceRow(
        id: fields.first, state: fields[1], attributes: attributes));
  }
  return rows;
}

/// Discovers Android devices through adb.
class AdbDeviceDiscovery implements DeviceDiscovery {
  @override
  Future<DeviceInventory> discover() async {
    final warnings = <String>[];
    final adb = _findExecutable('adb');
    if (adb == null) {
      return const DeviceInventory(
        devices: <DeviceCandidate>[],
        warnings: <String>['adb was not found on PATH.'],
      );
    }
    ProcessResult listing;
    try {
      listing = await _runProcess(
        adb,
        const <String>['devices', '-l'],
        timeout: const Duration(seconds: 10),
      );
    } on Object catch (error) {
      return DeviceInventory(
        devices: const <DeviceCandidate>[],
        warnings: <String>['adb discovery failed: $error'],
      );
    }
    if (listing.exitCode != 0) {
      warnings.add('adb devices failed: ${_trimProcessError(listing)}');
      return DeviceInventory(
          devices: const <DeviceCandidate>[], warnings: warnings);
    }

    final devices = <DeviceCandidate>[];
    for (final row in parseAdbDeviceLines(listing.stdout.toString())) {
      var model = row.attributes['model'] ?? 'Android device';
      var manufacturer = '';
      var osVersion = 'unknown';
      try {
        final properties = await _runProcess(
          adb,
          <String>['-s', row.id, 'shell', 'getprop'],
          timeout: const Duration(seconds: 5),
        );
        if (properties.exitCode == 0) {
          final values = _parseGetProp(properties.stdout.toString());
          manufacturer = values['ro.product.manufacturer'] ?? '';
          model = values['ro.product.model'] ?? model;
          osVersion = values['ro.build.version.release'] ?? osVersion;
        } else {
          warnings.add(
              'Could not read properties from ${row.id}: ${_trimProcessError(properties)}');
        }
      } on Object catch (error) {
        warnings.add('Could not read properties from ${row.id}: $error');
      }
      final displayName = manufacturer.isEmpty ? model : '$manufacturer $model';
      devices.add(
        DeviceCandidate(
          id: row.id,
          platform: 'android',
          model: model,
          osVersion: osVersion,
          name: displayName,
          state: row.state,
          connection: row.id.contains(':') ? 'network' : 'usb',
          usable: row.state == 'device',
        ),
      );
    }
    return DeviceInventory(devices: devices, warnings: warnings);
  }

  Map<String, String> _parseGetProp(String source) {
    final values = <String, String>{};
    final pattern = RegExp(r'^\[(.+?)\]: \[(.*)\]$');
    for (final line in const LineSplitter().convert(source)) {
      final match = pattern.firstMatch(line.trim());
      if (match != null) {
        values[match.group(1)!] = match.group(2)!;
      }
    }
    return values;
  }
}

/// Discovers iOS devices through CoreDevice, with libimobiledevice fallback.
class IosDeviceDiscovery implements DeviceDiscovery {
  @override
  Future<DeviceInventory> discover() async {
    final warnings = <String>[];
    final coreDevice = await _discoverWithCoreDevice(warnings);
    if (coreDevice.isNotEmpty) {
      return DeviceInventory(devices: coreDevice, warnings: warnings);
    }
    final fallback = await _discoverWithLibimobiledevice(warnings);
    return DeviceInventory(devices: fallback, warnings: warnings);
  }

  Future<List<DeviceCandidate>> _discoverWithCoreDevice(
      List<String> warnings) async {
    final xcrun = _findExecutable('xcrun');
    if (xcrun == null) {
      warnings.add('xcrun was not found on PATH.');
      return const <DeviceCandidate>[];
    }
    final temporaryDirectory =
        await Directory.systemTemp.createTemp('flutter_matter_devices.');
    final jsonFile = File('${temporaryDirectory.path}/devices.json');
    try {
      final result = await _runProcess(
        xcrun,
        <String>[
          'devicectl',
          'list',
          'devices',
          '--json-output',
          jsonFile.path
        ],
        timeout: const Duration(seconds: 30),
      );
      if (result.exitCode != 0 || !jsonFile.existsSync()) {
        warnings
            .add('devicectl discovery failed: ${_trimProcessError(result)}');
        return const <DeviceCandidate>[];
      }
      final decoded = jsonDecode(await jsonFile.readAsString());
      if (decoded is! Map) {
        warnings.add('devicectl returned a non-object JSON payload.');
        return const <DeviceCandidate>[];
      }
      final resultMap = _mapValue(decoded['result']);
      final rawDevices = resultMap?['devices'];
      if (rawDevices is! List) {
        warnings.add('devicectl JSON did not contain result.devices.');
        return const <DeviceCandidate>[];
      }
      final devices = <DeviceCandidate>[];
      for (final raw in rawDevices) {
        final device = _mapValue(raw);
        if (device == null) {
          continue;
        }
        final hardware = _mapValue(device['hardwareProperties']);
        final properties = _mapValue(device['deviceProperties']);
        final connection = _mapValue(device['connectionProperties']);
        final id = device['identifier'];
        if (id is! String || id.isEmpty) {
          continue;
        }
        final pairingState =
            connection?['pairingState']?.toString() ?? 'unknown';
        final tunnelState = connection?['tunnelState']?.toString() ?? 'unknown';
        final model = hardware?['marketingName']?.toString() ??
            hardware?['productType']?.toString() ??
            'iOS device';
        final osVersion =
            properties?['osVersionNumber']?.toString() ?? 'unknown';
        final name = properties?['name']?.toString() ??
            connection?['potentialHostnames']?.toString() ??
            model;
        devices.add(
          DeviceCandidate(
            id: id,
            platform: 'ios',
            model: model,
            osVersion: osVersion,
            name: name,
            state: tunnelState == 'connected' ? 'connected' : pairingState,
            connection: connection?['transportType']?.toString() ?? 'unknown',
            usable: pairingState == 'paired',
            iosUdid: hardware?['udid']?.toString(),
          ),
        );
      }
      return devices;
    } on Object catch (error) {
      warnings.add('devicectl discovery failed: $error');
      return const <DeviceCandidate>[];
    } finally {
      await temporaryDirectory.delete(recursive: true);
    }
  }

  Future<List<DeviceCandidate>> _discoverWithLibimobiledevice(
      List<String> warnings) async {
    final ideviceId = _findExecutable('idevice_id');
    if (ideviceId == null) {
      warnings.add('idevice_id was not found on PATH.');
      return const <DeviceCandidate>[];
    }
    final found = <String, String>{};
    for (final arguments in const <List<String>>[
      <String>['-l'],
      <String>['-n', '-l'],
    ]) {
      try {
        final result = await _runProcess(
          ideviceId,
          arguments,
          timeout: const Duration(seconds: 10),
        );
        if (result.exitCode == 0) {
          for (final line
              in const LineSplitter().convert(result.stdout.toString())) {
            final udid = line.trim();
            if (udid.isNotEmpty) {
              found[udid] = arguments.contains('-n') ? 'network' : 'usb';
            }
          }
        }
      } on Object catch (error) {
        warnings.add('idevice_id discovery failed: $error');
      }
    }

    final ideviceInfo = _findExecutable('ideviceinfo');
    final devices = <DeviceCandidate>[];
    for (final entry in found.entries) {
      var deviceName = 'iOS device';
      var model = 'iOS device';
      var osVersion = 'unknown';
      if (ideviceInfo != null) {
        deviceName = await _readIosProperty(
              ideviceInfo,
              entry.key,
              'DeviceName',
              network: entry.value == 'network',
            ) ??
            deviceName;
        model = await _readIosProperty(
              ideviceInfo,
              entry.key,
              'ProductType',
              network: entry.value == 'network',
            ) ??
            model;
        osVersion = await _readIosProperty(
              ideviceInfo,
              entry.key,
              'ProductVersion',
              network: entry.value == 'network',
            ) ??
            osVersion;
      }
      devices.add(
        DeviceCandidate(
          id: entry.key,
          platform: 'ios',
          model: model,
          osVersion: osVersion,
          name: deviceName,
          state: 'available',
          connection: entry.value,
          usable: true,
          iosUdid: entry.key,
        ),
      );
    }
    return devices;
  }

  Future<String?> _readIosProperty(
    String ideviceInfo,
    String udid,
    String key, {
    required bool network,
  }) async {
    for (final useNetwork in <bool>[network, !network]) {
      try {
        final result = await _runProcess(
          ideviceInfo,
          <String>[
            '-u',
            udid,
            if (useNetwork) '-n',
            '-k',
            key,
          ],
          timeout: const Duration(seconds: 8),
        );
        if (result.exitCode == 0) {
          final value = result.stdout.toString().trim();
          if (value.isNotEmpty) {
            return value;
          }
        }
      } on Object {
        // Try the alternate transport.
      }
    }
    return null;
  }
}

/// Resolves an explicit device selector without ever choosing a default.
DeviceCandidate resolveDeviceSelection(
  List<DeviceCandidate> candidates, {
  String? requested,
}) {
  final selector = requested?.trim();
  if (selector == null || selector.isEmpty) {
    throw DeviceSelectionRequired(
      message: 'An explicit --device selection is required.',
      candidates: candidates,
    );
  }
  final lower = selector.toLowerCase();
  var matches = candidates
      .where((candidate) => candidate.id.toLowerCase() == lower)
      .toList();
  if (matches.isEmpty) {
    matches = candidates
        .where((candidate) => candidate.name.toLowerCase() == lower)
        .toList();
  }
  if (matches.isEmpty) {
    matches = candidates
        .where((candidate) => candidate.id.toLowerCase().startsWith(lower))
        .toList();
  }
  if (matches.isEmpty) {
    throw DeviceNotFound(requested: selector, candidates: candidates);
  }
  if (matches.length > 1) {
    throw DeviceSelectionRequired(
      message: 'The selector "$selector" matched more than one device.',
      candidates: matches,
    );
  }
  final selected = matches.single;
  if (!selected.usable) {
    throw CliFailure(
      code: 'device_unavailable',
      message: 'The selected device is not ready: ${selected.state}.',
      exitCode: 3,
      details: <String, Object?>{'device': selected.toJson()},
    );
  }
  return selected;
}

DeviceDiscovery defaultDeviceDiscovery() {
  return CompositeDeviceDiscovery(<DeviceDiscovery>[
    AdbDeviceDiscovery(),
    IosDeviceDiscovery(),
  ]);
}

Future<void> main(List<String> arguments) async {
  final code = await _runCli(arguments);
  if (code != 0) {
    exitCode = code;
  }
}

Future<int> _runCli(List<String> arguments) async {
  if (arguments.isEmpty) {
    _printJson(<String, Object?>{
      'ok': false,
      'error': const <String, Object?>{
        'code': 'usage',
        'message':
            'Expected a command: devices, serve, status, wait, command, restart-app, screenshot, report, or stop.',
      },
    });
    return 2;
  }
  final command = arguments.first;
  try {
    switch (command) {
      case 'devices':
        await _commandDevices(arguments.sublist(1));
      case 'serve':
        await _commandServe(arguments.sublist(1));
      case 'status':
        await _commandStatus(arguments.sublist(1));
      case 'wait':
        await _commandWait(arguments.sublist(1));
      case 'command':
        await _commandGeneric(arguments.sublist(1));
      case 'restart-app':
        await _commandRestartApp(arguments.sublist(1));
      case 'screenshot':
        await _commandScreenshot(arguments.sublist(1));
      case 'report':
        await _commandReport(arguments.sublist(1));
      case 'stop':
        await _commandStop(arguments.sublist(1));
      default:
        throw CliFailure(
          code: 'usage',
          message: 'Unknown command "$command".',
          exitCode: 2,
        );
    }
    return 0;
  } on CliFailure catch (failure) {
    _printFailure(command, failure);
    return failure.exitCode;
  } on Object catch (error) {
    _printFailure(
      command,
      CliFailure(
        code: 'internal_error',
        message: error.toString(),
      ),
    );
    return 1;
  }
}

Future<void> _commandDevices(List<String> arguments) async {
  _Options.parse(arguments,
      valueOptions: const <String>{}, flags: const <String>{});
  final inventory = await defaultDeviceDiscovery().discover();
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'devices',
    'selection_required': true,
    'devices': <Map<String, Object?>>[
      for (final device in inventory.devices) device.toJson(),
    ],
    'warnings': inventory.warnings,
  });
}

Future<void> _commandServe(List<String> arguments) async {
  final options = _Options.parse(
    arguments,
    valueOptions: const <String>{
      'device',
      'port',
      'android-package',
      'ios-bundle-id',
      'artifact-dir',
    },
    flags: const <String>{'verbose'},
  );
  if (await _activeSessionExists()) {
    throw const CliFailure(
      code: 'session_already_running',
      message: 'A controller session is already running. Run stop first.',
      exitCode: 4,
    );
  }
  final inventory = await defaultDeviceDiscovery().discover();
  final selected = resolveDeviceSelection(
    inventory.devices,
    requested: options.values['device'],
  );
  final port = options.values['port'] == null
      ? _defaultWebSocketPort
      : _parsePort(options.values['port']!);
  final androidPackage =
      options.values['android-package'] ?? defaultAndroidDeviceTestPackage;
  final iosBundleId =
      options.values['ios-bundle-id'] ?? defaultIosDeviceTestBundleId;
  final root = _repoRoot();
  final artifactDirectory = options.values['artifact-dir'] == null
      ? Directory('${root.path}/build/device-test-agent')
      : Directory(_resolvePath(options.values['artifact-dir']!));
  final stateDirectory = _stateDirectory();
  await stateDirectory.create(recursive: true);
  final server = _AgentHostServer(
    selectedDevice: selected,
    websocketPort: port,
    androidPackage: androidPackage,
    iosBundleId: iosBundleId,
    artifactDirectory: artifactDirectory,
    stateFile: _sessionFile(),
    repoRoot: root,
    deviceInventoryWarnings: inventory.warnings,
    verbose: options.flags.contains('verbose'),
  );
  await server.start();
  await server.waitForShutdown();
}

class _Options {
  const _Options({required this.values, required this.flags});

  final Map<String, String> values;
  final Set<String> flags;

  static _Options parse(
    List<String> arguments, {
    required Set<String> valueOptions,
    required Set<String> flags,
  }) {
    final values = <String, String>{};
    final seenFlags = <String>{};
    var index = 0;
    while (index < arguments.length) {
      final token = arguments[index];
      if (!token.startsWith('--')) {
        throw CliFailure(
          code: 'usage',
          message: 'Unexpected positional argument "$token".',
          exitCode: 2,
        );
      }
      final withoutPrefix = token.substring(2);
      final equals = withoutPrefix.indexOf('=');
      final name =
          equals < 0 ? withoutPrefix : withoutPrefix.substring(0, equals);
      if (flags.contains(name)) {
        if (equals >= 0) {
          throw CliFailure(
            code: 'usage',
            message: 'Flag --$name does not accept a value.',
            exitCode: 2,
          );
        }
        if (!seenFlags.add(name)) {
          throw CliFailure(
            code: 'usage',
            message: 'Flag --$name was provided more than once.',
            exitCode: 2,
          );
        }
        index++;
        continue;
      }
      if (!valueOptions.contains(name)) {
        throw CliFailure(
          code: 'usage',
          message: 'Unknown option --$name.',
          exitCode: 2,
        );
      }
      if (values.containsKey(name)) {
        throw CliFailure(
          code: 'usage',
          message: 'Option --$name was provided more than once.',
          exitCode: 2,
        );
      }
      String value;
      if (equals >= 0) {
        value = withoutPrefix.substring(equals + 1);
        index++;
      } else {
        if (index + 1 >= arguments.length) {
          throw CliFailure(
            code: 'usage',
            message: 'Option --$name requires a value.',
            exitCode: 2,
          );
        }
        value = arguments[index + 1];
        index += 2;
      }
      if (value.isEmpty) {
        throw CliFailure(
          code: 'usage',
          message: 'Option --$name requires a non-empty value.',
          exitCode: 2,
        );
      }
      values[name] = value;
    }
    return _Options(values: values, flags: seenFlags);
  }
}

class _SessionDescriptor {
  const _SessionDescriptor({
    required this.pid,
    required this.controlPort,
    required this.websocketEndpoint,
    required this.artifactDirectory,
    required this.device,
    required this.raw,
  });

  final int pid;
  final int controlPort;
  final String websocketEndpoint;
  final String artifactDirectory;
  final Map<String, Object?> device;
  final Map<String, Object?> raw;
}

Future<void> _commandStatus(List<String> arguments) async {
  _Options.parse(arguments,
      valueOptions: const <String>{}, flags: const <String>{});
  final descriptor = _readSessionDescriptor();
  if (descriptor == null) {
    _printJson(
        <String, Object?>{'ok': true, 'command': 'status', 'active': false});
    return;
  }
  try {
    final response = await _postControl(
      descriptor,
      const <String, Object?>{'action': 'status'},
      timeout: const Duration(seconds: 5),
    );
    _printJson(<String, Object?>{
      'ok': true,
      'command': 'status',
      'active': true,
      'session': response,
    });
  } on Object {
    await _removeStaleSessionFile();
    _printJson(
        <String, Object?>{'ok': true, 'command': 'status', 'active': false});
  }
}

Future<void> _commandWait(List<String> arguments) async {
  final options = _Options.parse(
    arguments,
    valueOptions: const <String>{'for', 'value', 'timeout-seconds'},
    flags: const <String>{},
  );
  final descriptor = await _requireActiveSession();
  final condition = options.values['for'] ?? 'connected';
  if (!const <String>{'connected', 'disconnected', 'state', 'event', 'report'}
      .contains(condition)) {
    throw const CliFailure(
      code: 'usage',
      message:
          '--for must be connected, disconnected, state, event, or report.',
      exitCode: 2,
    );
  }
  if ((condition == 'state' || condition == 'event') &&
      options.values['value'] == null) {
    throw CliFailure(
      code: 'usage',
      message: '--value is required for --for $condition.',
      exitCode: 2,
    );
  }
  final timeoutSeconds =
      _parseSeconds(options.values['timeout-seconds'], defaultValue: 300);
  final response = await _postControl(
    descriptor,
    <String, Object?>{
      'action': 'wait',
      'condition': condition,
      'value': options.values['value'],
      'timeout_seconds': timeoutSeconds,
    },
    timeout: Duration(seconds: timeoutSeconds + 10),
  );
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'wait',
    'condition': condition,
    'result': response,
  });
}

/// Resolves runner command arguments from `--args-json` or `--args-file`.
///
/// At most one source may be supplied. When neither is supplied, the
/// arguments default to an empty JSON object. Arguments loaded from
/// `--args-file` never appear in error messages or CLI output, so setup
/// codes and network credentials cannot leak through diagnostics.
Map<Object?, Object?> resolveCommandArguments({
  String? argsJson,
  String? argsFile,
}) {
  if (argsJson != null && argsFile != null) {
    throw const CliFailure(
      code: 'usage',
      message: 'Provide only one of --args-json or --args-file.',
      exitCode: 2,
    );
  }
  if (argsFile != null) {
    return readCommandArgumentsFile(argsFile);
  }
  final decoded = jsonDecode(argsJson ?? '{}');
  if (decoded is! Map) {
    throw const CliFailure(
      code: 'usage',
      message: '--args-json must be a JSON object. Use --args-file <path> '
          'to load arguments from a UTF-8 JSON object file.',
      exitCode: 2,
    );
  }
  return decoded;
}

/// Reads runner command arguments from a UTF-8 JSON object file.
///
/// The path resolves relative to the current working directory. Missing
/// paths, directories, symbolic links, pipes, invalid UTF-8, invalid JSON,
/// and non-object JSON are rejected with stable error codes. The file
/// contents are never included in error messages or CLI output.
Map<Object?, Object?> readCommandArgumentsFile(String path) {
  final entityType = FileSystemEntity.typeSync(path, followLinks: false);
  if (entityType == FileSystemEntityType.notFound) {
    throw CliFailure(
      code: 'args_file_not_found',
      message: '--args-file does not exist: $path',
      exitCode: 2,
    );
  }
  if (entityType != FileSystemEntityType.file) {
    throw CliFailure(
      code: 'args_file_not_regular',
      message: '--args-file must be a regular file, not a directory, '
          'symbolic link, pipe, or special file: $path',
      exitCode: 2,
    );
  }
  final List<int> bytes;
  try {
    bytes = File(path).readAsBytesSync();
  } on FileSystemException {
    throw CliFailure(
      code: 'args_file_unreadable',
      message: '--args-file could not be read: $path',
      exitCode: 2,
    );
  }
  final String contents;
  try {
    contents = utf8.decode(bytes);
  } on FormatException {
    throw CliFailure(
      code: 'args_file_encoding',
      message: '--args-file must contain valid UTF-8 text: $path',
      exitCode: 2,
    );
  }
  try {
    final decoded = jsonDecode(contents);
    if (decoded is! Map) {
      throw CliFailure(
        code: 'args_file_invalid_json',
        message: '--args-file must contain a JSON object: $path',
        exitCode: 2,
      );
    }
    return decoded;
  } on FormatException {
    throw CliFailure(
      code: 'args_file_invalid_json',
      message: '--args-file must contain a JSON object: $path',
      exitCode: 2,
    );
  }
}

Future<void> _commandGeneric(List<String> arguments) async {
  final options = _Options.parse(
    arguments,
    valueOptions: const <String>{
      'name',
      'args-json',
      'args-file',
      'command-id',
      'timeout-seconds'
    },
    flags: const <String>{},
  );
  final name = options.values['name'];
  if (name == null || name.isEmpty) {
    throw const CliFailure(
      code: 'usage',
      message: '--name is required.',
      exitCode: 2,
    );
  }
  final decodedArguments = resolveCommandArguments(
    argsJson: options.values['args-json'],
    argsFile: options.values['args-file'],
  );
  final descriptor = await _requireActiveSession();
  final timeoutSeconds =
      _parseSeconds(options.values['timeout-seconds'], defaultValue: 120);
  final commandId = options.values['command-id'] ?? _newId('command');
  final response = await _postControl(
    descriptor,
    <String, Object?>{
      'action': 'command',
      'name': name,
      'arguments': _stringKeyedMap(decodedArguments),
      'command_id': commandId,
      'timeout_seconds': timeoutSeconds,
    },
    timeout: Duration(seconds: timeoutSeconds + 10),
  );
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'command',
    'command_id': commandId,
    'result': response,
  });
}

Future<void> _commandRestartApp(List<String> arguments) async {
  final options = _Options.parse(
    arguments,
    valueOptions: const <String>{
      'device',
      'android-package',
      'ios-bundle-id',
      'reconnect-timeout-seconds',
    },
    flags: const <String>{},
  );
  final reconnectTimeout = _parseSeconds(
      options.values['reconnect-timeout-seconds'],
      defaultValue: 30);
  final descriptor = _readSessionDescriptor();
  if (descriptor != null) {
    try {
      final response = await _postControl(
        descriptor,
        <String, Object?>{
          'action': 'restart_app',
          'android_package': options.values['android-package'],
          'ios_bundle_id': options.values['ios-bundle-id'],
          'reconnect_timeout_seconds': reconnectTimeout,
        },
        timeout: Duration(seconds: reconnectTimeout + 90),
      );
      _printJson(<String, Object?>{
        'ok': true,
        'command': 'restart-app',
        'result': response,
      });
      return;
    } on CliFailure catch (failure) {
      if (failure.code != 'no_active_session') {
        rethrow;
      }
    } on Object {
      await _removeStaleSessionFile();
    }
  }

  final inventory = await defaultDeviceDiscovery().discover();
  final selected = resolveDeviceSelection(
    inventory.devices,
    requested: options.values['device'],
  );
  final result = await _restartDevice(
    selected,
    androidPackage:
        options.values['android-package'] ?? defaultAndroidDeviceTestPackage,
    iosBundleId:
        options.values['ios-bundle-id'] ?? defaultIosDeviceTestBundleId,
  );
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'restart-app',
    'result': result,
  });
}

Future<void> _commandScreenshot(List<String> arguments) async {
  final options = _Options.parse(
    arguments,
    valueOptions: const <String>{'device', 'output', 'timeout-seconds'},
    flags: const <String>{},
  );
  final timeoutSeconds =
      _parseSeconds(options.values['timeout-seconds'], defaultValue: 30);
  final outputPath = options.values['output'] == null
      ? '${_repoRoot().path}/build/device-test-agent/screenshots/screenshot-${_timestampForFile()}.png'
      : _resolvePath(options.values['output']!);
  final descriptor = _readSessionDescriptor();
  if (descriptor != null) {
    try {
      final response = await _postControl(
        descriptor,
        <String, Object?>{
          'action': 'screenshot',
          'output': outputPath,
          'timeout_seconds': timeoutSeconds,
        },
        timeout: Duration(seconds: timeoutSeconds + 20),
      );
      _printJson(<String, Object?>{
        'ok': true,
        'command': 'screenshot',
        'result': response,
      });
      return;
    } on CliFailure {
      rethrow;
    } on Object {
      await _removeStaleSessionFile();
    }
  }

  final inventory = await defaultDeviceDiscovery().discover();
  final selected = resolveDeviceSelection(
    inventory.devices,
    requested: options.values['device'],
  );
  final result = await _capturePlatformScreenshot(selected, outputPath);
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'screenshot',
    'result': result,
  });
}

Future<void> _commandReport(List<String> arguments) async {
  final options = _Options.parse(
    arguments,
    valueOptions: const <String>{'output-dir', 'timeout-seconds'},
    flags: const <String>{},
  );
  final descriptor = await _requireActiveSession();
  final timeoutSeconds =
      _parseSeconds(options.values['timeout-seconds'], defaultValue: 120);
  final response = await _postControl(
    descriptor,
    <String, Object?>{
      'action': 'report',
      'output_dir': options.values['output-dir'],
      'timeout_seconds': timeoutSeconds,
    },
    timeout: Duration(seconds: timeoutSeconds + 20),
  );
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'report',
    'result': response,
  });
}

Future<void> _commandStop(List<String> arguments) async {
  _Options.parse(arguments,
      valueOptions: const <String>{}, flags: const <String>{});
  final descriptor = await _requireActiveSession();
  final response = await _postControl(
    descriptor,
    const <String, Object?>{'action': 'stop'},
    timeout: const Duration(seconds: 10),
  );
  _printJson(<String, Object?>{
    'ok': true,
    'command': 'stop',
    'result': response,
  });
}

Future<Map<String, Object?>> _restartDevice(
  DeviceCandidate device, {
  required String androidPackage,
  required String iosBundleId,
}) async {
  switch (device.platform) {
    case 'android':
      final adb = _requireExecutable('adb');
      final androidArguments = buildAndroidRestartArguments(
        deviceId: device.id,
        androidPackage: androidPackage,
      );
      final stop = await _runProcess(
        adb,
        androidArguments[0],
        timeout: const Duration(seconds: 30),
      );
      if (stop.exitCode != 0) {
        throw CliFailure(
          code: 'restart_failed',
          message:
              'adb could not force-stop $androidPackage: ${_trimProcessError(stop)}',
        );
      }
      final launch = await _runProcess(
        adb,
        androidArguments[1],
        timeout: const Duration(seconds: 30),
      );
      if (launch.exitCode != 0) {
        throw CliFailure(
          code: 'restart_failed',
          message:
              'adb could not launch $androidPackage: ${_trimProcessError(launch)}',
        );
      }
      return <String, Object?>{
        'device_id': device.id,
        'platform': 'android',
        'android_package': androidPackage,
        'force_stopped': true,
        'launched': true,
      };
    case 'ios':
      final xcrun = _requireExecutable('xcrun');
      final launch = await _runProcess(
        xcrun,
        buildIosRestartArguments(deviceId: device.id, bundleId: iosBundleId),
        timeout: const Duration(seconds: 90),
      );
      if (launch.exitCode != 0) {
        throw CliFailure(
          code: 'restart_failed',
          message:
              'devicectl could not launch $iosBundleId: ${_trimProcessError(launch)}',
        );
      }
      return <String, Object?>{
        'device_id': device.id,
        'platform': 'ios',
        'ios_bundle_id': iosBundleId,
        'terminate_existing': true,
        'launched': true,
      };
    default:
      throw CliFailure(
        code: 'unsupported_platform',
        message: 'Unsupported device platform: ${device.platform}',
      );
  }
}

Future<Map<String, Object?>> _capturePlatformScreenshot(
  DeviceCandidate device,
  String outputPath,
) async {
  final file = File(outputPath);
  await file.parent.create(recursive: true);
  switch (device.platform) {
    case 'android':
      final adb = _requireExecutable('adb');
      final process = await Process.start(
        adb,
        <String>['-s', device.id, 'exec-out', 'screencap', '-p'],
      );
      final stderrFuture = process.stderr.transform(utf8.decoder).join();
      final sink = file.openWrite();
      try {
        await process.stdout.pipe(sink);
        final exit = await process.exitCode;
        final stderrText = await stderrFuture;
        if (exit != 0) {
          await file.delete().catchError((_) => file);
          throw CliFailure(
            code: 'screenshot_failed',
            message: 'adb screencap failed: ${stderrText.trim()}',
          );
        }
      } finally {
        await sink.close();
      }
      return <String, Object?>{
        'path': file.absolute.path,
        'source': 'android_adb',
        'device_id': device.id,
      };
    case 'ios':
      final ideviceScreenshot = _requireExecutable('idevicescreenshot');
      final target = device.iosUdid ?? device.id;
      final result = await _runProcess(
        ideviceScreenshot,
        <String>['-u', target, file.absolute.path],
        timeout: const Duration(seconds: 30),
      );
      if (result.exitCode != 0 || !file.existsSync()) {
        throw CliFailure(
          code: 'screenshot_failed',
          message: 'idevicescreenshot failed: ${_trimProcessError(result)}',
        );
      }
      return <String, Object?>{
        'path': file.absolute.path,
        'source': 'idevicescreenshot',
        'device_id': device.id,
      };
    default:
      throw CliFailure(
        code: 'unsupported_platform',
        message: 'Unsupported device platform: ${device.platform}',
      );
  }
}

Future<_SessionDescriptor> _requireActiveSession() async {
  final descriptor = _readSessionDescriptor();
  if (descriptor == null) {
    throw const CliFailure(
      code: 'no_active_session',
      message: 'No controller session is running. Start serve first.',
      exitCode: 4,
    );
  }
  try {
    await _postControl(
      descriptor,
      const <String, Object?>{'action': 'status'},
      timeout: const Duration(seconds: 3),
    );
    return descriptor;
  } on Object {
    await _removeStaleSessionFile();
    throw const CliFailure(
      code: 'no_active_session',
      message: 'No controller session is running. Start serve first.',
      exitCode: 4,
    );
  }
}

Future<bool> _activeSessionExists() async {
  final descriptor = _readSessionDescriptor();
  if (descriptor == null) {
    return false;
  }
  try {
    await _postControl(
      descriptor,
      const <String, Object?>{'action': 'status'},
      timeout: const Duration(seconds: 3),
    );
    return true;
  } on Object {
    await _removeStaleSessionFile();
    return false;
  }
}

_SessionDescriptor? _readSessionDescriptor() {
  final file = _sessionFile();
  if (!file.existsSync()) {
    return null;
  }
  try {
    final decoded = jsonDecode(file.readAsStringSync());
    if (decoded is! Map) {
      return null;
    }
    final raw = _stringKeyedMap(decoded);
    final pid = raw['pid'];
    final controlPort = raw['control_port'];
    if (pid is! int || controlPort is! int) {
      return null;
    }
    return _SessionDescriptor(
      pid: pid,
      controlPort: controlPort,
      websocketEndpoint: raw['websocket_endpoint']?.toString() ?? '',
      artifactDirectory: raw['artifact_directory']?.toString() ?? '',
      device: _mapValue(raw['device']) ?? const <String, Object?>{},
      raw: raw,
    );
  } on Object {
    return null;
  }
}

Future<void> _removeStaleSessionFile() async {
  final file = _sessionFile();
  if (await file.exists()) {
    await file.delete();
  }
}

Future<Map<String, Object?>> _postControl(
  _SessionDescriptor descriptor,
  Map<String, Object?> body, {
  required Duration timeout,
}) async {
  final client = HttpClient()..connectionTimeout = const Duration(seconds: 3);
  try {
    final request = await client
        .postUrl(Uri.parse(
            'http://127.0.0.1:${descriptor.controlPort}$_controlPath'))
        .timeout(timeout);
    request.headers.contentType = ContentType.json;
    request.write(jsonEncode(body));
    final response = await request.close().timeout(timeout);
    final text = await response.transform(utf8.decoder).join();
    final decoded = jsonDecode(text);
    if (decoded is! Map) {
      throw const CliFailure(
        code: 'control_error',
        message: 'Control server returned a non-object response.',
      );
    }
    final map = _stringKeyedMap(decoded);
    if (map['ok'] != true) {
      final error = _mapValue(map['error']) ?? const <String, Object?>{};
      throw CliFailure(
        code: error['code']?.toString() ?? 'control_error',
        message: error['message']?.toString() ?? 'Control request failed.',
        exitCode: error['exit_code'] is int ? error['exit_code']! as int : 1,
        details: error['details'] is Map
            ? _stringKeyedMap(error['details']! as Map)
            : const <String, Object?>{},
      );
    }
    return _mapValue(map['result']) ?? const <String, Object?>{};
  } finally {
    client.close(force: true);
  }
}

void _printFailure(String command, CliFailure failure) {
  _printJson(<String, Object?>{
    'ok': false,
    'command': command,
    'error': <String, Object?>{
      'code': failure.code,
      'message': failure.message,
      'exit_code': failure.exitCode,
      'details': failure.details,
    },
  });
}

void _printJson(Map<String, Object?> value) {
  stdout.writeln(jsonEncode(value));
}

Directory _repoRoot() {
  var directory = File.fromUri(Platform.script).parent;
  if (directory.path.endsWith('${Platform.pathSeparator}tool')) {
    directory = directory.parent;
  }
  if (File('${directory.path}${Platform.pathSeparator}pubspec.yaml')
      .existsSync()) {
    return directory.absolute;
  }
  return Directory.current.absolute;
}

Directory _stateDirectory() =>
    Directory('${_repoRoot().path}/.dart_tool/device_test_agent');

File _sessionFile() => File('${_stateDirectory().path}/session.json');

String _resolvePath(String path) {
  final file = File(path);
  if (file.isAbsolute) {
    return file.absolute.path;
  }
  return '${_repoRoot().path}/$path';
}

int _parsePort(String source) {
  final value = int.tryParse(source);
  if (value == null || value < 1 || value > 65535) {
    throw const CliFailure(
      code: 'usage',
      message: '--port must be an integer from 1 to 65535.',
      exitCode: 2,
    );
  }
  return value;
}

int _parseSeconds(String? source, {required int defaultValue}) {
  if (source == null) {
    return defaultValue;
  }
  final value = int.tryParse(source);
  if (value == null || value < 1 || value > 3600) {
    throw const CliFailure(
      code: 'usage',
      message: 'Timeout values must be integers from 1 to 3600 seconds.',
      exitCode: 2,
    );
  }
  return value;
}

String _newId(String prefix) {
  final random = Random.secure();
  final bytes = List<int>.generate(16, (_) => random.nextInt(256));
  return '$prefix-${bytes.map((value) => value.toRadixString(16).padLeft(2, '0')).join()}';
}

String _timestampForFile() {
  return DateTime.now()
      .toUtc()
      .toIso8601String()
      .replaceAll(':', '-')
      .replaceAll('.', '-');
}

String _requireExecutable(String name) {
  final executable = _findExecutable(name);
  if (executable == null) {
    throw CliFailure(
      code: 'tool_not_found',
      message: '$name was not found on PATH.',
    );
  }
  return executable;
}

String? _findExecutable(String name) {
  if (name.contains(Platform.pathSeparator)) {
    return File(name).existsSync() ? name : null;
  }
  final path = Platform.environment['PATH'];
  if (path == null) {
    return null;
  }
  for (final directory in path.split(':')) {
    final candidate = File('$directory/$name');
    if (candidate.existsSync()) {
      return candidate.path;
    }
  }
  return null;
}

Future<ProcessResult> _runProcess(
  String executable,
  List<String> arguments, {
  required Duration timeout,
}) async {
  try {
    return await Process.run(
      executable,
      arguments,
      runInShell: false,
    ).timeout(timeout);
  } on TimeoutException {
    throw CliFailure(
      code: 'tool_timeout',
      message: '$executable timed out after ${timeout.inSeconds} seconds.',
    );
  } on ProcessException catch (error) {
    throw CliFailure(
      code: 'process_failed',
      message: 'Could not run $executable: ${error.message}',
    );
  }
}

String _trimProcessError(ProcessResult result) {
  final stderrText = result.stderr.toString().trim();
  if (stderrText.isNotEmpty) {
    return stderrText.length > 800
        ? '${stderrText.substring(0, 800)}...'
        : stderrText;
  }
  final stdoutText = result.stdout.toString().trim();
  if (stdoutText.isNotEmpty) {
    return stdoutText.length > 800
        ? '${stdoutText.substring(0, 800)}...'
        : stdoutText;
  }
  return 'exit code ${result.exitCode}';
}

Map<String, Object?>? _mapValue(Object? value) {
  if (value is Map) {
    return _stringKeyedMap(value);
  }
  return null;
}

Map<String, Object?> _stringKeyedMap(Map<Object?, Object?> source) {
  return <String, Object?>{
    for (final entry in source.entries) entry.key.toString(): entry.value,
  };
}

class _AgentHostServer {
  _AgentHostServer({
    required this.selectedDevice,
    required this.websocketPort,
    required this.androidPackage,
    required this.iosBundleId,
    required this.artifactDirectory,
    required this.stateFile,
    required this.repoRoot,
    required this.deviceInventoryWarnings,
    required this.verbose,
  }) : sessionId = _newId('session');

  final DeviceCandidate selectedDevice;
  final int websocketPort;
  final String androidPackage;
  final String iosBundleId;
  final Directory artifactDirectory;
  final File stateFile;
  final Directory repoRoot;
  final List<String> deviceInventoryWarnings;
  final bool verbose;
  final String sessionId;

  late final HttpServer _appServer;
  late final HttpServer _controlServer;
  final Completer<void> _shutdownCompleter = Completer<void>();
  final List<StreamSubscription<ProcessSignal>> _signalSubscriptions =
      <StreamSubscription<ProcessSignal>>[];

  WebSocket? _appSocket;
  StreamSubscription<dynamic>? _appSubscription;
  Map<String, Object?>? _hello;
  Map<String, Object?>? _latestState;
  final List<Map<String, Object?>> _events = <Map<String, Object?>>[];
  Map<String, Object?>? _lastCommandResult;
  Map<String, Object?>? _lastError;
  Map<String, Object?>? _lastScreenshot;
  Map<String, Object?>? _lastReport;
  _PendingCommand? _pendingCommand;
  String? _appInstanceId;
  bool _helloThisConnection = false;
  bool _appConnected = false;
  bool _shutdownRequested = false;
  int _lastAppSequence = 0;
  int _helloGeneration = 0;
  int _hostSequence = 0;
  DateTime? _startedAt;
  DateTime? _connectedAt;
  DateTime? _lastDisconnectAt;
  String? _lastConnectedDeviceName;
  String? _websocketEndpoint;
  int? _controlPort;

  Future<void> start() async {
    _startedAt = DateTime.now().toUtc();
    await artifactDirectory.create(recursive: true);
    try {
      _appServer = await HttpServer.bind(
        InternetAddress.anyIPv4,
        websocketPort,
        shared: false,
      );
      _controlServer = await HttpServer.bind(
        InternetAddress.loopbackIPv4,
        0,
        shared: false,
      );
    } on SocketException catch (error) {
      throw CliFailure(
        code: 'server_bind_failed',
        message: 'Could not start the agent host: ${error.message}',
      );
    }
    _controlPort = _controlServer.port;
    final lanAddress = await _findLanAddress();
    _websocketEndpoint = 'ws://$lanAddress:$websocketPort$_agentPath';
    _appServer.listen(_handleAppHttpRequest);
    _controlServer.listen(_handleControlHttpRequest);
    _installSignalHandlers();
    await _writeSessionFile();
    _printJson(<String, Object?>{
      'ok': true,
      'command': 'serve',
      'session': <String, Object?>{
        'session_id': sessionId,
        'pid': pid,
        'selected_device': selectedDevice.toJson(),
        'websocket_endpoint': _websocketEndpoint,
        'control_port': _controlPort,
        'artifact_directory': artifactDirectory.absolute.path,
        'protocol': <String, Object?>{
          'name': _protocolName,
          'version': _protocolVersion,
        },
        'warnings': deviceInventoryWarnings,
      },
    });
  }

  Future<void> waitForShutdown() => _shutdownCompleter.future;

  Future<void> _writeSessionFile() async {
    await stateFile.parent.create(recursive: true);
    await stateFile.writeAsString(
      const JsonEncoder.withIndent('  ').convert(<String, Object?>{
        'pid': pid,
        'session_id': sessionId,
        'control_port': _controlPort,
        'websocket_endpoint': _websocketEndpoint,
        'artifact_directory': artifactDirectory.absolute.path,
        'device': selectedDevice.toJson(),
        'protocol': <String, Object?>{
          'name': _protocolName,
          'version': _protocolVersion,
        },
        'started_at': _startedAt?.toIso8601String(),
      }),
      flush: true,
    );
  }

  void _installSignalHandlers() {
    for (final signal in <ProcessSignal>[
      ProcessSignal.sigint,
      ProcessSignal.sigterm
    ]) {
      try {
        _signalSubscriptions.add(
          signal.watch().listen((_) => unawaited(shutdown())),
        );
      } on Object {
        // A platform may not expose one of the signals.
      }
    }
  }

  Future<void> _handleAppHttpRequest(HttpRequest request) async {
    if (request.uri.path != _agentPath) {
      request.response.statusCode = HttpStatus.notFound;
      request.response.headers.contentType = ContentType.json;
      request.response.write(
        jsonEncode(<String, Object?>{
          'ok': false,
          'error': 'Unknown path. Use $_agentPath for the WebSocket.',
        }),
      );
      await request.response.close();
      return;
    }
    if (!WebSocketTransformer.isUpgradeRequest(request)) {
      request.response.statusCode = HttpStatus.upgradeRequired;
      request.response.headers.contentType = ContentType.json;
      request.response.write(
        jsonEncode(<String, Object?>{
          'ok': false,
          'error': 'A WebSocket upgrade is required.',
          'endpoint': _websocketEndpoint,
        }),
      );
      await request.response.close();
      return;
    }

    if (_appSocket != null) {
      final rejected = await WebSocketTransformer.upgrade(request);
      rejected.add(
        jsonEncode(
          _encodeEnvelope(
            type: 'error',
            payload: const <String, Object?>{
              'code': 'session_busy',
              'message': 'One controller session is already connected.',
              'retryable': true,
              'details': <String, Object?>{},
            },
          ),
        ),
      );
      await rejected.close(WebSocketStatus.goingAway, 'session_busy');
      return;
    }

    final socket = await WebSocketTransformer.upgrade(request);
    socket.pingInterval = const Duration(seconds: 20);
    _attachAppSocket(socket);
  }

  void _attachAppSocket(WebSocket socket) {
    _appSocket = socket;
    _helloThisConnection = false;
    _appConnected = false;
    _appSubscription = socket.listen(
      (data) => _handleAppData(socket, data),
      onError: (Object error, StackTrace stackTrace) =>
          _handleAppDisconnect(socket),
      onDone: () => _handleAppDisconnect(socket),
      cancelOnError: true,
    );
  }

  void _handleAppDisconnect(WebSocket socket) {
    if (!identical(_appSocket, socket)) {
      return;
    }
    _appSocket = null;
    _helloThisConnection = false;
    _appConnected = false;
    _lastDisconnectAt = DateTime.now().toUtc();
    final subscription = _appSubscription;
    _appSubscription = null;
    unawaited(subscription?.cancel());
    _failPending('app_disconnected', 'The test app disconnected.');
  }

  void _handleAppData(WebSocket socket, Object? data) {
    if (!identical(_appSocket, socket)) {
      return;
    }
    _Envelope envelope;
    try {
      final text = switch (data) {
        String value => value,
        List<int> value => utf8.decode(value),
        _ => throw const FormatException('Expected a UTF-8 text frame.'),
      };
      envelope = _Envelope.fromJsonString(text);
    } on Object catch (error) {
      _sendProtocolError(
        code: 'invalid_message',
        message: error.toString(),
      );
      return;
    }

    if (envelope.type == 'hello') {
      _handleHello(envelope);
      return;
    }
    if (!_helloThisConnection) {
      _sendProtocolError(
        code: 'hello_required',
        message: 'The app must send hello before other messages.',
        commandId: envelope.commandId,
      );
      return;
    }
    if (!_acceptAppSequence(envelope.sequence)) {
      _sendProtocolError(
        code: 'out_of_order_sequence',
        message: 'App sequence must increase for every message.',
        commandId: envelope.commandId,
        details: <String, Object?>{
          'received': envelope.sequence,
          'last': _lastAppSequence,
        },
      );
      return;
    }

    switch (envelope.type) {
      case 'state':
        _handleState(envelope);
      case 'event':
        _handleEvent(envelope);
      case 'command_result':
        _handleCommandResult(envelope);
      case 'screenshot':
        _handleScreenshot(envelope);
      case 'report':
        _handleReport(envelope);
      case 'error':
        _handleAppError(envelope);
      default:
        _sendProtocolError(
          code: 'unsupported_message_type',
          message: 'The host does not accept ${envelope.type} messages.',
          commandId: envelope.commandId,
        );
    }
  }

  void _handleHello(_Envelope envelope) {
    if (_helloThisConnection) {
      _sendProtocolError(
        code: 'duplicate_hello',
        message: 'Only one hello is allowed per WebSocket connection.',
      );
      return;
    }
    final instanceId = envelope.payload['instance_id'];
    if (instanceId is! String || instanceId.isEmpty) {
      _sendProtocolError(
        code: 'invalid_hello',
        message: 'hello.instance_id must be a non-empty string.',
      );
      return;
    }
    if (_appInstanceId != instanceId) {
      _appInstanceId = instanceId;
      _lastAppSequence = 0;
      _latestState = null;
      _events.clear();
      _lastCommandResult = null;
      _lastError = null;
      _lastScreenshot = null;
      _lastReport = null;
    }
    if (!_acceptAppSequence(envelope.sequence)) {
      _sendProtocolError(
        code: 'out_of_order_sequence',
        message: 'hello sequence must increase for this app instance.',
        details: <String, Object?>{
          'received': envelope.sequence,
          'last': _lastAppSequence,
        },
      );
      return;
    }
    final controllerPlatform = envelope.payload['controller_platform'];
    if (controllerPlatform != selectedDevice.platform) {
      _sendProtocolError(
        code: 'device_mismatch',
        message:
            'The app controller platform does not match the selected device.',
        details: <String, Object?>{
          'selected': selectedDevice.platform,
          'reported': controllerPlatform,
        },
      );
      return;
    }
    if (envelope.payload['plugin_commit'] is! String ||
        envelope.payload['device_model'] is! String ||
        envelope.payload['os_version'] is! String) {
      _sendProtocolError(
        code: 'invalid_hello',
        message: 'hello is missing plugin or controller metadata.',
      );
      return;
    }
    _hello = envelope.payload;
    _helloThisConnection = true;
    _appConnected = true;
    _helloGeneration++;
    _connectedAt = DateTime.now().toUtc();
    _lastConnectedDeviceName = envelope.payload['device_model']?.toString();
  }

  bool _acceptAppSequence(int sequence) {
    if (sequence <= _lastAppSequence) {
      return false;
    }
    _lastAppSequence = sequence;
    return true;
  }

  void _handleState(_Envelope envelope) {
    if (envelope.payload['status'] is! String) {
      _sendProtocolError(
        code: 'invalid_state',
        message: 'state.status must be a string.',
        commandId: envelope.commandId,
      );
      return;
    }
    _latestState = <String, Object?>{
      'sequence': envelope.sequence,
      'message_id': envelope.messageId,
      'sent_at': envelope.sentAt.toIso8601String(),
      ...envelope.payload,
    };
  }

  void _handleEvent(_Envelope envelope) {
    if (envelope.payload['kind'] is! String ||
        envelope.payload['message'] is! String) {
      _sendProtocolError(
        code: 'invalid_event',
        message: 'event.kind and event.message are required strings.',
        commandId: envelope.commandId,
      );
      return;
    }
    _events.add(<String, Object?>{
      'sequence': envelope.sequence,
      'message_id': envelope.messageId,
      'sent_at': envelope.sentAt.toIso8601String(),
      ...envelope.payload,
    });
    while (_events.length > 200) {
      _events.removeAt(0);
    }
  }

  void _handleCommandResult(_Envelope envelope) {
    final commandId = envelope.commandId;
    final status = envelope.payload['status'];
    if (commandId == null) {
      _sendProtocolError(
        code: 'missing_command_id',
        message: 'command_result requires command_id.',
      );
      return;
    }
    if (status is! String ||
        !const <String>{'completed', 'failed', 'duplicate'}.contains(status)) {
      _sendProtocolError(
        code: 'invalid_command_result',
        message:
            'command_result.status must be completed, failed, or duplicate.',
        commandId: commandId,
      );
      return;
    }
    if (status == 'failed' && envelope.payload['error_code'] is! String) {
      _sendProtocolError(
        code: 'invalid_command_result',
        message: 'A failed command_result requires error_code.',
        commandId: commandId,
      );
      return;
    }
    final stored = <String, Object?>{
      'sequence': envelope.sequence,
      'message_id': envelope.messageId,
      'sent_at': envelope.sentAt.toIso8601String(),
      'command_id': commandId,
      ...envelope.payload,
    };
    _lastCommandResult = stored;
    final pending = _pendingCommand;
    if (pending != null && pending.commandId == commandId) {
      pending.acceptResult(stored);
    }
  }

  void _handleScreenshot(_Envelope envelope) {
    final commandId = envelope.commandId;
    if (commandId == null || envelope.payload['data_base64'] is! String) {
      _sendProtocolError(
        code: 'invalid_screenshot',
        message: 'screenshot requires command_id and data_base64.',
      );
      return;
    }
    List<int> bytes;
    try {
      bytes = base64Decode(envelope.payload['data_base64']! as String);
    } on FormatException {
      _sendProtocolError(
        code: 'invalid_screenshot',
        message: 'screenshot.data_base64 is not valid base64.',
        commandId: commandId,
      );
      return;
    }
    _lastScreenshot = <String, Object?>{
      'sequence': envelope.sequence,
      'message_id': envelope.messageId,
      'command_id': commandId,
      'mime_type': envelope.payload['mime_type']?.toString() ?? 'image/png',
      'captured_at': envelope.payload['captured_at'],
      'label': envelope.payload['label'],
      'bytes': bytes.length,
    };
    final pending = _pendingCommand;
    if (pending != null && pending.commandId == commandId) {
      pending.acceptScreenshot(envelope.payload);
    }
  }

  void _handleReport(_Envelope envelope) {
    final commandId = envelope.commandId;
    if (commandId == null ||
        envelope.payload['report_json'] is! Map ||
        envelope.payload['report_markdown'] is! String) {
      _sendProtocolError(
        code: 'invalid_report_message',
        message:
            'report requires command_id, report_json, and report_markdown.',
      );
      return;
    }
    _lastReport = <String, Object?>{
      'sequence': envelope.sequence,
      'message_id': envelope.messageId,
      'command_id': commandId,
      'run_id': envelope.payload['run_id'],
      'sanitized': envelope.payload['sanitized'],
    };
    final pending = _pendingCommand;
    if (pending != null && pending.commandId == commandId) {
      pending.acceptReport(envelope.payload);
    }
  }

  void _handleAppError(_Envelope envelope) {
    final stored = <String, Object?>{
      'sequence': envelope.sequence,
      'message_id': envelope.messageId,
      'sent_at': envelope.sentAt.toIso8601String(),
      if (envelope.commandId != null) 'command_id': envelope.commandId,
      ...envelope.payload,
    };
    _lastError = stored;
    final pending = _pendingCommand;
    if (pending != null &&
        envelope.commandId != null &&
        pending.commandId == envelope.commandId) {
      pending.completeError(
        CliFailure(
          code: envelope.payload['code']?.toString() ?? 'app_error',
          message: envelope.payload['message']?.toString() ??
              'The app returned an error.',
          exitCode: 5,
          details: stored,
        ),
      );
    }
  }

  void _sendProtocolError({
    required String code,
    required String message,
    String? commandId,
    Map<String, Object?> details = const <String, Object?>{},
  }) {
    _lastError = <String, Object?>{
      'code': code,
      'message': message,
      'details': details,
    };
    final socket = _appSocket;
    if (socket != null) {
      socket.add(
        jsonEncode(
          _encodeEnvelope(
            type: 'error',
            commandId: commandId,
            payload: <String, Object?>{
              'code': code,
              'message': message,
              'retryable': false,
              'details': details,
            },
          ),
        ),
      );
    }
  }

  Map<String, Object?> _encodeEnvelope({
    required String type,
    required Map<String, Object?> payload,
    String? commandId,
  }) {
    return <String, Object?>{
      'protocol': _protocolName,
      'version': _protocolVersion,
      'type': type,
      'sequence': ++_hostSequence,
      'message_id': _newId('message'),
      'sent_at': DateTime.now().toUtc().toIso8601String(),
      if (commandId != null) 'command_id': commandId,
      'payload': payload,
    };
  }

  Future<void> _handleControlHttpRequest(HttpRequest request) async {
    var stopAfterResponse = false;
    Map<String, Object?> response;
    try {
      if (request.method != 'POST' || request.uri.path != _controlPath) {
        throw const CliFailure(
          code: 'not_found',
          message: 'POST to /control is required.',
          exitCode: 2,
        );
      }
      final bodyText = await utf8.decoder.bind(request).join();
      final decoded = jsonDecode(bodyText);
      if (decoded is! Map) {
        throw const CliFailure(
          code: 'invalid_body',
          message: 'Control body must be a JSON object.',
          exitCode: 2,
        );
      }
      final body = _stringKeyedMap(decoded);
      final action = body['action']?.toString();
      Map<String, Object?> result;
      switch (action) {
        case 'status':
          result = _statusSnapshot();
        case 'wait':
          result = await _handleWaitControl(body);
        case 'command':
          result = await _handleCommandControl(body);
        case 'restart_app':
          result = await _handleRestartControl(body);
        case 'screenshot':
          result = await _handleScreenshotControl(body);
        case 'report':
          result = await _handleReportControl(body);
        case 'stop':
          result = <String, Object?>{'stopped': true, 'session_id': sessionId};
          stopAfterResponse = true;
        default:
          throw CliFailure(
            code: 'unknown_action',
            message: 'Unknown control action "$action".',
            exitCode: 2,
          );
      }
      response = <String, Object?>{'ok': true, 'result': result};
    } on CliFailure catch (failure) {
      response = <String, Object?>{
        'ok': false,
        'error': <String, Object?>{
          'code': failure.code,
          'message': failure.message,
          'exit_code': failure.exitCode,
          'details': failure.details,
        },
      };
    } on Object catch (error) {
      response = <String, Object?>{
        'ok': false,
        'error': <String, Object?>{
          'code': 'internal_error',
          'message': error.toString(),
          'exit_code': 1,
          'details': const <String, Object?>{},
        },
      };
    }
    request.response.headers.contentType = ContentType.json;
    request.response.write(jsonEncode(response));
    await request.response.close();
    if (stopAfterResponse) {
      unawaited(shutdown());
    }
  }

  Future<Map<String, Object?>> _handleWaitControl(
      Map<String, Object?> body) async {
    final condition = body['condition']?.toString() ?? 'connected';
    final value = body['value']?.toString();
    final timeoutSeconds =
        _bodySeconds(body, 'timeout_seconds', defaultValue: 300);
    return _waitForCondition(
      condition,
      value,
      timeout: Duration(seconds: timeoutSeconds),
    );
  }

  Future<Map<String, Object?>> _handleCommandControl(
      Map<String, Object?> body) async {
    final name = _bodyString(body, 'name');
    final commandId = _bodyString(body, 'command_id');
    final rawArguments = body['arguments'];
    final arguments = rawArguments is Map
        ? _stringKeyedMap(rawArguments)
        : const <String, Object?>{};
    final timeoutSeconds =
        _bodySeconds(body, 'timeout_seconds', defaultValue: 120);
    final exchange = await _executeCommand(
      name: name,
      arguments: arguments,
      commandId: commandId,
      timeout: Duration(seconds: timeoutSeconds),
    );
    return <String, Object?>{
      'status': exchange.result['status'],
      'data': exchange.result['data'] ?? const <String, Object?>{},
      if (exchange.result['error_code'] != null)
        'error_code': exchange.result['error_code'],
      if (exchange.result['error_message'] != null)
        'error_message': exchange.result['error_message'],
      if (exchange.screenshot != null)
        'screenshot': <String, Object?>{
          'mime_type': exchange.screenshot!['mime_type'],
          'captured_at': exchange.screenshot!['captured_at'],
          'bytes': base64Decode(exchange.screenshot!['data_base64']! as String)
              .length,
        },
      if (exchange.report != null)
        'report': <String, Object?>{
          'run_id': exchange.report!['run_id'],
          'sanitized': exchange.report!['sanitized'],
        },
    };
  }

  Future<Map<String, Object?>> _handleRestartControl(
      Map<String, Object?> body) async {
    final reconnectSeconds = _bodySeconds(
      body,
      'reconnect_timeout_seconds',
      defaultValue: 30,
    );
    final baseline = _helloGeneration;
    final result = await _restartDevice(
      selectedDevice,
      androidPackage: body['android_package']?.toString() ?? androidPackage,
      iosBundleId: body['ios_bundle_id']?.toString() ?? iosBundleId,
    );
    var reconnected = false;
    final deadline = DateTime.now().add(Duration(seconds: reconnectSeconds));
    while (DateTime.now().isBefore(deadline)) {
      if (_appConnected && _helloGeneration > baseline) {
        reconnected = true;
        break;
      }
      await Future<void>.delayed(const Duration(milliseconds: 200));
    }
    return <String, Object?>{
      ...result,
      'bridge_reconnected': reconnected,
      'app_connected': _appConnected,
      if (!reconnected)
        'warning':
            'The app did not reconnect within $reconnectSeconds seconds.',
    };
  }

  Future<Map<String, Object?>> _handleScreenshotControl(
      Map<String, Object?> body) async {
    final output = body['output']?.toString();
    if (output == null || output.isEmpty) {
      throw const CliFailure(
        code: 'usage',
        message: 'screenshot.output is required.',
        exitCode: 2,
      );
    }
    final timeoutSeconds =
        _bodySeconds(body, 'timeout_seconds', defaultValue: 30);
    return _captureScreenshot(
      outputPath: _resolvePath(output),
      timeout: Duration(seconds: timeoutSeconds),
    );
  }

  Future<Map<String, Object?>> _handleReportControl(
      Map<String, Object?> body) async {
    final timeoutSeconds =
        _bodySeconds(body, 'timeout_seconds', defaultValue: 120);
    final outputDirectory = body['output_dir']?.toString();
    return _pullReport(
      outputDirectory:
          outputDirectory == null ? null : _resolvePath(outputDirectory),
      timeout: Duration(seconds: timeoutSeconds),
    );
  }

  Future<Map<String, Object?>> _waitForCondition(
    String condition,
    String? value, {
    required Duration timeout,
  }) async {
    final deadline = DateTime.now().add(timeout);
    while (true) {
      final matched = switch (condition) {
        'connected' => _appConnected,
        'disconnected' => _appSocket == null,
        'state' => _latestState?['status'] == value,
        'event' => _events.any((event) => event['kind'] == value),
        'report' => _lastReport != null,
        _ => false,
      };
      if (matched) {
        return <String, Object?>{
          'condition': condition,
          'value': value,
          'matched_at': DateTime.now().toUtc().toIso8601String(),
          'status': _statusSnapshot(),
        };
      }
      if (!DateTime.now().isBefore(deadline)) {
        throw CliFailure(
          code: 'wait_timeout',
          message:
              'Timed out waiting for $condition${value == null ? '' : '=$value'}.',
          exitCode: 5,
          details: <String, Object?>{'status': _statusSnapshot()},
        );
      }
      await Future<void>.delayed(const Duration(milliseconds: 200));
    }
  }

  Future<_CommandExchange> _executeCommand({
    required String name,
    required Map<String, Object?> arguments,
    required String commandId,
    required Duration timeout,
    bool requiresScreenshot = false,
    bool requiresReport = false,
  }) async {
    final socket = _appSocket;
    if (!_appConnected || socket == null) {
      throw const CliFailure(
        code: 'app_disconnected',
        message: 'The test app is not connected.',
        exitCode: 5,
      );
    }
    if (_pendingCommand != null) {
      throw const CliFailure(
        code: 'command_in_progress',
        message: 'Another command is already in progress.',
        exitCode: 4,
      );
    }
    final pending = _PendingCommand(
      commandId: commandId,
      requiresScreenshot: requiresScreenshot,
      requiresReport: requiresReport,
    );
    _pendingCommand = pending;
    socket.add(
      jsonEncode(
        _encodeEnvelope(
          type: 'command',
          commandId: commandId,
          payload: <String, Object?>{
            'name': name,
            'arguments': arguments,
          },
        ),
      ),
    );
    try {
      final exchange = await pending.completer.future.timeout(timeout);
      final result = exchange.result;
      if (result['status'] == 'failed') {
        throw CliFailure(
          code: result['error_code']?.toString() ?? 'command_failed',
          message: result['error_message']?.toString() ??
              'The app reported a failed command.',
          exitCode: 5,
          details: <String, Object?>{'result': result},
        );
      }
      return exchange;
    } on TimeoutException {
      _lastError = <String, Object?>{
        'code': 'command_timeout',
        'message': 'Command $name timed out.',
        'command_id': commandId,
      };
      throw CliFailure(
        code: 'command_timeout',
        message: 'Command $name timed out after ${timeout.inSeconds} seconds.',
        exitCode: 5,
        details: <String, Object?>{'command_id': commandId},
      );
    } finally {
      if (identical(_pendingCommand, pending)) {
        _pendingCommand = null;
      }
    }
  }

  Future<Map<String, Object?>> _captureScreenshot({
    required String outputPath,
    required Duration timeout,
  }) async {
    if (_appConnected) {
      try {
        final exchange = await _executeCommand(
          name: 'screenshot',
          arguments: const <String, Object?>{},
          commandId: _newId('command'),
          timeout: timeout,
          requiresScreenshot: true,
        );
        final screenshot = exchange.screenshot;
        if (screenshot == null) {
          throw const CliFailure(
            code: 'screenshot_missing',
            message:
                'The app completed the command without a screenshot payload.',
          );
        }
        final bytes = base64Decode(screenshot['data_base64']! as String);
        final file = File(outputPath);
        await file.parent.create(recursive: true);
        await file.writeAsBytes(bytes, flush: true);
        final result = <String, Object?>{
          'path': file.absolute.path,
          'source': 'app_bridge',
          'command_id': exchange.result['command_id'],
          'mime_type': screenshot['mime_type'] ?? 'image/png',
          'bytes': bytes.length,
        };
        _lastScreenshot = result;
        return result;
      } on Object catch (error) {
        final fallback =
            await _capturePlatformScreenshot(selectedDevice, outputPath);
        return <String, Object?>{
          ...fallback,
          'app_bridge_error': error.toString(),
        };
      }
    }
    final result = await _capturePlatformScreenshot(selectedDevice, outputPath);
    _lastScreenshot = result;
    return result;
  }

  Future<Map<String, Object?>> _pullReport({
    required String? outputDirectory,
    required Duration timeout,
  }) async {
    final exchange = await _executeCommand(
      name: 'report',
      arguments: const <String, Object?>{},
      commandId: _newId('command'),
      timeout: timeout,
      requiresReport: true,
    );
    final report = exchange.report;
    if (report == null) {
      throw const CliFailure(
        code: 'report_missing',
        message: 'The app completed the command without a report payload.',
      );
    }
    final runId = report['run_id']?.toString();
    if (runId == null || runId.isEmpty) {
      throw const CliFailure(
        code: 'invalid_report',
        message: 'The report payload is missing run_id.',
      );
    }
    final reportJson = _mapValue(report['report_json']);
    final markdown = report['report_markdown']?.toString();
    if (reportJson == null || markdown == null || markdown.trim().isEmpty) {
      throw const CliFailure(
        code: 'invalid_report',
        message: 'The report payload is missing JSON or Markdown content.',
      );
    }
    if (report['sanitized'] != true) {
      throw const CliFailure(
        code: 'report_not_sanitized',
        message: 'The app did not confirm report sanitization.',
      );
    }
    final head = await _currentGitHead();
    _validateReportJson(reportJson, expectedPluginCommit: head);
    final safeRunId = runId.replaceAll(RegExp(r'[^A-Za-z0-9._-]'), '_');
    final targetDirectory = Directory(
      outputDirectory ?? '${artifactDirectory.path}/reports/$safeRunId',
    );
    await targetDirectory.create(recursive: true);
    final jsonFile = File('${targetDirectory.path}/device-test-report.json');
    final markdownFile = File('${targetDirectory.path}/device-test-report.md');
    await jsonFile.writeAsString(
      '${const JsonEncoder.withIndent('  ').convert(reportJson)}\n',
      flush: true,
    );
    await markdownFile.writeAsString(
      markdown.endsWith('\n') ? markdown : '$markdown\n',
      flush: true,
    );
    final summary =
        _mapValue(reportJson['summary']) ?? const <String, Object?>{};
    final result = <String, Object?>{
      'run_id': runId,
      'json_path': jsonFile.absolute.path,
      'markdown_path': markdownFile.absolute.path,
      'plugin_commit': reportJson['plugin_commit'],
      'plugin_commit_matches_head': true,
      'summary': summary,
    };
    _lastReport = result;
    return result;
  }

  void _failPending(String code, String message) {
    final pending = _pendingCommand;
    if (pending == null || pending.completer.isCompleted) {
      return;
    }
    _pendingCommand = null;
    pending.completer.completeError(
      CliFailure(code: code, message: message, exitCode: 5),
    );
  }

  Map<String, Object?> _statusSnapshot() {
    return <String, Object?>{
      'session_id': sessionId,
      'pid': pid,
      'selected_device': selectedDevice.toJson(),
      'websocket_endpoint': _websocketEndpoint,
      'control_port': _controlPort,
      'artifact_directory': artifactDirectory.absolute.path,
      'started_at': _startedAt?.toIso8601String(),
      'app_connected': _appConnected,
      'app_instance_id': _appInstanceId,
      'app_last_sequence': _lastAppSequence,
      'connected_at': _connectedAt?.toIso8601String(),
      'last_disconnect_at': _lastDisconnectAt?.toIso8601String(),
      'last_connected_device_name': _lastConnectedDeviceName,
      'hello': _hello,
      'latest_state': _latestState,
      'recent_events':
          _events.length > 25 ? _events.sublist(_events.length - 25) : _events,
      'last_command_result': _lastCommandResult,
      'last_error': _lastError,
      'last_screenshot': _lastScreenshot,
      'last_report': _lastReport,
      'command_in_progress': _pendingCommand != null,
      'warnings': deviceInventoryWarnings,
    };
  }

  Future<String> _currentGitHead() async {
    final git = _requireExecutable('git');
    final result = await _runProcess(
      git,
      <String>['-C', repoRoot.path, 'rev-parse', 'HEAD'],
      timeout: const Duration(seconds: 10),
    );
    if (result.exitCode != 0) {
      throw CliFailure(
        code: 'git_head_unavailable',
        message:
            'Could not read the current Git HEAD: ${_trimProcessError(result)}',
      );
    }
    final head = result.stdout.toString().trim();
    if (!RegExp(r'^[0-9a-f]{40}$').hasMatch(head)) {
      throw const CliFailure(
        code: 'git_head_unavailable',
        message: 'Git HEAD was not a 40-character lowercase SHA.',
      );
    }
    return head;
  }

  Future<void> shutdown() async {
    if (_shutdownRequested) {
      return;
    }
    _shutdownRequested = true;
    _failPending('server_stopping', 'The controller session is stopping.');
    final socket = _appSocket;
    _appSocket = null;
    _appConnected = false;
    final subscription = _appSubscription;
    _appSubscription = null;
    await subscription?.cancel();
    if (socket != null) {
      await socket.close(WebSocketStatus.goingAway, 'server_stopping');
    }
    for (final subscription in _signalSubscriptions) {
      await subscription.cancel();
    }
    _signalSubscriptions.clear();
    await _appServer.close(force: true);
    await _controlServer.close(force: true);
    if (await stateFile.exists()) {
      await stateFile.delete();
    }
    if (!_shutdownCompleter.isCompleted) {
      _shutdownCompleter.complete();
    }
  }

  Future<String> _findLanAddress() async {
    final interfaces = await NetworkInterface.list(
      type: InternetAddressType.IPv4,
      includeLoopback: false,
    );
    final candidates = <String, String>{};
    for (final interface in interfaces) {
      for (final address in interface.addresses) {
        if (_isPrivateIpv4(address.address)) {
          candidates[interface.name] = address.address;
        }
      }
    }
    if (candidates.isEmpty) {
      return '127.0.0.1';
    }
    if (candidates.containsKey('en0')) {
      return candidates['en0']!;
    }
    return candidates.values.first;
  }

  bool _isPrivateIpv4(String address) {
    final parts = address.split('.').map(int.tryParse).toList();
    if (parts.length != 4 || parts.any((part) => part == null)) {
      return false;
    }
    final first = parts[0]!;
    final second = parts[1]!;
    return first == 10 ||
        (first == 172 && second >= 16 && second <= 31) ||
        (first == 192 && second == 168);
  }
}

class _Envelope {
  const _Envelope({
    required this.type,
    required this.sequence,
    required this.messageId,
    required this.sentAt,
    required this.payload,
    this.commandId,
  });

  final String type;
  final int sequence;
  final String messageId;
  final DateTime sentAt;
  final String? commandId;
  final Map<String, Object?> payload;

  factory _Envelope.fromJsonString(String source) {
    final decoded = jsonDecode(source);
    if (decoded is! Map) {
      throw const FormatException('Message must be a JSON object.');
    }
    final json = _stringKeyedMap(decoded);
    if (json['protocol'] != _protocolName) {
      throw FormatException('Unsupported protocol: ${json['protocol']}');
    }
    if (json['version'] != _protocolVersion) {
      throw FormatException('Unsupported protocol version: ${json['version']}');
    }
    final type = json['type'];
    final sequence = json['sequence'];
    final messageId = json['message_id'];
    final sentAtText = json['sent_at'];
    final payload = json['payload'];
    if (type is! String ||
        sequence is! int ||
        sequence < 1 ||
        messageId is! String ||
        messageId.isEmpty ||
        sentAtText is! String ||
        payload is! Map) {
      throw const FormatException(
          'Message envelope is missing required fields.');
    }
    final sentAt = DateTime.tryParse(sentAtText);
    if (sentAt == null) {
      throw const FormatException('sent_at must be an ISO-8601 timestamp.');
    }
    final commandId = json['command_id'];
    if (commandId != null && (commandId is! String || commandId.isEmpty)) {
      throw const FormatException('command_id must be a non-empty string.');
    }
    return _Envelope(
      type: type,
      sequence: sequence,
      messageId: messageId,
      sentAt: sentAt.toUtc(),
      commandId: commandId as String?,
      payload: _stringKeyedMap(payload),
    );
  }
}

class _PendingCommand {
  _PendingCommand({
    required this.commandId,
    required this.requiresScreenshot,
    required this.requiresReport,
  });

  final String commandId;
  final bool requiresScreenshot;
  final bool requiresReport;
  final Completer<_CommandExchange> completer = Completer<_CommandExchange>();
  Map<String, Object?>? result;
  Map<String, Object?>? screenshot;
  Map<String, Object?>? report;

  void acceptResult(Map<String, Object?> value) {
    result = value;
    _tryComplete();
  }

  void acceptScreenshot(Map<String, Object?> value) {
    screenshot = value;
    _tryComplete();
  }

  void acceptReport(Map<String, Object?> value) {
    report = value;
    _tryComplete();
  }

  void completeError(Object error) {
    if (!completer.isCompleted) {
      completer.completeError(error);
    }
  }

  void _tryComplete() {
    final currentResult = result;
    if (currentResult == null || completer.isCompleted) {
      return;
    }
    if (currentResult['status'] == 'failed') {
      completer.complete(
        _CommandExchange(
          commandId: commandId,
          result: currentResult,
          screenshot: screenshot,
          report: report,
        ),
      );
      return;
    }
    if (requiresScreenshot && screenshot == null) {
      return;
    }
    if (requiresReport && report == null) {
      return;
    }
    completer.complete(
      _CommandExchange(
        commandId: commandId,
        result: currentResult,
        screenshot: screenshot,
        report: report,
      ),
    );
  }
}

class _CommandExchange {
  const _CommandExchange({
    required this.commandId,
    required this.result,
    this.screenshot,
    this.report,
  });

  final String commandId;
  final Map<String, Object?> result;
  final Map<String, Object?>? screenshot;
  final Map<String, Object?>? report;
}

String _bodyString(Map<String, Object?> body, String field) {
  final value = body[field];
  if (value is! String || value.isEmpty) {
    throw CliFailure(
      code: 'invalid_body',
      message: '$field must be a non-empty string.',
      exitCode: 2,
    );
  }
  return value;
}

int _bodySeconds(Map<String, Object?> body, String field,
    {required int defaultValue}) {
  final value = body[field];
  if (value == null) {
    return defaultValue;
  }
  if (value is! int || value < 1 || value > 3600) {
    throw CliFailure(
      code: 'invalid_body',
      message: '$field must be an integer from 1 to 3600.',
      exitCode: 2,
    );
  }
  return value;
}

/// Validates a device-test report JSON document against schema v2.
///
/// This is a narrow, test-facing wrapper around the internal report validator.
/// It reports field-level validation errors only; error messages and details
/// never include report values, provisioning secrets, or device identifiers.
void validateDeviceTestReportJson(
  Map<String, Object?> report, {
  required String expectedPluginCommit,
}) {
  _validateReportJson(report, expectedPluginCommit: expectedPluginCommit);
}

void _validateReportJson(
  Map<String, Object?> report, {
  required String expectedPluginCommit,
}) {
  const requiredKeys = <String>{
    'schema_version',
    'generated_at',
    'test_app',
    'plugin_commit',
    'controller',
    'commissionee',
    'summary',
    'tests',
    'sanitization',
  };
  _requireExactKeys(report, requiredKeys, 'report');
  if (report['schema_version'] != 2) {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'Report schema_version must be 2.',
    );
  }
  final generatedAt =
      DateTime.tryParse(report['generated_at']?.toString() ?? '');
  if (generatedAt == null) {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'Report generated_at must be an ISO-8601 timestamp.',
    );
  }
  final testApp = _requiredMap(report, 'test_app');
  _requireExactKeys(
      testApp, const <String>{'name', 'version', 'commit'}, 'test_app');
  for (final field in const <String>['name', 'version', 'commit']) {
    if (testApp[field] is! String || (testApp[field]! as String).isEmpty) {
      throw CliFailure(
        code: 'invalid_report',
        message: 'test_app.$field must be a non-empty string.',
      );
    }
  }
  _requireCommit(testApp['commit'], 'test_app.commit');
  final pluginCommit = report['plugin_commit'];
  _requireCommit(pluginCommit, 'plugin_commit');
  if (pluginCommit != expectedPluginCommit) {
    throw CliFailure(
      code: 'plugin_commit_mismatch',
      message: 'The report plugin_commit does not match the current Git HEAD.',
      details: <String, Object?>{
        'report_plugin_commit': pluginCommit,
        'current_head': expectedPluginCommit,
      },
    );
  }

  final controller = _requiredMap(report, 'controller');
  _requireExactKeys(
    controller,
    const <String>{'platform', 'device_model', 'os_version', 'app_build'},
    'controller',
  );
  if (!const <String>{'android', 'ios'}.contains(controller['platform'])) {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'controller.platform must be android or ios.',
    );
  }
  for (final field in const <String>[
    'device_model',
    'os_version',
    'app_build'
  ]) {
    if (controller[field] is! String ||
        (controller[field]! as String).isEmpty) {
      throw CliFailure(
        code: 'invalid_report',
        message: 'controller.$field must be a non-empty string.',
      );
    }
  }

  final commissionee = _requiredMap(report, 'commissionee');
  const commissioneeRequired = <String>{
    'type',
    'model',
    'firmware',
    'commissioning_transport',
    'network_transport',
    'state_change_method',
  };
  _requireAllowedKeys(
    commissionee,
    <String>{...commissioneeRequired, 'state_change_notes'},
    'commissionee',
  );
  for (final key in commissioneeRequired) {
    if (!commissionee.containsKey(key)) {
      throw CliFailure(
        code: 'invalid_report',
        message: 'commissionee.$key is required.',
      );
    }
  }
  if (commissionee['type'] != 'real') {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'commissionee.type must be real.',
    );
  }
  if (commissionee['commissioning_transport'] != 'ip') {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'commissionee.commissioning_transport must be ip.',
    );
  }
  if (commissionee['network_transport'] != 'wifi') {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'commissionee.network_transport must be wifi.',
    );
  }
  if (!const <String>{
    'physical_control',
    'vendor_app',
    'commissionee_ui',
    'other'
  }.contains(commissionee['state_change_method'])) {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'Unsupported commissionee.state_change_method.',
    );
  }

  final tests = _requiredMap(report, 'tests');
  _requireExactKeys(tests, _reportTestIds.toSet(), 'tests');
  final counts = <String, int>{'passed': 0, 'failed': 0, 'not_run': 0};
  final p0NotRun = <String>{};
  const p0Ids = <String>{
    'build_install',
    'ip_discovery',
    'ip_commissioning',
    'operational_connect',
    'onoff_invoke',
    'onoff_subscription',
    'node_label_persistence',
  };
  for (final testId in _reportTestIds) {
    final test = _requiredMap(tests, testId);
    _requireAllowedKeys(
      test,
      const <String>{'status', 'duration_ms', 'notes', 'evidence_files'},
      'tests.$testId',
    );
    final status = test['status'];
    final duration = test['duration_ms'];
    if (!const <String>{'passed', 'failed', 'not_run'}.contains(status)) {
      throw CliFailure(
        code: 'invalid_report',
        message: 'tests.$testId.status is invalid.',
      );
    }
    if (duration is! int || duration < 0) {
      throw CliFailure(
        code: 'invalid_report',
        message: 'tests.$testId.duration_ms must be a non-negative integer.',
      );
    }
    counts[status! as String] = counts[status]! + 1;
    if (p0Ids.contains(testId) && status == 'not_run') {
      p0NotRun.add(testId);
    }
  }
  final summary = _requiredMap(report, 'summary');
  _requireExactKeys(
    summary,
    const <String>{'result', 'passed', 'failed', 'not_run'},
    'summary',
  );
  for (final status in const <String>['passed', 'failed', 'not_run']) {
    if (summary[status] != counts[status]) {
      throw CliFailure(
        code: 'invalid_report',
        message: 'summary.$status does not match the tests object.',
      );
    }
  }
  final expectedResult = counts['failed']! > 0
      ? 'failed'
      : p0NotRun.isNotEmpty
          ? 'not_run'
          : 'passed';
  if (summary['result'] != expectedResult) {
    throw const CliFailure(
      code: 'invalid_report',
      message: 'summary.result is inconsistent with test statuses.',
    );
  }

  final sanitization = _requiredMap(report, 'sanitization');
  _requireExactKeys(sanitization, const <String>{'reviewed', 'policy_version'},
      'sanitization');
  if (sanitization['reviewed'] != true || sanitization['policy_version'] != 1) {
    throw const CliFailure(
      code: 'report_not_sanitized',
      message:
          'sanitization.reviewed must be true and policy_version must be 1.',
    );
  }
  _scanForSensitiveData(report, r'$');
}

Map<String, Object?> _requiredMap(Map<String, Object?> source, String key) {
  final value = source[key];
  if (value is! Map) {
    throw CliFailure(
      code: 'invalid_report',
      message: '$key must be an object.',
    );
  }
  return _stringKeyedMap(value);
}

void _requireExactKeys(
    Map<String, Object?> source, Set<String> expected, String path) {
  final actual = source.keys.toSet();
  if (actual.length != expected.length || !actual.containsAll(expected)) {
    throw CliFailure(
      code: 'invalid_report',
      message: '$path has unexpected or missing keys.',
      details: <String, Object?>{
        'expected': expected.toList()..sort(),
        'actual': actual.toList()..sort(),
      },
    );
  }
}

void _requireAllowedKeys(
    Map<String, Object?> source, Set<String> allowed, String path) {
  final unexpected =
      source.keys.where((key) => !allowed.contains(key)).toList();
  if (unexpected.isNotEmpty) {
    throw CliFailure(
      code: 'invalid_report',
      message: '$path contains unexpected keys.',
      details: <String, Object?>{'unexpected': unexpected..sort()},
    );
  }
}

void _requireCommit(Object? value, String field) {
  if (value is! String || !RegExp(r'^[0-9a-f]{40}$').hasMatch(value)) {
    throw CliFailure(
      code: 'invalid_report',
      message: '$field must be a 40-character lowercase Git SHA.',
    );
  }
}

void _scanForSensitiveData(Object? value, String path) {
  if (value is Map) {
    for (final entry in value.entries) {
      final key = entry.key.toString();
      final lowerKey = key.toLowerCase();
      if (const <String>{
        'serial',
        'serial_number',
        'udid',
        'ssid',
        'password',
        'setup_code',
        'onboarding_payload',
        'ble_address',
        'certificate',
        'private_key',
      }.contains(lowerKey)) {
        throw CliFailure(
          code: 'report_sensitive_data',
          message: 'Report contains a forbidden field at $path.$key.',
        );
      }
      _scanForSensitiveData(entry.value, '$path.$key');
    }
    return;
  }
  if (value is List) {
    for (var index = 0; index < value.length; index++) {
      _scanForSensitiveData(value[index], '$path[$index]');
    }
    return;
  }
  if (value is! String) {
    return;
  }
  final forbidden = <RegExp>[
    RegExp(r'-----BEGIN [A-Z ]+PRIVATE KEY-----'),
    RegExp(r'(?:[0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}'),
    RegExp(r'\b[Mm][Tt]:[A-Za-z0-9]+'),
    RegExp(
      r'\b(?:[Pp][Aa][Ss][Ss][Ww][Oo][Rr][Dd]|[Pp][Aa][Ss][Ss][Ww][Dd]|[Ss][Ss][Ii][Dd]|[Ss][Ee][Rr][Ii][Aa][Ll]|[Uu][Dd][Ii][Dd])=',
    ),
  ];
  for (final pattern in forbidden) {
    if (pattern.hasMatch(value)) {
      throw CliFailure(
        code: 'report_sensitive_data',
        message: 'Report contains forbidden sensitive text at $path.',
      );
    }
  }
}
