import 'package:flutter/material.dart';

import '../../domain/domain.dart';
import '../dialogs.dart';
import '../setup_validator.dart';
import '../ui_controller.dart';
import '../ui_keys.dart';
import '../ui_models.dart';
import '../widgets.dart';

class SetupScreen extends StatefulWidget {
  const SetupScreen({super.key, required this.controller, required this.state});

  final DeviceTestUiController controller;
  final DeviceTestUiState state;

  @override
  State<SetupScreen> createState() => _SetupScreenState();
}

class _SetupScreenState extends State<SetupScreen> {
  final TextEditingController _fallbackReasonController =
      TextEditingController();
  final TextEditingController _modelController = TextEditingController();
  final TextEditingController _firmwareController = TextEditingController();
  final TextEditingController _stateChangeNotesController =
      TextEditingController();
  final TextEditingController _setupCodeController = TextEditingController();
  final TextEditingController _wifiSsidController = TextEditingController();
  final TextEditingController _wifiPasswordController = TextEditingController();
  final TextEditingController _threadDatasetController =
      TextEditingController();

  CommissioneeType _commissioneeType = CommissioneeType.real;
  NetworkTransport _networkTransport = NetworkTransport.wifi;
  StateChangeMethod _stateChangeMethod = StateChangeMethod.physicalControl;
  TestProfile _profile = TestProfile.full;
  bool _virtualFallbackConfirmed = false;
  bool _controllerClean = false;
  bool _commissioneeClean = false;
  bool _secretsPurged = false;
  bool _hideSetupCode = true;
  bool _hideWifiPassword = true;
  bool _hideThreadDataset = true;
  bool _submitted = false;
  bool _submitting = false;
  String? _actionError;
  Map<SetupField, String> _errors = const <SetupField, String>{};

