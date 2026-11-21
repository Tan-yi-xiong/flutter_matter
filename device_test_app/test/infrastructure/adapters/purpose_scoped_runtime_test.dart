import 'package:flutter_matter_device_test_app/src/application/ports.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/adapters/adapters.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test(
    'restart replaces the runtime and load reuses the replacement',
    () async {
      final provider = FlutterMatterControllerRuntimeProvider();
      addTearDown(provider.close);
      final request = ControllerIdentityRequest(
        runId: 'run-1',
        purpose: ControllerIdentityPurpose.main,
        platform: ControllerPlatform.android,
      );

      final original = await provider.load(request);
      final restarted = await provider.restart(request);
      final loaded = await provider.load(request);

      expect(restarted, isNot(same(original)));
      expect(restarted.controller, isNot(same(original.controller)));
      expect(restarted.identityStore, isNot(same(original.identityStore)));
      expect(loaded, same(restarted));
    },
  );
}
