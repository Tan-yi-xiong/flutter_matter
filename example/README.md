# flutter_matter API showcase

The example app exercises the public `flutter_matter` APIs through interactive
feature panels instead of mock data.

## Features

- QR and manual onboarding payload parsing with `OnboardingPayloadParser`.
- SDK-managed Wi-Fi commissioning through `ChipDeviceController.pairDevice`.
- Optional Android manual BLE/GATT transport through `BlePlatformDelegate`.
- CASE connection ownership through `connectedDevice` and
  `releaseConnectContext`.
- `BasicInformationCluster` and `DescriptorCluster` reads.
- On/Off `invoke`, attribute `subscribe`, and `unSubscription`.
- NodeLabel `read` and `write` with TLV input/output.
- Commissioning window creation with `openPairingWindowWithPIN`.
- Fabric Table inspection and current-fabric removal through
  OperationalCredentials `read` + `invoke`.
- A generic API console for `invoke`, `read`, `write`, and `subscribe`,
  including wildcard paths, event paths, data-version filters, and raw TLV.
- Android `pairDeviceWithAddress` and an NSD callback monitor in Advanced.

## Run

```sh
cd example
fvm flutter pub get
fvm flutter run
```

The app is mobile-only. Android uses the permissions declared in the example
manifest. iOS requires the Matter Extension, App Group, `AppGroupId`,
Info.plist entries, and signing setup documented in the repository README.
The vendored `ZGMatter.framework` does not support the iOS simulator.

## Storage and security

This example persists its demo fabric identity and device list in
`SharedPreferences` so the flow survives an app restart. That is intentionally
simple and is not production-safe. Real applications must protect controller
private keys, certificates, setup payloads, and Wi-Fi credentials with a
platform keystore and explicit user consent.

Setup codes, Wi-Fi passwords, pairing codes, certificates, private keys, and
raw native logs are not written to the operation log or example documentation.
