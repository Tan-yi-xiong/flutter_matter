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
    if (draft.commissioneeType == CommissioneeType.virtual) {
      if (draft.fallbackReason.trim().isEmpty) {
        errors[SetupField.fallbackReason] =
            'Explain why no qualified real Matter device is available.';
      }
      if (!draft.virtualFallbackConfirmed) {
        errors[SetupField.fallbackConfirmation] =
            'Confirm that the virtual commissionee is the fallback.';
      }
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
    switch (draft.networkTransport) {
      case NetworkTransport.wifi:
        if (draft.wifiSsid.trim().isEmpty) {
          errors[SetupField.networkCredentials] = 'Wi-Fi SSID is required.';
        }
      case NetworkTransport.thread:
        if (draft.threadOperationalDataset.trim().isEmpty) {
          errors[SetupField.networkCredentials] =
              'Thread operational dataset is required.';
        }
      case NetworkTransport.unknown:
        break;
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
