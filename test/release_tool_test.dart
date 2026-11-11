import 'package:flutter_test/flutter_test.dart';

import '../tool/release.dart';

const _pubspec = '''
name: flutter_matter
version: 0.0.11 # release version
environment:
  sdk: '>=3.3.3 <4.0.0'
''';

const _changelog = '''
# Changelog

## Unreleased

### Improvements
- Work in progress.

## 0.0.11

### Bug Fixes
- Fixed release notes boundaries.

### Documentation
- Kept the exact section heading.

## 0.0.10

### Improvements
- Previous release.
''';

void main() {
  group('validateReleaseMetadata', () {
    test('accepts matching stable metadata and extracts its section', () {
      final metadata = validateReleaseMetadata(
        tag: 'v0.0.11',
        pubspecContents: _pubspec,
        changelogContents: _changelog,
      );

      expect(metadata.tag, 'v0.0.11');
      expect(metadata.version, '0.0.11');
      expect(metadata.archiveName, 'flutter_matter-0.0.11.tar.gz');
      expect(metadata.notes, '''
## 0.0.11

### Bug Fixes
- Fixed release notes boundaries.

### Documentation
- Kept the exact section heading.''');
    });

    test('rejects a tag that does not match the pubspec version', () {
      expect(
        () => validateReleaseMetadata(
          tag: 'v0.0.12',
          pubspecContents: _pubspec,
          changelogContents: _changelog,
        ),
        throwsA(
          isA<ReleaseToolException>().having(
            (error) => error.message,
            'message',
            contains('does not match pubspec version 0.0.11'),
          ),
        ),
      );
    });

    test('rejects a version missing from the changelog', () {
      expect(
        () => validateReleaseMetadata(
          tag: 'v0.0.12',
          pubspecContents: 'name: flutter_matter\nversion: 0.0.12\n',
          changelogContents: _changelog,
        ),
        throwsA(
          isA<ReleaseToolException>().having(
            (error) => error.message,
            'message',
            contains('does not contain a "## 0.0.12" release section'),
          ),
        ),
      );
    });
  });

  group('extractChangelogSection', () {
    test('stops at the next level-two heading only', () {
      final notes = extractChangelogSection(_changelog, '0.0.11');

      expect(notes, startsWith('## 0.0.11'));
      expect(notes, contains('### Bug Fixes'));
      expect(notes, isNot(contains('## Unreleased')));
      expect(notes, isNot(contains('## 0.0.10')));
      expect(notes, isNot(contains('Previous release.')));
    });

    test('normalizes CRLF input and trims only trailing blank lines', () {
      const contents = '## 0.0.11\r\n\r\nBody\r\n\r\n## 0.0.10\r\nOld\r\n';
      final notes = extractChangelogSection(contents, '0.0.11');

      expect(notes, '## 0.0.11\n\nBody');
    });

    test('rejects duplicate sections for the requested version', () {
      const contents = '## 0.0.11\nFirst\n## 0.0.11\nSecond\n';

      expect(
        () => extractChangelogSection(contents, '0.0.11'),
        throwsA(
          isA<ReleaseToolException>().having(
            (error) => error.message,
            'message',
            contains('more than one section'),
          ),
        ),
      );
    });

    test('rejects malformed or non-stable changelog headings', () {
      for (final contents in <String>[
        '## 0.0\nBody\n',
        '## v0.0.11\nBody\n',
        '### 0.0.11\nBody\n',
      ]) {
        expect(
          () => extractChangelogSection(contents, '0.0.11'),
          throwsA(isA<ReleaseToolException>()),
          reason: contents,
        );
      }
    });
  });

  group('malformed input', () {
    test('rejects malformed stable tag shapes', () {
      for (final tag in <String>[
        '0.0.11',
        'v0.0',
        'v00.0.11',
        'v0.0.11-beta',
        'v0.0.11+build',
      ]) {
        expect(
          () => parseStableReleaseTag(tag),
          throwsA(isA<ReleaseToolException>()),
          reason: tag,
        );
      }
    });

    test('rejects malformed stable version shapes', () {
      for (final version in <String>[
        '0.0',
        '00.0.11',
        'v0.0.11',
        '0.0.11-beta',
        '0.0.11+build',
      ]) {
        expect(
          () => parseStableReleaseVersion(version),
          throwsA(isA<ReleaseToolException>()),
          reason: version,
        );
      }
    });

    test('rejects pubspec contents without a stable version', () {
      expect(
        () => parsePubspecVersion('name: flutter_matter\n'),
        throwsA(
          isA<ReleaseToolException>().having(
            (error) => error.message,
            'message',
            contains('does not define a top-level version field'),
          ),
        ),
      );
      expect(
        () => parsePubspecVersion('version: 0.0.11-beta\n'),
        throwsA(isA<ReleaseToolException>()),
      );
    });
  });
}
