import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import '../ble/matter_ble.dart';
import 'matter_callback_wrappers.dart';
import 'matter_certificate_service.dart';
import 'matter_contracts.dart';
import 'matter_controller_port.dart';
import 'matter_credentials_service.dart';
import 'matter_subscription.dart';
import 'matter_tlv.dart';

class MatterControllerService {
  MatterControllerService({
    required MatterTargetPlatform targetPlatform,
    required MatterBleScanner bleScanner,
    required MatterBleGattSessionFactory gattSessionFactory,
    required MatterBleLayerBridge bleLayerBridge,
    required MatterControllerCredentialsService credentialsService,
    required MatterControllerFactory controllerFactory,
    required MatterCertificateIssuer certificateIssuer,
    MatterControllerConfig? config,
  }) : _targetPlatform = targetPlatform,
       _bleScanner = bleScanner,
       _gattSessionFactory = gattSessionFactory,
       _bleLayerBridge = bleLayerBridge,
       _credentialsService = credentialsService,
       _controllerFactory = controllerFactory,
       _certificateIssuer = certificateIssuer,
       _config = config ?? MatterControllerConfig();

  factory MatterControllerService.flutter({
    required MatterTargetPlatform targetPlatform,
    MatterControllerConfig? config,
  }) {
    final certificateIssuer = const FlutterMatterCertificateIssuer();
    return MatterControllerService(
      targetPlatform: targetPlatform,
      bleScanner: MatterBleScanner(
        platform: FlutterBluePlusMatterBlePlatform(),
      ),
      gattSessionFactory: DefaultMatterBleGattSessionFactory(),
      bleLayerBridge: FlutterMatterBleLayerBridge(),
      credentialsService: MatterControllerCredentialsService(
        storage: FlutterSecureMatterCredentialStorage(),
        certificateIssuer: certificateIssuer,
      ),
      controllerFactory: const FlutterMatterControllerFactory(),
      certificateIssuer: certificateIssuer,
      config: config,
    );
  }

  final MatterTargetPlatform _targetPlatform;
  final MatterBleScanner _bleScanner;
  final MatterBleGattSessionFactory _gattSessionFactory;
  final MatterBleLayerBridge _bleLayerBridge;
  final MatterControllerCredentialsService _credentialsService;
  final MatterControllerFactory _controllerFactory;
  final MatterCertificateIssuer _certificateIssuer;

  final StreamController<MatterCommissioningStage> _commissioningStages =
      StreamController<MatterCommissioningStage>.broadcast();

  MatterControllerConfig _config;
  MatterControllerPort? _controller;
  MatterControllerCredentials? _credentials;
  Future<void>? _initialization;

  MatterControllerConfig get config => _config;

  Stream<MatterCommissioningStage> get commissioningStages =>
      _commissioningStages.stream;

  Future<void> initialize({MatterControllerConfig? config}) async {
    if (config != null && _controller != null) {
      await _disposeController();
      _config = config;
      _credentials = null;
    } else if (config != null) {
      _config = config;
    }
    if (_controller != null) {
      return;
    }
    final pending = _initialization;
    if (pending != null) {
      return pending;
    }
    final initialization = _createController();
    _initialization = initialization;
    try {
      await initialization;
    } finally {
      _initialization = null;
    }
  }

  Future<void> _createController() async {
    try {
      final credentials = await withMatterTimeout<MatterControllerCredentials>(
        future: _credentialsService.loadOrCreate(_config),
        timeout: _config.commissioningTimeout,
        operation: 'Load or create Matter controller credentials',
      );
      final params = ControllerParams(
        fabricId: _config.fabricId,
        controllerVendorId: _config.controllerVendorId,
        skipCommissioningComplete: false,
        keypairDelegate: credentials.identity,
        rootCertificate: credentials.rootCertificate,
        intermediateCertificate: credentials.rootCertificate,
        operationalCertificate: credentials.operationalCertificate,
        ipk: _config.ipk,
        nodeId: _config.controllerNodeId,
        adminSubject: _config.adminSubject,
      );
      final controller = await withMatterTimeout<MatterControllerPort>(
        future: _controllerFactory.create(params),
        timeout: _config.operationTimeout,
        operation: 'Create Matter controller',
      );
      _credentials = credentials;
      _controller = controller;
    } catch (error) {
      throw MatterException(
        MatterFailureCode.initializationFailed,
        'Unable to initialize the Matter controller',
        error,
      );
    }
  }

