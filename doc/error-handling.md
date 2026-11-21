# Error handling

This document defines the error boundary and compatibility contract for the
Dart bridge, Android, iOS, and TLV modules. The goals are to fail predictably,
preserve the existing MethodChannel wire format, and keep credentials, setup
payloads, certificates, private keys, and raw parameter JSON out of errors and
logs.

## Invariants

- Preserve the MethodChannel name `flutter_matter`, the `zgMatter://<host>/<path>`
  URL shape, and the `{code, jsonData}` / `{code, resultJson}` envelopes.
- Validate arguments before dispatching work or mutating writer/controller
  state.
- Convert malformed native payloads into typed, contextual errors rather than
  leaking `NoSuchMethodError`, `TypeError`, `RangeError`, or platform stack text.
- Keep stack traces in local diagnostics. Do not send native stack traces, raw
  exception messages, or full request parameters back to Dart.
- Complete each owned `Future`, `Completer`, or `FlutterResult` at most once.
- Preserve existing error codes where callers already consume them. Add
  structured detail instead of silently changing a public code.
- Controller lifecycle failures fail closed. Once native shutdown fails, the
  manager must not attempt to construct another controller in the same process.

## Dart error contract

| Boundary | Failure class | Behavior |
| --- | --- | --- |
| `MethodChannelFlutterMatter.requestPlatform` native failures | `CallPlatformException` | Wraps `PlatformException` and `MissingPluginException` with a method name, normalized code, safe category, and the original exception as its cause. |
| `MethodChannelFlutterMatter.requestPlatform` response envelope | `PlatformProtocolException` / `FormatException` | Rejects non-string, non-JSON, non-object, missing-field, wrong-type, and non-string-key response envelopes. `PlatformProtocolException` remains a `CallPlatformException` and also implements `FormatException` for compatibility with format-failure handling. |
| Callback handler boundary | `ArgumentError` or framework error envelope | Invalid callback arguments map to the compatible `argsInvalid` / `-99` envelopes with a safe message. |
| `checkCallArgNotNull` | `ArgumentError` | Reports the missing field and callback context without serializing the callback payload. |
| Controller request methods | `CallPlatformException` | `invoke`, `subscribe`, `read`, `write`, and `connectedDevice` await native acceptance. A rejected request removes its pending callback and rethrows the typed platform error. |
| Controller lifecycle | `ControllerLifecycleException` | A closed or superseded handle reports `ControllerLifecycleFailure.closed`; invalid manager state reports `nativeStateConflict`; native shutdown failure reports `shutdownFailed` and poisons further creation. |
| BLE and NSD calls | `CallPlatformException` | Keeps code and method name as structured fields and removes full parameter JSON from messages. |
| Onboarding parser | `CallPlatformException` / `FormatException` / `ArgumentError` | Distinguishes native parser failure, malformed native payload, and empty caller input. |
| Model `fromJson` / `decode` | `FormatException` | Reports a concrete field path such as `NodeState.endpoints[1]`. |
| Cluster helpers | `CallPlatformException` | Awaits request acceptance, then completes with a typed error for request rejection, missing reports, malformed TLV, callback failure, or the 15-second one-shot read timeout instead of hanging. The timeout is retained as the exception cause. |
| TLV decoding | `TlvParsingException` | Invalid bytes, truncated fields, invalid UTF-8, and out-of-range decoded values fail closed. |
| TLV misuse | `ArgumentError` | Invalid tag placement, container transitions, and caller arguments are rejected before mutation. |
| TLV encoding | `TlvEncodingException` | Unclosed containers and internal encoding failures are reported without corrupting the writer. |

`CallPlatformException` and `PlatformProtocolException` remain internal bridge
types. `ControllerLifecycleException` is re-exported from `controller.dart` so
callers can distinguish closed handles and poisoned lifecycle state. Existing
callers can continue to catch all of these as `Exception` through the affected
APIs.

`FlutterMatterPlatform` declares the transport methods used by controller, BLE,
NSD, and onboarding code: `requestPlatform`, `addHandler`, and `removeHandler`.
The controller creation, BLE manager, NSD request, and onboarding request paths
use this interface instead of downcasting to `MethodChannelFlutterMatter`.

