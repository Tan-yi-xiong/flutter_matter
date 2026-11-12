import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

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

    final preparePrompt = OperatorPrompt(
      id: 'invalid_setup_passcode_prepare',
      title: 'Prepare the commissionee for an invalid passcode test',
      instructions:
          'Factory reset the commissionee and leave it commissionable, then '
          'confirm.',
      requiredActor: context.commissioneeActionActor,
      testId: id,
    );
    final prepareDecision = await context.prompt(preparePrompt);
    final prepareOutcome = outcomeForPromptDecision(
      preparePrompt,
      prepareDecision,
    );
    if (prepareOutcome != null) {
      return prepareOutcome;
    }

    final transport = context.execution.commissioningTransport;
    if (transport == null) {
      return TestCaseOutcome.notRun(
        'Commissioning discovery did not select a transport.',
      );
    }

    TestCaseOutcome diagnosticOutcome;
    try {
      final identityRequest = ControllerIdentityRequest(
        runId: context.runId,
        purpose: ControllerIdentityPurpose.invalidSetupPasscode,
        platform: controller.platform,
      );
      await context.ports.controllerIdentity.reset(identityRequest);
      final identity = await context.ports.controllerIdentity.loadOrCreate(
        identityRequest,
      );
      final result = await commissionTarget(
        context,
        identity: identity,
        secrets: secrets,
        commissioningTransport: transport,
        timeout: context.timeoutFor(id),
        setupPinCode: secrets.invalidSetupPinCode,
      );
      diagnosticOutcome = result.succeeded
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
      diagnosticOutcome = clearFailure
          ? const TestCaseOutcome.passed(
              notes:
                  'Invalid setup passcode returned a clear commissioning failure.',
            )
          : TestCaseOutcome.failed(
              'Invalid setup passcode produced an unexpected '
              '${error.code.wireName} failure.',
            );
    } on TimeoutException {
      diagnosticOutcome = TestCaseOutcome.failed(
        'The invalid-passcode commissioning test timed out.',
      );
    }

    final cleanupPrompt = OperatorPrompt(
      id: 'invalid_setup_passcode_cleanup',
      title: 'Restore the commissionee after the invalid passcode test',
      instructions:
          'Factory reset the commissionee or otherwise restore a known-clean '
          'state, then confirm.',
      requiredActor: context.commissioneeActionActor,
      testId: id,
      canSkip: true,
    );
    final cleanupDecision = await context.prompt(cleanupPrompt);
    if (!cleanupDecision.isConfirmed) {
      return TestCaseOutcome.failed(
        cleanupDecision.reason == null
            ? 'Invalid-passcode cleanup was not confirmed.'
            : 'Invalid-passcode cleanup was not confirmed: '
                  '${cleanupDecision.reason}.',
      );
    }
    return diagnosticOutcome;
  }
}
