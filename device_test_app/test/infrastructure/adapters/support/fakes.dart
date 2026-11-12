import 'dart:async';
import 'package:flutter/services.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_device_test_app/src/application/ports.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/adapters/adapters.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/ble/matter_ble.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/discovery/discovery.dart';
import 'package:flutter_matter_device_test_app/src/infrastructure/matter/matter.dart';

typedef CommissionHandler =
    Future<MatterCommissionResult> Function(MatterCommissionRequest request);
typedef ReadHandler =
    Future<MatterAttributeValue> Function(MatterReadAttributeRequest request);
typedef InvokeHandler =
    Future<MatterInvokeResult> Function(MatterOnOffRequest request);
typedef NodeLabelReadHandler =
    Future<String> Function(int nodeId, MatterConnection? connection);
typedef NodeLabelWriteHandler =
    Future<MatterWriteResult> Function(MatterWriteNodeLabelRequest request);
typedef FabricRemoveHandler =
    Future<MatterInvokeResult> Function(MatterRemoveFabricRequest request);

class FakeMatterControllerApi implements MatterControllerApi {
  CommissionHandler? commissionHandler;
  ReadHandler? readHandler;
  InvokeHandler? invokeHandler;
  NodeLabelReadHandler? nodeLabelReadHandler;
  NodeLabelWriteHandler? nodeLabelWriteHandler;
  FabricRemoveHandler? removeFabricHandler;
  Future<MatterSubscription> Function()? subscribeHandler;
  Future<MatterConnection> Function(MatterConnectRequest request)?
  connectHandler;
  Future<void> Function(MatterConnection connection)? releaseHandler;

  final List<MatterCommissionRequest> commissionRequests =
      <MatterCommissionRequest>[];
  final List<MatterConnectRequest> connectRequests = <MatterConnectRequest>[];
  final List<MatterReadAttributeRequest> readRequests =
      <MatterReadAttributeRequest>[];
  final List<MatterOnOffRequest> invokeRequests = <MatterOnOffRequest>[];
  final List<MatterWriteNodeLabelRequest> nodeLabelWriteRequests =
      <MatterWriteNodeLabelRequest>[];
  final List<MatterRemoveFabricRequest> removeFabricRequests =
      <MatterRemoveFabricRequest>[];
  final List<MatterConnection> releasedConnections = <MatterConnection>[];
  int closeCount = 0;

  @override
  Future<MatterCommissionResult> commission(MatterCommissionRequest request) {
    commissionRequests.add(request);
    final handler = commissionHandler;
    if (handler != null) {
      return handler(request);
    }
    return Future<MatterCommissionResult>.value(
      MatterCommissionResult(nodeId: request.nodeId, stages: const []),
    );
  }

  @override
  Future<MatterConnection> connect(MatterConnectRequest request) {
    connectRequests.add(request);
    final handler = connectHandler;
    if (handler != null) {
      return handler(request);
    }
    return Future<MatterConnection>.value(
      MatterConnection(nodeId: request.nodeId, context: 'context'),
    );
  }

  @override
  Future<void> releaseConnection(MatterConnection connection) async {
    releasedConnections.add(connection);
    await releaseHandler?.call(connection);
  }

  @override
  Future<MatterInvokeResult> invokeOnOff(MatterOnOffRequest request) {
    invokeRequests.add(request);
    final handler = invokeHandler;
    if (handler != null) {
      return handler(request);
    }
    return Future<MatterInvokeResult>.value(MatterInvokeResult(successCode: 0));
  }

  @override
  Future<MatterAttributeValue> readAttribute(
    MatterReadAttributeRequest request,
  ) {
    readRequests.add(request);
    final handler = readHandler;
    if (handler != null) {
      return handler(request);
    }
    return Future<MatterAttributeValue>.value(
      MatterAttributeValue(
        endpointId: request.endpointId,
        clusterId: request.clusterId,
        attributeId: request.attributeId,
        tlv: matterBoolTlv(true),
      ),
    );
  }

  @override
  Future<String> readNodeLabel({
    required int nodeId,
    MatterConnection? connection,
  }) {
    final handler = nodeLabelReadHandler;
    if (handler != null) {
      return handler(nodeId, connection);
    }
    return Future<String>.value('label');
  }

  @override
  Future<MatterWriteResult> writeNodeLabel(
    MatterWriteNodeLabelRequest request,
  ) {
    nodeLabelWriteRequests.add(request);
    final handler = nodeLabelWriteHandler;
    if (handler != null) {
      return handler(request);
    }
    return Future<MatterWriteResult>.value(
      const MatterWriteResult(statusCode: 0),
    );
  }

  @override
  Future<MatterSubscription> subscribeOnOff({
    required int nodeId,
    MatterConnection? connection,
  }) {
    final handler = subscribeHandler;
    if (handler != null) {
      return handler();
    }
    return Future<MatterSubscription>.value(FakeMatterSubscription());
  }