`reportMatterError` records only a safe error summary and stack frames. It does
not log request parameters, native response bodies, or lower-level exception
messages.

For controller operations, acceptance of the native request is the boundary:
after acceptance, results and terminal callback events continue to use the
existing callback methods. A request rejection is different from an asynchronous
callback error, so only the callback registered for that rejected request is
removed.

The manager invalidates the Dart handle before issuing native deletion. This
means an in-flight request that completes after a fabric switch is rejected by
the post-request closed-handle check and cannot be mistaken for a result from the
replacement controller. Native shutdown and replacement creation are serialized
through the same lifecycle queue.

## Android

### MethodChannel dispatch and controller operations

`android/src/main/kotlin/com/tyx/flutter_matter/DeviceControl.kt` preserves the
external `-99` unexpected-error code. The Dart-facing message is the stable
`Device control operation failed`; the stack remains in the native log.

The controller argument helpers reject missing or wrong JSON types before the
Matter SDK is called. `pairDevice` and `pairDeviceWithAddress` use explicit
optional-string checks, so an absent completion listener is no longer confused
with `JSONObject.NULL`. Attestation and NOC callbacks catch failures inside
background threads and report them instead of losing an uncaught `NPE`.

`DeviceControl.kt` owns a single `ControllerLifecycleGate` slot. `/new` reserves
the slot before invoking the native constructor, and `/deleteDeviceController`
calls `shutdownCommissioning()` rather than reflection or `finalize()`.
`shutdownCommissioning()` stops the CHIP IO thread before wrapper and factory
shutdown. Successful shutdown returns the gate to `EMPTY`; a throw transitions it
to `POISONED`. The gate records the owning Flutter engine, so only that engine's
detach schedules the safe shutdown on the plugin's single-thread executor.

### BLE, DNS-SD, onboarding, and shared utilities

- `BLE.kt` validates discriminator, connection, boolean, and byte-array inputs,
  contains delegate callback failures, and maps unexpected failures to a safe
  `-99` result.
- Dart BLE registration removes a newly registered delegate handler when the
  native registration request fails. Clearing a delegate keeps the existing
  local handler until native confirms the clear.
- `Nsd.kt` validates service and TXT-record inputs, rejects unknown paths, uses
  thread-safe callback maps, and contains resolver/publish/remove callbacks.
- `BluetoothManager.kt` contains scan, connection, GATT, service-discovery, MTU,
  and cleanup failures so callback failures do not terminate silently.
- `Onboarding.kt` validates the JSON object and the required string field,
  rejects empty input, and returns stable QR/manual-pairing error messages.
- `Utils.kt` provides typed JSON extraction helpers, sanitized error categories,
  safe main-thread result delivery, and bounded native-to-Flutter callback waits.
  Inbound Android byte-array conversion accepts only integer values in the range
  `0..255`. On the Dart side, native response bytes accept either the Android
  signed representation (`-128..127`) or the unsigned representation (`0..255`)
  and normalize both to the same octet values.
- `ChipClient.kt` validates platform/context initialization and reports a safe
  initialization failure.
- `ExampleAttestationTrustStoreDelegate.kt` contains malformed test-certificate
  failures locally and never exposes certificate material to Dart.
- `Onboarding.kt` serializes discovery capabilities as the stable wire values
  `SOFT_AP = 1`, `BLE = 2`, and `ON_NETWORK = 3`; capabilities without a Dart
  representation are omitted.

The example DNS-SD resolver skips a service whose resolved host is null or
blank instead of forwarding an empty host to the callback.

## iOS

`ios/Classes/Utiles.h` and `Utiles.m` define the stable iOS bridge error codes:

- `invalidArguments`
- `invalidMethod`
- `unsupportedHost`
- `methodNotImplemented`
- `callbackDeliveryFailed`
- `internalError`

Existing `onBLECallException`, `onOnboardingCallException`, and
`DeviceControlCallException` codes remain compatible where callers already use
them.

