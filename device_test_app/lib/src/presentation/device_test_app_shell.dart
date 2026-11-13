import 'package:flutter/material.dart';

import 'screens/home_screen.dart';
import 'screens/results_screen.dart';
import 'screens/runner_screen.dart';
import 'screens/setup_screen.dart';
import 'ui_controller.dart';
import 'ui_models.dart';

/// Root presentation widget for the dedicated device-test app.
///
/// The app bootstrap owns controller construction and secret storage. This
/// widget only renders immutable state and forwards user intent.
class DeviceTestAppShell extends StatefulWidget {
  const DeviceTestAppShell({
    super.key,
    required this.controller,
    this.initialScreen = DeviceTestScreen.home,
  });

  final DeviceTestUiController controller;
  final DeviceTestScreen initialScreen;

  @override
  State<DeviceTestAppShell> createState() => _DeviceTestAppShellState();
}

class _DeviceTestAppShellState extends State<DeviceTestAppShell> {
  late DeviceTestScreen _screen;

  @override
  void initState() {
    super.initState();
    _screen = widget.initialScreen;
    widget.controller.addListener(_handleControllerChanged);
  }

  @override
  void didUpdateWidget(covariant DeviceTestAppShell oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.controller != widget.controller) {
      oldWidget.controller.removeListener(_handleControllerChanged);
      widget.controller.addListener(_handleControllerChanged);
    }
  }

  @override
  void dispose() {
    widget.controller.removeListener(_handleControllerChanged);
    super.dispose();
  }

  void _handleControllerChanged() {
    if (!mounted) {
      return;
    }
    setState(() {
      _screen = widget.controller.state.screen;
    });
  }

  @override
  Widget build(BuildContext context) {
    final state = widget.controller.state;
    return MaterialApp(
      title: 'Flutter Matter Device Test',
      debugShowCheckedModeBanner: false,
      theme: _theme(Brightness.light),
      darkTheme: _theme(Brightness.dark),
      themeMode: ThemeMode.system,
      home: switch (_screen) {
        DeviceTestScreen.home => HomeScreen(
          controller: widget.controller,
          state: state,
        ),
        DeviceTestScreen.setup => SetupScreen(
          controller: widget.controller,
          state: state,
        ),
        DeviceTestScreen.runner => RunnerScreen(
          controller: widget.controller,
          state: state,
        ),
        DeviceTestScreen.results => ResultsScreen(
          controller: widget.controller,
          state: state,
        ),
      },
    );
  }

  ThemeData _theme(Brightness brightness) {
    final scheme = ColorScheme.fromSeed(
      seedColor: const Color(0xFF315A45),
      brightness: brightness,
    );
    return ThemeData(
      useMaterial3: true,
      colorScheme: scheme,
      visualDensity: VisualDensity.standard,
      scaffoldBackgroundColor: scheme.surface,
      cardTheme: CardThemeData(
        elevation: 0,
        margin: EdgeInsets.zero,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(16),
          side: BorderSide(color: scheme.outlineVariant),
        ),
      ),
      inputDecorationTheme: const InputDecorationTheme(
        border: OutlineInputBorder(),
      ),
      filledButtonTheme: FilledButtonThemeData(
        style: FilledButton.styleFrom(
          padding: const EdgeInsets.symmetric(horizontal: 18, vertical: 14),
        ),
      ),
      outlinedButtonTheme: OutlinedButtonThemeData(
        style: OutlinedButton.styleFrom(
          padding: const EdgeInsets.symmetric(horizontal: 18, vertical: 14),
        ),
      ),
    );
  }
}
