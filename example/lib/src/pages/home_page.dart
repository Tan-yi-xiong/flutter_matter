import 'package:flutter/material.dart';

import '../app.dart';
import '../models.dart';
import '../widgets.dart';
import 'advanced_page.dart';
import 'api_console_page.dart';
import 'commissioning_page.dart';
import 'device_page.dart';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) {
    final controller = ExampleScope.of(context);
    return AnimatedBuilder(
      animation: controller,
      builder: (context, _) {
        if (!controller.initialized) {
          return const Scaffold(
            body: Center(child: CircularProgressIndicator()),
          );
        }
        if (controller.initializationError != null) {
          return Scaffold(
            appBar: AppBar(title: const Text('Matter API Showcase')),
            body: Center(
              child: Padding(
                padding: const EdgeInsets.all(24),
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    const Icon(Icons.error_outline, size: 40),
                    const SizedBox(height: 12),
                    const Text('Example initialization failed.'),
                    const SizedBox(height: 8),
                    SelectableText(
                      controller.initializationError!,
                      textAlign: TextAlign.center,
                    ),
                    const SizedBox(height: 16),
                    FilledButton(
                      onPressed: controller.initialize,
                      child: const Text('Retry'),
                    ),
                  ],
                ),
              ),
            ),
          );
        }
        return Scaffold(
          appBar: AppBar(
            title: const Text('Matter API Showcase'),
            actions: const [LogButton(), SizedBox(width: 8)],
          ),
          body: RefreshIndicator(
            onRefresh: controller.initialize,
            child: ListView(
              padding: const EdgeInsets.fromLTRB(16, 8, 16, 32),
              children: [
                _HeroPanel(controller: controller),
                const SizedBox(height: 18),
                _QuickActions(controller: controller),
                const SizedBox(height: 24),
                Row(
                  children: [
                    Expanded(
                      child: Text(
                        'Saved devices',
                        style: Theme.of(context).textTheme.titleLarge,
                      ),
                    ),
                    Text(
                      '${controller.devices.length}',
                      style: Theme.of(context).textTheme.labelLarge,
                    ),
                  ],
                ),
                const SizedBox(height: 10),
                if (controller.devices.isEmpty)
                  const _EmptyDevices()
                else
                  ...controller.devices.map(
                    (device) => Padding(
                      padding: const EdgeInsets.only(bottom: 10),
                      child: _DeviceCard(device: device),
                    ),
                  ),
                const SizedBox(height: 14),
                Text(
                  'Demo persistence uses SharedPreferences. Production apps '
                  'must protect controller key material and fabric credentials.',
                  style: Theme.of(context).textTheme.bodySmall?.copyWith(
                    color: Theme.of(context).colorScheme.onSurfaceVariant,
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

class _HeroPanel extends StatelessWidget {
  const _HeroPanel({required this.controller});

  final MatterSessionController controller;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final colors = theme.colorScheme;
    final active = controller.activeDevice;
    return Container(
      padding: const EdgeInsets.all(22),
      decoration: BoxDecoration(
        borderRadius: BorderRadius.circular(28),
        gradient: LinearGradient(
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
          colors: [
            colors.primary,
            colors.primary.withValues(alpha: 0.78),
            colors.tertiary.withValues(alpha: 0.86),
          ],
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            'Matter API / feature console',
            style: theme.textTheme.headlineSmall?.copyWith(
              color: colors.onPrimary,
              fontWeight: FontWeight.w700,
            ),
          ),
          const SizedBox(height: 8),
          Text(
            'Exercise commissioning, CASE connection, cluster helpers, '
            'interaction-model APIs, commissioning windows and advanced '
            'platform hooks from one app.',
            style: theme.textTheme.bodyMedium?.copyWith(
              color: colors.onPrimary.withValues(alpha: 0.86),
            ),
          ),
          const SizedBox(height: 18),
          Wrap(
            spacing: 10,
            runSpacing: 10,
            children: [
              _HeroMetric(
                icon: Icons.memory_outlined,
                label: controller.identity == null
                    ? 'Identity loading'
                    : 'Controller ready',
              ),
              _HeroMetric(
                icon: Icons.devices_other_outlined,
                label: '${controller.devices.length} saved',
              ),
              _HeroMetric(
                icon: Icons.link,
                label: active == null ? 'No active device' : active.displayName,
              ),
            ],
          ),
        ],
      ),
    );
  }
}

class _HeroMetric extends StatelessWidget {
  const _HeroMetric({required this.icon, required this.label});

  final IconData icon;
  final String label;

  @override
  Widget build(BuildContext context) {
    final color = Theme.of(context).colorScheme.onPrimary;
    return DecoratedBox(
      decoration: BoxDecoration(
        color: color.withValues(alpha: 0.12),
        borderRadius: BorderRadius.circular(999),
        border: Border.all(color: color.withValues(alpha: 0.24)),
      ),
      child: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 11, vertical: 7),
        child: Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            Icon(icon, size: 16, color: color),
            const SizedBox(width: 7),
            Text(
              label,
              style: Theme.of(
                context,
              ).textTheme.labelMedium?.copyWith(color: color),
            ),
          ],
        ),
      ),
    );
  }
}

class _QuickActions extends StatelessWidget {
  const _QuickActions({required this.controller});

  final MatterSessionController controller;

  @override
  Widget build(BuildContext context) {
    return Row(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Expanded(
          child: _ActionCard(
            icon: Icons.add_link,
            title: 'Commission',
            detail: 'QR / manual code',
            color: Theme.of(context).colorScheme.primary,
            onTap: () => Navigator.of(context).push(
              MaterialPageRoute<void>(
                builder: (_) => const CommissioningPage(),
              ),
            ),
          ),
        ),
        const SizedBox(width: 10),
        Expanded(
          child: _ActionCard(
            icon: Icons.terminal,
            title: 'API Console',
            detail: 'invoke / read / write / subscribe',
            color: Theme.of(context).colorScheme.tertiary,
            onTap: () => _openConsole(context, controller),
          ),
        ),
        const SizedBox(width: 10),
        Expanded(
          child: _ActionCard(
            icon: Icons.tune,
            title: 'Advanced',
            detail: 'BLE / address / NSD',
            color: Theme.of(context).colorScheme.secondary,
            onTap: () => Navigator.of(context).push(
              MaterialPageRoute<void>(builder: (_) => const AdvancedPage()),
            ),
          ),
        ),
      ],
    );
  }

  void _openConsole(BuildContext context, MatterSessionController controller) {
    final device =
        controller.activeDevice ??
        (controller.devices.isEmpty ? null : controller.devices.first);
    if (device == null) {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('Commission or select a device first.')),
      );
      return;
    }
    controller.selectDevice(device);
    Navigator.of(
      context,
    ).push(MaterialPageRoute<void>(builder: (_) => const ApiConsolePage()));
  }
}

