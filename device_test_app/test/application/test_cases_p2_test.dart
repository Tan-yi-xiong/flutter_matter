import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/invalid_setup_passcode_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/invalid_wifi_password_case.dart';
import 'package:flutter_matter_device_test_app/src/application/cases/remove_fabric_ui_case.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/fakes.dart';

void main() {
  group('invalid_setup_passcode', () {
    test('passes on a clear non-zero invalid-passcode failure', () async {
      final hardware = FakeHardware();
      final harness = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      );
      final context = harness.build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(
        hardware.commissioning.requests.single.setupPinCode,
        isNot(20202021),
      );
      expect(harness.prompts.length, 2);
      expect(harness.prompts.first.requiredActor, RequiredActor.human);
    });

    test('uses a typed invalid-setup failure as a clear failure', () async {
      final hardware = FakeHardware();
      hardware.commissioning.handler = (_) async {
        throw CommissioningException(CommissioningFailureCode.invalidSetupCode);
      };
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
    });

    test('fails when an invalid passcode incorrectly succeeds', () async {
      final hardware = FakeHardware();
      hardware.commissioning.handler = (_) async =>
          const CommissioningResult(errorCode: 0);
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('incorrectly reported success'));
    });

    test('returns not_run when the preparation prompt is skipped', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
        operatorHandler: (_) => OperatorDecision.skipped('device unavailable'),
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });

    test('fails when cleanup cannot be confirmed', () async {
      final hardware = FakeHardware();
      var promptCount = 0;
      final context = TestContextHarness(
        testId: DeviceTestId.invalidSetupPasscode,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
        operatorHandler: (_) {
          promptCount++;
          return promptCount == 1
              ? OperatorDecision.confirmed()
              : OperatorDecision.skipped('cleanup unavailable');
        },
      ).build();

      final outcome = await const InvalidSetupPasscodeCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('cleanup'));
    });
  });

  group('invalid_wifi_password', () {
    test('passes on a clear non-zero invalid-Wi-Fi failure', () async {
      final hardware = FakeHardware();
      final harness = TestContextHarness(
        testId: DeviceTestId.invalidWifiPassword,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      );
      final context = harness.build();

      final outcome = await const InvalidWifiPasswordCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      final network = hardware.commissioning.requests.single.network;
      expect(network, isA<WifiProvisioningSecret>());
      expect(
        (network as WifiProvisioningSecret).password,
        contains('#invalid'),
      );
      expect(harness.prompts.length, 2);
    });

    test('fails when invalid Wi-Fi credentials incorrectly succeed', () async {
      final hardware = FakeHardware();
      hardware.commissioning.handler = (_) async =>
          const CommissioningResult(errorCode: 0);
      final context = TestContextHarness(
        testId: DeviceTestId.invalidWifiPassword,
        ports: hardware.ports,
        execution: makeExecution()
          ..commissioningTransport = CommissioningTransport.ip,
      ).build();

      final outcome = await const InvalidWifiPasswordCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('incorrectly reported success'));
    });

    test('returns not_run for a Thread commissionee', () async {
      final hardware = FakeHardware();
      const threadCommissionee = CommissioneeMetadata(
        vendorId: 4660,
        productId: 258,
        networkTransport: NetworkTransport.thread,
      );
      final context = TestContextHarness(
        testId: DeviceTestId.invalidWifiPassword,
        ports: hardware.ports,
        session: makeSession(commissionee: threadCommissionee),
      ).build();

      final outcome = await const InvalidWifiPasswordCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });

    test('returns not_run when the preparation prompt is skipped', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.invalidWifiPassword,
        ports: hardware.ports,
        operatorHandler: (_) =>
            OperatorDecision.skipped('Wi-Fi test unavailable'),
      ).build();

      final outcome = await const InvalidWifiPasswordCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });
  });

  group('remove_fabric_ui', () {
    test('passes when no fabric remains after the UI action', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.removeFabricUi,
        ports: hardware.ports,
        operatorHandler: (_) {
          hardware.fabric.status = const FabricStatus(present: false);
          return OperatorDecision.confirmed();
        },
      ).build();

      final outcome = await const RemoveFabricUiCase().execute(context);

      expect(outcome.status, DeviceTestStatus.passed);
      expect(hardware.fabric.inspectCount, 1);
    });

    test('fails when a fabric remains after the UI action', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.removeFabricUi,
        ports: hardware.ports,
        operatorHandler: (_) => OperatorDecision.confirmed(),
      ).build();

      final outcome = await const RemoveFabricUiCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('remained'));
    });

    test('returns not_run when the UI action is skipped', () async {
      final hardware = FakeHardware();
      final context = TestContextHarness(
        testId: DeviceTestId.removeFabricUi,
        ports: hardware.ports,
        operatorHandler: (_) => OperatorDecision.skipped('UI unavailable'),
      ).build();

      final outcome = await const RemoveFabricUiCase().execute(context);

      expect(outcome.status, DeviceTestStatus.notRun);
    });

    test('fails when fabric inspection fails', () async {
      final hardware = FakeHardware();
      hardware.fabric.inspectError = FabricException(
        FabricFailureCode.inspectFailed,
      );
      final context = TestContextHarness(
        testId: DeviceTestId.removeFabricUi,
        ports: hardware.ports,
      ).build();

      final outcome = await const RemoveFabricUiCase().execute(context);

      expect(outcome.status, DeviceTestStatus.failed);
      expect(outcome.notes, contains('inspect_failed'));
    });
  });
}
