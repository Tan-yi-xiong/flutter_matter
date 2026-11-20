import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

/// Verifies the library surfaces a clear failure for a wrong setup passcode.
///
/// The commissionee already carries the main fabric, so the case re-opens a
/// commissioning window with the original discriminator and passcode before
/// attempting discovery with a well-formed payload that carries a wrong
/// passcode. A failed PASE handshake adds no fabric to the commissionee.
class InvalidSetupPasscodeCase implements DeviceTestCase {
  const InvalidSetupPasscodeCase();

  @override
  DeviceTestId get id => DeviceTestId.invalidSetupPasscode;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for the invalid-passcode test.',
      );
    }
    final controller = context.controller;
    if (controller == null) {
      return TestCaseOutcome.notRun('Controller metadata is unavailable.');
    }
    final mainIdentity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    final mainConnection = await restoreConnection(context);
    if (mainIdentity == null || nodeId == null || mainConnection == null) {
      return mainIdentity == null || nodeId == null
          ? TestCaseOutcome.notRun(
              'An operational connection and commissioned node are required.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }
    final discriminator = secrets.setupDiscriminator;
    if (discriminator == null) {
      return TestCaseOutcome.notRun(
        'A setup discriminator is required to re-open the commissioning window.',
      );
    }

    try {
      await context.ports.commissioningWindow.open(
        identity: mainIdentity,
        nodeId: nodeId,
        connection: mainConnection,
        durationSeconds: commissioningWindowDurationSeconds,
        discriminator: discriminator,
        setupPinCode: secrets.setupPinCode,
        timeout: context.timeouts.commissioningWindow,
      );
    } on CommissioningWindowException catch (error) {
      return TestCaseOutcome.failed(
        'Opening the commissioning window failed with '
        '${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Opening the commissioning window timed out.',
      );
    }

    // Same-phone Android validation advertises the re-opened window in basic
    // commissioning mode, which the SDK's payload discovery refuses to hand
    // to PASE. Commissioning directly to the on-phone VDA loopback endpoint
    // bypasses discovery while the window is open, so the wrong passcode is
    // still exercised against the real PASE handshake. Reuse the live main
    // controller: creating a second CHIP controller in the same process aborts
    // in the pinned Android controller implementation.
    final endpoint =
        secrets.onNetworkEndpoint ??
        (controller.platform == ControllerPlatform.android
            ? OnNetworkCommissioningEndpoint(address: '127.0.0.1', port: 5540)
            : null);
    try {
      final result = await commissionTarget(
        context,
        identity: mainIdentity,
        secrets: secrets,
        timeout: context.timeoutFor(id),
        onboardingPayload: secrets.invalidSetupOnboardingPayload,
        setupPinCode: secrets.invalidSetupPinCode,
        onNetworkEndpoint: endpoint,
      );
      return result.succeeded
          ? TestCaseOutcome.failed(
              'Invalid setup passcode incorrectly reported success.',
            )
          : const TestCaseOutcome.passed(
              notes:
                  'Invalid setup passcode returned a clear non-zero failure.',
            );
    } on CommissioningException catch (error) {
      final clearFailure =
          error.code == CommissioningFailureCode.invalidSetupCode ||
          error.code == CommissioningFailureCode.invalidCredentials ||
          (error.code == CommissioningFailureCode.commissioningFailed &&
              error.errorCode != null &&
              error.errorCode != 0);
      return clearFailure
          ? const TestCaseOutcome.passed(
              notes:
                  'Invalid setup passcode produced a clear provisioning '
                  'failure.',
            )
          : TestCaseOutcome.failed(
              'Invalid setup passcode produced an unexpected '
              '${error.code.wireName} failure.',
            );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'The invalid-passcode commissioning test timed out.',
      );
    }
  }
}
