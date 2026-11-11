import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_matter_method_channel.dart';

abstract class FlutterMatterPlatform extends PlatformInterface {
  /// Constructs a FlutterMatterPlatform.
  FlutterMatterPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterMatterPlatform _instance = MethodChannelFlutterMatter();

  /// The default instance of [FlutterMatterPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterMatter].
  static FlutterMatterPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterMatterPlatform] when
  /// they register themselves.
  static set instance(FlutterMatterPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  void addHandler(MethodCallHandler handler) {
    throw UnimplementedError('addHandler() has not been implemented.');
  }

  void removeHandler(MethodCallHandler handler) {
    throw UnimplementedError('removeHandler() has not been implemented.');
  }

  Future<PlatformResult> requestPlatform(RequestPlatformParams params) {
    throw UnimplementedError('requestPlatform() has not been implemented.');
  }
}
