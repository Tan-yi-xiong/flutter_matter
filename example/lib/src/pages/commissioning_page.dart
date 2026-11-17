import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:mobile_scanner/mobile_scanner.dart';

import '../app.dart';
import '../models.dart';
import '../widgets.dart';
import 'device_page.dart';

class CommissioningPage extends StatefulWidget {
  const CommissioningPage({super.key});

  @override
  State<CommissioningPage> createState() => _CommissioningPageState();
}

class _CommissioningPageState extends State<CommissioningPage> {
  final _codeController = TextEditingController();
  final _ssidController = TextEditingController();
  final _passwordController = TextEditingController();
  final _labelController = TextEditingController(text: 'Matter On/Off');
  final _scannerController = MobileScannerController();

  OnboardingPayload? _payload;
  bool _parsing = false;
  bool _scanning = false;
  bool _useAndroidBle = false;

  @override
  void dispose() {
    _codeController.dispose();
    _ssidController.dispose();
    _passwordController.dispose();
    _labelController.dispose();
    _scannerController.dispose();
    super.dispose();
  }

  Future<void> _parsePayload([String? scannedValue]) async {
    if (_parsing) {
      return;
    }
    final code = (scannedValue ?? _codeController.text).trim();
    if (code.isEmpty) {
      _showMessage('Enter a QR or manual setup code.');
      return;
    }
    setState(() => _parsing = true);
    try {
      final payload = await OnboardingPayloadParser().parse(code);
      if (_scanning) {
        try {
          await _scannerController.stop();
        } catch (_) {
          // Parsing still succeeds if the camera controller already stopped.
        }
      }
      if (!mounted) {
        return;
      }
      setState(() {
        _codeController.text = code;
        _payload = payload;
        _scanning = false;
      });
    } catch (error) {
      if (mounted) {
        setState(() => _payload = null);
        _showMessage('Payload parsing failed: $error');
      }
    } finally {
      if (mounted) {
        setState(() => _parsing = false);
      }
    }
  }

  Future<void> _startCommissioning() async {
    final payload = _payload;
    if (payload == null) {
      _showMessage('Parse a setup payload first.');
      return;
    }
    final ssid = _ssidController.text.trim();
    final password = _passwordController.text;
    if (ssid.isEmpty || password.isEmpty) {
      _showMessage('SSID and Wi-Fi password are required.');
      return;
    }
    final controller = ExampleScope.of(context);
    final result = await controller.commission(
      payload: payload,
      onboardingPayload: _codeController.text.trim(),
      ssid: ssid,
      password: password,
      deviceLabel: _labelController.text,
      useAndroidBle: Platform.isAndroid && _useAndroidBle,
    );
    if (!mounted) {
      return;
    }
    if (!result.success) {
      _showMessage(result.summary);
    }
  }

  void _showMessage(String message) {
    ScaffoldMessenger.of(context)
      ..hideCurrentSnackBar()
      ..showSnackBar(SnackBar(content: Text(message)));
  }

