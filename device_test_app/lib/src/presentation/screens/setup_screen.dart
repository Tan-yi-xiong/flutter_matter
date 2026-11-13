import 'dart:async';

import 'package:flutter/material.dart';

import '../../domain/domain.dart';
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
  final TextEditingController _setupCodeController = TextEditingController();
  final TextEditingController _wifiSsidController = TextEditingController();
  final TextEditingController _wifiPasswordController = TextEditingController();

  TestProfile _profile = TestProfile.full;
  bool _hideSetupCode = true;
  bool _hideWifiPassword = true;
  bool _manualSsidRequired = true;
  bool _prefillLoaded = false;
  bool _submitting = false;
  bool _submitted = false;
  String? _actionError;
  Map<SetupField, String> _errors = const <SetupField, String>{};

  @override
  void initState() {
    super.initState();
    unawaited(_loadWifiPrefill());
  }

  @override
  void dispose() {
    _setupCodeController.dispose();
    _wifiSsidController.dispose();
    _wifiPasswordController.dispose();
    super.dispose();
  }

  Future<void> _loadWifiPrefill() async {
    try {
      final prefill = await widget.controller.loadWifiSetupPrefill();
      if (!mounted) {
        return;
      }
      setState(() {
        _prefillLoaded = true;
        _manualSsidRequired = prefill.manualSsidRequired;
        _wifiSsidController.text = prefill.currentSsid ?? '';
        _wifiPasswordController.text = prefill.password;
      });
    } on Object {
      if (!mounted) {
        return;
      }
      setState(() {
        _prefillLoaded = true;
        _manualSsidRequired = true;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final busy = widget.state.busy || _submitting;
    final controllerInfo = widget.state.controllerInfo;
    final visiblePreflight = widget.state.preflightChecks
        .where((check) => check.status != PreflightStatus.passed)
        .toList(growable: false);

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
                    'Prepare a device validation Run',
                    style: theme.textTheme.headlineSmall,
                  ),
                ),
                const SizedBox(height: 6),
                Text(
                  'Matter SDK discovery uses BLE and Wi-Fi/IP concurrently. '
                  'The SDK selects the first matching path for this Run.',
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
                if (visiblePreflight.isNotEmpty) ...<Widget>[
                  const SizedBox(height: 16),
                  PresentationCard(
                    key: DeviceTestUiKeys.preflightList,
                    title: 'Preflight',
                    subtitle: 'Only warnings and blocking checks are shown.',
                    child: Column(
                      children: <Widget>[
                        for (final check in visiblePreflight) ...<Widget>[
                          PreflightRow(check: check),
                          if (check != visiblePreflight.last)
                            const Divider(height: 20),
                        ],
                      ],
                    ),
                  ),
                ],
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Matter Setup Code',
                  subtitle: 'Paste a QR payload or manual pairing code.',
                  child: TextField(
                    key: DeviceTestUiKeys.setupCode,
                    controller: _setupCodeController,
                    enabled: !busy,
                    obscureText: _hideSetupCode,
                    autocorrect: false,
                    enableSuggestions: false,
                    decoration: _fieldDecoration(
                      label: 'Setup code or QR payload',
                      field: SetupField.setupCode,
                      suffixIcon: IconButton(
                        tooltip: _hideSetupCode
                            ? 'Show setup code'
                            : 'Hide setup code',
                        onPressed: busy
                            ? null
                            : () => setState(
                                () => _hideSetupCode = !_hideSetupCode,
                              ),
                        icon: Icon(
                          _hideSetupCode
                              ? Icons.visibility_outlined
                              : Icons.visibility_off_outlined,
                        ),
                      ),
                    ),
                    onChanged: (_) => _clearError(SetupField.setupCode),
                  ),
                ),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Wi-Fi',
                  subtitle:
                      'Used when the commissionee joins the local network over '
                      'Wi-Fi. Leave the password empty for an open network.',
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      if (!_prefillLoaded)
                        const LinearProgressIndicator()
                      else if (_manualSsidRequired)
                        TextField(
                          key: DeviceTestUiKeys.wifiSsidManual,
                          controller: _wifiSsidController,
                          enabled: !busy,
                          textInputAction: TextInputAction.next,
                          decoration: _fieldDecoration(
                            label: 'Wi-Fi SSID',
                            field: SetupField.networkCredentials,
                          ),
                          onChanged: (_) =>
                              _clearError(SetupField.networkCredentials),
                        )
                      else
                        Row(
                          children: <Widget>[
                            Expanded(
                              child: Semantics(
                                key: DeviceTestUiKeys.wifiSsidDisplay,
                                label:
                                    'Current Wi-Fi network '
                                    '${_wifiSsidController.text}',
                                child: DeviceTestStatusLine(
                                  label: 'Current Wi-Fi',
                                  value: _wifiSsidController.text,
                                ),
                              ),
                            ),
                            TextButton(
                              key: DeviceTestUiKeys.wifiSsidChange,
                              onPressed: busy
                                  ? null
                                  : () => setState(
                                      () => _manualSsidRequired = true,
                                    ),
                              child: const Text('Change'),
                            ),
                          ],
                        ),
                      const SizedBox(height: 12),
                      TextField(
                        key: DeviceTestUiKeys.wifiPassword,
                        controller: _wifiPasswordController,
                        enabled: !busy,
                        obscureText: _hideWifiPassword,
                        autocorrect: false,
                        enableSuggestions: false,
                        decoration: _fieldDecoration(
                          label: 'Wi-Fi password',
                          hint: 'Optional for open networks',
                          field: SetupField.networkCredentials,
                          suffixIcon: IconButton(
                            tooltip: _hideWifiPassword
                                ? 'Show Wi-Fi password'
                                : 'Hide Wi-Fi password',
                            onPressed: busy
                                ? null
                                : () => setState(
                                    () =>
                                        _hideWifiPassword = !_hideWifiPassword,
                                  ),
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
                      const SizedBox(height: 8),
                      Align(
                        alignment: Alignment.centerLeft,
                        child: TextButton.icon(
                          key: DeviceTestUiKeys.wifiClearCredentials,
                          onPressed: busy ? null : _clearWifiCredentials,
                          icon: const Icon(Icons.delete_outline),
                          label: const Text('Clear Wi-Fi Credentials'),
                        ),
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 16),
                PresentationCard(
                  title: 'Cleanup',
                  subtitle: 'Cleanup runs automatically before every Run.',
                  child: const Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: <Widget>[
                      InfoBanner(
                        icon: Icons.restart_alt,
                        message:
                            'Before every Run the app purges old Run secrets '
                            'and resets controller identities for this platform.',
                      ),
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
    Widget? suffixIcon,
  }) {
    return InputDecoration(
      labelText: label,
      hintText: hint,
      errorText: field == null ? null : _errors[field],
      suffixIcon: suffixIcon,
      border: const OutlineInputBorder(),
    );
  }

  void _clearError(SetupField field) {
    if (!_errors.containsKey(field)) {
      return;
    }
    setState(() {
      _errors = _without(_errors, field);
    });
  }

  Future<void> _clearWifiCredentials() async {
    try {
      await widget.controller.clearWifiCredentials();
      if (!mounted) {
        return;
      }
      setState(() {
        _wifiPasswordController.clear();
        _actionError = null;
      });
    } on Object {
      if (mounted) {
        setState(() {
          _actionError = 'Stored Wi-Fi credentials could not be cleared.';
        });
      }
    }
  }

  Future<void> _submit() async {
    FocusManager.instance.primaryFocus?.unfocus();
    final controllerInfo = widget.state.controllerInfo;
    final draft = DeviceTestSetupDraft(
      setupCode: _setupCodeController.text,
      wifiSsid: _wifiSsidController.text,
      wifiPassword: _wifiPasswordController.text,
      profile: _profile,
    );

    final validation = DeviceTestSetupValidator.validate(
      draft: draft,
      controller: controllerInfo,
      preflightChecks: widget.state.preflightChecks,
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
      setupCode: draft.setupCode.trim(),
      wifiSsid: draft.wifiSsid.trim(),
      wifiPassword: draft.wifiPassword,
      profile: draft.profile,
    );

    setState(() {
      _submitting = true;
    });
    try {
      await widget.controller.startRun(request);
      _setupCodeController.clear();
      _wifiPasswordController.clear();
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
