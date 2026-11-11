import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/ble/matter_ble.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  final serviceId = Uint8List.fromList(
    List<int>.generate(16, (index) => index),
  );
  final characteristicId = Uint8List.fromList(
    List<int>.generate(16, (index) => 0xff - index),
  );

  test(
    'GATT writes forward the confirmation after returning to CHIP',
    () async {
      final session = _FakeGattSession();
      final bridge = _FakeBleLayerBridge();
      final delegate = MatterGattBleDelegate(
        session: session,
        bridge: bridge,
        operationTimeout: const Duration(milliseconds: 100),
      );
      final value = Uint8List.fromList([1, 2, 3]);

      final result = await delegate.sendWriteRequest(
        4,
        serviceId,
        characteristicId,
        value,
      );

      expect(result, isTrue);
      expect(session.writes, isEmpty);
      expect(bridge.writeConfirmations, isEmpty);

      await _flushAsyncWork();

      expect(session.writes, hasLength(1));
      expect(session.writes.single.value, value);
      expect(session.writes.single.withoutResponse, isFalse);
      expect(bridge.writeConfirmations, hasLength(1));
      expect(bridge.writeConfirmations.single.success, isTrue);
    },
  );

  test(
    'GATT write failures are reported after sendWriteRequest returns',
    () async {
      final session = _FakeGattSession(failWrites: true);
      final bridge = _FakeBleLayerBridge();
      final delegate = MatterGattBleDelegate(
        session: session,
        bridge: bridge,
        operationTimeout: const Duration(milliseconds: 100),
      );

      final result = await delegate.sendWriteRequest(
        4,
        serviceId,
        characteristicId,
        Uint8List.fromList([9]),
      );

      expect(result, isTrue);
      expect(bridge.writeConfirmations, isEmpty);

      await _flushAsyncWork();

      expect(bridge.writeConfirmations, hasLength(1));
      expect(bridge.writeConfirmations.single.success, isFalse);
    },
  );

  test('subscription enables notifications and forwards indications', () async {
    final session = _FakeGattSession();
    final bridge = _FakeBleLayerBridge();
    final delegate = MatterGattBleDelegate(
      session: session,
      bridge: bridge,
      operationTimeout: const Duration(milliseconds: 100),
    );

    final subscribed = await delegate.subscribeCharacteristic(
      4,
      serviceId,
      characteristicId,
    );
    session.emit(Uint8List.fromList([0xaa, 0xbb]));
    await Future<void>.delayed(Duration.zero);

    expect(subscribed, isTrue);
    expect(session.notificationStates.single, isTrue);
    expect(bridge.subscribeResults.single, isTrue);
    expect(bridge.indications, hasLength(1));
    expect(bridge.indications.single.value, [0xaa, 0xbb]);

    final unsubscribed = await delegate.unsubscribeCharacteristic(
      4,
      serviceId,
      characteristicId,
    );
    expect(unsubscribed, isTrue);
    expect(session.notificationStates.last, isFalse);
    expect(bridge.unsubscribeResults.single, isTrue);
  });

  test('MTU is read from the active GATT session', () async {
    final delegate = MatterGattBleDelegate(
      session: _FakeGattSession(),
      bridge: _FakeBleLayerBridge(),
      operationTimeout: const Duration(milliseconds: 100),
    );

    expect(await delegate.getMTU(4), 185);
  });
}

Future<void> _flushAsyncWork() async {
  await Future<void>.delayed(Duration.zero);
  await Future<void>.delayed(Duration.zero);
}

class _FakeGattSession implements MatterBleGattSession {
  _FakeGattSession({this.failWrites = false});

  final bool failWrites;
  final StreamController<Uint8List> _notifications =
      StreamController<Uint8List>.broadcast();
  final List<_WriteRecord> writes = [];
  final List<bool> notificationStates = [];

  @override
  String get deviceId => 'fake-device';

  @override
  int get mtu => 185;

  @override
  Future<void> setNotify({
    required String serviceUuid,
    required String characteristicUuid,
    required bool enabled,
    required Duration timeout,
  }) async {
    notificationStates.add(enabled);
  }

  @override
  Future<void> write({
    required String serviceUuid,
    required String characteristicUuid,
    required Uint8List value,
    required bool withoutResponse,
    required Duration timeout,
  }) async {
    if (failWrites) {
      throw StateError('write failed');
    }
    writes.add(
      _WriteRecord(
        value: Uint8List.fromList(value),
        withoutResponse: withoutResponse,
      ),
    );
  }

  @override
  Stream<Uint8List> notifications({
    required String serviceUuid,
    required String characteristicUuid,
  }) {
    return _notifications.stream;
  }

  @override
  Future<void> disconnect(Duration timeout) async {}

  void emit(Uint8List value) {
    _notifications.add(value);
  }
}

class _WriteRecord {
  _WriteRecord({required this.value, required this.withoutResponse});

  final Uint8List value;
  final bool withoutResponse;
}

class _FakeBleLayerBridge implements MatterBleLayerBridge {
  final List<_WriteConfirmation> writeConfirmations = [];
  final List<bool> subscribeResults = [];
  final List<bool> unsubscribeResults = [];
  final List<_Indication> indications = [];

  @override
  Future<void> setDelegate(BlePlatformDelegate? delegate) async {}

  @override
  Future<void> handleSubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) async {
    subscribeResults.add(success);
  }

  @override
  Future<void> handleUnsubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) async {
    unsubscribeResults.add(success);
  }

  @override
  Future<void> handleIndicationReceived({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required Uint8List value,
  }) async {
    indications.add(
      _Indication(
        serviceId: serviceId,
        characteristicId: characteristicId,
        value: Uint8List.fromList(value),
      ),
    );
  }

  @override
  Future<void> handleWriteConfirmation({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) async {
    writeConfirmations.add(
      _WriteConfirmation(
        serviceId: serviceId,
        characteristicId: characteristicId,
        success: success,
      ),
    );
  }

  @override
  Future<void> handleConnectionError({
    required Object? connection,
    required int errorCode,
  }) async {}
}

class _WriteConfirmation {
  _WriteConfirmation({
    required this.serviceId,
    required this.characteristicId,
    required this.success,
  });

  final Uint8List serviceId;
  final Uint8List characteristicId;
  final bool success;
}

class _Indication {
  _Indication({
    required this.serviceId,
    required this.characteristicId,
    required this.value,
  });

  final Uint8List serviceId;
  final Uint8List characteristicId;
  final Uint8List value;
}
