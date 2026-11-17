import 'dart:io';

import 'package:flutter/material.dart';

import '../app.dart';
import '../models.dart';
import '../widgets.dart';
import 'device_page.dart';

class AdvancedPage extends StatefulWidget {
  const AdvancedPage({super.key});

  @override
  State<AdvancedPage> createState() => _AdvancedPageState();
}

class _AdvancedPageState extends State<AdvancedPage> {
  final _addressController = TextEditingController();
  final _portController = TextEditingController(text: '5540');
  final _discriminatorController = TextEditingController();
  final _setupPinController = TextEditingController();
  final _labelController = TextEditingController(text: 'Direct address device');
  OperationResult? _result;

  @override
  void dispose() {
    _addressController.dispose();
    _portController.dispose();
    _discriminatorController.dispose();
    _setupPinController.dispose();
    _labelController.dispose();
    super.dispose();
  }

  Future<void> _commissionByAddress() async {
    final session = ExampleScope.of(context);
    final address = _addressController.text.trim();
    final port = int.tryParse(_portController.text);
    final discriminator = int.tryParse(_discriminatorController.text);
    final setupPin = int.tryParse(_setupPinController.text);
    if (address.isEmpty) {
      _showMessage('Address is required.');
      return;
    }
    if (port == null || port < 1 || port > 65535) {
      _showMessage('Port must be 1..65535.');
      return;
    }
    if (discriminator == null || discriminator < 0 || discriminator > 0xFFF) {
      _showMessage('Discriminator must be 0..4095.');
      return;
    }
    if (setupPin == null || setupPin < 1 || setupPin > 99999998) {
      _showMessage('Setup PIN is invalid.');
      return;
    }
    final result = await session.commissionWithAddress(
      address: address,
      port: port,
      discriminator: discriminator,
      setupPin: setupPin,
      deviceLabel: _labelController.text,
    );
    if (mounted) {
      setState(() => _result = result);
    }
  }

  void _showMessage(String message) {
    ScaffoldMessenger.of(context)
      ..hideCurrentSnackBar()
      ..showSnackBar(SnackBar(content: Text(message)));
  }

