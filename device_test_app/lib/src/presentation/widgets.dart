import 'package:flutter/material.dart';

import '../application/operator_prompt.dart';
import '../domain/domain.dart';
import '../report/report.dart';
import 'ui_keys.dart';
import 'ui_models.dart';

class DeviceTestPage extends StatelessWidget {
  const DeviceTestPage({
    super.key,
    required this.title,
    required this.child,
    this.actions = const <Widget>[],
    this.leading,
    this.screenKey,
  });

  final String title;
  final Widget child;
  final List<Widget> actions;
  final Widget? leading;
  final Key? screenKey;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: screenKey,
      appBar: AppBar(title: Text(title), leading: leading, actions: actions),
      body: SafeArea(child: child),
    );
  }
}

class PresentationCard extends StatelessWidget {
  const PresentationCard({
    super.key,
    required this.child,
    this.title,
    this.subtitle,
    this.trailing,
    this.padding = const EdgeInsets.all(16),
  });

  final Widget child;
  final String? title;
  final String? subtitle;
  final Widget? trailing;
  final EdgeInsetsGeometry padding;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Card(
      clipBehavior: Clip.antiAlias,
      child: Padding(
        padding: padding,
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: <Widget>[
            if (title != null)
              Row(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: <Widget>[
                  Expanded(
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: <Widget>[
                        Semantics(
                          header: true,
                          child: Text(
                            title!,
                            style: theme.textTheme.titleMedium,
                          ),
                        ),
                        if (subtitle != null) ...<Widget>[
                          const SizedBox(height: 4),
                          Text(subtitle!, style: theme.textTheme.bodySmall),
                        ],
                      ],
                    ),
                  ),
                  if (trailing != null) ...<Widget>[
                    const SizedBox(width: 12),
                    trailing!,
                  ],
                ],
              ),
            if (title != null) const SizedBox(height: 12),
            child,
          ],
        ),
      ),
    );
  }
}

class ErrorBanner extends StatelessWidget {
  const ErrorBanner({super.key, required this.message});

  final String message;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    return Semantics(
      container: true,
      liveRegion: true,
      label: 'Error: $message',
      child: Container(
        decoration: BoxDecoration(
          color: colors.errorContainer,
          borderRadius: BorderRadius.circular(12),
        ),
        padding: const EdgeInsets.all(12),
        child: Row(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Icon(Icons.error_outline, color: colors.onErrorContainer),
            const SizedBox(width: 8),
            Expanded(
              child: Text(
                message,
                style: TextStyle(color: colors.onErrorContainer),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class InfoBanner extends StatelessWidget {
  const InfoBanner({
    super.key,
    required this.message,
    this.icon = Icons.info_outline,
    this.tone,
  });

  final String message;
  final IconData icon;
  final Color? tone;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final effectiveTone = tone ?? colors.primary;
    return Container(
      decoration: BoxDecoration(
        color: effectiveTone.withValues(alpha: 0.09),
        border: Border.all(color: effectiveTone.withValues(alpha: 0.35)),
        borderRadius: BorderRadius.circular(12),
      ),
      padding: const EdgeInsets.all(12),
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          Icon(icon, color: effectiveTone),
          const SizedBox(width: 8),
          Expanded(child: Text(message)),
        ],
      ),
    );
  }
}

class PriorityBadge extends StatelessWidget {
  const PriorityBadge({super.key, required this.priority});

  final DeviceTestPriority priority;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final background = switch (priority) {
      DeviceTestPriority.p0 => colors.errorContainer,
      DeviceTestPriority.p1 => colors.tertiaryContainer,
      DeviceTestPriority.p2 => colors.secondaryContainer,
    };
    final foreground = switch (priority) {
      DeviceTestPriority.p0 => colors.onErrorContainer,
      DeviceTestPriority.p1 => colors.onTertiaryContainer,
      DeviceTestPriority.p2 => colors.onSecondaryContainer,
    };
    return _Badge(
      label: priority.label,
      background: background,
      foreground: foreground,
    );
  }
}

class TestStatusBadge extends StatelessWidget {
  const TestStatusBadge({super.key, required this.status});

  final DeviceTestStatus status;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final (
      Color background,
      Color foreground,
      IconData icon,
    ) = switch (status) {
      DeviceTestStatus.pending => (
        colors.surfaceContainerHighest,
        colors.onSurfaceVariant,
        Icons.schedule,
      ),
      DeviceTestStatus.running => (
        colors.primaryContainer,
        colors.onPrimaryContainer,
        Icons.play_arrow,
      ),
      DeviceTestStatus.passed => (
        colors.secondaryContainer,
        colors.onSecondaryContainer,
        Icons.check_circle_outline,
      ),
      DeviceTestStatus.failed => (
        colors.errorContainer,
        colors.onErrorContainer,
        Icons.cancel_outlined,
      ),
      DeviceTestStatus.notRun => (
        colors.tertiaryContainer,
        colors.onTertiaryContainer,
        Icons.remove_circle_outline,
      ),
    };
    return _Badge(
      label: status.label,
      background: background,
      foreground: foreground,
      icon: icon,
    );
  }
}

class ReportResultBadge extends StatelessWidget {
  const ReportResultBadge({super.key, required this.result});

