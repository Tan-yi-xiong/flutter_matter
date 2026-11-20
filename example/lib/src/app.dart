import 'dart:async';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_google_home/flutter_matter_google_home.dart';

import 'commissioning_service.dart';
import 'identity.dart';
import 'matter_api_service.dart';
import 'models.dart';
import 'nsd_monitor.dart';
import 'pages/home_page.dart';
import 'storage.dart';

class ExampleApp extends StatefulWidget {
  const ExampleApp({super.key});

  @override
  State<ExampleApp> createState() => _ExampleAppState();
}

class _ExampleAppState extends State<ExampleApp> {
  late final MatterSessionController _controller;

  @override
  void initState() {
    super.initState();
    _controller = MatterSessionController()..initialize();
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    const seed = Color(0xFF25636F);
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Matter API Showcase',
      theme: ThemeData(
        useMaterial3: true,
        colorScheme: ColorScheme.fromSeed(
          seedColor: seed,
          brightness: Brightness.light,
        ),
        scaffoldBackgroundColor: const Color(0xFFF4F7F5),
        cardTheme: const CardThemeData(
          margin: EdgeInsets.zero,
          clipBehavior: Clip.antiAlias,
          elevation: 0,
        ),
        inputDecorationTheme: const InputDecorationTheme(
          border: OutlineInputBorder(),
          isDense: true,
        ),
      ),
      builder: (context, child) {
        return ExampleScope(
          controller: _controller,
          child: SafeArea(child: child ?? const SizedBox.shrink()),
        );
      },
      home: const HomePage(),
    );
  }
}

class ExampleScope extends InheritedNotifier<MatterSessionController> {
  const ExampleScope({
    super.key,
    required MatterSessionController controller,
    required super.child,
  }) : super(notifier: controller);

  static MatterSessionController of(BuildContext context) {
    final scope = context.dependOnInheritedWidgetOfExactType<ExampleScope>();
    assert(scope != null, 'ExampleScope is missing from the widget tree.');
    return scope!.notifier!;
  }
}

class MatterSessionController extends ChangeNotifier {
  final ExampleStore _store = ExampleStore();
  final MatterApiService api = MatterApiService();
  late final MatterIdentityRepository _identityRepository;
  final MatterCommissioningService _commissioningService =
      MatterCommissioningService();
  final MatterNsdMonitor nsd = MatterNsdMonitor();

  final GoogleHomeMatterCommissioner _googleCommissioner =
      GoogleHomeMatterCommissioner();
  GoogleHomeMatterAvailability? googleAvailability;
  GoogleHomeMatterTarget googleTarget =
      GoogleHomeMatterTarget.androidLocalFabric;
  bool googleAvailabilityChecking = false;

  MatterSessionController() {
    _identityRepository = MatterIdentityRepository(_store);
  }

  bool get supportsGoogleCommissioning => Platform.isAndroid;

  MatterIdentity? identity;
  ChipDeviceController? _controller;
  List<SavedDevice> devices = const [];
  SavedDevice? activeDevice;
  Object? connectionContext;
  ConnectionPhase connectionPhase = ConnectionPhase.disconnected;
  bool initialized = false;
  String? initializationError;
  bool operationBusy = false;
  String? currentOperation;
  String? commissioningStage;
  OperationResult? lastResult;
  final List<OperationLogEntry> operationLog = [];

  ChipDeviceController get controller {
    final value = _controller;
    if (value == null) {
      throw StateError('Matter controller has not been created yet.');
    }
    return value;
  }

  Future<({String ssid, String password})?> loadWifiCredentials() {
    return _store.loadWifiCredentials();
  }

  Future<void> saveWifiCredentials(String ssid, String password) {
    return _store.saveWifiCredentials(ssid, password);
  }

  Future<bool> cancelCommissioning() async {
    if (!operationBusy ||
        (currentOperation != 'commissionDevice' &&
            currentOperation != 'googleDualFabric')) {
      return false;
    }
    commissioningStage = 'Cancelling commissioning';
    notifyListeners();
    return _commissioningService.cancelCommissioning();
  }

  void setGoogleTarget(GoogleHomeMatterTarget target) {
    if (googleTarget == target) {
      return;
    }
    googleTarget = target;
    notifyListeners();
  }

