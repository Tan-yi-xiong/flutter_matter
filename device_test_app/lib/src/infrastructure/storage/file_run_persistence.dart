import 'dart:io';

import '../../application/ports.dart';
import 'run_directory.dart';

/// Removes stale run-state files left behind by interrupted Runs.
///
/// Runs are intentionally one-shot and are never resumed, so this port only
/// exists to clean artifacts; report files stay available for evidence.
class FileRunPersistence implements RunPersistencePort {
  FileRunPersistence({required RunDirectory runDirectory})
    : _runDirectory = runDirectory;

  static const stateFileName = 'run_state.json';

  final RunDirectory _runDirectory;

  @override
  Future<void> cleanupUnfinished() async {
    final runsDirectory = await _runDirectory.runsRoot();
    await for (final entity in runsDirectory.list(followLinks: false)) {
      if (entity is! Directory) {
        continue;
      }
      final stateFile = File('${entity.path}/$stateFileName');
      if (await stateFile.exists()) {
        try {
          await stateFile.delete();
        } on Object {
          // A single undeletable file must not block the cleanup sweep.
        }
      }
    }
  }
}
