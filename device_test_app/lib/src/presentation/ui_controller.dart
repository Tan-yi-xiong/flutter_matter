import 'package:flutter/foundation.dart';

import 'ui_models.dart';

/// Presentation contract for the future application coordinator.
///
/// Implementations translate these requests into RunCoordinator operations and
/// publish immutable state changes. Widgets never call hardware APIs directly.
abstract class DeviceTestUiController extends ChangeNotifier {
  DeviceTestUiState get state;

  void navigate(DeviceTestScreen screen);

  Future<void> resumeActiveRun();

  Future<void> startRun(DeviceTestSetupRequest request);

  Future<WifiSetupPrefill> loadWifiSetupPrefill();

  Future<void> clearWifiCredentials();

  Future<void> confirmPrompt();

  Future<void> skipPrompt(String reason);

  Future<void> failPrompt(String reason);

  Future<void> purgeSecrets();

  Future<void> shareJsonReport();

  Future<void> shareMarkdownReport();
}