  @override
  void dispose() {
    _fallbackReasonController.dispose();
    _modelController.dispose();
    _firmwareController.dispose();
    _stateChangeNotesController.dispose();
    _setupCodeController.dispose();
    _wifiSsidController.dispose();
    _wifiPasswordController.dispose();
    _threadDatasetController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final busy = widget.state.busy || _submitting;
    final controllerInfo = widget.state.controllerInfo;

    return DeviceTestPage(
      screenKey: DeviceTestUiKeys.setupScreen,
      title: 'New Run Setup',
      leading: IconButton(
        tooltip: 'Back to home',
        onPressed: busy
            ? null
            : () => widget.controller.navigate(DeviceTestScreen.home),
        icon: const Icon(Icons.arrow_back),
      ),
      child: SingleChildScrollView(
        padding: const EdgeInsets.all(16),
        child: Center(
          child: ConstrainedBox(
            constraints: const BoxConstraints(maxWidth: 960),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: <Widget>[
                Semantics(
                  header: true,
                  child: Text(
                    'Prepare a clean validation Run',
                    style: theme.textTheme.headlineSmall,
                  ),
                ),
                const SizedBox(height: 6),
                Text(
                  'Real Matter hardware is the primary path. The virtual '
                  'commissionee is a fallback that requires a recorded reason.',
                  style: theme.textTheme.bodyMedium,
                ),
                if (_actionError != null ||
                    widget.state.errorMessage != null) ...<Widget>[
                  const SizedBox(height: 16),
                  ErrorBanner(
                    message: _actionError ?? widget.state.errorMessage!,
                  ),
                ],
                if (_submitted && _errors.isNotEmpty) ...<Widget>[
                  const SizedBox(height: 16),
                  Semantics(
                    key: DeviceTestUiKeys.setupValidationSummary,
                    liveRegion: true,
                    container: true,
                    label:
                        'Setup validation failed. Review the highlighted fields.',
                    excludeSemantics: true,
                    child: const ErrorBanner(
                      message:
                          'Setup validation failed. Review the highlighted fields.',
                    ),
                  ),
                ],
                const SizedBox(height: 20),
                _buildControllerCard(context, controllerInfo),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Commissionee',
                  subtitle:
                      'Select the physical device or the distinct Android '
                      'virtual-device fallback.',
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      Wrap(
                        spacing: 8,
                        runSpacing: 8,
                        children: <Widget>[
                          _selectionChip(
                            key: DeviceTestUiKeys.realCommissionee,
                            label: 'Real Matter device',
                            semanticsLabel: 'Select a real Matter commissionee',
                            selected:
                                _commissioneeType == CommissioneeType.real,
                            enabled: !busy,
                            onSelected: () =>
                                _setCommissioneeType(CommissioneeType.real),
                          ),
                          _selectionChip(
                            key: DeviceTestUiKeys.virtualCommissionee,
                            label: 'Android virtual device',
                            semanticsLabel:
                                'Select an Android virtual commissionee',
                            selected:
                                _commissioneeType == CommissioneeType.virtual,
                            enabled: !busy,
                            onSelected: () =>
                                _setCommissioneeType(CommissioneeType.virtual),
                          ),
                        ],
                      ),
                      if (_commissioneeType ==
                          CommissioneeType.virtual) ...<Widget>[
                        const SizedBox(height: 16),
                        InfoBanner(
                          icon: Icons.devices_other,
                          message:
                              'The virtual commissionee must be a distinct '
                              'Android phone running the Project CHIP Virtual '
                              'Device App.',
                        ),
                        const SizedBox(height: 12),
                        TextField(
                          key: DeviceTestUiKeys.fallbackReason,
                          controller: _fallbackReasonController,
                          enabled: !busy,
                          minLines: 2,
                          maxLines: 4,
                          decoration: _fieldDecoration(
                            label: 'Fallback reason',
                            hint:
                                'Explain why no qualified real Matter On/Off '
                                'device is available.',
                            field: SetupField.fallbackReason,
                          ),
                          onChanged: (_) =>
                              _clearError(SetupField.fallbackReason),
                        ),
                        CheckboxListTile(
                          key: DeviceTestUiKeys.fallbackConfirmation,
                          value: _virtualFallbackConfirmed,
                          onChanged: busy
                              ? null
                              : (value) => setState(() {
                                  _virtualFallbackConfirmed = value ?? false;
                                  _errors = _without(
                                    _errors,
                                    SetupField.fallbackConfirmation,
                                  );
                                }),
                          controlAffinity: ListTileControlAffinity.leading,
                          contentPadding: EdgeInsets.zero,
                          title: const Text(
                            'I confirm that a real Matter device is unavailable.',
                          ),
                          subtitle: _errorText(SetupField.fallbackConfirmation),
                        ),
                      ],
                      const SizedBox(height: 16),
                      TextField(
                        key: DeviceTestUiKeys.modelField,
                        controller: _modelController,
                        enabled: !busy,
                        textInputAction: TextInputAction.next,
                        decoration: _fieldDecoration(
                          label: 'Commissionee model',
                          hint: 'Example: Example Matter Plug',
                          field: SetupField.model,
                        ),
                        onChanged: (_) => _clearError(SetupField.model),
                      ),
                      const SizedBox(height: 12),
                      TextField(
                        key: DeviceTestUiKeys.firmwareField,
                        controller: _firmwareController,
                        enabled: !busy,
                        textInputAction: TextInputAction.next,
                        decoration: _fieldDecoration(
                          label: 'Firmware version',
                          hint: 'Example: 1.0.0',
                          field: SetupField.firmware,
                        ),
                        onChanged: (_) => _clearError(SetupField.firmware),
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Network and State Changes',
                  subtitle:
                      'Describe how the commissionee reaches the network and '
                      'how its On/Off state can be changed.',
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      Text(
                        'Network transport',
                        style: theme.textTheme.labelLarge,
                      ),
                      const SizedBox(height: 8),
                      Wrap(
                        spacing: 8,
                        runSpacing: 8,
                        children: <Widget>[
                          for (final transport in NetworkTransport.values)
                            _selectionChip(
                              key: DeviceTestUiKeys.networkChoice(transport),
                              label: transport.label,
                              semanticsLabel:
                                  'Select ${transport.label} network transport',
                              selected: _networkTransport == transport,
                              enabled: !busy,
                              onSelected: () => _setNetworkTransport(transport),
                            ),
                        ],
                      ),
                      const SizedBox(height: 16),
                      if (_networkTransport ==
                          NetworkTransport.wifi) ...<Widget>[
                        TextField(
                          key: DeviceTestUiKeys.wifiSsid,
                          controller: _wifiSsidController,
                          enabled: !busy,
                          textInputAction: TextInputAction.next,
                          decoration: _fieldDecoration(
                            label: 'Wi-Fi SSID',
                            field: SetupField.networkCredentials,
                          ),
                          onChanged: (_) =>
                              _clearError(SetupField.networkCredentials),
                        ),
                        const SizedBox(height: 12),
                        TextField(
                          key: DeviceTestUiKeys.wifiPassword,
                          controller: _wifiPasswordController,
                          enabled: !busy,
                          obscureText: _hideWifiPassword,
                          autocorrect: false,
                          enableSuggestions: false,
                          decoration:
                              _fieldDecoration(
                                label:
                                    'Wi-Fi password (optional for open networks)',
                                field: null,
                              ).copyWith(
                                suffixIcon: IconButton(
                                  tooltip: _hideWifiPassword
                                      ? 'Show Wi-Fi password'
                                      : 'Hide Wi-Fi password',
                                  onPressed: busy
                                      ? null
                                      : () => setState(() {
                                          _hideWifiPassword =
                                              !_hideWifiPassword;
                                        }),
                                  icon: Icon(
                                    _hideWifiPassword
                                        ? Icons.visibility_outlined
                                        : Icons.visibility_off_outlined,
                                  ),
                                ),
                              ),
                          onChanged: (_) =>
                              _clearError(SetupField.networkCredentials),
                        ),
                      ] else if (_networkTransport ==
                          NetworkTransport.thread) ...<Widget>[
                        TextField(
                          key: DeviceTestUiKeys.threadDataset,
                          controller: _threadDatasetController,
                          enabled: !busy,
                          obscureText: _hideThreadDataset,
                          autocorrect: false,
                          enableSuggestions: false,
                          decoration:
                              _fieldDecoration(
                                label: 'Thread operational dataset',
                                field: SetupField.networkCredentials,
                              ).copyWith(
                                suffixIcon: IconButton(
                                  tooltip: _hideThreadDataset
                                      ? 'Show Thread operational dataset'
                                      : 'Hide Thread operational dataset',
                                  onPressed: busy
                                      ? null
                                      : () => setState(() {
                                          _hideThreadDataset =
                                              !_hideThreadDataset;
                                        }),
                                  icon: Icon(
                                    _hideThreadDataset
                                        ? Icons.visibility_outlined
                                        : Icons.visibility_off_outlined,
                                  ),
                                ),
                              ),
                          onChanged: (_) =>
                              _clearError(SetupField.networkCredentials),
                        ),
                      ] else
                        const InfoBanner(
                          icon: Icons.settings_ethernet,
                          message:
                              'Unknown transport credentials must be supplied '
                              'by the test harness before commissioning.',
                        ),
                      const SizedBox(height: 16),
                      Text(
                        'State-change method',
                        style: theme.textTheme.labelLarge,
                      ),
                      const SizedBox(height: 8),
                      Wrap(
                        spacing: 8,
                        runSpacing: 8,
                        children: <Widget>[
                          for (final method in StateChangeMethod.values)
                            _selectionChip(
                              key: DeviceTestUiKeys.stateChangeChoice(method),
                              label: method.label,
                              semanticsLabel:
                                  'Select ${method.label} state-change method',
                              selected: _stateChangeMethod == method,
                              enabled: !busy,
                              onSelected: () => _setStateChangeMethod(method),
                            ),
                        ],
                      ),
                      const SizedBox(height: 12),
                      TextField(
                        key: DeviceTestUiKeys.stateChangeNotes,
                        controller: _stateChangeNotesController,
                        enabled: !busy,
                        minLines: 2,
                        maxLines: 4,
                        decoration: _fieldDecoration(
                          label: 'State-change notes',
                          hint:
                              'Identify the physical control, vendor app, or '
                              'commissionee UI without including secrets.',
                          field: SetupField.stateChangeNotes,
                        ),
                        onChanged: (_) =>
                            _clearError(SetupField.stateChangeNotes),
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Provisioning Inputs',
                  subtitle:
                      'Secrets remain transient inputs and are never copied '
                      'into visible Run state.',
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      TextField(
                        key: DeviceTestUiKeys.setupCode,
                        controller: _setupCodeController,
                        enabled: !busy,
                        obscureText: _hideSetupCode,
                        autocorrect: false,
                        enableSuggestions: false,
                        decoration:
                            _fieldDecoration(
                              label: 'Matter setup code or QR payload',
                              field: SetupField.setupCode,
                            ).copyWith(
                              suffixIcon: IconButton(
                                tooltip: _hideSetupCode
                                    ? 'Show setup code'
                                    : 'Hide setup code',
                                onPressed: busy
                                    ? null
                                    : () => setState(() {
                                        _hideSetupCode = !_hideSetupCode;
                                      }),
                                icon: Icon(
                                  _hideSetupCode
                                      ? Icons.visibility_outlined
                                      : Icons.visibility_off_outlined,
                                ),
                              ),
                            ),
                        onChanged: (_) => _clearError(SetupField.setupCode),
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Preflight',
                  subtitle:
                      'Permissions, Bluetooth, local network, and connectivity '
                      'must be ready before the Run starts.',
                  child: Container(
                    key: DeviceTestUiKeys.preflightList,
                    child: widget.state.preflightChecks.isEmpty
                        ? const InfoBanner(
                            message: 'No preflight checks were reported.',
                            icon: Icons.pending_outlined,
                          )
                        : Column(
                            children: <Widget>[
                              for (final check in widget.state.preflightChecks)
                                PreflightRow(check: check),
                            ],
                          ),
                  ),
                ),
                if (_errorText(SetupField.preflight) != null) ...<Widget>[
                  const SizedBox(height: 8),
                  _InlineError(error: _errors[SetupField.preflight]!),
                ],
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Clean-cycle Confirmations',
                  subtitle:
                      'Every controller path and every fallback must begin from '
                      'a clean test state.',
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      CheckboxListTile(
                        key: DeviceTestUiKeys.controllerClean,
                        value: _controllerClean,
                        onChanged: busy
                            ? null
                            : (value) => setState(() {
                                _controllerClean = value ?? false;
                                _errors = _without(
                                  _errors,
                                  SetupField.controllerClean,
                                );
                              }),
                        controlAffinity: ListTileControlAffinity.leading,
                        contentPadding: EdgeInsets.zero,
                        title: const Text(
                          'Controller has a clean fabric and app state.',
                        ),
                        subtitle: _errorText(SetupField.controllerClean),
                      ),
                      CheckboxListTile(
                        key: DeviceTestUiKeys.commissioneeClean,
                        value: _commissioneeClean,
                        onChanged: busy
                            ? null
                            : (value) => setState(() {
                                _commissioneeClean = value ?? false;
                                _errors = _without(
                                  _errors,
                                  SetupField.commissioneeClean,
                                );
                              }),
                        controlAffinity: ListTileControlAffinity.leading,
                        contentPadding: EdgeInsets.zero,
                        title: const Text(
                          'Commissionee was factory-reset or has a clean virtual state.',
                        ),
                        subtitle: _errorText(SetupField.commissioneeClean),
                      ),
                      CheckboxListTile(
                        key: DeviceTestUiKeys.secretsPurged,
                        value: _secretsPurged,
                        onChanged: busy
                            ? null
                            : (value) => setState(() {
                                _secretsPurged = value ?? false;
                                _errors = _without(
                                  _errors,
                                  SetupField.secretsPurged,
                                );
                              }),
                        controlAffinity: ListTileControlAffinity.leading,
                        contentPadding: EdgeInsets.zero,
                        title: const Text(
                          'Previous test secrets and controller identity were purged.',
                        ),
                        subtitle: _errorText(SetupField.secretsPurged),
                      ),
                      if (widget.state.hasStoredSecrets) ...<Widget>[
                        const SizedBox(height: 8),
                        const InfoBanner(
                          icon: Icons.lock_outline,
                          message:
                              'Stored secrets are still present. Purge them '
                              'before starting this Run.',
                        ),
                        const SizedBox(height: 8),
                        Align(
                          alignment: Alignment.centerLeft,
                          child: Semantics(
                            label: 'Purge stored controller secrets from setup',
                            button: true,
                            enabled: !busy,
                            excludeSemantics: true,
                            child: OutlinedButton.icon(
                              key: DeviceTestUiKeys.setupPurgeSecrets,
                              onPressed: busy ? null : _purgeSecrets,
                              icon: const Icon(Icons.delete_forever_outlined),
                              label: const Text('Purge Secrets Now'),
                            ),
                          ),
                        ),
                      ],
                    ],
                  ),
                ),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Profile',
                  subtitle:
                      'Quick is iteration-only. Full is required for PR and '
                      'release evidence.',
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      Wrap(
                        spacing: 8,
                        runSpacing: 8,
                        children: <Widget>[
                          for (final profile in TestProfile.values)
                            _selectionChip(
                              key: profile == TestProfile.quick
                                  ? DeviceTestUiKeys.quickProfile
                                  : DeviceTestUiKeys.fullProfile,
                              label: profile.label,
                              semanticsLabel: 'Select ${profile.label} profile',
                              selected: _profile == profile,
                              enabled: !busy,
                              onSelected: () =>
                                  setState(() => _profile = profile),
                            ),
                        ],
                      ),
                      const SizedBox(height: 8),
                      Text(
                        _profile.description,
                        style: theme.textTheme.bodySmall,
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 20),
                Semantics(
                  label: 'Start device test run',
                  button: true,
                  enabled: !busy,
                  excludeSemantics: true,
                  child: FilledButton.icon(
                    key: DeviceTestUiKeys.startRun,
                    onPressed: busy ? null : _submit,
                    icon: const Icon(Icons.play_circle_outline),
                    label: Text(busy ? 'Starting…' : 'Start Run'),
                  ),
                ),
                const SizedBox(height: 24),
              ],
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildControllerCard(
    BuildContext context,
    ControllerInfoViewModel? controllerInfo,
  ) {
    return Semantics(
      key: DeviceTestUiKeys.controllerInfo,
      container: true,
      label: controllerInfo == null
          ? 'Controller information is not available'
          : 'Controller ${controllerInfo.platformLabel}, '
                '${controllerInfo.displayName}',
      excludeSemantics: true,
      child: PresentationCard(
        title: 'Controller',
        subtitle: 'Detected automatically by the app bootstrap.',
        child: controllerInfo == null
            ? const InfoBanner(
                message: 'Waiting for controller information.',
                icon: Icons.phone_android,
              )
            : Column(
                children: <Widget>[
                  DeviceTestStatusLine(
                    label: 'Platform',
                    value: controllerInfo.platformLabel,
                  ),
                  DeviceTestStatusLine(
                    label: 'Model',
                    value: controllerInfo.deviceModel,
                  ),
                  DeviceTestStatusLine(
                    label: 'OS version',
                    value: controllerInfo.osVersion,
                  ),
                  DeviceTestStatusLine(
                    label: 'App build',
                    value: controllerInfo.appBuild,
                  ),
                ],
              ),
      ),
    );
  }

  Widget _selectionChip({
    required Key key,
    required String label,
    required String semanticsLabel,
    required bool selected,
    required bool enabled,
    required VoidCallback onSelected,
  }) {
    return Semantics(
      label: semanticsLabel,
      button: true,
      selected: selected,
      enabled: enabled,
      excludeSemantics: true,
      child: ChoiceChip(
        key: key,
        label: Text(label),
        selected: selected,
        onSelected: enabled ? (_) => onSelected() : null,
      ),
    );
  }

  InputDecoration _fieldDecoration({
    required String label,
    SetupField? field,
    String? hint,
  }) {
    return InputDecoration(
      labelText: label,
      hintText: hint,
      errorText: field == null ? null : _errors[field],
      border: const OutlineInputBorder(),
    );
  }

  Widget? _errorText(SetupField field) {
    final error = _errors[field];
    return error == null ? null : _InlineError(error: error);
  }

  void _setCommissioneeType(CommissioneeType type) {
    setState(() {
      _commissioneeType = type;
      _errors = _without(_errors, SetupField.fallbackReason);
      _errors = _without(_errors, SetupField.fallbackConfirmation);
    });
  }

  void _setNetworkTransport(NetworkTransport transport) {
    setState(() {
      _networkTransport = transport;
      _errors = _without(_errors, SetupField.networkCredentials);
    });
  }

  void _setStateChangeMethod(StateChangeMethod method) {
    setState(() {
      _stateChangeMethod = method;
      _errors = _without(_errors, SetupField.stateChangeNotes);
    });
  }

  void _clearError(SetupField field) {
    if (!_errors.containsKey(field)) {
      return;
    }
    setState(() {
      _errors = _without(_errors, field);
    });
  }

  Future<void> _purgeSecrets() async {
    final confirmed = await showPurgeSecretsDialog(context);
    if (!confirmed || !mounted) {
      return;
    }
    try {
      await widget.controller.purgeSecrets();
    } on Object {
      if (mounted) {
        setState(() {
          _actionError = 'Secrets could not be purged.';
        });
      }
    }
  }

  Future<void> _submit() async {
    FocusManager.instance.primaryFocus?.unfocus();
    final controllerInfo = widget.state.controllerInfo;
    final cleanCycle = CleanCycleConfirmations(
      controllerClean: _controllerClean,
      commissioneeClean: _commissioneeClean,
      secretsPurged: _secretsPurged,
    );
    final draft = DeviceTestSetupDraft(
      commissioneeType: _commissioneeType,
      fallbackReason: _fallbackReasonController.text,
      virtualFallbackConfirmed: _virtualFallbackConfirmed,
      model: _modelController.text,
      firmware: _firmwareController.text,
      networkTransport: _networkTransport,
      stateChangeMethod: _stateChangeMethod,
      stateChangeNotes: _stateChangeNotesController.text,
      setupCode: _setupCodeController.text,
      wifiSsid: _wifiSsidController.text,
      wifiPassword: _wifiPasswordController.text,
      threadOperationalDataset: _threadDatasetController.text,
      profile: _profile,
      cleanCycle: cleanCycle,
    );

    final validation = DeviceTestSetupValidator.validate(
      draft: draft,
      controller: controllerInfo,
      preflightChecks: widget.state.preflightChecks,
      hasStoredSecrets: widget.state.hasStoredSecrets,
    );
    setState(() {
      _submitted = true;
      _errors = validation.errors;
      _actionError = null;
    });
    if (!validation.isValid || controllerInfo == null) {
      return;
    }

    final request = DeviceTestSetupRequest(
      controller: controllerInfo,
      commissioneeType: draft.commissioneeType,
      fallbackReason: draft.fallbackReason.trim(),
      model: draft.model.trim(),
      firmware: draft.firmware.trim(),
      networkTransport: draft.networkTransport,
      stateChangeMethod: draft.stateChangeMethod,
      stateChangeNotes: draft.stateChangeNotes.trim(),
      setupCode: draft.setupCode.trim(),
      wifiSsid: draft.wifiSsid.trim(),
      wifiPassword: draft.wifiPassword,
      threadOperationalDataset: draft.threadOperationalDataset.trim(),
      profile: draft.profile,
      cleanCycle: draft.cleanCycle,
    );

    setState(() {
      _submitting = true;
    });
    try {
      await widget.controller.startRun(request);
      _setupCodeController.clear();
      _wifiPasswordController.clear();
      _threadDatasetController.clear();
    } on Object {
      if (mounted) {
        setState(() {
          _actionError = 'The Run could not be started.';
        });
      }
    } finally {
      if (mounted) {
        setState(() {
          _submitting = false;
        });
      }
    }
  }
}

class _InlineError extends StatelessWidget {
  const _InlineError({required this.error});

  final String error;

  @override
  Widget build(BuildContext context) {
    return Semantics(
      container: true,
      liveRegion: true,
      label: error,
      child: Text(
        error,
        style: Theme.of(context).textTheme.bodySmall?.copyWith(
          color: Theme.of(context).colorScheme.error,
        ),
      ),
    );
  }
}

Map<SetupField, String> _without(
  Map<SetupField, String> errors,
  SetupField field,
) {
  if (!errors.containsKey(field)) {
    return errors;
  }
  final next = Map<SetupField, String>.of(errors)..remove(field);
  return next;
}
