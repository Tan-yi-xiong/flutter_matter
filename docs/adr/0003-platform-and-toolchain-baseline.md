# ADR 0003: Platform and Toolchain Baseline

- Status: Accepted
- Date: 2026-11-11

## Context

The repository has several independent build surfaces: the plugin Dart package, the Android plugin module, the Android example, the iOS plugin podspec, the iOS example project, and the vendored Matter frameworks. Version declarations are not currently uniform, and the iOS framework has a different binary capability from the Dart package constraints.

The project needs one documented baseline that reviewers and contributors can use when deciding whether a build or device result is relevant.

## Decision

Document and use this baseline:

- Flutter `3.41.0`, pinned in `.fvmrc`.
- Dart SDK constraint `>=3.3.3 <4.0.0`, unchanged.
- Flutter SDK constraint `>=3.3.0`, unchanged.
- Flutter `3.41.0` is the only currently validated Flutter version.
- Android `minSdkVersion 21`, `compileSdk 34`, JDK 17.
- Example Android build: Gradle 8.7, Android Gradle Plugin 8.6.0, Kotlin 1.7.10.
- iOS minimum support: 16.1 for both the plugin and example.
- iOS toolchain baseline: Xcode 16.4 or later and CocoaPods 1.17.
- iOS binary support: physical iPhoneOS arm64 devices only; no simulator.

`pubspec.yaml` lower bounds remain unchanged. The Android entries describe the current build files and do not claim that an SDK or Gradle upgrade has already been completed.

The iOS 16.1 minimum is aligned across the podspec, Podfile, app framework metadata, and Xcode targets. A Flutter 3.41 device build without code signing completed with Xcode 26.3 and CocoaPods 1.17.0. Xcode 16.4 remains the documented baseline for the hosted macOS runner family.

## Consequences

- Contributors must not use a simulator run as iOS plugin evidence.
- Toolchain upgrades require configuration, documentation, validation, and compatibility review together.
- The Dart workflow remains host-only and does not verify any entry in this baseline beyond the Dart layer.
- Platform build checks are declared in pull requests with the actual device, OS, JDK, Xcode, and CocoaPods versions used.
- Future changes to Flutter, Dart, Android, iOS, or Matter binary support must update `docs/platform-support.md` and the relevant ADR or add a replacement ADR.
