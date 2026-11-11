import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class BluetoothDisabledCase implements DeviceTestCase {
  const BluetoothDisabledCase();

  @override
  DeviceTestId get id => DeviceTestId.bluetoothDisabled;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final disablePrompt = OperatorPrompt(
      id: 'bluetooth_disabled_disable',
      title: 'Disable Bluetooth',
      instructions: 'Disable Bluetooth on the controller device, then confirm.',
      requiredActor: context.controllerSystemActor,
      testId: id,
    );
    final disableDecision = await context.prompt(disablePrompt);
    final disableOutcome = outcomeForPromptDecision(
      disablePrompt,
      disableDecision,
    );
    if (disableOutcome != null) {
      return disableOutcome;
    }

    TestCaseOutcome diagnosticOutcome;
    try {
      final result = await context.ports.bleDiscovery.discover(
        BleDiscoveryRequest(
          timeout: context.timeoutFor(id),
          onboardingPayload: context.secrets?.onboardingPayload,
        ),
      );
      diagnosticOutcome = result.candidateCount == 0
          ? const TestCaseOutcome.passed(
              notes: 'BLE discovery reported no candidates with Bluetooth off.',
            )
          : TestCaseOutcome.failed(
              'BLE discovery returned candidates while Bluetooth was disabled.',
            );
    } on BleDiscoveryException catch (error) {
      diagnosticOutcome =
          error.code == BleDiscoveryFailureCode.bluetoothUnavailable
          ? const TestCaseOutcome.passed(
              notes: 'Bluetooth unavailability produced a clear BLE failure.',
            )
          : TestCaseOutcome.failed(
              'Bluetooth-disabled discovery failed with '
              '${error.code.wireName}.',
            );
    } on TimeoutException {
      diagnosticOutcome = TestCaseOutcome.failed(
        'The Bluetooth-disabled discovery test timed out.',
      );
    }

    final restorePrompt = OperatorPrompt(
      id: 'bluetooth_disabled_restore',
      title: 'Restore Bluetooth',
      instructions: 'Enable Bluetooth on the controller device, then confirm.',
      requiredActor: context.controllerSystemActor,
      testId: id,
      canSkip: false,
      skipRequiresReason: false,
    );
    final restoreDecision = await context.prompt(restorePrompt);
    if (!restoreDecision.isConfirmed) {
      return TestCaseOutcome.failed(
        restoreDecision.reason == null
            ? 'Bluetooth state could not be restored.'
            : 'Bluetooth state could not be restored: '
                  '${restoreDecision.reason}.',
      );
    }
    return diagnosticOutcome;
  }
}