  Future<MatterCommissionResult> commission(
    MatterCommissionRequest request,
  ) async {
    await initialize();
    final controller = _requireController();
    final credentials = _requireCredentials();
    final timeout = request.timeout ?? _config.commissioningTimeout;

    MatterBleDiscoveredDevice? discovered;
    MatterBleGattSession? gattSession;
    MatterGattBleDelegate? delegate;
    StreamSubscription<MatterCommissioningStage>? stageSubscription;
    var pairingStarted = false;
    var commissioningCompleted = false;

    try {
      if (request.preScanBle) {
        try {
          discovered = await _bleScanner.scan(
            MatterBleDiscoveryRequest(
              discriminator: request.discriminator,
              hasShortDiscriminator: request.hasShortDiscriminator,
              timeout: request.bleScanTimeout,
            ),
          );
        } catch (error) {
          throw MatterException(
            MatterFailureCode.bleDiscoveryFailed,
            'Matter BLE discovery failed',
            error,
          );
        }
      }

      if (_targetPlatform == MatterTargetPlatform.android) {
        if (discovered == null) {
          throw MatterException(
            MatterFailureCode.bleConnectionFailed,
            'Android commissioning requires a successful BLE pre-scan',
          );
        }
        try {
          gattSession = await _gattSessionFactory.connect(discovered.device);
          delegate = MatterGattBleDelegate(
            session: gattSession,
            bridge: _bleLayerBridge,
          );
          await _bleLayerBridge.setDelegate(delegate);
        } catch (error) {
          throw MatterException(
            MatterFailureCode.bleConnectionFailed,
            'Unable to prepare the Android Matter BLE transport',
            error,
          );
        }
      }

      final listener = MatterCommissioningListener(
        fallbackNodeId: request.nodeId,
      );
      stageSubscription = listener.stages.listen(_commissioningStages.add);
      final nocIssuer = _MatterNocChainIssuer(
        controller: controller,
        credentials: credentials,
        config: _config,
        targetNodeId: request.nodeId,
        certificateIssuer: _certificateIssuer,
        onFailure: listener.fail,
        timeout: _config.operationTimeout,
      );
      final attestationDelegate = _MatterAttestationDelegate(
        controller: controller,
        onFailure: listener.fail,
        timeout: _config.operationTimeout,
      );

      await withMatterTimeout<void>(
        future: controller.setNocChainIssuer(nocIssuer),
        timeout: _config.operationTimeout,
        operation: 'Configure NOC chain issuer',
      );

      final networkCredentials = request.networkCredentials
          .toPluginCredentials();
      final connectId = _targetPlatform == MatterTargetPlatform.android
          ? androidMatterBleConnectionId
          : null;
      pairingStarted = true;
      await withMatterTimeout<void>(
        future: controller.pairDevice(
          nodeId: request.nodeId,
          connectId: connectId,
          setupPinCode: request.setupPinCode,
          onboardingPayload: request.onboardingPayload,
          networkCredentials: networkCredentials,
          attestationDelegate: attestationDelegate,
          completionListener: listener,
        ),
        timeout: timeout,
        operation: 'Start Matter commissioning',
      );

      final outcome = await listener.wait(timeout);
      if (outcome.errorCode != 0) {
        throw MatterException(
          MatterFailureCode.commissioningFailed,
          'Commissioning failed with error code ${outcome.errorCode}',
        );
      }
      commissioningCompleted = true;
      return MatterCommissionResult(
        nodeId: outcome.nodeId,
        stages: listener.stageHistory,
      );
    } finally {
      if (pairingStarted && !commissioningCompleted) {
        try {
          await withMatterTimeout<void>(
            future: controller.stopDevicePairing(request.nodeId),
            timeout: _config.operationTimeout,
            operation: 'Stop failed Matter pairing',
          );
        } catch (_) {
          // Preserve the primary commissioning failure during cleanup.
        }
      }
      await stageSubscription?.cancel();
      if (delegate != null) {
        try {
          await _bleLayerBridge.setDelegate(null);
        } catch (_) {
          // Preserve the primary commissioning result during cleanup.
        }
      }
      if (gattSession != null) {
        try {
          await gattSession.disconnect(_config.operationTimeout);
        } catch (_) {
          // The native layer may already have closed the BLE connection.
        }
      }
    }
  }

  Future<MatterConnection> connect(MatterConnectRequest request) async {
    final controller = await _requireInitializedController();
    final collector = MatterConnectedDeviceCollector();
    final timeout = request.timeout ?? _config.connectTimeout;
    try {
      await withMatterTimeout<void>(
        future: controller.connectedDevice(request.nodeId, collector),
        timeout: timeout,
        operation: 'Request operational connection',
      );
      final context = await collector.wait(timeout);
      return MatterConnection(nodeId: request.nodeId, context: context);
    } catch (error) {
      if (error is MatterException) {
        rethrow;
      }
      throw MatterException(
        MatterFailureCode.connectFailed,
        'Operational connection failed',
        error,
      );
    }
  }

