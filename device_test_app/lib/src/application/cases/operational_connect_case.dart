import '../../domain/domain.dart';
import '../test_case.dart';
import '../test_context.dart';

class OperationalConnectCase implements DeviceTestCase {
  const OperationalConnectCase();

  @override
  DeviceTestId get id => DeviceTestId.operationalConnect;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final identity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    if (identity == null || nodeId == null) {
      return TestCaseOutcome.notRun(
        'Controller identity and commissioned node ID are required.',
      );
    }

    final connection = await context.ports.operationalConnection.connect(
      identity: identity,
      nodeId: nodeId,
      timeout: context.timeoutFor(id),
    );
    if (!connection.isValid) {
      return TestCaseOutcome.failed(
        'Operational CASE connection did not return a valid context.',
      );
    }
    await context.updateExecution((execution) {
      execution.connection = connection;
    });
    return const TestCaseOutcome.passed(
      notes: 'Operational CASE connection returned a valid context.',
    );
  }
}
