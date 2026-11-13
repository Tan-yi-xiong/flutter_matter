import 'dart:async';

import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/report/device_test_report.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/fakes.dart';

class ScriptedCase implements DeviceTestCase {
  ScriptedCase(this.id, this.handler);

  @override
  final DeviceTestId id;
  final FutureOr<TestCaseOutcome> Function(TestContext context) handler;
  int calls = 0;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    calls++;
    return handler(context);
  }
}

class PassCase extends ScriptedCase {
  PassCase(DeviceTestId id) : super(id, (_) => const TestCaseOutcome.passed());
}

TestCaseRegistry scriptedRegistry({
  Map<DeviceTestId, DeviceTestCase> overrides = const {},
}) {
  return TestCaseRegistry(<DeviceTestCase>[
    for (final id in DeviceTestCatalog.all) overrides[id] ?? PassCase(id),
  ]);
}

RunStartRequest startRequest(TestProfile profile) {
  final session = makeSession(profile: profile);
  return RunStartRequest(
    runId: session.id,
    profile: profile,
    testApp: session.testApp,
    pluginCommit: session.pluginCommit,
    controller: session.controller!,
    commissionee: session.commissionee!,
    targetNodeId: 1,
  );
}

RunSession sessionWithRunningTest(DeviceTestId runningTest) {
  final base = makeSession();
  var session = base;
  for (final id in DeviceTestCatalog.all) {
    if (id == runningTest) {
      session = session.startTest(id, at: testNow);
      break;
    }
    session = session.recordResult(
      DeviceTestResult(testId: id, status: DeviceTestStatus.passed),
      at: testNow,
    );
  }
  return session;
}