  Future<void> releaseConnection(MatterConnection connection) async {
    final controller = await _requireInitializedController();
    final context = connection.context;
    if (context == null) {
      return;
    }
    await withMatterTimeout<void>(
      future: controller.releaseConnectContext(context),
      timeout: _config.operationTimeout,
      operation: 'Release operational connection',
    );
  }

  Future<MatterInvokeResult> invokeOnOff(MatterOnOffRequest request) {
    final commandId = switch (request.command) {
      MatterOnOffCommand.off => matterOnOffOffCommandId,
      MatterOnOffCommand.on => matterOnOffOnCommandId,
      MatterOnOffCommand.toggle => matterOnOffToggleCommandId,
    };
    return _invoke(
      nodeId: request.nodeId,
      endpointId: request.endpointId,
      connection: request.connection,
      timedRequestTimeoutMs: request.timedRequestTimeoutMs,
      imTimeoutMs: request.imTimeoutMs,
      clusterId: matterOnOffClusterId,
      commandId: commandId,
      tlv: emptyStructureTlv(),
    );
  }

  Future<MatterInvokeResult> _invoke({
    required int nodeId,
    required int endpointId,
    required MatterConnection? connection,
    required int timedRequestTimeoutMs,
    required int imTimeoutMs,
    required int clusterId,
    required int commandId,
    required Uint8List tlv,
  }) async {
    final controller = await _requireInitializedController();
    final collector = MatterInvokeCollector();
    try {
      await withMatterTimeout<void>(
        future: controller.invoke(
          collector,
          nodeId,
          InvokeElement.create(endpointId, clusterId, commandId, tlv, null),
          connectContext: connection?.context,
          timedRequestTimeoutMs: timedRequestTimeoutMs,
          imTimeoutMs: imTimeoutMs,
        ),
        timeout: _config.operationTimeout,
        operation: 'Send Matter invoke',
      );
      return await collector.wait(_config.operationTimeout);
    } catch (error) {
      if (error is MatterException) {
        rethrow;
      }
      throw MatterException(
        MatterFailureCode.invokeFailed,
        'Matter invoke failed',
        error,
      );
    }
  }

  Future<MatterAttributeValue> readAttribute(
    MatterReadAttributeRequest request,
  ) async {
    final controller = await _requireInitializedController();
    final collector = MatterReadCollector(
      endpointId: request.endpointId,
      clusterId: request.clusterId,
      attributeId: request.attributeId,
    );
    final path = ChipAttributePath(
      endpointId: ChipPathId.forId(request.endpointId),
      clusterId: ChipPathId.forId(request.clusterId),
      attributeId: ChipPathId.forId(request.attributeId),
    );
    try {
      await withMatterTimeout<void>(
        future: controller.read(
          request.nodeId,
          collector,
          [path],
          null,
          null,
          false,
          request.imTimeoutMs,
          0,
          connectContext: request.connection?.context,
        ),
        timeout: _config.operationTimeout,
        operation: 'Request attribute read',
      );
      return await collector.wait(_config.operationTimeout);
    } catch (error) {
      if (error is MatterException) {
        rethrow;
      }
      throw MatterException(
        MatterFailureCode.readFailed,
        'Attribute read failed',
        error,
      );
    }
  }

  Future<String> readNodeLabel({
    required int nodeId,
    MatterConnection? connection,
  }) async {
    final value = await readAttribute(
      MatterReadAttributeRequest(
        nodeId: nodeId,
        clusterId: matterBasicInformationClusterId,
        attributeId: matterNodeLabelAttributeId,
        connection: connection,
      ),
    );
    try {
      return value.decodeString();
    } on MatterTlvException catch (error) {
      throw MatterException(
        MatterFailureCode.readFailed,
        'NodeLabel response was not a string',
        error,
      );
    }
  }

