import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class FactoryResetRecommissionCase implements DeviceTestCase {
  const FactoryResetRecommissionCase();

  @override
  DeviceTestId get id => DeviceTestId.factoryResetRecommission;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for recommissioning.',
      );
    }
    final controller = context.controller;
    if (controller == null) {
      return TestCaseOutcome.notRun('Controller metadata is unavailable.');
    }

    final prompt = OperatorPrompt(
      id: 'factory_reset_recommission',
      title: 'Factory reset the commissionee',
      instructions:
          'Factory reset the commissionee and leave it in a commissionable '
          'state, then confirm. The runner will create a fresh controller '
          'identity and commission it again.',
      requiredActor: context.commissioneeActionActor,
      testId: id,
    );
    final decision = await context.prompt(prompt);
    final promptOutcome = outcomeForPromptDecision(prompt, decision);
    if (promptOutcome != null) {
      return promptOutcome;
    }

    try {
      final identityRequest = ControllerIdentityRequest(
        runId: context.runId,
        purpose: ControllerIdentityPurpose.main,
        platform: controller.platform,
      );
      await context.ports.controllerIdentity.reset(identityRequest);
      final identity = await context.ports.controllerIdentity.loadOrCreate(
        identityRequest,
      );
      await context.updateExecution((execution) {
        execution.identity = identity;
        execution.nodeId = null;
        execution.networkTransport = null;
        execution.connection = null;
        execution.lastOnOffState = null;
      });

      final commissioningTimeout = context.timeoutFor(
        DeviceTestId.commissioning,
      );
      final commissioning = await commissionTarget(
        context,
        identity: identity,
        secrets: secrets,
        timeout: commissioningTimeout,
      );
      if (!commissioning.succeeded) {
        return TestCaseOutcome.failed(
          'Recommissioning returned error code ${commissioning.errorCode}.',
        );
      }

      final nodeId = commissioning.nodeId ?? context.targetNodeId;
      final connection = await context.ports.operationalConnection.connect(
        identity: identity,
        nodeId: nodeId,
        timeout: context.timeoutFor(DeviceTestId.operationalConnect),
      );
      if (!connection.isValid) {
        return TestCaseOutcome.failed(
          'Operational connection was invalid after recommissioning.',
        );
      }

      final onResult = await context.ports.onOff.invoke(
        connection: connection,
        command: OnOffCommand.on,
        timeout: context.timeoutFor(DeviceTestId.onoffInvoke),
      );
      if (onResult.currentState != OnOffState.on) {
        return TestCaseOutcome.failed(
          'The recommissioned commissionee did not accept an On command.',
        );
      }

      await context.updateExecution((execution) {
        execution.identity = identity;
        execution.nodeId = nodeId;
        execution.networkTransport =
            commissioning.networkTransport ?? secrets.transport;
        execution.connection = connection;
        execution.lastOnOffState = OnOffState.on;
      });
      return const TestCaseOutcome.passed(
        notes: 'Factory reset and full Wi-Fi/IP recommissioning succeeded.',
      );
    } on CommissioningException catch (error) {
      return TestCaseOutcome.failed(
        'Post-reset commissioning failed with ${error.code.wireName}'
        '${error.errorCode == null ? '' : ' (code ${error.errorCode})'}.',
      );
    } on OnOffException catch (error) {
      return TestCaseOutcome.failed(
        'Post-reset OnOff validation failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed('Factory reset recommissioning timed out.');
    }
  }
}
