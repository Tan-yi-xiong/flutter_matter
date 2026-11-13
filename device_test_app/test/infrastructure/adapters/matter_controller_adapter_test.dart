import 'dart:async';

import 'package:flutter_matter_device_test_app/src/application/ports.dart';
import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/adapters/adapters.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';
import 'package:flutter_test/flutter_test.dart';

import 'support/fakes.dart';

void main() {
  late FakeRuntimeProvider runtimeProvider;
  late MatterControllerAdapter adapter;

  setUp(() {
    runtimeProvider = FakeRuntimeProvider();
    adapter = MatterControllerAdapter(
      runtimeProvider: runtimeProvider,
      platform: ControllerPlatform.android,
    );
  });

  group('identity and direct commissioning', () {
    test(
      'keeps an identity stable across loads and separated by purpose',
      () async {
        final request = ControllerIdentityRequest(
          runId: 'run-1',
          purpose: ControllerIdentityPurpose.main,
          platform: ControllerPlatform.android,
        );
        final first = await adapter.loadOrCreate(request);
        final second = await adapter.loadOrCreate(request);
        final negative = await adapter.loadOrCreate(
          ControllerIdentityRequest(
            runId: 'run-1',
            purpose: ControllerIdentityPurpose.invalidSetupPasscode,
            platform: ControllerPlatform.android,
          ),
        );

        expect(second.opaqueId, first.opaqueId);
        expect(negative.opaqueId, isNot(first.opaqueId));
        expect(
          negative.purpose,
          ControllerIdentityPurpose.invalidSetupPasscode,
        );
      },
    );

    test(
      'reset clears only the requested purpose and invalidates its handle',
      () async {
        final mainRequest = ControllerIdentityRequest(
          runId: 'run-1',
          purpose: ControllerIdentityPurpose.main,
          platform: ControllerPlatform.android,
        );
        final negativeRequest = ControllerIdentityRequest(
          runId: 'run-1',
          purpose: ControllerIdentityPurpose.invalidSetupPasscode,
          platform: ControllerPlatform.android,
        );
        final mainBefore = await adapter.loadOrCreate(mainRequest);
        final negativeBefore = await adapter.loadOrCreate(negativeRequest);
        final mainController = runtimeProvider.controllerFor(
          ControllerIdentityPurpose.main,
        );
        final mainStore = runtimeProvider.identityFor(
          ControllerIdentityPurpose.main,
        );

        await adapter.reset(mainRequest);

        expect(mainController.closeCount, 1);
        expect(mainStore.clearCount, 1);
        final mainAfter = await adapter.loadOrCreate(mainRequest);
        final negativeAfter = await adapter.loadOrCreate(negativeRequest);
        expect(mainAfter.opaqueId, isNot(mainBefore.opaqueId));
        expect(negativeAfter.opaqueId, negativeBefore.opaqueId);
      },
    );

    test(
      'maps a Wi-Fi commissioning request to the direct Matter SDK request',
      () async {
        final identity = await _identity(adapter);
        final result = await adapter.commission(
          CommissioningRequest(
            identity: identity,
            targetNodeId: 42,
            onboardingPayload: 'MT:PAYLOAD',
            setupPinCode: 20202021,
            network: const WifiProvisioningSecret(
              ssid: 'Lab Wi-Fi',
              password: 'secret',
            ),
            timeout: const Duration(seconds: 3),
          ),
        );

        final request = runtimeProvider
            .controllerFor(ControllerIdentityPurpose.main)
            .commissionRequests
            .single;
        expect(result.succeeded, isTrue);
        expect(result.nodeId, 42);
        expect(result.networkTransport, NetworkTransport.wifi);
        expect(request.onboardingPayload, 'MT:PAYLOAD');
        expect(request.setupPinCode, 20202021);
        expect(request.nodeId, 42);
        expect(request.timeout, const Duration(seconds: 3));
        expect(request.networkCredentials, isA<MatterWifiNetworkCredentials>());
        expect(
          (request.networkCredentials as MatterWifiNetworkCredentials)
              .credentials
              .ssid,
          'Lab Wi-Fi',
        );
        expect(
          (request.networkCredentials as MatterWifiNetworkCredentials)
              .credentials
              .password,
          'secret',
        );
      },
    );

    test(
      'maps Thread credentials for direct commissioning without discovery',
      () async {
        final identity = await _identity(adapter);
        final result = await adapter.commission(
          CommissioningRequest(
            identity: identity,
            targetNodeId: 7,
            onboardingPayload: 'MT:THREAD',
            setupPinCode: 20202021,
            network: ThreadProvisioningSecret(
              operationalDataset: <int>[1, 2, 3, 4],
            ),
            timeout: const Duration(seconds: 5),
          ),
        );

        final request = runtimeProvider
            .controllerFor(ControllerIdentityPurpose.main)
            .commissionRequests
            .single;
        expect(result.succeeded, isTrue);
        expect(result.networkTransport, NetworkTransport.thread);
        expect(request.onboardingPayload, 'MT:THREAD');
        expect(request.setupPinCode, 20202021);
        expect(request.nodeId, 7);
        expect(request.timeout, const Duration(seconds: 5));
        final credentials =
            request.networkCredentials as MatterThreadNetworkCredentials;
        expect(credentials.credentials.operationalDataset, <int>[1, 2, 3, 4]);
      },
    );

    test('preserves a non-zero commissioning failure code', () async {
      final identity = await _identity(adapter);
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      controller.commissionHandler = (_) async {
        throw MatterException(
          MatterFailureCode.commissioningFailed,
          'Commissioning failed with error code 17',
        );
      };

      await expectLater(
        adapter.commission(_commissionRequest(identity)),
        throwsA(
          isA<CommissioningException>()
              .having(
                (error) => error.code,
                'code',
                CommissioningFailureCode.commissioningFailed,
              )
              .having((error) => error.errorCode, 'errorCode', 17),
        ),
      );
    });

    test('maps a commissioning timeout to the timeout failure code', () async {
      final identity = await _identity(adapter);
      runtimeProvider
          .controllerFor(ControllerIdentityPurpose.main)
          .commissionHandler = (_) async {
        throw MatterTimeoutException('Matter commissioning');
      };

      await expectLater(
        adapter.commission(_commissionRequest(identity)),
        throwsA(
          isA<CommissioningException>().having(
            (error) => error.code,
            'code',
            CommissioningFailureCode.timeout,
          ),
        ),
      );
    });

    test('maps a platform permission error to permission denied', () async {
      final identity = await _identity(adapter);
      runtimeProvider
          .controllerFor(ControllerIdentityPurpose.main)
          .commissionHandler = (_) async {
        throw MatterException(
          MatterFailureCode.pairingFailed,
          'Pairing failed',
          permissionPlatformException(),
        );
      };

      await expectLater(
        adapter.commission(_commissionRequest(identity)),
        throwsA(
          isA<CommissioningException>().having(
            (error) => error.code,
            'code',
            CommissioningFailureCode.permissionDenied,
          ),
        ),
      );
    });

    test('maps an invalid setup payload to the invalid setup code', () async {
      final identity = await _identity(adapter);
      runtimeProvider
          .controllerFor(ControllerIdentityPurpose.main)
          .commissionHandler = (_) async {
        throw const FormatException('Unrecognized onboarding payload');
      };

      await expectLater(
        adapter.commission(_commissionRequest(identity)),
        throwsA(
          isA<CommissioningException>().having(
            (error) => error.code,
            'code',
            CommissioningFailureCode.invalidSetupCode,
          ),
        ),
      );
    });
  });

  group('operational connection and OnOff', () {
    test(
      'preserves opaque connection handles and releases the context',
      () async {
        final identity = await _identity(adapter);
        final lease = await adapter.connect(
          identity: identity,
          nodeId: 42,
          timeout: const Duration(seconds: 2),
        );

        expect(lease.opaqueId, isNotEmpty);
        expect(lease.isValid, isTrue);
        expect(
          runtimeProvider
              .controllerFor(ControllerIdentityPurpose.main)
              .connectRequests
              .single
              .nodeId,
          42,
        );

        await adapter.disconnect(lease);
        expect(
          runtimeProvider
              .controllerFor(ControllerIdentityPurpose.main)
              .releasedConnections,
          hasLength(1),
        );
      },
    );

    test('reads before and after an OnOff invocation', () async {
      final identity = await _identity(adapter);
      final lease = await adapter.connect(
        identity: identity,
        nodeId: 42,
        timeout: const Duration(seconds: 2),
      );
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      final states = <bool>[true, false];
      controller.readHandler = (request) async {
        return matterBoolValue(request, states.removeAt(0));
      };

      final result = await adapter.invoke(
        connection: lease,
        command: OnOffCommand.toggle,
        timeout: const Duration(seconds: 2),
      );

      expect(result.previousState, OnOffState.on);
      expect(result.currentState, OnOffState.off);
      expect(result.changed, isTrue);
      expect(controller.readRequests, hasLength(2));
      expect(
        controller.invokeRequests.single.command,
        MatterOnOffCommand.toggle,
      );
      expect(controller.invokeRequests.single.nodeId, 42);
    });

    test(
      'exposes subscription initial state, updates, and cancellation',
      () async {
        final identity = await _identity(adapter);
        final lease = await adapter.connect(
          identity: identity,
          nodeId: 42,
          timeout: const Duration(seconds: 2),
        );
        final controller = runtimeProvider.controllerFor(
          ControllerIdentityPurpose.main,
        );
        final subscription = FakeMatterSubscription();
        controller.readHandler = (request) async {
          return matterBoolValue(request, true);
        };
        controller.subscribeHandler = () async => subscription;

        final active = await adapter.subscribe(
          connection: lease,
          timeout: const Duration(seconds: 2),
        );
        expect(active.initialState, OnOffState.on);

        final update = expectLater(active.updates, emits(OnOffState.off));
        subscription.emit(
          matterBoolValue(
            const MatterReadAttributeRequest(
              nodeId: 42,
              clusterId: matterOnOffClusterId,
              attributeId: matterOnOffAttributeId,
              endpointId: 1,
            ),
            false,
          ),
        );
        await update;
        await active.cancel();
        expect(subscription.closeCount, 1);
      },
    );

    test('shares concurrent subscription cancellation cleanup', () async {
      final identity = await _identity(adapter);
      final lease = await adapter.connect(
        identity: identity,
        nodeId: 42,
        timeout: const Duration(seconds: 2),
      );
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      final subscription = FakeMatterSubscription();
      controller.readHandler = (request) async {
        return matterBoolValue(request, true);
      };
      controller.subscribeHandler = () async => subscription;

      final active = await adapter.subscribe(
        connection: lease,
        timeout: const Duration(seconds: 2),
      );
      final closeGate = Completer<void>();
      subscription.closeDelay = () => closeGate.future;
      final firstCancel = active.cancel();
      var secondCancelCompleted = false;
      final secondCancel = active.cancel().then((_) {
        secondCancelCompleted = true;
      });

      await Future<void>.delayed(Duration.zero);
      expect(secondCancelCompleted, isFalse);

      closeGate.complete();
      await secondCancel;
      expect(secondCancelCompleted, isTrue);
      expect(subscription.closeCount, 1);
      expect(subscription.closeCompletionCount, 1);
      await firstCancel;
      expect(subscription.closeCount, 1);
    });

    test('disconnect cancels active subscriptions before release', () async {
      final identity = await _identity(adapter);
      final lease = await adapter.connect(
        identity: identity,
        nodeId: 42,
        timeout: const Duration(seconds: 2),
      );
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      final subscription = FakeMatterSubscription();
      controller.readHandler = (request) async {
        return matterBoolValue(request, true);
      };
      controller.subscribeHandler = () async => subscription;

      final active = await adapter.subscribe(
        connection: lease,
        timeout: const Duration(seconds: 2),
      );
      await adapter.disconnect(lease);

      expect(subscription.closeCount, 1);
      expect(subscription.closeCompletionCount, 1);
      expect(controller.releasedConnections, hasLength(1));
      await expectLater(active.updates, emitsDone);
      await active.cancel();
      expect(subscription.closeCount, 1);
    });

    test(
      'reconnect cancels subscriptions for the replaced connection',
      () async {
        final identity = await _identity(adapter);
        final lease = await adapter.connect(
          identity: identity,
          nodeId: 42,
          timeout: const Duration(seconds: 2),
        );
        final controller = runtimeProvider.controllerFor(
          ControllerIdentityPurpose.main,
        );
        final subscription = FakeMatterSubscription();
        controller.readHandler = (request) async {
          return matterBoolValue(request, true);
        };
        controller.subscribeHandler = () async => subscription;

        final active = await adapter.subscribe(
          connection: lease,
          timeout: const Duration(seconds: 2),
        );
        final replacement = await adapter.reconnect(
          identity: identity,
          nodeId: 42,
          timeout: const Duration(seconds: 2),
        );

        expect(subscription.closeCount, 1);
        expect(subscription.closeCompletionCount, 1);
        expect(controller.connectRequests, hasLength(2));
        expect(controller.releasedConnections, hasLength(1));
        expect(replacement.opaqueId, isNot(lease.opaqueId));
        await active.cancel();
        expect(subscription.closeCount, 1);
      },
    );

    test('maps a stale connection to an OnOff connection failure', () async {
      await _identity(adapter);
      final stale = OperationalConnectionLease(
        opaqueId: 'stale-connection',
        nodeId: 42,
        isValid: false,
      );

      await expectLater(
        adapter.readState(
          connection: stale,
          timeout: const Duration(seconds: 2),
        ),
        throwsA(
          isA<OnOffException>().having(
            (error) => error.code,
            'code',
            OnOffFailureCode.notConnected,
          ),
        ),
      );
    });

    test('maps rejected OnOff invocation results', () async {
      final identity = await _identity(adapter);
      final lease = await adapter.connect(
        identity: identity,
        nodeId: 42,
        timeout: const Duration(seconds: 2),
      );
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      controller.readHandler = (request) async {
        return matterBoolValue(request, false);
      };
      controller.invokeHandler = (_) async {
        return MatterInvokeResult(successCode: 1);
      };

      await expectLater(
        adapter.invoke(
          connection: lease,
          command: OnOffCommand.on,
          timeout: const Duration(seconds: 2),
        ),
        throwsA(
          isA<OnOffException>().having(
            (error) => error.code,
            'code',
            OnOffFailureCode.invokeRejected,
          ),
        ),
      );
    });
  });

  group('NodeLabel and fabric', () {
    test('maps NodeLabel read and write operations', () async {
      final identity = await _identity(adapter);
      final lease = await adapter.connect(
        identity: identity,
        nodeId: 42,
        timeout: const Duration(seconds: 2),
      );
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      controller.nodeLabelReadHandler = (_, _) async => 'stored-label';

      expect(
        await adapter.read(
          connection: lease,
          timeout: const Duration(seconds: 2),
        ),
        'stored-label',
      );
      await adapter.write(
        connection: lease,
        value: 'new-label',
        timeout: const Duration(seconds: 2),
      );
      expect(controller.nodeLabelWriteRequests.single.label, 'new-label');
      expect(controller.nodeLabelWriteRequests.single.nodeId, 42);
    });

    test('inspects and removes the current fabric', () async {
      final identity = await _identity(adapter);
      final lease = await adapter.connect(
        identity: identity,
        nodeId: 42,
        timeout: const Duration(seconds: 2),
      );
      final controller = runtimeProvider.controllerFor(
        ControllerIdentityPurpose.main,
      );
      controller.readHandler = (request) async {
        return matterUnsignedValue(request, 3);
      };

      final status = await adapter.inspect(
        identity: identity,
        nodeId: 42,
        connection: lease,
        timeout: const Duration(seconds: 2),
      );
      expect(status.present, isTrue);
      expect(status.fabricIndex, 3);

      await adapter.remove(
        identity: identity,
        nodeId: 42,
        connection: lease,
        timeout: const Duration(seconds: 2),
      );
      expect(controller.removeFabricRequests.single.nodeId, 42);
      expect(
        controller.readRequests.single.clusterId,
        matterOperationalCredentialsClusterId,
      );
    });

    test(
      'maps a CurrentFabricIndex read failure to an inspection failure',
      () async {
        final identity = await _identity(adapter);
        final lease = await adapter.connect(
          identity: identity,
          nodeId: 42,
          timeout: const Duration(seconds: 2),
        );
        runtimeProvider
            .controllerFor(ControllerIdentityPurpose.main)
            .readHandler = (_) async {
          throw MatterException(
            MatterFailureCode.readFailed,
            'CurrentFabricIndex is unavailable',
          );
        };

        await expectLater(
          adapter.inspect(
            identity: identity,
            nodeId: 42,
            connection: lease,
            timeout: const Duration(seconds: 2),
          ),
          throwsA(
            isA<FabricException>().having(
              (error) => error.code,
              'code',
              FabricFailureCode.inspectFailed,
            ),
          ),
        );
      },
    );
  });
}

CommissioningRequest _commissionRequest(ControllerIdentity identity) {
  return CommissioningRequest(
    identity: identity,
    targetNodeId: 42,
    onboardingPayload: 'MT:PAYLOAD',
    setupPinCode: 20202021,
    network: const WifiProvisioningSecret(
      ssid: 'Lab Wi-Fi',
      password: 'secret',
    ),
    timeout: const Duration(seconds: 3),
  );
}

Future<ControllerIdentity> _identity(MatterControllerAdapter adapter) {
  return adapter.loadOrCreate(
    ControllerIdentityRequest(
      runId: 'run-1',
      purpose: ControllerIdentityPurpose.main,
      platform: ControllerPlatform.android,
    ),
  );
}
