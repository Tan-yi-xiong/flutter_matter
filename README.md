<div align="center">

# flutter_matter

A beautiful and low-level [Matter](https://csa-iot.org/) plugin for **Flutter** on **Android** and **iOS**.

<p align="center">
  <img src="images/demo.gif" alt="flutter_matter demo" width="320" />
</p>

</div>

---

## ✨ Features

- **Provisioning**  
  Supports both **BLE commissioning** and **on-network commissioning**.  
  On Android, you can also provide your own GATT implementation to send Matter commissioning data.

- **Thread network support**  
  Pass a Thread Active Operational Dataset using:

  ```dart
  NetworkCredentials.thread(ThreadCredentials(...))
  ```

- **ICD (Intermittently Connected Devices)**  
  Full support for **Matter 1.2+ ICD commissioning** via:

  ```dart
  CompletionListener.onICDRegistrationComplete
  ```

- **Attribute read**  
  Read any attribute from any cluster.

- **Attribute write**  
  Write any attribute to any cluster.

- **Attribute / event subscribe**  
  Subscribe with optional `DataVersionFilter` for efficient change-only updates.

- **Invoke**  
  Send commands to any cluster endpoint.

- **Unpair**  
  Remove a device from the fabric with:

  ```dart
  unPairDevice(nodeId)
  ```

- **TLV**  
  Full TLV read/write stack for advanced low-level control.

- **Cluster helpers**  
  Convenience wrappers for:
  - `BasicInformationCluster`
  - `DescriptorCluster`

---

## Requirements and platform support

| Area | Supported baseline |
| --- | --- |
| Flutter | Flutter `3.41.0`, pinned in `.fvmrc`; older SDKs satisfy the pubspec constraint but are not currently validated |
| Dart | `>=3.3.3 <4.0.0`, unchanged in `pubspec.yaml` |
| Android | `minSdkVersion 21`, `compileSdk 34`, JDK 17 |
| Example Android build | Gradle 8.7, Android Gradle Plugin 8.6.0, Kotlin 1.7.10 |
| iOS | iOS 16.1 minimum for the plugin and example; Xcode 16.4 or later and CocoaPods 1.17 |
| iOS device support | Physical arm64 iPhoneOS devices only; the vendored `ZGMatter.framework` has no simulator slice |

The Android values describe the current repository build configuration and do not imply that an SDK upgrade has already been completed. The iOS deployment targets are aligned to 16.1. A Flutter 3.41 device build without code signing completed with Xcode 26.3 and CocoaPods 1.17.0.

Automated tests cover the plugin root `test/` suite only. The `example/` application is a build and manual demonstration target, never an automated test target.

See [Architecture](ARCHITECTURE.md), [Public API](docs/public-api.md), [Platform support](docs/platform-support.md), [Contributing](CONTRIBUTING.md), and the [PR review checklist](docs/pr-review-checklist.md) for details.

---

## 🚀 Getting Started

## Android

Make sure the following permissions are added to your **AndroidManifest.xml**:

```xml
<!-- Tell Google Play Store that your app uses Bluetooth LE -->
<!-- Set android:required="true" if Bluetooth is required -->
<uses-feature
    android:name="android.hardware.bluetooth_le"
    android:required="false" />

<!-- Android 12+ Bluetooth permissions -->
<uses-permission
    android:name="android.permission.BLUETOOTH_SCAN"
    android:usesPermissionFlags="neverForLocation" />
<uses-permission android:name="android.permission.BLUETOOTH_CONNECT" />

<!-- Android 11 and lower -->
<uses-permission
    android:name="android.permission.BLUETOOTH"
    android:maxSdkVersion="30" />
<uses-permission
    android:name="android.permission.BLUETOOTH_ADMIN"
    android:maxSdkVersion="30" />
<uses-permission
    android:name="android.permission.ACCESS_FINE_LOCATION"
    android:maxSdkVersion="30" />

<!-- Android 9 and lower -->
<uses-permission
    android:name="android.permission.ACCESS_COARSE_LOCATION"
    android:maxSdkVersion="28" />

<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
<uses-permission android:name="android.permission.CHANGE_WIFI_STATE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

---

## iOS

### 1. Add the required keys to `Info.plist`

```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>This app uses Bluetooth to connect to nearby devices for communication.</string>

<key>NSBonjourServices</key>
<array>
  <string>_meshcop._udp</string>
  <string>_matter._tcp</string>
  <string>_matterc._udp</string>
  <string>_matterd._udp</string>
</array>

<key>NSCameraUsageDescription</key>
<string>This app needs camera access to scan QR codes.</string>

<key>NSLocalNetworkUsageDescription</key>
<string>Required to discover local network devices.</string>
```

### 2. Add a Matter Extension to your project

<p align="center">
  <img src="images/addMatterExt.png" alt="Add Matter Extension" width="700" />
</p>

### 3. Add capabilities to both targets

In both the **main app target** and the **Matter Extension target**, add:

- **App Groups**
- **Matter Allow Setup Payload**

Make sure both targets use the **same App Group**.

<p align="center">
  <img src="images/ExtAppGroups.png" alt="App Groups setup" width="700" />
</p>

### 4. Add `AppGroupId` to both targets

In the **Info** section of both the main app target and the Matter Extension target, add:

- **Key:** `AppGroupId`
- **Value:** the same App Group value selected in step 3

This allows data sharing between the two targets.

<p align="center">
  <img src="images/infoConfig.jpeg" alt="Info.plist AppGroupId configuration" width="700" />
</p>

### 5. Copy the request handler code

Copy the contents of:

```text
example/ios/MatterExt/RequestHandler.swift
```

into your Matter Extension’s:

```text
RequestHandler.swift
```

---

## ▶️ Run the Example

## iOS

Open the following workspace in Xcode:

```sh
example/ios/Runner.xcworkspace
```

Then:

1. Fill in your signing information
2. Complete the iOS setup steps above

## Android

No additional setup is required.

## Start the example

```sh
cd example
fvm flutter pub get
fvm flutter run
```

---

## 📌 Notes

- Images are displayed using fixed widths to keep them clean and prevent stretching.
- Centered screenshots and demo media usually make plugin documentation look much better.
- This README keeps the setup simple while still looking polished and professional.

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome.

If you find this plugin useful, consider giving it a star.
