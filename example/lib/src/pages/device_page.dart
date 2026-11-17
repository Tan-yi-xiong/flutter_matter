import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';

import '../app.dart';
import '../models.dart';
import '../widgets.dart';
import 'advanced_page.dart';
import 'api_console_page.dart';

class DevicePage extends StatefulWidget {
  const DevicePage({super.key});

  @override
  State<DevicePage> createState() => _DevicePageState();
}

class _DevicePageState extends State<DevicePage> {
  final Map<String, OperationResult?> _results = {};
  final _nodeLabelController = TextEditingController();
  final _durationController = TextEditingController(text: '180');
  final _discriminatorController = TextEditingController(text: '3850');
  final _setupPinController = TextEditingController(text: '20202021');

  SubscriptionSession? _subscription;
  String? _onOffState;
  CommissioningWindowResult? _commissioningWindow;

  @override
  void dispose() {
    final subscription = _subscription;
    if (subscription != null) {
      unawaited(subscription.cancel().catchError((_) => false));
    }
    _nodeLabelController.dispose();
    _durationController.dispose();
    _discriminatorController.dispose();
    _setupPinController.dispose();
    super.dispose();
  }

  Future<void> _run(
    String key,
    String apiName,
    String title,
    Future<OperationResult> Function(ChipDeviceController controller) action,
  ) async {
    final session = ExampleScope.of(context);
    final device = session.activeDevice;
    if (device == null) {
      return;
    }
    final controller = await session.ensureController();
    final result = await session.runOperation(
      apiName: apiName,
      title: title,
      action: () => action(controller),
    );
    if (mounted) {
      setState(() => _results[key] = result);
    }
  }

  Future<OperationResult> _connectDevice(
    MatterSessionController session,
  ) async {
    final result = await session.connect();
    if (mounted) {
      setState(() => _results['connection'] = result);
    }
    return result;
  }

  Future<OperationResult> _disconnectDevice(
    MatterSessionController session,
  ) async {
    await _cancelSubscription();
    final result = await session.disconnect();
    if (mounted) {
      setState(() {
        _results['connection'] = result;
        _onOffState = null;
      });
    }
    return result;
  }

  Future<void> _cancelSubscription() async {
    final subscription = _subscription;
    _subscription = null;
    if (subscription != null) {
      await subscription.cancel().catchError((_) => false);
    }
  }

  Future<OperationResult> _readBasicInformation(
    ChipDeviceController controller,
  ) async {
    final session = ExampleScope.of(context);
    final device = session.activeDevice!;
    final helper = BasicInformationCluster(
      controller: controller,
      connContext: session.connectionContext,
      nodeId: device.nodeId,
    );
    final vendorId = await helper.readVendorIDAttribute();
    final productId = await helper.readProductIDAttribute();
    final softwareVersion = await helper.readSoftwareVersionAttribute();
    final hardwareVersion = await helper.readHardwareVersionStringAttribute();
    return OperationResult(
      success: true,
      summary: 'Basic Information loaded.',
      detail: [
        'Vendor ID: ${formatId(vendorId)}',
        'Product ID: ${formatId(productId)}',
        'Software version: $softwareVersion',
        'Hardware version: $hardwareVersion',
      ].join('\n'),
    );
  }

  Future<OperationResult> _readDescriptor(
    ChipDeviceController controller,
  ) async {
    final session = ExampleScope.of(context);
    final device = session.activeDevice!;
    final helper = DescriptorCluster(
      controller: controller,
      connContext: session.connectionContext,
      endpointId: 1,
      nodeId: device.nodeId,
    );
    final deviceTypes = await helper.readDeviceTypeListAttribute();
    final servers = await helper.readServerListAttribute();
    final parts = await helper.readPartsListAttribute();
    return OperationResult(
      success: true,
      summary: 'Descriptor endpoint 1 loaded.',
      detail: [
        'Device types: ${deviceTypes.map(formatId).join(', ')}',
        'Server clusters: ${servers.map(formatId).join(', ')}',
        'Parts: ${parts.map(formatId).join(', ')}',
      ].join('\n'),
    );
  }

