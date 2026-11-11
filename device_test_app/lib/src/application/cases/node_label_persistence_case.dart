import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class NodeLabelPersistenceCase implements DeviceTestCase {
  const NodeLabelPersistenceCase();

  static const _testLabel = 'flutter-matter-test';

  @override
  DeviceTestId get id => DeviceTestId.nodeLabelPersistence;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final identity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    final connection = await restoreConnection(context);
    if (identity == null || nodeId == null || connection == null) {
      return context.execution.identity == null ||
              context.execution.nodeId == null
          ? TestCaseOutcome.notRun(
              'An operational connection and commissioned node are required.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }

    final timeout = context.timeoutFor(id);
    try {
      await context.ports.nodeLabel.write(
        connection: connection,
        value: _testLabel,
        timeout: timeout,
      );
      final written = await context.ports.nodeLabel.read(
        connection: connection,
        timeout: timeout,
      );
      if (written != _testLabel) {
        return TestCaseOutcome.failed(
          'NodeLabel readback did not match the written value.',
        );
      }

      final prompt = OperatorPrompt(
        id: 'node_label_restart_commissionee',
        title: 'Restart the commissionee',
        instructions:
            context.commissioneeActionActor == RequiredActor.agentAndroid
            ? 'Restart the virtual commissionee without factory resetting it, '
                  'then confirm when it is online.'
            : 'Restart the physical commissionee without factory resetting it, '
                  'then confirm when it is online.',
        requiredActor: context.commissioneeActionActor,
        testId: id,
      );
      final decision = await context.prompt(prompt);
      final promptOutcome = outcomeForPromptDecision(prompt, decision);
      if (promptOutcome != null) {
        return promptOutcome;
      }

      final reconnectTimeout = context.timeoutFor(
        DeviceTestId.operationalConnect,
      );
      final reconnected = await context.ports.operationalConnection.reconnect(
        identity: identity,
        nodeId: nodeId,
        timeout: reconnectTimeout,
      );
      if (!reconnected.isValid) {
        return TestCaseOutcome.failed(
          'Operational connection was invalid after the commissionee restart.',
        );
      }
      await context.updateExecution((execution) {
        execution.connection = reconnected;
      });

      final persisted = await context.ports.nodeLabel.read(
        connection: reconnected,
        timeout: timeout,
      );
      if (persisted != _testLabel) {
        return TestCaseOutcome.failed(
          'NodeLabel did not survive the commissionee restart.',
        );
      }
      return const TestCaseOutcome.passed(
        notes: 'NodeLabel write/read succeeded and survived restart.',
      );
    } on NodeLabelException catch (error) {
      return TestCaseOutcome.failed(
        'NodeLabel operation failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'NodeLabel persistence timed out after ${timeoutLabel(timeout)}.',
      );
    } on Object {
      return TestCaseOutcome.failed(
        'Operational reconnection failed after the commissionee restart.',
      );
    }
  }
}