void main() {
  group('RunCoordinator happy path', () {
    test(
      'quick profile executes four cases and never builds formal evidence',
      () async {
        final hardware = FakeHardware();
        final persistence = MemoryRunPersistencePort();
        final prompts = FakeOperatorPromptPort();
        final clock = FakeClock();
        final screenshot = FakeScreenshotPort();
        final hooks = RecordingHooksPort();
        final ports = hardware.applicationPorts(
          persistence: persistence,
          secrets: FakeSecretAccessPort(makeSecrets()),
          prompts: prompts,
          clock: clock,
          screenshot: screenshot,
          hooks: hooks,
        );
        final coordinator = RunCoordinator(
          ports: ports,
          timeouts: fastTimeouts,
        );
        addTearDown(coordinator.dispose);

        final snapshot = await coordinator.start(
          startRequest(TestProfile.quick),
        );

        expect(snapshot.status, RunnerStatus.passed);
        expect(snapshot.session!.profile, TestProfile.quick);
        expect(snapshot.session!.allResultsTerminal, isTrue);
        expect(
          snapshot.session!.orderedResults.map((result) => result.testId),
          DeviceTestCatalog.quickTestIds,
        );
        expect(
          await coordinator.buildFormalReport(
            generatedAt: testNow,
            sanitizationReviewed: true,
          ),
          isNull,
        );
        expect(hooks.states.length, greaterThan(5));
        expect(hooks.states, isNotEmpty);
        expect(
          hooks.events.map((event) => event.type),
          contains(RunnerEventType.runCompleted),
        );
      },
    );

    test(
      'full profile reaches 11 terminal results and sanitized state',
      () async {
        final hardware = FakeHardware();
        final persistence = MemoryRunPersistencePort();
        final prompts = FakeOperatorPromptPort(
          handler: (prompt) {
            if (prompt.id == 'onoff_subscription_external_change') {
              hardware.onOff.pushUpdate(hardware.onOff.currentState.toggled);
            } else if (prompt.id == 'remove_fabric_ui') {
              hardware.fabric.status = const FabricStatus(present: false);
            }
            return OperatorDecision.confirmed();
          },
        );
        final ports = hardware.applicationPorts(
          persistence: persistence,
          secrets: FakeSecretAccessPort(makeSecrets()),
          prompts: prompts,
          clock: FakeClock(),
          screenshot: FakeScreenshotPort(),
          hooks: RecordingHooksPort(),
        );
        final coordinator = RunCoordinator(
          ports: ports,
          timeouts: fastTimeouts,
        );
        addTearDown(coordinator.dispose);

        final snapshot = await coordinator.start(
          startRequest(TestProfile.full),
        );

        expect(snapshot.status, RunnerStatus.passed);
        expect(snapshot.session!.allResultsTerminal, isTrue);
        expect(snapshot.session!.orderedResults.length, 11);
        expect(
          snapshot.session!.orderedResults.every(
            (result) => result.status == DeviceTestStatus.passed,
          ),
          isTrue,
        );
        expect('${snapshot.toJson()}', isNot(contains('correct')));
        expect(persistence.cleanupCount, 2); // start + finalize

        final report = await coordinator.buildFormalReport(
          generatedAt: testNow,
          sanitizationReviewed: true,
        );
        expect(report, isNotNull);
        expect(report!.summary.result, ReportResult.passed);
      },
    );
  });

  group('RunCoordinator failure policy', () {
    test(
      'P0 failure stops the run and marks remaining tests not_run',
      () async {
        final hardware = FakeHardware();
        final persistence = MemoryRunPersistencePort();
        final ports = hardware.applicationPorts(
          persistence: persistence,
          secrets: FakeSecretAccessPort(makeSecrets()),
          prompts: FakeOperatorPromptPort(),
          clock: FakeClock(),
        );
        final failing = ScriptedCase(
          DeviceTestId.commissioning,
          (_) => TestCaseOutcome.failed('commissioning failed'),
        );
        final coordinator = RunCoordinator(
          ports: ports,
          registry: scriptedRegistry(
            overrides: {DeviceTestId.commissioning: failing},
          ),
          timeouts: fastTimeouts,
        );
        addTearDown(coordinator.dispose);

        final snapshot = await coordinator.start(
          startRequest(TestProfile.full),
        );

        expect(snapshot.status, RunnerStatus.failed);
        expect(failing.calls, 1);
        expect(
          snapshot.session!.results[DeviceTestId.commissioning]!.status,
          DeviceTestStatus.failed,
        );
        expect(
          snapshot
              .session!
              .results[DeviceTestId.factoryResetRecommission]!
              .status,
          DeviceTestStatus.notRun,
        );
        expect(
          snapshot.session!.results[DeviceTestId.invalidWifiPassword]!.status,
          DeviceTestStatus.notRun,
        );
        expect(snapshot.session!.allResultsTerminal, isTrue);
      },
    );

    test('P0 skip also stops the run and records reasons', () async {
      final hardware = FakeHardware();
      final persistence = MemoryRunPersistencePort();
      final ports = hardware.applicationPorts(
        persistence: persistence,
        secrets: FakeSecretAccessPort(makeSecrets()),
        prompts: FakeOperatorPromptPort(),
        clock: FakeClock(),
      );
      final skipped = ScriptedCase(
        DeviceTestId.commissioning,
        (_) => TestCaseOutcome.notRun('commissioning unavailable'),
      );
      final coordinator = RunCoordinator(
        ports: ports,
        registry: scriptedRegistry(
          overrides: {DeviceTestId.commissioning: skipped},
        ),
        timeouts: fastTimeouts,
      );
      addTearDown(coordinator.dispose);

      final snapshot = await coordinator.start(startRequest(TestProfile.full));

      expect(snapshot.status, RunnerStatus.notRun);
      expect(
        snapshot.session!.results[DeviceTestId.operationalConnect]!.status,
        DeviceTestStatus.notRun,
      );
      expect(
        snapshot.session!.results[DeviceTestId.operationalConnect]!.notes,
        contains('commissioning not_run'),
      );
    });

    test('app_restart P1 failure does not stop later cases', () async {
      final hardware = FakeHardware();
      final persistence = MemoryRunPersistencePort();
      final ports = hardware.applicationPorts(
        persistence: persistence,
        secrets: FakeSecretAccessPort(makeSecrets()),
        prompts: FakeOperatorPromptPort(),
        clock: FakeClock(),
      );
      final appRestart = ScriptedCase(
        DeviceTestId.appRestart,
        (_) => TestCaseOutcome.failed('reconnect failed'),
      );
      final factoryReset = ScriptedCase(
        DeviceTestId.factoryResetRecommission,
        (_) => const TestCaseOutcome.passed(),
      );
      final coordinator = RunCoordinator(
        ports: ports,
        registry: scriptedRegistry(
          overrides: {
            DeviceTestId.appRestart: appRestart,
            DeviceTestId.factoryResetRecommission: factoryReset,
          },
        ),
        timeouts: fastTimeouts,
      );
      addTearDown(coordinator.dispose);

      final snapshot = await coordinator.start(startRequest(TestProfile.full));

      expect(snapshot.status, RunnerStatus.failed);
      expect(factoryReset.calls, 1);
      expect(
        snapshot
            .session!
            .results[DeviceTestId.factoryResetRecommission]!
            .status,
        DeviceTestStatus.passed,
      );
    });

    test('factory-reset P1 failure stops the remaining P2 sequence', () async {
      final hardware = FakeHardware();
      final persistence = MemoryRunPersistencePort();
      final ports = hardware.applicationPorts(
        persistence: persistence,
        secrets: FakeSecretAccessPort(makeSecrets()),
        prompts: FakeOperatorPromptPort(),
        clock: FakeClock(),
      );
      final factoryReset = ScriptedCase(
        DeviceTestId.factoryResetRecommission,
        (_) => TestCaseOutcome.failed('factory reset failed'),
      );
      final invalidWifi = ScriptedCase(
        DeviceTestId.invalidWifiPassword,
        (_) => const TestCaseOutcome.passed(),
      );
      final coordinator = RunCoordinator(
        ports: ports,
        registry: scriptedRegistry(
          overrides: {
            DeviceTestId.factoryResetRecommission: factoryReset,
            DeviceTestId.invalidWifiPassword: invalidWifi,
          },
        ),
        timeouts: fastTimeouts,
      );
      addTearDown(coordinator.dispose);

      final snapshot = await coordinator.start(startRequest(TestProfile.full));

      expect(invalidWifi.calls, 0);
      expect(
        snapshot.session!.results[DeviceTestId.invalidWifiPassword]!.status,
        DeviceTestStatus.notRun,
      );
      expect(snapshot.session!.allResultsTerminal, isTrue);
    });

    test('P2 failure is recorded and later cases continue', () async {
      final hardware = FakeHardware();
      final persistence = MemoryRunPersistencePort();
      final ports = hardware.applicationPorts(
        persistence: persistence,
        secrets: FakeSecretAccessPort(makeSecrets()),
        prompts: FakeOperatorPromptPort(),
        clock: FakeClock(),
      );
      final invalidSetup = ScriptedCase(
        DeviceTestId.invalidSetupPasscode,
        (_) => TestCaseOutcome.failed('invalid passcode was accepted'),
      );
      final invalidWifi = ScriptedCase(
        DeviceTestId.invalidWifiPassword,
        (_) => const TestCaseOutcome.passed(),
      );
      final removeFabric = ScriptedCase(
        DeviceTestId.removeFabricUi,
        (_) => const TestCaseOutcome.passed(),
      );
      final coordinator = RunCoordinator(
        ports: ports,
        registry: scriptedRegistry(
          overrides: {
            DeviceTestId.invalidSetupPasscode: invalidSetup,
            DeviceTestId.invalidWifiPassword: invalidWifi,
            DeviceTestId.removeFabricUi: removeFabric,
          },
        ),
        timeouts: fastTimeouts,
      );
      addTearDown(coordinator.dispose);

      final snapshot = await coordinator.start(startRequest(TestProfile.full));

      expect(invalidWifi.calls, 1);
      expect(removeFabric.calls, 1);
      expect(snapshot.status, RunnerStatus.failed);
      expect(snapshot.session!.allResultsTerminal, isTrue);
    });

    test('case timeout is converted into a failed result', () async {
      final hardware = FakeHardware();
      final persistence = MemoryRunPersistencePort();
      final ports = hardware.applicationPorts(
        persistence: persistence,
        secrets: FakeSecretAccessPort(makeSecrets()),
        prompts: FakeOperatorPromptPort(),
        clock: FakeClock(),
      );
      final hanging = ScriptedCase(
        DeviceTestId.onoffInvoke,
        (_) => Completer<TestCaseOutcome>().future,
      );
      final coordinator = RunCoordinator(
        ports: ports,
        registry: scriptedRegistry(
          overrides: {DeviceTestId.onoffInvoke: hanging},
        ),
        timeouts: const TestTimeouts(
          buildInstall: Duration(milliseconds: 100),
          commissioning: Duration(milliseconds: 100),
          operationalConnect: Duration(milliseconds: 100),
          onOffInvoke: Duration(milliseconds: 10),
          onOffSubscription: Duration(milliseconds: 100),
          nodeLabelPersistence: Duration(milliseconds: 100),
          appRestart: Duration(milliseconds: 100),
          factoryResetRecommission: Duration(milliseconds: 100),
          invalidSetupPasscode: Duration(milliseconds: 100),
          invalidWifiPassword: Duration(milliseconds: 100),
          removeFabricUi: Duration(milliseconds: 100),
        ),
      );
      addTearDown(coordinator.dispose);

      final snapshot = await coordinator.start(startRequest(TestProfile.quick));

      expect(snapshot.status, RunnerStatus.failed);
      final result = snapshot.session!.results[DeviceTestId.onoffInvoke]!;
      expect(result.status, DeviceTestStatus.failed);
      expect(result.notes, contains('Timed out'));
    });
  });

  group('RunCoordinator prompt routing', () {
    test('exposes waiting state and persists an active human prompt', () async {
      final hardware = FakeHardware();
      final persistence = MemoryRunPersistencePort();
      final promptCompleter = Completer<OperatorDecision>();
      final prompts = FakeOperatorPromptPort(
        handler: (_) => promptCompleter.future,
      );
      final ports = hardware.applicationPorts(
        persistence: persistence,
        secrets: FakeSecretAccessPort(makeSecrets()),
        prompts: prompts,
        clock: FakeClock(),
      );
      final promptCase = ScriptedCase(DeviceTestId.onoffInvoke, (
        context,
      ) async {
        final decision = await context.prompt(
          const OperatorPrompt(
            id: 'human_check',
            title: 'Human check',
            instructions: 'Confirm the human check.',
            requiredActor: RequiredActor.human,
            testId: DeviceTestId.onoffInvoke,
          ),
        );
        return decision.isConfirmed
            ? const TestCaseOutcome.passed()
            : TestCaseOutcome.notRun('not confirmed');
      });
      final coordinator = RunCoordinator(
        ports: ports,
        registry: scriptedRegistry(
          overrides: {DeviceTestId.onoffInvoke: promptCase},
        ),
        timeouts: fastTimeouts,
      );
      addTearDown(coordinator.dispose);

      final runFuture = coordinator.start(startRequest(TestProfile.quick));
      await Future<void>.delayed(Duration.zero);
      expect(coordinator.snapshot.status, RunnerStatus.waitingForHuman);

      promptCompleter.complete(OperatorDecision.confirmed());
      final snapshot = await runFuture;
      expect(snapshot.status, RunnerStatus.passed);
    });
  });
}
