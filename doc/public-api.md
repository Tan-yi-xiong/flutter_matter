# Public API

The only supported import is:

```dart
import 'package:flutter_matter/flutter_matter.dart';
```

Everything exported by that library is public API. Direct imports from `package:flutter_matter/src/...` are internal implementation paths and are not a supported consumer boundary. Tests may import internal paths when they need to verify implementation details.

The package version is currently `0.0.11`. The public surface is organized below by capability. The final export-map table is the authoritative list of paths exported from `lib/flutter_matter.dart`.

## Controller and commissioning

Core controller types:

- `ChipDeviceController`
- `ControllerParams`
- `NetworkCredentials`
- `WiFiCredentials`
- `ThreadCredentials`
- `AttestationInfo`
- `CSRInfo`
- `defaultIpk`
- `kTestControllerNodeId`

Commissioning delegates:

- `CompletionListener`
- `NOCChainIssuer`
- `DeviceAttestationDelegate`
- `KeypairDelegate`
- `InvokeCallback`
- `OpenCommissioningCallback`
- `ConnectedDeviceCallback`
- `ReportCallback`
- `ReportCallbackWarp`
- `SubscriptionCallback`
- `SubscriptionCallbackWarp`
- `WriteAttributesCallback`
- `WriteAttributesCallbackWarp`
- `KeypairDelegateCallbackHandler`

`ChipDeviceController` provides the main workflows: `newControllerIfNotExist`, `pairDevice`, `setCompletionListener`, `setNocChainIssuer`, `continueCommissioning`, `invoke`, `read`, `write`, `subscribe`, `connectedDevice`, `releaseConnectContext`, `openPairingWindowWithPIN`, `getFabricIndex`, `unSubscription`, and `deleteDeviceController`.

The callback wrapper types and callback-handler types are exported for advanced use. Most applications should implement the delegate interfaces and use the wrapper classes instead of constructing bridge handlers directly.

`NetworkCredentials` retains the legacy Wi-Fi constructor for compatibility and provides named Wi-Fi and Thread constructors. Empty Wi-Fi passwords are valid for open networks.

## Onboarding

- `DiscoveryCapability`
- `OnboardingPayload`
- `OnboardingPayloadParser`
- `onboardingPayloadHost`

`OnboardingPayloadParser` parses either a QR setup code or a manual pairing code. iOS callers must provide an onboarding payload to `pairDevice`.

## BLE and GATT

- `BLEManager`
- `BLELayerPlatform`
- `BlePlatformDelegate`
- `BlePlatformDelegateCallbackHandler`
- `bleHostName`

Current BLE error constants:

```text
BLE_ERROR_ADAPTER_UNAVAILABLE
BLE_ERROR_NO_CONNECTION_RECEIVED_CALLBACK
BLE_ERROR_CENTRAL_UNSUBSCRIBED
BLE_ERROR_GATT_SUBSCRIBE_FAILED
BLE_ERROR_GATT_UNSUBSCRIBE_FAILED
BLE_ERROR_GATT_WRITE_FAILED
BLE_ERROR_GATT_INDICATE_FAILED
BLE_ERROR_CHIPOBLE_PROTOCOL_ABORT
BLE_ERROR_REMOTE_DEVICE_DISCONNECTED
BLE_ERROR_APP_CLOSED_CONNECTION
BLE_ERROR_NOT_CHIP_DEVICE
BLE_ERROR_INCOMPATIBLE_PROTOCOL_VERSIONS
BLE_ERROR_INVALID_FRAGMENT_SIZE
BLE_ERROR_START_TIMER_FAILED
BLE_ERROR_CONNECT_TIMED_OUT
BLE_ERROR_RECEIVE_TIMED_OUT
BLE_ERROR_INVALID_MESSAGE
BLE_ERROR_FRAGMENT_ACK_TIMED_OUT
BLE_ERROR_KEEP_ALIVE_TIMED_OUT
BLE_ERROR_NO_CONNECT_COMPLETE_CALLBACK
BLE_ERROR_INVALID_ACK
BLE_ERROR_REASSEMBLER_MISSING_DATA
BLE_ERROR_INVALID_BTP_HEADER_FLAGS
BLE_ERROR_INVALID_BTP_SEQUENCE_NUMBER
BLE_ERROR_REASSEMBLER_INCORRECT_STATE
```

## DNS-SD

- `NsdManager`
- `NsdServiceInfo`
- `ResolveCallback`
- `RemoveServicesCallback`
- `PublishCallback`
- `nsdHostName`

The NSD host is implemented on Android only. The iOS plugin does not route `nsd` requests.

## Matter paths and state models

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

These types define the JSON models exchanged with native code. Their field names and JSON representations are compatibility surfaces. `DataVersionFilter` is currently supported by Android subscriptions only.

## TLV primitives

- `Element`
- `TlvReader`
- `TlvWriter`
- `TlvParsingException`
- `TlvEncodingException`
- `Value`
- `IntValue`
- `UnsignedIntValue`
- `BooleanValue`
- `FloatValue`
- `DoubleValue`
- `Utf8StringValue`
- `ByteStringValue`
- `NullValue`
- `StructureValue`
- `ArrayValue`
- `ListValue`
- `EndOfContainerValue`
- `Tag`
- `AnonymousTag`
- `ContextSpecificTag`
- `CommonProfileTag`
- `ImplicitProfileTag`
- `FullyQualifiedTag`
- `encodeSize`
- `SignedIntType`
- `UnsignedIntType`
- `BooleanType`
- `FloatType`
- `DoubleType`
- `Utf8StringType`
- `ByteStringType`
- `NullType`
- `StructureType`
- `ArrayType`
- `ListType`
- `EndOfContainerType`

