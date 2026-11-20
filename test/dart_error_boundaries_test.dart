import 'dart:async';
import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter/services.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/callback_handler.dart';
import 'package:flutter_matter/src/exception.dart';
import 'package:flutter_test/flutter_test.dart';

class _BoundaryCallbackPayload {}

class _BoundaryCallbackHandler<T> extends CallbackHandler<T> {
  String? methodName;
  dynamic arguments;

  @override
  dynamic onCallbackMethodCall(String methodName, dynamic arguments) {
    this.methodName = methodName;
    this.arguments = arguments;
    return 'handled';
  }
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  test('CallbackHandler rejects malformed callback paths with ArgumentError',
      () {
    final handler = _BoundaryCallbackHandler<_BoundaryCallbackPayload>();

    expect(handler.match('zgMatter://ignored', <String, dynamic>{}), isFalse);
    expect(handler.match('', <String, dynamic>{}), isFalse);
    expect(
      () => handler.call('zgMatter://ignored', <String, dynamic>{}),
      throwsArgumentError,
    );
    expect(
      () => handler.call('', <String, dynamic>{}),
      throwsArgumentError,
    );
  });

  group('cluster report completion', () {
    late MethodChannelFlutterMatter platform;
    late Completer<String> readRequest;
    late ChipDeviceController controller;
    late bool failRead;

    setUp(() async {
      platform = MethodChannelFlutterMatter();
      FlutterMatterPlatform.instance = platform;
      readRequest = Completer<String>();
      failRead = false;
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(platform.methodChannel, (call) async {
        if (call.method.endsWith('/new')) {
          return jsonEncode({
            'code': 0,
            'jsonData': {'handle': 'cluster-test-controller'},
          });
        }
        if (call.method.endsWith('/read')) {
          if (failRead) {
            return jsonEncode({'code': 7, 'jsonData': <String, dynamic>{}});
          }
          if (!readRequest.isCompleted) {
            readRequest.complete(call.arguments as String);
          }
          return jsonEncode({'code': 0, 'jsonData': {}});
        }
        return jsonEncode({'code': 0, 'jsonData': {}});
      });
      controller = await ChipDeviceController.newControllerIfNotExist(
        ControllerParams(
          fabricId: 901234567,
          rootCertificate: Uint8List.fromList(<int>[1, 2, 3]),
        ),
      );
    });

    tearDown(() {
      controller.destroy();
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(platform.methodChannel, null);
    });

    test('DescriptorCluster completes after a valid report', () async {
      final writer = TlvWriter()
        ..startArray(AnonymousTag.instance)
        ..putUnsigned(AnonymousTag.instance, 1)
        ..putUnsigned(AnonymousTag.instance, 2)
        ..endArray();
      final future = DescriptorCluster(
        controller: controller,
        connContext: null,
        endpointId: 1,
        nodeId: 1,
      ).readServerListAttribute();

      final params = jsonDecode(await readRequest.future) as Map;
      final handle = params['callbackHandle'] as String;
      final arguments = jsonEncode({
        'reportCallbackPoint': handle,
        'nodeState': {
          'endpoints': {
            '1': {
              'clusters': {
                '29': {
                  'attributes': {
                    '1': {'tlv': writer.getEncoded().toList()},
                  },
                },
              },
            },
          },
        },
      });
      final result = controller.call(
        'zgMatter://devicecontroller/ReportCallback/onReport',
        arguments,
      );

      expect(result.code, successCode);
      expect(await future, <int>[1, 2]);

      // A duplicate native report must not attempt to complete the same
      // Completer a second time.
      final duplicate = controller.call(
        'zgMatter://devicecontroller/ReportCallback/onReport',
        arguments,
      );
      expect(duplicate.code, successCode);
    });

    test('DescriptorCluster completes typed error when read request fails',
        () async {
      failRead = true;

      final future = DescriptorCluster(
        controller: controller,
        connContext: null,
        endpointId: 1,
        nodeId: 1,
      ).readServerListAttribute();

      await expectLater(
        future,
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', 7)
              .having((error) => error.methodName, 'methodName', 'read'),
        ),
      );
    });

    test('DescriptorCluster completes with typed error for missing payload',
        () async {
      final future = DescriptorCluster(
        controller: controller,
        connContext: null,
        endpointId: 1,
        nodeId: 1,
      ).readServerListAttribute();

      final params = jsonDecode(await readRequest.future) as Map;
      final handle = params['callbackHandle'] as String;
      controller.call(
        'zgMatter://devicecontroller/ReportCallback/onReport',
        jsonEncode({
          'reportCallbackPoint': handle,
          'nodeState': {
            'endpoints': {
              '1': {
                'clusters': {
                  '29': {'attributes': <String, dynamic>{}},
                },
              },
            },
          },
        }),
      );

      await expectLater(
        future,
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.methodName, 'methodName',
                  'DescriptorCluster.readServerListAttribute')
              .having((error) => error.details?['category'], 'category',
                  'cluster-report'),
        ),
      );
    });

    test('DescriptorCluster wraps a malformed TLV in a typed error', () async {
      final future = DescriptorCluster(
        controller: controller,
        connContext: null,
        endpointId: 1,
        nodeId: 1,
      ).readPartsListAttribute();

      final params = jsonDecode(await readRequest.future) as Map;
      final handle = params['callbackHandle'] as String;
      controller.call(
        'zgMatter://devicecontroller/ReportCallback/onReport',
        jsonEncode({
          'reportCallbackPoint': handle,
          'nodeState': {
            'endpoints': {
              '1': {
                'clusters': {
                  '29': {
                    'attributes': {
                      '3': {
                        'tlv': <int>[0x15, 0x18]
                      },
                    },
                  },
                },
              },
            },
          },
        }),
      );

      await expectLater(
        future,
        throwsA(
          isA<CallPlatformException>().having(
            (error) => error.methodName,
            'methodName',
            'DescriptorCluster.readPartsListAttribute',
          ),
        ),
      );
    });

    test('DescriptorCluster fails typed when the read completes without report',
        () async {
      final future = DescriptorCluster(
        controller: controller,
        connContext: null,
        endpointId: 1,
        nodeId: 1,
      ).readServerListAttribute();

      final params = jsonDecode(await readRequest.future) as Map;
      final handle = params['callbackHandle'] as String;
      controller.call(
        'zgMatter://devicecontroller/ReportCallback/onDone',
        jsonEncode({'reportCallbackPoint': handle}),
      );

      await expectLater(
        future,
        throwsA(
          isA<CallPlatformException>().having(
            (error) => error.methodName,
            'methodName',
            'DescriptorCluster.readServerListAttribute',
          ),
        ),
      );
    });

    test('BasicInformationCluster wraps malformed TLV in a typed error',
        () async {
      final future = BasicInformationCluster(
        controller: controller,
        connContext: null,
        nodeId: 1,
      ).readProductIDAttribute();

      final params = jsonDecode(await readRequest.future) as Map;
      final handle = params['callbackHandle'] as String;
      controller.call(
        'zgMatter://devicecontroller/ReportCallback/onReport',
        jsonEncode({
          'reportCallbackPoint': handle,
          'nodeState': {
            'endpoints': {
              '0': {
                'clusters': {
                  '40': {
                    'attributes': {
                      '4': {
                        'tlv': <int>[0x15, 0x18]
                      },
                    },
                  },
                },
              },
            },
          },
        }),
      );

      await expectLater(
        future,
        throwsA(
          isA<CallPlatformException>().having(
            (error) => error.methodName,
            'methodName',
            'BasicInformationCluster.readProductIDAttribute',
          ),
        ),
      );
    });

    test('BasicInformationCluster wraps a missing payload in a typed error',
        () async {
      final future = BasicInformationCluster(
        controller: controller,
        connContext: null,
        nodeId: 1,
      ).readVendorIDAttribute();

      final params = jsonDecode(await readRequest.future) as Map;
      final handle = params['callbackHandle'] as String;
      controller.call(
        'zgMatter://devicecontroller/ReportCallback/onReport',
        jsonEncode({
          'reportCallbackPoint': handle,
          'nodeState': {
            'endpoints': {
              '0': {
                'clusters': {
                  '40': {'attributes': <String, dynamic>{}},
                },
              },
            },
          },
        }),
      );

      await expectLater(
        future,
        throwsA(
          isA<CallPlatformException>().having(
            (error) => error.methodName,
            'methodName',
            'BasicInformationCluster.readVendorIDAttribute',
          ),
        ),
      );
    });

    testWidgets(
        'DescriptorCluster times out after destroy clears an accepted callback',
        (tester) async {
      final future = DescriptorCluster(
        controller: controller,
        connContext: null,
        endpointId: 1,
        nodeId: 1,
      ).readServerListAttribute();

      await tester.pump();
      expect(readRequest.isCompleted, isTrue);

      controller.destroy();

      final expectation = expectLater(
        future,
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', unHandlerException)
              .having(
                (error) => error.methodName,
                'methodName',
                'DescriptorCluster.readServerListAttribute',
              )
              .having(
                (error) => error.cause,
                'cause',
                isA<TimeoutException>(),
              ),
        ),
      );

      await tester.pump(const Duration(seconds: 15));
      await expectation;
    });
  });

  group('controller request and callback lifecycle', () {
    late MethodChannelFlutterMatter platform;
    late ChipDeviceController controller;
    String? failingMethod;

    setUp(() async {
      platform = MethodChannelFlutterMatter();
      FlutterMatterPlatform.instance = platform;
      failingMethod = null;
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(platform.methodChannel, (call) async {
        if (call.method.endsWith('/new')) {
          return jsonEncode({
            'code': 0,
            'jsonData': {'handle': 'lifecycle-test-controller'},
          });
        }
        if (call.method.endsWith('/openPairingWindowWithPIN')) {
          if (failingMethod == 'openPairingWindowWithPIN') {
            return jsonEncode({'code': 7, 'jsonData': <String, dynamic>{}});
          }
          return jsonEncode({
            'code': 0,
            'jsonData': {'data': true}
          });
        }
        final methodName = call.method.split('/').last;
        if (methodName == failingMethod) {
          return jsonEncode({'code': 7, 'jsonData': <String, dynamic>{}});
        }
        return jsonEncode({'code': 0, 'jsonData': <String, dynamic>{}});
      });
      controller = await ChipDeviceController.newControllerIfNotExist(
        ControllerParams(
          fabricId: 901234568,
          rootCertificate: Uint8List.fromList(<int>[4, 5, 6]),
        ),
      );
    });

    tearDown(() {
      controller.destroy();
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(platform.methodChannel, null);
    });

    test('native request failures rethrow and remove pending callbacks',
        () async {
      final invokeCallback = _RecordingInvokeCallback();
      failingMethod = 'invoke';
      await expectLater(
        controller.invoke(
          invokeCallback,
          1,
          InvokeElement.create(1, 2, 3, null, null),
        ),
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', 7)
              .having((error) => error.methodName, 'methodName', 'invoke'),
        ),
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/InvokeCallback/onDone',
              jsonEncode({
                'invokeCallbackPoint': invokeCallback.hashCode.toString(),
              }),
            )
            .code,
        argsInvalid,
      );

      final subscriptionCallback = _RecordingSubscriptionCallback();
      failingMethod = 'subscribe';
      await expectLater(
        controller.subscribe(
          1,
          subscriptionCallback,
          null,
          null,
          null,
          0,
          0,
          false,
          false,
          0,
          0,
        ),
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', 7)
              .having((error) => error.methodName, 'methodName', 'subscribe'),
        ),
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/SubscriptionCallback/onDone',
              jsonEncode({
                'subscriptionCallbackPoint':
                    subscriptionCallback.hashCode.toString(),
              }),
            )
            .code,
        argsInvalid,
      );

      final reportCallback = _RecordingReportCallback();
      failingMethod = 'read';
      await expectLater(
        controller.read(
          1,
          reportCallback,
          null,
          null,
          null,
          false,
          0,
          0,
        ),
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', 7)
              .having((error) => error.methodName, 'methodName', 'read'),
        ),
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/ReportCallback/onDone',
              jsonEncode({
                'reportCallbackPoint': reportCallback.hashCode.toString(),
              }),
            )
            .code,
        argsInvalid,
      );

      final writeCallback = _RecordingWriteCallback();
      failingMethod = 'write';
      await expectLater(
        controller.write(
          1,
          writeCallback,
          <AttributeWriteRequest>[
            AttributeWriteRequest(
              endpointId: ChipPathId.forId(1),
              clusterId: ChipPathId.forId(2),
              attributeId: ChipPathId.forId(3),
              dataVersion: 0,
            ),
          ],
          0,
          0,
        ),
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', 7)
              .having((error) => error.methodName, 'methodName', 'write'),
        ),
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/WriteAttributesCallback/onDone',
              jsonEncode({
                'writeAttributesCallbackPoint':
                    writeCallback.hashCode.toString(),
              }),
            )
            .code,
        argsInvalid,
      );

      final connectedCallback = _RecordingConnectedCallback();
      failingMethod = 'connectedDevice';
      await expectLater(
        controller.connectedDevice(1, connectedCallback),
        throwsA(
          isA<CallPlatformException>()
              .having((error) => error.code, 'code', 7)
              .having(
                  (error) => error.methodName, 'methodName', 'connectedDevice'),
        ),
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/ConnectedDeviceCallback/onDeviceConnected',
              jsonEncode({
                'callbackHandle': connectedCallback.hashCode.toString(),
              }),
            )
            .code,
        argsInvalid,
      );
    });

    test('subscription reports remain live until an idempotent terminal done',
        () async {
      final callback = _RecordingSubscriptionCallback();
      await controller.subscribe(
        1,
        callback,
        null,
        null,
        null,
        0,
        0,
        false,
        false,
        0,
        0,
      );

      final handle = callback.hashCode.toString();
      final reportArguments = jsonEncode({
        'subscriptionCallbackPoint': handle,
        'nodeState': {'endpoints': <String, dynamic>{}},
      });
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/SubscriptionCallback/onReport',
              reportArguments,
            )
            .code,
        successCode,
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/SubscriptionCallback/onReport',
              reportArguments,
            )
            .code,
        successCode,
      );
      expect(callback.reportCount, 2);

      expect(
        controller
            .call(
              'zgMatter://devicecontroller/SubscriptionCallback/onDone',
              jsonEncode({'subscriptionCallbackPoint': handle}),
            )
            .code,
        successCode,
      );
      expect(callback.doneCount, 1);
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/SubscriptionCallback/onDone',
              jsonEncode({'subscriptionCallbackPoint': handle}),
            )
            .code,
        argsInvalid,
      );
    });

    test('subscription establishment invokes its callback once', () async {
      final callback = _RecordingSubscriptionCallback();
      await controller.subscribe(
        1,
        callback,
        null,
        null,
        null,
        0,
        0,
        false,
        false,
        0,
        0,
      );

      final result = controller.call(
        'zgMatter://devicecontroller/SubscriptionCallback/onSubscriptionEstablished',
        jsonEncode({
          'subscriptionCallbackPoint': callback.hashCode.toString(),
          'subscriptionId': 42,
        }),
      );

      expect(result.code, successCode);
      expect(callback.establishedSubscriptionIds, <int>[42]);
    });

    test('invoke removes its callback after terminal done', () async {
      final callback = _RecordingInvokeCallback();
      await controller.invoke(
        callback,
        1,
        InvokeElement.create(1, 2, 3, null, null),
      );

      final handle = callback.hashCode.toString();
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/InvokeCallback/onDone',
              jsonEncode({'invokeCallbackPoint': handle}),
            )
            .code,
        successCode,
      );
      expect(callback.doneCount, 1);
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/InvokeCallback/onDone',
              jsonEncode({'invokeCallbackPoint': handle}),
            )
            .code,
        argsInvalid,
      );
    });

    test('open commissioning removes callbacks after success and error',
        () async {
      final successCallback = _RecordingOpenCommissioningCallback();
      expect(
        await controller.openPairingWindowWithPIN(
          1,
          60,
          1,
          123456,
          successCallback,
        ),
        isTrue,
      );
      final successHandle = successCallback.hashCode.toString();
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/OpenCommissioningCallback/onSuccess',
              jsonEncode({
                'callbackHandle': successHandle,
                'manualPairingCode': '12345678901',
                'qrCode': 'MT:TEST',
              }),
            )
            .code,
        successCode,
      );
      expect(successCallback.successCount, 1);
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/OpenCommissioningCallback/onSuccess',
              jsonEncode({
                'callbackHandle': successHandle,
                'manualPairingCode': '12345678901',
                'qrCode': 'MT:TEST',
              }),
            )
            .code,
        argsInvalid,
      );

      final errorCallback = _RecordingOpenCommissioningCallback();
      expect(
        await controller.openPairingWindowWithPIN(
          1,
          60,
          2,
          654321,
          errorCallback,
        ),
        isTrue,
      );
      final errorHandle = errorCallback.hashCode.toString();
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/OpenCommissioningCallback/onError',
              jsonEncode({
                'callbackHandle': errorHandle,
                'status': 1,
              }),
            )
            .code,
        successCode,
      );
      expect(errorCallback.errorCount, 1);
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/OpenCommissioningCallback/onError',
              jsonEncode({
                'callbackHandle': errorHandle,
                'status': 1,
              }),
            )
            .code,
        argsInvalid,
      );
    });

    test('destroy clears connected and open commissioning callbacks', () async {
      final connectedCallback = _RecordingConnectedCallback();
      final openCallback = _RecordingOpenCommissioningCallback();
      await controller.connectedDevice(1, connectedCallback);
      expect(
        await controller.openPairingWindowWithPIN(
            1, 60, 1, 123456, openCallback),
        isTrue,
      );

      controller.destroy();

      expect(
        controller
            .call(
              'zgMatter://devicecontroller/ConnectedDeviceCallback/onDeviceConnected',
              jsonEncode({
                'callbackHandle': connectedCallback.hashCode.toString(),
              }),
            )
            .code,
        argsInvalid,
      );
      expect(
        controller
            .call(
              'zgMatter://devicecontroller/OpenCommissioningCallback/onSuccess',
              jsonEncode({
                'callbackHandle': openCallback.hashCode.toString(),
                'manualPairingCode': '12345678901',
                'qrCode': 'MT:TEST',
              }),
            )
            .code,
        argsInvalid,
      );
    });
  });
}

