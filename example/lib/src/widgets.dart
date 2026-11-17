import 'package:flutter/material.dart';

import 'app.dart';
import 'models.dart';

class ApiBadge extends StatelessWidget {
  const ApiBadge(this.api, {super.key});

  final String api;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    return DecoratedBox(
      decoration: BoxDecoration(
        color: colors.secondaryContainer,
        borderRadius: BorderRadius.circular(999),
      ),
      child: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
        child: Text(
          api,
          style: Theme.of(context).textTheme.labelMedium?.copyWith(
            color: colors.onSecondaryContainer,
            fontFamily: 'monospace',
          ),
        ),
      ),
    );
  }
}

class SectionCard extends StatelessWidget {
  const SectionCard({
    super.key,
    required this.title,
    required this.children,
    this.api,
    this.subtitle,
    this.trailing,
  });

  final String title;
  final String? subtitle;
  final String? api;
  final Widget? trailing;
  final List<Widget> children;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Card(
      color: theme.colorScheme.surface,
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(20),
        side: BorderSide(color: theme.colorScheme.outlineVariant),
      ),
      child: Padding(
        padding: const EdgeInsets.all(18),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Row(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Expanded(
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Wrap(
                        spacing: 10,
                        runSpacing: 8,
                        crossAxisAlignment: WrapCrossAlignment.center,
                        children: [
                          Text(title, style: theme.textTheme.titleMedium),
                          if (api != null) ApiBadge(api!),
                        ],
                      ),
                      if (subtitle != null) ...[
                        const SizedBox(height: 6),
                        Text(
                          subtitle!,
                          style: theme.textTheme.bodySmall?.copyWith(
                            color: theme.colorScheme.onSurfaceVariant,
                          ),
                        ),
                      ],
                    ],
                  ),
                ),
                if (trailing != null) trailing!,
              ],
            ),
            const SizedBox(height: 16),
            ...children,
          ],
        ),
      ),
    );
  }
}

class OperationResultCard extends StatelessWidget {
  const OperationResultCard({super.key, required this.result});

  final OperationResult? result;

  @override
  Widget build(BuildContext context) {
    final value = result;
    if (value == null) {
      return const SizedBox.shrink();
    }
    final colors = Theme.of(context).colorScheme;
    final background = value.success
        ? colors.primaryContainer.withValues(alpha: 0.55)
        : colors.errorContainer.withValues(alpha: 0.65);
    final foreground = value.success
        ? colors.onPrimaryContainer
        : colors.onErrorContainer;
    return Container(
      width: double.infinity,
      padding: const EdgeInsets.all(14),
      decoration: BoxDecoration(
        color: background,
        borderRadius: BorderRadius.circular(14),
        border: Border.all(
          color: value.success ? colors.primary : colors.error,
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            children: [
              Icon(
                value.success
                    ? Icons.check_circle_outline
                    : Icons.error_outline,
                color: foreground,
                size: 20,
              ),
              const SizedBox(width: 8),
              Expanded(
                child: Text(
                  value.summary,
                  style: Theme.of(context).textTheme.bodyMedium?.copyWith(
                    color: foreground,
                    fontWeight: FontWeight.w600,
                  ),
                ),
              ),
            ],
          ),
          if (value.detail case final detail?)
            if (detail.trim().isNotEmpty) ...[
              const SizedBox(height: 10),
              SelectableText(
                detail,
                style: Theme.of(context).textTheme.bodySmall?.copyWith(
                  color: foreground,
                  fontFamily: 'monospace',
                ),
              ),
            ],
        ],
      ),
    );
  }
}

class InfoRow extends StatelessWidget {
  const InfoRow(this.label, this.value, {super.key});

  final String label;
  final String value;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 5),
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          SizedBox(
            width: 132,
            child: Text(
              label,
              style: theme.textTheme.bodySmall?.copyWith(
                color: theme.colorScheme.onSurfaceVariant,
              ),
            ),
          ),
          Expanded(
            child: SelectableText(value, style: theme.textTheme.bodyMedium),
          ),
        ],
      ),
    );
  }
}

class BusyActionButton extends StatelessWidget {
  const BusyActionButton({
    super.key,
    required this.label,
    required this.onPressed,
    this.icon,
    this.busy = false,
  });

  final String label;
  final IconData? icon;
  final bool busy;
  final VoidCallback? onPressed;

