import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class RemoveFabricUiCase implements DeviceTestCase {
  const RemoveFabricUiCase();

  @override
  DeviceTestId get id => DeviceTestId.removeFabricUi;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final identity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    final connection = await restoreConnection(context);
    if (identity == null || nodeId == null || connection == null) {
      return context.execution.identity == null ||
              context.execution.nodeId == null
          ? TestCaseOutcome.notRun(
              'An active commissioning and operational connection are required.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }

    final prompt = OperatorPrompt(
      id: 'remove_fabric_ui',
      title: 'Remove the device fabric through the UI',
      instructions:
          'Open the controller device UI, use the existing Remove/Delete '
          'Device action, then confirm when the fabric is gone.',
      requiredActor: context.controllerSystemActor,
      testId: id,
    );
    final decision = await context.prompt(prompt);
    final promptOutcome = outcomeForPromptDecision(prompt, decision);
    if (promptOutcome != null) {
      return promptOutcome;
    }

    try {
      final status = await context.ports.fabric.inspect(
        identity: identity,
        nodeId: nodeId,
        connection: connection,
        timeout: context.timeoutFor(id),
      );
      if (status.present) {
        return TestCaseOutcome.failed(
          'A controller fabric remained after the remove-device UI action.',
        );
      }
      return const TestCaseOutcome.passed(
        notes: 'Remove/delete-device UI completed and no fabric remained.',
      );
    } on FabricException catch (error) {
      return TestCaseOutcome.failed(
        'Fabric inspection failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Fabric inspection timed out after ${timeoutLabel(context.timeoutFor(id))}.',
      );
    }
  }
}
