import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class AppRestartCase implements DeviceTestCase {
  const AppRestartCase();

  @override
  DeviceTestId get id => DeviceTestId.appRestart;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final existingCheckpoint = context.resumeCheckpoint;
    var identity = context.execution.identity;
    var nodeId = context.execution.nodeId;

    if (existingCheckpoint != null) {
      nodeId = existingCheckpoint.nodeId;
      identity ??= ControllerIdentity(
        opaqueId: existingCheckpoint.identityOpaqueId,
        purpose: ControllerIdentityPurpose.main,
      );
    }

    if (identity == null || nodeId == null) {
      return TestCaseOutcome.notRun(
        'A main controller identity and commissioned node are required.',
      );
    }

    var confirmedRestart = existingCheckpoint != null;
    if (!confirmedRestart) {
      await context.saveAppRestartCheckpoint(
        AppRestartCheckpoint(
          stage: AppRestartCheckpointStage.awaitingRestart,
          identityOpaqueId: identity.opaqueId,
          nodeId: nodeId,
        ),
      );
      final prompt = OperatorPrompt(
        id: 'app_restart_controller',
        title: 'Restart the controller app',
        instructions:
            'Restart the test app without clearing app data. The runner will '
            'resume from its saved checkpoint after relaunch; confirm once the '
            'app is running again.',
        requiredActor: context.controllerAppRestartActor,
        testId: id,
      );
      final decision = await context.prompt(prompt);
      final promptOutcome = outcomeForPromptDecision(prompt, decision);
      if (promptOutcome != null) {
        await context.clearAppRestartCheckpoint();
        return promptOutcome;
      }
      confirmedRestart = true;
    }

    if (!confirmedRestart) {
      await context.clearAppRestartCheckpoint();
      return TestCaseOutcome.failed(
        'Controller app restart was not confirmed.',
      );
    }

    final checkpoint = AppRestartCheckpoint(
      stage: AppRestartCheckpointStage.awaitingReconnect,
      identityOpaqueId: identity.opaqueId,
      nodeId: nodeId,
    );
    await context.saveAppRestartCheckpoint(checkpoint);

    final timeout = context.timeoutFor(DeviceTestId.operationalConnect);
    try {
      final loadedIdentity = await context.ports.controllerIdentity
          .loadOrCreate(
            ControllerIdentityRequest(
              runId: context.runId,
              purpose: ControllerIdentityPurpose.main,
              platform: context.controller!.platform,
            ),
          );
      if (loadedIdentity.opaqueId != checkpoint.identityOpaqueId) {
        await context.clearAppRestartCheckpoint();
        return TestCaseOutcome.failed(
          'The controller identity changed across the app restart.',
        );
      }

      final connection = await context.ports.operationalConnection.reconnect(
        identity: loadedIdentity,
        nodeId: checkpoint.nodeId,
        timeout: timeout,
      );
      if (!connection.isValid) {
        await context.clearAppRestartCheckpoint();
        return TestCaseOutcome.failed(
          'Operational reconnection was invalid after the app restart.',
        );
      }
      await context.updateExecution((execution) {
        execution.identity = loadedIdentity;
        execution.nodeId = checkpoint.nodeId;
        execution.connection = connection;
      });
      await context.clearAppRestartCheckpoint();
      return const TestCaseOutcome.passed(
        notes: 'Controller app restart reconnected without recommissioning.',
      );
    } on TimeoutException {
      await context.clearAppRestartCheckpoint();
      return TestCaseOutcome.failed(
        'Controller app reconnect timed out after ${timeoutLabel(timeout)}.',
      );
    } on Object {
      await context.clearAppRestartCheckpoint();
      return TestCaseOutcome.failed('Controller app restart recovery failed.');
    }
  }
}
