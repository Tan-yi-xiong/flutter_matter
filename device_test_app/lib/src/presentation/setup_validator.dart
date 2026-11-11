import '../domain/domain.dart';
import 'ui_models.dart';

/// Validates setup form values without performing hardware or platform work.
abstract final class DeviceTestSetupValidator {
  static SetupValidationResult validate({
    required DeviceTestSetupDraft draft,
    required ControllerInfoViewModel? controller,
    required List<PreflightCheckViewModel> preflightChecks,
    required bool hasStoredSecrets,
  }) {
    final errors = <SetupField, String>{};

    if (controller == null || !controller.isReady) {
      errors[SetupField.controller] = 'Waiting for controller information.';
    }
    if (preflightChecks.any((check) => check.isBlocking)) {
      errors[SetupField.preflight] =
          'Resolve blocking preflight checks before starting.';
    }
    if (draft.commissioneeType != CommissioneeType.real) {
      errors[SetupField.commissioneeType] =
          'Device validation requires a real Matter commissionee.';
    }
    if (draft.commissioningTransport != CommissioningTransport.ip) {
      errors[SetupField.commissioningTransport] =
          'Device validation requires Wi-Fi/IP commissioning.';
    }
    if (draft.model.trim().isEmpty) {
      errors[SetupField.model] = 'Commissionee model is required.';
    }
    if (draft.firmware.trim().isEmpty) {
      errors[SetupField.firmware] = 'Firmware version is required.';
    }
    if (draft.setupCode.trim().isEmpty) {
      errors[SetupField.setupCode] =
          'Matter setup code or QR payload is required.';
    }
    if (draft.networkTransport != NetworkTransport.wifi) {
      errors[SetupField.networkCredentials] =
          'Only Wi-Fi/IP commissioning is supported.';
    } else if (draft.wifiSsid.trim().isEmpty) {
      errors[SetupField.networkCredentials] = 'Wi-Fi SSID is required.';
    }
    if (draft.stateChangeMethod == StateChangeMethod.other &&
        draft.stateChangeNotes.trim().isEmpty) {
      errors[SetupField.stateChangeNotes] =
          'Describe how state changes will be triggered.';
    }
    if (!draft.cleanCycle.controllerClean) {
      errors[SetupField.controllerClean] =
          'Confirm the controller starts from a clean fabric and app state.';
    }
    if (!draft.cleanCycle.commissioneeClean) {
      errors[SetupField.commissioneeClean] =
          'Confirm the commissionee was reset for this Run.';
    }
    if (hasStoredSecrets || !draft.cleanCycle.secretsPurged) {
      errors[SetupField.secretsPurged] =
          'Purge stored controller secrets before starting a new Run.';
    }

    return SetupValidationResult(errors);
  }
}