  @override
  Widget build(BuildContext context) {
    final session = ExampleScope.of(context);
    return AnimatedBuilder(
      animation: session,
      builder: (context, _) {
        final busy = session.operationBusy;
        return Scaffold(
          appBar: AppBar(
            title: const Text('Advanced'),
            actions: const [LogButton(), SizedBox(width: 8)],
          ),
          body: ListView(
            padding: const EdgeInsets.fromLTRB(16, 8, 16, 32),
            children: [
              const SectionCard(
                title: 'Manual Android BLE / GATT',
                api: 'BlePlatformDelegate',
                subtitle:
                    'The implementation is available in the commissioning flow on Android.',
                children: [
                  InfoRow('Default transport', 'SDK-managed discovery'),
                  InfoRow(
                    'Manual override',
                    'Enable on the Commission device screen',
                  ),
                  InfoRow(
                    'Validation status',
                    'Compiled on both platforms; manual BLE path is build-only for this refactor.',
                  ),
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Direct-address commissioning',
                api: 'pairDeviceWithAddress',
                subtitle: Platform.isAndroid
                    ? 'Android only: bypass SDK discovery and connect PASE directly to the supplied endpoint.'
                    : 'This platform does not implement pairDeviceWithAddress; use pairDevice.',
                children: [
                  TextField(
                    controller: _addressController,
                    enabled: Platform.isAndroid && !busy,
                    decoration: const InputDecoration(
                      labelText: 'IP address or host',
                      prefixIcon: Icon(Icons.lan_outlined),
                    ),
                  ),
                  const SizedBox(height: 10),
                  Row(
                    children: [
                      Expanded(
                        child: TextField(
                          controller: _portController,
                          enabled: Platform.isAndroid && !busy,
                          keyboardType: TextInputType.number,
                          decoration: const InputDecoration(labelText: 'Port'),
                        ),
                      ),
                      const SizedBox(width: 10),
                      Expanded(
                        child: TextField(
                          controller: _discriminatorController,
                          enabled: Platform.isAndroid && !busy,
                          keyboardType: TextInputType.number,
                          decoration: const InputDecoration(
                            labelText: 'Discriminator',
                          ),
                        ),
                      ),
                    ],
                  ),
                  const SizedBox(height: 10),
                  TextField(
                    controller: _setupPinController,
                    enabled: Platform.isAndroid && !busy,
                    keyboardType: TextInputType.number,
                    decoration: const InputDecoration(
                      labelText: 'Setup PIN',
                      prefixIcon: Icon(Icons.password),
                    ),
                  ),
                  const SizedBox(height: 10),
                  TextField(
                    controller: _labelController,
                    enabled: Platform.isAndroid && !busy,
                    decoration: const InputDecoration(
                      labelText: 'Device label',
                      prefixIcon: Icon(Icons.label_outline),
                    ),
                  ),
                  const SizedBox(height: 12),
                  FilledButton.tonalIcon(
                    onPressed: Platform.isAndroid && !busy
                        ? _commissionByAddress
                        : null,
                    icon: const Icon(Icons.router_outlined),
                    label: const Text('Commission by address'),
                  ),
                  if (busy) ...[
                    const SizedBox(height: 12),
                    const LinearProgressIndicator(),
                    const SizedBox(height: 8),
                    Text(
                      session.commissioningStage ?? 'Working…',
                      textAlign: TextAlign.center,
                    ),
                  ],
                  const SizedBox(height: 12),
                  OperationResultCard(result: _result),
                  if (_result?.success == true) ...[
                    const SizedBox(height: 12),
                    OutlinedButton.icon(
                      onPressed: () => Navigator.of(context).push(
                        MaterialPageRoute<void>(
                          builder: (_) => const DevicePage(),
                        ),
                      ),
                      icon: const Icon(Icons.developer_board_outlined),
                      label: const Text('Open device workspace'),
                    ),
                  ],
                ],
              ),
              const SizedBox(height: 14),
              AnimatedBuilder(
                animation: session.nsd,
                builder: (context, _) {
                  final monitor = session.nsd;
                  return SectionCard(
                    title: 'NSD callback monitor',
                    api: 'NsdManager',
                    subtitle: monitor.supported
                        ? 'Resolves Matter mDNS requests with Bonsoir and shows native resolve, publish and remove callbacks.'
                        : 'The iOS plugin does not route NsdManager in this version.',
                    trailing: Switch.adaptive(
                      value: monitor.enabled,
                      onChanged: monitor.supported
                          ? (value) async {
                              if (value) {
                                await monitor.enable();
                              } else {
                                await monitor.disable();
                              }
                            }
                          : null,
                    ),
                    children: [
                      if (!monitor.enabled)
                        const Text(
                          'Enable the monitor before starting SDK-managed commissioning.',
                        )
                      else if (monitor.events.isEmpty)
                        const Text('Waiting for NSD activity…')
                      else
                        Container(
                          constraints: const BoxConstraints(maxHeight: 260),
                          decoration: BoxDecoration(
                            color: Theme.of(
                              context,
                            ).colorScheme.surfaceContainerLow,
                            borderRadius: BorderRadius.circular(14),
                          ),
                          child: ListView.builder(
                            shrinkWrap: true,
                            padding: const EdgeInsets.all(12),
                            itemCount: monitor.events.length,
                            itemBuilder: (context, index) => Padding(
                              padding: const EdgeInsets.symmetric(vertical: 5),
                              child: Text(
                                monitor.events[index],
                                style: Theme.of(context).textTheme.bodySmall
                                    ?.copyWith(fontFamily: 'monospace'),
                              ),
                            ),
                          ),
                        ),
                      if (monitor.events.isNotEmpty) ...[
                        const SizedBox(height: 10),
                        Align(
                          alignment: Alignment.centerRight,
                          child: TextButton.icon(
                            onPressed: monitor.clear,
                            icon: const Icon(Icons.clear_all),
                            label: const Text('Clear events'),
                          ),
                        ),
                      ],
                    ],
                  );
                },
              ),
            ],
          ),
        );
      },
    );
  }
}