  @override
  Future<MatterInvokeResult> removeFabric(MatterRemoveFabricRequest request) {
    removeFabricRequests.add(request);
    final handler = removeFabricHandler;
    if (handler != null) {
      return handler(request);
    }
    return Future<MatterInvokeResult>.value(MatterInvokeResult(successCode: 0));
  }

  @override
  Future<void> close() async {
    closeCount++;
  }
}

class FakeMatterIdentityStore implements MatterControllerIdentityStoreApi {
  FakeMatterIdentityStore({MatterControllerIdentity? identity})
    : _identity = identity;

  MatterControllerIdentity? _identity;
  int loadCount = 0;
  int clearCount = 0;

  @override
  Future<MatterControllerCredentials> loadOrCreate(
    MatterControllerConfig config,
  ) async {
    loadCount++;
    final identity = _identity ??= MatterControllerIdentity.generate();
    return MatterControllerCredentials(
      identity: identity,
      rootCertificate: Uint8List.fromList(<int>[1, 2, 3]),
      operationalCertificate: Uint8List.fromList(<int>[4, 5, 6]),
    );
  }

  @override
  Future<void> clear() async {
    clearCount++;
    _identity = null;
  }
}

class FakeRuntimeProvider implements MatterControllerRuntimeProvider {
  FakeRuntimeProvider({MatterControllerConfig? config})
    : config = config ?? MatterControllerConfig();

  final MatterControllerConfig config;
  final Map<ControllerIdentityPurpose, _RuntimeEntry> _entries =
      <ControllerIdentityPurpose, _RuntimeEntry>{};
  int closeCount = 0;

  FakeMatterControllerApi controllerFor(ControllerIdentityPurpose purpose) {
    return _entry(purpose).controller;
  }

  FakeMatterIdentityStore identityFor(ControllerIdentityPurpose purpose) {
    return _entry(purpose).identity;
  }

  @override
  Future<MatterControllerRuntime> load(
    ControllerIdentityRequest request,
  ) async {
    final entry = _entry(request.purpose);
    return MatterControllerRuntime(
      purpose: request.purpose,
      config: config,
      controller: entry.controller,
      identityStore: entry.identity,
    );
  }

  @override
  Future<void> reset(ControllerIdentityRequest request) async {
    final entry = _entries.remove(request.purpose);
    if (entry == null) {
      return;
    }
    await entry.controller.close();
    await entry.identity.clear();
  }

  @override
  Future<void> close() async {
    closeCount++;
    final entries = _entries.values.toList(growable: false);
    _entries.clear();
    for (final entry in entries) {
      await entry.controller.close();
    }
  }

  _RuntimeEntry _entry(ControllerIdentityPurpose purpose) {
    return _entries.putIfAbsent(
      purpose,
      () => _RuntimeEntry(
        controller: FakeMatterControllerApi(),
        identity: FakeMatterIdentityStore(),
      ),
    );
  }
}

class _RuntimeEntry {
  _RuntimeEntry({required this.controller, required this.identity});

  final FakeMatterControllerApi controller;
  final FakeMatterIdentityStore identity;
}

class FakeOnboardingPayloadResolver implements MatterOnboardingPayloadResolver {
  FakeOnboardingPayloadResolver({
    this.discriminator = 0x0acd,
    this.hasShortDiscriminator = false,
    this.setupPinCode = 20202021,
    this.error,
  });

  final int discriminator;
  final bool hasShortDiscriminator;
  final int setupPinCode;
  final Object? error;
  final List<String> requests = <String>[];

  @override
  Future<OnboardingPayload> resolve(String payload) async {
    requests.add(payload);
    final failure = error;
    if (failure != null) {
      throw failure;
    }
    return OnboardingPayload(
      version: 0,
      vendorId: 0xfff1,
      productId: 0x8000,
      commissioningFlow: 0,
      discoveryCapabilities: <DiscoveryCapability>{DiscoveryCapability.ble},
      discriminator: discriminator,
      hasShortDiscriminator: hasShortDiscriminator,
      setupPinCode: setupPinCode,
    );
  }
}

class FakeMatterBleScanner implements MatterBleScannerApi {
  FakeMatterBleScanner({MatterBleDiscoveredDevice? discovered, this.error})
    : discovered = discovered ?? makeDiscoveredDevice();

  MatterBleDiscoveredDevice discovered;
  Object? error;
  final List<MatterBleDiscoveryRequest> requests =
      <MatterBleDiscoveryRequest>[];

  @override
  Future<MatterBleDiscoveredDevice> scan(
    MatterBleDiscoveryRequest request,
  ) async {
    requests.add(request);
    final failure = error;
    if (failure != null) {
      throw failure;
    }
    return discovered;
  }
}

