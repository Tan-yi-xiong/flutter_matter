import 'dart:convert';

import 'package:shared_preferences/shared_preferences.dart';

import 'models.dart';

class ExampleStore {
  static const _devicesKey = 'devices';
  static const _maxNodeIdKey = 'last_node_id';
  static const _wifiSsidKey = 'commissioning_wifi_ssid';
  static const _wifiPasswordKey = 'commissioning_wifi_password';
  static const _keypairKey = 'network_keypair';
  static const _certificateKey = 'network_certificate';

  Future<List<SavedDevice>> loadDevices() async {
    final preferences = await SharedPreferences.getInstance();
    final encoded = preferences.getString(_devicesKey);
    if (encoded == null || encoded.isEmpty) {
      return const [];
    }
    try {
      final decoded = jsonDecode(encoded);
      if (decoded is! List) {
        return const [];
      }
      return decoded
          .whereType<Map>()
          .map((entry) => SavedDevice.fromJson(entry.cast<String, dynamic>()))
          .toList(growable: false);
    } catch (_) {
      return const [];
    }
  }

  Future<void> saveDevices(List<SavedDevice> devices) async {
    final preferences = await SharedPreferences.getInstance();
    await preferences.setString(
      _devicesKey,
      jsonEncode(devices.map((device) => device.toJson()).toList()),
    );
  }

  Future<int> allocateNodeId() async {
    final preferences = await SharedPreferences.getInstance();
    final current = preferences.getInt(_maxNodeIdKey) ?? 0;
    final next = current + 1;
    await preferences.setInt(_maxNodeIdKey, next);
    return next;
  }

  Future<String?> readKeypairJson() async {
    final preferences = await SharedPreferences.getInstance();
    return preferences.getString(_keypairKey);
  }

  Future<String?> readCertificateJson() async {
    final preferences = await SharedPreferences.getInstance();
    return preferences.getString(_certificateKey);
  }

  Future<void> saveIdentity(String keypairJson, String certificateJson) async {
    final preferences = await SharedPreferences.getInstance();
    await preferences.setString(_keypairKey, keypairJson);
    await preferences.setString(_certificateKey, certificateJson);
  }

  Future<({String ssid, String password})?> loadWifiCredentials() async {
    final preferences = await SharedPreferences.getInstance();
    final ssid = preferences.getString(_wifiSsidKey);
    final password = preferences.getString(_wifiPasswordKey);
    if (ssid == null || password == null) {
      return null;
    }
    return (ssid: ssid, password: password);
  }

  Future<void> saveWifiCredentials(String ssid, String password) async {
    final preferences = await SharedPreferences.getInstance();
    await preferences.setString(_wifiSsidKey, ssid);
    await preferences.setString(_wifiPasswordKey, password);
  }
}
