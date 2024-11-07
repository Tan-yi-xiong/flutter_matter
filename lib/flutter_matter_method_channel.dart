import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutter_matter_platform_interface.dart';

/// An implementation of [FlutterMatterPlatform] that uses method channels.
class MethodChannelFlutterMatter extends FlutterMatterPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_matter');

  
}
