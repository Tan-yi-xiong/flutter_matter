import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/ble/matter_ble.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('commissioning request construction', () {
    test(
      'iOS uses the native onboarding path and no GATT connect id',
      () async {
        final fixture = _TestFixture(MatterTargetPlatform.ios);
        addTearDown(fixture.service.close);

        final result = await fixture.service.commission(_commissionRequest());

        expect(result.nodeId, 42);
        final pair = fixture.controller.pairRequest;
        expect(pair, isNotNull);
        expect(pair!.connectId, isNull);
        expect(pair.onboardingPayload, 'MT:TEST-PAYLOAD');
        expect(pair.setupPinCode, 20202021);
        expect(pair.networkCredentials.wifiCredentials!.ssid, 'Lab Wi-Fi');
        expect(fixture.controllerFactory.params!.fabricId, 709394);
        expect(
          fixture.controllerFactory.params!.rootCertificate,
          fixture.certificateIssuer.rootCertificate,
        );
      },
    );

    test('failed commissioning stops the native pairing attempt', () async {
      final fixture = _TestFixture(MatterTargetPlatform.ios);
      addTearDown(fixture.service.close);
      fixture.controller.commissionedErrorCode = 1;

      await expectLater(
        fixture.service.commission(_commissionRequest()),
        throwsA(isA<MatterException>()),
      );

      expect(fixture.controller.stoppedPairingNodeIds, [42]);
    });

    test(
      'Android scans, wires the GATT delegate, and uses conn id 4',
      () async {
        final fixture = _TestFixture(
          MatterTargetPlatform.android,
          emitAdvertisement: true,
        );
        addTearDown(fixture.service.close);
        var pairSawScanning = true;
        var pairSawDelegate = false;
        fixture.controller.onPair = () {
          pairSawScanning = fixture.blePlatform.isScanning;
          pairSawDelegate = fixture.bridge.currentDelegate != null;
        };

        final result = await fixture.service.commission(
          _commissionRequest(transport: MatterCommissioningTransport.ble),
        );

        expect(result.nodeId, 42);
        expect(fixture.controller.pairRequest!.connectId, 4);
        expect(pairSawScanning, isFalse);
        expect(pairSawDelegate, isTrue);
        expect(fixture.bridge.delegateHistory.first, isNotNull);
        expect(fixture.bridge.delegateHistory.last, isNull);
        expect(fixture.session.disconnected, isTrue);
      },
    );

    test(
      'Android IP commissioning skips the BLE transport and pairs on network',
      () async {
        final fixture = _TestFixture(
          MatterTargetPlatform.android,
          emitAdvertisement: true,
        );
        addTearDown(fixture.service.close);

        final result = await fixture.service.commission(_commissionRequest());

        expect(result.nodeId, 42);
        expect(fixture.controller.pairRequest!.connectId, isNull);
        expect(fixture.controller.pairRequest!.onboardingPayload, isNotEmpty);
        expect(fixture.controller.pairRequest!.networkCredentials, isNotNull);
        expect(fixture.blePlatform.startScanCount, 0);
        expect(fixture.gattSessionFactory.connectCount, 0);
        expect(fixture.bridge.currentDelegate, isNull);
        expect(fixture.bridge.delegateHistory, isEmpty);
        expect(fixture.session.disconnected, isFalse);
      },
    );
  });

  group('controller operations', () {
    test('connect returns a reusable operational context', () async {
      final fixture = _TestFixture(MatterTargetPlatform.ios);
      addTearDown(fixture.service.close);

      final connection = await fixture.service.connect(
        MatterConnectRequest(nodeId: 42),
      );
      await fixture.service.releaseConnection(connection);

      expect(connection.context, 'connected-context');
      expect(fixture.controller.releasedContexts, ['connected-context']);
    });

    test('OnOff command is sent to endpoint 1 cluster 0x0006', () async {
      final fixture = _TestFixture(MatterTargetPlatform.ios);
      addTearDown(fixture.service.close);

      final result = await fixture.service.invokeOnOff(
        const MatterOnOffRequest(nodeId: 42, command: MatterOnOffCommand.on),
      );

      expect(result.isSuccess, isTrue);
      final invoke = fixture.controller.lastInvokeElement;
      expect(invoke, isNotNull);
      expect(invoke!.endpointId!.id, 1);
      expect(invoke.clusterId.id, 0x0006);
      expect(invoke.commandId.id, 0x01);
      final reader = TlvReader(invoke.tlv!)
        ..enterStructure(AnonymousTag.instance);
      expect(reader.isEndOfContainer(), isTrue);
    });

    test(
      'readNodeLabel decodes the reported Basic Information value',
      () async {
        final fixture = _TestFixture(MatterTargetPlatform.ios);
        addTearDown(fixture.service.close);
        fixture.controller.readState = _nodeStateWithAttribute(
          clusterId: 0x0028,
          attributeId: 0x0005,
          tlv: nodeLabelTlv('Reading lamp'),
        );

        final label = await fixture.service.readNodeLabel(nodeId: 42);

        expect(label, 'Reading lamp');
        expect(fixture.controller.lastReadPath!.clusterId.id, 0x0028);
        expect(fixture.controller.lastReadPath!.attributeId.id, 0x0005);
      },
    );

    test('writeNodeLabel sends the expected path and UTF-8 TLV', () async {
      final fixture = _TestFixture(MatterTargetPlatform.ios);
      addTearDown(fixture.service.close);

      final result = await fixture.service.writeNodeLabel(
        MatterWriteNodeLabelRequest(nodeId: 42, label: 'Office lamp'),
      );

      expect(result.isSuccess, isTrue);
      final request = fixture.controller.lastWriteAttributes.single;
      expect(request.endpointId.id, 0);
      expect(request.clusterId.id, 0x0028);
      expect(request.attributeId.id, 0x0005);
      expect(decodeMatterString(request.tlv!), 'Office lamp');
    });

    test('OnOff subscription reports are forwarded to the caller', () async {
      final fixture = _TestFixture(MatterTargetPlatform.ios);
      addTearDown(fixture.service.close);
      fixture.controller.subscriptionState = _nodeStateWithAttribute(
        clusterId: 0x0006,
        attributeId: 0x0000,
        tlv: TlvWriter().putBool(AnonymousTag.instance, true).getEncoded(),
        endpointId: 1,
      );

      final subscription = await fixture.service
          .subscribeOnOff(nodeId: 42)
          .timeout(const Duration(seconds: 2));
      final report = await subscription.reports.first.timeout(
        const Duration(seconds: 2),
      );
      final closed = await subscription.close(
        timeout: const Duration(seconds: 2),
      );

      expect(report.decodeBool(), isTrue);
      expect(closed, isTrue);
      expect(fixture.controller.lastSubscribePath!.clusterId.id, 0x0006);
      expect(fixture.controller.unsubscriptions, hasLength(1));
    });

    test('RemoveFabric sends cluster 0x003e command 0x0a', () async {
      final fixture = _TestFixture(MatterTargetPlatform.ios);
      addTearDown(fixture.service.close);

      final result = await fixture.service.removeFabric(
        const MatterRemoveFabricRequest(nodeId: 42, fabricIndex: 3),
      );

      expect(result.isSuccess, isTrue);
      final invoke = fixture.controller.lastInvokeElement!;
      expect(invoke.endpointId!.id, 0);
      expect(invoke.clusterId.id, 0x003e);
      expect(invoke.commandId.id, 0x0a);
      expect(decodeRemoveFabricIndex(invoke.tlv!), 3);
    });
  });
}

