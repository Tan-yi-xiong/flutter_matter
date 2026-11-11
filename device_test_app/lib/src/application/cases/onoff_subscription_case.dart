import 'dart:async';

import '../../domain/domain.dart';
import '../operator_prompt.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

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

      final prompt = OperatorPrompt(
        id: 'onoff_subscription_external_change',
        title: 'Change the commissionee OnOff state',
        instructions:
            context.commissioneeActionActor == RequiredActor.agentAndroid
            ? 'Change the virtual commissionee OnOff state externally, '
                  'then confirm.'
            : 'Use the physical switch or vendor app to change the OnOff '
                  'state externally, then confirm.',
        requiredActor: context.commissioneeActionActor,
        testId: id,
      );
      final decision = await context.prompt(prompt);
      final promptOutcome = outcomeForPromptDecision(prompt, decision);
      if (promptOutcome != null) {
        return promptOutcome;
      }

      final updated = await changedState.future.timeout(timeout);
      await context.updateExecution((execution) {
        execution.lastOnOffState = updated;
      });
      return const TestCaseOutcome.passed(
        notes: 'Initial state and an external OnOff update were observed.',
      );
    } on OnOffException catch (error) {
      return TestCaseOutcome.failed(
        'OnOff subscription failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'No external OnOff update arrived within ${timeoutLabel(timeout)}.',
      );
    } on StateError {
      return TestCaseOutcome.failed(
        'The OnOff subscription ended before an external update arrived.',
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
