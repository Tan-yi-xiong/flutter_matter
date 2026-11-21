import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'package:bonsoir/bonsoir.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter_matter/flutter_matter.dart';

class MatterNsdMonitor extends ChangeNotifier {
  final List<String> _events = [];
  final List<BonsoirDiscovery> _discoveries = [];
  final List<BonsoirBroadcast> _broadcasts = [];
  bool _enabled = false;

  bool get enabled => _enabled;
  List<String> get events => List.unmodifiable(_events);
  bool get supported => Platform.isAndroid;

  Future<void> enable() async {
    if (_enabled || !supported) {
      return;
    }
    final manager = NsdManager();
    await manager.setResolveHandle(_ResolveHandler(this));
    await manager.setPublishHandle(_PublishHandler(this));
    await manager.setRemoveServices(_RemoveHandler(this));
    _enabled = true;
    _addEvent('NSD monitor enabled');
  }

  Future<void> disable() async {
    if (!_enabled) {
      return;
    }
    final manager = NsdManager();
    await manager.setResolveHandle(null);
    await manager.setPublishHandle(null);
    await manager.setRemoveServices(null);
    await _stopAll();
    _enabled = false;
    _addEvent('NSD monitor disabled');
  }

  void clear() {
    _events.clear();
    notifyListeners();
  }

  void _addEvent(String event) {
    _events.insert(0, event);
    if (_events.length > 80) {
      _events.removeRange(80, _events.length);
    }
    notifyListeners();
  }

  Future<void> _resolve(
    String serviceName,
    String serviceType,
    Future Function(NsdServiceInfo) chipMdnsCallback,
  ) async {
    _addEvent('Resolve request: $serviceName ($serviceType)');
    final discovery = BonsoirDiscovery(type: serviceType, printLogs: false);
    _discoveries.add(discovery);
    StreamSubscription<BonsoirDiscoveryEvent>? subscription;
    Timer? timeout;
    await discovery.initialize();
    subscription = discovery.eventStream?.listen((event) async {
      final service = event.service;
      if (service == null) {
        return;
      }
      if (event is BonsoirDiscoveryServiceFoundEvent) {
        _addEvent('Service found: ${service.name}');
        await service.resolve(discovery.serviceResolver);
        return;
      }
      if (event is! BonsoirDiscoveryServiceResolvedEvent) {
        return;
      }
      if (service.name != serviceName && serviceName.isNotEmpty) {
        return;
      }
      final host = service.host;
      if (host == null || host.trim().isEmpty) {
        return;
      }
      await chipMdnsCallback(
        NsdServiceInfo(
          hostName: host,
          serviceType: service.type,
          serviceName: service.name,
          address: host,
          port: service.port,
          attributes: service.attributes.map(
            (key, value) =>
                MapEntry(key, Uint8List.fromList(utf8.encode(value))),
          ),
        ),
      );
      _addEvent('Service resolved: ${service.name}');
      timeout?.cancel();
      await subscription?.cancel();
      await discovery.stop();
      _discoveries.remove(discovery);
    });
    await discovery.start();
    timeout = Timer(const Duration(seconds: 20), () async {
      _addEvent('Resolve timed out: $serviceName');
      await subscription?.cancel();
      await discovery.stop();
      _discoveries.remove(discovery);
    });
  }

  Future<void> _publish(
    String serviceName,
    String hostName,
    String type,
    int port,
    List<String>? keys,
    List<String>? subTypes,
    List<Uint8List>? values,
  ) async {
    final attributes = <String, String>{};
    final keyList = keys ?? const <String>[];
    final valueList = values ?? const <Uint8List>[];
    for (var index = 0; index < keyList.length; index++) {
      if (index < valueList.length) {
        attributes[keyList[index]] = utf8.decode(
          valueList[index],
          allowMalformed: true,
        );
      }
    }
    final broadcast = BonsoirBroadcast(
      service: BonsoirService(
        name: serviceName,
        type: type,
        port: port,
        attributes: attributes,
      ),
      printLogs: false,
    );
    _broadcasts.add(broadcast);
    await broadcast.initialize();
    await broadcast.start();
    _addEvent('Publish request: $serviceName ($type)');
  }

  Future<void> _removeAll() async {
    _addEvent('Remove services request');
    await _stopBroadcasts();
  }

  Future<void> _stopBroadcasts() async {
    for (final broadcast in [..._broadcasts]) {
      await broadcast.stop();
      _broadcasts.remove(broadcast);
    }
  }

  Future<void> _stopAll() async {
    for (final discovery in [..._discoveries]) {
      await discovery.stop();
      _discoveries.remove(discovery);
    }
    await _stopBroadcasts();
  }

  @override
  void dispose() {
    unawaited(disable());
    super.dispose();
  }
}

class _ResolveHandler implements ResolveCallback {
  _ResolveHandler(this.monitor);

  final MatterNsdMonitor monitor;

  @override
  void resolve(
    String serviceName,
    String serviceType,
    Future Function(NsdServiceInfo) chipMdnsCallback,
  ) {
    unawaited(monitor._resolve(serviceName, serviceType, chipMdnsCallback));
  }
}

class _PublishHandler implements PublishCallback {
  _PublishHandler(this.monitor);

  final MatterNsdMonitor monitor;

  @override
  void publish(
    String serviceName,
    String hostName,
    String type,
    int port,
    List<String>? textEntriesKeys,
    List<String>? subTypes,
    List<Uint8List>? textEntriesDatas,
  ) {
    unawaited(
      monitor._publish(
        serviceName,
        hostName,
        type,
        port,
        textEntriesKeys,
        subTypes,
        textEntriesDatas,
      ),
    );
  }
}

class _RemoveHandler implements RemoveServicesCallback {
  _RemoveHandler(this.monitor);

  final MatterNsdMonitor monitor;

  @override
  void removeServices() {
    unawaited(monitor._removeAll());
  }
}
