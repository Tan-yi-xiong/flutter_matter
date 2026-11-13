/// Produces adapter-owned handles without exposing transport identifiers.
class OpaqueHandleFactory {
  OpaqueHandleFactory({DateTime Function()? clock})
    : _clock = clock ?? DateTime.now;

  final DateTime Function() _clock;
  int _sequence = 0;

  String next(String namespace) {
    final prefix = namespace.trim();
    if (prefix.isEmpty) {
      throw ArgumentError.value(namespace, 'namespace', 'Must not be empty');
    }
    return '$prefix-${_clock().microsecondsSinceEpoch}-${_sequence++}';
  }
}