MatterCommissionRequest _commissionRequest({
  MatterCommissioningTransport transport = MatterCommissioningTransport.ip,
}) {
  return MatterCommissionRequest(
    onboardingPayload: 'MT:TEST-PAYLOAD',
    setupPinCode: 20202021,
    discriminator: 0x0acd,
    hasShortDiscriminator: false,
    nodeId: 42,
    networkCredentials: MatterWifiNetworkCredentials(
      MatterWifiCredentials(ssid: 'Lab Wi-Fi', password: 'secret'),
    ),
    commissioningTransport: transport,
    bleScanTimeout: const Duration(milliseconds: 200),
    timeout: const Duration(milliseconds: 500),
  );
}

NodeState _nodeStateWithAttribute({
  required int clusterId,
  required int attributeId,
  required Uint8List tlv,
  int endpointId = 0,
}) {
  return NodeState(
    endpoints: <int, EndpointState>{
      endpointId: EndpointState(<int, ClusterState>{
        clusterId: ClusterState(
          attributes: <int, AttributeState>{
            attributeId: AttributeState(tlv: tlv),
          },
          events: const <int, List<EventState>>{},
          attributeStatuses: const <int, Status>{},
          eventStatuses: const <int, List<Status>>{},
        ),
      }),
    },
  );
}

