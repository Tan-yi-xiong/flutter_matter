import 'package:flutter_matter_device_test_app/src/infrastructure/wifi/wifi.dart';
import 'package:flutter_test/flutter_test.dart';

class _StubWifiSsidSource implements WifiSsidSource {
  _StubWifiSsidSource(Future<String?> Function() resolver)
    : _resolver = resolver;

  final Future<String?> Function() _resolver;

  @override
  Future<String?> getWifiName() => _resolver();
}

void main() {
  group('WifiSsidNormalizer', () {
    test('keeps plain SSIDs', () {
      expect(WifiSsidNormalizer.normalize('HomeNet'), 'HomeNet');
    });

    test('strips surrounding padding and matching double quotes', () {
      expect(WifiSsidNormalizer.normalize('  Office  '), 'Office');
      expect(WifiSsidNormalizer.normalize('"Quoted"'), 'Quoted');
      expect(
        WifiSsidNormalizer.normalize('  "  Spaced Net  "  '),
        'Spaced Net',
      );
      expect(WifiSsidNormalizer.normalize('""'), isNull);
    });

    test('preserves inner whitespace and special characters', () {
      expect(WifiSsidNormalizer.normalize('Home Net #1'), 'Home Net #1');
      expect(WifiSsidNormalizer.normalize('"Weird "Net"'), 'Weird "Net');
    });

    test('treats sentinels and blanks as unavailable', () {
      const unavailable = <String?>[
        null,
        '',
        '   ',
        '\t\n',
        'unknown',
        'UNKNOWN',
        'Unknown',
        '<unknown ssid>',
        '<UNKNOWN SSID>',
        '"<unknown ssid>"',
        ' "<unknown ssid>" ',
        '"unknown"',
      ];
      for (final raw in unavailable) {
        expect(WifiSsidNormalizer.normalize(raw), isNull, reason: '$raw');
      }
    });
  });

  group('WifiSsidReader', () {
    test('returns the normalized SSID from the source', () async {
      final reader = WifiSsidReader(
        source: _StubWifiSsidSource(() async => '"  Home Net  "'),
      );

      expect(await reader.read(), 'Home Net');
    });

    test('reports sentinel values as unavailable', () async {
      final reader = WifiSsidReader(
        source: _StubWifiSsidSource(() async => '<unknown ssid>'),
      );

      expect(await reader.read(), isNull);
    });

    test('reports source errors as unavailable', () async {
      final reader = WifiSsidReader(
        source: _StubWifiSsidSource(
          () async => throw StateError('platform failure'),
        ),
      );

      expect(await reader.read(), isNull);
    });
  });

  group('NetworkInfoWifiSsidSource', () {
    test('delegates to the injected reader', () async {
      final source = NetworkInfoWifiSsidSource(
        wifiNameReader: () async => '"Raw"',
      );

      expect(await source.getWifiName(), '"Raw"');
    });
  });
}
