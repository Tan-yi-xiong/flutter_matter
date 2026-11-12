import 'wifi_ssid_normalizer.dart';
import 'wifi_ssid_source.dart';

/// Reads the current Wi-Fi SSID without requesting permissions.
///
/// Platform errors, including missing-permission failures, are reported as
/// unavailable so callers can fall back to manual input.
class WifiSsidReader {
  WifiSsidReader({required WifiSsidSource source}) : _source = source;

  final WifiSsidSource _source;

  /// Returns the normalized current SSID, or `null` when unavailable.
  Future<String?> read() async {
    try {
      final raw = await _source.getWifiName();
      return WifiSsidNormalizer.normalize(raw);
    } catch (_) {
      return null;
    }
  }
}