  final ReportResult result;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final (
      Color background,
      Color foreground,
      IconData icon,
    ) = switch (result) {
      ReportResult.passed => (
        colors.secondaryContainer,
        colors.onSecondaryContainer,
        Icons.verified_outlined,
      ),
      ReportResult.failed => (
        colors.errorContainer,
        colors.onErrorContainer,
        Icons.error_outline,
      ),
      ReportResult.notRun => (
        colors.tertiaryContainer,
        colors.onTertiaryContainer,
        Icons.remove_circle_outline,
      ),
    };
    return _Badge(
      label: result.label,
      background: background,
      foreground: foreground,
      icon: icon,
    );
  }
}

class RequiredActorBadge extends StatelessWidget {
  const RequiredActorBadge({super.key, required this.actor});

  final RequiredActor actor;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final (Color background, Color foreground, IconData icon) = switch (actor) {
      RequiredActor.app => (
        colors.secondaryContainer,
        colors.onSecondaryContainer,
        Icons.smart_toy_outlined,
      ),
      RequiredActor.agentAndroid => (
        colors.primaryContainer,
        colors.onPrimaryContainer,
        Icons.phone_android,
      ),
      RequiredActor.human => (
        colors.tertiaryContainer,
        colors.onTertiaryContainer,
        Icons.person_outline,
      ),
    };
    return Semantics(
      key: DeviceTestUiKeys.requiredActor,
      container: true,
      label: actor.semanticsLabel,
      excludeSemantics: true,
      child: _Badge(
        label: actor.visibleLabel,
        background: background,
        foreground: foreground,
        icon: icon,
      ),
    );
  }
}

class PreflightRow extends StatelessWidget {
  const PreflightRow({super.key, required this.check});

  final PreflightCheckViewModel check;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final (IconData icon, Color color) = switch (check.status) {
      PreflightStatus.passed => (Icons.check_circle, colors.primary),
      PreflightStatus.warning => (Icons.warning_amber, colors.tertiary),
      PreflightStatus.failed => (Icons.cancel, colors.error),
    };
    return Semantics(
      container: true,
      label: 'Preflight ${check.label}: ${check.status.label}',
      excludeSemantics: true,
      child: Padding(
        padding: const EdgeInsets.symmetric(vertical: 6),
        child: Row(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Icon(icon, color: color, size: 20),
            const SizedBox(width: 8),
            Expanded(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: <Widget>[
                  Text(
                    check.label,
                    style: Theme.of(context).textTheme.bodyMedium?.copyWith(
                      fontWeight: FontWeight.w600,
                    ),
                  ),
                  if (check.detail != null)
                    Text(
                      check.detail!,
                      style: Theme.of(context).textTheme.bodySmall,
                    ),
                ],
              ),
            ),
            const SizedBox(width: 8),
            Text(check.status.label, style: TextStyle(color: color)),
          ],
        ),
      ),
    );
  }
}

class DeviceTestStatusLine extends StatelessWidget {
  const DeviceTestStatusLine({
    super.key,
    required this.label,
    required this.value,
  });

  final String label;
  final String value;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 3),
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          SizedBox(
            width: 132,
            child: Text(label, style: Theme.of(context).textTheme.bodySmall),
          ),
          Expanded(
            child: Text(value, style: Theme.of(context).textTheme.bodyMedium),
          ),
        ],
      ),
    );
  }
}

class _Badge extends StatelessWidget {
  const _Badge({
    required this.label,
    required this.background,
    required this.foreground,
    this.icon,
  });

  final String label;
  final Color background;
  final Color foreground;
  final IconData? icon;

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        color: background,
        borderRadius: BorderRadius.circular(999),
      ),
      padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 4),
      child: Row(
        mainAxisSize: MainAxisSize.min,
        children: <Widget>[
          if (icon != null) ...<Widget>[
            Icon(icon, size: 14, color: foreground),
            const SizedBox(width: 4),
          ],
          Text(
            label,
            style: Theme.of(context).textTheme.labelSmall?.copyWith(
              color: foreground,
              fontWeight: FontWeight.w700,
            ),
          ),
        ],
      ),
    );
  }
}

String formatDuration(Duration duration) {
  final minutes = duration.inMinutes;
  final seconds = duration.inSeconds.remainder(60).toString().padLeft(2, '0');
  return '$minutes:$seconds';
}
