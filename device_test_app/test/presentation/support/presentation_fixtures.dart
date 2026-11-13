import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';

const controllerInfo = ControllerInfoViewModel(
  platform: ControllerPlatform.android,
  deviceModel: 'Pixel 8',
  osVersion: 'Android 15',
  appBuild: 'debug 1.0.0 (1)',
);

const readyPreflight = <PreflightCheckViewModel>[
  PreflightCheckViewModel(
    id: 'bluetooth',
    label: 'Bluetooth permission',
    status: PreflightStatus.passed,
  ),
  PreflightCheckViewModel(
    id: 'local-network',
    label: 'Local network connectivity',
    status: PreflightStatus.passed,
  ),
];

List<TestProgressViewModel> testProgress(
  TestProfile profile, {
  Map<DeviceTestId, DeviceTestStatus> statuses = const {},
}) {
  return <TestProgressViewModel>[
    for (final testId in profile.testIds)
      TestProgressViewModel(
        testId: testId,
        status: statuses[testId] ?? DeviceTestStatus.pending,
        duration: statuses[testId]?.isTerminal ?? false
            ? const Duration(seconds: 3)
            : Duration.zero,
      ),
  ];
}

ActiveRunViewModel activeRun({
  TestProfile profile = TestProfile.full,
  RunPhase phase = RunPhase.testing,
  Map<DeviceTestId, DeviceTestStatus> statuses = const {},
  DeviceTestId? currentTestId = DeviceTestId.commissioning,
  String? currentInstruction = 'Commissioning the Matter device.',
}) {
  return ActiveRunViewModel(
    runId: 'run-fixture',
    profile: profile,
    phase: phase,
    tests: testProgress(profile, statuses: statuses),
    currentTestId: currentTestId,
    currentInstruction: currentInstruction,
    currentElapsed: const Duration(seconds: 30),
    currentTimeout: const Duration(minutes: 5),
  );
}

RunnerPromptViewModel prompt({
  RequiredActor actor = RequiredActor.human,
  String id = 'prompt-fixture',
  String title = 'Change the commissionee On/Off state',
  String instructions = 'Press the physical On/Off control once.',
}) {
  return RunnerPromptViewModel(
    id: id,
    title: title,
    instructions: instructions,
    requiredActor: actor,
    testId: DeviceTestId.onoffInvoke,
  );
}

DeviceTestUiState setupState({bool hasStoredSecrets = false}) {
  return DeviceTestUiState(
    screen: DeviceTestScreen.setup,
    controllerInfo: controllerInfo,
    preflightChecks: readyPreflight,
    hasStoredSecrets: hasStoredSecrets,
  );
}

DeviceTestUiState runnerState({
  ActiveRunViewModel? run,
  RunnerPromptViewModel? activePrompt,
  bool busy = false,
}) {
  return DeviceTestUiState(
    screen: DeviceTestScreen.runner,
    controllerInfo: controllerInfo,
    preflightChecks: readyPreflight,
    activeRun: run ?? activeRun(),
    prompt: activePrompt,
    busy: busy,
  );
}
