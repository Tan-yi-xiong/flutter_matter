import 'package:flutter/material.dart';

import 'ui_keys.dart';

Future<bool> showPurgeSecretsDialog(BuildContext context) async {
  final confirmed = await showDialog<bool>(
    context: context,
    builder: (context) => AlertDialog(
      title: const Text('Purge stored secrets?'),
      content: const Text(
        'This removes setup codes, network credentials, certificates, and '
        'controller identity material from secure storage. It cannot be undone.',
      ),
      actions: <Widget>[
        TextButton(
          key: DeviceTestUiKeys.reasonDialogCancel,
          onPressed: () => Navigator.of(context).pop(false),
          child: const Text('Cancel'),
        ),
        FilledButton(
          key: DeviceTestUiKeys.confirmPurgeSecrets,
          onPressed: () => Navigator.of(context).pop(true),
          child: const Text('Purge'),
        ),
      ],
    ),
  );
  return confirmed ?? false;
}

Future<String?> showReasonDialog({
  required BuildContext context,
  required String title,
  required String actionLabel,
  required Key fieldKey,
}) {
  return showDialog<String>(
    context: context,
    builder: (context) => _ReasonDialog(
      title: title,
      actionLabel: actionLabel,
      fieldKey: fieldKey,
    ),
  );
}

class _ReasonDialog extends StatefulWidget {
  const _ReasonDialog({
    required this.title,
    required this.actionLabel,
    required this.fieldKey,
  });

  final String title;
  final String actionLabel;
  final Key fieldKey;

  @override
  State<_ReasonDialog> createState() => _ReasonDialogState();
}

class _ReasonDialogState extends State<_ReasonDialog> {
  final TextEditingController _controller = TextEditingController();
  String? _errorText;

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  void _submit() {
    final reason = _controller.text.trim();
    if (reason.isEmpty) {
      setState(() {
        _errorText = 'A reason is required.';
      });
      return;
    }
    Navigator.of(context).pop(reason);
  }

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: Text(widget.title),
      content: TextField(
        key: widget.fieldKey,
        controller: _controller,
        autofocus: true,
        minLines: 2,
        maxLines: 4,
        decoration: InputDecoration(
          labelText: 'Reason',
          hintText: 'Describe what happened without including secrets.',
          errorText: _errorText,
        ),
        onChanged: (_) {
          if (_errorText != null) {
            setState(() {
              _errorText = null;
            });
          }
        },
      ),
      actions: <Widget>[
        TextButton(
          key: DeviceTestUiKeys.reasonDialogCancel,
          onPressed: () => Navigator.of(context).pop(),
          child: const Text('Cancel'),
        ),
        FilledButton(
          key: DeviceTestUiKeys.reasonDialogSubmit,
          onPressed: _submit,
          child: Text(widget.actionLabel),
        ),
      ],
    );
  }
}

/// Explains the post-Run commissionee cleanup and asks the operator to
/// confirm once the device has actually been factory-reset.
Future<bool> showCommissioneeResetDialog(BuildContext context) {
  return showDialog<bool>(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        title: const Text('Reset the commissionee?'),
        content: const Text(
          'Factory reset the commissionee (or reset the virtual device) so '
          'the next Run starts without accumulated fabrics. Confirm only '
          'after the device is factory-reset and commissionable again.',
        ),
        actions: <Widget>[
          TextButton(
            onPressed: () => Navigator.of(context).pop(false),
            child: const Text('Cancel'),
          ),
          FilledButton(
            onPressed: () => Navigator.of(context).pop(true),
            child: const Text('I reset the device'),
          ),
        ],
      );
    },
  ).then((value) => value ?? false);
}