  Future<void> checkGoogleAvailability() async {
    if (!supportsGoogleCommissioning || googleAvailabilityChecking) {
      return;
    }
    googleAvailabilityChecking = true;
    notifyListeners();
    try {
      googleAvailability = await _googleCommissioner.checkAvailability();
    } finally {
      googleAvailabilityChecking = false;
      notifyListeners();
    }
  }

  Future<void> requestGoogleModuleInstall() async {
    if (!supportsGoogleCommissioning) {
      return;
    }
    await _googleCommissioner.requestModuleInstall();
    await checkGoogleAvailability();
  }

  Future<OperationResult> commissionGoogleDualFabric({
    OnboardingPayload? payload,
    required String onboardingPayload,
  }) async {
    if (operationBusy) {
      return OperationResult.failure('Another operation is already running.');
    }
    operationBusy = true;
    currentOperation = 'googleDualFabric';
    commissioningStage = 'Preparing Google commissioning';
    lastResult = null;
    notifyListeners();
    try {
      identity ??= await _identityRepository.loadOrCreate();
      final nodeId = await _store.allocateNodeId();
      final outcome = await _commissioningService.commissionGoogleDualFabric(
        identity: identity!,
        nodeId: nodeId,
        onboardingPayload: onboardingPayload,
        target: googleTarget,
        onStage: (stage) {
          commissioningStage = stage;
          notifyListeners();
        },
      );
      _controller = await ensureController();
      final result = outcome.result;
      final device = SavedDevice(
        nodeId: outcome.nodeId,
        vendorId: result.vendorId ?? payload?.vendorId,
        productId: result.productId ?? payload?.productId,
        label: result.deviceName?.trim().isEmpty == false
            ? result.deviceName!.trim()
            : 'Google dual fabric',
        commissionedAt: DateTime.now(),
      );
      await _saveDevice(device);
      activeDevice = device;
      connectionContext = null;
      connectionPhase = ConnectionPhase.disconnected;
      final operationResult = OperationResult(
        success: true,
        summary:
            'Dual-fabric commissioning complete (${result.target.wireName}).',
      );
      lastResult = operationResult;
      _addLog(
        'commissionGoogleDualFabric via startHandoffSession',
        'Google dual fabric',
        operationResult,
      );
      return operationResult;
    } catch (error) {
      final result = OperationResult.failure(
        'Google dual-fabric commissioning failed.',
        error,
      );
      lastResult = result;
      _addLog(
        'commissionGoogleDualFabric via startHandoffSession',
        'Google dual fabric',
        result,
      );
      return result;
    } finally {
      operationBusy = false;
      currentOperation = null;
      notifyListeners();
    }
  }

  void resetCommissioningState() {
    if (operationBusy) {
      return;
    }
    commissioningStage = null;
    lastResult = null;
    notifyListeners();
  }

  bool get isConnected =>
      connectionPhase == ConnectionPhase.connected && connectionContext != null;

  Future<void> initialize() async {
    try {
      identity = await _identityRepository.loadOrCreate();
      devices = await _store.loadDevices();
      initializationError = null;
    } catch (error) {
      initializationError = error.toString();
    } finally {
      initialized = true;
      notifyListeners();
    }
  }

  Future<ChipDeviceController> ensureController() async {
    final existing = _controller;
    if (existing != null && existing.isRunning) {
      return existing;
    }
    _controller = null;
    identity ??= await _identityRepository.loadOrCreate();
    final created = await ChipDeviceController.newControllerIfNotExist(
      identity!.controllerParams,
    );
    _controller = created;
    return created;
  }

  Future<void> _adoptCommissionedController(
    ChipDeviceController controller,
  ) async {
    final previous = _controller;
    _controller = controller;
    if (previous != null && identical(previous, controller)) {
      // The commissioning service acquired one additional reference to the
      // session-owned controller. Collapse that lease without shutting down the
      // native controller.
      await controller.close();
    }
  }

