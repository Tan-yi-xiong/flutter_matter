import 'dart:async';
import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/exception.dart';
import 'package:flutter_matter/src/utils.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  final defaultPlatform =
      FlutterMatterPlatform.instance as MethodChannelFlutterMatter;

  test('controller creation failure rolls back the hashCode keypair handle',
      () async {
    const codec = StandardMethodCodec();
    final platform = defaultPlatform;
    FlutterMatterPlatform.instance = platform;
    final channel = platform.methodChannel;
    final responseQueue = <String>[
      jsonEncode({'code': 7, 'jsonData': <String, dynamic>{}}),
      'not-json',
    ];
    final requestPayloads = <Map<String, dynamic>>[];
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      if (call.method.endsWith('/new')) {
        requestPayloads
            .add(jsonDecode(call.arguments as String) as Map<String, dynamic>);
        return responseQueue.removeAt(0);
      }
      return jsonEncode({'code': 0, 'jsonData': <String, dynamic>{}});
    });
    addTearDown(() {
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(channel, null);
    });

    final keypairs = <_TestKeypairDelegate>[
      _TestKeypairDelegate(),
      _TestKeypairDelegate(),
    ];
    final expectedErrors = <Matcher>[
      isA<CallPlatformException>().having(
        (error) => error.methodName,
        'methodName',
        'new',
      ),
      isA<PlatformProtocolException>().having(
        (error) => error.methodName,
        'methodName',
        'zgmatter://devicecontroller/new',
      ),
    ];
    for (var index = 0; index < keypairs.length; index++) {
      await expectLater(
        ChipDeviceController.newControllerIfNotExist(
          ControllerParams(
            fabricId: 700000 + index,
            keypairDelegate: keypairs[index],
          ),
        ),
        throwsA(expectedErrors[index]),
      );

      final response = await TestDefaultBinaryMessengerBinding
          .instance.defaultBinaryMessenger
          .handlePlatformMessage(
        'flutter_matter',
        codec.encodeMethodCall(
          MethodCall(
            'zgMatter://devicecontroller/KeypairDelegate/GetPublicKey',
            jsonEncode({'handle': keypairs[index].hashCode.toString()}),
          ),
        ),
        null,
      );
      final encoded = codec.decodeEnvelope(response!) as String;
      final envelope = jsonDecode(encoded) as Map<String, dynamic>;
      expect(envelope['code'], argsInvalid);
    }

    expect(requestPayloads, hasLength(2));
    for (var index = 0; index < keypairs.length; index++) {
      expect(
        requestPayloads[index]['keypairDelegateHandle'],
        keypairs[index].hashCode.toString(),
      );
    }
  });

  test('CallPlatformException is an Exception with structured safe fields', () {
    const secret = 'secret-network-password';
    final legacy = CallPlatformException('legacy message');
    expect(legacy.message, 'legacy message');

    final exception = CallPlatformException(
      'Call pairDevice failed with code 1',
      code: 1,
      methodName: 'pairDevice',
      details: const {'category': 'platform-error'},
    );

    expect(exception, isA<Exception>());
    expect(exception.code, 1);
    expect(exception.methodName, 'pairDevice');
    expect(exception.details?['category'], 'platform-error');
    expect(exception.data, same(exception.details));
    expect(exception.toString(), isNot(contains(secret)));
  });

  test('platform request and result toString redact payloads', () {
    const secret = 'secret-platform-payload';
    final params = RequestPlatformParams(
      methodName: 'zgMatter://ble/connectDevice',
      methodParamsJson: jsonEncode({'password': secret}),
    );
    final result = PlatformResult(
      code: 0,
      jsonData: {'password': secret},
    );

    expect(params.toString(), contains('zgMatter://ble/connectDevice'));
    expect(params.toString(), isNot(contains(secret)));
    expect(result.toString(), contains('code: 0'));
    expect(result.toString(), isNot(contains(secret)));
  });

  test('checkCallArgNotNull throws ArgumentError with key and context', () {
    const secret = 'secret-value-that-must-not-be-in-error';
    expect(
      () => checkCallArgNotNull(
        {'payload': secret},
        'missingKey',
        context: 'BLE callback',
      ),
      throwsA(
        allOf(
          isA<ArgumentError>(),
          predicate<ArgumentError>(
            (error) =>
                error.name == 'missingKey' &&
                error.message.toString().contains('BLE callback') &&
                !error.toString().contains(secret),
          ),
        ),
      ),
    );

    expect(checkCallArgNotNull({'value': 42}, 'value'), 42);
  });

  test('PlatformProtocolException keeps payload out of its message', () {
    final exception = PlatformProtocolException(
      'response code must be an integer',
      methodName: 'zgMatter://devicecontroller/new',
      cause: StateError('secret payload'),
    );

    expect(exception, isA<CallPlatformException>());
    expect(exception.violation, 'response code must be an integer');
    expect(exception.methodName, 'zgMatter://devicecontroller/new');
    expect(exception.toString(), isNot(contains('secret payload')));
  });

  test('error envelope helper preserves documented shape', () {
    final result =
        createPlatformCallExceptionResult(argsInvalid, 'safe message');
    expect(result.code, argsInvalid);
    expect(result.resultJson, '{"msg":"safe message"}');
  });

  test('toUint8List accepts signed and unsigned byte representations', () {
    expect(
      toUint8List(<dynamic>[-0x80, -1, 0, 0x7f, 0xff]),
      orderedEquals(<int>[0x80, 0xff, 0, 0x7f, 0xff]),
    );
  });

  test('toUint8List rejects invalid byte values with ArgumentError', () {
    expect(() => toUint8List(<dynamic>[-0x81]), throwsArgumentError);
    expect(() => toUint8List(<dynamic>[256]), throwsArgumentError);
    expect(() => toUint8List(<dynamic>['1']), throwsArgumentError);
  });

  test('reportMatterError logs stack frames but not raw messages', () {
    const secret = 'secret-in-low-level-error';
    final logs = <String>[];

    runZoned(
      () => reportMatterError(
        'callback',
        StateError(secret),
        StackTrace.current,
      ),
      zoneSpecification: ZoneSpecification(
        print: (self, parent, zone, line) => logs.add(line),
      ),
    );

    expect(logs.join('\n'), contains('StateError'));
    expect(logs.join('\n'), contains('#0'));
    expect(logs.join('\n'), isNot(contains(secret)));
  });

  test('BLE platform failures redact request parameters', () async {
    const secret = 'secret-wifi-credential';
    const channel = MethodChannel('flutter_matter');
    final platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({
        'code': 1,
        'jsonData': {'password': secret},
      });
    });

    await expectLater(
      BLELayerPlatform.handleConnectionError(1, 2),
      throwsA(
        predicate(
          (error) =>
              error is CallPlatformException &&
              error.code == 1 &&
              error.methodName == 'handleConnectionError' &&
              !error.toString().contains(secret),
        ),
      ),
    );

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('BLE disconnect failures surface a typed platform exception', () async {
    const channel = MethodChannel('flutter_matter');
    final platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({'code': 7, 'jsonData': <String, dynamic>{}});
    });

    await expectLater(
      BLEManager().disconnect(9),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', 7)
            .having((error) => error.methodName, 'methodName', 'disconnect'),
      ),
    );

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('certificate failures surface a typed platform exception', () async {
    const channel = MethodChannel('flutter_matter');
    final platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({'code': 7, 'jsonData': <String, dynamic>{}});
    });

    await expectLater(
      ChipDeviceController.createRootCertificate(
        _TestKeypairDelegate(),
        1,
        2,
      ),
      throwsA(
        isA<CallPlatformException>()
            .having((error) => error.code, 'code', 7)
            .having((error) => error.methodName, 'methodName',
                'createRootCertificate'),
      ),
    );

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('certificate success payload must be a byte array', () async {
    const channel = MethodChannel('flutter_matter');
    final platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({'code': 0, 'jsonData': <String, dynamic>{}});
    });

    await expectLater(
      ChipDeviceController.createRootCertificate(
        _TestKeypairDelegate(),
        1,
        2,
      ),
      throwsA(
        isA<PlatformProtocolException>().having(
          (error) => error.methodName,
          'methodName',
          'createRootCertificate',
        ),
      ),
    );

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('certificate success payload accepts Android signed bytes', () async {
    const channel = MethodChannel('flutter_matter');
    final platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({
        'code': 0,
        'jsonData': {
          'data': <int>[-0x80, -1, 0, 0x7f],
        },
      });
    });

    final certificate = await ChipDeviceController.createRootCertificate(
      _TestKeypairDelegate(),
      1,
      2,
    );

    expect(certificate, orderedEquals(<int>[0x80, 0xff, 0, 0x7f]));

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('NSD platform failures redact request parameters', () async {
    const secret = 'secret-mdns-service-data';
    const channel = MethodChannel('flutter_matter');
    final platform = MethodChannelFlutterMatter();
    FlutterMatterPlatform.instance = platform;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, (call) async {
      return jsonEncode({
        'code': 1,
        'jsonData': {'secret': secret},
      });
    });

    await expectLater(
      NsdManager().setResolveHandle(null),
      throwsA(
        predicate(
          (error) =>
              error is CallPlatformException &&
              error.code == 1 &&
              error.methodName == 'setResolve' &&
              !error.toString().contains(secret),
        ),
      ),
    );

    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });
}

class _TestKeypairDelegate implements KeypairDelegate {
  @override
  Uint8List createCertificateSigningRequest() => Uint8List(0);

  @override
  Uint8List ecdsaSignMessage(List<int> message) => Uint8List(0);

  @override
  void generatePrivateKey() {}

  @override
  Uint8List getPublicKey() => Uint8List(0);
}