  Future<MatterWriteResult> writeNodeLabel(
    MatterWriteNodeLabelRequest request,
  ) async {
    final controller = await _requireInitializedController();
    final collector = MatterWriteCollector();
    final attribute = AttributeWriteRequest(
      endpointId: ChipPathId.forId(request.endpointId),
      clusterId: ChipPathId.forId(matterBasicInformationClusterId),
      attributeId: ChipPathId.forId(matterNodeLabelAttributeId),
      dataVersion: 0,
      tlv: nodeLabelTlv(request.label),
    );
    try {
      await withMatterTimeout<void>(
        future: controller.write(
          request.nodeId,
          collector,
          [attribute],
          request.timedRequestTimeoutMs,
          request.imTimeoutMs,
          connectContext: request.connection?.context,
        ),
        timeout: _config.operationTimeout,
        operation: 'Request NodeLabel write',
      );
      return await collector.wait(_config.operationTimeout);
    } catch (error) {
      if (error is MatterException) {
        rethrow;
      }
      throw MatterException(
        MatterFailureCode.writeFailed,
        'NodeLabel write failed',
        error,
      );
    }
  }

  Future<MatterSubscription> subscribeAttribute(
    MatterSubscribeRequest request,
  ) async {
    final controller = await _requireInitializedController();
    final subscription = MatterAttributeSubscription(
      nodeId: request.nodeId,
      endpointId: request.endpointId,
      clusterId: request.clusterId,
      attributeId: request.attributeId,
      closeAction: (subscriptionId) =>
          _unsubscribe(nodeId: request.nodeId, subscriptionId: subscriptionId),
    );
    final path = ChipAttributePath(
      endpointId: ChipPathId.forId(request.endpointId),
      clusterId: ChipPathId.forId(request.clusterId),
      attributeId: ChipPathId.forId(request.attributeId),
    );
    try {
      await withMatterTimeout<void>(
        future: controller.subscribe(
          request.nodeId,
          subscription,
          [path],
          null,
          null,
          request.minInterval,
          request.maxInterval,
          request.keepSubscriptions,
          request.isFabricFiltered,
          request.imTimeoutMs,
          request.eventMin,
          connectContext: request.connection?.context,
        ),
        timeout: _config.operationTimeout,
        operation: 'Request Matter subscription',
      );
      await subscription.waitForEstablished(
        request.establishTimeout ?? _config.subscriptionTimeout,
      );
      return subscription;
    } catch (error) {
      if (error is MatterException) {
        rethrow;
      }
      throw MatterException(
        MatterFailureCode.subscribeFailed,
        'Matter subscription failed',
        error,
      );
    }
  }

  Future<MatterSubscription> subscribeOnOff({
    required int nodeId,
    MatterConnection? connection,
  }) {
    return subscribeAttribute(
      MatterSubscribeRequest(
        nodeId: nodeId,
        endpointId: 1,
        clusterId: matterOnOffClusterId,
        attributeId: matterOnOffAttributeId,
        connection: connection,
      ),
    );
  }

  Future<bool> _unsubscribe({
    required int nodeId,
    required int subscriptionId,
  }) async {
    final controller = _requireController();
    final fabricIndex = await withMatterTimeout<int?>(
      future: controller.getFabricIndex(),
      timeout: _config.operationTimeout,
      operation: 'Read controller fabric index',
    );
    if (fabricIndex == null) {
      return false;
    }
    return withMatterTimeout<bool>(
      future: controller.unSubscription(fabricIndex, nodeId, subscriptionId),
      timeout: _config.operationTimeout,
      operation: 'Remove Matter subscription',
    );
  }

  Future<MatterInvokeResult> removeFabric(
    MatterRemoveFabricRequest request,
  ) async {
    final fabricIndex = request.fabricIndex ?? await _readFabricIndex(request);
    return _invoke(
      nodeId: request.nodeId,
      endpointId: request.endpointId,
      connection: request.connection,
      timedRequestTimeoutMs: request.timedRequestTimeoutMs,
      imTimeoutMs: request.imTimeoutMs,
      clusterId: matterOperationalCredentialsClusterId,
      commandId: matterRemoveFabricCommandId,
      tlv: removeFabricCommandTlv(fabricIndex),
    );
  }

  Future<int> _readFabricIndex(MatterRemoveFabricRequest request) async {
    final value = await readAttribute(
      MatterReadAttributeRequest(
        nodeId: request.nodeId,
        endpointId: request.endpointId,
        clusterId: matterOperationalCredentialsClusterId,
        attributeId: matterCurrentFabricIndexAttributeId,
        connection: request.connection,
        imTimeoutMs: request.imTimeoutMs,
      ),
    );
    try {
      return value.decodeUnsigned();
    } on MatterTlvException catch (error) {
      throw MatterException(
        MatterFailureCode.readFailed,
        'CurrentFabricIndex response was not an unsigned integer',
        error,
      );
    }
  }

  Future<MatterControllerPort> _requireInitializedController() async {
    await initialize();
    return _requireController();
  }

