import 'package:flutter_matter_device_test_app/src/agent/protocol.dart';
import 'package:flutter_matter_device_test_app/src/application/runner_state.dart';
import 'package:flutter_matter_device_test_app/src/bootstrap/agent_bridge_projection.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/presentation/presentation.dart';
import 'package:flutter_test/flutter_test.dart';

import '../presentation/support/presentation_fixtures.dart';

void main() {
  const projection = AgentBridgeProjection();

  group('AgentBridgeProjection state', () {
    test('projects idle state', () {
      final payload = projection.projectState(const DeviceTestUiState());

      expect(payload.status, AgentRunStatus.idle);
      expect(payload.mode, AgentRunMode.none);
      expect(payload.completedTests, 0);
      expect(payload.totalTests, 0);
    });

    test('projects a running full run', () {
      final payload = projection.projectState(
        runnerState(run: activeRun(profile: TestProfile.full)),
      );

      expect(payload.status, AgentRunStatus.running);
      expect(payload.mode, AgentRunMode.full);
      expect(payload.runId, 'run-fixture');
      expect(payload.currentTestId, DeviceTestId.commissioning.wireName);
      expect(payload.details['phase'], RunPhase.testing.wireName);
      expect(payload.details['screen'], DeviceTestScreen.runner.name);
    });

    test('projects prompt actor and sanitized message', () {
      final payload = projection.projectState(
        runnerState(activePrompt: prompt(actor: RequiredActor.agentAndroid)),
      );

      expect(payload.status, AgentRunStatus.waitingForAgentAndroid);
      expect(payload.prompt?.channel, AgentPromptChannel.agentAndroid);
      expect(payload.prompt?.testId, DeviceTestId.onoffInvoke.wireName);
      expect(payload.message, isNot(contains('password')));
    });

    test('passes only when all tests are terminal without failures', () {
      final statuses = <DeviceTestId, DeviceTestStatus>{
        for (final testId in TestProfile.full.testIds)
          testId: DeviceTestStatus.passed,
      };
      final payload = projection.projectState(
        runnerState(
          run: activeRun(
            profile: TestProfile.full,
            phase: RunPhase.completed,
            statuses: statuses,
            currentTestId: null,
          ),
        ),
      );

      expect(payload.status, AgentRunStatus.passed);
      expect(payload.completedTests, 11);
      expect(payload.totalTests, 11);
    });

    test('keeps a P0 not-run result out of the passed state', () {
      final statuses = <DeviceTestId, DeviceTestStatus>{
        for (final testId in TestProfile.full.testIds)
          testId: testId.priority == DeviceTestPriority.p0
              ? DeviceTestStatus.notRun
              : DeviceTestStatus.passed,
      };
      final payload = projection.projectState(
        runnerState(
          run: activeRun(
            profile: TestProfile.full,
            phase: RunPhase.completed,
            statuses: statuses,
            currentTestId: null,
          ),
        ),
      );

      expect(payload.status, AgentRunStatus.notRun);
    });

    test('drops secret-looking state messages', () {
      final payload = projection.projectState(
        runnerState(
          run: activeRun(currentInstruction: 'password=correct-horse-battery'),
        ),
      );

      expect(payload.message, isNull);
    });
  });

  group('AgentBridgeProjection event', () {
    test('maps failure severity and removes unapproved data', () {
      final event = RunnerEvent(
        sequence: 2,
        type: RunnerEventType.testFailed,
        timestamp: DateTime.utc(2026, 11, 12),
        message: 'Fabric removal failed.',
        runId: 'run-fixture',
        testId: DeviceTestId.removeFabricUi,
        data: const <String, Object?>{
          'stage': 'remove',
          'password': 'must-not-leak',
          'raw_log': 'must-not-leak',
        },
      );

      final payload = projection.projectEvent(event);

      expect(payload.severity, AgentEventSeverity.error);
      expect(payload.testId, DeviceTestId.removeFabricUi.wireName);
      expect(payload.data, <String, Object?>{'stage': 'remove'});
    });

    test('drops secret-looking event messages', () {
      final event = RunnerEvent(
        sequence: 3,
        type: RunnerEventType.runStarted,
        timestamp: DateTime.utc(2026, 11, 12),
        message: 'SSID: private-network',
      );

      final payload = projection.projectEvent(event);

      expect(payload.message, 'Device test event.');
    });
  });
}
