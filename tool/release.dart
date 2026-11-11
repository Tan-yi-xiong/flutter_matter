import 'dart:io';

const String usage = '''
Usage:
  dart run tool/release.dart validate --tag vX.Y.Z [--pubspec path] [--changelog path]
  dart run tool/release.dart notes --version X.Y.Z [--changelog path]

Commands:
  validate  Validate a stable SemVer tag, pubspec version, and CHANGELOG section.
  notes     Print the CHANGELOG section for a stable version.
''';

final RegExp _stableVersionPattern =
    RegExp(r'^(?:0|[1-9]\d*)\.(?:0|[1-9]\d*)\.(?:0|[1-9]\d*)$');
final RegExp _stableTagPattern =
    RegExp(r'^v(?:0|[1-9]\d*)\.(?:0|[1-9]\d*)\.(?:0|[1-9]\d*)$');
final RegExp _pubspecVersionLinePattern = RegExp(r'^version:[ \t]*([^# \t]+)');
final RegExp _changelogVersionHeadingPattern = RegExp(
  r'^##[ \t]+((?:0|[1-9]\d*)\.(?:0|[1-9]\d*)\.(?:0|[1-9]\d*))[ \t]*$',
);
final RegExp _changelogSectionBoundaryPattern = RegExp(r'^##(?:[ \t]+|$)');

class ReleaseToolException implements Exception {
  const ReleaseToolException(this.message);

  final String message;

  @override
  String toString() => message;
}

class ReleaseMetadata {
  const ReleaseMetadata({
    required this.tag,
    required this.version,
    required this.notes,
  });

  final String tag;
  final String version;
  final String notes;

  String get archiveName => 'flutter_matter-$version.tar.gz';
}

String parseStableReleaseTag(String tag) {
  if (!_stableTagPattern.hasMatch(tag)) {
    throw ReleaseToolException(
      'Invalid release tag "$tag". Expected a stable SemVer tag in the form vX.Y.Z.',
    );
  }
  return tag.substring(1);
}

String parseStableReleaseVersion(String version) {
  if (!_stableVersionPattern.hasMatch(version)) {
    throw ReleaseToolException(
      'Invalid release version "$version". Expected a stable SemVer version in the form X.Y.Z.',
    );
  }
  return version;
}

String parsePubspecVersion(String pubspecContents) {
  String? version;

  for (final line in _normalizedLines(pubspecContents)) {
    final match = _pubspecVersionLinePattern.firstMatch(line);
    if (match == null) {
      continue;
    }

    if (version != null) {
      throw const ReleaseToolException(
        'pubspec.yaml defines the top-level version field more than once.',
      );
    }

    var value = match.group(1)!;
    if (value.length >= 2 &&
        ((value.startsWith('"') && value.endsWith('"')) ||
            (value.startsWith("'") && value.endsWith("'")))) {
      value = value.substring(1, value.length - 1);
    }
    version = parseStableReleaseVersion(value);
  }

  if (version == null) {
    throw const ReleaseToolException(
      'pubspec.yaml does not define a top-level version field.',
    );
  }

  return version;
}

String extractChangelogSection(String changelogContents, String version) {
  final stableVersion = parseStableReleaseVersion(version);
  final lines = _normalizedLines(changelogContents);
  int? sectionStart;

  for (var index = 0; index < lines.length; index++) {
    final match = _changelogVersionHeadingPattern.firstMatch(lines[index]);
    if (match?.group(1) != stableVersion) {
      continue;
    }

    if (sectionStart != null) {
      throw ReleaseToolException(
        'CHANGELOG.md contains more than one section for version $stableVersion.',
      );
    }
    sectionStart = index;
  }

  if (sectionStart == null) {
    throw ReleaseToolException(
      'CHANGELOG.md does not contain a "## $stableVersion" release section.',
    );
  }

  var sectionEnd = lines.length;
  for (var index = sectionStart + 1; index < lines.length; index++) {
    if (_changelogSectionBoundaryPattern.hasMatch(lines[index])) {
      sectionEnd = index;
      break;
    }
  }

  while (
      sectionEnd > sectionStart + 1 && lines[sectionEnd - 1].trim().isEmpty) {
    sectionEnd--;
  }

  return lines.sublist(sectionStart, sectionEnd).join('\n');
}

