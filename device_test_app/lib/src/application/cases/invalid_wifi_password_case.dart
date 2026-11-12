import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class InvalidWifiPasswordCase implements DeviceTestCase {
  const InvalidWifiPasswordCase();

  @override
  DeviceTestId get id => DeviceTestId.invalidWifiPassword;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    if (context.commissionee?.networkTransport != NetworkTransport.wifi) {
      return TestCaseOutcome.notRun(
        'The invalid Wi-Fi password scenario is not applicable to this '
        'commissionee network transport.',
      );
    }
    final secrets = context.secrets;
    if (secrets == null || secrets.network is! WifiProvisioningSecret) {
      return TestCaseOutcome.notRun(
        'Wi-Fi provisioning secrets are unavailable for this test.',
      );
    }
    final controller = context.controller;
    if (controller == null) {
      return TestCaseOutcome.notRun('Controller metadata is unavailable.');
    }

    final preparePrompt = OperatorPrompt(
      id: 'invalid_wifi_password_prepare',
      title: 'Prepare the commissionee for an invalid Wi-Fi test',
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
        purpose: ControllerIdentityPurpose.invalidWifiPassword,
        platform: controller.platform,
      );
      await context.ports.controllerIdentity.reset(identityRequest);
      final identity = await context.ports.controllerIdentity.loadOrCreate(
        identityRequest,
      );
      final invalidSecrets = secrets.withInvalidWifiPassword();
      final result = await commissionTarget(
        context,
        identity: identity,
        secrets: invalidSecrets,
        commissioningTransport: transport,
        timeout: context.timeoutFor(id),
      );
      diagnosticOutcome = result.succeeded
          ? TestCaseOutcome.failed(
              'Invalid Wi-Fi credentials incorrectly reported success.',
            )
          : const TestCaseOutcome.passed(
              notes: 'Invalid Wi-Fi credentials returned a non-zero failure.',
            );
    } on CommissioningException catch (error) {
      final clearFailure =
          error.code == CommissioningFailureCode.invalidCredentials ||
          (error.code == CommissioningFailureCode.commissioningFailed &&
              error.errorCode != null &&
              error.errorCode != 0);
      diagnosticOutcome = clearFailure
          ? const TestCaseOutcome.passed(
              notes:
                  'Invalid Wi-Fi credentials produced a clear provisioning '
                  'failure.',
            )
          : TestCaseOutcome.failed(
              'Invalid Wi-Fi credentials produced an unexpected '
              '${error.code.wireName} failure.',
            );
    } on TimeoutException {
      diagnosticOutcome = TestCaseOutcome.failed(
        'The invalid-Wi-Fi commissioning test timed out.',
      );
    }

    final cleanupPrompt = OperatorPrompt(
      id: 'invalid_wifi_password_cleanup',
      title: 'Restore the commissionee after the invalid Wi-Fi test',
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
            ? 'Invalid-Wi-Fi cleanup was not confirmed.'
            : 'Invalid-Wi-Fi cleanup was not confirmed: '
                  '${cleanupDecision.reason}.',
      );
    }
    return diagnosticOutcome;
  }
}
