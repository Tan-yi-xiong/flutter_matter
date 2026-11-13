import 'package:network_info_plus/network_info_plus.dart';

/// Reads the raw Wi-Fi name reported by the platform.
typedef WifiNameReader = Future<String?> Function();

/// Abstracts reading the current Wi-Fi SSID from the platform.
///
/// Implementations must never request permissions or trigger system dialogs;
/// they only report what the platform already exposes.
abstract interface class WifiSsidSource {
  /// Returns the raw platform Wi-Fi name, or `null` when unavailable.
  Future<String?> getWifiName();
}

/// Default [WifiSsidSource] backed by `network_info_plus`.
///
/// The [NetworkInfo] singleton is only constructed when the reader runs, so
/// tests can inject a [WifiNameReader] without touching platform channels.
class NetworkInfoWifiSsidSource implements WifiSsidSource {
  NetworkInfoWifiSsidSource({WifiNameReader? wifiNameReader})
    : _wifiNameReader = wifiNameReader ?? _readNetworkInfoWifiName;

  static Future<String?> _readNetworkInfoWifiName() =>
      NetworkInfo().getWifiName();

  final WifiNameReader _wifiNameReader;

  @override
  Future<String?> getWifiName() => _wifiNameReader();
}
