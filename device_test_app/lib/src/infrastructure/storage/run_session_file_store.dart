import 'dart:convert';
import 'dart:io';

import '../../domain/domain.dart';
import 'run_directory.dart';

class RunSessionFileStore {
  RunSessionFileStore({required RunDirectory runDirectory})
    : _runDirectory = runDirectory;

  static const sessionFileName = 'session.json';

  final RunDirectory _runDirectory;

  Future<void> save(RunSession session) async {
    await _runDirectory.writeAtomically(
      runId: session.id,
      fileName: sessionFileName,
      contents: const JsonEncoder.withIndent('  ').convert(session.toJson()),
    );
  }

  Future<RunSession?> load(String runId) async {
    final directory = await _runDirectory.find(runId);
    if (directory == null) {
      return null;
    }
    final file = File('${directory.path}/$sessionFileName');
    if (!await file.exists()) {
      return null;
    }
    final decoded = jsonDecode(await file.readAsString());
    if (decoded is! Map<String, dynamic>) {
      throw const FormatException('session.json must contain a JSON object');
    }
    return RunSession.fromJson(decoded);
  }

  Future<RunSession?> loadLatestUnfinished() async {
    final runsDirectory = await _runDirectory.runsRoot();
    RunSession? latest;
    await for (final entity in runsDirectory.list(followLinks: false)) {
      if (entity is! Directory) {
        continue;
      }
      final runId = entity.uri.pathSegments
          .where((segment) => segment.isNotEmpty)
          .last;
      final RunSession? session;
      try {
        session = await load(runId);
      } on Object {
        continue;
      }
      if (session == null || session.phase.isTerminal) {
        continue;
      }
      if (latest == null || session.updatedAt.isAfter(latest.updatedAt)) {
        latest = session;
      }
    }
    return latest;
  }

  Future<void> delete(String runId) => _runDirectory.delete(runId);
}
