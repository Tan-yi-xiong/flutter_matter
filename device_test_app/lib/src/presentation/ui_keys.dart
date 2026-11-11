import 'package:flutter/widgets.dart';

import '../domain/domain.dart';

/// Stable widget keys for Agent automation and focused widget tests.
abstract final class DeviceTestUiKeys {
  static const homeScreen = ValueKey<String>('device-test-home-screen');
  static const setupScreen = ValueKey<String>('device-test-setup-screen');
  static const runnerScreen = ValueKey<String>('device-test-runner-screen');
  static const resultsScreen = ValueKey<String>('device-test-results-screen');

  static const resumeRun = ValueKey<String>('device-test-resume-run');
  static const newRun = ValueKey<String>('device-test-new-run');
  static const homeViewResults = ValueKey<String>(
    'device-test-home-view-results',
  );
  static const purgeSecrets = ValueKey<String>('device-test-purge-secrets');
  static const confirmPurgeSecrets = ValueKey<String>(
    'device-test-confirm-purge-secrets',
  );
  static const setupPurgeSecrets = ValueKey<String>(
    'device-test-setup-purge-secrets',
  );
  static const startRun = ValueKey<String>('device-test-start-run');
  static const controllerInfo = ValueKey<String>('device-test-controller-info');
  static const preflightList = ValueKey<String>('device-test-preflight-list');
  static const setupValidationSummary = ValueKey<String>(
    'device-test-setup-validation-summary',
  );

  static const modelField = ValueKey<String>('device-test-commissionee-model');
  static const firmwareField = ValueKey<String>(
    'device-test-commissionee-firmware',
  );
  static const stateChangeNotes = ValueKey<String>(
    'device-test-state-change-notes',
  );
  static const setupCode = ValueKey<String>('device-test-setup-code');
  static const wifiSsid = ValueKey<String>('device-test-wifi-ssid');
  static const wifiPassword = ValueKey<String>('device-test-wifi-password');
  static const controllerClean = ValueKey<String>(
    'device-test-clean-controller',
  );
  static const commissioneeClean = ValueKey<String>(
    'device-test-clean-commissionee',
  );
  static const secretsPurged = ValueKey<String>('device-test-secrets-purged');
  static const quickProfile = ValueKey<String>('device-test-profile-quick');
  static const fullProfile = ValueKey<String>('device-test-profile-full');

  static const runProgress = ValueKey<String>('device-test-run-progress');
  static const currentTestTimeout = ValueKey<String>(
    'device-test-current-test-timeout',
  );
  static const waitingForAppRestart = ValueKey<String>(
    'device-test-waiting-for-app-restart',
  );
  static const currentInstruction = ValueKey<String>(
    'device-test-current-instruction',
  );
  static const requiredActor = ValueKey<String>('device-test-required-actor');
  static const promptCard = ValueKey<String>('device-test-prompt-card');
  static const promptConfirm = ValueKey<String>('device-test-prompt-confirm');
  static const promptSkip = ValueKey<String>('device-test-prompt-skip');
  static const promptFail = ValueKey<String>('device-test-prompt-fail');
  static const skipReasonField = ValueKey<String>(
    'device-test-skip-reason-field',
  );
  static const failReasonField = ValueKey<String>(
    'device-test-fail-reason-field',
  );
  static const reasonDialogSubmit = ValueKey<String>(
    'device-test-reason-dialog-submit',
  );
  static const reasonDialogCancel = ValueKey<String>(
    'device-test-reason-dialog-cancel',
  );
  static const runnerViewResults = ValueKey<String>(
    'device-test-runner-view-results',
  );
  static const runnerViewResultsAppBar = ValueKey<String>(
    'device-test-runner-view-results-app-bar',
  );

  static const resultsSummary = ValueKey<String>('device-test-results-summary');
  static const resultsValidation = ValueKey<String>(
    'device-test-results-validation',
  );
  static const resultsTable = ValueKey<String>('device-test-results-table');
  static const shareJson = ValueKey<String>('device-test-share-json');
  static const shareMarkdown = ValueKey<String>('device-test-share-markdown');
  static const resultsPurgeSecrets = ValueKey<String>(
    'device-test-results-purge-secrets',
  );
  static const resultsNewRun = ValueKey<String>('device-test-results-new-run');

  static ValueKey<String> testRow(DeviceTestId testId) =>
      ValueKey<String>('device-test-row-${testId.wireName}');

  static ValueKey<String> resultsRow(DeviceTestId testId) =>
      ValueKey<String>('device-test-results-row-${testId.wireName}');

  static ValueKey<String> stateChangeChoice(StateChangeMethod method) =>
      ValueKey<String>('device-test-state-change-${method.wireName}');
}
