import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

/// Verifies the fabric-removal command path of the library.
///
/// Reset-by-command replaces the retired factory-reset-and-recommission
/// scenario: the removal is issued over CASE and the commissionee must no
/// longer accept an operational connection afterwards.
class FabricRemoveCase implements DeviceTestCase {
  const FabricRemoveCase();

  @override
  DeviceTestId get id => DeviceTestId.fabricRemove;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final identity = context.execution.identity;
    final nodeId = context.execution.nodeId;
    final connection = await restoreConnection(context);
    if (identity == null || nodeId == null || connection == null) {
      return identity == null || nodeId == null
          ? TestCaseOutcome.notRun(
              'An active commissioning and operational connection are required.',
            )
          : TestCaseOutcome.failed(
              'The operational connection could not be restored.',
            );
    }

    final timeout = context.timeoutFor(id);
    try {
      final status = await context.ports.fabric.inspect(
        identity: identity,
        nodeId: nodeId,
        connection: connection,
        timeout: timeout,
      );
      if (!status.present) {
        return TestCaseOutcome.failed(
          'No fabric remained before the removal command was sent.',
        );
      }
      await context.ports.fabric.remove(
        identity: identity,
        nodeId: nodeId,
        connection: connection,
        timeout: timeout,
      );
    } on FabricException catch (error) {
      return TestCaseOutcome.failed(
        'Fabric removal failed with ${error.code.wireName}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Fabric removal timed out after ${timeoutLabel(timeout)}.',
      );
    }

    try {
      final status = await context.ports.fabric.inspect(
        identity: identity,
        nodeId: nodeId,
        connection: connection,
        timeout: timeout,
      );
      if (status.present) {
        return TestCaseOutcome.failed(
          'A fabric remained after the removal command was accepted.',
        );
      }
      return const TestCaseOutcome.passed(
        notes: 'Fabric removal command succeeded; no fabric remained.',
      );
    } on Object {
      // Removing the invoking fabric may tear down the CASE session together
      // with the fabric. Prove absence with a fresh connection attempt.
      try {
        await context.ports.operationalConnection.connect(
          identity: identity,
          nodeId: nodeId,
          timeout: context.timeoutFor(DeviceTestId.operationalConnect),
        );
        return TestCaseOutcome.failed(
          'The commissionee still accepts CASE after fabric removal.',
        );
      } on Object {
        return const TestCaseOutcome.passed(
          notes: 'Fabric removal command succeeded; CASE no longer connects.',
        );
      }
    }
  }
}
