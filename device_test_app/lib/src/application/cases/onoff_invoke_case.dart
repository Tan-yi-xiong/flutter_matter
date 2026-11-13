import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class OnOffInvokeCase implements DeviceTestCase {
  const OnOffInvokeCase();

  @override
  DeviceTestId get id => DeviceTestId.onoffInvoke;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final connection = await restoreConnection(context);
    if (connection == null) {
      return context.execution.identity == null ||
              context.execution.nodeId == null
          ? TestCaseOutcome.notRun(
              'An operational connection is required for OnOff invocation.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }

    final timeout = context.timeoutFor(id);
    try {
      var current = await context.ports.onOff.readState(
        connection: connection,
        timeout: timeout,
      );

      // The contract requires Off, On, and Toggle to each change state. If the
      // commissionee starts Off, establish On first so Off is a real change.
      if (current == OnOffState.off) {
        final setup = await context.ports.onOff.invoke(
          connection: connection,
          command: OnOffCommand.on,
          timeout: timeout,
        );
        if (!setup.changed || setup.currentState != OnOffState.on) {
          return TestCaseOutcome.failed(
            'The OnOff setup command did not turn the commissionee on.',
          );
        }
        current = setup.currentState;
        await context.updateExecution((execution) {
          execution.lastOnOffState = current;
        });
      }

      final offResult = await context.ports.onOff.invoke(
        connection: connection,
        command: OnOffCommand.off,
        timeout: timeout,
      );
      if (!offResult.changed || offResult.currentState != OnOffState.off) {
        return TestCaseOutcome.failed(
          'The Off command did not change the commissionee to Off.',
        );
      }
      await context.updateExecution((execution) {
        execution.lastOnOffState = offResult.currentState;
      });

      final onResult = await context.ports.onOff.invoke(
        connection: connection,
        command: OnOffCommand.on,
        timeout: timeout,
      );
      if (!onResult.changed || onResult.currentState != OnOffState.on) {
        return TestCaseOutcome.failed(
          'The On command did not change the commissionee to On.',
        );
      }
      await context.updateExecution((execution) {
        execution.lastOnOffState = onResult.currentState;
      });

      final toggleResult = await context.ports.onOff.invoke(
        connection: connection,
        command: OnOffCommand.toggle,
        timeout: timeout,
      );
      if (!toggleResult.changed ||
          toggleResult.currentState != onResult.currentState.toggled) {
        return TestCaseOutcome.failed(
          'The Toggle command did not invert the commissionee state.',
        );
      }
      await context.updateExecution((execution) {
        execution.lastOnOffState = toggleResult.currentState;
      });

      return const TestCaseOutcome.passed(
        notes: 'Off, On, and Toggle changed the commissionee state.',
      );
    } on OnOffException catch (error) {
      return TestCaseOutcome.failed(
        'OnOff invocation failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'OnOff invocation timed out after ${timeoutLabel(timeout)}.',
      );
    }
  }
}
