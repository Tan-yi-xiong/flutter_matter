/// A sensitive-data category found in report content.
class SensitiveDataFinding {
  const SensitiveDataFinding({required this.path, required this.category});

  final String path;
  final String category;

  @override
  String toString() => '$path contains $category';
}

/// Conservative scanning for values that must never appear in public evidence.
///
/// Commit fields are intentionally scanned too because a raw 40-character hex
/// value is not identifiable as an iOS UDID without context. The policy only
/// rejects contextual UDID assignments, not legitimate report commits.
abstract final class SensitiveDataPolicy {
  static final List<({String category, RegExp pattern})>
  patterns = List<({String category, RegExp pattern})>.unmodifiable(<
    ({String category, RegExp pattern})
  >[
    (
      category: 'a private key',
      pattern: RegExp(
        r'-----BEGIN [A-Z0-9 ]*PRIVATE KEY-----',
        caseSensitive: false,
      ),
    ),
    (
      category: 'a certificate',
      pattern: RegExp(r'-----BEGIN CERTIFICATE-----', caseSensitive: false),
    ),
    (
      category: 'a device address',
      pattern: RegExp(
        r'(?<![0-9A-Fa-f])(?:[0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}(?![0-9A-Fa-f])',
      ),
    ),
    (
      category: 'an onboarding payload',
      pattern: RegExp(r'\bMT:[A-Za-z0-9+/=_-]{4,}'),
    ),
    (
      category: 'a provisioning secret',
      pattern: RegExp(
        r'\b(?:password|passwd|pass|ssid|serial(?:[ _-]?number)?|udid|'
        r'setup[ _-]?code|manual[ _-]?code|pairing[ _-]?code|'
        r'onboarding[ _-]?payload|wifi[ _-]?(?:password|credentials)|'
        r'ble[ _-]?address)\s*[:=]\s*\S+',
        caseSensitive: false,
      ),
    ),
  ]);

  static List<SensitiveDataFinding> scan(Object? value) {
    final findings = <SensitiveDataFinding>[];
    _scan(value, r'$', findings);
    return List<SensitiveDataFinding>.unmodifiable(findings);
  }

  static bool containsSensitiveData(Object? value) => scan(value).isNotEmpty;

  static void _scan(
    Object? value,
    String path,
    List<SensitiveDataFinding> findings,
  ) {
    if (value is String) {
      for (final entry in patterns) {
        if (entry.pattern.hasMatch(value)) {
          findings.add(
            SensitiveDataFinding(path: path, category: entry.category),
          );
        }
      }
      return;
    }

    if (value is Map) {
      for (final entry in value.entries) {
        final key = entry.key.toString();
        _scan(entry.value, '$path.$key', findings);
      }
      return;
    }

    if (value is Iterable) {
      var index = 0;
      for (final item in value) {
        _scan(item, '$path[$index]', findings);
        index++;
      }
    }
  }
}