  @override
  Widget build(BuildContext context) {
    final child = busy
        ? const SizedBox(
            width: 18,
            height: 18,
            child: CircularProgressIndicator(strokeWidth: 2),
          )
        : icon == null
        ? Text(label)
        : Row(
            mainAxisSize: MainAxisSize.min,
            children: [
              Icon(icon, size: 18),
              const SizedBox(width: 8),
              Text(label),
            ],
          );
    return FilledButton(onPressed: busy ? null : onPressed, child: child);
  }
}

class ConnectionBadge extends StatelessWidget {
  const ConnectionBadge({super.key, required this.phase});

  final ConnectionPhase phase;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final (label, color) = switch (phase) {
      ConnectionPhase.disconnected => ('Disconnected', colors.outline),
      ConnectionPhase.connecting => ('Connecting', colors.tertiary),
      ConnectionPhase.connected => ('Connected', colors.primary),
    };
    return DecoratedBox(
      decoration: BoxDecoration(
        color: color.withValues(alpha: 0.12),
        borderRadius: BorderRadius.circular(999),
        border: Border.all(color: color.withValues(alpha: 0.45)),
      ),
      child: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
        child: Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            Icon(Icons.circle, size: 8, color: color),
            const SizedBox(width: 6),
            Text(label, style: Theme.of(context).textTheme.labelMedium),
          ],
        ),
      ),
    );
  }
}

class LogButton extends StatelessWidget {
  const LogButton({super.key});

  @override
  Widget build(BuildContext context) {
    final controller = ExampleScope.of(context);
    return IconButton(
      tooltip: 'Operation log',
      onPressed: () => showModalBottomSheet<void>(
        context: context,
        isScrollControlled: true,
        showDragHandle: true,
        builder: (_) => _OperationLogSheet(controller: controller),
      ),
      icon: const Icon(Icons.receipt_long_outlined),
    );
  }
}

class _OperationLogSheet extends StatelessWidget {
  const _OperationLogSheet({required this.controller});

  final MatterSessionController controller;

  @override
  Widget build(BuildContext context) {
    return AnimatedBuilder(
      animation: controller,
      builder: (context, _) {
        final entries = controller.operationLog;
        return FractionallySizedBox(
          heightFactor: 0.85,
          child: SafeArea(
            top: false,
            child: Column(
              children: [
                Padding(
                  padding: const EdgeInsets.fromLTRB(20, 0, 12, 8),
                  child: Row(
                    children: [
                      Expanded(
                        child: Text(
                          'Operation log',
                          style: Theme.of(context).textTheme.titleLarge,
                        ),
                      ),
                      TextButton.icon(
                        onPressed: entries.isEmpty ? null : controller.clearLog,
                        icon: const Icon(Icons.delete_sweep_outlined),
                        label: const Text('Clear'),
                      ),
                    ],
                  ),
                ),
                const Divider(height: 1),
                Expanded(
                  child: entries.isEmpty
                      ? const Center(child: Text('No API operations yet.'))
                      : ListView.separated(
                          padding: const EdgeInsets.all(16),
                          itemCount: entries.length,
                          separatorBuilder: (_, __) =>
                              const SizedBox(height: 10),
                          itemBuilder: (context, index) {
                            final entry = entries[index];
                            return Card(
                              color: Theme.of(
                                context,
                              ).colorScheme.surfaceContainerLow,
                              child: ExpansionTile(
                                leading: Icon(
                                  entry.result.success
                                      ? Icons.check_circle_outline
                                      : Icons.error_outline,
                                ),
                                title: Text(entry.title),
                                subtitle: Padding(
                                  padding: const EdgeInsets.only(top: 6),
                                  child: Wrap(
                                    spacing: 10,
                                    runSpacing: 6,
                                    children: [
                                      ApiBadge(entry.api),
                                      Text(_formatTime(entry.timestamp)),
                                    ],
                                  ),
                                ),
                                childrenPadding: const EdgeInsets.fromLTRB(
                                  16,
                                  0,
                                  16,
                                  16,
                                ),
                                children: [
                                  Align(
                                    alignment: Alignment.centerLeft,
                                    child: OperationResultCard(
                                      result: entry.result,
                                    ),
                                  ),
                                ],
                              ),
                            );
                          },
                        ),
                ),
              ],
            ),
          ),
        );
      },
    );
  }
}

String _formatTime(DateTime value) {
  final local = value.toLocal();
  String two(int part) => part.toString().padLeft(2, '0');
  return '${two(local.hour)}:${two(local.minute)}:${two(local.second)}';
}
