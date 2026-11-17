# flutter_matter API showcase

The example app exercises the public `flutter_matter` APIs through interactive
feature panels instead of mock data.

## Features

- QR or manual setup-code entry. Commissioning works straight from the raw
  onboarding code; `OnboardingPayloadParser` is optional and only surfaces
  payload details (VID / PID / discriminator / discovery capabilities).
- SDK-managed Wi-Fi commissioning through `ChipDeviceController.pairDevice`.
- Google Home dual-fabric commissioning on Android through the sibling
  `flutter_matter_google_home` plugin: GMS hosts the first fabric via
  `startHandoffSession`, the handoff endpoint feeds a local-stack
  `pairDeviceWithAddress` second fabric, and the session is completed with the
  truthful second-fabric result.
- Persisted Wi-Fi SSID / password auto-fill on the commissioning page.
- Commissioning window creation with `openPairingWindowWithPIN`; re-opening
  first clears any existing window state so the action can be repeated.
- Optional Android manual BLE/GATT transport through `BlePlatformDelegate`.
- CASE connection ownership through `connectedDevice` and
  `releaseConnectContext`.
- `BasicInformationCluster` and `DescriptorCluster` reads.
- On/Off `invoke`, attribute `subscribe`, and `unSubscription`.
- NodeLabel `read` and `write` with TLV input/output.
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
manifest, and Android builds require `GOOGLE_MATTER_SDK_REPO` pointing at the
unzipped Google Home Android SDK (Home APIs 1.11.1) Maven repository
(`home.android.sdk_1_11_1.zip`, SHA256
`9154ee88b3d93e7eafb85a1132043e281a14d1f60fc50913a4c230b34afafef4`); the Google
dual-fabric path additionally needs the sibling `flutter_matter_google_home`
checkout and a device with Google Play Services' Home module. iOS requires the
Matter Extension, App Group, `AppGroupId`, Info.plist entries, and signing
setup documented in the repository README. The vendored `ZGMatter.framework`
does not support the iOS simulator.

## Storage and security

This example persists its demo fabric identity and device list in
`SharedPreferences` so the flow survives an app restart. That is intentionally
simple and is not production-safe. Real applications must protect controller
private keys, certificates, setup payloads, and Wi-Fi credentials with a
platform keystore and explicit user consent.

Setup codes, Wi-Fi passwords, pairing codes, certificates, private keys, and
raw native logs are not written to the operation log or example documentation.
The example deliberately renders all user inputs (setup codes and Wi-Fi
passwords included) in plain text for debugging; real applications must not
follow this.
