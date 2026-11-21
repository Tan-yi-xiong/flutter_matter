import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  late FlutterMatterPlatform originalPlatform;
  late _RecordingMatterPlatform platform;

  setUp(() {
    originalPlatform = FlutterMatterPlatform.instance;
    ChipDeviceControllerManager.instance.resetForTesting();
    platform = _RecordingMatterPlatform();
    FlutterMatterPlatform.instance = platform;
  });

  tearDown(() {
    ChipDeviceControllerManager.instance.resetForTesting();
    FlutterMatterPlatform.instance = originalPlatform;
  });

  test('same fabric identity shares one handle until the final release',
      () async {
    final manager = ChipDeviceControllerManager.instance;
    final params = ControllerParams(
      fabricId: 10,
      rootCertificate: Uint8List.fromList(<int>[1, 2, 3]),
    );

    final first = await manager.acquire(params);
    final second = await manager.acquire(
      ControllerParams(
        fabricId: 10,
        rootCertificate: Uint8List.fromList(<int>[1, 2, 3]),
      ),
    );

    expect(second, same(first));
    expect(manager.activeController, same(first));
    expect(manager.hasActiveController, isTrue);
    expect(platform.controllerCalls, <String>['new']);

    await manager.release(first);
    expect(first.isRunning, isTrue);
    expect(platform.controllerCalls, <String>['new']);

    await second.deleteDeviceController();
    await first.closed;
    expect(first.isRunning, isFalse);
    expect(manager.activeController, isNull);
    expect(manager.hasActiveController, isFalse);
    expect(platform.controllerCalls, <String>['new', 'deleteDeviceController']);
  });

  test('switching invalidates the old handle before native deletion', () async {
    final manager = ChipDeviceControllerManager.instance;
    final oldController = await manager.acquire(
      ControllerParams(
        fabricId: 10,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );
    final deleteStarted = Completer<void>();
    final allowDelete = Completer<void>();
    platform.onDelete = () async {
      deleteStarted.complete();
      await allowDelete.future;
    };

    final switchFuture = manager.acquire(
      ControllerParams(
        fabricId: 11,
        rootCertificate: Uint8List.fromList(<int>[2]),
      ),
    );
    await deleteStarted.future;

    var oldClosed = false;
    unawaited(oldController.closed.then((_) => oldClosed = true));
    await Future<void>.delayed(Duration.zero);
    expect(oldClosed, isTrue);
    expect(manager.activeController, isNull);
    expect(manager.hasActiveController, isFalse);
    expect(platform.controllerCalls, <String>['new', 'deleteDeviceController']);

    allowDelete.complete();
    final replacement = await switchFuture;
    expect(replacement, isNot(same(oldController)));
    expect(manager.activeController, same(replacement));
    expect(platform.controllerCalls,
        <String>['new', 'deleteDeviceController', 'new']);
  });

  test('concurrent acquires are serialized in request order', () async {
    final manager = ChipDeviceControllerManager.instance;
    final firstNewStarted = Completer<void>();
    final allowFirstNew = Completer<void>();
    platform.onNew = () async {
      if (!firstNewStarted.isCompleted) {
        firstNewStarted.complete();
        await allowFirstNew.future;
      }
    };

    final firstAcquire = manager.acquire(
      ControllerParams(
        fabricId: 20,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );
    await firstNewStarted.future;
    final secondAcquire = manager.acquire(
      ControllerParams(
        fabricId: 21,
        rootCertificate: Uint8List.fromList(<int>[2]),
      ),
    );

    expect(platform.controllerCalls, <String>['new']);
    expect(manager.activeController, isNull);
    expect(manager.hasActiveController, isFalse);
    allowFirstNew.complete();
    final controllers = await Future.wait(<Future<ChipDeviceController>>[
      firstAcquire,
      secondAcquire,
    ]);

    expect(controllers[0], isNot(same(controllers[1])));
    expect(controllers[0].isRunning, isFalse);
    expect(controllers[1].isRunning, isTrue);
    expect(platform.controllerCalls,
        <String>['new', 'deleteDeviceController', 'new']);
  });

  test('acquiring a previous identity after a switch creates a new handle',
      () async {
    final manager = ChipDeviceControllerManager.instance;
    final firstA = await manager.acquire(
      ControllerParams(
        fabricId: 25,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );
    final controllerB = await manager.acquire(
      ControllerParams(
        fabricId: 26,
        rootCertificate: Uint8List.fromList(<int>[2]),
      ),
    );
    final secondA = await manager.acquire(
      ControllerParams(
        fabricId: 25,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );

    expect(secondA, isNot(same(firstA)));
    expect(firstA.isRunning, isFalse);
    expect(controllerB.isRunning, isFalse);
    expect(manager.activeController, same(secondA));
    expect(platform.controllerCalls, <String>[
      'new',
      'deleteDeviceController',
      'new',
      'deleteDeviceController',
      'new',
    ]);
  });

  test('release underflow and repeat close are rejected', () async {
    final manager = ChipDeviceControllerManager.instance;
    final controller = await manager.acquire(
      ControllerParams(
        fabricId: 27,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );

    await controller.close();
    await expectLater(
      manager.release(controller),
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.closed)),
    );
    await expectLater(
      controller.close(),
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.closed)),
    );
    expect(platform.controllerCalls, <String>['new', 'deleteDeviceController']);
  });

  test('closeAll queued during a switch closes the replacement', () async {
    final manager = ChipDeviceControllerManager.instance;
    await manager.acquire(
      ControllerParams(
        fabricId: 28,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );
    final deleteStarted = Completer<void>();
    final allowDelete = Completer<void>();
    platform.onDelete = () async {
      if (!deleteStarted.isCompleted) {
        deleteStarted.complete();
      }
      await allowDelete.future;
    };

    final switchFuture = manager.acquire(
      ControllerParams(
        fabricId: 29,
        rootCertificate: Uint8List.fromList(<int>[2]),
      ),
    );
    await deleteStarted.future;
    final closeAllFuture = manager.closeAll();
    var closeAllCompleted = false;
    unawaited(closeAllFuture.then((_) => closeAllCompleted = true));
    await Future<void>.delayed(Duration.zero);
    expect(closeAllCompleted, isFalse);

    allowDelete.complete();
    final replacement = await switchFuture;
    await closeAllFuture;
    await replacement.closed;
    expect(manager.activeController, isNull);
    expect(manager.hasActiveController, isFalse);
    expect(platform.controllerCalls, <String>[
      'new',
      'deleteDeviceController',
      'new',
      'deleteDeviceController',
    ]);
  });

  test('destroy before a queued acquire forces cleanup and recreation',
      () async {
    final manager = ChipDeviceControllerManager.instance;
    final params = ControllerParams(
      fabricId: 32,
      rootCertificate: Uint8List.fromList(<int>[1]),
    );
    final original = await manager.acquire(params);

    final queuedAcquire = manager.acquire(params);
    original.destroy();
    expect(platform.controllerCalls, <String>['new']);

    final replacement = await queuedAcquire;
    expect(replacement, isNot(same(original)));
    expect(original.isRunning, isFalse);
    expect(replacement.isRunning, isTrue);
    expect(platform.controllerCalls,
        <String>['new', 'deleteDeviceController', 'new']);
  });

  test('destroy invalidates a close that was queued before it', () async {
    final manager = ChipDeviceControllerManager.instance;
    final params = ControllerParams(
      fabricId: 37,
      rootCertificate: Uint8List.fromList(<int>[1]),
    );
    final controller = await manager.acquire(params);

    final queuedClose = controller.close();
    controller.destroy();
    await expectLater(
      queuedClose,
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.closed)),
    );
    expect(platform.controllerCalls, <String>['new']);

    final replacement = await manager.acquire(params);
    expect(replacement, isNot(same(controller)));
    expect(platform.controllerCalls,
        <String>['new', 'deleteDeviceController', 'new']);
  });

  test('superseded handles reject new requests', () async {
    final manager = ChipDeviceControllerManager.instance;
    final oldController = await manager.acquire(
      ControllerParams(
        fabricId: 30,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );
    await manager.acquire(
      ControllerParams(
        fabricId: 31,
        rootCertificate: Uint8List.fromList(<int>[2]),
      ),
    );

    await expectLater(
      oldController.releaseConnectContext(1),
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.closed)),
    );
  });

  test('closed handles reject callback registration before dispatch', () async {
    final manager = ChipDeviceControllerManager.instance;
    final controller = await manager.acquire(
      ControllerParams(
        fabricId: 33,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );
    await controller.close();
    final callsAfterClose = List<String>.of(platform.controllerCalls);

    final invokeFuture = controller.invoke(
      _TestInvokeCallback(),
      1,
      InvokeElement.create(1, 2, 3, null, null),
    );
    await expectLater(
      invokeFuture,
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.closed)),
    );
    expect(platform.controllerCalls, callsAfterClose);
  });

  test('failed initial new leaves the manager reusable', () async {
    final manager = ChipDeviceControllerManager.instance;
    platform.failNextNewCount = 1;
    final params = ControllerParams(
      fabricId: 34,
      rootCertificate: Uint8List.fromList(<int>[1]),
    );

    await expectLater(
      manager.acquire(params),
      throwsA(isA<Exception>()),
    );
    expect(manager.activeController, isNull);
    expect(manager.hasActiveController, isFalse);

    final controller = await manager.acquire(params);
    expect(controller.isRunning, isTrue);
    expect(platform.controllerCalls, <String>['new', 'new']);
  });

  test('successful new without a handle poisons native state', () async {
    final manager = ChipDeviceControllerManager.instance;
    platform.returnMissingHandleOnNextNew = true;

    await expectLater(
      manager.acquire(
        ControllerParams(
          fabricId: 35,
          rootCertificate: Uint8List.fromList(<int>[1]),
        ),
      ),
      throwsA(
          _isLifecycleFailure(ControllerLifecycleFailure.nativeStateConflict)),
    );
    expect(manager.activeController, isNull);
    expect(manager.hasActiveController, isFalse);
    await expectLater(
      manager.acquire(
        ControllerParams(
          fabricId: 36,
          rootCertificate: Uint8List.fromList(<int>[2]),
        ),
      ),
      throwsA(
          _isLifecycleFailure(ControllerLifecycleFailure.nativeStateConflict)),
    );
  });

  test('destroy is local-only and the next acquire cleans up before new',
      () async {
    final manager = ChipDeviceControllerManager.instance;
    final params = ControllerParams(
      fabricId: 40,
      rootCertificate: Uint8List.fromList(<int>[1]),
    );
    final oldController = await manager.acquire(params);

    oldController.destroy();
    await oldController.closed;
    expect(oldController.isRunning, isFalse);
    expect(manager.activeController, isNull);
    expect(platform.controllerCalls, <String>['new']);

    final replacement = await manager.acquire(params);
    expect(replacement, isNot(same(oldController)));
    expect(platform.controllerCalls,
        <String>['new', 'deleteDeviceController', 'new']);

    await manager.closeAll();
    expect(platform.controllerCalls, <String>[
      'new',
      'deleteDeviceController',
      'new',
      'deleteDeviceController',
    ]);
  });

  test('shutdown failure poisons the manager against later creation', () async {
    final manager = ChipDeviceControllerManager.instance;
    platform.failDelete = true;
    final controller = await manager.acquire(
      ControllerParams(
        fabricId: 50,
        rootCertificate: Uint8List.fromList(<int>[1]),
      ),
    );

    await expectLater(
      controller.close(),
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.shutdownFailed)),
    );
    expect(controller.isRunning, isFalse);
    expect(manager.hasActiveController, isFalse);

    await expectLater(
      manager.acquire(
        ControllerParams(
          fabricId: 51,
          rootCertificate: Uint8List.fromList(<int>[2]),
        ),
      ),
      throwsA(_isLifecycleFailure(ControllerLifecycleFailure.shutdownFailed)),
    );
    expect(platform.controllerCalls, <String>['new', 'deleteDeviceController']);
  });
}

