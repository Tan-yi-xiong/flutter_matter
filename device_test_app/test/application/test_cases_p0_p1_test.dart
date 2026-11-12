import 'dart:async';

import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/app_restart_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/build_install_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/commissioning_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/commissioning_discovery_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/factory_reset_recommission_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/node_label_persistence_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/onoff_invoke_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/onoff_subscription_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/operational_connect_case.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/fakes.dart';

void main() {
  group('build_install', () {
    test(
      'passes when test-app metadata and controller identity are available',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.buildInstall,
          ports: hardware.ports,
          execution: makeExecution(
            withIdentity: false,
            withNode: false,
            withConnection: false,
          ),
        ).build();

        final outcome = await const BuildInstallCase().execute(context);

        expect(outcome.status, DeviceTestStatus.passed);
        expect(outcome.notes, contains('identity'));
        expect(hardware.identity.requests, isNotEmpty);
      },
    );

    test('returns not_run when controller metadata is missing', () async {
      final session = RunSession.start(
        id: 'run-missing-metadata',
        profile: TestProfile.full,
        testApp: const TestAppMetadata(
          name: 'flutter_matter_device_test_app',
          version: '1.0.0',
          commit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        ),
        pluginCommit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
        startedAt: testNow,
      );
      final context = TestContextHarness(
        testId: DeviceTestId.buildInstall,
        session: session,
      ).build();

      final outcome = await const BuildInstallCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });

  group('commissioning_discovery', () {
    test('matches an IP commissionee and records the selected route', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioningDiscovery,
        ports: hardware.ports,
      ).build();

      final outcome = await const CommissioningDiscoveryCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(outcome.notes, contains('ip'));
      expect(
        hardware.commissioningDiscovery.requests.single.onboardingPayload,
        'MT:TEST-ONBOARDING-PAYLOAD',
      );
      expect(
        hardware.commissioningDiscovery.requests.single.timeout,
        fastTimeouts.commissioningDiscovery,
      );
      expect(
        context.execution.commissioningTransport,
        CommissioningTransport.ip,
      );
      expect(context.execution.target, isNull);
    });

    test('matches a BLE commissionee and records its live target', () async {
      final hardware = FakeHardware(
        commissioningDiscovery: FakeCommissioningDiscoveryPort(
          transport: CommissioningTransport.ble,
          bleTarget: const BleCommissionee(
            opaqueId: 'ble-opaque',
            displayName: 'BLE commissionee',
          ),
        ),
      );
      final context = TestContextHarness(
        testId: DeviceTestId.commissioningDiscovery,
        ports: hardware.ports,
      ).build();

      final outcome = await const CommissioningDiscoveryCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(outcome.notes, contains('ble'));
      expect(
        context.execution.commissioningTransport,
        CommissioningTransport.ble,
      );
      expect(context.execution.target?.opaqueId, 'ble-opaque');
    });

    test('returns not_run without provisioning secrets', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioningDiscovery,
        ports: hardware.ports,
        withSecrets: false,
      ).build();

      final outcome = await const CommissioningDiscoveryCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
      expect(hardware.commissioningDiscovery.requests, isEmpty);
      expect(context.execution.commissioningTransport, isNull);
    });

    test(
      'fails on a typed discovery failure without selecting a route',
      () async {
        final hardware = FakeHardware()
          ..commissioningDiscovery.failureCode =
              CommissioningDiscoveryFailureCode.noCommissionableDevice;
        final context = TestContextHarness(
          testId: DeviceTestId.commissioningDiscovery,
          ports: hardware.ports,
        ).build();

        final outcome = await const CommissioningDiscoveryCase().execute(
          context,
        );

        expect(outcome.status, DeviceTestStatus.failed);
        expect(outcome.notes, contains('no_commissionable_device'));
        expect(context.execution.commissioningTransport, isNull);
        expect(context.execution.target, isNull);
      },
    );

    test('fails when discovery times out', () async {
      final hardware = FakeHardware()
        ..commissioningDiscovery.handler = (_) async =>
            throw TimeoutException('discovery timeout');
      final context = TestContextHarness(
        testId: DeviceTestId.commissioningDiscovery,
        ports: hardware.ports,
      ).build();

      final outcome = await const CommissioningDiscoveryCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('timed out'));
      expect(context.execution.commissioningTransport, isNull);
    });
  });

  group('commissioning', () {
    test('uses the IP route selected by discovery', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
      ).build();

      final discoveryOutcome = await const CommissioningDiscoveryCase().execute(
        context,
      );
      final outcome = await const CommissioningCase().execute(context);

      expect(discoveryOutcome.status, DeviceTestStatus.passed);
      expect(outcome.status, DeviceTestStatus.passed);
      expect(outcome.notes, contains('ip'));
      expect(context.execution.nodeId, 1);
      expect(context.execution.networkTransport, NetworkTransport.wifi);
      expect(hardware.commissioningDiscovery.requests, hasLength(1));
      expect(hardware.commissioning.requests.single.target, isNull);
      expect(
        hardware.commissioning.requests.single.commissioningTransport,
        CommissioningTransport.ip,
      );
    });

    test('uses the BLE route and target selected by discovery', () async {
      final hardware = FakeHardware(
        commissioningDiscovery: FakeCommissioningDiscoveryPort(
          transport: CommissioningTransport.ble,
          bleTarget: const BleCommissionee(
            opaqueId: 'ble-opaque',
            displayName: 'BLE commissionee',
          ),
        ),
      );
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
      ).build();

      final discoveryOutcome = await const CommissioningDiscoveryCase().execute(
        context,
      );
      final outcome = await const CommissioningCase().execute(context);

      expect(discoveryOutcome.status, DeviceTestStatus.passed);
      expect(outcome.status, DeviceTestStatus.passed);
      expect(outcome.notes, contains('ble'));
      expect(
        hardware.commissioning.requests.single.target?.opaqueId,
        'ble-opaque',
      );
      expect(
        hardware.commissioning.requests.single.commissioningTransport,
        CommissioningTransport.ble,
      );
    });

    test('does not rediscover when commissioning is resumed', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      ).build();

      final outcome = await const CommissioningCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.commissioningDiscovery.requests, isEmpty);
      expect(
        hardware.commissioning.requests.single.commissioningTransport,
        CommissioningTransport.ip,
      );
    });

    test(
      'does not attempt a fallback route after commissioning fails',
      () async {
        final transportRequests = <CommissioningTransport>[];
        final hardware = FakeHardware()
          ..commissioning.handler = (request) async {
            transportRequests.add(request.commissioningTransport);
            return const CommissioningResult(errorCode: 7);
          };
        final context = TestContextHarness(
          testId: DeviceTestId.commissioning,
          ports: hardware.ports,
        ).build();

        final discoveryOutcome = await const CommissioningDiscoveryCase()
            .execute(context);
        final outcome = await const CommissioningCase().execute(context);

        expect(discoveryOutcome.status, DeviceTestStatus.passed);
        expect(outcome.status, DeviceTestStatus.failed);
        expect(outcome.notes, contains('7'));
        expect(transportRequests, <CommissioningTransport>[
          CommissioningTransport.ip,
        ]);
        expect(hardware.commissioning.requests, hasLength(1));
      },
    );

    test('fails when discovery did not select a route', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
        execution: makeExecution(),
      ).build();

      final outcome = await const CommissioningCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('did not select a transport'));
      expect(hardware.commissioning.requests, isEmpty);
    });

    test('fails on a non-zero commissioning result', () async {
      final hardware = FakeHardware();
      hardware.commissioning.handler = (_) async =>
          const CommissioningResult(errorCode: 17);
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      ).build();

      final outcome = await const CommissioningCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('17'));
    });

    test('returns not_run without provisioning secrets', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
        withSecrets: false,
      ).build();

      final outcome = await const CommissioningCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });

  group('operational_connect', () {
    test('passes with a valid connection lease', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.operationalConnect,
        ports: hardware.ports,
      ).build();

      final outcome = await const OperationalConnectCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(context.execution.connection, isNotNull);
    });

    test('fails with an invalid connection lease', () async {
      final hardware = FakeHardware()..operational.connectValid = false;
      final context = TestContextHarness(
        testId: DeviceTestId.operationalConnect,
        ports: hardware.ports,
      ).build();

      final outcome = await const OperationalConnectCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
    });

    test('returns not_run without controller context', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.operationalConnect,
        ports: hardware.ports,
        execution: makeExecution(
          withIdentity: false,
          withNode: false,
          withConnection: false,
        ),
      ).build();

      final outcome = await const OperationalConnectCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });

  group('onoff_invoke', () {
    test('passes when Off, On, and Toggle all change state', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.onoffInvoke,
        ports: hardware.ports,
      ).build();

      final outcome = await const OnOffInvokeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(
        hardware.onOff.invokedCommands,
        containsAll(<OnOffCommand>[
          OnOffCommand.off,
          OnOffCommand.on,
          OnOffCommand.toggle,
        ]),
      );
    });

    test('establishes On before changing to Off when starting Off', () async {
      final hardware = FakeHardware()..onOff.currentState = OnOffState.off;
      final context = TestContextHarness(
        testId: DeviceTestId.onoffInvoke,
        ports: hardware.ports,
      ).build();

      final outcome = await const OnOffInvokeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.onOff.invokedCommands.first, OnOffCommand.on);
    });

    test('fails when an invocation does not change state', () async {
      final hardware = FakeHardware()
        ..onOff.currentState = OnOffState.off
        ..onOff.handler = (_, _, _) async => const OnOffInvocation(
          previousState: OnOffState.off,
          currentState: OnOffState.off,
        );
      final context = TestContextHarness(
        testId: DeviceTestId.onoffInvoke,
        ports: hardware.ports,
      ).build();

      final outcome = await const OnOffInvokeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('setup'));
    });

    test(
      'restores a lost connection from persisted identity and node',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.onoffInvoke,
          ports: hardware.ports,
          execution: makeExecution(withConnection: false),
        ).build();

        final outcome = await const OnOffInvokeCase().execute(context);

        expect(outcome.status, DeviceTestStatus.passed);
        expect(hardware.operational.reconnectCount, 1);
      },
    );

    test('returns not_run without an operational connection', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.onoffInvoke,
        ports: hardware.ports,
        execution: makeExecution(
          withIdentity: false,
          withNode: false,
          withConnection: false,
        ),
      ).build();

      final outcome = await const OnOffInvokeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });

  group('onoff_subscription', () {
    test(
      'passes when an external update arrives and routes the prompt',
      () async {
        final hardware = FakeHardware();
        final harness = TestContextHarness(
          testId: DeviceTestId.onoffSubscription,
          ports: hardware.ports,
          operatorHandler: (prompt) async {
            expect(prompt.requiredActor, RequiredActor.human);
            expect(prompt.testId, DeviceTestId.onoffSubscription);
            hardware.onOff.pushUpdate(OnOffState.off);
            return OperatorDecision.confirmed();
          },
        );
        final context = harness.build();

        final outcome = await const OnOffSubscriptionCase().execute(context);

        expect(outcome.status, DeviceTestStatus.passed);
        expect(harness.prompts.single.id, 'onoff_subscription_external_change');
        expect(hardware.onOff.cancelCount, 1);
      },
    );

    test(
      'returns not_run when the operator skips the external action',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.onoffSubscription,
          ports: hardware.ports,
          operatorHandler: (_) =>
              OperatorDecision.skipped('external update unavailable'),
        ).build();

        final outcome = await const OnOffSubscriptionCase().execute(context);

        expect(outcome.status, DeviceTestStatus.notRun);
        expect(outcome.notes, contains('external update unavailable'));
      },
    );

    test('fails when no external update arrives before the timeout', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.onoffSubscription,
        ports: hardware.ports,
        operatorHandler: (_) => OperatorDecision.confirmed(),
      ).build();

      final outcome = await const OnOffSubscriptionCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('external OnOff update'));
    });
  });

  group('node_label_persistence', () {
    test('passes when NodeLabel survives a commissionee restart', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.nodeLabelPersistence,
        ports: hardware.ports,
      ).build();

      final outcome = await const NodeLabelPersistenceCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.nodeLabel.writeCount, 1);
      expect(hardware.nodeLabel.readCount, 2);
      expect(hardware.operational.reconnectCount, 1);
    });

    test('fails when NodeLabel changes after the restart', () async {
      final hardware = FakeHardware();
      var reads = 0;
      hardware.nodeLabel.readHandler = () async {
        reads++;
        return reads == 1 ? 'flutter-matter-test' : 'changed';
      };
      final context = TestContextHarness(
        testId: DeviceTestId.nodeLabelPersistence,
        ports: hardware.ports,
      ).build();

      final outcome = await const NodeLabelPersistenceCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('did not survive'));
    });

    test('returns not_run when restart confirmation is skipped', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.nodeLabelPersistence,
        ports: hardware.ports,
        operatorHandler: (_) =>
            OperatorDecision.skipped('device restart unavailable'),
      ).build();

      final outcome = await const NodeLabelPersistenceCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });

  group('app_restart', () {
    test('passes after a normal restart prompt and reconnect', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.appRestart,
        ports: hardware.ports,
        operatorHandler: (prompt) async {
          expect(prompt.requiredActor, RequiredActor.agentAndroid);
          return OperatorDecision.confirmed();
        },
      ).build();

      final outcome = await const AppRestartCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.operational.reconnectCount, 1);
    });

    test(
      'passes by resuming from an app-restart checkpoint without a prompt',
      () async {
        final hardware = FakeHardware();
        final checkpoint = AppRestartCheckpoint(
          stage: AppRestartCheckpointStage.awaitingReconnect,
          identityOpaqueId: 'identity-main',
          nodeId: 1,
        );
        final harness = TestContextHarness(
          testId: DeviceTestId.appRestart,
          ports: hardware.ports,
          resumeCheckpoint: checkpoint,
        );
        final context = harness.build();

        final outcome = await const AppRestartCase().execute(context);

        expect(outcome.status, DeviceTestStatus.passed);
        expect(harness.prompts, isEmpty);
      },
    );

    test('returns not_run when restart confirmation is skipped', () async {
      final hardware = FakeHardware();
      final harness = TestContextHarness(
        testId: DeviceTestId.appRestart,
        ports: hardware.ports,
        operatorHandler: (_) => OperatorDecision.skipped('restart unavailable'),
      );
      final context = harness.build();

      final outcome = await const AppRestartCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
      expect(harness.clearedCheckpoint, isNull);
    });

    test('fails when reconnect returns an invalid connection', () async {
      final hardware = FakeHardware()..operational.reconnectValid = false;
      final context = TestContextHarness(
        testId: DeviceTestId.appRestart,
        ports: hardware.ports,
      ).build();

      final outcome = await const AppRestartCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
    });
  });

  group('factory_reset_recommission', () {
    test(
      'passes through reset, recommissioning, connection, and OnOff',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.factoryResetRecommission,
          ports: hardware.ports,
          execution: makeExecution()
            ..commissioningTransport = CommissioningTransport.ip,
        ).build();

        final outcome = await const FactoryResetRecommissionCase().execute(
          context,
        );

        expect(outcome.status, DeviceTestStatus.passed);
        expect(hardware.identity.resetCount, greaterThanOrEqualTo(1));
        expect(hardware.commissioningDiscovery.requests, isEmpty);
        expect(hardware.commissioning.requests, isNotEmpty);
        expect(hardware.onOff.invokedCommands, contains(OnOffCommand.on));
      },
    );

    test(
      'returns not_run when operator skips the factory reset prompt',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.factoryResetRecommission,
          ports: hardware.ports,
          operatorHandler: (_) =>
              OperatorDecision.skipped('factory reset unavailable'),
        ).build();

        final outcome = await const FactoryResetRecommissionCase().execute(
          context,
        );

        expect(outcome.status, DeviceTestStatus.notRun);
      },
    );

    test('fails when post-reset commissioning fails', () async {
      final hardware = FakeHardware();
      hardware.commissioning.handler = (_) async =>
          const CommissioningResult(errorCode: 23);
      final context = TestContextHarness(
        testId: DeviceTestId.factoryResetRecommission,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      ).build();

      final outcome = await const FactoryResetRecommissionCase().execute(
        context,
      );

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('23'));
    });
  });
}
