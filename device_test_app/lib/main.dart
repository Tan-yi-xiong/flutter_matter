import 'dart:async';

import 'package:flutter/widgets.dart';

import 'src/bootstrap/device_test_app_runtime.dart';
import 'src/presentation/presentation.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  try {
    final runtime = await DeviceTestAppRuntime.create();
    runApp(DeviceTestApplication(runtime: runtime));
  } on Object catch (error) {
    debugPrint('Device test app startup failed: ${error.runtimeType}');
    runApp(const DeviceTestStartupFailureApp());
  }
}

/// Root widget for the dedicated device-test application.
class DeviceTestApplication extends StatefulWidget {
  const DeviceTestApplication({super.key, required this.runtime});

  final DeviceTestAppRuntime runtime;

  @override
  State<DeviceTestApplication> createState() => _DeviceTestApplicationState();
}

class _DeviceTestApplicationState extends State<DeviceTestApplication> {
  @override
  void dispose() {
    unawaited(widget.runtime.close());
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return RepaintBoundary(
      key: widget.runtime.screenshotBoundaryKey,
      child: DeviceTestAppShell(controller: widget.runtime.controller),
    );
  }
}

/// Minimal fallback used when platform plugins or the object graph fail.
class DeviceTestStartupFailureApp extends StatelessWidget {
  const DeviceTestStartupFailureApp({super.key});

  @override
  Widget build(BuildContext context) {
    return WidgetsApp(
      color: const Color(0xFF315A45),
      debugShowCheckedModeBanner: false,
      builder: _buildStartupFailure,
    );
  }

  static Widget _buildStartupFailure(BuildContext context, Widget? child) {
    return const Directionality(
      textDirection: TextDirection.ltr,
      child: ColoredBox(
        color: Color(0xFFF7F9F5),
        child: Center(
          child: Padding(
            padding: EdgeInsets.all(24),
            child: Text(
              'Device test app initialization failed. Build through the '
              'official wrapper and check platform permissions.',
              textAlign: TextAlign.center,
              textDirection: TextDirection.ltr,
              style: TextStyle(color: Color(0xFF18211B), fontSize: 16),
            ),
          ),
        ),
      ),
    );
  }
}