  Future<OperationResult> commission({
    required OnboardingPayload? payload,
    required String onboardingPayload,
    required String ssid,
    required String password,
    required String deviceLabel,
    required bool useAndroidBle,
  }) async {
    if (operationBusy) {
      return OperationResult.failure('Another operation is already running.');
    }
    operationBusy = true;
    currentOperation = 'commissionDevice';
    commissioningStage = 'Preparing commissioning';
    lastResult = null;
    notifyListeners();
    try {
      identity ??= await _identityRepository.loadOrCreate();
      final nodeId = await _store.allocateNodeId();
      final result = await _commissioningService.commission(
        identity: identity!,
        payload: payload,
        onboardingPayload: onboardingPayload,
        ssid: ssid,
        password: password,
        nodeId: nodeId,
        deviceLabel: deviceLabel,
        useAndroidBle: useAndroidBle,
        onStage: (stage) {
          commissioningStage = stage;
          notifyListeners();
        },
      );
      await _adoptCommissionedController(
        result.controller as ChipDeviceController,
      );
      final device = SavedDevice(
        nodeId: result.nodeId,
        vendorId: result.vendorId,
        productId: result.productId,
        label: deviceLabel.trim().isEmpty ? null : deviceLabel.trim(),
        commissionedAt: DateTime.now(),
      );
      // Vendor/product fall back to the parsed payload when the native result
      // does not surface them.
      await _saveDevice(device);
      activeDevice = device;
      connectionContext = null;
      connectionPhase = ConnectionPhase.disconnected;
      final operationResult = OperationResult(
        success: true,
        summary: 'Commissioned ${device.displayName}.',
      );
      lastResult = operationResult;
      _addLog(
        'commissionDevice via pairDevice',
        'Commission device',
        operationResult,
      );
      return operationResult;
    } catch (error) {
      final result = OperationResult.failure('Commissioning failed.', error);
      lastResult = result;
      _addLog('commissionDevice via pairDevice', 'Commission device', result);
      return result;
    } finally {
      operationBusy = false;
      currentOperation = null;
      notifyListeners();
    }
  }

  Future<OperationResult> commissionWithAddress({
    required String address,
    required int port,
    required int discriminator,
    required int setupPin,
    required String deviceLabel,
  }) async {
    if (operationBusy) {
      return OperationResult.failure('Another operation is already running.');
    }
    operationBusy = true;
    currentOperation = 'pairDeviceWithAddress';
    commissioningStage = 'Preparing direct-address commissioning';
    lastResult = null;
    notifyListeners();
    try {
      await disconnect(recordLog: false);
      identity ??= await _identityRepository.loadOrCreate();
      final nodeId = await _store.allocateNodeId();
      final result = await _commissioningService.commissionWithAddress(
        identity: identity!,
        address: address,
        port: port,
        discriminator: discriminator,
        setupPin: setupPin,
        nodeId: nodeId,
        onStage: (stage) {
          commissioningStage = stage;
          notifyListeners();
        },
      );
      await _adoptCommissionedController(
        result.controller as ChipDeviceController,
      );
      final device = SavedDevice(
        nodeId: result.nodeId,
        label: deviceLabel.trim().isEmpty
            ? 'Direct address ${result.nodeId}'
            : deviceLabel.trim(),
        commissionedAt: DateTime.now(),
      );
      await _saveDevice(device);
      activeDevice = device;
      final operationResult = OperationResult(
        success: true,
        summary: 'Commissioned ${device.displayName} by address.',
      );
      lastResult = operationResult;
      _addLog(
        'pairDeviceWithAddress',
        'Direct-address commissioning',
        operationResult,
      );
      return operationResult;
    } catch (error) {
      final result = OperationResult.failure(
        'Direct-address commissioning failed.',
        error,
      );
      lastResult = result;
      _addLog('pairDeviceWithAddress', 'Direct-address commissioning', result);
      return result;
    } finally {
      operationBusy = false;
      currentOperation = null;
      notifyListeners();
    }
  }

  Future<OperationResult> selectDevice(SavedDevice device) async {
    if (activeDevice?.nodeId != device.nodeId) {
      await disconnect(recordLog: false);
    }
    activeDevice = device;
    lastResult = null;
    notifyListeners();
    return const OperationResult(success: true, summary: 'Device selected.');
  }

