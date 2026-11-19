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

### Device Test App and Agent Automation
- Added a dedicated Android/iOS device-test app with quick and full validation profiles, one-shot Run lifecycle with stale-state cleanup, secure credential storage, and schema-validated JSON/Markdown reports.
- Added a Mac-hosted WebSocket Agent bridge, JSON CLI, and repository Skill for guided device validation. Multiple connected phones require an explicit user choice.
- The device-test app remains outside the required CI workflow; its local checks and Agent workflows are documented for contributors.

### Compatibility
- **iOS 16.1 minimum support** — The podspec, Podfile, app framework metadata, and Xcode targets now use iOS 16.1 for both the plugin and the example. A Flutter 3.41 device build without code signing completed with Xcode 26.3 and CocoaPods 1.17.0.
- **iOS Matter SDK 1.6.1** — Rebuilt `ZGMatter.framework` from official connectedhomeip `v1.6.1-branch` (`da8f6a0bff`) with a reproducible rename + feature-patch pipeline. The framework keeps the ZGMTR-prefixed public APIs and no longer carries the legacy iOS BLE proxy overrides.
- **Android Matter SDK 1.6.1** — Rebuilt the prefixed Android artifact from the same official connectedhomeip commit (`da8f6a0bff`) for `arm64-v8a` and `armeabi-v7a`. The dependency is now `com.github.Tan-yi-xiong:flutter_matter_android_prefixed:1.0.6`.
- **Breaking: `ControllerParams.setupURL` removed** — Matter 1.6.1 removed `ControllerParams.Builder.setSetupURL`; the field and its JSON wire key were removed. Migrate by omitting `setupURL`; there is no upstream replacement.

### Tooling and tests
- Moved the reproducible ZGMatter framework build pipeline into `ios/zgmatter/`, with explicit `ZGMATTER_CONNECTEDHOMEIP_DIR` or `--connectedhomeip-dir` source configuration and English maintainer documentation.
- Added a root plugin Dart test suite covering public exports, MethodChannel contracts, models, TLV parsing, onboarding parsing, and callback routing.
- Pinned Flutter `3.41.0` through `.fvmrc`; the Dart and Flutter pubspec lower bounds remain unchanged, while only Flutter `3.41.0` is currently validated.
- Documented the plugin Android baseline as `minSdk 21`, `compileSdk 34`, JDK 17, and Kotlin 1.7.10, with the example Gradle/AGP/Kotlin baseline tracked separately.
- Removed the example's obsolete `win32` override after refreshing its mobile plugin dependencies.
- Kept the required CI gate Dart-only and limited automated tests to the plugin root `test/` suite. The example remains a build and manual demonstration target.
- Reworked the example into an English API and feature showcase with a generic Interaction Model console, direct-address and NSD advanced tools, explicit operation results, and demo-only restart persistence.
- Integrated Google Home dual-fabric commissioning into the example through the pinned `flutter_matter_google_home` git dependency: GMS hosts the first fabric (`startHandoffSession`), the handoff endpoint drives a local-stack `pairDeviceWithAddress` second fabric, and the session reports the truthful second-fabric outcome.
- Commissioning now works straight from the raw onboarding code; payload parsing is optional and only displays payload details.
- Commissioning-window re-open clears the previous window state first so the action can be repeated.
- Back-press during commissioning cancels the active pairing and resets stale state; Wi-Fi SSID / password persist and auto-fill.
- Updated the example Android baseline to Kotlin 2.4.0, minSdk 29, and compileSdk 36 for the Google Home SDK, and documented the `GOOGLE_MATTER_SDK_REPO` build prerequisite. The plugin's own Android baseline is unchanged.

### Bug Fixes
- Fixed Android Matter 1.6.1 commissioning failing at `GenerateNOCChain` with `CHIP_ERROR_BAD_REQUEST` (`0x92`, callback code `146`). The Android bridge now supplies an empty ICAC instead of `null`.
- Fixed signed little-endian TLV decoding for negative integer widths.
- Fixed context-tagged TLV boolean and non-integer type parsing.
- Fixed nested event and event-status decoding in `ClusterState`.

### Documentation
- Reorganized consumer documentation into a Getting started tutorial, commissioning and device-operation guides, and a compact public API boundary, with symbol-level links to the runnable `example/` implementation.
- Added core dartdoc comments for controller, commissioning, onboarding, connection, and Interaction Model operations.
- Added architecture, public API, platform support, and architecture decision records.
- Added contribution and review guidance for public API, MethodChannel, JSON, platform, and testing compatibility.
- Added a device-validation process and schema-versioned JSON/Markdown report contract for Android and physical iOS controllers using Matter commissionees with SDK-managed discovery and commissioning.
- Added the Flutter 3.41 UIScene migration for the iOS example and aligned its deployment targets to iOS 16.1.
- Clarified that `example/**` is never an automated test target and that iOS simulator builds are unsupported by the current vendored Matter framework.
- Corrected the public documentation to describe fabric removal through OperationalCredentials `read` + `invoke`; `unPairDevice` is not part of the current exported controller API.
- Refreshed the README and core project documentation around plugin-user onboarding, platform baselines, device-test lifecycle, and the 8-test schema v4 matrix; consolidated the device-test app guide into its README; reduced duplication across the PR template, review checklist, and contributor guide.

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