class _TestFixture {
  _TestFixture(this.platform, {bool emitAdvertisement = true}) {
    controller = _FakeMatterControllerPort();
    controllerFactory = _FakeMatterControllerFactory(controller);
    certificateIssuer = _FakeCertificateIssuer();
    storage = _FakeCredentialStorage();
    blePlatform = _FakeBlePlatform(emitAdvertisement: emitAdvertisement);
    session = _FakeGattSession();
    gattSessionFactory = _FakeGattSessionFactory(session);
    bridge = _FakeBleLayerBridge();
    final identity = MatterControllerIdentity.generate();
    final credentialsService = MatterControllerCredentialsService(
      storage: storage,
      certificateIssuer: certificateIssuer,
      identityGenerator: () => identity,
    );
    service = MatterControllerService(
      targetPlatform: platform,
      bleScanner: MatterBleScanner(
        platform: blePlatform,
        cleanupTimeout: const Duration(milliseconds: 100),
      ),
      gattSessionFactory: gattSessionFactory,
      bleLayerBridge: bridge,
      credentialsService: credentialsService,
      controllerFactory: controllerFactory,
      certificateIssuer: certificateIssuer,
      config: MatterControllerConfig(
        operationTimeout: const Duration(milliseconds: 500),
        connectTimeout: const Duration(milliseconds: 500),
        commissioningTimeout: const Duration(milliseconds: 500),
        subscriptionTimeout: const Duration(milliseconds: 500),
      ),
    );
  }

  final MatterTargetPlatform platform;
  late final _FakeMatterControllerPort controller;
  late final _FakeMatterControllerFactory controllerFactory;
  late final _FakeCertificateIssuer certificateIssuer;
  late final _FakeCredentialStorage storage;
  late final _FakeBlePlatform blePlatform;
  late final _FakeGattSession session;
  late final _FakeGattSessionFactory gattSessionFactory;
  late final _FakeBleLayerBridge bridge;
  late final MatterControllerService service;
}

class _FakeMatterControllerFactory implements MatterControllerFactory {
  _FakeMatterControllerFactory(this.controller);

  final _FakeMatterControllerPort controller;
  ControllerParams? params;

  @override
  Future<MatterControllerPort> create(ControllerParams params) async {
    this.params = params;
    return controller;
  }
}

class _PairRequest {
  _PairRequest({
    required this.nodeId,
    required this.connectId,
    required this.setupPinCode,
    required this.onboardingPayload,
    required this.networkCredentials,
    required this.attestationDelegate,
    required this.completionListener,
  });

  final int nodeId;
  final int? connectId;
  final int setupPinCode;
  final String? onboardingPayload;
  final NetworkCredentials networkCredentials;
  final DeviceAttestationDelegate? attestationDelegate;
  final CompletionListener completionListener;
}

class _FakeMatterControllerPort implements MatterControllerPort {
  _PairRequest? pairRequest;
  NOCChainIssuer? nocChainIssuer;
  InvokeElement? lastInvokeElement;
  InvokeCallback? lastInvokeCallback;
  ChipAttributePath? lastReadPath;
  NodeState? readState;
  List<AttributeWriteRequest> lastWriteAttributes = [];
  ChipAttributePath? lastSubscribePath;
  NodeState? subscriptionState;
  int invokeSuccessCode = 0;
  int commissionedErrorCode = 0;
  int? fabricIndex = 3;
  final List<Object> releasedContexts = [];
  final List<List<int>> unsubscriptions = [];
  final List<int> stoppedPairingNodeIds = [];
  VoidCallback? onPair;

  @override
  Future<void> setNocChainIssuer(NOCChainIssuer issuer) async {
    nocChainIssuer = issuer;
  }

