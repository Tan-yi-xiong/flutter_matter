import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';

import '../app.dart';
import '../matter_api_service.dart';
import '../models.dart';
import '../widgets.dart';

enum _ConsoleOperation { invoke, read, write, subscribe }

extension on _ConsoleOperation {
  String get label => switch (this) {
    _ConsoleOperation.invoke => 'invoke',
    _ConsoleOperation.read => 'read',
    _ConsoleOperation.write => 'write',
    _ConsoleOperation.subscribe => 'subscribe',
  };
}

class ApiConsolePage extends StatefulWidget {
  const ApiConsolePage({super.key});

  @override
  State<ApiConsolePage> createState() => _ApiConsolePageState();
}

class _ApiConsolePageState extends State<ApiConsolePage> {
  _ConsoleOperation _operation = _ConsoleOperation.invoke;
  final _endpointController = TextEditingController(text: '1');
  final _clusterController = TextEditingController(text: '0x0006');
  final _attributeController = TextEditingController(text: '0');
  final _commandController = TextEditingController(text: '1');
  final _eventController = TextEditingController();
  final _tlvController = TextEditingController();
  final _dataVersionController = TextEditingController(text: '0');
  final _minIntervalController = TextEditingController(text: '1');
  final _maxIntervalController = TextEditingController(text: '10');
  bool _eventUrgent = false;
  bool _fabricFiltered = false;
  OperationResult? _result;
  SubscriptionSession? _subscription;
  final List<String> _subscriptionReports = [];

  @override
  void dispose() {
    final subscription = _subscription;
    if (subscription != null) {
      unawaited(subscription.cancel().catchError((_) => false));
    }
    _endpointController.dispose();
    _clusterController.dispose();
    _attributeController.dispose();
    _commandController.dispose();
    _eventController.dispose();
    _tlvController.dispose();
    _dataVersionController.dispose();
    _minIntervalController.dispose();
    _maxIntervalController.dispose();
    super.dispose();
  }

  Future<void> _execute() async {
    final session = ExampleScope.of(context);
    if (!session.isConnected) {
      _showMessage('Connect the active device before using the console.');
      return;
    }
    final controller = await session.ensureController();
    final result = await session.runOperation(
      apiName: _operation.label,
      title: 'API Console ${_operation.label}',
      action: () => _perform(session, controller),
    );
    if (mounted) {
      setState(() => _result = result);
    }
  }

