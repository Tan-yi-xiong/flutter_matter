# Public API

The only supported import is:

```dart
import 'package:flutter_matter/flutter_matter.dart';
```

Everything exported from that library is public API. Files under `package:flutter_matter/src/` are internal; tests may import them, applications should not.

The current package version is `0.0.11`.

Use the generated [pub.dev API reference](https://pub.dev/documentation/flutter_matter/latest/) for signatures, parameters, return values, and member-level documentation. This page records the supported import boundary, exported surface, and compatibility rules.

For task-oriented examples, start with [Getting started](getting-started.md), [Commissioning](commissioning.md), or [Device operations](device-operations.md).

The [example code map](../example/README.md#code-map) links each workflow to the corresponding file and symbol under `example/lib/`.

## Controller and commissioning

Core types:

- `ChipDeviceController`
- `ControllerParams`
- `NetworkCredentials`
- `WiFiCredentials`
- `ThreadCredentials`
- `AttestationInfo`
- `CSRInfo`
- `defaultIpk`
- `kTestControllerNodeId`

Delegates and callbacks:

- `CompletionListener`
- `NOCChainIssuer`
- `DeviceAttestationDelegate`
- `KeypairDelegate`
- `InvokeCallback`
- `OpenCommissioningCallback`
- `ConnectedDeviceCallback`
- `ReportCallback` and `ReportCallbackWarp`
- `SubscriptionCallback` and `SubscriptionCallbackWarp`
- `WriteAttributesCallback` and `WriteAttributesCallbackWarp`
- `KeypairDelegateCallbackHandler`

`ChipDeviceController` provides:

- lifecycle: `newControllerIfNotExist`, `deleteDeviceController`, `destroy`
- commissioning: `pairDevice`, `pairDeviceWithAddress`, `stopDevicePairing`, `continueCommissioning`, `setCompletionListener`, `setNocChainIssuer`
- identity: `createRootCertificate`, `createOperationalCertificate`, `publicKeyFromCSR`, `onNOCChainGeneration`
- operations: `invoke`, `read`, `write`, `subscribe`, `unSubscription`, `connectedDevice`, `releaseConnectContext`
- commissioning windows and fabric state: `openPairingWindowWithPIN`, `getFabricIndex`

`NetworkCredentials` supports named Wi-Fi and Thread constructors plus the legacy Wi-Fi constructor. An empty Wi-Fi password represents an open network.

Fabric removal is not exposed as `unPairDevice`. Read the OperationalCredentials Fabric Table, obtain the active fabric index with `getFabricIndex()`, then send `RemoveFabric` through `invoke`.

`ControllerParams` currently sends `skipAttestationCertificateValidation: true` in its JSON payload. Treat this as a security-sensitive native-configuration limit. `setupURL` is not supported by the Matter 1.6.1 Android SDK and was removed from `ControllerParams`; omit it from constructor calls and JSON payloads.

## Onboarding

- `DiscoveryCapability`
- `OnboardingPayload`
- `OnboardingPayloadParser`
- `onboardingPayloadHost`

`OnboardingPayloadParser` parses QR setup codes and manual pairing codes. `pairDevice` requires an onboarding payload on iOS.

## BLE and GATT

- `BLEManager`
- `BLELayerPlatform`
- `BlePlatformDelegate`
- `BlePlatformDelegateCallbackHandler`
- `bleHostName`
- All exported `BLE_ERROR_*` constants

Android supports a custom GATT platform delegate. iOS exposes the callback surface, but Android remains the documented custom-GATT path.

## DNS-SD

- `NsdManager`
- `NsdServiceInfo`
- `ResolveCallback`
- `RemoveServicesCallback`
- `PublishCallback`
- `nsdHostName`

DNS-SD is implemented on Android. The iOS plugin does not route `nsd` requests.

## Matter paths and state

- `ChipAttributePath`
- `ChipEventPath`
- `ChipPathId`
- `IdType`
- `DataVersionFilter`
- `InvokeElement`
- `AttributeState`
- `AttributeWriteRequest`
- `ClusterState`
- `EventState`
- `Status`
- `NodeState`
- `EndpointState`
- `ICDDeviceInfo`

These types encode the JSON exchanged with native code. Their public fields and JSON representations are compatibility surfaces. `DataVersionFilter` is supported in Android subscriptions only.

## TLV

- `Element`
- `TlvReader`
- `TlvWriter`
- `TlvParsingException`
- `TlvEncodingException`
- `Value` and its concrete value types
- `Tag` and its concrete tag types
- TLV type classes, type constants, tag constants, and `encodeSize`

`tlv_types.dart` exports a `Type` class that is hidden from the package root to avoid colliding with `dart:core`.

## Cluster helpers

- `DescriptorCluster`
- `BasicInformationCluster`

Both helpers require a connected `ChipDeviceController`, node ID, and connection context.

## Export map

| Export path | Public symbols |
| --- | --- |
| `src/controller.dart` | Controller, credentials, callback, delegate, and certificate APIs listed above |
| `src/onboarding.dart` | Onboarding types and parser |
| `src/ble.dart` | BLE manager, platform delegate, host name, and `BLE_ERROR_*` constants |
| `src/nsd.dart` | NSD manager, service info, callbacks, and host name |
| `src/model/*.dart` | Matter paths, state, status, invoke, data-version, and ICD models |
| `src/tlv/*.dart` | TLV elements, tags, values, readers, writers, type classes, and constants |
| `src/clusters/*.dart` | Basic Information and Descriptor helpers |

`test/public_api_test.dart` guards the golden export list. `test/method_channel_contract_test.dart` guards URL construction and JSON envelopes. These tests do not replace compatibility review of method signatures or callback semantics.

## Versioning and deprecation

The package follows Semantic Versioning. Public types, constructors, methods, default values, export paths, and MethodChannel contracts are compatibility surfaces.

- Before `1.0.0`, a breaking change may use a minor version under Semantic Versioning's initial-development rule. Label it explicitly and provide migration guidance.
- After `1.0.0`, breaking changes require a major version.
- Compatible additions and fixes follow normal minor and patch rules.
- Deprecations use `@Deprecated` with a replacement and migration note. Keep a deprecated API for at least one minor release unless retention is unsafe or impossible.
- Removing or changing an existing API requires the same versioning review as adding a breaking replacement.
