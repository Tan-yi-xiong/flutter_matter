import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

/// Verifies that the commissionee pushes OnOff updates over an active
/// subscription. The case triggers the state change itself with an OnOff
/// command, so the full push path (command execution, attribute change,
/// subscription report) is validated without operator interaction.
class OnOffSubscriptionCase implements DeviceTestCase {
  const OnOffSubscriptionCase();

  @override
  DeviceTestId get id => DeviceTestId.onoffSubscription;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final connection = await restoreConnection(context);
    if (connection == null) {
      return context.execution.identity == null ||
              context.execution.nodeId == null
          ? TestCaseOutcome.notRun(
              'An operational connection is required for OnOff subscription.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }

    final timeout = context.timeoutFor(id);
    OnOffSubscription? subscription;
    StreamSubscription<OnOffState>? updateSubscription;
    Completer<OnOffState>? changedState;
    try {
      final activeSubscription = await context.ports.onOff.subscribe(
        connection: connection,
        timeout: timeout,
      );
      subscription = activeSubscription;
      final initial = activeSubscription.initialState;
      final stateCompleter = Completer<OnOffState>();
      changedState = stateCompleter;
      updateSubscription = activeSubscription.updates.listen(
        (state) {
          if (state != initial && !stateCompleter.isCompleted) {
            stateCompleter.complete(state);
          }
        },
        onError: (Object error, StackTrace stackTrace) {
          if (!stateCompleter.isCompleted) {
            stateCompleter.completeError(error, stackTrace);
          }
        },
      );

      // Trigger the state change through the same controller: the device
      // executes the command, the attribute changes, and the subscription
      // must deliver the update.
      final trigger = await context.ports.onOff.invoke(
        connection: connection,
        command: OnOffCommand.toggle,
        timeout: timeout,
      );
      if (!trigger.changed) {
        return TestCaseOutcome.failed(
          'The OnOff trigger command did not change the commissionee state.',
        );
      }

      final updated = await changedState.future.timeout(timeout);
      await context.updateExecution((execution) {
        execution.lastOnOffState = updated;
      });
      return const TestCaseOutcome.passed(
        notes:
            'Initial state and a command-triggered OnOff update were '
            'observed on the subscription.',
      );
    } on OnOffException catch (error) {
      return TestCaseOutcome.failed(
        'OnOff subscription failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'No OnOff subscription update arrived within ${timeoutLabel(timeout)}.',
      );
    } on StateError {
      return TestCaseOutcome.failed(
        'The OnOff subscription ended before an update arrived.',
      );
    } finally {
      await updateSubscription?.cancel();
      final activeSubscription = subscription;
      if (activeSubscription != null) {
        try {
          await activeSubscription.cancel();
        } on Object {
          // Subscription teardown must not mask the test outcome.
        }
      }
    }
  }
}
