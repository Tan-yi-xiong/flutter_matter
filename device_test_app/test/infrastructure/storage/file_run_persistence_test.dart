import 'dart:io';

import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/file_run_persistence.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/storage/run_directory.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  late Directory documents;
  late RunDirectory runDirectory;
  late FileRunPersistence persistence;
  final startedAt = DateTime.utc(2026, 11, 11, 12);

  setUp(() async {
    documents = await Directory.systemTemp.createTemp(
      'flutter-matter-persistence-',
    );
    runDirectory = RunDirectory(documentsDirectory: () async => documents);
    persistence = FileRunPersistence(runDirectory: runDirectory);
  });

  tearDown(() async {
    if (await documents.exists()) {
      await documents.delete(recursive: true);
    }
  });

  RunSession sessionFor({required String id, required DateTime updatedAt}) {
    return RunSession.start(
      id: id,
      profile: TestProfile.quick,
      testApp: const TestAppMetadata(
        name: 'device-test-app',
        version: '1.0.0',
        commit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
      ),
      pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
      startedAt: startedAt,
    ).withPhase(RunPhase.testing, at: updatedAt);
  }

  PersistedRunState stateFor(String id, {required DateTime updatedAt}) {
    return PersistedRunState(
      session: sessionFor(id: id, updatedAt: updatedAt),
      execution: const RunExecutionContextSnapshot(),
      targetNodeId: 1,
    );
  }

  test('round-trips the complete unfinished run state', () async {
    final checkpoint = const AppRestartCheckpoint(
      stage: AppRestartCheckpointStage.awaitingReconnect,
      identityOpaqueId: 'identity-main',
      nodeId: 17,
    );
    final prompt = const OperatorPrompt(
      id: 'prompt-onoff',
      title: 'Toggle the light',
      instructions: 'Toggle the commissionee and confirm the state changed.',
      requiredActor: RequiredActor.agentAndroid,
      testId: DeviceTestId.onoffInvoke,
      confirmLabel: 'State changed',
      canSkip: false,
      skipRequiresReason: false,
    );
    final session = sessionFor(
      id: 'run-round-trip',
      updatedAt: startedAt.add(const Duration(minutes: 2)),
    ).startTest(DeviceTestId.buildInstall, at: startedAt);
    final state = PersistedRunState(
      session: session,
      execution: const RunExecutionContextSnapshot(
        identityOpaqueId: 'identity-main',
        identityPurpose: ControllerIdentityPurpose.invalidWifiPassword,
        nodeId: 17,
        networkTransport: NetworkTransport.thread,
        lastOnOffState: OnOffState.off,
      ),
      targetNodeId: 17,
      appRestartCheckpoint: checkpoint,
      activePrompt: ActiveOperatorPromptSnapshot(
        testId: DeviceTestId.onoffInvoke,
        prompt: prompt,
      ),
    );

    await persistence.save(state);
    final loaded = await persistence.loadUnfinished();

    expect(loaded, isNotNull);
    expect(loaded!.session.id, session.id);
    expect(loaded.session.phase, session.phase);
    expect(loaded.session.updatedAt, session.updatedAt);
    expect(
      loaded.session.results[DeviceTestId.buildInstall]!.status,
      DeviceTestStatus.running,
    );
    expect(loaded.targetNodeId, 17);
    expect(loaded.execution.identityOpaqueId, 'identity-main');
    expect(
      loaded.execution.identityPurpose,
      ControllerIdentityPurpose.invalidWifiPassword,
    );
    expect(loaded.execution.nodeId, 17);
    expect(loaded.execution.networkTransport, NetworkTransport.thread);
    expect(loaded.execution.lastOnOffState, OnOffState.off);
    expect(
      loaded.appRestartCheckpoint?.stage,
      AppRestartCheckpointStage.awaitingReconnect,
    );
    expect(loaded.appRestartCheckpoint?.identityOpaqueId, 'identity-main');
    expect(loaded.appRestartCheckpoint?.nodeId, 17);
    expect(loaded.activePrompt?.testId, DeviceTestId.onoffInvoke);
    expect(loaded.activePrompt?.prompt.id, 'prompt-onoff');
    expect(
      loaded.activePrompt?.prompt.requiredActor,
      RequiredActor.agentAndroid,
    );
    expect(loaded.activePrompt?.prompt.canSkip, isFalse);
    expect(loaded.activePrompt?.prompt.skipRequiresReason, isFalse);

    final stateFile = File(
      '${documents.path}/runs/${session.id}/${FileRunPersistence.stateFileName}',
    );
    expect(await stateFile.exists(), isTrue);
    expect(
      await File(
        '${documents.path}/runs/${session.id}/.${FileRunPersistence.stateFileName}.tmp',
      ).exists(),
      isFalse,
    );
  });

  test('selects the newest unfinished run by session update time', () async {
    await persistence.save(
      stateFor('run-old', updatedAt: startedAt.add(const Duration(minutes: 1))),
    );
    await persistence.save(
      stateFor('run-new', updatedAt: startedAt.add(const Duration(minutes: 3))),
    );
    await persistence.save(
      stateFor(
        'run-middle',
        updatedAt: startedAt.add(const Duration(minutes: 2)),
      ),
    );

    final loaded = await persistence.loadUnfinished();

    expect(loaded?.session.id, 'run-new');
  });

  test('uses the run id as a deterministic tie-break', () async {
    final sameTime = startedAt.add(const Duration(minutes: 2));
    await persistence.save(stateFor('run-alpha', updatedAt: sameTime));
    await persistence.save(stateFor('run-zulu', updatedAt: sameTime));

    final loaded = await persistence.loadUnfinished();

    expect(loaded?.session.id, 'run-zulu');
  });

  test('ignores terminal runs when selecting unfinished state', () async {
    final terminal = sessionFor(
      id: 'run-terminal',
      updatedAt: startedAt.add(const Duration(minutes: 5)),
    ).withPhase(RunPhase.failed, at: startedAt.add(const Duration(minutes: 5)));
    await persistence.save(
      PersistedRunState(
        session: terminal,
        execution: const RunExecutionContextSnapshot(),
        targetNodeId: 1,
      ),
    );
    await persistence.save(
      stateFor(
        'run-unfinished',
        updatedAt: startedAt.add(const Duration(minutes: 2)),
      ),
    );

    final loaded = await persistence.loadUnfinished();

    expect(loaded?.session.id, 'run-unfinished');
    expect(loaded?.session.phase.isTerminal, isFalse);
  });

  test('ignores corrupt run state and still returns a valid run', () async {
    final corruptDirectory = await runDirectory.create('run-corrupt');
    await File(
      '${corruptDirectory.path}/${FileRunPersistence.stateFileName}',
    ).writeAsString('{"snapshot_version":1,"session":');
    await persistence.save(
      stateFor(
        'run-valid',
        updatedAt: startedAt.add(const Duration(minutes: 2)),
      ),
    );

    final loaded = await persistence.loadUnfinished();

    expect(loaded?.session.id, 'run-valid');
  });

  test(
    'clears only the newest unfinished state and preserves artifacts',
    () async {
      final older = stateFor(
        'run-older',
        updatedAt: startedAt.add(const Duration(minutes: 1)),
      );
      final newest = stateFor(
        'run-newest',
        updatedAt: startedAt.add(const Duration(minutes: 4)),
      );
      await persistence.save(older);
      await persistence.save(newest);

      final newestDirectory = await runDirectory.find('run-newest');
      final report = File('${newestDirectory!.path}/report.json');
      await report.writeAsString('{"status":"preserved"}');

      await persistence.clearUnfinished();

      expect(await persistence.loadUnfinished(), isNotNull);
      expect((await persistence.loadUnfinished())?.session.id, 'run-older');
      expect(
        await File(
          '${newestDirectory.path}/${FileRunPersistence.stateFileName}',
        ).exists(),
        isFalse,
      );
      expect(await report.exists(), isTrue);
      expect(await report.readAsString(), '{"status":"preserved"}');
      expect(await runDirectory.find('run-older'), isNotNull);
      expect(await runDirectory.find('run-newest'), isNotNull);
    },
  );
}
