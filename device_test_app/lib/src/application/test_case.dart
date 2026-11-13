import '../domain/domain.dart';
import 'test_context.dart';

/// A terminal outcome returned by a test case.
///
/// Running and pending states are owned exclusively by the coordinator.
class TestCaseOutcome {
  const TestCaseOutcome._(this.status, this.notes);

  const TestCaseOutcome.passed({String? notes})
    : this._(DeviceTestStatus.passed, notes);

  factory TestCaseOutcome.failed(String notes) =>
      TestCaseOutcome._(DeviceTestStatus.failed, _requiredNote(notes));

  factory TestCaseOutcome.notRun(String reason) =>
      TestCaseOutcome._(DeviceTestStatus.notRun, _requiredNote(reason));

  final DeviceTestStatus status;
  final String? notes;

  bool get isPass => status == DeviceTestStatus.passed;

  bool get isNotRun => status == DeviceTestStatus.notRun;
}

String _requiredNote(String value) {
  final trimmed = value.trim();
  if (trimmed.isEmpty) {
    throw ArgumentError.value(value, 'notes', 'Must not be empty');
  }
  return trimmed;
}

abstract interface class DeviceTestCase {
  DeviceTestId get id;

  Future<TestCaseOutcome> execute(TestContext context);
}