  @override
  Widget build(BuildContext context) {
    final controller = ExampleScope.of(context);
    return AnimatedBuilder(
      animation: controller,
      builder: (context, _) {
        final busy = controller.operationBusy;
        return Scaffold(
          appBar: AppBar(
            title: const Text('Commission device'),
            actions: const [LogButton(), SizedBox(width: 8)],
          ),
          body: ListView(
            padding: const EdgeInsets.fromLTRB(16, 8, 16, 32),
            children: [
              _PayloadCard(
                codeController: _codeController,
                scannerController: _scannerController,
                scanning: _scanning,
                parsing: _parsing,
                payload: _payload,
                onToggleScanner: (value) {
                  setState(() => _scanning = value);
                },
                onScanned: _parsePayload,
                onParse: _parsePayload,
                busy: busy,
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Controller identity',
                api: 'newControllerIfNotExist',
                subtitle:
                    'The example reuses one persisted demo fabric identity.',
                children: [
                  const InfoRow(
                    'Storage',
                    'SharedPreferences (demo only; not a secure keystore)',
                  ),
                  InfoRow(
                    'State',
                    controller.identity == null ? 'Loading' : 'Identity ready',
                  ),
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Network credentials',
                api: 'NetworkCredentials.wifi',
                subtitle:
                    'This build exposes password-protected Wi-Fi commissioning only.',
                children: [
                  TextField(
                    controller: _ssidController,
                    textInputAction: TextInputAction.next,
                    decoration: const InputDecoration(
                      labelText: 'Wi-Fi SSID',
                      prefixIcon: Icon(Icons.wifi),
                    ),
                  ),
                  const SizedBox(height: 12),
                  TextField(
                    controller: _passwordController,
                    obscureText: true,
                    enableSuggestions: false,
                    autocorrect: false,
                    decoration: const InputDecoration(
                      labelText: 'Wi-Fi password',
                      prefixIcon: Icon(Icons.password),
                    ),
                  ),
                  const SizedBox(height: 12),
                  TextField(
                    controller: _labelController,
                    decoration: const InputDecoration(
                      labelText: 'Device label',
                      prefixIcon: Icon(Icons.label_outline),
                    ),
                  ),
                ],
              ),
              if (Platform.isAndroid) ...[
                const SizedBox(height: 14),
                SectionCard(
                  title: 'Transport override',
                  api: 'BlePlatformDelegate',
                  subtitle: 'SDK-managed discovery is the default path.',
                  children: [
                    SwitchListTile.adaptive(
                      contentPadding: EdgeInsets.zero,
                      value: _useAndroidBle,
                      onChanged: busy
                          ? null
                          : (value) => setState(() => _useAndroidBle = value),
                      title: const Text('Use manual Android BLE / GATT'),
                      subtitle: const Text(
                        'Advanced path: scans and connects with flutter_blue_plus before pairDevice.',
                      ),
                    ),
                  ],
                ),
              ],
              const SizedBox(height: 18),
              BusyActionButton(
                label: busy
                    ? (controller.commissioningStage ?? 'Commissioning')
                    : 'Start commissioning',
                icon: Icons.play_arrow,
                busy: busy,
                onPressed: _payload == null ? null : _startCommissioning,
              ),
              if (busy) ...[
                const SizedBox(height: 14),
                LinearProgressIndicator(
                  borderRadius: BorderRadius.circular(99),
                ),
                const SizedBox(height: 8),
                Text(
                  controller.commissioningStage ?? 'Working…',
                  textAlign: TextAlign.center,
                  style: Theme.of(context).textTheme.bodySmall,
                ),
              ],
              const SizedBox(height: 14),
              OperationResultCard(result: controller.lastResult),
              if (controller.lastResult?.success == true) ...[
                const SizedBox(height: 14),
                FilledButton.tonalIcon(
                  onPressed: () => Navigator.of(context).pushReplacement(
                    MaterialPageRoute<void>(builder: (_) => const DevicePage()),
                  ),
                  icon: const Icon(Icons.developer_board_outlined),
                  label: const Text('Open device workspace'),
                ),
              ],
            ],
          ),
        );
      },
    );
  }
}

class _PayloadCard extends StatelessWidget {
  const _PayloadCard({
    required this.codeController,
    required this.scannerController,
    required this.scanning,
    required this.parsing,
    required this.payload,
    required this.onToggleScanner,
    required this.onScanned,
    required this.onParse,
    required this.busy,
  });

  final TextEditingController codeController;
  final MobileScannerController scannerController;
  final bool scanning;
  final bool parsing;
  final OnboardingPayload? payload;
  final ValueChanged<bool> onToggleScanner;
  final Future<void> Function(String value) onScanned;
  final Future<void> Function() onParse;
  final bool busy;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    return SectionCard(
      title: 'Onboarding payload',
      api: 'OnboardingPayloadParser.parse',
      subtitle:
          'Scan a QR code or enter the code manually. The value is never logged.',
      children: [
        if (scanning)
          ClipRRect(
            borderRadius: BorderRadius.circular(16),
            child: SizedBox(
              height: 240,
              child: MobileScanner(
                controller: scannerController,
                onDetect: (capture) {
                  final value = capture.barcodes.firstOrNull?.rawValue;
                  if (value != null && value.isNotEmpty) {
                    onScanned(value);
                  }
                },
              ),
            ),
          ),
        if (scanning) const SizedBox(height: 12),
        TextField(
          controller: codeController,
          obscureText: true,
          enableSuggestions: false,
          autocorrect: false,
          decoration: InputDecoration(
            labelText: 'QR or manual setup code',
            prefixIcon: const Icon(Icons.qr_code_2),
            suffixIcon: IconButton(
              tooltip: scanning ? 'Stop scanner' : 'Scan QR',
              onPressed: busy ? null : () => onToggleScanner(!scanning),
              icon: Icon(
                scanning ? Icons.camera_alt : Icons.camera_alt_outlined,
              ),
            ),
          ),
        ),
        const SizedBox(height: 10),
        Row(
          children: [
            Expanded(
              child: FilledButton.tonalIcon(
                onPressed: busy || parsing ? null : onParse,
                icon: parsing
                    ? const SizedBox(
                        width: 16,
                        height: 16,
                        child: CircularProgressIndicator(strokeWidth: 2),
                      )
                    : const Icon(Icons.manage_search),
                label: const Text('Parse payload'),
              ),
            ),
          ],
        ),
        if (payload != null) ...[
          const SizedBox(height: 14),
          Container(
            padding: const EdgeInsets.all(14),
            decoration: BoxDecoration(
              color: colors.surfaceContainerLow,
              borderRadius: BorderRadius.circular(14),
            ),
            child: Column(
              children: [
                InfoRow('Vendor ID', formatId(payload!.vendorId)),
                InfoRow('Product ID', formatId(payload!.productId)),
                InfoRow('Discriminator', formatId(payload!.discriminator)),
                InfoRow(
                  'Discovery',
                  payload!.discoveryCapabilities
                      .map((capability) => capability.name)
                      .join(', '),
                ),
                InfoRow(
                  'Commissioning flow',
                  payload!.commissioningFlow.toString(),
                ),
              ],
            ),
          ),
        ],
      ],
    );
  }
}
