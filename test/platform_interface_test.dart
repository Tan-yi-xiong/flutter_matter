import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/src/platform_transport_types.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  late FlutterMatterPlatform originalPlatform;

  setUp(() {
    originalPlatform = FlutterMatterPlatform.instance;
  });

  tearDown(() {
    FlutterMatterPlatform.instance = originalPlatform;
  });

  test('controller uses a custom platform without a concrete cast', () async {
    final platform = _CustomFlutterMatterPlatform({
      'zgmatter://devicecontroller/new': PlatformResult(
        code: 0,
        jsonData: {'handle': 'controller-handle'},
      ),
    });
    FlutterMatterPlatform.instance = platform;

    final controller = await ChipDeviceController.newControllerIfNotExist(
      ControllerParams(fabricId: 987654),
    );

    expect(controller.isRunning, isTrue);
    expect(platform.handlers, contains(controller));
    expect(
        platform.requests.single.methodName, 'zgmatter://devicecontroller/new');

    controller.destroy();
    expect(platform.handlers, isNot(contains(controller)));
  });

  test('BLE manager uses a custom platform without a concrete cast', () async {
    final platform = _CustomFlutterMatterPlatform({
      'zgmatter://ble/connectDevice': PlatformResult(
        code: 0,
        jsonData: {'data': 42},
      ),
    });
    FlutterMatterPlatform.instance = platform;

    final id = await BLEManager().connect(OnboardingPayload(
      version: 0,
      vendorId: 10,
      productId: 20,
      commissioningFlow: 0,
      discoveryCapabilities: const {},
      discriminator: 100,
      hasShortDiscriminator: false,
      setupPinCode: 20202021,
    ));

    expect(id, 42);
    expect(platform.requests.single.methodName, 'zgmatter://ble/connectDevice');
  });

  test('NSD manager uses a custom platform without a concrete cast', () async {
    final platform = _CustomFlutterMatterPlatform({
      'zgmatter://nsd/setResolve': PlatformResult(
        code: 0,
        jsonData: <String, dynamic>{},
      ),
    });
    FlutterMatterPlatform.instance = platform;

    await NsdManager().setResolveHandle(null);

    expect(platform.requests.single.methodName, 'zgmatter://nsd/setResolve');
  });

  test('onboarding parser uses a custom platform without a concrete cast',
      () async {
    final platform = _CustomFlutterMatterPlatform({
      'zgmatter://onboarding/parseManualPairingCode': PlatformResult(
        code: 0,
        jsonData: {
          'version': 0,
          'vendorId': 10,
          'productId': 20,
          'commissioningFlow': 0,
          'discoveryCapabilities': <int>[],
          'discriminator': 100,
          'hasShortDiscriminator': false,
          'setupPinCode': 20202021,
        },
      ),
    });
    FlutterMatterPlatform.instance = platform;

    final payload = await OnboardingPayloadParser()
        .parseManualPairingCode('12345678901234567890');

    expect(payload.vendorId, 10);
    expect(platform.requests.single.methodName,
        'zgmatter://onboarding/parseManualPairingCode');
  });

  test('keypair callback handler registers with a custom platform', () {
    final platform = _CustomFlutterMatterPlatform({});
    FlutterMatterPlatform.instance = platform;

    final handler = KeypairDelegateCallbackHandler();

    expect(platform.handlers, contains(handler));
  });

  test('BLE callback handler registers with a custom platform', () {
    final platform = _CustomFlutterMatterPlatform({});
    FlutterMatterPlatform.instance = platform;

    final handler = BlePlatformDelegateCallbackHandler();

    expect(platform.handlers, contains(handler));
  });
}

class _CustomFlutterMatterPlatform extends FlutterMatterPlatform {
  _CustomFlutterMatterPlatform(this.responses);

  final Map<String, PlatformResult> responses;
  final List<RequestPlatformParams> requests = <RequestPlatformParams>[];
  final Set<MethodCallHandler> handlers = <MethodCallHandler>{};

  @override
  Future<PlatformResult> requestPlatform(RequestPlatformParams params) async {
    requests.add(params);
    return responses[params.methodName] ??
        PlatformResult(code: 0, jsonData: <String, dynamic>{});
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