class _ActionCard extends StatelessWidget {
  const _ActionCard({
    required this.icon,
    required this.title,
    required this.detail,
    required this.color,
    required this.onTap,
  });

  final IconData icon;
  final String title;
  final String detail;
  final Color color;
  final VoidCallback onTap;

  @override
  Widget build(BuildContext context) {
    return Card(
      color: Theme.of(context).colorScheme.surface,
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(18),
        side: BorderSide(color: Theme.of(context).colorScheme.outlineVariant),
      ),
      child: InkWell(
        onTap: onTap,
        child: Padding(
          padding: const EdgeInsets.all(14),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Icon(icon, color: color),
              const SizedBox(height: 14),
              Text(title, style: Theme.of(context).textTheme.titleSmall),
              const SizedBox(height: 4),
              Text(
                detail,
                maxLines: 2,
                overflow: TextOverflow.ellipsis,
                style: Theme.of(context).textTheme.bodySmall?.copyWith(
                  color: Theme.of(context).colorScheme.onSurfaceVariant,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class _DeviceCard extends StatelessWidget {
  const _DeviceCard({required this.device});

  final SavedDevice device;

  @override
  Widget build(BuildContext context) {
    final controller = ExampleScope.of(context);
    final active = controller.activeDevice?.nodeId == device.nodeId;
    return Card(
      color: active
          ? Theme.of(
              context,
            ).colorScheme.primaryContainer.withValues(alpha: 0.4)
          : Theme.of(context).colorScheme.surface,
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(18),
        side: BorderSide(
          color: active
              ? Theme.of(context).colorScheme.primary
              : Theme.of(context).colorScheme.outlineVariant,
        ),
      ),
      child: ListTile(
        contentPadding: const EdgeInsets.symmetric(horizontal: 16, vertical: 6),
        leading: CircleAvatar(
          child: Icon(active ? Icons.link : Icons.lightbulb_outline),
        ),
        title: Text(device.displayName),
        subtitle: Padding(
          padding: const EdgeInsets.only(top: 5),
          child: Text(
            'Node ${formatId(device.nodeId)}'
            '${device.vendorId == null ? '' : '  •  Vendor ${formatId(device.vendorId!)}'}'
            '${device.productId == null ? '' : '  •  Product ${formatId(device.productId!)}'}',
          ),
        ),
        trailing: const Icon(Icons.chevron_right),
        onTap: () async {
          await controller.selectDevice(device);
          if (context.mounted) {
            await Navigator.of(
              context,
            ).push(MaterialPageRoute<void>(builder: (_) => const DevicePage()));
          }
        },
      ),
    );
  }
}

class _EmptyDevices extends StatelessWidget {
  const _EmptyDevices();

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    return Container(
      padding: const EdgeInsets.all(22),
      decoration: BoxDecoration(
        color: colors.surface,
        borderRadius: BorderRadius.circular(20),
        border: Border.all(color: colors.outlineVariant),
      ),
      child: Column(
        children: [
          Icon(Icons.sensors_off_outlined, size: 34, color: colors.outline),
          const SizedBox(height: 10),
          Text(
            'No commissioned devices',
            style: Theme.of(context).textTheme.titleMedium,
          ),
          const SizedBox(height: 5),
          Text(
            'Use Commission to parse a setup payload and run the Matter SDK flow.',
            textAlign: TextAlign.center,
            style: Theme.of(
              context,
            ).textTheme.bodySmall?.copyWith(color: colors.onSurfaceVariant),
          ),
        ],
      ),
    );
  }
}