class FakeMatterMdnsScanner implements MatterMdnsCommissioningScannerApi {
  FakeMatterMdnsScanner({this.matched = false, this.error});

  bool matched;
  Object? error;
  final List<MatterBleDiscoveryRequest> requests =
      <MatterBleDiscoveryRequest>[];

  @override
  Future<bool> waitForMatch({
    required int discriminator,
    required bool hasShortDiscriminator,
    required Duration timeout,
  }) async {
    requests.add(
      MatterBleDiscoveryRequest(
        discriminator: discriminator,
        hasShortDiscriminator: hasShortDiscriminator,
        timeout: timeout,
      ),
    );
    final failure = error;
    if (failure != null) {
      throw failure;
    }
    return matched;
  }
}

class FakeMatterBlePlatform implements MatterBlePlatform {
  FakeMatterBlePlatform({this.error});

  Object? error;
  bool ensureAdapterCalled = false;
  bool scanning = false;
  final StreamController<MatterBleAdvertisement> _advertisements =
      StreamController<MatterBleAdvertisement>.broadcast();

  @override
  Stream<MatterBleAdvertisement> get advertisements => _advertisements.stream;

  @override
  Future<void> ensureAdapterIsOn(Duration timeout) async {
    ensureAdapterCalled = true;
    final failure = error;
    if (failure != null) {
      throw failure;
    }
  }

  @override
  Future<void> startScan(Duration timeout) async {
    scanning = true;
  }

  @override
  Future<void> stopScan() async {
    scanning = false;
  }
}

class FakeMatterSubscription implements MatterSubscription {
  FakeMatterSubscription({this.initialReport, this.closed = true});

  final MatterAttributeValue? initialReport;
  final bool closed;
  final StreamController<MatterAttributeValue> _reports =
      StreamController<MatterAttributeValue>.broadcast();
  final StreamController<MatterException> _errors =
      StreamController<MatterException>.broadcast();
  int closeCount = 0;
  int closeCompletionCount = 0;
  Future<void> Function()? closeDelay;

  @override
  Stream<MatterAttributeValue> get reports => _reports.stream;

  @override
  Stream<MatterException> get errors => _errors.stream;

  @override
  int get subscriptionId => 7;

  @override
  Future<int> waitForEstablished(Duration timeout) async => subscriptionId;

  void emit(MatterAttributeValue value) {
    if (initialReport != null && !_reports.hasListener) {
      _reports.add(initialReport!);
      return;
    }
    if (!_reports.isClosed) {
      _reports.add(value);
    }
  }

  void emitError(MatterException error) {
    if (!_errors.isClosed) {
      _errors.add(error);
    }
  }

  @override
  Future<bool> close({Duration timeout = const Duration(seconds: 10)}) async {
    closeCount++;
    await closeDelay?.call();
    if (!_reports.isClosed) {
      await _reports.close();
    }
    if (!_errors.isClosed) {
      await _errors.close();
    }
    closeCompletionCount++;
    return closed;
  }
}

class FakeMatterBleDevice implements MatterBleDevice {
  @override
  bool get isConnected => false;

  @override
  int get mtu => 247;

  @override
  String get deviceId => 'fake-device-id';

  @override
  Future<void> connect(Duration timeout) async {}

  @override
  Future<void> disconnect() async {}

  @override
  Future<List<MatterBleGattService>> discoverServices(Duration timeout) async {
    return const <MatterBleGattService>[];
  }
}

MatterBleDiscoveredDevice makeDiscoveredDevice({
  String? name = 'Fake Matter device',
  int discriminator = 0x0acd,
}) {
  final advertisement = MatterBleAdvertisement(
    device: FakeMatterBleDevice(),
    serviceData: <String, Uint8List>{},
    rssi: -40,
    advertisedName: name,
  );
  return MatterBleDiscoveredDevice(
    advertisement: advertisement,
    matterServiceData: Uint8List(0),
    discriminator: discriminator,
  );
}

MatterAttributeValue matterBoolValue(
  MatterReadAttributeRequest request,
  bool value,
) {
  return MatterAttributeValue(
    endpointId: request.endpointId,
    clusterId: request.clusterId,
    attributeId: request.attributeId,
    tlv: matterBoolTlv(value),
  );
}

MatterAttributeValue matterUnsignedValue(
  MatterReadAttributeRequest request,
  int value,
) {
  final writer = TlvWriter()..putUnsigned(AnonymousTag.instance, value);
  return MatterAttributeValue(
    endpointId: request.endpointId,
    clusterId: request.clusterId,
    attributeId: request.attributeId,
    tlv: writer.validateTlv().getEncoded(),
  );
}

Uint8List matterBoolTlv(bool value) {
  final writer = TlvWriter()..putBool(AnonymousTag.instance, value);
  return writer.validateTlv().getEncoded();
}

PlatformException permissionPlatformException() {
  return PlatformException(code: 'permission_denied');
}
