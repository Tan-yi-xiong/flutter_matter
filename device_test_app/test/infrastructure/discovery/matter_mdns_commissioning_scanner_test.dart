import 'dart:async';

import 'package:flutter_matter_device_test_app/src/infrastructure/discovery/discovery.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('MatterMdnsDiscriminatorMatcher', () {
    test('matches a full discriminator from the D attribute', () {
      expect(
        MatterMdnsDiscriminatorMatcher.matches(
          attributes: const <String, String>{'D': '3841'},
          discriminator: 3841,
          hasShortDiscriminator: false,
        ),
        isTrue,
      );
    });

    test('matches a short discriminator against the high nibble', () {
      expect(
        MatterMdnsDiscriminatorMatcher.matches(
          attributes: const <String, String>{'D': '3841'},
          discriminator: 0xf,
          hasShortDiscriminator: true,
        ),
        isTrue,
      );
    });

    test('accepts a hexadecimal D attribute', () {
      expect(
        MatterMdnsDiscriminatorMatcher.matches(
          attributes: const <String, String>{'D': '0xF01'},
          discriminator: 3841,
          hasShortDiscriminator: false,
        ),
        isTrue,
      );
    });

    test('rejects missing and malformed attributes', () {
      expect(
        MatterMdnsDiscriminatorMatcher.matches(
          attributes: const <String, String>{},
          discriminator: 3841,
          hasShortDiscriminator: false,
        ),
        isFalse,
      );
      expect(
        MatterMdnsDiscriminatorMatcher.matches(
          attributes: const <String, String>{'D': 'not-a-number'},
          discriminator: 3841,
          hasShortDiscriminator: false,
        ),
        isFalse,
      );
    });
  });

  group('MatterMdnsCommissioningScanner', () {
    test('resolves an unresolved service and matches its attributes', () async {
      final browser = _FakeMatterMdnsBrowser();
      final scanner = MatterMdnsCommissioningScanner(
        browserFactory: () => browser,
      );

      final result = scanner.waitForMatch(
        discriminator: 3841,
        hasShortDiscriminator: false,
        timeout: const Duration(seconds: 1),
      );

      await browser.started.future;
      browser.add(
        MatterMdnsService(
          name: 'unresolved',
          type: matterCommissionableServiceType,
          attributes: const <String, String>{},
          resolve: () async {
            browser.add(
              const MatterMdnsService(
                name: 'resolved',
                type: matterCommissionableServiceType,
                attributes: <String, String>{'D': '3841'},
              ),
            );
          },
        ),
      );

      expect(await result, isTrue);
      expect(browser.stopCount, 1);
    });

    test('returns false on timeout and stops the browser', () async {
      final browser = _FakeMatterMdnsBrowser();
      final scanner = MatterMdnsCommissioningScanner(
        browserFactory: () => browser,
      );

      expect(
        await scanner.waitForMatch(
          discriminator: 3841,
          hasShortDiscriminator: false,
          timeout: const Duration(milliseconds: 5),
        ),
        isFalse,
      );
      expect(browser.stopCount, 1);
    });
  });
}

class _FakeMatterMdnsBrowser implements MatterMdnsBrowser {
  final StreamController<MatterMdnsService> _controller =
      StreamController<MatterMdnsService>.broadcast();
  final Completer<void> started = Completer<void>();
  int stopCount = 0;

  void add(MatterMdnsService service) => _controller.add(service);

  @override
  Stream<MatterMdnsService> get services => _controller.stream;

  @override
  Future<void> start() async {
    started.complete();
  }

  @override
  Future<void> stop() async {
    stopCount++;
    await _controller.close();
  }
}
