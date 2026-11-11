import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

class FakeDeviceTestUiController extends DeviceTestUiController {
  FakeDeviceTestUiController(this._state);

  DeviceTestUiState _state;

  int resumeCalls = 0;
  int confirmCalls = 0;
  int purgeCalls = 0;
  int shareJsonCalls = 0;
  int shareMarkdownCalls = 0;
  String? lastSkipReason;
  String? lastFailReason;
  DeviceTestSetupRequest? submittedRequest;
  final List<DeviceTestScreen> navigations = <DeviceTestScreen>[];

  @override
  DeviceTestUiState get state => _state;

  void emit(DeviceTestUiState next) {
    _state = next;
    notifyListeners();
  }

  @override
  void navigate(DeviceTestScreen screen) {
    navigations.add(screen);
    _state = _copy(screen: screen);
    notifyListeners();
  }

  @override
  Future<void> resumeActiveRun() async {
    resumeCalls++;
    _state = _copy(screen: DeviceTestScreen.runner);
    notifyListeners();
  }

  @override
  Future<void> startRun(DeviceTestSetupRequest request) async {
    submittedRequest = request;
    _state = _copy(screen: DeviceTestScreen.runner);
    notifyListeners();
  }

  @override
  Future<void> confirmPrompt() async {
    confirmCalls++;
  }

  @override
  Future<void> skipPrompt(String reason) async {
    lastSkipReason = reason;
  }

  @override
  Future<void> failPrompt(String reason) async {
    lastFailReason = reason;
  }

  @override
  Future<void> purgeSecrets() async {
    purgeCalls++;
    _state = _copy(hasStoredSecrets: false);
    notifyListeners();
  }

  @override
  Future<void> shareJsonReport() async {
    shareJsonCalls++;
  }

  @override
  Future<void> shareMarkdownReport() async {
    shareMarkdownCalls++;
  }

  DeviceTestUiState _copy({DeviceTestScreen? screen, bool? hasStoredSecrets}) {
    return DeviceTestUiState(
      screen: screen ?? _state.screen,
      busy: _state.busy,
      errorMessage: _state.errorMessage,
      controllerInfo: _state.controllerInfo,
      preflightChecks: _state.preflightChecks,
      activeRun: _state.activeRun,
      prompt: _state.prompt,
      recentRun: _state.recentRun,
      results: _state.results,
      hasStoredSecrets: hasStoredSecrets ?? _state.hasStoredSecrets,
    );
  }
}
