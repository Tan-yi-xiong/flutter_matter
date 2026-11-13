import 'package:flutter/material.dart';

import '../../domain/domain.dart';
import '../dialogs.dart';
import '../ui_controller.dart';
import '../ui_keys.dart';
import '../ui_models.dart';
import '../widgets.dart';

class ResultsScreen extends StatelessWidget {
  const ResultsScreen({
    super.key,
    required this.controller,
    required this.state,
  });

  final DeviceTestUiController controller;
  final DeviceTestUiState state;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final results = state.results;

    return DeviceTestPage(
      screenKey: DeviceTestUiKeys.resultsScreen,
      title: 'Run Results',
      leading: IconButton(
        tooltip: 'Back to home',
        onPressed: state.busy
            ? null
            : () => controller.navigate(DeviceTestScreen.home),
        icon: const Icon(Icons.arrow_back),
      ),
      child: results == null
          ? Center(
              child: Padding(
                padding: const EdgeInsets.all(24),
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: <Widget>[
                    const Icon(Icons.assessment_outlined, size: 48),
                    const SizedBox(height: 12),
                    Text(
                      'No completed Run is available.',
                      style: theme.textTheme.titleMedium,
                    ),
                    const SizedBox(height: 16),
                    FilledButton(
                      onPressed: () =>
                          controller.navigate(DeviceTestScreen.setup),
                      child: const Text('Start New Run'),
                    ),
                  ],
                ),
              ),
            )
          : ListView(
              padding: const EdgeInsets.all(16),
              children: <Widget>[
                Center(
                  child: ConstrainedBox(
                    constraints: const BoxConstraints(maxWidth: 1100),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: <Widget>[
                        Semantics(
                          header: true,
                          child: Text(
                            '${results.profile.label} profile results',
                            style: theme.textTheme.headlineSmall,
                          ),
                        ),
                        const SizedBox(height: 6),
                        Text(
                          results.profile == TestProfile.full
                              ? 'Full runs can produce formal PR and release evidence.'
                              : 'Quick runs are iteration-only and must not be attached as formal evidence.',
                          style: theme.textTheme.bodyMedium,
                        ),
                        if (state.errorMessage != null) ...<Widget>[
                          const SizedBox(height: 16),
                          ErrorBanner(message: state.errorMessage!),
                        ],
                        const SizedBox(height: 20),
                        _buildSummaryCard(context, results),
                        const SizedBox(height: 16),
                        _buildValidationCard(context, results.validation),
                        const SizedBox(height: 16),
                        PresentationCard(
                          title: 'All Tests',
                          subtitle:
                              'Every result is read-only. A P0 failure or skip '
                              'is preserved as evidence.',
                          child: SingleChildScrollView(
                            scrollDirection: Axis.horizontal,
                            child: DataTable(
                              key: DeviceTestUiKeys.resultsTable,
                              columns: const <DataColumn>[
                                DataColumn(label: Text('Priority')),
                                DataColumn(label: Text('Test')),
                                DataColumn(label: Text('Status')),
                                DataColumn(label: Text('Duration')),
                                DataColumn(label: Text('Notes')),
                              ],
                              rows: <DataRow>[
                                for (final result in results.tests)
                                  DataRow(
                                    cells: <DataCell>[
                                      DataCell(
                                        Text(
                                          result.priority.label,
                                          key: DeviceTestUiKeys.resultsRow(
                                            result.testId,
                                          ),
                                        ),
                                      ),
                                      DataCell(Text(result.title)),
                                      DataCell(
                                        TestStatusBadge(status: result.status),
                                      ),
                                      DataCell(
                                        Text(formatDuration(result.duration)),
                                      ),
                                      DataCell(
                                        ConstrainedBox(
                                          constraints: const BoxConstraints(
                                            maxWidth: 320,
                                          ),
                                          child: Text(result.notes ?? '—'),
                                        ),
                                      ),
                                    ],
                                  ),
                              ],
                            ),
                          ),
                        ),
                        const SizedBox(height: 16),
                        PresentationCard(
                          title: 'Artifacts',
                          subtitle:
                              'JSON and Markdown are generated from the same '
                              'sanitized result object.',
                          child: Wrap(
                            spacing: 8,
                            runSpacing: 8,
                            children: <Widget>[
                              Semantics(
                                label: 'Share JSON device test report',
                                button: true,
                                enabled:
                                    results.jsonAvailable &&
                                    !state.busy &&
                                    results.validation.isValid,
                                excludeSemantics: true,
                                child: FilledButton.icon(
                                  key: DeviceTestUiKeys.shareJson,
                                  onPressed:
                                      results.jsonAvailable &&
                                          !state.busy &&
                                          results.validation.isValid
                                      ? () => _share(
                                          context,
                                          controller.shareJsonReport,
                                        )
                                      : null,
                                  icon: const Icon(Icons.data_object),
                                  label: const Text('Share JSON'),
                                ),
                              ),
                              Semantics(
                                label: 'Share Markdown device test report',
                                button: true,
                                enabled:
                                    results.markdownAvailable &&
                                    !state.busy &&
                                    results.validation.isValid,
                                excludeSemantics: true,
                                child: OutlinedButton.icon(
                                  key: DeviceTestUiKeys.shareMarkdown,
                                  onPressed:
                                      results.markdownAvailable &&
                                          !state.busy &&
                                          results.validation.isValid
                                      ? () => _share(
                                          context,
                                          controller.shareMarkdownReport,
                                        )
                                      : null,
                                  icon: const Icon(Icons.description_outlined),
                                  label: const Text('Share Markdown'),
                                ),
                              ),
                            ],
                          ),
                        ),
                        const SizedBox(height: 16),
                        PresentationCard(
                          title: 'Cleanup and Next Run',
                          child: Wrap(
                            spacing: 8,
                            runSpacing: 8,
                            children: <Widget>[
                              Semantics(
                                label: 'Purge stored controller secrets',
                                button: true,
                                enabled: state.hasStoredSecrets && !state.busy,
                                excludeSemantics: true,
                                child: OutlinedButton.icon(
                                  key: DeviceTestUiKeys.resultsPurgeSecrets,
                                  onPressed:
                                      state.hasStoredSecrets && !state.busy
                                      ? () => _purge(context)
                                      : null,
                                  icon: const Icon(
                                    Icons.delete_forever_outlined,
                                  ),
                                  label: const Text('Purge Secrets'),
                                ),
                              ),
                              Semantics(
                                label: 'Start a new device test setup',
                                button: true,
                                enabled: !state.busy,
                                excludeSemantics: true,
                                child: FilledButton.icon(
                                  key: DeviceTestUiKeys.resultsNewRun,
                                  onPressed: state.busy
                                      ? null
                                      : () => controller.navigate(
                                          DeviceTestScreen.setup,
                                        ),
                                  icon: const Icon(Icons.add),
                                  label: const Text('New Run'),
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

  Widget _buildSummaryCard(BuildContext context, ResultsViewModel results) {
    final summary = results.summary;
    return PresentationCard(
      title: 'Summary',
      child: summary == null
          ? const InfoBanner(
              message: 'No validated summary is available for this Run.',
              icon: Icons.pending_outlined,
            )
          : Semantics(
              key: DeviceTestUiKeys.resultsSummary,
              container: true,
              label:
                  'Overall result ${summary.result.label}. '
                  '${summary.passed} passed, ${summary.failed} failed, '
                  '${summary.notRun} not run.',
              excludeSemantics: true,
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: <Widget>[
                  Row(
                    children: <Widget>[
                      ReportResultBadge(result: summary.result),
                      const Spacer(),
                      Text('${summary.total} tests'),
                    ],
                  ),
                  const SizedBox(height: 16),
                  Row(
                    children: <Widget>[
                      Expanded(
                        child: _CountTile(
                          label: 'Passed',
                          value: summary.passed,
                          icon: Icons.check_circle_outline,
                        ),
                      ),
                      const SizedBox(width: 8),
                      Expanded(
                        child: _CountTile(
                          label: 'Failed',
                          value: summary.failed,
                          icon: Icons.cancel_outlined,
                        ),
                      ),
                      const SizedBox(width: 8),
                      Expanded(
                        child: _CountTile(
                          label: 'Not run',
                          value: summary.notRun,
                          icon: Icons.remove_circle_outline,
                        ),
                      ),
                    ],
                  ),
                ],
              ),
            ),
    );
  }

  Widget _buildValidationCard(
    BuildContext context,
    ReportValidationViewModel validation,
  ) {
    final colors = Theme.of(context).colorScheme;
    final (IconData icon, Color color) = switch (validation.status) {
      ReportUiValidationStatus.valid => (
        Icons.verified_outlined,
        colors.primary,
      ),
      ReportUiValidationStatus.invalid => (Icons.error_outline, colors.error),
      ReportUiValidationStatus.notApplicable => (
        Icons.info_outline,
        colors.tertiary,
      ),
      ReportUiValidationStatus.unavailable => (
        Icons.pending_outlined,
        colors.onSurfaceVariant,
      ),
    };
    return Semantics(
      key: DeviceTestUiKeys.resultsValidation,
      container: true,
      label: 'Report validation: ${validation.message}',
      excludeSemantics: true,
      child: PresentationCard(
        title: 'Report Validation',
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: <Widget>[
            Row(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                Icon(icon, color: color),
                const SizedBox(width: 8),
                Expanded(child: Text(validation.message)),
              ],
            ),
            if (validation.issues.isNotEmpty) ...<Widget>[
              const SizedBox(height: 12),
              for (final issue in validation.issues)
                Padding(
                  padding: const EdgeInsets.only(bottom: 4),
                  child: Text('• $issue'),
                ),
            ],
          ],
        ),
      ),
    );
  }

  Future<void> _share(
    BuildContext context,
    Future<void> Function() action,
  ) async {
    try {
      await action();
    } on Object {
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('Report artifacts could not be shared.'),
          ),
        );
      }
    }
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

class _CountTile extends StatelessWidget {
  const _CountTile({
    required this.label,
    required this.value,
    required this.icon,
  });

  final String label;
  final int value;
  final IconData icon;

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        color: Theme.of(context).colorScheme.surfaceContainerHighest,
        borderRadius: BorderRadius.circular(12),
      ),
      padding: const EdgeInsets.all(12),
      child: Column(
        children: <Widget>[
          Icon(icon),
          const SizedBox(height: 4),
          Text('$value', style: Theme.of(context).textTheme.titleLarge),
          Text(label),
        ],
      ),
    );
  }
}
