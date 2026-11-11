# Architecture

`flutter_matter` is a low-level Flutter plugin that exposes Matter operations through Dart APIs backed by platform-native Matter SDKs. The plugin supports Android and physical iOS devices; it is not a pure-Dart Matter implementation.

## System layers

```text
Host Flutter application
        |
        v
Public Dart API and models
        |
        v
MethodChannel boundary: flutter_matter
        |
        +-------------------------------+
        |                               |
        v                               v
Android plugin and Matter SDK     iOS plugin and ZGMatter framework
```

The public Dart surface is exported from `package:flutter_matter/flutter_matter.dart`. It contains controller and commissioning APIs, onboarding helpers, BLE/GATT hooks, NSD helpers, Matter path/state models, TLV primitives, and two cluster helper classes.

## Dart to native transport

All plugin requests use the `flutter_matter` MethodChannel. A request method name is a custom URL in this form:

```text
zgmatter://<host>/<path>
```

`Uri` normalizes the scheme and host to lower case, while the path remains case-sensitive. The effective hosts are:

| Host | Purpose | Android | iOS |
| --- | --- | --- | --- |
| `devicecontroller` | Controller lifecycle, commissioning, read, write, invoke, and subscriptions | Yes | Yes |
| `ble` | BLE connection and GATT-related operations | Yes | Yes |
| `onboarding` | QR and manual setup-code parsing | Yes | Yes |
| `nsd` | DNS-SD resolution and publishing | Yes | No |

Request arguments are a JSON-encoded string. Successful request results and errors share this envelope:

```json
{
  "code": 0,
  "jsonData": {}
}
```

`code == 0` is success. Non-zero codes are handled by the Dart layer as plugin errors. The JSON field names and host/path routing are compatibility surfaces, not incidental implementation details.

## Controllers and native handles

`ChipDeviceController.newControllerIfNotExist` requests a native controller and receives an opaque `handle`. Native code stores controllers by that handle, and every subsequent request includes it in its JSON arguments.

The Dart controller registers a `MethodCallHandler` and routes callbacks only when both the native handle and the callback path match. `newControllerIfNotExist` reuses an existing controller when `fabricId` and `rootCertificate` match. `deleteDeviceController` destroys the native controller; `destroy()` removes Dart handlers and callback maps without making a native delete request.

Callback instances are also tracked by hash-based handles in the corresponding controller maps. Applications should retain callback objects for as long as the native operation may emit callbacks.

## Native to Dart callbacks

Native code sends callbacks through the same MethodChannel using paths such as:

```text
devicecontroller/CompletionListener/onCommissioningComplete
devicecontroller/SubscriptionCallback/onReport
devicecontroller/ReportCallback/onError
ble/BlePlatformDelegate/sendWriteRequest
```

Callback arguments are a JSON string containing a handle and callback-specific fields. Callback responses use:

```json
{
  "code": 0,
  "resultJson": "{}"
}
```

`resultJson` is a JSON string rather than a nested object. Callback families include `NOCChainIssuer`, `CompletionListener`, `DeviceAttestationDelegate`, `InvokeCallback`, `SubscriptionCallback`, `ReportCallback`, `WriteAttributesCallback`, `ConnectedDeviceCallback`, `OpenCommissioningCallback`, and BLE platform-delegate methods.

## Threading and lifecycle

Android dispatches plugin work through a shared single-thread executor. Matter callbacks that need a Dart response block on a non-main worker thread, schedule the MethodChannel call on the main Looper, and resume after the Dart response arrives. Native request results are also returned on the main Looper. Calls that require blocking native-to-Dart callbacks must not originate on the Android main thread.

iOS creates a serial queue named `Matter Thread queue`, stores it in `Global`, and runs device, BLE, and onboarding work on that queue. `InitializeZGMTR()` runs during plugin registration. Native request results are returned on the main queue, and blocking callback bridges also dispatch MethodChannel work to the main queue.

Because callback bridges wait for or synchronize with the main thread, callback implementations must not perform unbounded blocking work or wait on the same native queue. Keep callback handlers short and return quickly.

## Native implementation boundaries

### Android

`FlutterMatterPlugin` owns the channel and routes by URI host to the device-controller, BLE, onboarding, and NSD handlers. Controller state is stored in a native handle map. The Matter implementation comes from the prefixed Android artifact `com.github.Tan-yi-xiong:flutter_matter_android_prefixed:1.0.5`.

