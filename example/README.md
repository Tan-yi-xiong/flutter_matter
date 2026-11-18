# flutter_matter API showcase

This app exercises the public `flutter_matter` APIs through interactive feature panels. It is a manual build and demonstration target, not an automated test suite.

## Code map

| Feature | Source location |
| --- | --- |
| Persistent fabric identity and controller parameters | [`MatterIdentity`](lib/src/identity.dart#L13-L41), [`MatterIdentityRepository.loadOrCreate`](lib/src/identity.dart#L48-L67) |
| SDK-managed Wi-Fi commissioning | [`MatterCommissioningService.commission`](lib/src/commissioning_service.dart#L26-L93) |
| Cancel an in-progress commissioning attempt | [`cancelCommissioning`](lib/src/commissioning_service.dart#L16-L24) |
| Direct-address commissioning | [`commissionWithAddress`](lib/src/commissioning_service.dart#L95-L143) |
| Google Home dual-fabric commissioning | [`commissionGoogleDualFabric`](lib/src/commissioning_service.dart#L145-L197) |
| Commissioning callbacks, NOC issuance, and attestation | [`_CommissioningDelegate`](lib/src/commissioning_service.dart#L208-L341) |
| Android custom BLE/GATT transport | [`AndroidBleTransport`](lib/src/android_ble_transport.dart#L8-L225) |
| Connection, read, write, invoke, and subscribe | [`MatterApiService`](lib/src/matter_api_service.dart#L8-L220) |
| Fabric Table read and removal | [`readFabrics` / `removeFabric`](lib/src/matter_api_service.dart#L286-L335) |
| Commissioning UI flow | [`CommissioningPage._startCommissioning`](lib/src/pages/commissioning_page.dart#L130-L169) |
| Device control UI flow | [`DevicePage`](lib/src/pages/device_page.dart#L19-L418) |
| Generic Interaction Model console | [`ApiConsolePage`](lib/src/pages/api_console_page.dart#L22-L286) |
| Android direct-address and NSD tools | [`AdvancedPage`](lib/src/pages/advanced_page.dart#L10-L262) |

These links identify the complete implementation. The user guide pages keep only minimal snippets and link back here instead of duplicating the code.

## Run

```sh
cd example
fvm flutter pub get

# Android builds only.
export GOOGLE_MATTER_SDK_REPO=/absolute/path/to/home.android.sdk_1_11_1/repo
fvm flutter run
```

The app is mobile-only. Android uses the permissions declared in the example manifest. The `GOOGLE_MATTER_SDK_REPO` variable must point at the extracted Google Home Android SDK.

Download the SDK from the [Google Home Android release notes](https://developers.home.google.com/apis/android/release-notes). Do not commit SDK artifacts. Google dual-fabric commissioning also requires a device with the Play Services Home module.

For iOS, complete the Matter Extension, App Group, `AppGroupId`, Info.plist, and signing steps in [Getting started](../doc/getting-started.md), then run on a physical iPhone. The vendored `ZGMatter.framework` does not support the simulator.

## Related guides

- [Getting started](../doc/getting-started.md)
- [Commissioning](../doc/commissioning.md)
- [Device operations](../doc/device-operations.md)
- [Platform support](../doc/platform-support.md)

## Storage and security

The example persists its demo fabric identity and device list in `SharedPreferences`. That is intentionally simple and not production-safe. Real applications must protect controller private keys, certificates, setup payloads, and Wi-Fi credentials with platform secure storage and explicit user consent.

The example renders setup codes and Wi-Fi passwords as plain text for debugging. Do not copy that behavior into a production app. The operation log excludes setup codes, passwords, pairing codes, certificates, private keys, and raw native logs.
