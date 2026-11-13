import 'package:flutter_matter_device_test_app/main.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  testWidgets('startup failure app renders a safe recovery message', (
    tester,
  ) async {
    await tester.pumpWidget(const DeviceTestStartupFailureApp());

    expect(
      find.textContaining('Device test app initialization failed.'),
      findsOneWidget,
    );
  });
}
