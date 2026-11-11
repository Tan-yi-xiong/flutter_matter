import 'dart:async';

import '../../domain/domain.dart';
import '../ports.dart';
import '../test_case.dart';
import '../test_context.dart';
import 'case_support.dart';

class BleCommissioningCase implements DeviceTestCase {
  const BleCommissioningCase();

  @override
  DeviceTestId get id => DeviceTestId.bleCommissioning;

  @override
  Future<TestCaseOutcome> execute(TestContext context) async {
    final secrets = context.secrets;
    if (secrets == null) {
      return TestCaseOutcome.notRun(
        'Provisioning secrets are unavailable for commissioning.',
      );
    }
    var target = context.execution.target;
    if (target == null &&
        context.session.results[DeviceTestId.bleDiscovery]!.status ==
            DeviceTestStatus.passed) {
      try {
        target = await discoverTarget(context, secrets: secrets);
      } on BleDiscoveryException catch (error) {
        return TestCaseOutcome.failed(
          'BLE rediscovery after resume failed with ${error.code.wireName}.',
        );
      } on MissingDiscoveryTargetException {
        return TestCaseOutcome.failed(
          'The commissionee was not rediscovered after resume.',
        );
      } on TimeoutException {
        return TestCaseOutcome.failed(
          'BLE rediscovery after resume timed out.',
        );
      }
    }
    if (target == null) {
      return TestCaseOutcome.notRun(
        'A discovered BLE commissionee is required before commissioning.',
      );
    }
    final identity =
        context.execution.identity ??
        await ensureIdentity(context, purpose: ControllerIdentityPurpose.main);

    final timeout = context.timeoutFor(id);
    try {
      final result = await commissionTarget(
        context,
        target: target,
        identity: identity,
        secrets: secrets,
        timeout: timeout,
      );
      if (!result.succeeded) {
        return TestCaseOutcome.failed(
          'Commissioning returned error code ${result.errorCode}.',
        );
      }
      final nodeId = result.nodeId ?? context.targetNodeId;
      final transport = result.networkTransport ?? secrets.transport;
      await context.updateExecution((execution) {
        execution.nodeId = nodeId;
        execution.networkTransport = transport;
      });
      return TestCaseOutcome.passed(
        notes: 'Commissioning completed with error code 0 over BLE.',
      );
    } on CommissioningException catch (error) {
      return TestCaseOutcome.failed(
        'Commissioning failed with ${error.code.wireName}'
        '${error.errorCode == null ? '' : ' (code ${error.errorCode})'}.',
      );
    } on TimeoutException {
      return TestCaseOutcome.failed(
        'Commissioning timed out after ${timeoutLabel(timeout)}.',
      );
    }
  }
}
