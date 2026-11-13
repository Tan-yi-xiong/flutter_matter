import '../../domain/domain.dart';
import 'platform_info_service.dart';

class BuildMetadata {
  const BuildMetadata({
    required this.pluginCommit,
    required this.testAppCommit,
  });

  static const _pluginCommit = String.fromEnvironment('PLUGIN_COMMIT');
  static const _testAppCommit = String.fromEnvironment('TEST_APP_COMMIT');

  static const current = BuildMetadata(
    pluginCommit: _pluginCommit,
    testAppCommit: _testAppCommit,
  );

  final String pluginCommit;
  final String testAppCommit;

  bool get hasValidCommits =>
      _gitCommitPattern.hasMatch(pluginCommit) &&
      _gitCommitPattern.hasMatch(testAppCommit);

  TestAppMetadata testAppMetadata(PlatformInfo info) {
    return TestAppMetadata(
      name: 'flutter_matter_device_test_app',
      version: info.appVersion,
      commit: testAppCommit,
    );
  }
}

final RegExp _gitCommitPattern = RegExp(r'^[0-9a-f]{40}$');
