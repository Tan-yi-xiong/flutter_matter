import 'package:flutter/material.dart';

import '../../domain/domain.dart';
import '../dialogs.dart';
import '../ui_controller.dart';
import '../ui_keys.dart';
import '../ui_models.dart';
import '../widgets.dart';

class RunnerScreen extends StatelessWidget {
  const RunnerScreen({
    super.key,
    required this.controller,
    required this.state,
  });

  final DeviceTestUiController controller;
  final DeviceTestUiState state;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final activeRun = state.activeRun;
    if (activeRun == null) {
      return DeviceTestPage(
        screenKey: DeviceTestUiKeys.runnerScreen,
        title: 'Test Runner',
        child: Center(
          child: Padding(
            padding: const EdgeInsets.all(24),
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: <Widget>[
                const Icon(Icons.play_circle_outline, size: 48),
                const SizedBox(height: 12),
                Text(
                  'No active Run is loaded.',
                  style: theme.textTheme.titleMedium,
                ),
                const SizedBox(height: 16),
                FilledButton(
                  onPressed: () => controller.navigate(DeviceTestScreen.home),
                  child: const Text('Back to Home'),
                ),
              ],
            ),
          ),
        ),
      );
    }

    final instruction =
        state.prompt?.instructions ??
        activeRun.currentInstruction ??
        'The test runner is preparing the next action.';
    final timeout = activeRun.currentTimeout;
    final elapsed = activeRun.currentElapsed;
    final timeoutProgress = timeout == null || timeout == Duration.zero
        ? null
        : ((elapsed ?? Duration.zero).inMilliseconds / timeout.inMilliseconds)
              .clamp(0.0, 1.0)
              .toDouble();

    return DeviceTestPage(
      screenKey: DeviceTestUiKeys.runnerScreen,
      title: 'Test Runner',
      leading: IconButton(
        tooltip: 'Back to home',
        onPressed: state.busy
            ? null
            : () => controller.navigate(DeviceTestScreen.home),
        icon: const Icon(Icons.arrow_back),
      ),
      actions: <Widget>[
        if (state.results != null)
          IconButton(
            key: DeviceTestUiKeys.runnerViewResultsAppBar,
            tooltip: 'View results',
            onPressed: state.busy
                ? null
                : () => controller.navigate(DeviceTestScreen.results),
            icon: const Icon(Icons.table_chart_outlined),
          ),
      ],
      child: ListView(
        padding: const EdgeInsets.all(16),
        children: <Widget>[
          Center(
            child: ConstrainedBox(
              constraints: const BoxConstraints(maxWidth: 960),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: <Widget>[
                  if (state.errorMessage != null) ...<Widget>[
                    ErrorBanner(message: state.errorMessage!),
                    const SizedBox(height: 16),
                  ],
                  PresentationCard(
                    title: '${activeRun.profile.label} Run',
                    subtitle:
                        '${activeRun.phase.label} · '
                        '${activeRun.completedCount} of '
                        '${activeRun.totalCount} tests complete',
                    trailing: activeRun.isTerminal
                        ? null
                        : const SizedBox.square(
                            dimension: 20,
                            child: CircularProgressIndicator(strokeWidth: 2),
                          ),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: <Widget>[
                        Semantics(
                          label:
                              'Run progress: '
                              '${(activeRun.progress * 100).round()} percent',
                          value:
                              '${(activeRun.progress * 100).round()} percent',
                          child: LinearProgressIndicator(
                            key: DeviceTestUiKeys.runProgress,
                            value: activeRun.progress,
                          ),
                        ),
                        const SizedBox(height: 8),
                        Text(
                          '${(activeRun.progress * 100).round()}% complete',
                          style: theme.textTheme.bodySmall,
                        ),
                      ],
                    ),
                  ),
                  const SizedBox(height: 16),
                  PresentationCard(
                    title: 'Current Test',
                    subtitle:
                        activeRun.currentTestId?.title ??
                        'Waiting for the next test',
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: <Widget>[
                        if (activeRun.currentTestId != null)
                          Wrap(
                            spacing: 8,
                            runSpacing: 8,
                            crossAxisAlignment: WrapCrossAlignment.center,
                            children: <Widget>[
                              PriorityBadge(
                                priority: activeRun.currentTestId!.priority,
                              ),
                              TestStatusBadge(
                                status: _statusFor(
                                  activeRun,
                                  activeRun.currentTestId!,
                                ),
                              ),
                            ],
                          ),
                        const SizedBox(height: 12),
                        Semantics(
                          key: DeviceTestUiKeys.currentInstruction,
                          liveRegion: true,
                          container: true,
                          label: instruction,
                          excludeSemantics: true,
                          child: Text(
                            instruction,
                            style: theme.textTheme.bodyLarge,
                          ),
                        ),
                        if (elapsed != null || timeout != null) ...<Widget>[
                          const SizedBox(height: 16),
                          Row(
                            children: <Widget>[
                              const Icon(Icons.timer_outlined, size: 18),
                              const SizedBox(width: 6),
                              Expanded(
                                child: Text(
                                  'Elapsed ${formatDuration(elapsed ?? Duration.zero)}'
                                  '${timeout == null ? '' : ' of ${formatDuration(timeout)}'}',
                                  key: DeviceTestUiKeys.currentTestTimeout,
                                  style: theme.textTheme.bodySmall,
                                ),
                              ),
                            ],
                          ),
                          if (timeoutProgress != null) ...<Widget>[
                            const SizedBox(height: 8),
                            LinearProgressIndicator(
                              value: timeoutProgress,
                              semanticsLabel: 'Current test timeout progress',
                            ),
                          ],
                        ],
                      ],
                    ),
                  ),
                  const SizedBox(height: 16),
                  if (state.prompt != null) ...<Widget>[
                    _PromptCard(
                      controller: controller,
                      prompt: state.prompt!,
                      busy: state.busy,
                    ),
                    const SizedBox(height: 16),
                  ],
                  PresentationCard(
                    title: 'Fixed Test Progress',
                    subtitle:
                        'Results are read-only once a test reaches a terminal '
                        'state.',
                    child: Column(
                      children: <Widget>[
                        for (
                          var index = 0;
                          index < activeRun.tests.length;
                          index++
                        ) ...<Widget>[
                          _TestRow(
                            result: activeRun.tests[index],
                            index: index,
                          ),
                          if (index != activeRun.tests.length - 1)
                            const Divider(height: 1),
                        ],
                      ],
                    ),
                  ),
                  if (state.results != null) ...<Widget>[
                    const SizedBox(height: 16),
                    Align(
                      alignment: Alignment.centerRight,
                      child: Semantics(
                        label: 'View completed device test results',
                        button: true,
                        enabled: !state.busy,
                        excludeSemantics: true,
                        child: FilledButton.icon(
                          key: DeviceTestUiKeys.runnerViewResults,
                          onPressed: state.busy
                              ? null
                              : () => controller.navigate(
                                  DeviceTestScreen.results,
                                ),
                          icon: const Icon(Icons.assessment_outlined),
                          label: const Text('View Results'),
                        ),
                      ),
                    ),
                  ],
                  if (activeRun.isTerminal) ...<Widget>[
                    const SizedBox(height: 16),
                    PresentationCard(
                      key: DeviceTestUiKeys.commissioneeReset,
                      title: 'Commissionee cleanup',
                      subtitle:
                          'Optional. Reset the device after a finished Run to '
                          'free its fabric slots for the next Run.',
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.stretch,
                        children: <Widget>[
                          const InfoBanner(
                            icon: Icons.restore,
                            message:
                                'Factory reset the commissionee (or reset the '
                                'virtual device) so it starts the next Run '
                                'without accumulated fabrics.',
                          ),
                          const SizedBox(height: 8),
                          FilledButton.tonalIcon(
                            onPressed: state.busy
                                ? null
                                : () => _confirmCommissioneeReset(
                                    context,
                                    controller,
                                  ),
                            icon: const Icon(Icons.restart_alt),
                            label: const Text('I reset the device'),
                          ),
                        ],
                      ),
                    ),
                  ],
                  const SizedBox(height: 24),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }

  Future<void> _confirmCommissioneeReset(
    BuildContext context,
    DeviceTestUiController controller,
  ) async {
    final confirmed = await showCommissioneeResetDialog(context);
    if (!confirmed || !context.mounted) {
      return;
    }
    try {
      await controller.confirmCommissioneeReset();
    } on Object {
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('The commissionee cleanup could not be recorded.'),
          ),
        );
      }
    }
  }

  static DeviceTestStatus _statusFor(
    ActiveRunViewModel run,
    DeviceTestId testId,
  ) {
    for (final result in run.tests) {
      if (result.testId == testId) {
        return result.status;
      }
    }
    return DeviceTestStatus.pending;
  }
}

