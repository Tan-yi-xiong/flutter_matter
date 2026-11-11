import 'package:flutter_matter/flutter_matter.dart';
import 'package:share_plus/share_plus.dart';

import '../application/application.dart';
import '../domain/domain.dart';
import '../infrastructure/platform/build_metadata.dart';
import '../infrastructure/platform/platform_info_service.dart';
import '../infrastructure/reporting/report_file_repository.dart';
import '../infrastructure/storage/provisioning_secret_store.dart';
import '../presentation/ui_models.dart';
import '../report/report.dart';
import 'app_ports.dart';

final RegExp _gitCommitPattern = RegExp(r'^[0-9a-f]{40}$');

/// Loads the current controller and validates build metadata for official Runs.
class LiveDeviceTestBootstrap implements DeviceTestBootstrapPort {
  LiveDeviceTestBootstrap({
    PlatformInfoService? platformInfo,
    BuildMetadata buildMetadata = BuildMetadata.current,
  }) : _platformInfo = platformInfo ?? PlatformInfoService(),
       _buildMetadata = buildMetadata;

  final PlatformInfoService _platformInfo;
  final BuildMetadata _buildMetadata;

  @override
  Future<DeviceTestAppBootstrap> load() async {
    final info = await _platformInfo.load();
    final platform = ControllerPlatform.parse(info.platform);
    final pluginCommitValid = _gitCommitPattern.hasMatch(
      _buildMetadata.pluginCommit,
    );
    final testAppCommitValid = _gitCommitPattern.hasMatch(
      _buildMetadata.testAppCommit,
    );
    final checks = <PreflightCheckViewModel>[
      PreflightCheckViewModel(
        id: 'plugin_commit',
        label: 'PLUGIN_COMMIT',
        status: pluginCommitValid
            ? PreflightStatus.passed
            : PreflightStatus.failed,
        detail: pluginCommitValid
            ? 'The plugin commit is a valid Git SHA.'
            : 'Rebuild with tool/device_test_app.dart to inject a valid SHA.',
      ),
      PreflightCheckViewModel(
        id: 'test_app_commit',
        label: 'TEST_APP_COMMIT',
        status: testAppCommitValid
            ? PreflightStatus.passed
            : PreflightStatus.failed,
        detail: testAppCommitValid
            ? 'The test app commit is a valid Git SHA.'
            : 'Rebuild with tool/device_test_app.dart to inject a valid SHA.',
      ),
      PreflightCheckViewModel(
        id: 'platform',
        label: 'Mobile controller platform',
        status: PreflightStatus.passed,
        detail: '${info.deviceModel} running ${info.osVersion}.',
      ),
      if (info.appBuild.trim().isEmpty)
        const PreflightCheckViewModel(
          id: 'app_build',
          label: 'App build metadata',
          status: PreflightStatus.warning,
          detail: 'No app build label is available.',
        ),
    ];

    return DeviceTestAppBootstrap(
      controller: ControllerInfoViewModel(
        platform: platform,
        deviceModel: info.deviceModel,
        osVersion: info.osVersion,
        appBuild: info.appBuild,
      ),
      preflightChecks: checks,
      testApp: _buildMetadata.testAppMetadata(info),
      pluginCommit: _buildMetadata.pluginCommit,
    );
  }
}

/// Wraps the production RunCoordinator behind the app-facing port.
class LiveDeviceTestRunner implements DeviceTestRunPort {
  const LiveDeviceTestRunner(this.coordinator);

  final RunCoordinator coordinator;

  @override
  RunnerStateSnapshot get snapshot => coordinator.snapshot;

  @override
  Stream<RunnerStateSnapshot> get stateStream => coordinator.stateStream;

  @override
  Stream<RunnerEvent> get eventStream => coordinator.eventStream;

  @override
  Future<PersistedRunState?> loadUnfinished() =>
      coordinator.ports.persistence.loadUnfinished();

  @override
  Future<RunnerStateSnapshot> start(RunStartRequest request) =>
      coordinator.start(request);

  @override
  Future<RunnerStateSnapshot?> resume() => coordinator.resume();

  @override
  Future<void> stop({String reason = 'Stopped by operator.'}) =>
      coordinator.stop(reason: reason);

  @override
  Future<DeviceTestReportV2?> buildFormalReport({
    required DateTime generatedAt,
    required bool sanitizationReviewed,
  }) => coordinator.buildFormalReport(
    generatedAt: generatedAt,
    sanitizationReviewed: sanitizationReviewed,
  );

  @override
  Future<void> dispose() => coordinator.dispose();
}

/// Adapts the secure provisioning store to the app-facing port.
class LiveProvisioningSecrets implements ProvisioningSecretsPort {
  const LiveProvisioningSecrets(this.store);

  final ProvisioningSecretStore store;

  @override
  Future<void> save(String runId, ProvisioningSecrets secrets) =>
      store.save(runId, secrets);

  @override
  Future<ProvisioningSecrets?> load(String runId) => store.load(runId);

  @override
  Future<void> purge(String runId) => store.purge(runId);
}

/// Uses the plugin's native onboarding parser.
class MethodChannelOnboardingPayloadReader implements OnboardingPayloadReader {
  MethodChannelOnboardingPayloadReader({OnboardingPayloadParser? parser})
    : _parser = parser ?? OnboardingPayloadParser();

  final OnboardingPayloadParser _parser;

  @override
  Future<OnboardingPayload> parse(String setupCode) => _parser.parse(setupCode);
}

/// Adapts the report file repository to the app-facing artifact port.
class LiveDeviceTestReportArtifacts implements DeviceTestReportArtifactPort {
  const LiveDeviceTestReportArtifacts(this.repository);

  final ReportFileRepository repository;

  @override
  Future<String> loadCanonicalSchema() => repository.loadCanonicalSchema();

  @override
  Future<DeviceTestReportFiles> write({
    required String runId,
    required String jsonContents,
    required String markdownContents,
  }) async {
    final artifacts = await repository.write(
      runId: runId,
      jsonContents: jsonContents,
      markdownContents: markdownContents,
    );
    return DeviceTestReportFiles(
      jsonPath: artifacts.jsonFile.path,
      markdownPath: artifacts.markdownFile.path,
    );
  }
}

/// Shares exactly the artifact selected by the caller.
class SharePlusDeviceTestReportSharer implements DeviceTestReportSharePort {
  const SharePlusDeviceTestReportSharer();

  @override
  Future<void> share(
    DeviceTestReportFiles files, {
    required DeviceTestReportShareFormat format,
  }) {
    final path = switch (format) {
      DeviceTestReportShareFormat.json => files.jsonPath,
      DeviceTestReportShareFormat.markdown => files.markdownPath,
    };
    return SharePlus.instance.share(
      ShareParams(
        title: 'flutter_matter device validation',
        subject: 'flutter_matter device validation report',
        files: <XFile>[XFile(path)],
      ),
    );
  }
}