The `Type` class from `tlv_types.dart` is intentionally hidden at the package root to avoid a name collision. Type-code and tag constants exported from the root are:

```text
MODIFIED_TYPE_MASK
ELEMENT_TYPE_MASK
SIGNED_INT_TYPE
UNSIGNED_INT_TYPE
UTF8_STRING_TYPE
BYTE_STRING_TYPE
BOOLEAN_FALSE
BOOLEAN_TRUE
FLOATING_POINT_4
FLOATING_POINT_8
NULL
STRUCTURE
ARRAY
LIST
END_OF_CONTAINER
TAG_MASK
ANONYMOUS
CONTEXT_SPECIFIC
COMMON_PROFILE_2
COMMON_PROFILE_4
IMPLICIT_PROFILE_2
IMPLICIT_PROFILE_4
FULLY_QUALIFIED_6
FULLY_QUALIFIED_8
```

## Cluster helpers

- `DescriptorCluster` with `readDeviceTypeListAttribute`, `readPartsListAttribute`, and `readServerListAttribute`.
- `BasicInformationCluster` with `readProductIDAttribute`, `readVendorIDAttribute`, `readSoftwareVersionAttribute`, and `readHardwareVersionStringAttribute`.

Both helpers require a connected `ChipDeviceController`, node ID, and connection context.

## Export map

| Export path | Exported top-level symbols |
| --- | --- |
| `src/controller.dart` | `AttestationInfo`, `ChipDeviceController`, `CompletionListener`, `ConnectedDeviceCallback`, `ControllerParams`, `CSRInfo`, `defaultIpk`, `DeviceAttestationDelegate`, `InvokeCallback`, `KeypairDelegate`, `KeypairDelegateCallbackHandler`, `kTestControllerNodeId`, `NetworkCredentials`, `NOCChainIssuer`, `OpenCommissioningCallback`, `ReportCallback`, `ReportCallbackWarp`, `SubscriptionCallback`, `SubscriptionCallbackWarp`, `ThreadCredentials`, `WiFiCredentials`, `WriteAttributesCallback`, `WriteAttributesCallbackWarp` |
| `src/onboarding.dart` | `DiscoveryCapability`, `onboardingPayloadHost`, `OnboardingPayload`, `OnboardingPayloadParser` |
| `src/ble.dart` | `bleHostName`, all `BLE_ERROR_*` constants, `BLELayerPlatform`, `BLEManager`, `BlePlatformDelegate`, `BlePlatformDelegateCallbackHandler` |
| `src/model/invoke_element.dart` | `InvokeElement` |
| `src/model/chip_path_id.dart` | `ChipPathId`, `IdType` |
| `src/tlv/element.dart` | `Element` |
| `src/tlv/tag.dart` | `Tag` hierarchy and tag constants |
| `src/tlv/tlv_reader.dart` | `TlvParsingException`, `TlvReader` |
| `src/tlv/tlv_writer.dart` | `TlvEncodingException`, `TlvWriter` |
| `src/tlv/tlv_types.dart` | Type classes, type constants, and `encodeSize`; `Type` is hidden at the package root |
| `src/tlv/values.dart` | `Value` hierarchy |
| `src/model/attribute_state.dart` | `AttributeState` |
| `src/model/attribute_write_request.dart` | `AttributeWriteRequest` |
| `src/model/cluster_state.dart` | `ClusterState` |
| `src/model/event_state.dart` | `EventState` |
| `src/model/status.dart` | `Status` |
| `src/model/node_state.dart` | `NodeState` |
| `src/model/endpoint_state.dart` | `EndpointState` |
| `src/model/chip_attribute_path.dart` | `ChipAttributePath` |
| `src/model/chip_event_path.dart` | `ChipEventPath` |
| `src/model/data_version_filter.dart` | `DataVersionFilter` |
| `src/model/icd_device_info.dart` | `ICDDeviceInfo` |
| `src/nsd.dart` | `NsdManager`, `NsdServiceInfo`, `nsdHostName`, `PublishCallback`, `RemoveServicesCallback`, `ResolveCallback` |
| `src/clusters/descriptor_cluster.dart` | `DescriptorCluster` |
| `src/clusters/basic_information_cluster.dart` | `BasicInformationCluster` |

## Versioning and deprecation policy

The package follows Semantic Versioning. Public types, constructors, methods, default values, exported paths, and MethodChannel wire contracts are compatibility surfaces.

- Before `1.0.0`, a breaking public API change may be released in a minor version under Semantic Versioning's initial-development rule. It must be labeled explicitly in the pull request and `CHANGELOG.md`, and it must include migration guidance.
- After `1.0.0`, breaking changes require a major version.
- Compatible additions and fixes follow normal minor and patch rules.
- Deprecations use Dart's `@Deprecated` annotation with the replacement and migration note. A deprecated API should remain for at least one minor release unless retaining it is unsafe or technically impossible.
- Removing or changing an existing MethodChannel host, path, JSON key, or callback envelope requires compatibility review even when no Dart symbol is removed.
- Direct `src/` imports are not versioned as a consumer API and may change without a public migration path.

Public export drift is guarded by `test/public_api_test.dart`. URL and envelope behavior is guarded by `test/method_channel_contract_test.dart`. These tests are lightweight governance; they do not replace review of method signatures or wire compatibility.
