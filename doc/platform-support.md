# Platform Support

This page defines the supported platform and toolchain baseline for `flutter_matter`.

## Support matrix

| Area | Supported baseline |
| --- | --- |
| Plugin platforms | Android and physical iOS devices |
| Flutter | Flutter `3.41.0`, pinned in `.fvmrc` |
| Dart SDK | `>=3.3.3 <4.0.0` in `pubspec.yaml`, unchanged |
| Flutter SDK constraint | `>=3.3.0` in `pubspec.yaml`, unchanged |
| Validated Flutter version | `3.41.0` only |
| Android minimum SDK | 21 |
| Android compile SDK | 34 |
| Android build JDK | 17 |
| Example Android Gradle | 8.7 |
| Example Android Gradle Plugin | 8.6.0 |
| Kotlin | 1.7.10 |
| iOS minimum support | 16.1 for both plugin and example |
| iOS build host | macOS with Xcode 16.4 or later |
| CocoaPods | 1.17 |
| iOS architecture | iPhoneOS arm64 only |
| iOS simulator | Not supported |

The Flutter and Dart lower bounds in `pubspec.yaml` remain unchanged. Compatibility is currently validated with Flutter 3.41.0; older versions satisfy the declared constraints but are not part of the validated baseline.

The Android baseline reflects the current example build files and plugin declarations. It does not record or imply a recent SDK upgrade. The wrapper properties target Gradle 8.7. The example `gradlew` and wrapper JAR are generated local files and are intentionally ignored by the example project, so documentation and CI must not depend on them being present in a clean checkout. Flutter 3.41 defaults new app projects to minSdk 24 and may attempt to migrate the example's current minSdk 21 declaration during an Android build; that migration is intentionally outside this phase and must be reviewed before it is committed.

The iOS support floor is 16.1 across the podspec, Podfile, app framework metadata, and Xcode targets. A Flutter 3.41 device build without code signing completed on 2026-11-11 with Xcode 26.3 and CocoaPods 1.17.0. Xcode 16.4 remains the documented `macos-15` baseline unless a future validation records a different supported host.

## Device and simulator policy

The vendored `ios/frameworks/ZGMatter.framework` contains only an iPhoneOS arm64 binary. It has no simulator slice and is not a universal framework for Intel iOS devices.

Consequences:

- Validate iOS changes with a physical arm64 device build or an explicit no-codesign device build.
- Do not use an iOS simulator as evidence for plugin behavior.
- Do not claim simulator support based on a successful Dart test or analyze run.
- Any future simulator support requires a compatible framework and an explicit platform-support change.

## Feature availability

| Feature | Android | iOS |
| --- | --- | --- |
| Device controller lifecycle | Yes | Yes |
| BLE and commissioning | Yes | Yes |
| On-network commissioning | Yes | Yes |
| Wi-Fi credentials, including open Wi-Fi | Yes | Yes |
| Thread operational dataset | Yes | Yes |
| ICD registration callbacks | Yes | Yes |
| Attribute read, write, invoke, and subscriptions | Yes | Yes |
| `DataVersionFilter` subscriptions | Yes | No |
| DNS-SD helpers | Yes | No |
| Custom GATT platform delegate | Yes | Callback surface exists; Android is the documented custom-GATT path |

The `iOS pairDevice` API requires `onboardingPayload`. The Dart layer throws before making the native call when the payload is missing on iOS.

## Verification boundary

The required `Dart check and tests` workflow runs on Ubuntu and covers only the Dart layer. It does not build Android or iOS native code and cannot validate Matter behavior.

Required pull request evidence separately covers the relevant path:

- Android debug build on a JDK 17 build host.
- iOS no-codesign device build on macOS with the documented Xcode and CocoaPods baseline.
- A schema-based Android and/or iOS device-validation report on the affected controller platform when device behavior changes.
- An explicit `Not run` reason and residual-risk statement when the required hardware or toolchain is unavailable.

Formal device validation requires a Matter commissionee. The app passes the raw onboarding payload directly to the Matter SDK, which performs commissionee discovery and commissioning, and uses Wi-Fi network credentials for the active validation flow. A commissioning failure is preserved without retrying commissioning. Device provenance is not part of the report contract. Shared behavior requires Android and physical iOS reports; stable releases require one clean P0 cycle on both platforms. The repository does not run device tests in hosted CI and does not currently define a self-hosted device runner.

See [CONTRIBUTING.md](../CONTRIBUTING.md), [the device validation process](device-validation.md), [the device test report contract](device-test-report.md), [the PR review checklist](pr-review-checklist.md), [ADR 0005](adr/0005-dart-only-ci-and-pr-evidence.md), and [ADR 0006](adr/0006-device-validation-report-contract.md).

## Toolchain update policy

When the Flutter, Dart, JDK, Gradle, Android Gradle Plugin, Kotlin, Xcode, CocoaPods, or iOS deployment target changes:

1. Update the repository configuration and documentation together.
2. Record whether the change is a supported baseline, a validated version, or only a local toolchain.
3. Run the applicable Dart, Android, and iOS verification.
4. Add compatibility notes for consumers when the minimum supported version changes.
5. Do not describe an upgrade as complete until both configuration and validation evidence exist.
