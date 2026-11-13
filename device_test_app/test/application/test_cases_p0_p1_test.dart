import 'dart:async';

import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/app_restart_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/build_install_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/commissioning_case.dart';
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

  group('commissioning', () {
    test(
      'passes the onboarding payload and network credentials to the SDK',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.commissioning,
          ports: hardware.ports,
        ).build();

        final outcome = await const CommissioningCase().execute(context);

        expect(outcome.status, DeviceTestStatus.passed);
        expect(outcome.notes, contains('error code 0'));
        expect(context.execution.nodeId, 1);
        expect(context.execution.networkTransport, NetworkTransport.wifi);

        final request = hardware.commissioning.requests.single;
        expect(request.identity.opaqueId, 'identity-main');
        expect(request.targetNodeId, 1);
        expect(request.onboardingPayload, 'MT:TEST-ONBOARDING-PAYLOAD');
        expect(request.setupPinCode, 20202021);
        expect((request.network as WifiProvisioningSecret).ssid, 'matter-lab');
        expect(request.timeout, fastTimeouts.commissioning);
      },
    );

    test('fails when commissioning times out', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
      ).build();

      hardware.commissioning.handler = (_) async =>
          throw TimeoutException('commissioning timeout');
      final outcome = await const CommissioningCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('timed out'));
    });

    test('reuses an existing SDK-managed commissioning identity', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.commissioning,
        ports: hardware.ports,
      ).build();

      final outcome = await const CommissioningCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.identity.requests, isEmpty);
    });

    test(
      'fails on a non-zero commissioning result without a fallback',
      () async {
        final hardware = FakeHardware();
        hardware.commissioning.handler = (_) async =>
            const CommissioningResult(errorCode: 17);
        final context = TestContextHarness(
          testId: DeviceTestId.commissioning,
          ports: hardware.ports,
        ).build();

        final outcome = await const CommissioningCase().execute(context);

        expect(outcome.status, DeviceTestStatus.failed);
        expect(outcome.notes, contains('17'));
        expect(hardware.commissioning.requests, hasLength(1));
      },
    );

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
    test('restarts the runtime and reconnects without a prompt', () async {
      final hardware = FakeHardware();
      final harness = TestContextHarness(
        testId: DeviceTestId.appRestart,
        ports: hardware.ports,
      );
      final context = harness.build();

      final outcome = await const AppRestartCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.operational.reconnectCount, 1);
      expect(harness.prompts, isEmpty);
    });

    test('returns not_run without identity or node context', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.appRestart,
        ports: hardware.ports,
        execution: RunExecutionContext(),
      ).build();

      final outcome = await const AppRestartCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
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
          execution: makeExecution(),
        ).build();

        final outcome = await const FactoryResetRecommissionCase().execute(
          context,
        );

        expect(outcome.status, DeviceTestStatus.passed);
        expect(hardware.identity.resetCount, greaterThanOrEqualTo(1));
        expect(
          hardware.commissioning.requests.single.onboardingPayload,
          'MT:TEST-ONBOARDING-PAYLOAD',
        );
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
        execution: makeExecution(),
      ).build();

      final outcome = await const FactoryResetRecommissionCase().execute(
        context,
      );

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('23'));
    });
  });
}
