# Device operations

Use this guide after a device has been commissioned. A controller can create or reuse a CASE connection, run Interaction Model operations, and release the connection context when the session ends.

## Connection lifecycle

Call `controller.connectedDevice(nodeId, callback)`. On success, `ConnectedDeviceCallback.onConnected` returns an opaque `context`. Pass that context to subsequent `read`, `write`, `invoke`, and `subscribe` calls, then call `controller.releaseConnectContext(context)` when the session is no longer needed.

The example's callback-to-`Future` adapter is [`MatterApiService.connect`](../example/lib/src/matter_api_service.dart#L9-L23). Context cleanup is [`releaseContext`](../example/lib/src/matter_api_service.dart#L25-L32).

## Read

Use `controller.read` with a `ReportCallback` or `ReportCallbackWarp`. Provide one or more `ChipAttributePath` values, or event paths when reading events.

```dart
await controller.read(
  nodeId,
  callback,
  attributePaths,
  eventPaths,
  dataVersionFilters,
  isFabricFiltered,
  imTimeoutMs,
  eventMin,
  connectContext: context,
);
```

The complete implementation is [`MatterApiService.read`](../example/lib/src/matter_api_service.dart#L74-L118). It resolves the first report into a `NodeState` and handles empty reports and errors.

Use [Public API](public-api.md#matter-paths-and-state) to find the path and state types. `dataVersionFilters` are supported in Android subscriptions only; see [Platform support](platform-support.md#feature-availability).

## Write

Use `controller.write` with a `WriteAttributesCallback` and a list of `AttributeWriteRequest` values. The callback receives an optional status for each path and an error when the request fails.

See [`MatterApiService.write`](../example/lib/src/matter_api_service.dart#L120-L156).

## Invoke

Use `controller.invoke` with an `InvokeElement` and an `InvokeCallback`. A successful response can contain TLV data or only a success status; handle both cases. The callback must also handle `onError` and `onDone`.

See [`MatterApiService.invoke`](../example/lib/src/matter_api_service.dart#L34-L72) and the On/Off command flow in [`DevicePage._invokeOnOff`](../example/lib/src/pages/device_page.dart#L148-L177).

## Subscribe

Use `controller.subscribe` with a `SubscriptionCallback` or `SubscriptionCallbackWarp`. Wait for `onSubscriptionEstablished` before reporting the subscription as active. Reports arrive through `onReport`; failures arrive through `onError`.

To cancel, obtain the current fabric index with `controller.getFabricIndex()` and call `controller.unSubscription(fabricIndex, nodeId, subscriptionId)`.

See [`MatterApiService.subscribe`](../example/lib/src/matter_api_service.dart#L158-L220) and [`DevicePage._cancelSubscription`](../example/lib/src/pages/device_page.dart#L89-L96).

## Fabric management

Fabric removal is not exposed as `unPairDevice`. Read the OperationalCredentials Fabric Table, obtain the active fabric index with `getFabricIndex()`, then send `RemoveFabric` through `invoke`.

The example implements both steps in [`readFabrics`](../example/lib/src/matter_api_service.dart#L286-L310) and [`removeFabric`](../example/lib/src/matter_api_service.dart#L312-L335). The guarded user flow is in [`DevicePage._removeFabric`](../example/lib/src/pages/device_page.dart#L357-L418).

## Callback lifetime

Keep callback objects alive for as long as the native operation can emit events. The `*Warp` classes adapt the callback interfaces to Dart functions:

- `ReportCallbackWarp` for `read`
- `WriteAttributesCallbackWarp` for `write`
- `SubscriptionCallbackWarp` for `subscribe`
- `_InvokeCallback` in the example for `invoke`
- `_ConnectedCallback` in the example for `connectedDevice`

Do not complete a `Future` more than once when a native callback can fire `onError`, `onDone`, or multiple reports. The example's service classes show the expected guards.

## Example map

| Operation | Complete implementation |
| --- | --- |
| Connect and release | [`MatterApiService.connect` / `releaseContext`](../example/lib/src/matter_api_service.dart#L9-L32) |
| Read | [`MatterApiService.read`](../example/lib/src/matter_api_service.dart#L74-L118) |
| Write | [`MatterApiService.write`](../example/lib/src/matter_api_service.dart#L120-L156) |
| Invoke | [`MatterApiService.invoke`](../example/lib/src/matter_api_service.dart#L34-L72) |
| Subscribe and cancel | [`MatterApiService.subscribe`](../example/lib/src/matter_api_service.dart#L158-L220) |
| Fabric table and removal | [`readFabrics` / `removeFabric`](../example/lib/src/matter_api_service.dart#L286-L335) |
| Device UI flows | [`DevicePage`](../example/lib/src/pages/device_page.dart#L19-L418) |

For the full controller surface, see [Public API](public-api.md). For platform differences, see [Platform support](platform-support.md).
