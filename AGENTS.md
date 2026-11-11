# AGENTS.md — flutter_matter

Guidelines for coding agents working in **this repository only**.

This is a Flutter plugin (`flutter_matter` 0.0.11) that exposes a low-level [Matter](https://csa-iot.org/) API on **Android and iOS**. Do not apply the parent workspace Python/Django `AGENTS.md` here.

## Overview

- Public Dart API: `package:flutter_matter/flutter_matter.dart`
- Dart SDK `>=3.3.3 <4.0.0`, Flutter `>=3.3.0`; validated with Flutter `3.41.0`
- MethodChannel name: `flutter_matter`
- Dart → native calls use `zgMatter://<host>/<path>` URLs from `createRequestPlatformUrl` in `lib/flutter_matter_method_channel.dart`. Native plugins parse host + path.
- Hosts:
  - `devicecontroller` → `ChipDeviceController`
  - `BLE` → BLE / GATT
  - onboarding host → QR / manual setup-code parsing
  - `nsd` on Android (the iOS plugin currently does not route NSD)
- Android plugin: `com.tyx.flutter_matter.FlutterMatterPlugin`
- iOS plugin: `FlutterMatterPlugin` (Objective-C), vendored `ios/frameworks/ZGMatter.framework`
- Android Matter stack: `com.github.Tan-yi-xiong:flutter_matter_android_prefixed:1.0.5`
- FVM Flutter **3.41.0** (`.fvmrc`). Prefer `fvm flutter` / `fvm dart` when FVM is available; otherwise use Flutter `3.41.0` and `flutter` / `dart` on PATH.

## Commands

From the plugin root:

```bash
# Prefer FVM when present
fvm flutter pub get
fvm flutter analyze
fvm dart format .
fvm flutter test

# Example app
cd example
fvm flutter pub get
fvm flutter build apk --debug
fvm flutter build ios --debug --no-codesign
fvm flutter run
```

Android plugin unit test sources exist, but `example/android/gradlew` and its wrapper JAR are generated local files and are not tracked. The current Android test is not part of required CI.

iOS example workspace:

```bash
open example/ios/Runner.xcworkspace
```

Do not invent pytest, ruff, mypy, or Docker workflows. Automated tests cover the root plugin `test/` suite only. The example is a build and manual demo target and has no automated test role.

## Project structure

```
flutter_matter/
├── lib/
│   ├── flutter_matter.dart                    # public exports
│   ├── flutter_matter_platform_interface.dart
│   ├── flutter_matter_method_channel.dart     # channel + URL helpers
│   └── src/
│       ├── controller.dart                    # ChipDeviceController + callbacks
│       ├── ble.dart
│       ├── onboarding.dart
│       ├── nsd.dart
│       ├── tlv/                               # TLV reader/writer
│       ├── clusters/                          # Descriptor, BasicInformation
│       └── model/
├── android/src/main/kotlin/com/tyx/flutter_matter/
├── ios/Classes/                               # ObjC + some Swift
├── ios/frameworks/ZGMatter.framework
├── doc/                                       # architecture, API, release, and ADR docs
├── tool/release.dart                          # release metadata and notes CLI
├── SECURITY.md                                # security policy
├── example/                                   # Android + iOS demo only
│   └── ios/MatterExt/RequestHandler.swift
└── test/                                      # root plugin Dart test suite
```

New public types and functions must be exported from `lib/flutter_matter.dart`, documented in `doc/public-api.md`, and reflected in the export golden test when the public export list changes. Consumers should not import `src/` paths; tests may do so.

## Dart / Flutter conventions

- Follow `package:flutter_lints/flutter.yaml` (`analysis_options.yaml`).
- Format with `dart format` (2-space indent). Match existing style; do not reformat unrelated files.
- Preserve the MethodChannel URL scheme and JSON result shapes (`{code, jsonData}` / `{code, resultJson}`).
- Native → Dart callbacks use path prefixes such as `NOCChainIssuer`, `CompletionListener`, `InvokeCallback`, `SubscriptionCallback`, `ReportCallback`, `WriteAttributesCallback`, `ConnectedDeviceCallback`, `OpenCommissioningCallback`.
- Prefer existing wrappers: `ReportCallbackWarp`, `SubscriptionCallbackWarp`, `WriteAttributesCallbackWarp`.
- `ChipDeviceController.newControllerIfNotExist` reuses a controller with the same `fabricId` + `rootCertificate`.
- iOS `pairDevice` requires `onboardingPayload`.
- Open Wi-Fi: empty `WiFiCredentials.password` is valid.
- Thread: `NetworkCredentials.thread(ThreadCredentials(operationalDataset: ...))`.
- ICD: implement `CompletionListener.onICDRegistrationComplete`.
- `subscribe()` `dataVersionFilters` is currently Android-only.
- Keep legacy constructors (`NetworkCredentials({required WiFiCredentials ...})`) unless a breaking change is explicitly requested.
- Known typo in code: `_findSameFarbicControl`. Do not rename it unless that is the task.
- Generated cluster code is not currently present, and code-generation dependencies are intentionally omitted. Add `built_value` / `build_runner` only when introducing generated code.

## Native conventions

When adding a Dart platform call, implement **both** Android and iOS unless the change is documented as one-platform (NSD / `dataVersionFilters`).

### Android (Kotlin, `com.tyx.flutter_matter`)

- Entry: `FlutterMatterPlugin.kt` dispatches by URI host to `onDeviceControlCall`, `onBLECall`, `onOnboardingCall`, `onNsdCall`.
- minSdk 21, compileSdk 34, Java/Kotlin 1.8.
- Do not revive `com.zengge.flutter_matter`.
- Example applicationId / namespace: `com.fluttermatter.example`.
- BLE / Wi-Fi permissions belong in the **host app** `AndroidManifest.xml` (see README), not necessarily the plugin manifest.

### iOS (ObjC plugin + Swift Matter Extension)

- Entry: `ios/Classes/FlutterMatterPlugin.m` — hosts for device controller, BLE, and onboarding only.
- Matter work runs on the `Global` serial queue; `InitializeZGMTR()` runs on plugin register.
- Vendored framework: `ZGMatter.framework` via `ios/flutter_matter.podspec`.
- Deployment targets are iOS 16.1. Documented toolchain baseline is Xcode 16.4 or later with CocoaPods 1.17; the migration build evidence used Xcode 26.3 and CocoaPods 1.17.0.
- The vendored `ZGMatter.framework` is iPhoneOS arm64 only; simulator builds are not supported.
- Host apps need a Matter Extension, App Groups, `AppGroupId`, and Matter Allow Setup Payload (README). Copy `example/ios/MatterExt/RequestHandler.swift`.
- Info.plist: Bluetooth, Bonjour (`_matter._tcp`, `_matterc._udp`, `_matterd._udp`, `_meshcop._udp`), local network, and camera if scanning QR codes.

## Example app

- Mobile-only. Linux / macOS / Windows / Web targets were removed.
- BLE demo uses `flutter_blue_plus` / `flutter_reactive_ble`; NSD uses `bonsoir`.
- On iOS the example can autofill the current Wi-Fi SSID and commission with an empty password; otherwise it falls back to `WifiInputPage`.
- The example is for builds and manual functional testing. It has no automated test role.

## Agent working rules

- Prefer `fvm flutter` / `fvm dart` in this repo.
- Do not add `example/**` tests to required CI or report them as automated evidence.
- Do not commit Flutter's Android minSdk 21 -> 24 migration unless it is part of an explicit compatibility task.
- Do not commit `.history/`, `build/`, `.dart_tool/`, or `pubspec.lock` / `example/pubspec.lock` (gitignored for this plugin).
- Do not rewrite `ZGMatter.framework` or the prefixed Android Matter AAR unless that is the task.
- Recent behavior to preserve (see `CHANGELOG.md`): open Wi-Fi commissioning, ICD, Thread credentials, `unPairDevice`, iOS wildcard attribute paths.

## Quick reference

| Action | Command |
|--------|---------|
| Analyze plugin (errors only) | `fvm flutter analyze --no-fatal-infos --no-fatal-warnings` |
| Format Dart | `fvm dart format .` |
| Plugin tests | `fvm flutter test` |
| Example Android build | `cd example && fvm flutter build apk --debug` |
| Example iOS build | `cd example && fvm flutter build ios --debug --no-codesign` |
| Run example | `cd example && fvm flutter run` |
| iOS workspace | `open example/ios/Runner.xcworkspace` |