  @override
  Future<void> pairDevice({
    required int nodeId,
    required int? connectId,
    required int setupPinCode,
    required String? onboardingPayload,
    required NetworkCredentials networkCredentials,
    required DeviceAttestationDelegate? attestationDelegate,
    required CompletionListener completionListener,
  }) async {
    onPair?.call();
    pairRequest = _PairRequest(
      nodeId: nodeId,
      connectId: connectId,
      setupPinCode: setupPinCode,
      onboardingPayload: onboardingPayload,
      networkCredentials: networkCredentials,
      attestationDelegate: attestationDelegate,
      completionListener: completionListener,
    );
    scheduleMicrotask(() {
      completionListener.onCommissioningComplete(nodeId, commissionedErrorCode);
    });
  }

  @override
  Future<void> stopDevicePairing(int nodeId) async {
    stoppedPairingNodeIds.add(nodeId);
  }

  @override
  Future<Uint8List> publicKeyFromCSR(Uint8List csr) async {
    return Uint8List(65);
  }

  @override
  Future<int> onNOCChainGeneration(
    ControllerParams params, {
    String? onNOCChainGenerationCompleteHandle,
  }) async {
    return 0;
  }

  @override
  Future<void> continueCommissioning(
    int devicePtr,
    bool ignoreAttestationFailure,
  ) async {}

  @override
  Future<void> connectedDevice(
    int nodeId,
    ConnectedDeviceCallback callback, {
    Object? connectContext,
  }) async {
    scheduleMicrotask(() => callback.onConnected('connected-context'));
  }

  @override
  Future<void> releaseConnectContext(Object connectContext) async {
    releasedContexts.add(connectContext);
  }

  @override
  Future<void> invoke(
    InvokeCallback callback,
    int nodeId,
    InvokeElement invokeElement, {
    Object? connectContext,
    int timedRequestTimeoutMs = 0,
    int imTimeoutMs = 0,
  }) async {
    lastInvokeElement = invokeElement;
    lastInvokeCallback = callback;
    scheduleMicrotask(() {
      callback.onResponse(
        InvokeElement.create(
          invokeElement.endpointId?.id ?? 0,
          invokeElement.clusterId.id,
          invokeElement.commandId.id,
          null,
          null,
        ),
        invokeSuccessCode,
      );
    });
  }

  @override
  Future<void> read(
    int nodeId,
    ReportCallback callback,
    List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    bool isFabricFiltered,
    int imTimeoutMs,
    int eventMin, {
    Object? connectContext,
  }) async {
    lastReadPath = attributePaths!.single;
    scheduleMicrotask(() {
      callback.onReport(readState!);
      callback.onDone();
    });
  }

  @override
  Future<void> write(
    int nodeId,
    WriteAttributesCallback callback,
    List<AttributeWriteRequest> attributeList,
    int timedRequestTimeoutMs,
    int imTimeoutMs, {
    Object? connectContext,
  }) async {
    lastWriteAttributes = attributeList;
    scheduleMicrotask(() {
      callback.onResponse(
        ChipAttributePath(
          endpointId: attributeList.single.endpointId,
          clusterId: attributeList.single.clusterId,
          attributeId: attributeList.single.attributeId,
        ),
        Status(status: 0),
      );
      callback.onDone();
    });
  }

  @override
  Future<void> subscribe(
    int nodeId,
    SubscriptionCallback callback,
    List<ChipAttributePath>? attributePaths,
    List<ChipEventPath>? eventPaths,
    List<DataVersionFilter>? dataVersionFilters,
    int minInterval,
    int maxInterval,
    bool keepSubscriptions,
    bool isFabricFiltered,
    int imTimeoutMs,
    int eventMin, {
    Object? connectContext,
  }) async {
    lastSubscribePath = attributePaths!.single;
    callback.onSubscriptionEstablished(9);
    callback.onReport(subscriptionState!);
  }

  @override
  Future<int?> getFabricIndex() async => fabricIndex;

  @override
  Future<bool> unSubscription(
    int fabricIndex,
    int nodeId,
    int subscriptionId,
  ) async {
    unsubscriptions.add([fabricIndex, nodeId, subscriptionId]);
    return true;
  }

  @override
  Future<void> deleteDeviceController() async {}
}

class _FakeCertificateIssuer implements MatterCertificateIssuer {
  final Uint8List rootCertificate = Uint8List.fromList([0x30, 0x01]);
  final Uint8List operationalCertificate = Uint8List.fromList([0x30, 0x02]);

  @override
  Future<Uint8List> createRootCertificate({
    required KeypairDelegate keypair,
    required int issuerId,
    required int fabricId,
  }) async {
    return rootCertificate;
  }

