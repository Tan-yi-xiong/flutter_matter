import 'dart:convert';
import 'dart:io';

const _appDirectory = 'device_test_app';
const _defaultPluginCommitDefine = 'PLUGIN_COMMIT';
const _defaultTestAppCommitDefine = 'TEST_APP_COMMIT';

Future<void> main(List<String> arguments) async {
  try {
    exitCode = await _run(arguments);
  } on _DeviceTestToolException catch (error) {
    stderr.writeln('device-test-app: ${error.message}');
    exitCode = 1;
  } on ProcessException catch (error) {
    stderr.writeln('device-test-app: ${error.message}');
    exitCode = 1;
  }
}

Future<int> _run(List<String> arguments) async {
  if (arguments.isEmpty ||
      arguments.first == '--help' ||
      arguments.first == '-h') {
    stdout.writeln(_usage);
    return 0;
  }

  final command = arguments.first;
  final commandArguments = arguments.sublist(1);
  final repositoryRoot = _repositoryRoot();

  switch (command) {
    case 'metadata':
      stdout.writeln(const JsonEncoder.withIndent('  ').convert(
        await _metadata(repositoryRoot),
      ));
      return 0;
    case 'check':
      _requireCleanTrackedWorktree(repositoryRoot);
      await _execute(repositoryRoot, [
        'fvm',
        'dart',
        'format',
        '--output=none',
        '--set-exit-if-changed',
        _appDirectory
      ]);
      await _execute(
          repositoryRoot,
          [
            'fvm',
            'flutter',
            'analyze',
            '--no-fatal-infos',
            '--no-fatal-warnings'
          ],
          workingDirectory: _appDirectory);
      await _execute(repositoryRoot, ['fvm', 'flutter', 'test'],
          workingDirectory: _appDirectory);
      return 0;
    case 'build-apk':
      _requireCleanTrackedWorktree(repositoryRoot);
      await _execute(
        repositoryRoot,
        [
          'fvm',
          'flutter',
          'build',
          'apk',
          '--debug',
          ..._commitDefines(await _metadata(repositoryRoot)),
        ],
        workingDirectory: _appDirectory,
      );
      return 0;
    case 'build-ios':
      _requireCleanTrackedWorktree(repositoryRoot);
      await _execute(
        repositoryRoot,
        [
          'fvm',
          'flutter',
          'build',
          'ios',
          '--debug',
          '--no-codesign',
          ..._commitDefines(await _metadata(repositoryRoot)),
        ],
        workingDirectory: _appDirectory,
      );
      return 0;
    case 'run':
      _requireCleanTrackedWorktree(repositoryRoot);
      final options = _parseRunOptions(commandArguments);
      await _execute(
        repositoryRoot,
        [
          'fvm',
          'flutter',
          'run',
          '-d',
          options.device,
          ..._commitDefines(await _metadata(repositoryRoot)),
          ...options.passthrough,
        ],
        workingDirectory: _appDirectory,
      );
      return 0;
    default:
      throw _DeviceTestToolException(
          'Unknown command "$command". Run with --help for usage.');
  }
}

String _repositoryRoot() {
  final result = Process.runSync('git', ['rev-parse', '--show-toplevel']);
  if (result.exitCode != 0) {
    throw const _DeviceTestToolException(
        'Run this command from inside the flutter_matter Git repository.');
  }
  return result.stdout.toString().trim();
}

Future<Map<String, String>> _metadata(String repositoryRoot) async {
  final result = await Process.run(
    'git',
    ['rev-parse', 'HEAD'],
    workingDirectory: repositoryRoot,
  );
  if (result.exitCode != 0) {
    throw const _DeviceTestToolException(
        'Unable to read the current Git HEAD.');
  }
  final commit = result.stdout.toString().trim();
  if (!RegExp(r'^[0-9a-f]{40}$').hasMatch(commit)) {
    throw const _DeviceTestToolException(
        'Git HEAD is not a 40-character lowercase commit SHA.');
  }
  return {
    'plugin_commit': commit,
    'test_app_commit': commit,
  };
}

List<String> _commitDefines(Map<String, String> metadata) {
  return [
    '--dart-define=$_defaultPluginCommitDefine=${metadata['plugin_commit']}',
    '--dart-define=$_defaultTestAppCommitDefine=${metadata['test_app_commit']}',
  ];
}

void _requireCleanTrackedWorktree(String repositoryRoot) {
  final result = Process.runSync(
    'git',
    ['status', '--porcelain', '--untracked-files=no'],
    workingDirectory: repositoryRoot,
  );
  if (result.exitCode != 0) {
    throw const _DeviceTestToolException('Unable to inspect the Git worktree.');
  }
  if (result.stdout.toString().trim().isNotEmpty) {
    throw const _DeviceTestToolException(
      'Official device-test builds require a clean tracked worktree. Commit or revert tracked changes first.',
    );
  }
}

Future<void> _execute(
  String repositoryRoot,
  List<String> command, {
  String? workingDirectory,
}) async {
  final directory = workingDirectory == null
      ? Directory(repositoryRoot)
      : Directory('$repositoryRoot/$workingDirectory');
  stdout.writeln('> ${command.join(' ')}');
  final process = await Process.start(
    command.first,
    command.sublist(1),
    workingDirectory: directory.path,
    mode: ProcessStartMode.inheritStdio,
  );
  final exitCode = await process.exitCode;
  if (exitCode != 0) {
    throw _DeviceTestToolException('Command failed with exit code $exitCode.');
  }
}

_RunOptions _parseRunOptions(List<String> arguments) {
  String? device;
  final passthrough = <String>[];
  var parsingPassthrough = false;
  for (var index = 0; index < arguments.length; index++) {
    final argument = arguments[index];
    if (parsingPassthrough) {
      passthrough.add(argument);
      continue;
    }
    if (argument == '--') {
      parsingPassthrough = true;
      continue;
    }
    if (argument == '--device') {
      if (index + 1 >= arguments.length || arguments[index + 1].isEmpty) {
        throw const _DeviceTestToolException(
            '--device requires a non-empty value.');
      }
      device = arguments[++index];
      continue;
    }
    passthrough.add(argument);
  }
  if (device == null) {
    throw const _DeviceTestToolException('run requires --device <id>.');
  }
  return _RunOptions(
      device: device, passthrough: List.unmodifiable(passthrough));
}

class _RunOptions {
  const _RunOptions({required this.device, required this.passthrough});

  final String device;
  final List<String> passthrough;
}

class _DeviceTestToolException implements Exception {
  const _DeviceTestToolException(this.message);

  final String message;
}

const _usage = '''
Usage:
  fvm dart run tool/device_test_app.dart metadata
  fvm dart run tool/device_test_app.dart check
  fvm dart run tool/device_test_app.dart build-apk
  fvm dart run tool/device_test_app.dart build-ios
  fvm dart run tool/device_test_app.dart run --device <id> [-- <flutter run args>]

Official runs require a clean tracked Git worktree and inject the current HEAD as
PLUGIN_COMMIT and TEST_APP_COMMIT.
''';