ReleaseMetadata validateReleaseMetadata({
  required String tag,
  required String pubspecContents,
  required String changelogContents,
}) {
  final version = parseStableReleaseTag(tag);
  final pubspecVersion = parsePubspecVersion(pubspecContents);

  if (version != pubspecVersion) {
    throw ReleaseToolException(
      'Release tag $tag does not match pubspec version $pubspecVersion.',
    );
  }

  final notes = extractChangelogSection(changelogContents, version);
  return ReleaseMetadata(tag: tag, version: version, notes: notes);
}

String runReleaseTool(
  List<String> arguments, {
  String defaultPubspecPath = 'pubspec.yaml',
  String defaultChangelogPath = 'CHANGELOG.md',
}) {
  if (arguments.isEmpty) {
    throw const ReleaseToolException(
      'Missing command. Run with --help for usage.',
    );
  }

  if (arguments.length == 1 &&
      (arguments.single == '--help' || arguments.single == '-h')) {
    return usage.trimRight();
  }

  final command = arguments.first;
  final commandArguments = arguments.sublist(1);

  switch (command) {
    case 'validate':
      final options = _parseOptions(
        commandArguments,
        allowed: const {'--tag', '--pubspec', '--changelog'},
      );
      final tag = _requiredOption(options, '--tag');
      final pubspecPath = options['--pubspec'] ?? defaultPubspecPath;
      final changelogPath = options['--changelog'] ?? defaultChangelogPath;
      final metadata = validateReleaseMetadata(
        tag: tag,
        pubspecContents: _readRequiredFile(pubspecPath, 'pubspec'),
        changelogContents: _readRequiredFile(changelogPath, 'CHANGELOG'),
      );
      return 'Validated ${metadata.tag}: ${metadata.archiveName} is ready.';
    case 'notes':
      final options = _parseOptions(
        commandArguments,
        allowed: const {'--version', '--changelog'},
      );
      final version =
          parseStableReleaseVersion(_requiredOption(options, '--version'));
      final changelogPath = options['--changelog'] ?? defaultChangelogPath;
      return extractChangelogSection(
        _readRequiredFile(changelogPath, 'CHANGELOG'),
        version,
      );
    default:
      throw ReleaseToolException(
        'Unknown command "$command". Run with --help for usage.',
      );
  }
}

Map<String, String> _parseOptions(
  List<String> arguments, {
  required Set<String> allowed,
}) {
  if (arguments.length.isOdd) {
    throw const ReleaseToolException(
      'Every option must be followed by a value. Run with --help for usage.',
    );
  }

  final options = <String, String>{};
  for (var index = 0; index < arguments.length; index += 2) {
    final name = arguments[index];
    final value = arguments[index + 1];
    if (!allowed.contains(name)) {
      throw ReleaseToolException(
        'Unknown option "$name". Run with --help for usage.',
      );
    }
    if (options.containsKey(name)) {
      throw ReleaseToolException('Option "$name" was provided more than once.');
    }
    if (value.isEmpty) {
      throw ReleaseToolException('Option "$name" requires a non-empty value.');
    }
    options[name] = value;
  }
  return options;
}

String _requiredOption(Map<String, String> options, String name) {
  final value = options[name];
  if (value == null) {
    throw ReleaseToolException(
      'Missing required option "$name". Run with --help for usage.',
    );
  }
  return value;
}

String _readRequiredFile(String path, String label) {
  final file = File(path);
  if (!file.existsSync()) {
    throw ReleaseToolException('$label file not found at "$path".');
  }
  return file.readAsStringSync();
}

List<String> _normalizedLines(String contents) =>
    contents.replaceAll('\r\n', '\n').replaceAll('\r', '\n').split('\n');

void main(List<String> arguments) {
  try {
    stdout.writeln(runReleaseTool(arguments));
  } on ReleaseToolException catch (error) {
    stderr.writeln('release: ${error.message}');
    exitCode = 1;
  } on FileSystemException catch (error) {
    final path = error.path == null ? '' : ' (${error.path})';
    stderr.writeln('release: could not read file$path: ${error.message}');
    exitCode = 1;
  }
}