  Future<OperationResult> connect() async {
    final device = activeDevice;
    if (device == null) {
      return OperationResult.failure('Select a device first.');
    }
    if (isConnected) {
      return const OperationResult(
        success: true,
        summary: 'Device is already connected.',
      );
    }
    if (connectionPhase == ConnectionPhase.connecting) {
      return OperationResult.failure('Connection is already in progress.');
    }
    connectionPhase = ConnectionPhase.connecting;
    notifyListeners();
    try {
      final chipController = await ensureController();
      final context = await api.connect(
        controller: chipController,
        nodeId: device.nodeId,
      );
      connectionContext = context;
      connectionPhase = ConnectionPhase.connected;
      final result = OperationResult(
        success: true,
        summary: 'CASE connection established for ${device.displayName}.',
        detail: context == null ? null : 'Connect context acquired.',
      );
      _addLog('connectedDevice', 'Connect device', result);
      lastResult = result;
      return result;
    } catch (error) {
      connectionContext = null;
      connectionPhase = ConnectionPhase.disconnected;
      final result = OperationResult.failure('Connection failed.', error);
      _addLog('connectedDevice', 'Connect device', result);
      lastResult = result;
      return result;
    } finally {
      notifyListeners();
    }
  }

  Future<OperationResult> disconnect({bool recordLog = true}) async {
    final chipController = _controller;
    final context = connectionContext;
    connectionContext = null;
    connectionPhase = ConnectionPhase.disconnected;
    notifyListeners();
    if (chipController != null && context != null) {
      try {
        await api.releaseContext(chipController, context);
      } catch (error) {
        if (recordLog) {
          final result = OperationResult.failure(
            'Released local state, but the native context release failed.',
            error,
          );
          _addLog('releaseConnectContext', 'Disconnect device', result);
          return result;
        }
      }
    }
    const result = OperationResult(success: true, summary: 'Disconnected.');
    if (recordLog) {
      _addLog('releaseConnectContext', 'Disconnect device', result);
      lastResult = result;
    }
    return result;
  }

  Future<OperationResult> runOperation({
    required String apiName,
    required String title,
    required Future<OperationResult> Function() action,
  }) async {
    if (operationBusy) {
      return OperationResult.failure('Another operation is already running.');
    }
    operationBusy = true;
    currentOperation = apiName;
    lastResult = null;
    notifyListeners();
    try {
      final result = await action();
      lastResult = result;
      _addLog(apiName, title, result);
      return result;
    } catch (error) {
      final result = OperationResult.failure('$title failed.', error);
      lastResult = result;
      _addLog(apiName, title, result);
      return result;
    } finally {
      operationBusy = false;
      currentOperation = null;
      notifyListeners();
    }
  }

  Future<void> _saveDevice(SavedDevice device) async {
    final updated = [...devices]
      ..removeWhere((entry) => entry.nodeId == device.nodeId)
      ..add(device);
    updated.sort((left, right) => left.nodeId.compareTo(right.nodeId));
    devices = updated;
    await _store.saveDevices(devices);
  }

  Future<void> removeLocalDevice(SavedDevice device) async {
    if (activeDevice?.nodeId == device.nodeId) {
      await disconnect(recordLog: false);
      activeDevice = null;
    }
    devices = devices
        .where((entry) => entry.nodeId != device.nodeId)
        .toList(growable: false);
    await _store.saveDevices(devices);
    notifyListeners();
  }

  void addExternalLog(String apiName, String title, OperationResult result) {
    _addLog(apiName, title, result);
    lastResult = result;
    notifyListeners();
  }

  void clearLog() {
    operationLog.clear();
    notifyListeners();
  }

  void _addLog(String apiName, String title, OperationResult result) {
    operationLog.insert(
      0,
      OperationLogEntry(
        timestamp: DateTime.now(),
        api: apiName,
        title: title,
        result: result,
      ),
    );
    if (operationLog.length > 200) {
      operationLog.removeRange(200, operationLog.length);
    }
  }

  @override
  void dispose() {
    final chipController = _controller;
    final context = connectionContext;
    if (chipController != null) {
      unawaited(() async {
        if (context != null) {
          await chipController
              .releaseConnectContext(context)
              .catchError((_) {});
        }
        await chipController.deleteDeviceController().catchError((_) {});
      }());
    }
    nsd.dispose();
    super.dispose();
  }
}
