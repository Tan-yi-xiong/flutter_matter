import '../application/operator_prompt.dart';
import '../domain/domain.dart';
import '../report/report.dart';

/// Top-level surfaces owned by the presentation layer.
enum DeviceTestScreen { home, setup, runner, results }

/// Presentation states for preflight checks reported by platform adapters.
enum PreflightStatus { passed, warning, failed }

/// Presentation-only validation status for a generated report.
enum ReportUiValidationStatus { unavailable, notApplicable, valid, invalid }

/// Stable, user-facing summary of the controller that will run the tests.
class ControllerInfoViewModel {
  const ControllerInfoViewModel({
    required this.platform,
    required this.deviceModel,
    required this.osVersion,
    required this.appBuild,
    this.isReady = true,
  });

  final ControllerPlatform platform;
  final String deviceModel;
  final String osVersion;
  final String appBuild;
  final bool isReady;

  String get platformLabel => switch (platform) {
    ControllerPlatform.android => 'Android',
    ControllerPlatform.ios => 'iOS',
  };

  String get displayName => '$deviceModel ($osVersion)';
}

/// One user-visible environment check from the bootstrap/platform layer.
class PreflightCheckViewModel {
  const PreflightCheckViewModel({
    required this.id,
    required this.label,
    required this.status,
    this.detail,
  });

  final String id;
  final String label;
  final PreflightStatus status;
  final String? detail;

  bool get isBlocking => status == PreflightStatus.failed;
}

/// A read-only test progress entry shown in the runner and results table.
class TestProgressViewModel {
  const TestProgressViewModel({
    required this.testId,
    required this.status,
    this.duration = Duration.zero,
    this.notes,
  });

  final DeviceTestId testId;
  final DeviceTestStatus status;
  final Duration duration;
  final String? notes;

  DeviceTestPriority get priority => testId.priority;
  String get title => testId.title;
  bool get isTerminal => status.isTerminal;
}

/// Running or resumable Run information projected by the application layer.
class ActiveRunViewModel {
  const ActiveRunViewModel({
    required this.runId,
    required this.profile,
    required this.phase,
    required this.tests,
    this.currentTestId,
    this.currentInstruction,
    this.currentElapsed,
    this.currentTimeout,
    this.awaitingAppRestart = false,
  });

  final String runId;
  final TestProfile profile;
  final RunPhase phase;
  final List<TestProgressViewModel> tests;
  final DeviceTestId? currentTestId;
  final String? currentInstruction;
  final Duration? currentElapsed;
  final Duration? currentTimeout;
  final bool awaitingAppRestart;

  int get completedCount =>
      tests.where((test) => test.status.isTerminal).length;
  int get totalCount => tests.length;
  double get progress => tests.isEmpty ? 0 : completedCount / tests.length;
  bool get isTerminal => phase.isTerminal;
  bool get canResume => !isTerminal && !awaitingAppRestart;
}

/// A prompt that needs an explicit human, Agent, or app decision.
class RunnerPromptViewModel {
  const RunnerPromptViewModel({
    required this.id,
    required this.title,
    required this.instructions,
    required this.requiredActor,
    this.testId,
    this.confirmLabel = 'Confirm',
    this.canSkip = true,
    this.skipRequiresReason = true,
  });

  final String id;
  final String title;
  final String instructions;
  final RequiredActor requiredActor;
  final DeviceTestId? testId;
  final String confirmLabel;
  final bool canSkip;
  final bool skipRequiresReason;
}

/// Compact summary of the most recent completed Run.
class RecentRunViewModel {
  const RecentRunViewModel({
    required this.profile,
    required this.summary,
    required this.completedAt,
    required this.formalEvidence,
  });

  final TestProfile profile;
  final ReportSummary summary;
  final DateTime completedAt;
  final bool formalEvidence;
}

/// Validation feedback for the report generated from a completed Run.
class ReportValidationViewModel {
  const ReportValidationViewModel({
    required this.status,
    required this.message,
    this.issues = const <String>[],
  });

  final ReportUiValidationStatus status;
  final String message;
  final List<String> issues;

  bool get isValid => status == ReportUiValidationStatus.valid;
}

/// Read-only results screen projection.
class ResultsViewModel {
  const ResultsViewModel({
    required this.profile,
    required this.tests,
    required this.validation,
    required this.jsonAvailable,
    required this.markdownAvailable,
    this.summary,
  });

  final TestProfile profile;
  final List<TestProgressViewModel> tests;
  final ReportSummary? summary;
  final ReportValidationViewModel validation;
  final bool jsonAvailable;
  final bool markdownAvailable;
}

/// Complete presentation state consumed by [DeviceTestAppShell].
class DeviceTestUiState {
  const DeviceTestUiState({
    this.screen = DeviceTestScreen.home,
    this.busy = false,
    this.errorMessage,
    this.controllerInfo,
    this.preflightChecks = const <PreflightCheckViewModel>[],
    this.activeRun,
    this.prompt,
    this.recentRun,
    this.results,
    this.hasStoredSecrets = false,
  });

  final DeviceTestScreen screen;
  final bool busy;
  final String? errorMessage;
  final ControllerInfoViewModel? controllerInfo;
  final List<PreflightCheckViewModel> preflightChecks;
  final ActiveRunViewModel? activeRun;
  final RunnerPromptViewModel? prompt;
  final RecentRunViewModel? recentRun;
  final ResultsViewModel? results;
  final bool hasStoredSecrets;
}

/// Clean-cycle acknowledgements required before a Run can start.
class CleanCycleConfirmations {
  const CleanCycleConfirmations({
    required this.controllerClean,
    required this.commissioneeClean,
    required this.secretsPurged,
  });

