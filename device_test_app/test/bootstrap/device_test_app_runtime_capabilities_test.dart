import 'package:flutter_matter_device_test_app/src/agent/agent_command_handler.dart';
import 'package:flutter_matter_device_test_app/src/bootstrap/device_test_app_runtime.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('advertised bridge capabilities cover every routed command', () {
    expect(
      DeviceTestAppRuntime.agentCapabilities,
      containsAll(AgentCommandNames.all),
    );
    expect(
      DeviceTestAppRuntime.agentCapabilities,
      containsAll(<String>['state', 'event', 'command', 'report']),
    );
  });
}
