import 'ui_models.dart';

/// Validates setup form values without performing hardware or platform work.
abstract final class DeviceTestSetupValidator {
  static SetupValidationResult validate({
    required DeviceTestSetupDraft draft,
    required ControllerInfoViewModel? controller,
    required List<PreflightCheckViewModel> preflightChecks,
  }) {
    final errors = <SetupField, String>{};

    if (controller == null || !controller.isReady) {
      errors[SetupField.controller] = 'Waiting for controller information.';
    }
    if (preflightChecks.any((check) => check.isBlocking)) {
      errors[SetupField.preflight] =
          'Resolve blocking preflight checks before starting.';
    }
    if (draft.setupCode.trim().isEmpty) {
      errors[SetupField.setupCode] =
          'Matter setup code or QR payload is required.';
    }
    if (draft.wifiSsid.trim().isEmpty) {
      errors[SetupField.networkCredentials] = 'Wi-Fi SSID is required.';
    }
    if (!draft.cleanCycle.commissioneeClean) {
      errors[SetupField.commissioneeClean] =
          'Confirm the commissionee was factory-reset and is in a '
          'commissioning window.';
    }

    return SetupValidationResult(errors);
  }
}