  Future<OperationResult> _perform(
    MatterSessionController session,
    ChipDeviceController controller,
  ) async {
    final nodeId = session.activeDevice!.nodeId;
    final endpoint = parsePathId(_endpointController.text);
    final cluster = parsePathId(_clusterController.text);
    switch (_operation) {
      case _ConsoleOperation.invoke:
        final command = parsePathId(_commandController.text);
        final tlv = _tlvController.text.trim().isEmpty
            ? (TlvWriter()
                    ..startStructure(AnonymousTag.instance)
                    ..endStructure())
                  .getEncoded()
            : encodeHex(_tlvController.text);
        final reply = await session.api.invoke(
          controller: controller,
          nodeId: nodeId,
          context: session.connectionContext,
          element: InvokeElement(
            endpointId: endpoint,
            clusterId: cluster,
            commandId: command,
            groupId: 0,
            tlv: tlv,
          ),
        );
        return OperationResult(
          success: reply.successCode == 0,
          summary: 'Invoke response ${reply.successCode}.',
          detail: [
            'Endpoint: ${_endpointController.text}',
            'Cluster: ${_clusterController.text}',
            'Command: ${_commandController.text}',
            'Response TLV: '
                '${formatBytes((reply.element as InvokeElement).tlv)}',
          ].join('\n'),
        );
      case _ConsoleOperation.read:
        final state = await session.api.read(
          controller: controller,
          nodeId: nodeId,
          context: session.connectionContext,
          attributePaths: [_attributePath(endpoint, cluster)],
          eventPaths: _eventPaths(),
          dataVersionFilters: _dataVersionFilters(),
          isFabricFiltered: _fabricFiltered,
        );
        return OperationResult(
          success: true,
          summary: 'Read returned interaction-model data.',
          detail: describeNodeState(state),
        );
      case _ConsoleOperation.write:
        final tlvSource = _tlvController.text.trim();
        if (tlvSource.isEmpty) {
          return OperationResult.failure('Write requires TLV hex.');
        }
        final dataVersion = int.tryParse(_dataVersionController.text) ?? 0;
        final status = await session.api.write(
          controller: controller,
          nodeId: nodeId,
          context: session.connectionContext,
          attributes: [
            AttributeWriteRequest(
              endpointId: endpoint,
              clusterId: cluster,
              attributeId: parsePathId(_attributeController.text),
              dataVersion: dataVersion,
              tlv: encodeHex(tlvSource),
            ),
          ],
        );
        return OperationResult(
          success: status == null || status.status == 0,
          summary: status == null
              ? 'Write completed without a status response.'
              : 'Write status ${status.status}.',
          detail: status?.clusterStatus == null
              ? 'Data version: $dataVersion'
              : 'Cluster status: ${status!.clusterStatus}',
        );
      case _ConsoleOperation.subscribe:
        await _cancelSubscription();
        final subscription = await session.api.subscribe(
          controller: controller,
          nodeId: nodeId,
          context: session.connectionContext,
          attributePaths: [_attributePath(endpoint, cluster)],
          eventPaths: _eventPaths(),
          dataVersionFilters: _dataVersionFilters(),
          minInterval: int.tryParse(_minIntervalController.text) ?? 1,
          maxInterval: int.tryParse(_maxIntervalController.text) ?? 10,
          isFabricFiltered: _fabricFiltered,
        );
        _subscription = subscription;
        subscription.updates.listen((update) {
          if (!mounted) {
            return;
          }
          setState(() {
            if (update.error != null) {
              _subscriptionReports.insert(0, 'Error: ${update.error}');
            } else if (update.nodeState != null) {
              _subscriptionReports.insert(
                0,
                describeNodeState(update.nodeState),
              );
            }
            if (_subscriptionReports.length > 20) {
              _subscriptionReports.removeRange(20, _subscriptionReports.length);
            }
          });
        });
        return OperationResult(
          success: true,
          summary: 'Subscription established.',
          detail: 'Subscription ID: ${subscription.id}',
        );
    }
  }

  ChipAttributePath _attributePath(ChipPathId endpoint, ChipPathId cluster) {
    return ChipAttributePath(
      endpointId: endpoint,
      clusterId: cluster,
      attributeId: parsePathId(
        _attributeController.text,
        allowWildcard:
            _operation == _ConsoleOperation.read ||
            _operation == _ConsoleOperation.subscribe,
      ),
    );
  }

  List<ChipEventPath>? _eventPaths() {
    final eventText = _eventController.text.trim();
    if (eventText.isEmpty) {
      return null;
    }
    return [
      ChipEventPath(
        endpointId: parsePathId(_endpointController.text, allowWildcard: true),
        clusterId: parsePathId(_clusterController.text, allowWildcard: true),
        eventId: parsePathId(eventText, allowWildcard: true),
        isUrgent: _eventUrgent,
      ),
    ];
  }

  List<DataVersionFilter>? _dataVersionFilters() {
    final source = _dataVersionController.text.trim();
    if (source.isEmpty) {
      return null;
    }
    final version = int.tryParse(source);
    if (version == null) {
      throw FormatException('Invalid data version: $source');
    }
    return [
      DataVersionFilter(
        endpointId: parsePathId(_endpointController.text),
        clusterId: parsePathId(_clusterController.text),
        dataVersion: version,
      ),
    ];
  }

  Future<void> _cancelSubscription() async {
    final subscription = _subscription;
    _subscription = null;
    if (subscription != null) {
      await subscription.cancel().catchError((_) => false);
    }
  }

  void _showMessage(String message) {
    ScaffoldMessenger.of(context)
      ..hideCurrentSnackBar()
      ..showSnackBar(SnackBar(content: Text(message)));
  }

  void _applyOnOffPreset() {
    setState(() {
      _operation = _ConsoleOperation.invoke;
      _endpointController.text = '1';
      _clusterController.text = '0x0006';
      _commandController.text = '1';
      _tlvController.clear();
    });
  }

