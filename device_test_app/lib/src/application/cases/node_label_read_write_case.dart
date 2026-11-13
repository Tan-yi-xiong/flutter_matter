import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

/// Verifies the NodeLabel write and read APIs round-trip through the library.
///
/// Device-side persistence is intentionally out of scope: this case only
/// proves that a value written through the library can be read back.
class NodeLabelReadWriteCase implements DeviceTestCase {
  const NodeLabelReadWriteCase();

  static const _testLabel = 'flutter-matter-test';

  @override
  DeviceTestId get id => DeviceTestId.nodeLabelReadWrite;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final identity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    final connection = await restoreConnection(context);
    if (identity == null || nodeId == null || connection == null) {
      return identity == null || nodeId == null
          ? TestCaseOutcome.notRun(
              'An operational connection and commissioned node are required.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }

    final timeout = context.timeoutFor(id);
    try {
      await context.ports.nodeLabel.write(
        connection: connection,
        value: _testLabel,
        timeout: timeout,
      );
      final written = await context.ports.nodeLabel.read(
        connection: connection,
        timeout: timeout,
      );
      if (written != _testLabel) {
        return TestCaseOutcome.failed(
          'NodeLabel readback did not match the written value.',
        );
      }
      return const TestCaseOutcome.passed(
        notes: 'NodeLabel write/read round trip succeeded.',
      );
    } on NodeLabelException catch (error) {
      return TestCaseOutcome.failed(
        'NodeLabel operation failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'NodeLabel round trip timed out after ${timeoutLabel(timeout)}.',
      );
    } on Object {
      return TestCaseOutcome.failed('NodeLabel round trip failed.');
    }
  }
}
