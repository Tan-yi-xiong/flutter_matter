# Platform support

`flutter_matter` supports Android and physical iOS controllers. This page is the source of truth for the current toolchain and feature baseline.

Use [Getting started](getting-started.md) for host-app setup, [Commissioning](commissioning.md) for pairing flows, and [Device operations](device-operations.md) for post-commissioning control.

## Support matrix

| Area | Supported baseline |
| --- | --- |
| Flutter | 3.41.0, pinned in `.fvmrc` |
| Dart SDK | `>=3.3.3 <4.0.0` in `pubspec.yaml` |
| Flutter SDK constraint | `>=3.3.0` in `pubspec.yaml` |
| Validated Flutter version | 3.41.0 |
| Android plugin | `minSdk 21`, `compileSdk 34`, JDK 17, Kotlin 1.7.10, Matter 1.6.1 artifact `1.0.6` |
| Example Android build | `minSdk 29`, `compileSdk 36`, Kotlin 2.4.0, Gradle 8.7, AGP 8.6.0 |
| Device-test app Android | `minSdk 24`, `compileSdk 36`, arm64 |
| iOS | 16.1 or later for the plugin and example |
| iOS build host | macOS with Xcode 16.4 or later and CocoaPods 1.17 |
| iOS architecture | Physical iPhoneOS arm64 only |
| iOS simulator | Not supported |

The Dart and Flutter lower bounds remain unchanged in `pubspec.yaml`; only Flutter 3.41.0 is part of the validated baseline.

The plugin and example have separate Android baselines. The example moved to `minSdk 29`, `compileSdk 36`, and Kotlin 2.4.0 for the Google Play Services Home APIs artifact used by dual-fabric commissioning. Its Android build requires:

```sh
export GOOGLE_MATTER_SDK_REPO=/absolute/path/to/home.android.sdk_1_11_1/repo
```

Download `home.android.sdk_1_11_1.zip` from the [Google Home Android release notes](https://developers.home.google.com/apis/android/release-notes) and verify SHA-256 `9154ee88b3d93e7eafb85a1132043e281a14d1f60fc50913a4c230b34afafef4`. Do not commit the extracted SDK.

The iOS minimum is 16.1 across the podspec, Podfile, framework metadata, and Xcode targets. A Flutter 3.41 device build without code signing has been validated with Xcode 26.3 and CocoaPods 1.17.0; Xcode 16.4 remains the documented minimum.

The vendored framework is generated from a pinned official `connectedhomeip` commit by the reproducible pipeline in `ios/zgmatter/`. See [ZGMatter framework build](zgmatter-build.md) for the explicit source-path contract, patch workflow, and validation steps.

## Device and simulator policy

`ios/frameworks/ZGMatter.framework` contains an iPhoneOS arm64 binary and no simulator slice.

- Use a physical arm64 device or a no-codesign device build for iOS verification.
- Do not use simulator results as plugin evidence.
- Any simulator support requires a compatible framework and an explicit platform-support change.

## Feature availability

| Feature | Android | iOS |
| --- | --- | --- |
| Controller lifecycle and CASE connections | Yes | Yes |
| BLE and on-network commissioning | Yes | Yes |
| Wi-Fi credentials, including open Wi-Fi | Yes | Yes |
| Thread operational dataset | Yes | Yes |
| ICD registration callbacks | Yes | Yes |
| Attribute/event read, write, invoke, and subscribe | Yes | Yes |
| `DataVersionFilter` subscriptions | Yes | No |
| DNS-SD helpers | Yes | No |
| `pairDeviceWithAddress` | Yes | No |
| Custom GATT platform delegate | Yes | Callback surface only |

`pairDevice` requires an onboarding payload on iOS. The Dart layer rejects an iOS call that supplies only a setup PIN.

## Verification boundary

The required Dart workflow covers only the Dart layer. Native builds and Matter behavior are pull-request evidence, not CI results. Device-behavior changes require a `full` Run with a schema v4 report on every affected controller platform.

See [Contributing](../CONTRIBUTING.md), [Device validation](device-validation.md), and [Device test report contract](device-test-report.md).

## Toolchain changes

When changing Flutter, Dart, JDK, Gradle, AGP, Kotlin, Xcode, CocoaPods, or an iOS deployment target:

1. Update configuration and this page together.
2. State whether the version is validated, a minimum baseline, or a local-only toolchain.
3. Run the applicable Dart, Android, and iOS checks.
4. Add consumer migration notes when a minimum supported version changes.
5. Do not call an upgrade complete without configuration and validation evidence.
