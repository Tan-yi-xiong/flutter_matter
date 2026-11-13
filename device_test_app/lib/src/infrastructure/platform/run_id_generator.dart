import 'package:uuid/uuid.dart';

class RunIdGenerator {
  const RunIdGenerator({Uuid uuid = const Uuid()}) : _uuid = uuid;

  final Uuid _uuid;

  String next() {
    final timestamp = DateTime.now().toUtc().toIso8601String().replaceAll(
      RegExp(r'[^0-9]'),
      '',
    );
    final suffix = _uuid.v4().replaceAll('-', '').substring(0, 8);
    return 'run-$timestamp-$suffix';
  }
}
