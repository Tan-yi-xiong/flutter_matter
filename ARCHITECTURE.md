# Architecture

`flutter_matter` is a low-level Flutter plugin for apps that control and commission Matter devices. Dart APIs delegate to native Matter implementations on Android and iOS; the package is not a pure-Dart Matter stack.

## Layers

```text
Flutter host app
      |
      v
Public Dart API and models
      |
      v
MethodChannel: flutter_matter
      |
      +-----------------------------+
      |                             |
      v                             v
Android plugin + Matter SDK     iOS plugin + ZGMatter
```

The supported consumer surface is exported by `package:flutter_matter/flutter_matter.dart`. See [Public API](doc/public-api.md).

## MethodChannel contract

Dart requests use the `flutter_matter` MethodChannel and a URI-shaped method name:

```text
zgmatter://<host>/<path>
```

`Uri` lowercases the scheme and host; the path remains case-sensitive. The protocol hosts are:

| Host | Purpose | Android | iOS |
| --- | --- | --- | --- |
| `devicecontroller` | Controller lifecycle, commissioning, read, write, invoke, and subscriptions | Yes | Yes |
| `ble` | BLE connection and GATT operations | Yes | Yes |
| `onboarding` | QR and manual setup-code parsing | Yes | Yes |
| `nsd` | DNS-SD resolution and publishing | Yes | No |

Request arguments are JSON strings. Native responses use:

```json
{"code": 0, "jsonData": {}}
```

Non-zero codes become Dart plugin errors. Host names, paths, JSON fields, and envelopes are compatibility surfaces.

## Controllers and callbacks

`ChipDeviceController.newControllerIfNotExist` requests a controller from the
process-wide `ChipDeviceControllerManager` and receives an opaque native handle.
The manager serializes all create/delete transitions and permits exactly one
live Dart-visible native controller. Requests with the same `fabricId` and
`rootCertificate` return the same Dart object and increment an acquisition
reference count. A different identity invalidates the old Dart handle, performs
native shutdown, and only then creates the replacement.

Native-to-Dart callbacks use the same channel and return:

```json
{"code": 0, "resultJson": "{}"}
```

`resultJson` is a JSON string. Callback families include `CompletionListener`, `NOCChainIssuer`, `DeviceAttestationDelegate`, invoke/subscription/report/write callbacks, connection callbacks, commissioning-window callbacks, and BLE platform delegates. Keep callback objects alive for as long as the native operation can emit events.

`close()` releases one acquisition; the final release deletes the native
controller. `deleteDeviceController()` remains a compatibility alias.
`destroy()` only removes Dart handlers and callback maps, but the manager keeps
the abandoned native handle so the next acquisition can shut it down before
creating a replacement. A failed native shutdown poisons the manager until the
process restarts.

The Dart manager is isolate-scoped; the native gate is process-wide. Multiple
Flutter engines therefore cannot each own a controller, even though each engine
has an independent Dart manager.

## Threading

Android dispatches plugin work through a shared single-thread executor. Native-to-Dart callback bridges schedule MethodChannel work on the main Looper and may block a worker until Dart responds. Do not start blocking native operations from the Android main thread.

iOS runs plugin work on the serial `Matter Thread queue`. Callback bridges dispatch to the main queue. Callback handlers must return quickly and must not wait on the same native queue.

## Native boundaries

The Android entry point is `FlutterMatterPlugin`. It routes requests by URI host to controller, BLE, onboarding, and NSD handlers. Matter behavior comes from the prefixed Android artifact `com.github.Tan-yi-xiong:flutter_matter_android_prefixed:1.0.6`.

The iOS entry point is the Objective-C `FlutterMatterPlugin`, backed by the vendored `ZGMatter.framework`. It routes controller, BLE, and onboarding hosts. NSD is not implemented on iOS. `ZGMTRInitializeControllerFactory()` starts the process-wide factory during plugin registration without creating a hidden default controller.

## Platform differences

| Capability | Android | iOS |
| --- | --- | --- |
| Controller, commissioning, read, write, invoke, subscriptions | Yes | Yes |
| `pairDevice` onboarding payload | Optional with a setup PIN | Required |
| `pairDeviceWithAddress` | Yes | No |
| `dataVersionFilters` | Yes | No |
| DNS-SD helpers | Yes | No |
| Custom GATT platform delegate | Supported path | Callback surface only |
| Simulator | Not applicable | Not supported |

Empty Wi-Fi passwords represent open networks. Thread credentials use an operational dataset. ICD registration is exposed through `CompletionListener`.

`ControllerParams.toJson()` currently sends `skipAttestationCertificateValidation: true` because of the native controller configuration. Treat this as a security-sensitive known limit until the native path supports configurable attestation validation.

## Verification boundary

Automated tests cover the root Dart `test/` suite: public exports, MethodChannel URL construction and envelopes, models, TLV, onboarding, and callback routing. The required Dart workflow does not compile Android or iOS code, run native tests, or validate Matter behavior.

The example app is a manual build and demonstration target. The dedicated device-test app produces versioned evidence for device-behavior changes. See [Contributing](CONTRIBUTING.md), [Platform support](doc/platform-support.md), and [Device validation](doc/device-validation.md).