  @override
  Future<Uint8List> createOperationalCertificate({
    required KeypairDelegate signingKeypair,
    required Uint8List signingCertificate,
    required Uint8List operationalPublicKey,
    required int fabricId,
    required int nodeId,
    List<int>? caseAuthenticatedTags,
  }) async {
    return operationalCertificate;
  }
}

class _FakeCredentialStorage implements MatterSecureCredentialStorage {
  String? value;

  @override
  Future<void> delete() async {
    value = null;
  }

  @override
  Future<String?> read() async => value;

  @override
  Future<void> write(String value) async {
    this.value = value;
  }
}

class _FakeBlePlatform implements MatterBlePlatform {
  _FakeBlePlatform({required this.emitAdvertisement});

  final bool emitAdvertisement;
  final StreamController<MatterBleAdvertisement> _advertisements =
      StreamController<MatterBleAdvertisement>.broadcast();
  final _FakeBleDevice device = _FakeBleDevice();
  bool isScanning = false;
  int startScanCount = 0;

  @override
  Stream<MatterBleAdvertisement> get advertisements => _advertisements.stream;

  @override
  Future<void> ensureAdapterIsOn(Duration timeout) async {}

  @override
  Future<void> startScan(Duration timeout) async {
    startScanCount++;
    isScanning = true;
    if (!emitAdvertisement) {
      return;
    }
    scheduleMicrotask(() {
      _advertisements.add(
        MatterBleAdvertisement(
          device: device,
          serviceData: <String, Uint8List>{
            matterGattServiceUuid: Uint8List.fromList([
              0x00,
              0xcd,
              0x0a,
              0xaa,
              0xbb,
            ]),
          },
          rssi: -45,
        ),
      );
    });
  }

  @override
  Future<void> stopScan() async {
    isScanning = false;
  }
}

class _FakeBleDevice implements MatterBleDevice {
  @override
  String get deviceId => 'android-commissionee';

  @override
  bool get isConnected => false;

  @override
  int get mtu => 185;

  @override
  Future<void> connect(Duration timeout) async {}

  @override
  Future<void> disconnect() async {}

  @override
  Future<List<MatterBleGattService>> discoverServices(Duration timeout) async {
    return const [];
  }
}

class _FakeGattSessionFactory implements MatterBleGattSessionFactory {
  _FakeGattSessionFactory(this.session);

  final _FakeGattSession session;
  int connectCount = 0;

  @override
  Future<MatterBleGattSession> connect(MatterBleDevice device) async {
    connectCount++;
    return session;
  }
}

class _FakeGattSession implements MatterBleGattSession {
  bool disconnected = false;

  @override
  String get deviceId => 'android-commissionee';

  @override
  int get mtu => 185;

  @override
  Future<void> setNotify({
    required String serviceUuid,
    required String characteristicUuid,
    required bool enabled,
    required Duration timeout,
  }) async {}

  @override
  Future<void> write({
    required String serviceUuid,
    required String characteristicUuid,
    required Uint8List value,
    required bool withoutResponse,
    required Duration timeout,
  }) async {}

  @override
  Stream<Uint8List> notifications({
    required String serviceUuid,
    required String characteristicUuid,
  }) {
    return const Stream<Uint8List>.empty();
  }

  @override
  Future<void> disconnect(Duration timeout) async {
    disconnected = true;
  }
}

class _FakeBleLayerBridge implements MatterBleLayerBridge {
  final List<BlePlatformDelegate?> delegateHistory = [];
  BlePlatformDelegate? currentDelegate;

  @override
  Future<void> setDelegate(BlePlatformDelegate? delegate) async {
    currentDelegate = delegate;
    delegateHistory.add(delegate);
  }

  @override
  Future<void> handleSubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) async {}

  @override
  Future<void> handleUnsubscribeComplete({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) async {}

  @override
  Future<void> handleIndicationReceived({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required Uint8List value,
  }) async {}

  @override
  Future<void> handleWriteConfirmation({
    required Object? connection,
    required Uint8List serviceId,
    required Uint8List characteristicId,
    required bool success,
  }) async {}

  @override
  Future<void> handleConnectionError({
    required Object? connection,
    required int errorCode,
  }) async {}
}

typedef VoidCallback = void Function();