class _RecordingInvokeCallback implements InvokeCallback {
  int doneCount = 0;

  @override
  void onDone() => doneCount++;

  @override
  void onError(Exception e) {}

  @override
  void onResponse(InvokeElement invokeElement, int successCode) {}
}

class _RecordingSubscriptionCallback implements SubscriptionCallback {
  int doneCount = 0;
  int reportCount = 0;
  final List<int> establishedSubscriptionIds = <int>[];

  @override
  void onDone() => doneCount++;

  @override
  void onError(
    ChipAttributePath? attributePath,
    ChipEventPath? eventPath,
    Exception e,
  ) {}

  @override
  void onReport(NodeState nodeState) => reportCount++;

  @override
  void onSubscriptionEstablished(int subscriptionId) {
    establishedSubscriptionIds.add(subscriptionId);
  }
}

class _RecordingReportCallback implements ReportCallback {
  @override
  void onDone() {}

  @override
  void onError(
    ChipAttributePath? attributePath,
    ChipEventPath? eventPath,
    Exception e,
  ) {}

  @override
  void onReport(NodeState nodeState) {}
}

class _RecordingWriteCallback implements WriteAttributesCallback {
  @override
  void onDone() {}

  @override
  void onError(ChipAttributePath? attributePath, Exception e) {}

  @override
  void onResponse(ChipAttributePath? attributePath, Status? status) {}
}

class _RecordingConnectedCallback implements ConnectedDeviceCallback {
  @override
  void onConnected(Object? context) {}

  @override
  void onError(Exception e) {}
}

class _RecordingOpenCommissioningCallback implements OpenCommissioningCallback {
  int errorCount = 0;
  int successCount = 0;

  @override
  void onError(int status, Object? connectContext) => errorCount++;

  @override
  void onSuccess(
    Object? connectContext,
    String manualPairingCode,
    String qrCode,
  ) =>
      successCount++;
}
