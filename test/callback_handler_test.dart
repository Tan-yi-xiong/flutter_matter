import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/src/callback_handler.dart';

class ProbeCallbackPayload {}

class ProbeCallbackHandler extends CallbackHandler<ProbeCallbackPayload> {
  String? lastMethod;
  dynamic lastArguments;

  @override
  dynamic onCallbackMethodCall(String methodName, dynamic arguments) {
    lastMethod = methodName;
    lastArguments = arguments;
    return 'handled';
  }
}

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  test('CallbackHandler matches its generic callback route', () {
    final handler = ProbeCallbackHandler();

    expect(handler.match('zgMatter://ignored/ProbeCallbackPayload/onEvent', {}),
        isTrue);
    expect(
        handler.match('zgMatter://ignored/OtherCallback/onEvent', {}), isFalse);
  });

  test('CallbackHandler forwards the path after the callback type', () {
    final handler = ProbeCallbackHandler();
    final result = handler.call(
      'zgMatter://ignored/ProbeCallbackPayload/onEvent/detail',
      {'value': 1},
    );

    expect(result, 'handled');
    expect(handler.lastMethod, 'onEvent/detail');
    expect(handler.lastArguments, {'value': 1});
  });

  test('CallbackHandler adds and removes callback instances', () {
    final handler = ProbeCallbackHandler();
    final callback = ProbeCallbackPayload();
    final handle = handler.addHandler(callback);

    expect(handler.handlers[handle], same(callback));
    expect(handler.removeHandler(handle), isTrue);
    expect(handler.handlers, isEmpty);
    expect(handler.removeHandler(handle), isFalse);
  });
}