The plugin module declares `minSdkVersion 21` and `compileSdk 34`. The example Android build currently uses Gradle 8.7, Android Gradle Plugin 8.6.0, and Kotlin 1.7.10 on JDK 17. These are current repository facts, not evidence of an SDK upgrade.

### iOS

`FlutterMatterPlugin` routes device-controller, BLE, and onboarding hosts. It deliberately does not route `nsd`. The vendored `ZGMatter.framework` provides the Matter implementation and is linked through `ios/flutter_matter.podspec`.

The documented iOS support baseline is iOS 16.1 for both the plugin and the example. Xcode 16.4 or later and CocoaPods 1.17 are the documented toolchain baseline. The framework contains an iPhoneOS arm64 slice only, so simulator builds and Intel iOS devices are not supported.

The podspec, Podfile, app framework metadata, and Xcode target declarations are aligned to iOS 16.1. A Flutter 3.41 device build without code signing has been validated with Xcode 26.3 and CocoaPods 1.17.0.

## Platform differences

| Capability | Android | iOS |
| --- | --- | --- |
| Device control, commissioning, read, write, invoke | Yes | Yes |
| `pairDevice` onboarding payload | Optional when a setup pincode is supplied | Required |
| NSD helpers | Yes | Not implemented |
| `DataVersionFilter` in subscriptions | Yes | Not implemented |
| Custom GATT platform delegate | Yes | The callback surface exists, but Android is the documented custom-GATT path |
| iOS simulator | Not applicable | Not supported |

Additional constraints include:

- Open Wi-Fi is represented by an empty `WiFiCredentials.password`.
- Thread credentials use `NetworkCredentials.thread` with an Active Operational Dataset.
- ICD registration is exposed through `CompletionListener`.
- iOS device builds are required for validation because the vendored framework has no simulator slice.
- `ControllerParams` serializes `skipAttestationCertificateValidation` as `true`; this is a current native-selection constraint and should be treated as a security-sensitive known limit.

## Example application role

`example/` is a build and manual demonstration target. It is not part of the automated test contract. Use it to compile Android and iOS applications and to exercise commissioning, BLE, Wi-Fi, Thread, ICD, subscription, reconnect, and unpair scenarios on real devices.

Do not add `example/**` tests to required CI and do not describe a successful example test command as native or functional validation.

## Testing and CI boundaries

Automated tests cover the plugin root `test/` suite only:

- `test/public_api_test.dart` guards the export-path golden list and representative public symbols.
- `test/method_channel_contract_test.dart` guards URL construction and JSON envelopes.
- Model, TLV, onboarding, and callback-handler tests cover the Dart layer.

The required `Dart check and tests` workflow runs dependency resolution, non-fatal Dart analysis, and root plugin tests. It does not compile Android or iOS native code, run native or integration tests, validate packaging, or enforce formatting.

Android and iOS build/manual evidence belongs in the pull request template. A green Dart workflow never proves native compilation or device behavior.

## Known limits

- No iOS simulator support in the vendored Matter framework.
- No iOS NSD routing.
- `dataVersionFilters` is Android-only.
- MethodChannel wire compatibility is maintained manually; there is no external API-diff tool.
- Native Matter builds are validated through pull request evidence, not the required CI workflow.
- iOS builds are not part of required CI and depend on a macOS toolchain plus pull request evidence.
- Flutter 3.41 may auto-migrate the example's Android minSdk 21 declaration to the Flutter default of 24; this phase does not accept that Android compatibility change without a separate review.

## Related documents

- [Public API](doc/public-api.md)
- [Platform support](doc/platform-support.md)
- [ADR 0001: MethodChannel URL and JSON contract](doc/adr/0001-method-channel-url-and-json-contract.md)
- [ADR 0002: Public API boundary](doc/adr/0002-public-api-boundary-and-semver.md)
- [ADR 0003: Platform and toolchain baseline](doc/adr/0003-platform-and-toolchain-baseline.md)
- [ADR 0004: Lightweight API governance](doc/adr/0004-lightweight-api-governance.md)
- [ADR 0005: Dart-only CI and pull request evidence](doc/adr/0005-dart-only-ci-and-pr-evidence.md)
