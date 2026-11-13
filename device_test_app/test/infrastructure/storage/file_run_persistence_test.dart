import 'dart:io';

import 'package:flutter_matter_device_test_app/src/infrastructure/storage/file_run_persistence.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/run_directory.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:path_provider_platform_interface/path_provider_platform_interface.dart';

class _MemoryPathProvider extends PathProviderPlatform {
  final String basePath;

  _MemoryPathProvider(this.basePath);

  @override
  Future<String?> getApplicationDocumentsPath() async => basePath;
}

void main() {
  late Directory tempDirectory;
  late _MemoryPathProvider provider;

  setUp(() {
    tempDirectory = Directory.systemTemp.createTempSync(
      'file_run_persistence_test',
    );
    provider = _MemoryPathProvider(tempDirectory.path);
    PathProviderPlatform.instance = provider;
  });

  tearDown(() {
    tempDirectory.deleteSync(recursive: true);
  });

  RunDirectory runDirectory() => RunDirectory();

  test(
    'cleanupUnfinished removes state files but keeps other artifacts',
    () async {
      final directory = runDirectory();
      final first = await directory.create('run-1');
      final second = await directory.create('run-2');
      File('${first.path}/run_state.json').writeAsStringSync('{}');
      File('${first.path}/device-test-report.json').writeAsStringSync('{}');
      File('${second.path}/run_state.json').writeAsStringSync('{}');

      await FileRunPersistence(runDirectory: directory).cleanupUnfinished();

      expect(File('${first.path}/run_state.json').existsSync(), isFalse);
      expect(File('${second.path}/run_state.json').existsSync(), isFalse);
      expect(
        File('${first.path}/device-test-report.json').existsSync(),
        isTrue,
      );
    },
  );

  test('cleanupUnfinished succeeds when no run directories exist', () async {
    await runDirectory().runsRoot();

    await FileRunPersistence(runDirectory: runDirectory()).cleanupUnfinished();
  });
}