  Future<OperationResult> _invokeOnOff(
    ChipDeviceController controller,
    int command,
    String label,
  ) async {
    final session = ExampleScope.of(context);
    final writer = TlvWriter()
      ..startStructure(AnonymousTag.instance)
      ..endStructure();
    final reply = await session.api.invoke(
      controller: controller,
      nodeId: session.activeDevice!.nodeId,
      context: session.connectionContext,
      element: InvokeElement.create(
        1,
        0x0006,
        command,
        writer.getEncoded(),
        null,
      ),
    );
    return OperationResult(
      success: reply.successCode == 0,
      summary: reply.successCode == 0
          ? '$label command accepted.'
          : '$label returned status ${reply.successCode}.',
      detail: 'Cluster 0x0006 • Command ${formatId(command)}',
    );
  }

  Future<OperationResult> _startSubscription(
    ChipDeviceController controller,
  ) async {
    final session = ExampleScope.of(context);
    await _cancelSubscription();
    final subscription = await session.api.subscribe(
      controller: controller,
      nodeId: session.activeDevice!.nodeId,
      context: session.connectionContext,
      attributePaths: [
        ChipAttributePath(
          endpointId: ChipPathId.forId(1),
          clusterId: ChipPathId.forId(0x0006),
          attributeId: ChipPathId.forId(0),
        ),
      ],
    );
    _subscription = subscription;
    subscription.updates.listen((update) {
      final state = update.nodeState;
      if (!mounted || state == null) {
        return;
      }
      final tlv = state.endpoints[1]?.clusters[0x0006]?.attributes[0]?.tlv;
      if (tlv == null) {
        return;
      }
      try {
        final value = TlvReader(tlv).getBool(AnonymousTag.instance);
        setState(() => _onOffState = value ? 'On' : 'Off');
      } catch (_) {
        // A later report can still provide a decodable OnOff value.
      }
    });
    return OperationResult(
      success: true,
      summary: 'Subscription established.',
      detail: 'Subscription ID: ${subscription.id}',
    );
  }

  Future<OperationResult> _cancelSubscriptionResult(
    ChipDeviceController controller,
  ) async {
    final subscription = _subscription;
    if (subscription == null) {
      return OperationResult.failure('No active subscription.');
    }
    _subscription = null;
    final success = await subscription.cancel();
    if (mounted) {
      setState(() => _onOffState = null);
    }
    return OperationResult(
      success: success,
      summary: success
          ? 'Subscription cancelled.'
          : 'The subscription cancellation was rejected.',
    );
  }

  Future<OperationResult> _readNodeLabel(
    ChipDeviceController controller,
  ) async {
    final session = ExampleScope.of(context);
    final state = await session.api.read(
      controller: controller,
      nodeId: session.activeDevice!.nodeId,
      context: session.connectionContext,
      attributePaths: [
        ChipAttributePath(
          endpointId: ChipPathId.forId(0),
          clusterId: ChipPathId.forId(0x0028),
          attributeId: ChipPathId.forId(0x0005),
        ),
      ],
    );
    final tlv = state.endpoints[0]?.clusters[0x0028]?.attributes[0x0005]?.tlv;
    if (tlv == null) {
      throw StateError('NodeLabel was not present in the response.');
    }
    final value = TlvReader(tlv).getString(AnonymousTag.instance);
    _nodeLabelController.text = value;
    return OperationResult(
      success: true,
      summary: 'NodeLabel read.',
      detail: 'Value: $value',
    );
  }

