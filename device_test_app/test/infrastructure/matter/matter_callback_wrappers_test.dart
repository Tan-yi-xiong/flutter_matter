import 'dart:async';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('generic timeout wrapper throws a typed timeout error', () async {
    final never = Completer<void>();

    await expectLater(
      withMatterTimeout<void>(
        future: never.future,
        timeout: const Duration(milliseconds: 10),
        operation: 'Test callback',
      ),
      throwsA(
        isA<MatterTimeoutException>().having(
          (error) => error.code,
          'code',
          MatterFailureCode.callbackTimeout,
        ),
      ),
    );
  });

  test('commissioning listener times out explicitly', () async {
    final listener = MatterCommissioningListener(fallbackNodeId: 10);

    await expectLater(
      listener.wait(const Duration(milliseconds: 10)),
      throwsA(isA<MatterTimeoutException>()),
    );
    listener.fail(StateError('close test listener'));
  });

  test('invoke collector times out instead of hanging', () async {
    final collector = MatterInvokeCollector();

    await expectLater(
      collector.wait(const Duration(milliseconds: 10)),
      throwsA(isA<MatterTimeoutException>()),
    );
  });

  test('invoke collector stops waiting on a response', () async {
    final collector = MatterInvokeCollector();
    collector.onResponse(InvokeElement.create(1, 6, 1, null, null), 0);

    final result = await collector.wait(const Duration(milliseconds: 100));
    expect(result.successCode, 0);
    expect(result.isSuccess, isTrue);
  });

  test('read collector times out when the callback never reports', () async {
    final collector = MatterReadCollector(
      endpointId: 0,
      clusterId: 0x28,
      attributeId: 0x05,
    );

    await expectLater(
      collector.wait(const Duration(milliseconds: 10)),
      throwsA(isA<MatterTimeoutException>()),
    );
  });
}
