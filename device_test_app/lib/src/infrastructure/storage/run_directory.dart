import 'dart:io';

import 'package:path_provider/path_provider.dart';

class RunDirectory {
  RunDirectory({Future<Directory> Function()? documentsDirectory})
    : _documentsDirectory =
          documentsDirectory ?? getApplicationDocumentsDirectory;

  final Future<Directory> Function() _documentsDirectory;

  Future<Directory> runsRoot() async {
    final documents = await _documentsDirectory();
    final directory = Directory('${documents.path}/runs');
    await directory.create(recursive: true);
    return directory;
  }

  Future<Directory> create(String runId) async {
    _validateRunId(runId);
    final root = await runsRoot();
    final directory = Directory('${root.path}/$runId');
    await directory.create(recursive: true);
    return directory;
  }

  Future<List<String>> listRunIds() async {
    final root = await runsRoot();
    final ids = <String>[];
    await for (final entity in root.list(followLinks: false)) {
      if (entity is Directory) {
        final segments = entity.uri.pathSegments.where(
          (segment) => segment.isNotEmpty,
        );
        if (segments.isNotEmpty) {
          ids.add(segments.last);
        }
      }
    }
    ids.sort();
    return List<String>.unmodifiable(ids);
  }

  Future<Directory?> find(String runId) async {
    _validateRunId(runId);
    final root = await runsRoot();
    final directory = Directory('${root.path}/$runId');
    return await directory.exists() ? directory : null;
  }

  Future<void> delete(String runId) async {
    final directory = await find(runId);
    if (directory != null) {
      await directory.delete(recursive: true);
    }
  }

  Future<File> writeAtomically({
    required String runId,
    required String fileName,
    required String contents,
  }) async {
    _validateFileName(fileName);
    final directory = await create(runId);
    final target = File('${directory.path}/$fileName');
    final temporary = File('${directory.path}/.$fileName.tmp');
    await temporary.writeAsString(contents, flush: true);
    if (await target.exists()) {
      await target.delete();
    }
    return temporary.rename(target.path);
  }

  void _validateRunId(String runId) {
    if (!RegExp(r'^[A-Za-z0-9][A-Za-z0-9._-]{0,127}$').hasMatch(runId)) {
      throw ArgumentError.value(runId, 'runId', 'Unsafe run identifier');
    }
  }

  void _validateFileName(String fileName) {
    if (!RegExp(r'^[A-Za-z0-9][A-Za-z0-9._-]{0,127}$').hasMatch(fileName)) {
      throw ArgumentError.value(fileName, 'fileName', 'Unsafe file name');
    }
  }
}
