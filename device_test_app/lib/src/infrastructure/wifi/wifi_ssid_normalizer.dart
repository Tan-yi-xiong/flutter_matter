/// Normalizes platform Wi-Fi SSID values.
///
/// Android reports quoted SSIDs and several platforms report sentinel values
/// when location permission is missing or Wi-Fi is not connected.
class WifiSsidNormalizer {
  const WifiSsidNormalizer._();

  static const Set<String> _sentinels = <String>{'unknown', '<unknown ssid>'};

  /// Returns the normalized SSID, or `null` when the value is missing, blank,
  /// a platform sentinel, or only padding around a sentinel.
  static String? normalize(String? raw) {
    if (raw == null) {
      return null;
    }
    var value = raw.trim();
    if (value.length >= 2 && value.startsWith('"') && value.endsWith('"')) {
      value = value.substring(1, value.length - 1).trim();
    }
    if (value.isEmpty) {
      return null;
    }
    if (_sentinels.contains(value.toLowerCase())) {
      return null;
    }
    return value;
  }
}