class _PromptCard extends StatelessWidget {
  const _PromptCard({
    required this.controller,
    required this.prompt,
    required this.busy,
  });

  final DeviceTestUiController controller;
  final RunnerPromptViewModel prompt;
  final bool busy;

  @override
  Widget build(BuildContext context) {
    return Semantics(
      key: DeviceTestUiKeys.promptCard,
      container: true,
      label:
          'Operator action required. ${prompt.title}. '
          '${prompt.requiredActor.visibleLabel}.',
      child: PresentationCard(
        title: 'Operator Action Required',
        subtitle: prompt.title,
        trailing: RequiredActorBadge(actor: prompt.requiredActor),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: <Widget>[
            Text(prompt.instructions),
            const SizedBox(height: 16),
            Wrap(
              spacing: 8,
              runSpacing: 8,
              children: <Widget>[
                Semantics(
                  label: 'Confirm required operator action',
                  button: true,
                  enabled: !busy,
                  excludeSemantics: true,
                  child: FilledButton.icon(
                    key: DeviceTestUiKeys.promptConfirm,
                    onPressed: busy
                        ? null
                        : () => _runAction(
                            context,
                            () => controller.confirmPrompt(),
                          ),
                    icon: const Icon(Icons.check),
                    label: Text(prompt.confirmLabel),
                  ),
                ),
                if (prompt.canSkip)
                  Semantics(
                    label: 'Skip current test with a reason',
                    button: true,
                    enabled: !busy,
                    excludeSemantics: true,
                    child: OutlinedButton.icon(
                      key: DeviceTestUiKeys.promptSkip,
                      onPressed: busy ? null : () => _skip(context),
                      icon: const Icon(Icons.skip_next),
                      label: const Text('Skip'),
                    ),
                  ),
                Semantics(
                  label: 'Fail current test with a reason',
                  button: true,
                  enabled: !busy,
                  excludeSemantics: true,
                  child: TextButton.icon(
                    key: DeviceTestUiKeys.promptFail,
                    onPressed: busy ? null : () => _fail(context),
                    icon: const Icon(Icons.close),
                    label: const Text('Fail'),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }

  Future<void> _skip(BuildContext context) async {
    if (!prompt.skipRequiresReason) {
      await _runAction(
        context,
        () => controller.skipPrompt('Skipped from the Runner UI.'),
      );
      return;
    }
    final reason = await showReasonDialog(
      context: context,
      title: 'Skip this test?',
      actionLabel: 'Skip Test',
      fieldKey: DeviceTestUiKeys.skipReasonField,
    );
    if (reason == null || !context.mounted) {
      return;
    }
    await _runAction(context, () => controller.skipPrompt(reason));
  }

  Future<void> _fail(BuildContext context) async {
    final reason = await showReasonDialog(
      context: context,
      title: 'Fail this test?',
      actionLabel: 'Record Failure',
      fieldKey: DeviceTestUiKeys.failReasonField,
    );
    if (reason == null || !context.mounted) {
      return;
    }
    await _runAction(context, () => controller.failPrompt(reason));
  }

  Future<void> _runAction(
    BuildContext context,
    Future<void> Function() action,
  ) async {
    try {
      await action();
    } on Object {
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('The test action could not be completed.'),
          ),
        );
      }
    }
  }
}

class _TestRow extends StatelessWidget {
  const _TestRow({required this.result, required this.index});

  final TestProgressViewModel result;
  final int index;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final statusLabel = result.status.label;
    return Semantics(
      container: true,
      label:
          '${result.priority.label} ${result.title}, '
          'status $statusLabel',
      excludeSemantics: true,
      child: Container(
        key: DeviceTestUiKeys.testRow(result.testId),
        padding: const EdgeInsets.symmetric(vertical: 10),
        child: Row(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            SizedBox(
              width: 28,
              child: Text('${index + 1}', style: theme.textTheme.bodySmall),
            ),
            PriorityBadge(priority: result.priority),
            const SizedBox(width: 10),
            Expanded(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: <Widget>[
                  Text(result.title, style: theme.textTheme.titleSmall),
                  if (result.notes != null) ...<Widget>[
                    const SizedBox(height: 2),
                    Text(result.notes!, style: theme.textTheme.bodySmall),
                  ],
                ],
              ),
            ),
            const SizedBox(width: 8),
            Column(
              crossAxisAlignment: CrossAxisAlignment.end,
              children: <Widget>[
                TestStatusBadge(status: result.status),
                if (result.duration > Duration.zero) ...<Widget>[
                  const SizedBox(height: 4),
                  Text(
                    formatDuration(result.duration),
                    style: theme.textTheme.bodySmall,
                  ),
                ],
              ],
            ),
          ],
        ),
      ),
    );
  }
}
