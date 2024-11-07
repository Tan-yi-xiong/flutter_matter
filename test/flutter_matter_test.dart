import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter/flutter_matter_platform_interface.dart';
import 'package:flutter_matter/flutter_matter_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFlutterMatterPlatform
    with MockPlatformInterfaceMixin
    implements FlutterMatterPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final FlutterMatterPlatform initialPlatform = FlutterMatterPlatform.instance;

  test('$MethodChannelFlutterMatter is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFlutterMatter>());
  });

  test('getPlatformVersion', () async {
    FlutterMatter flutterMatterPlugin = FlutterMatter();
    MockFlutterMatterPlatform fakePlatform = MockFlutterMatterPlatform();
    FlutterMatterPlatform.instance = fakePlatform;

    expect(await flutterMatterPlugin.getPlatformVersion(), '42');
  });
}