  void _applyNodeLabelPreset() {
    setState(() {
      _operation = _ConsoleOperation.read;
      _endpointController.text = '0';
      _clusterController.text = '0x0028';
      _attributeController.text = '0x0005';
      _eventController.clear();
      _tlvController.clear();
    });
  }

  @override
  Widget build(BuildContext context) {
    final session = ExampleScope.of(context);
    return AnimatedBuilder(
      animation: session,
      builder: (context, _) {
        final enabled = session.isConnected && !session.operationBusy;
        return Scaffold(
          appBar: AppBar(
            title: const Text('API Console'),
            actions: const [LogButton(), SizedBox(width: 8)],
          ),
          body: ListView(
            padding: const EdgeInsets.fromLTRB(16, 8, 16, 32),
            children: [
              SectionCard(
                title: 'Interaction model',
                api: _operation.label,
                subtitle:
                    'Any concrete or wildcard path supported by the public controller API.',
                trailing: ConnectionBadge(phase: session.connectionPhase),
                children: [
                  SingleChildScrollView(
                    scrollDirection: Axis.horizontal,
                    child: SegmentedButton<_ConsoleOperation>(
                      segments: const [
                        ButtonSegment(
                          value: _ConsoleOperation.invoke,
                          icon: Icon(Icons.call_made),
                          label: Text('Invoke'),
                        ),
                        ButtonSegment(
                          value: _ConsoleOperation.read,
                          icon: Icon(Icons.download),
                          label: Text('Read'),
                        ),
                        ButtonSegment(
                          value: _ConsoleOperation.write,
                          icon: Icon(Icons.upload),
                          label: Text('Write'),
                        ),
                        ButtonSegment(
                          value: _ConsoleOperation.subscribe,
                          icon: Icon(Icons.notifications_active_outlined),
                          label: Text('Subscribe'),
                        ),
                      ],
                      selected: {_operation},
                      onSelectionChanged: enabled
                          ? (selection) {
                              setState(() => _operation = selection.first);
                            }
                          : null,
                    ),
                  ),
                  const SizedBox(height: 14),
                  _PathRow(
                    endpointController: _endpointController,
                    clusterController: _clusterController,
                  ),
                  const SizedBox(height: 10),
                  if (_operation == _ConsoleOperation.invoke)
                    TextField(
                      controller: _commandController,
                      decoration: const InputDecoration(
                        labelText: 'Command ID',
                        helperText: 'Decimal or 0x hex',
                      ),
                    )
                  else
                    TextField(
                      controller: _attributeController,
                      decoration: const InputDecoration(
                        labelText: 'Attribute ID',
                        helperText: 'Decimal, 0x hex, or * for read/subscribe',
                      ),
                    ),
                  const SizedBox(height: 10),
                  TextField(
                    controller: _eventController,
                    onChanged: (_) => setState(() {}),
                    decoration: const InputDecoration(
                      labelText: 'Event ID (optional)',
                      helperText:
                          'Adds one event path alongside the attribute path.',
                    ),
                  ),
                  if (_eventController.text.trim().isNotEmpty) ...[
                    const SizedBox(height: 4),
                    SwitchListTile.adaptive(
                      contentPadding: EdgeInsets.zero,
                      value: _eventUrgent,
                      onChanged: enabled
                          ? (value) => setState(() => _eventUrgent = value)
                          : null,
                      title: const Text('Urgent event'),
                    ),
                  ],
                  const SizedBox(height: 10),
                  _PathRow(
                    left: TextField(
                      controller: _minIntervalController,
                      keyboardType: TextInputType.number,
                      decoration: const InputDecoration(
                        labelText: 'Min interval (s)',
                      ),
                    ),
                    right: TextField(
                      controller: _maxIntervalController,
                      keyboardType: TextInputType.number,
                      decoration: const InputDecoration(
                        labelText: 'Max interval (s)',
                      ),
                    ),
                  ),
                  const SizedBox(height: 10),
                  TextField(
                    controller: _dataVersionController,
                    keyboardType: TextInputType.number,
                    decoration: const InputDecoration(
                      labelText: 'Data version / filter',
                      helperText:
                          'For write: dataVersion. For read/subscribe: optional filter.',
                    ),
                  ),
                  SwitchListTile.adaptive(
                    contentPadding: EdgeInsets.zero,
                    value: _fabricFiltered,
                    onChanged: enabled
                        ? (value) => setState(() => _fabricFiltered = value)
                        : null,
                    title: const Text('Fabric filtered'),
                  ),
                  TextField(
                    controller: _tlvController,
                    minLines: 2,
                    maxLines: 5,
                    decoration: const InputDecoration(
                      labelText: 'TLV hex',
                      hintText: 'Example: 15 18 18 18',
                      alignLabelWithHint: true,
                    ),
                  ),
                  const SizedBox(height: 12),
                  Wrap(
                    spacing: 10,
                    runSpacing: 10,
                    children: [
                      FilledButton.icon(
                        onPressed: enabled ? _execute : null,
                        icon: const Icon(Icons.play_arrow),
                        label: Text('Run ${_operation.label}'),
                      ),
                      OutlinedButton.icon(
                        onPressed: _subscription == null
                            ? null
                            : () async {
                                await _cancelSubscription();
                                if (mounted) {
                                  setState(() {});
                                }
                              },
                        icon: const Icon(Icons.stop_circle_outlined),
                        label: const Text('Cancel subscription'),
                      ),
                    ],
                  ),
                  if (session.operationBusy) ...[
                    const SizedBox(height: 12),
                    const LinearProgressIndicator(),
                  ],
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Presets',
                subtitle: 'Load a known path without changing the API surface.',
                children: [
                  Wrap(
                    spacing: 10,
                    runSpacing: 10,
                    children: [
                      ActionChip(
                        avatar: const Icon(Icons.power_settings_new, size: 18),
                        label: const Text('OnOff On'),
                        onPressed: enabled ? _applyOnOffPreset : null,
                      ),
                      ActionChip(
                        avatar: const Icon(Icons.label_outline, size: 18),
                        label: const Text('NodeLabel read'),
                        onPressed: enabled ? _applyNodeLabelPreset : null,
                      ),
                    ],
                  ),
                ],
              ),
              const SizedBox(height: 14),
              SectionCard(
                title: 'Result',
                api: _operation.label,
                children: [
                  OperationResultCard(result: _result),
                  if (_subscriptionReports.isNotEmpty) ...[
                    const SizedBox(height: 14),
                    Text(
                      'Subscription reports',
                      style: Theme.of(context).textTheme.titleSmall,
                    ),
                    const SizedBox(height: 8),
                    for (final report in _subscriptionReports)
                      Container(
                        width: double.infinity,
                        margin: const EdgeInsets.only(bottom: 8),
                        padding: const EdgeInsets.all(12),
                        decoration: BoxDecoration(
                          color: Theme.of(
                            context,
                          ).colorScheme.surfaceContainerLow,
                          borderRadius: BorderRadius.circular(12),
                        ),
                        child: SelectableText(
                          report,
                          style: Theme.of(context).textTheme.bodySmall
                              ?.copyWith(fontFamily: 'monospace'),
                        ),
                      ),
                  ],
                ],
              ),
            ],
          ),
        );
      },
    );
  }
}

class _PathRow extends StatelessWidget {
  const _PathRow({
    this.endpointController,
    this.clusterController,
    this.left,
    this.right,
  });

  final TextEditingController? endpointController;
  final TextEditingController? clusterController;
  final Widget? left;
  final Widget? right;

  @override
  Widget build(BuildContext context) {
    final leftWidget =
        left ??
        TextField(
          controller: endpointController,
          decoration: const InputDecoration(labelText: 'Endpoint ID'),
        );
    final rightWidget =
        right ??
        TextField(
          controller: clusterController,
          decoration: const InputDecoration(labelText: 'Cluster ID'),
        );
    return Row(
      children: [
        Expanded(child: leftWidget),
        const SizedBox(width: 10),
        Expanded(child: rightWidget),
      ],
    );
  }
}