  Future<OperationResult> _writeNodeLabel(
    ChipDeviceController controller,
  ) async {
    final session = ExampleScope.of(context);
    final value = _nodeLabelController.text;
    if (value.trim().isEmpty) {
      return OperationResult.failure('Enter a NodeLabel value first.');
    }
    final status = await session.api.write(
      controller: controller,
      nodeId: session.activeDevice!.nodeId,
      context: session.connectionContext,
      attributes: [
        AttributeWriteRequest(
          endpointId: ChipPathId.forId(0),
          clusterId: ChipPathId.forId(0x0028),
          attributeId: ChipPathId.forId(0x0005),
          dataVersion: 0,
          tlv: TlvWriter().putString(AnonymousTag.instance, value).getEncoded(),
        ),
      ],
    );
    return OperationResult(
      success: status?.status == null || status?.status == 0,
      summary: status == null
          ? 'NodeLabel write completed.'
          : 'NodeLabel write returned status ${status.status}.',
      detail: status?.clusterStatus == null
          ? null
          : 'Cluster status: ${status!.clusterStatus}',
    );
  }

  Future<OperationResult> _openCommissioningWindow(
    ChipDeviceController controller,
  ) async {
    final session = ExampleScope.of(context);
    final connectContext = session.connectionContext;
    if (connectContext == null) {
      return OperationResult.failure('Connect the device first.');
    }
    final duration = int.tryParse(_durationController.text);
    final discriminator = int.tryParse(_discriminatorController.text);
    final setupPin = int.tryParse(_setupPinController.text);
    if (duration == null || duration <= 0) {
      return OperationResult.failure('Duration must be a positive integer.');
    }
    if (discriminator == null || discriminator < 0 || discriminator > 0xFFF) {
      return OperationResult.failure('Discriminator must be 0..4095.');
    }
    if (setupPin == null || setupPin < 1 || setupPin > 99999998) {
      return OperationResult.failure('Setup PIN is invalid.');
    }
    final result = await session.api.openCommissioningWindow(
      controller: controller,
      nodeId: session.activeDevice!.nodeId,
      context: connectContext,
      durationSeconds: duration,
      discriminator: discriminator,
      setupPin: setupPin,
    );
    if (mounted) {
      setState(() => _commissioningWindow = result);
    }
    return const OperationResult(
      success: true,
      summary: 'Commissioning window opened.',
      detail: 'The pairing codes are shown only in this screen.',
    );
  }

  Future<OperationResult> _readFabrics(ChipDeviceController controller) async {
    final session = ExampleScope.of(context);
    final snapshot = await session.api.readFabrics(
      controller: controller,
      nodeId: session.activeDevice!.nodeId,
      context: session.connectionContext,
    );
    return OperationResult(
      success: true,
      summary: 'Fabric Table loaded.',
      detail: [
        if (snapshot.currentFabricIndex != null)
          'Controller fabric index: ${snapshot.currentFabricIndex}',
        'Raw Fabrics TLV: ${formatBytes(snapshot.rawTlv)}',
      ].join('\n'),
    );
  }

