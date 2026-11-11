import 'package:flutter_matter_device_test_app/src/app/app.dart';
import 'package:flutter_matter_device_test_app/src/application/application.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

OperatorPrompt prompt(
  String id, {
  bool canSkip = true,
  bool skipRequiresReason = true,
}) {
  return OperatorPrompt(
    id: id,
    title: 'Action $id',
    instructions: 'Complete action $id.',
    requiredActor: RequiredActor.human,
    testId: DeviceTestId.appRestart,
    canSkip: canSkip,
    skipRequiresReason: skipRequiresReason,
  );
}

void main() {
  test('serializes prompts and resolves the correct waiter', () async {
    final broker = OperatorPromptBroker();
    addTearDown(broker.dispose);

    final first = broker.request(prompt('one'));
    final second = broker.request(prompt('two'));
    final third = broker.request(prompt('three'));

    expect(broker.activePrompt?.id, 'one');
    expect(broker.queuedPromptCount, 2);

    broker.confirmActive();
    final firstDecision = await first;
    expect(firstDecision.status, OperatorPromptDecisionStatus.confirmed);
    expect(broker.activePrompt?.id, 'two');

    broker.skipActive('The optional path is unavailable.');
    final secondDecision = await second;
    expect(secondDecision.status, OperatorPromptDecisionStatus.skipped);
    expect(secondDecision.reason, 'The optional path is unavailable.');
    expect(broker.activePrompt?.id, 'three');

    broker.failActive('The physical device did not reset.');
    final thirdDecision = await third;
    expect(thirdDecision.status, OperatorPromptDecisionStatus.failed);
    expect(thirdDecision.reason, 'The physical device did not reset.');
    expect(broker.activePrompt, isNull);
    expect(broker.queuedPromptCount, 0);
  });

  test('does not advance or cross prompts on invalid decisions', () async {
    final broker = OperatorPromptBroker();
    addTearDown(broker.dispose);

    final blocked = broker.request(prompt('blocked', canSkip: false));
    expect(() => broker.skipActive('No skip allowed.'), throwsStateError);
    expect(broker.activePrompt?.id, 'blocked');

    final requiredReason = broker.request(
      prompt('required-reason', skipRequiresReason: true),
    );
    broker.confirmActive();
    await blocked;
    expect(broker.activePrompt?.id, 'required-reason');

    expect(() => broker.skipActive('   '), throwsArgumentError);
    expect(broker.activePrompt?.id, 'required-reason');
    broker.failActive('A concrete failure.');
    expect((await requiredReason).status, OperatorPromptDecisionStatus.failed);
  });

  test('uses a deterministic reason when skip reason is optional', () async {
    final broker = OperatorPromptBroker();
    addTearDown(broker.dispose);

    final decisionFuture = broker.request(
      prompt('optional', skipRequiresReason: false),
    );
    broker.skipActive('');
    final decision = await decisionFuture;
    expect(decision.status, OperatorPromptDecisionStatus.skipped);
    expect(decision.reason, 'Skipped by the operator.');
  });

  test('exposes only the active prompt', () async {
    final broker = OperatorPromptBroker();
    addTearDown(broker.dispose);
    final observed = <String?>[];
    final subscription = broker.activePromptStream.listen(
      (value) => observed.add(value?.id),
    );
    addTearDown(subscription.cancel);

    final first = broker.request(prompt('first'));
    final second = broker.request(prompt('second'));
    broker.confirmActive();
    await first;
    broker.confirmActive();
    await second;
    await Future<void>.delayed(Duration.zero);

    expect(observed, <String?>['first', 'second', null]);
  });
}
