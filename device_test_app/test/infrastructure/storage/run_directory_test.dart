import 'dart:io';

import 'package:flutter_matter_device_test_app/src/infrastructure/storage/run_directory.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test(
    'writes the requested file atomically and replaces prior contents',
    () async {
      final documents = await Directory.systemTemp.createTemp(
        'flutter-matter-run-',
      );
      addTearDown(() => documents.delete(recursive: true));
      final store = RunDirectory(documentsDirectory: () async => documents);

      final first = await store.writeAtomically(
        runId: 'run-123',
        fileName: 'session.json',
        contents: '{"version":1}',
      );
      expect(await first.readAsString(), '{"version":1}');

      final second = await store.writeAtomically(
        runId: 'run-123',
        fileName: 'session.json',
        contents: '{"version":2}',
      );
      expect(await second.readAsString(), '{"version":2}');
      expect(
        await File('${documents.path}/runs/run-123/.session.json.tmp').exists(),
        isFalse,
      );
    },
  );

  test('rejects unsafe run identifiers and file names', () async {
    final documents = await Directory.systemTemp.createTemp(
      'flutter-matter-run-',
    );
    addTearDown(() => documents.delete(recursive: true));
    final store = RunDirectory(documentsDirectory: () async => documents);

    expect(() => store.create('../escape'), throwsArgumentError);
    expect(
      () => store.writeAtomically(
        runId: 'valid',
        fileName: '../escape',
        contents: 'x',
      ),
      throwsArgumentError,
    );
  });

  test('deletes an existing run directory', () async {
    final documents = await Directory.systemTemp.createTemp(
      'flutter-matter-run-',
    );
    addTearDown(() => documents.delete(recursive: true));
    final store = RunDirectory(documentsDirectory: () async => documents);
    await store.create('delete-me');

    await store.delete('delete-me');

    expect(await store.find('delete-me'), isNull);
  });
}