### Entry and callback boundaries

- `FlutterMatterPlugin.m` validates the method URL, host, path, arguments type,
  and supported host before dispatch. Unknown hosts and paths return structured
  `FlutterError` values.
- Plugin registration starts the process-wide controller factory without creating
  a hidden default controller. `DeviceControlHandle.m` stores controllers by
  handle and allows multiple native controllers. `/deleteDeviceController` calls
  the controller's explicit `shutdown` and removes that handle; iOS does not add
  a native single-controller gate or process-wide poison state. The shared Dart
  manager still serializes the normal application lifecycle and poisons itself
  when a native shutdown request fails.
- `FlutterMatterResultSender` makes result delivery single-shot and main-thread
  safe.
- `DeviceControlHandle.m` validates pairing, Wi-Fi/Thread, callback-handle,
  certificate, byte-array, and path inputs; catches asynchronous exceptions; and
  delivers terminal callback events at most once for invoke/read/subscribe/write.
  Normal subscription reports do not emit `onDone`; a terminal subscription error
  emits one `onError` followed by one `onDone`. Path-level StatusIB results
  populate `attributeStatuses` or `eventStatuses`, and write callbacks identify
  the affected attribute with `attributeId`.
- `BleHandle.m` validates GATT payloads and returns structured failures for
  unsupported callback operations instead of reporting false success.
- `Onboarding.m` handles parser `NSError` values and returns stable messages for
  invalid QR or manual pairing input.
- `DeviceAttestationDelegate.m` handles nil attestation data and callback
  exceptions without constructing invalid JSON or crashing the callback thread.
- `MatterDevicePair.swift` uses a single-shot completion gate and maps missing
  App Group, malformed payload, and pairing failures to safe `NSError` values.
- `FlutterDeviceController.m`, `DefaultsUtils.m`, and `FabricKeys.m` guard nil
  values and log safe summaries rather than raw device, certificate, key, or
  storage values.

## TLV compatibility and migration

The TLV implementation follows the connectedhomeip Kotlin TLV behavior while
retaining the existing Dart entry points.

- `TlvReader` copies its input bytes, supports `Iterable<Element>`, and provides
  `peekElement`, `skipElement`, `exitContainer`, `reset`, `getLengthRead`, and
  `getRemainingLength`.
- `TlvWriter` uses a dynamic container stack, validates writes before mutating,
  and supports `putFloat`, `putUnsignedLongArray`, `putUnsignedBigInt`, and
  `putByteStringArrayValues(Tag, List<Uint8List>)`.
- `getULong()` remains source compatible but rejects values above
  `2^63 - 1`. Use `getULongBigInt()` or `UnsignedIntValue.unsignedValue` for the
  full unsigned 64-bit range.
- `putByteStringArray(Tag, List<int>)` is deprecated but retains its original
  signed-integer behavior. New code should use
  `putByteStringArrayValues(Tag, List<Uint8List>)` for octet-string arrays.
- `copyElement` accepts either `copyElement(reader)` or
  `copyElement(tag, reader)` and restores both writer and reader state on
  failure.

## Verification

Required Dart checks:

```sh
fvm dart format .
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
```

Targeted TLV checks:

```sh
fvm flutter test \
  test/tlv_read_write_test.dart \
  test/tlv_reader_test.dart \
  test/tlv_writer_test.dart \
  test/tlv_regression_test.dart
```

Device-test app checks:

```sh
cd device_test_app
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test test/infrastructure/matter/matter_tlv_test.dart
fvm flutter test
```

Native checks used for the current implementation:

```sh
cd example
GOOGLE_MATTER_SDK_REPO=/absolute/path/to/home.android.sdk_1_11_1/repo \
  fvm flutter build apk --debug
fvm flutter build ios --debug --no-codesign
```

The Dart and native build checks prove compilation and contract coverage. They
do not prove real Matter commissioning, BLE timing, NSD callback timing, or
iOS App Group behavior; those still require physical-device validation.

The current root plugin suite covers 171 tests. The device-test app remains a
separate local validation surface; its suite is not part of required CI.
