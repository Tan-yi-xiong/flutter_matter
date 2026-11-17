import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_google_home/flutter_matter_google_home.dart';
import 'package:mobile_scanner/mobile_scanner.dart';
import 'package:permission_handler/permission_handler.dart';

import '../app.dart';
import '../models.dart';
import '../widgets.dart';
import 'device_page.dart';

class CommissioningPage extends StatefulWidget {
  const CommissioningPage({super.key});

  @override
  State<CommissioningPage> createState() => _CommissioningPageState();
}

enum _CommissioningPath { localStack, googleHome }

class _CommissioningPageState extends State<CommissioningPage> {
  _CommissioningPath _path = _CommissioningPath.localStack;
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
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) {
      ExampleScope.of(context).resetCommissioningState();
      ExampleScope.of(context).checkGoogleAvailability();
      _loadSavedWifi();
    });
  }

  @override
  void dispose() {
    _codeController.dispose();
    _ssidController.dispose();
    _passwordController.dispose();
    _labelController.dispose();
    _scannerController.dispose();
    super.dispose();
  }

  Future<void> _loadSavedWifi() async {
    final saved = await ExampleScope.of(context).loadWifiCredentials();
    if (!mounted || saved == null) {
      return;
    }
    setState(() {
      _ssidController.text = saved.ssid;
      _passwordController.text = saved.password;
    });
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
        _useAndroidBle =
            Platform.isAndroid &&
            payload.discoveryCapabilities.contains(DiscoveryCapability.ble);
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

  Future<bool> _ensureAndroidBlePermissions() async {
    if (!Platform.isAndroid) {
      return true;
    }
    final statuses = await [
      Permission.bluetoothScan,
      Permission.bluetoothConnect,
    ].request();
    final missing = statuses.entries
        .where((entry) => !entry.value.isGranted && !entry.value.isLimited)
        .map((entry) => entry.key.toString())
        .toList();
    if (missing.isNotEmpty) {
      if (mounted) {
        _showMessage('Bluetooth permissions are required for commissioning.');
      }
      return false;
    }
    return true;
  }

  Future<void> _startCommissioning() async {
    if (Platform.isAndroid && _path == _CommissioningPath.googleHome) {
      await _startGoogleCommissioning();
      return;
    }
    final code = _codeController.text.trim();
    if (code.isEmpty) {
      _showMessage('Enter a QR or manual setup code.');
      return;
    }
    final payload = _payload;
    final ssid = _ssidController.text.trim();
    final password = _passwordController.text;
    if (ssid.isEmpty || password.isEmpty) {
      _showMessage('SSID and Wi-Fi password are required.');
      return;
    }
    final controller = ExampleScope.of(context);
    if (!await _ensureAndroidBlePermissions()) {
      return;
    }
    await controller.saveWifiCredentials(ssid, password);
    final result = await controller.commission(
      payload: payload,
      onboardingPayload: code,
      ssid: ssid,
      password: password,
      deviceLabel: _labelController.text,
      // Manual BLE needs a parsed payload; otherwise the SDK drives discovery
      // straight from the raw onboarding code.
      useAndroidBle: payload != null && Platform.isAndroid && _useAndroidBle,
    );
    if (!mounted) {
      return;
    }
    if (!result.success) {
      _showMessage(result.summary);
    }
  }

  Future<void> _startGoogleCommissioning() async {
    final code = _codeController.text.trim();
    if (code.isEmpty) {
      _showMessage('Enter a QR or manual setup code.');
      return;
    }
    final controller = ExampleScope.of(context);
    final result = await controller.commissionGoogleDualFabric(
      payload: _payload,
      onboardingPayload: code,
    );
    if (!mounted) {
      return;
    }
    if (!result.success) {
      _showMessage(result.summary);
    }
  }

  Widget _googleCommissioningCard(
    MatterSessionController controller,
    bool busy,
  ) {
    final availability = controller.googleAvailability;
    final checking = controller.googleAvailabilityChecking;
    final ready = availability?.isReady == true;
    final moduleUnavailable =
        availability?.status ==
        GoogleHomeMatterAvailabilityStatus.moduleUnavailable;
    final colors = Theme.of(context).colorScheme;
    return SectionCard(
      title: 'Google Home commissioning',
      api: 'startHandoffSession → pairDeviceWithAddress',
      subtitle:
          'GMS commissions the first fabric, then the example stack adds the second.',
      children: [
        DropdownButtonFormField<GoogleHomeMatterTarget>(
          initialValue: controller.googleTarget,
          decoration: const InputDecoration(
            labelText: 'First fabric target',
            prefixIcon: Icon(Icons.account_balance_outlined),
          ),
          items: [
            for (final target in GoogleHomeMatterTarget.values)
              DropdownMenuItem(
                value: target,
                child: Text(
                  target == GoogleHomeMatterTarget.googleHomeFabric
                      ? 'Google Home fabric'
                      : 'Android local fabric',
                ),
              ),
          ],
          onChanged: busy
              ? null
              : (value) {
                  if (value != null) {
                    controller.setGoogleTarget(value);
                  }
                },
        ),
        const SizedBox(height: 12),
        Container(
          padding: const EdgeInsets.all(14),
          decoration: BoxDecoration(
            color: colors.surfaceContainerLow,
            borderRadius: BorderRadius.circular(14),
          ),
          child: Column(
            children: [
              Row(
                children: [
                  Expanded(
                    child: InfoRow(
                      'Availability',
                      checking
                          ? 'Checking…'
                          : (availability?.status.wireName ?? 'unknown'),
                    ),
                  ),
                  if (!checking)
                    IconButton(
                      tooltip: 'Re-check availability',
                      onPressed: busy
                          ? null
                          : controller.checkGoogleAvailability,
                      icon: const Icon(Icons.refresh),
                    ),
                ],
              ),
              if ((availability?.playServicesVersion) != null)
                InfoRow('Play Services', availability!.playServicesVersion!),
              if (!ready &&
                  !checking &&
                  (availability?.message.isNotEmpty ?? false))
                Padding(
                  padding: const EdgeInsets.only(top: 6),
                  child: Text(
                    availability!.message,
                    style: Theme.of(context).textTheme.bodySmall,
                  ),
                ),
            ],
          ),
        ),
        if (moduleUnavailable) ...[
          const SizedBox(height: 12),
          FilledButton.tonalIcon(
            onPressed: busy ? null : controller.requestGoogleModuleInstall,
            icon: const Icon(Icons.download_outlined),
            label: const Text('Prepare Home module'),
          ),
        ],
      ],
    );
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
        final isGooglePath =
            Platform.isAndroid && _path == _CommissioningPath.googleHome;
        return PopScope(
          canPop: !busy,
          onPopInvokedWithResult: (didPop, _) async {
            if (didPop || !busy) {
              return;
            }
            final navigator = Navigator.of(context);
            await controller.cancelCommissioning();
            if (!mounted || !navigator.canPop()) {
              return;
            }
            navigator.pop();
          },
          child: Scaffold(
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
                if (Platform.isAndroid) ...[
                  const SizedBox(height: 14),
                  SectionCard(
                    title: 'Commissioning path',
                    api: 'pairDevice / startHandoffSession',
                    subtitle:
                        'Google path runs dual-fabric commissioning via GMS.',
                    children: [
                      SegmentedButton<_CommissioningPath>(
                        segments: const [
                          ButtonSegment(
                            value: _CommissioningPath.localStack,
                            label: Text('Example stack'),
                            icon: Icon(Icons.hub_outlined),
                          ),
                          ButtonSegment(
                            value: _CommissioningPath.googleHome,
                            label: Text('Google Home'),
                            icon: Icon(Icons.home_outlined),
                          ),
                        ],
                        selected: {_path},
                        onSelectionChanged: busy
                            ? null
                            : (selection) =>
                                  setState(() => _path = selection.first),
                      ),
                    ],
                  ),
                ],
                if (isGooglePath) ...[
                  const SizedBox(height: 14),
                  _googleCommissioningCard(controller, busy),
                ],
                if (!isGooglePath) ...[
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
                        controller.identity == null
                            ? 'Loading'
                            : 'Identity ready',
                      ),
                    ],
                  ),
                ],
                if (!isGooglePath) ...[
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
                ],
                if (!isGooglePath && Platform.isAndroid) ...[
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
                      : (isGooglePath
                            ? 'Start dual-fabric commissioning'
                            : 'Start commissioning'),
                  icon: Icons.play_arrow,
                  busy: busy,
                  onPressed:
                      isGooglePath &&
                          (controller.googleAvailability?.isReady ?? false) ==
                              false
                      ? null
                      : _startCommissioning,
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
