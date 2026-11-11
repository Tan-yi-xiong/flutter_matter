import 'package:flutter_matter_device_test_app/src/app/app.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('generates a stable positive node ID from the Run ID', () {
    const generator = StableTargetNodeIdGenerator();

    final first = generator('run-one');
    final second = generator('run-one');
    final other = generator('run-two');

    expect(first, second);
    expect(first, greaterThan(0));
    expect(other, greaterThan(0));
    expect(other, isNot(first));
  });

  test('rejects an empty Run ID', () {
    const generator = StableTargetNodeIdGenerator();
    expect(() => generator('   '), throwsArgumentError);
  });
}
