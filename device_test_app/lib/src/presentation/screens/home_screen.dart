import 'package:flutter/material.dart';

import '../dialogs.dart';
import '../ui_controller.dart';
import '../ui_keys.dart';
import '../ui_models.dart';
import '../widgets.dart';

class HomeScreen extends StatelessWidget {
  const HomeScreen({super.key, required this.controller, required this.state});

  final DeviceTestUiController controller;
  final DeviceTestUiState state;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final activeRun = state.activeRun;
    final recentRun = state.recentRun;

    return DeviceTestPage(
      screenKey: DeviceTestUiKeys.homeScreen,
      title: 'Flutter Matter Device Test',
      child: ListView(
        padding: const EdgeInsets.all(16),
        children: <Widget>[
          Center(
            child: ConstrainedBox(
              constraints: const BoxConstraints(maxWidth: 960),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: <Widget>[
                  Semantics(
                    header: true,
                    child: Text(
                      'Physical-device validation workspace',
                      style: theme.textTheme.headlineSmall,
                    ),
                  ),
                  const SizedBox(height: 6),
                  Text(
                    'Run the fixed Matter validation sequence on an Android or '
                    'physical iOS controller. Formal evidence requires the full '
                    'profile and a clean report.',
                    style: theme.textTheme.bodyMedium,
                  ),
                  if (state.errorMessage != null) ...<Widget>[
                    const SizedBox(height: 16),
                    ErrorBanner(message: state.errorMessage!),
                  ],
                  const SizedBox(height: 20),
                  PresentationCard(
                    title: 'Active Run',
                    subtitle: activeRun == null
                        ? 'No resumable Run is loaded.'
                        : '${activeRun.profile.label} profile · '
                              '${activeRun.phase.label}',
                    child: activeRun == null
                        ? const Text('Start a new Run when the setup is ready.')
                        : Column(
                            crossAxisAlignment: CrossAxisAlignment.stretch,
                            children: <Widget>[
                              Row(
                                children: <Widget>[
                                  Expanded(
                                    child: Text(
                                      activeRun.currentTestId == null
                                          ? 'Tests complete'
                                          : activeRun.currentTestId!.title,
                                      style: theme.textTheme.titleMedium,
                                    ),
                                  ),
                                  Text(
                                    '${activeRun.completedCount} / '
                                    '${activeRun.totalCount}',
                                  ),
                                ],
                              ),
                              const SizedBox(height: 10),
                              LinearProgressIndicator(
                                value: activeRun.progress,
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
                    title: 'New Run',
                    subtitle:
                        'The setup screen collects the setup code, Wi-Fi details, clean-cycle '
                        'confirmation, and profile.',
                    child: Align(
                      alignment: Alignment.centerLeft,
                      child: Semantics(
                        label: 'Start a new device test setup',
                        button: true,
                        enabled: !state.busy,
                        excludeSemantics: true,
                        child: FilledButton.icon(
                          key: DeviceTestUiKeys.newRun,
                          onPressed: state.busy
                              ? null
                              : () =>
                                    controller.navigate(DeviceTestScreen.setup),
                          icon: const Icon(Icons.add),
                          label: const Text('New Run'),
                        ),
                      ),
                    ),
                  ),
                  const SizedBox(height: 16),
                  PresentationCard(
                    title: 'Recent Result',
                    subtitle: recentRun == null
                        ? 'No completed result is available.'
                        : '${recentRun.profile.label} profile · '
                              '${recentRun.formalEvidence ? 'formal evidence' : 'informational only'}',
                    child: recentRun == null
                        ? const Text(
                            'Complete a Run to review its summary and export '
                            'report artifacts.',
                          )
                        : Column(
                            crossAxisAlignment: CrossAxisAlignment.stretch,
                            children: <Widget>[
                              Row(
                                children: <Widget>[
                                  ReportResultBadge(
                                    result: recentRun.summary.result,
                                  ),
                                  const Spacer(),
                                  Text(
                                    _formatDate(recentRun.completedAt),
                                    style: theme.textTheme.bodySmall,
                                  ),
                                ],
                              ),
                              const SizedBox(height: 12),
                              Text(
                                '${recentRun.summary.passed} passed · '
                                '${recentRun.summary.failed} failed · '
                                '${recentRun.summary.notRun} not run',
                              ),
                              const SizedBox(height: 16),
                              Align(
                                alignment: Alignment.centerLeft,
                                child: Semantics(
                                  label: 'View recent device test results',
                                  button: true,
                                  enabled: !state.busy,
                                  excludeSemantics: true,
                                  child: OutlinedButton.icon(
                                    key: DeviceTestUiKeys.homeViewResults,
                                    onPressed: state.busy
                                        ? null
                                        : () => controller.navigate(
                                            DeviceTestScreen.results,
                                          ),
                                    icon: const Icon(
                                      Icons.table_chart_outlined,
                                    ),
                                    label: const Text('View Results'),
                                  ),
                                ),
                              ),
                            ],
                          ),
                  ),
                  const SizedBox(height: 16),
                  PresentationCard(
                    title: 'Secure Storage',
                    subtitle: state.hasStoredSecrets
                        ? 'Controller identity or provisioning secrets are stored.'
                        : 'No stored controller secrets were reported.',
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: <Widget>[
                        const Text(
                          'Purge removes setup codes, network credentials, '
                          'certificates, and controller identity material. '
                          'Uninstalling the app is not a substitute.',
                        ),
                        const SizedBox(height: 12),
                        Align(
                          alignment: Alignment.centerLeft,
                          child: Semantics(
                            label: 'Purge stored controller secrets',
                            button: true,
                            enabled: state.hasStoredSecrets && !state.busy,
                            excludeSemantics: true,
                            child: OutlinedButton.icon(
                              key: DeviceTestUiKeys.purgeSecrets,
                              onPressed: state.hasStoredSecrets && !state.busy
                                  ? () => _purge(context)
                                  : null,
                              icon: const Icon(Icons.delete_forever_outlined),
                              label: const Text('Purge Secrets'),
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                  const SizedBox(height: 24),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }

  Future<void> _purge(BuildContext context) async {
    final confirmed = await showPurgeSecretsDialog(context);
    if (!confirmed || !context.mounted) {
      return;
    }
    try {
      await controller.purgeSecrets();
    } on Object {
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Secrets could not be purged.')),
        );
      }
    }
  }
}

String _formatDate(DateTime value) {
  final local = value.toLocal();
  final month = local.month.toString().padLeft(2, '0');
  final day = local.day.toString().padLeft(2, '0');
  final hour = local.hour.toString().padLeft(2, '0');
  final minute = local.minute.toString().padLeft(2, '0');
  return '${local.year}-$month-$day $hour:$minute';
}
