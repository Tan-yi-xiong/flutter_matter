import 'dart:async';

import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/app_restart_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/build_install_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/commissioning_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/invalid_setup_passcode_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/node_label_read_write_case.dart';
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
      'passes by triggering the state change and observing the update',
      () async {
        final hardware = FakeHardware();
        final context = TestContextHarness(
          testId: DeviceTestId.onoffSubscription,
          ports: hardware.ports,
        ).build();

        final outcome = await const OnOffSubscriptionCase().execute(context);

        expect(outcome.status, DeviceTestStatus.passed);
        expect(hardware.onOff.invokedCommands, [OnOffCommand.toggle]);
        expect(hardware.onOff.cancelCount, 1);
      },
    );

    test('fails when the trigger command does not change state', () async {
      final hardware = FakeHardware();
      hardware.onOff.handler = (connection, command, timeout) async {
        return OnOffInvocation(
          previousState: hardware.onOff.currentState,
          currentState: hardware.onOff.currentState,
        );
      };
      final context = TestContextHarness(
        testId: DeviceTestId.onoffSubscription,
        ports: hardware.ports,
      ).build();

      final outcome = await const OnOffSubscriptionCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(
        outcome.notes,
        contains('trigger command did not change the commissionee state'),
      );
    });

    test(
      'fails when no subscription update arrives before the timeout',
      () async {
        final hardware = FakeHardware();
        hardware.onOff.handler = (connection, command, timeout) async {
          // Report a state change without pushing it to the subscription.
          return const OnOffInvocation(
            previousState: OnOffState.on,
            currentState: OnOffState.off,
          );
        };
        final context = TestContextHarness(
          testId: DeviceTestId.onoffSubscription,
          ports: hardware.ports,
        ).build();

        final outcome = await const OnOffSubscriptionCase().execute(context);

        expect(outcome.status, DeviceTestStatus.failed);
        expect(outcome.notes, contains('No OnOff subscription update arrived'));
      },
    );
  });

  group('node_label_read_write', () {
    test('passes a write/read round trip without prompts', () async {
      final hardware = FakeHardware();
      final harness = TestContextHarness(
        testId: DeviceTestId.nodeLabelReadWrite,
        ports: hardware.ports,
      );
      final context = harness.build();

      final outcome = await const NodeLabelReadWriteCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.nodeLabel.writeCount, 1);
      expect(hardware.nodeLabel.readCount, 1);
      expect(hardware.operational.reconnectCount, 0);
      expect(harness.prompts, isEmpty);
    });

    test('fails when the readback does not match the written value', () async {
      final hardware = FakeHardware();
      hardware.nodeLabel.readHandler = () async => 'changed';
      final context = TestContextHarness(
        testId: DeviceTestId.nodeLabelReadWrite,
        ports: hardware.ports,
      ).build();

      final outcome = await const NodeLabelReadWriteCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('did not match'));
    });

    test('returns not_run without identity or node context', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.nodeLabelReadWrite,
        ports: hardware.ports,
        execution: RunExecutionContext(),
      ).build();

      final outcome = await const NodeLabelReadWriteCase().execute(context);

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

  group('invalid_setup_passcode', () {
    test('passes when the wrong passcode fails commissioning', () async {
      final hardware = FakeHardware();
      final harness = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
      );
      final context = harness.build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.commissioningWindow.openCount, 1);
      expect(hardware.commissioningWindow.discriminators.single, 3840);
      expect(hardware.commissioningWindow.setupPinCodes.single, 20202021);
      expect(hardware.commissioning.requests.single.setupPinCode, 20202022);
      expect(hardware.identity.resetCount, 0);
      expect(hardware.identity.requests, isEmpty);
      expect(
        hardware.commissioning.requests.single.identity.purpose,
        ControllerIdentityPurpose.main,
      );
      expect(
        hardware.commissioning.requests.single.onNetworkEndpoint?.address,
        '127.0.0.1',
      );
      expect(harness.prompts, isEmpty);
    });

    test('fails when the wrong passcode is accepted', () async {
      final hardware = FakeHardware();
      hardware.commissioning.handler = (_) async =>
          const CommissioningResult(errorCode: 0, nodeId: 1);
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('incorrectly reported success'));
    });

    test('fails when the commissioning window cannot open', () async {
      final hardware = FakeHardware();
      hardware.commissioningWindow.openError =
          CommissioningWindowFailureCode.openFailed;
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('open_failed'));
    });

    test('returns not_run without a setup discriminator', () async {
      final hardware = FakeHardware();
      final secrets = makeSecrets();
      final noDiscriminator = ProvisioningSecrets(
        onboardingPayload: secrets.onboardingPayload,
        invalidSetupOnboardingPayload: secrets.invalidSetupOnboardingPayload,
        setupPinCode: secrets.setupPinCode,
        network: secrets.network,
      );
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
        secrets: noDiscriminator,
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });
}
