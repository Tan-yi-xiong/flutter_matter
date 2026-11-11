import 'dart:io';

import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/run_directory.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/run_session_file_store.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  late Directory documents;
  late RunSessionFileStore store;
  final startedAt = DateTime.utc(2026, 11, 11, 12);

  setUp(() async {
    documents = await Directory.systemTemp.createTemp(
      'flutter-matter-session-',
    );
    store = RunSessionFileStore(
      runDirectory: RunDirectory(documentsDirectory: () async => documents),
    );
  });

  tearDown(() async {
    if (await documents.exists()) {
      await documents.delete(recursive: true);
    }
  });

  test('round-trips a run session and finds the unfinished run', () async {
    final session = RunSession.start(
      id: 'run-1',
      profile: TestProfile.quick,
      testApp: const TestAppMetadata(
        name: 'test-app',
        version: '1.0.0',
        commit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
      ),
      pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
      startedAt: startedAt,
    );

    await store.save(session);

    final loaded = await store.load('run-1');
    expect(loaded?.id, 'run-1');
    expect(loaded?.profile, TestProfile.quick);
    expect(await store.loadLatestUnfinished(), isNotNull);
  });

  test('does not return terminal sessions as unfinished', () async {
    final session =
        RunSession.start(
          id: 'run-2',
          profile: TestProfile.quick,
          testApp: const TestAppMetadata(
            name: 'test-app',
            version: '1.0.0',
            commit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
          ),
          pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
          startedAt: startedAt,
        ).withPhase(
          RunPhase.completed,
          at: startedAt.add(const Duration(minutes: 1)),
        );

    await store.save(session);

    expect(await store.loadLatestUnfinished(), isNull);
  });
}
