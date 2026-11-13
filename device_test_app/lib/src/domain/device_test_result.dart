import 'device_test_catalog.dart';

enum DeviceTestStatus {
  pending('pending'),
  running('running'),
  passed('passed'),
  failed('failed'),
  notRun('not_run');

  const DeviceTestStatus(this.wireName);

  final String wireName;

  bool get isTerminal => this != pending && this != running;

  static DeviceTestStatus parse(String value) {
    for (final status in values) {
      if (status.wireName == value) {
        return status;
      }
    }
    throw FormatException('Unknown device test status: $value');
  }
}

class DeviceTestResult {
  DeviceTestResult({
    required this.testId,
    this.status = DeviceTestStatus.pending,
    this.duration = Duration.zero,
    String? notes,
    Iterable<String> evidenceFiles = const <String>[],
  }) : notes = _emptyToNull(notes),
       evidenceFiles = List<String>.unmodifiable(evidenceFiles) {
    if (duration.isNegative) {
      throw ArgumentError.value(duration, 'duration', 'Must not be negative');
    }
  }

  final DeviceTestId testId;
  final DeviceTestStatus status;
  final Duration duration;
  final String? notes;
  final List<String> evidenceFiles;

  bool get isTerminal => status.isTerminal;

  factory DeviceTestResult.fromJson(
    DeviceTestId testId,
    Map<String, dynamic> json,
  ) {
    final durationMs = json['duration_ms'];
    if (durationMs is! int) {
      throw const FormatException('duration_ms must be an integer');
    }

    final rawNotes = json['notes'];
    if (rawNotes != null && rawNotes is! String) {
      throw const FormatException('notes must be a string');
    }

    final rawEvidenceFiles = json['evidence_files'];
    if (rawEvidenceFiles != null && rawEvidenceFiles is! List<dynamic>) {
      throw const FormatException('evidence_files must be an array');
    }
    final evidenceFiles = <String>[];
    if (rawEvidenceFiles != null) {
      for (final value in rawEvidenceFiles as List<dynamic>) {
        if (value is! String) {
          throw const FormatException('evidence_files must contain strings');
        }
        evidenceFiles.add(value);
      }
    }

    return DeviceTestResult(
      testId: testId,
      status: DeviceTestStatus.parse(_requiredString(json, 'status')),
      duration: Duration(milliseconds: durationMs),
      notes: rawNotes as String?,
      evidenceFiles: evidenceFiles,
    );
  }

  DeviceTestResult copyWith({
    DeviceTestStatus? status,
    Duration? duration,
    String? notes,
    bool clearNotes = false,
    Iterable<String>? evidenceFiles,
  }) {
    return DeviceTestResult(
      testId: testId,
      status: status ?? this.status,
      duration: duration ?? this.duration,
      notes: clearNotes ? null : notes ?? this.notes,
      evidenceFiles: evidenceFiles ?? this.evidenceFiles,
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'status': status.wireName,
    'duration_ms': duration.inMilliseconds,
    if (notes != null) 'notes': notes,
    if (evidenceFiles.isNotEmpty) 'evidence_files': evidenceFiles,
  };
}

String? _emptyToNull(String? value) {
  if (value == null || value.trim().isEmpty) {
    return null;
  }
  return value;
}

String _requiredString(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! String) {
    throw FormatException('$key must be a string');
  }
  return value;
}
