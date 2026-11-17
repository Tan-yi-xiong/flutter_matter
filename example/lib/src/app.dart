import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';

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
      home: ExampleScope(controller: _controller, child: const HomePage()),
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

  MatterSessionController() {
    _identityRepository = MatterIdentityRepository(_store);
  }

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
    if (existing != null) {
      return existing;
    }
    identity ??= await _identityRepository.loadOrCreate();
    final created = await ChipDeviceController.newControllerIfNotExist(
      identity!.controllerParams,
    );
    _controller = created;
    return created;
  }

  Future<OperationResult> commission({
    required OnboardingPayload payload,
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
      _controller = result.controller as ChipDeviceController;
      final device = SavedDevice(
        nodeId: result.nodeId,
        vendorId: result.vendorId,
        productId: result.productId,
        label: deviceLabel.trim().isEmpty ? null : deviceLabel.trim(),
        commissionedAt: DateTime.now(),
      );
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
      _controller = result.controller as ChipDeviceController;
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
