import 'dart:convert';

/// Produces a positive target node ID for one Run.
typedef TargetNodeIdFactory = int Function(String runId);

/// Generates a deterministic, positive, 63-bit node ID from the Run ID.
///
/// The coordinator persists the generated value with the Run, so both resume
/// and report generation observe exactly the same target node ID.
class StableTargetNodeIdGenerator {
  const StableTargetNodeIdGenerator();

  static final BigInt _offsetBasis = BigInt.parse('14695981039346656037');
  static final BigInt _prime = BigInt.parse('1099511628211');
  static final BigInt _uint64Mask = (BigInt.one << 64) - BigInt.one;
  static final BigInt _positiveMask = (BigInt.one << 63) - BigInt.one;

  int call(String runId) {
    if (runId.trim().isEmpty) {
      throw ArgumentError.value(runId, 'runId', 'Must not be empty');
    }
    var hash = _offsetBasis;
    for (final byte in utf8.encode(runId)) {
      hash ^= BigInt.from(byte);
      hash = (hash * _prime) & _uint64Mask;
    }
    final value = (hash & _positiveMask).toInt();
    return value == 0 ? 1 : value;
  }
}
