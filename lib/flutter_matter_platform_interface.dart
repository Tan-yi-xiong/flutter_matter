import 'dart:convert';

import 'package:collection/collection.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'src/exception.dart';
import 'src/platform_transport_types.dart';
import 'src/utils.dart';

part 'src/flutter_matter_method_channel_impl.dart';

/// Transport contract used by controller, BLE, NSD, and onboarding code.
///
/// Platform implementations must provide the MethodChannel transport surface
/// so higher-level APIs never depend on [MethodChannelFlutterMatter] directly.
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

  /// Sends one Dart-to-native request and returns its decoded envelope.
  Future<PlatformResult> requestPlatform(RequestPlatformParams params);

  /// Registers a handler for callbacks initiated by the native platform.
  void addHandler(MethodCallHandler handler);

  /// Removes a previously registered native callback handler.
  void removeHandler(MethodCallHandler handler);
}