  MatterControllerPort _requireController() {
    final controller = _controller;
    if (controller == null) {
      throw MatterException(
        MatterFailureCode.notInitialized,
        'Matter controller is not initialized',
      );
    }
    return controller;
  }

  MatterControllerCredentials _requireCredentials() {
    final credentials = _credentials;
    if (credentials == null) {
      throw MatterException(
        MatterFailureCode.notInitialized,
        'Matter controller credentials are not initialized',
      );
    }
    return credentials;
  }

  Future<void> close() async {
    await _disposeController();
    if (!_commissioningStages.isClosed) {
      await _commissioningStages.close();
    }
  }

  Future<void> purgeCredentials() async {
    await close();
    await _credentialsService.clear();
  }

  Future<void> _disposeController() async {
    final controller = _controller;
    _controller = null;
    _credentials = null;
    if (controller == null) {
      return;
    }
    try {
      await withMatterTimeout<void>(
        future: controller.deleteDeviceController(),
        timeout: _config.operationTimeout,
        operation: 'Delete Matter controller',
      );
    } catch (_) {
      // The controller is already unusable after a failed native cleanup.
    }
  }
}

class _MatterNocChainIssuer implements NOCChainIssuer {
  _MatterNocChainIssuer({
    required this.controller,
    required this.credentials,
    required this.config,
    required this.targetNodeId,
    required this.certificateIssuer,
    required this.onFailure,
    required this.timeout,
  });

  final MatterControllerPort controller;
  final MatterControllerCredentials credentials;
  final MatterControllerConfig config;
  final int targetNodeId;
  final MatterCertificateIssuer certificateIssuer;
  final void Function(Object error) onFailure;
  final Duration timeout;

  @override
  void onNOCChainGenerationNeeded(
    String? onNOCChainGenerationCompleteHandle,
    CSRInfo csrInfo,
    AttestationInfo attestationInfo,
  ) {
    unawaited(_issue(onNOCChainGenerationCompleteHandle, csrInfo));
  }

  Future<void> _issue(String? completionHandle, CSRInfo csrInfo) async {
    try {
      final operationalPublicKey = await withMatterTimeout<Uint8List>(
        future: controller.publicKeyFromCSR(csrInfo.csr),
        timeout: timeout,
        operation: 'Read operational public key from CSR',
      );
      final operationalCertificate = await withMatterTimeout<Uint8List>(
        future: certificateIssuer.createOperationalCertificate(
          signingKeypair: credentials.identity,
          signingCertificate: credentials.rootCertificate,
          operationalPublicKey: operationalPublicKey,
          fabricId: config.fabricId,
          nodeId: targetNodeId,
          caseAuthenticatedTags: null,
        ),
        timeout: timeout,
        operation: 'Issue commissionee operational certificate',
      );
      final generationResult = await withMatterTimeout<int>(
        future: controller.onNOCChainGeneration(
          ControllerParams(
            fabricId: config.fabricId,
            keypairDelegate: credentials.identity,
            rootCertificate: credentials.rootCertificate,
            intermediateCertificate: credentials.rootCertificate,
            operationalCertificate: operationalCertificate,
            ipk: config.ipk,
            nodeId: config.controllerNodeId,
            adminSubject: config.controllerNodeId,
          ),
          onNOCChainGenerationCompleteHandle: completionHandle,
        ),
        timeout: timeout,
        operation: 'Complete NOC chain generation',
      );
      if (generationResult != 0) {
        throw MatterException(
          MatterFailureCode.commissioningFailed,
          'NOC chain generation failed with error code $generationResult',
        );
      }
    } catch (error) {
      onFailure(
        MatterException(
          MatterFailureCode.commissioningFailed,
          'Unable to issue the commissionee NOC chain',
          error,
        ),
      );
    }
  }
}

class _MatterAttestationDelegate implements DeviceAttestationDelegate {
  _MatterAttestationDelegate({
    required this.controller,
    required this.onFailure,
    required this.timeout,
  });

  final MatterControllerPort controller;
  final void Function(Object error) onFailure;
  final Duration timeout;

  @override
  void onDeviceAttestationCompleted(
    int devicePtr,
    AttestationInfo? attestationInfo,
    int errorCode,
  ) {
    unawaited(_continue(devicePtr));
  }

  Future<void> _continue(int devicePtr) async {
    try {
      await withMatterTimeout<void>(
        future: controller.continueCommissioning(devicePtr, true),
        timeout: timeout,
        operation: 'Continue commissioning after attestation',
      );
    } catch (error) {
      onFailure(
        MatterException(
          MatterFailureCode.commissioningFailed,
          'Unable to continue after device attestation',
          error,
        ),
      );
    }
  }
}