  Future<void> _removeFabric(ChipDeviceController controller) async {
    final session = ExampleScope.of(context);
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Remove current fabric?'),
        content: const Text(
          'This invokes OperationalCredentials.RemoveFabric for the '
          'controller fabric index. The local device record is removed only '
          'after the command succeeds.',
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context, false),
            child: const Text('Cancel'),
          ),
          FilledButton(
            onPressed: () => Navigator.pop(context, true),
            child: const Text('Remove fabric'),
          ),
        ],
      ),
    );
    if (confirmed != true || !mounted) {
      return;
    }
    final device = session.activeDevice;
    if (device == null) {
      return;
    }
    await _run('fabric', 'invoke RemoveFabric', 'Remove fabric', (
      controller,
    ) async {
      final fabricIndex = await controller.getFabricIndex();
      if (fabricIndex == null) {
        return OperationResult.failure(
          'The controller did not report a fabric index.',
        );
      }
      final reply = await session.api.removeFabric(
        controller: controller,
        nodeId: device.nodeId,
        fabricIndex: fabricIndex,
        context: session.connectionContext,
      );
      if (reply.successCode != 0) {
        return OperationResult(
          success: false,
          summary: 'RemoveFabric returned status ${reply.successCode}.',
        );
      }
      await session.removeLocalDevice(device);
      if (mounted) {
        Navigator.of(context).pop();
      }
      return const OperationResult(
        success: true,
        summary: 'Current fabric removed and local record deleted.',
      );
    });
  }

  @override
  Widget build(BuildContext context) {
    final session = ExampleScope.of(context);
    final device = session.activeDevice;
    return AnimatedBuilder(
      animation: session,
      builder: (context, _) {
        if (device == null) {
          return const Scaffold(
            body: Center(child: Text('No device selected.')),
          );
        }
        final busy = session.operationBusy;
        final enabled = session.isConnected && !busy;
        return Scaffold(
          appBar: AppBar(
            title: Text(device.displayName),
            actions: [
              const LogButton(),
              PopupMenuButton<String>(
                onSelected: (value) async {
                  if (value == 'console') {
                    await Navigator.of(context).push(
                      MaterialPageRoute<void>(
                        builder: (_) => const ApiConsolePage(),
                      ),
                    );
                  } else if (value == 'advanced') {
                    await Navigator.of(context).push(
                      MaterialPageRoute<void>(
                        builder: (_) => const AdvancedPage(),
                      ),
                    );
                  } else if (value == 'forget') {
                    await session.removeLocalDevice(device);
                    if (context.mounted) {
                      Navigator.of(context).pop();
                    }
                  }
                },
                itemBuilder: (context) => const [
                  PopupMenuItem(
                    value: 'console',
                    child: Text('Open API Console'),
                  ),
                  PopupMenuItem(
                    value: 'advanced',
                    child: Text('Open Advanced'),
                  ),
                  PopupMenuDivider(),
                  PopupMenuItem(
                    value: 'forget',
                    child: Text('Forget local record'),
                  ),
                ],
              ),
              const SizedBox(width: 6),
            ],
          ),
          body: ListView(
            padding: const EdgeInsets.fromLTRB(16, 8, 16, 32),
            children: [
              _ConnectionCard(
                session: session,
                result: _results['connection'],
                onConnect: () => _connectDevice(session),
                onDisconnect: () => _disconnectDevice(session),
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Device overview',
                api: 'BasicInformationCluster / DescriptorCluster',
                subtitle:
                    'Read vendor, product, software, descriptor and parts data.',
                children: [
                  InfoRow('Node ID', formatId(device.nodeId)),
                  InfoRow(
                    'Vendor',
                    device.vendorId == null
                        ? 'Unknown'
                        : formatId(device.vendorId!),
                  ),
                  InfoRow(
                    'Product',
                    device.productId == null
                        ? 'Unknown'
                        : formatId(device.productId!),
                  ),
                  const SizedBox(height: 12),
                  Wrap(
                    spacing: 10,
                    runSpacing: 10,
                    children: [
                      FilledButton.tonalIcon(
                        onPressed: enabled
                            ? () => _run(
                                'basic',
                                'BasicInformationCluster',
                                'Read Basic Information',
                                _readBasicInformation,
                              )
                            : null,
                        icon: const Icon(Icons.info_outline),
                        label: const Text('Read Basic Information'),
                      ),
                      FilledButton.tonalIcon(
                        onPressed: enabled
                            ? () => _run(
                                'descriptor',
                                'DescriptorCluster',
                                'Read Descriptor',
                                _readDescriptor,
                              )
                            : null,
                        icon: const Icon(Icons.account_tree_outlined),
                        label: const Text('Read Descriptor'),
                      ),
                    ],
                  ),
                  const SizedBox(height: 12),
                  OperationResultCard(result: _results['basic']),
                  if (_results['basic'] != null &&
                      _results['descriptor'] != null)
                    const SizedBox(height: 10),
                  OperationResultCard(result: _results['descriptor']),
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'On/Off',
                api: 'invoke / subscribe',
                subtitle:
                    'Endpoint 0x01, OnOff cluster 0x0006, attribute 0x0000.',
                trailing: ConnectionBadge(phase: session.connectionPhase),
                children: [
                  if (_onOffState != null)
                    Padding(
                      padding: const EdgeInsets.only(bottom: 12),
                      child: InfoRow('Reported state', _onOffState!),
                    ),
                  Wrap(
                    spacing: 10,
                    runSpacing: 10,
                    children: [
                      FilledButton(
                        onPressed: enabled
                            ? () => _run(
                                'onoff',
                                'invoke Off',
                                'Send Off',
                                (controller) =>
                                    _invokeOnOff(controller, 0, 'Off'),
                              )
                            : null,
                        child: const Text('Off'),
                      ),
                      FilledButton(
                        onPressed: enabled
                            ? () => _run(
                                'onoff',
                                'invoke On',
                                'Send On',
                                (controller) =>
                                    _invokeOnOff(controller, 1, 'On'),
                              )
                            : null,
                        child: const Text('On'),
                      ),
                      FilledButton.tonal(
                        onPressed: enabled
                            ? () => _run(
                                'onoff',
                                'invoke Toggle',
                                'Send Toggle',
                                (controller) =>
                                    _invokeOnOff(controller, 2, 'Toggle'),
                              )
                            : null,
                        child: const Text('Toggle'),
                      ),
                      OutlinedButton.icon(
                        onPressed: enabled
                            ? () => _run(
                                'onoff',
                                'subscribe OnOff',
                                _subscription == null
                                    ? 'Start subscription'
                                    : 'Cancel subscription',
                                _subscription == null
                                    ? _startSubscription
                                    : _cancelSubscriptionResult,
                              )
                            : null,
                        icon: Icon(
                          _subscription == null
                              ? Icons.notifications_active_outlined
                              : Icons.notifications_off_outlined,
                        ),
                        label: Text(
                          _subscription == null ? 'Subscribe' : 'Unsubscribe',
                        ),
                      ),
                    ],
                  ),
                  const SizedBox(height: 12),
                  OperationResultCard(result: _results['onoff']),
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'NodeLabel',
                api: 'read / write',
                subtitle: 'Basic Information cluster 0x0028, attribute 0x0005.',
                children: [
                  TextField(
                    controller: _nodeLabelController,
                    decoration: const InputDecoration(
                      labelText: 'NodeLabel value',
                      prefixIcon: Icon(Icons.edit_outlined),
                    ),
                  ),
                  const SizedBox(height: 12),
                  Wrap(
                    spacing: 10,
                    runSpacing: 10,
                    children: [
                      FilledButton.tonalIcon(
                        onPressed: enabled
                            ? () => _run(
                                'nodeLabel',
                                'read NodeLabel',
                                'Read NodeLabel',
                                _readNodeLabel,
                              )
                            : null,
                        icon: const Icon(Icons.download_outlined),
                        label: const Text('Read'),
                      ),
                      FilledButton.icon(
                        onPressed: enabled
                            ? () => _run(
                                'nodeLabel',
                                'write NodeLabel',
                                'Write NodeLabel',
                                _writeNodeLabel,
                              )
                            : null,
                        icon: const Icon(Icons.upload_outlined),
                        label: const Text('Write'),
                      ),
                    ],
                  ),
                  const SizedBox(height: 12),
                  OperationResultCard(result: _results['nodeLabel']),
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Commissioning window',
                api: 'openPairingWindowWithPIN',
                subtitle:
                    'Invokes Basic Commissioning command 0x02, then opens the window.',
                children: [
                  Row(
                    children: [
                      Expanded(
                        child: TextField(
                          controller: _durationController,
                          keyboardType: TextInputType.number,
                          decoration: const InputDecoration(
                            labelText: 'Duration (s)',
                          ),
                        ),
                      ),
                      const SizedBox(width: 10),
                      Expanded(
                        child: TextField(
                          controller: _discriminatorController,
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
                    keyboardType: TextInputType.number,
                    obscureText: true,
                    decoration: const InputDecoration(
                      labelText: 'Setup PIN',
                      prefixIcon: Icon(Icons.password),
                    ),
                  ),
                  const SizedBox(height: 12),
                  FilledButton.tonalIcon(
                    onPressed: enabled
                        ? () => _run(
                            'ocw',
                            'openPairingWindowWithPIN',
                            'Open commissioning window',
                            _openCommissioningWindow,
                          )
                        : null,
                    icon: const Icon(Icons.open_in_new),
                    label: const Text('Open window'),
                  ),
                  const SizedBox(height: 12),
                  OperationResultCard(result: _results['ocw']),
                  if (_commissioningWindow != null) ...[
                    const SizedBox(height: 12),
                    _PairingCodes(result: _commissioningWindow!),
                  ],
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Fabric table',
                api: 'read / getFabricIndex / invoke',
                subtitle:
                    'Inspect the OperationalCredentials Fabric Table and remove only the current controller fabric.',
                children: [
                  Wrap(
                    spacing: 10,
                    runSpacing: 10,
                    children: [
                      FilledButton.tonalIcon(
                        onPressed: enabled
                            ? () => _run(
                                'fabric',
                                'read Fabrics',
                                'Read Fabric Table',
                                _readFabrics,
                              )
                            : null,
                        icon: const Icon(Icons.table_rows_outlined),
                        label: const Text('Read Fabric Table'),
                      ),
                      FilledButton.icon(
                        style: FilledButton.styleFrom(
                          backgroundColor: Theme.of(context).colorScheme.error,
                          foregroundColor: Theme.of(
                            context,
                          ).colorScheme.onError,
                        ),
                        onPressed: enabled
                            ? () async {
                                final controller = await session
                                    .ensureController();
                                await _removeFabric(controller);
                              }
                            : null,
                        icon: const Icon(Icons.link_off),
                        label: const Text('Remove current Fabric'),
                      ),
                    ],
                  ),
                  const SizedBox(height: 12),
                  OperationResultCard(result: _results['fabric']),
                ],
              ),
            ],
          ),
        );
      },
    );
  }
}

class _ConnectionCard extends StatelessWidget {
  const _ConnectionCard({
    required this.session,
    required this.result,
    required this.onConnect,
    required this.onDisconnect,
  });

  final MatterSessionController session;
  final OperationResult? result;
  final Future<OperationResult> Function() onConnect;
  final Future<OperationResult> Function() onDisconnect;

  @override
  Widget build(BuildContext context) {
    final connecting = session.connectionPhase == ConnectionPhase.connecting;
    final connected = session.isConnected;
    return SectionCard(
      title: 'Connection',
      api: 'connectedDevice / releaseConnectContext',
      subtitle:
          'CASE connection and connect-context ownership are shown explicitly.',
      trailing: ConnectionBadge(phase: session.connectionPhase),
      children: [
        Row(
          children: [
            Expanded(
              child: OutlinedButton.icon(
                onPressed: connecting ? null : onConnect,
                icon: connecting
                    ? const SizedBox(
                        width: 16,
                        height: 16,
                        child: CircularProgressIndicator(strokeWidth: 2),
                      )
                    : const Icon(Icons.link),
                label: Text(connected ? 'Reconnect' : 'Connect'),
              ),
            ),
            const SizedBox(width: 10),
            Expanded(
              child: OutlinedButton.icon(
                onPressed: connected ? onDisconnect : null,
                icon: const Icon(Icons.link_off),
                label: const Text('Disconnect'),
              ),
            ),
          ],
        ),
        const SizedBox(height: 12),
        OperationResultCard(result: result),
      ],
    );
  }
}

class _PairingCodes extends StatelessWidget {
  const _PairingCodes({required this.result});

  final CommissioningWindowResult result;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    return Container(
      padding: const EdgeInsets.all(14),
      decoration: BoxDecoration(
        color: colors.tertiaryContainer.withValues(alpha: 0.45),
        borderRadius: BorderRadius.circular(14),
        border: Border.all(color: colors.tertiary),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text('Pairing codes', style: Theme.of(context).textTheme.titleSmall),
          const SizedBox(height: 8),
          SelectableText('Manual: ${result.manualPairingCode}'),
          const SizedBox(height: 4),
          SelectableText('QR: ${result.qrCode}'),
        ],
      ),
    );
  }
}
