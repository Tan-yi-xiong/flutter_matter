import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class BuildInstallCase implements DeviceTestCase {
  const BuildInstallCase();

  @override
  DeviceTestId get id => DeviceTestId.buildInstall;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    if (context.controller == null || context.commissionee == null) {
      return TestCaseOutcome.notRun(
        'Controller and commissionee metadata are required.',
      );
    }
    final testApp = context.session.testApp;
    if (testApp.name.trim().isEmpty ||
        testApp.version.trim().isEmpty ||
        testApp.commit.trim().isEmpty) {
      return TestCaseOutcome.failed('Test-app build metadata is incomplete.');
    }
    final identity = await ensureIdentity(context);
    if (identity.purpose != ControllerIdentityPurpose.main) {
      return TestCaseOutcome.failed(
        'The main controller identity was not initialized.',
      );
    }
    return const TestCaseOutcome.passed(
      notes: 'Test app launched and controller identity initialized.',
    );
  }
}
