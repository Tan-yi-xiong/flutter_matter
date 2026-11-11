import 'dart:convert';
import 'dart:io';

import '../../application/ports.dart';
import 'run_directory.dart';

/// Persists the complete resumable runner state in each run directory.
///
/// Clearing the active snapshot removes only the state file. Report artifacts
/// and historical run directories remain available for evidence.
class FileRunPersistence implements RunPersistencePort {
  FileRunPersistence({required RunDirectory runDirectory})
    : _runDirectory = runDirectory;

  static const stateFileName = 'run_state.json';

  final RunDirectory _runDirectory;

  @override
  Future<PersistedRunState?> loadUnfinished() async {
    final record = await _findLatestUnfinished();
    return record?.state;
  }

  @override
  Future<void> save(PersistedRunState state) async {
    await _runDirectory.writeAtomically(
      runId: state.session.id,
      fileName: stateFileName,
      contents: const JsonEncoder.withIndent('  ').convert(state.toJson()),
    );
  }

  @override
  Future<void> clearUnfinished() async {
    final record = await _findLatestUnfinished();
    if (record != null && await record.stateFile.exists()) {
      await record.stateFile.delete();
    }
  }

  Future<_UnfinishedRun?> _findLatestUnfinished() async {
    final runsDirectory = await _runDirectory.runsRoot();
    _UnfinishedRun? latest;

    await for (final entity in runsDirectory.list(followLinks: false)) {
      if (entity is! Directory) {
        continue;
      }
      final runId = entity.uri.pathSegments
          .where((segment) => segment.isNotEmpty)
          .last;

      final _UnfinishedRun? candidate;
      try {
        candidate = await _readUnfinished(runId);
      } on Object {
        // A single invalid or unreadable run must not block app recovery.
        continue;
      }
      if (candidate == null) {
        continue;
      }
      if (latest == null || _isNewer(candidate.state, latest.state)) {
        latest = candidate;
      }
    }

    return latest;
  }

  Future<_UnfinishedRun?> _readUnfinished(String runId) async {
    final directory = await _runDirectory.find(runId);
    if (directory == null) {
      return null;
    }
    final stateFile = File('${directory.path}/$stateFileName');
    if (!await stateFile.exists()) {
      return null;
    }

    final decoded = jsonDecode(await stateFile.readAsString());
    if (decoded is! Map<String, dynamic>) {
      throw const FormatException('$stateFileName must contain an object');
    }
    final state = PersistedRunState.fromJson(decoded);
    if (state.session.phase.isTerminal) {
      return null;
    }
    return _UnfinishedRun(state: state, stateFile: stateFile);
  }

  bool _isNewer(PersistedRunState candidate, PersistedRunState current) {
    final candidateUpdatedAt = candidate.session.updatedAt;
    final currentUpdatedAt = current.session.updatedAt;
    if (candidateUpdatedAt != currentUpdatedAt) {
      return candidateUpdatedAt.isAfter(currentUpdatedAt);
    }
    return candidate.session.id.compareTo(current.session.id) > 0;
  }
}

class _UnfinishedRun {
  const _UnfinishedRun({required this.state, required this.stateFile});

  final PersistedRunState state;
  final File stateFile;
}
