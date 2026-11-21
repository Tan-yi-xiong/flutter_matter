# Commissioning

Use this guide after completing [Getting started](getting-started.md). Commissioning has two distinct outcomes: the device is added to the fabric by the native Matter stack, and the host app receives a node ID that can be used for later CASE operations.

## Choose a commissioning path

| Path | API | Platforms | Use when |
| --- | --- | --- | --- |
| SDK-managed Wi-Fi or Thread | `pairDevice` | Android, iOS | The native stack can discover the commissionee and you have an onboarding payload or setup PIN. |
| Direct address | `pairDeviceWithAddress` | Android | Platform discovery is unavailable, but the commissionee address, port, discriminator, and setup PIN are known. |
| Google dual-fabric handoff | Example integration | Android | The first fabric is created by Google Home and the app commissions the second fabric through the local stack. |

`pairDevice` is the default path. Prefer it unless you have a specific reason to bypass discovery.

## Standard commissioning flow

1. Create a persistent `ChipDeviceController` and keep the same fabric identity across app launches.
2. Set a `NOCChainIssuer` if your app issues operational certificates instead of using the native default.
3. Call `pairDevice` with the onboarding payload or setup PIN and the network credentials.
4. Wait for `CompletionListener.onCommissioningComplete` with error code `0`.
5. Use the returned node ID for connection and Interaction Model operations.

The complete flow is in [`MatterCommissioningService.commission`](../example/lib/src/commissioning_service.dart#L26-L93). The callback handling, NOC generation, attestation continuation, and timeout logic are in [`_CommissioningDelegate`](../example/lib/src/commissioning_service.dart#L208-L341).

## Network credentials

Use `NetworkCredentials.wifi` for Wi-Fi commissioning:

```dart
NetworkCredentials.wifi(
  WiFiCredentials(ssid: ssid, password: password),
)
```

An empty password is valid for an open Wi-Fi network. Use `NetworkCredentials.thread` with a Thread Active Operational Dataset for Thread commissioning:

```dart
NetworkCredentials.thread(
  ThreadCredentials(operationalDataset: operationalDataset),
)
```

The example uses SDK-managed Wi-Fi commissioning in [`commission`](../example/lib/src/commissioning_service.dart#L26-L93). Keep Wi-Fi passwords and Thread datasets out of logs and persistent plaintext storage.

## Direct-address commissioning

`pairDeviceWithAddress` bypasses discovery and starts PASE against an explicit `address` and `port`. It requires a discriminator and setup PIN and is implemented on Android only. On iOS, continue to use `pairDevice` with the onboarding payload.

See [`MatterCommissioningService.commissionWithAddress`](../example/lib/src/commissioning_service.dart#L95-L143).

## Google Home dual-fabric commissioning

The example includes an Android-only Google Home integration:

1. Start a Google Home handoff session.
2. Wait for the first-fabric handoff endpoint.
3. Commission the second fabric with `pairDeviceWithAddress`.
4. Complete the handoff with the real second-fabric outcome.

See [`MatterCommissioningService.commissionGoogleDualFabric`](../example/lib/src/commissioning_service.dart#L145-L197). This path requires the Google Home SDK and a device with the Play Services Home module; follow [Example app](../example/README.md) for the build prerequisites.

## Cancellation and failure handling

- Call `stopDevicePairing(nodeId)` when the user cancels an in-progress commissioning attempt.
- Complete or fail all waiting `Future`s exactly once. The example uses one `Completer` in `_CommissioningDelegate`.
- Treat non-zero pairing or commissioning error codes as failure. Do not report a node as commissioned based only on `pairDevice` returning.
- If commissioning fails, stop pairing and call `await controller.close()` when the controller will not be reused.
- Keep the controller alive for later operations when commissioning succeeds; every successful acquisition must eventually be balanced by `close()`.
- Do not call `destroy()` as native cleanup. It only clears Dart handlers and callback maps; the next acquisition performs the deferred native shutdown.

See [`cancelCommissioning`](../example/lib/src/commissioning_service.dart#L16-L24) and the failure path in [`commission`](../example/lib/src/commissioning_service.dart#L82-L92).

## Platform rules

- `pairDevice` requires an onboarding payload on iOS.
- `pairDevice` accepts a setup PIN or onboarding payload on Android.
- Direct-address commissioning is Android-only.
- Open Wi-Fi is represented by an empty password.
- `dataVersionFilters` are Android-only and apply to subscriptions, not commissioning.
- The iOS controller must run on a physical arm64 device.

For the full capability matrix, see [Platform support](platform-support.md).