Matcher _isLifecycleFailure(ControllerLifecycleFailure reason) {
  return isA<ControllerLifecycleException>()
      .having((error) => error.reason, 'reason', reason);
}

class _TestInvokeCallback implements InvokeCallback {
  @override
  void onError(Exception e) {}

  @override
  void onDone() {}

  @override
  void onResponse(InvokeElement invokeElement, int successCode) {}
}

class _RecordingMatterPlatform extends FlutterMatterPlatform {
  final List<String> controllerCalls = <String>[];
  final Set<MethodCallHandler> handlers = <MethodCallHandler>{};
  Future<void> Function()? onNew;
  Future<void> Function()? onDelete;
  bool failDelete = false;
  int failNextNewCount = 0;
  bool returnMissingHandleOnNextNew = false;
  int _nextHandle = 0;

  @override
  Future<PlatformResult> requestPlatform(RequestPlatformParams params) async {
    final path = Uri.parse(params.methodName).pathSegments.last;
    if (path == 'new') {
      controllerCalls.add(path);
      await onNew?.call();
      if (failNextNewCount > 0) {
        failNextNewCount--;
        return PlatformResult(code: 7, jsonData: <String, dynamic>{});
      }
      if (returnMissingHandleOnNextNew) {
        returnMissingHandleOnNextNew = false;
        return PlatformResult(code: 0, jsonData: <String, dynamic>{});
      }
      _nextHandle++;
      return PlatformResult(
        code: 0,
        jsonData: <String, dynamic>{'handle': 'controller-$_nextHandle'},
      );
    }
    if (path == 'deleteDeviceController') {
      controllerCalls.add(path);
      await onDelete?.call();
      if (failDelete) {
        return PlatformResult(code: 7, jsonData: <String, dynamic>{});
      }
    }
    return PlatformResult(code: 0, jsonData: <String, dynamic>{});
  }

  @override
  void addHandler(MethodCallHandler handler) {
    handlers.add(handler);
  }

  @override
  void removeHandler(MethodCallHandler handler) {
    handlers.remove(handler);
  }
}
