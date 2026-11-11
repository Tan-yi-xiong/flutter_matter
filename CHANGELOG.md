## Unreleased

### Packaging and Licensing
- Relicensed original `flutter_matter` code under the MIT License while preserving Apache-2.0 notices for Project CHIP/Matter SDK-derived source and bundled binaries.
- Added package repository, issue tracker, topics, and a release-ready description in `pubspec.yaml`.
- Renamed the top-level documentation directory from `docs/` to `doc/` and added `.pubignore` rules for repository-only files.
- Removed unused `built_value`, `built_value_generator`, and `build_runner` development dependencies.

### Release and Security
- Added a tag-driven source release workflow that validates package metadata, creates a deterministic source archive with SHA256, and publishes a GitHub Release.
- Added an internal release metadata CLI and release runbook. pub.dev publication remains a manual maintainer step.
- Added `SECURITY.md`, third-party license notices, and GitHub Private Vulnerability Reporting.

### Compatibility
- **iOS 16.1 minimum support** — The podspec, Podfile, app framework metadata, and Xcode targets now use iOS 16.1 for both the plugin and the example. A Flutter 3.41 device build without code signing completed with Xcode 26.3 and CocoaPods 1.17.0.

### Tooling and tests
- Added a root plugin Dart test suite covering public exports, MethodChannel contracts, models, TLV parsing, onboarding parsing, and callback routing.
- Pinned Flutter `3.41.0` through `.fvmrc`; the Dart and Flutter pubspec lower bounds remain unchanged, while only Flutter `3.41.0` is currently validated.
- Documented the Android build baseline as `minSdk 21`, `compileSdk 34`, JDK 17, Gradle 8.7, Android Gradle Plugin 8.6.0, and Kotlin 1.7.10 without claiming an upgrade.
- Documented that Flutter 3.41 may auto-migrate the example Android minSdk from 21 to 24 and that this migration is outside the current compatibility decision.
- Updated the example's `win32` override so dependency resolution remains compatible with Dart 3.11.
- Kept the required CI gate Dart-only and limited automated tests to the plugin root `test/` suite. The example remains a build and manual demonstration target.

### Bug Fixes
- Fixed signed little-endian TLV decoding for negative integer widths.
- Fixed context-tagged TLV boolean and non-integer type parsing.
- Fixed nested event and event-status decoding in `ClusterState`.

### Documentation
- Added architecture, public API, platform support, and architecture decision records.
- Added contribution and review guidance for public API, MethodChannel, JSON, platform, and testing compatibility.
- Added a device-validation process and schema-versioned JSON/Markdown report contract for Android and physical iOS controllers, preferring qualified real Matter devices with the Android Virtual Device App as fallback.
- Added the Flutter 3.41 UIScene migration for the iOS example and aligned its deployment targets to iOS 16.1.
- Clarified that `example/**` is never an automated test target and that iOS simulator builds are unsupported by the current vendored Matter framework.

## 0.0.11

### Bug Fixes
- Fixed iOS attribute path parsing for read and subscribe operations.
- Added support for converting Flutter wildcard path IDs to Matter SDK wildcard values.
- Added validation for malformed iOS attribute path input.

## 0.0.10

### Improvements
- **Open Wi-Fi commissioning support** — `WiFiCredentials.password` now supports empty-string values for open networks. The Dart API keeps serializing the password field, and both Android and iOS native commissioning paths now accept an empty password when an SSID is provided.
- **iOS example SSID autofill** — The example app now attempts to read the currently connected iPhone Wi-Fi SSID during onboarding and, when available, skips the manual `WifiInputPage` and starts provisioning with that SSID and an empty password. If the SSID cannot be read, the example falls back to the manual Wi-Fi input flow.

## 0.0.9

### Changes
- Simplified the example app by removing the Linux, macOS, Windows, and Web targets, keeping the maintained mobile example flow focused.
- Renamed the example Android application package from `com.zengge.example` to `com.fluttermatter.example`.

## 0.0.8

### New Features
- **ICD (Intermittently Connected Device) support** — Matter 1.2+
  - Added `ICDDeviceInfo` model class with all fields: `symmetricKey`, `userActiveModeTriggerHint`, `userActiveModeTriggerInstruction`, `icdNodeId`, `icdCounter`, `monitoredSubject`, `fabricId`, `fabricIndex`.
  - Added `onICDRegistrationComplete(int errorCode, ICDDeviceInfo? icdDeviceInfo)` to the `CompletionListener` interface — previously a TODO comment.
  - `ChipDeviceController.call()` now dispatches this callback with proper JSON decoding from the native side.
- **Thread network commissioning** — `NetworkCredentials` now supports Thread in addition to Wi-Fi:
  - New `ThreadCredentials` class wrapping a Thread Active Operational Dataset (`Uint8List operationalDataset`).
  - New named constructors `NetworkCredentials.wifi(WiFiCredentials)` and `NetworkCredentials.thread(ThreadCredentials)`.
  - Legacy `NetworkCredentials({required WiFiCredentials wifiCredentials})` constructor kept for backward compatibility.
  - `toJson()` correctly serialises whichever credential type is set. The Android native layer already parsed Thread credentials.
- **`setCompletionListener` is now public** — `Future<void> setCompletionListener(CompletionListener listener)` can now be called independently from `pairDevice`, allowing the listener to be assigned or swapped at any time.
- **`unPairDevice` is now fully active** — `Future<bool> unPairDevice(int nodeId)` removes a device from the fabric and was previously commented out. The Android native `/unPairDevice` route was already wired.

### Improvements
- **`DataVersionFilter` support in `subscribe()`** — The `dataVersionFilters` parameter is no longer ignored. Both the Dart method signature and the Android native layer now parse, pass, and forward the filter list to `subscribeToPath`, enabling efficient change-only subscriptions.
- **Additional public exports** — `ChipEventPath`, `DataVersionFilter`, and `ICDDeviceInfo` are now exported from `package:flutter_matter/flutter_matter.dart` so consumers can construct them directly without importing internal paths.
- **Android package rename** — Updated the Android plugin package/group/namespace from `com.zengge.flutter_matter` to `com.tyx.flutter_matter`.
- **Example lockfile handling** — Stopped tracking `example/pubspec.lock` and added it to `.gitignore` to avoid noisy example dependency lockfile diffs in plugin commits.

### Bug Fixes & Analysis Cleanup
- Fixed `eventPaths` parsing in iOS `subscribe()` and `readRequest()` so event path payloads are read from the correct request field.
- Expanded the Dart `subscribe()` / `read()` API docs and clarified that `dataVersionFilters` is currently supported on Android only.
- Removed unused imports: `dart:ffi` (controller.dart), `dart:collection` (node_state.dart), `dart:typed_data` (tlv_types.dart), `flutter/widgets.dart` (ble.dart), and several unused imports across the example app.
- Removed 7 unused `result` local variable assignments in `ble.dart` GATT handler methods.
- Fixed stale `@override` annotation on `onCloseBleComplete()` in the example app (method was removed from the `CompletionListener` interface).
- Fixed unnecessary non-null assertion (`!`) on `chipDeviceController` in `control_page.dart`.
- Replaced auto-generated stub test files (`plugin_integration_test.dart`, `widget_test.dart`) that referenced non-existent classes with minimal passing placeholder tests.
- Added `flutter_lints` as a dev dependency to the example app.
- Suppressed `unused_element` lint on the intentionally private `ChipPathId._` constructor.

## 0.0.6

* version 0.0.6

## 0.0.1

* Initial release.