  final bool controllerClean;
  final bool commissioneeClean;
  final bool secretsPurged;
}

/// Editable setup values kept only in the setup screen.
class DeviceTestSetupDraft {
  const DeviceTestSetupDraft({
    required this.commissioneeType,
    required this.model,
    required this.firmware,
    required this.networkTransport,
    required this.stateChangeMethod,
    required this.setupCode,
    required this.profile,
    required this.cleanCycle,
    this.commissioningTransport = CommissioningTransport.ip,
    this.stateChangeNotes = '',
    this.wifiSsid = '',
    this.wifiPassword = '',
    this.threadOperationalDataset = '',
  });

  final CommissioneeType commissioneeType;
  final String model;
  final String firmware;
  final NetworkTransport networkTransport;
  final StateChangeMethod stateChangeMethod;
  final CommissioningTransport commissioningTransport;
  final String stateChangeNotes;
  final String setupCode;
  final String wifiSsid;
  final String wifiPassword;
  final String threadOperationalDataset;
  final TestProfile profile;
  final CleanCycleConfirmations cleanCycle;
}

/// Validated setup request handed to the application coordinator.
///
/// Secret fields are transient command inputs. They must never be copied into
/// [DeviceTestUiState], report artifacts, or logs.
class DeviceTestSetupRequest {
  const DeviceTestSetupRequest({
    required this.controller,
    required this.commissioneeType,
    required this.model,
    required this.firmware,
    required this.networkTransport,
    required this.stateChangeMethod,
    required this.setupCode,
    required this.profile,
    required this.cleanCycle,
    this.commissioningTransport = CommissioningTransport.ip,
    this.stateChangeNotes = '',
    this.wifiSsid = '',
    this.wifiPassword = '',
    this.threadOperationalDataset = '',
  });

  final ControllerInfoViewModel controller;
  final CommissioneeType commissioneeType;
  final String model;
  final String firmware;
  final NetworkTransport networkTransport;
  final StateChangeMethod stateChangeMethod;
  final CommissioningTransport commissioningTransport;
  final String stateChangeNotes;
  final String setupCode;
  final String wifiSsid;
  final String wifiPassword;
  final String threadOperationalDataset;
  final TestProfile profile;
  final CleanCycleConfirmations cleanCycle;
}

/// Field identifiers used by setup validation messages.
enum SetupField {
  controller,
  preflight,
  commissioneeType,
  commissioningTransport,
  model,
  firmware,
  networkCredentials,
  stateChangeNotes,
  setupCode,
  controllerClean,
  commissioneeClean,
  secretsPurged,
}

class SetupValidationResult {
  SetupValidationResult(Map<SetupField, String> errors)
    : errors = Map<SetupField, String>.unmodifiable(errors);

  final Map<SetupField, String> errors;

  bool get isValid => errors.isEmpty;
  String? operator [](SetupField field) => errors[field];
}

extension RequiredActorPresentation on RequiredActor {
  String get shortLabel => switch (this) {
    RequiredActor.app => 'App',
    RequiredActor.agentAndroid => 'Agent (Android)',
    RequiredActor.human => 'Human',
  };

  String get visibleLabel => '$shortLabel required';
  String get semanticsLabel => 'Required actor: $shortLabel';
}

extension PreflightStatusPresentation on PreflightStatus {
  String get label => switch (this) {
    PreflightStatus.passed => 'Passed',
    PreflightStatus.warning => 'Warning',
    PreflightStatus.failed => 'Failed',
  };
}

extension TestProfilePresentation on TestProfile {
  String get label => this == TestProfile.quick ? 'Quick' : 'Full';
  String get description => this == TestProfile.quick
      ? 'Five-test iteration smoke run. Not formal evidence.'
      : 'All twelve tests. Required for formal evidence.';
}

extension DeviceTestStatusPresentation on DeviceTestStatus {
  String get label => switch (this) {
    DeviceTestStatus.pending => 'Pending',
    DeviceTestStatus.running => 'Running',
    DeviceTestStatus.passed => 'Passed',
    DeviceTestStatus.failed => 'Failed',
    DeviceTestStatus.notRun => 'Not run',
  };
}

extension RunPhasePresentation on RunPhase {
  String get label => switch (this) {
    RunPhase.idle => 'Idle',
    RunPhase.preparing => 'Preparing',
    RunPhase.discovering => 'Discovering commissionee',
    RunPhase.commissioning => 'Commissioning',
    RunPhase.connecting => 'Connecting',
    RunPhase.testing => 'Testing',
    RunPhase.awaitingOperator => 'Waiting for an operator',
    RunPhase.finalizing => 'Finalizing',
    RunPhase.completed => 'Completed',
    RunPhase.failed => 'Failed',
    RunPhase.cancelled => 'Cancelled',
  };
}

extension ReportResultPresentation on ReportResult {
  String get label => switch (this) {
    ReportResult.passed => 'Passed',
    ReportResult.failed => 'Failed',
    ReportResult.notRun => 'Not run',
  };
}

extension NetworkTransportPresentation on NetworkTransport {
  String get label => switch (this) {
    NetworkTransport.wifi => 'Wi-Fi',
    NetworkTransport.thread => 'Thread',
    NetworkTransport.unknown => 'Unknown',
  };
}

extension StateChangeMethodPresentation on StateChangeMethod {
  String get label => switch (this) {
    StateChangeMethod.physicalControl => 'Physical control',
    StateChangeMethod.vendorApp => 'Vendor app',
    StateChangeMethod.commissioneeUi => 'Commissionee UI',
    StateChangeMethod.other => 'Other',
  };
}
