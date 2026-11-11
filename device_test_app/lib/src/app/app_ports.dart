import 'package:flutter_matter/flutter_matter.dart';

import '../application/application.dart';
import '../domain/domain.dart';
import '../presentation/ui_models.dart';
import '../report/report.dart';

/// Immutable platform and build information captured during app startup.
class DeviceTestAppBootstrap {
  DeviceTestAppBootstrap({
    required this.controller,
    required Iterable<PreflightCheckViewModel> preflightChecks,
    required this.testApp,
    required this.pluginCommit,
  }) : preflightChecks = List<PreflightCheckViewModel>.unmodifiable(
         preflightChecks,
       );

  final ControllerInfoViewModel controller;
  final List<PreflightCheckViewModel> preflightChecks;
  final TestAppMetadata testApp;
  final String pluginCommit;

  bool get hasBlockingChecks =>
      preflightChecks.any((check) => check.isBlocking);

  List<String> get blockingCheckIds => List<String>.unmodifiable(
    preflightChecks.where((check) => check.isBlocking).map((check) => check.id),
  );
}

/// Loads controller identity and environment checks before a Run may start.
abstract interface class DeviceTestBootstrapPort {
  Future<DeviceTestAppBootstrap> load();
}

/// Persists and retrieves transient provisioning material.
abstract interface class ProvisioningSecretsPort {
  Future<void> save(String runId, ProvisioningSecrets secrets);

  Future<ProvisioningSecrets?> load(String runId);

  Future<void> purge(String runId);
}

/// Parses QR or manual Matter setup payloads.
abstract interface class OnboardingPayloadReader {
  Future<OnboardingPayload> parse(String setupCode);
}

/// Paths to the two report artifacts generated from one report object.
class DeviceTestReportFiles {
  const DeviceTestReportFiles({
    required this.jsonPath,
    required this.markdownPath,
  });

  final String jsonPath;
  final String markdownPath;
}

/// Writes formal report artifacts and exposes the canonical report schema.
abstract interface class DeviceTestReportArtifactPort {
  Future<String> loadCanonicalSchema();

  Future<DeviceTestReportFiles> write({
    required String runId,
    required String jsonContents,
    required String markdownContents,
  });
}

enum DeviceTestReportShareFormat { json, markdown }

/// Opens a platform share sheet for a validated report artifact.
abstract interface class DeviceTestReportSharePort {
  Future<void> share(
    DeviceTestReportFiles files, {
    required DeviceTestReportShareFormat format,
  });
}

/// The subset of RunCoordinator needed by the UI/application binding.
abstract interface class DeviceTestRunPort {
  RunnerStateSnapshot get snapshot;

  Stream<RunnerStateSnapshot> get stateStream;

  Stream<RunnerEvent> get eventStream;

  Future<PersistedRunState?> loadUnfinished();

  Future<RunnerStateSnapshot> start(RunStartRequest request);

  Future<RunnerStateSnapshot?> resume();

  Future<void> stop({String reason = 'Stopped by operator.'});

  Future<DeviceTestReportV1?> buildFormalReport({
    required DateTime generatedAt,
    required bool sanitizationReviewed,
  });

  Future<void> dispose();
}
