# ADR 0001: MethodChannel URL and JSON Contract

- Status: Accepted
- Date: 2026-11-11

## Context

The plugin uses one MethodChannel named `flutter_matter`. Calls are encoded as custom URLs and JSON strings rather than separate channel methods with structured maps. Native code routes requests by URL host and path, and callbacks return through the same channel. Small changes to host names, path spelling, JSON keys, or envelope shape can break Android and iOS compatibility without producing a Dart compile error.

## Decision

Treat the following as contractual:

- Channel name: `flutter_matter`.
- Request scheme and routing form: `zgmatter://<host>/<path>`.
- Effective hosts: `devicecontroller`, `ble`, `onboarding`, and `nsd`.
- Request argument encoding: a JSON string.
- Successful request result envelope: `{"code": 0, "jsonData": <object>}`.
- Request error envelope: a non-zero `code` with `jsonData` containing an error object.
- Native callback envelope: `{"code": 0, "resultJson": "<json-string>"}`.
- Callback paths use the same host/path form and include the applicable controller or callback handle.
- JSON field names used by models, controllers, and native handlers are part of the contract.

The scheme and host are normalized by `Uri`, so documentation uses lower-case `zgmatter` and lower-case host names. Path casing and JSON keys remain case-sensitive.

Do not rename, remove, or reinterpret an existing route or envelope in a compatible-looking patch change. A change requires both native implementations, Dart handlers, tests, documentation, and migration notes.

## Consequences

- `test/method_channel_contract_test.dart` is the lightweight guard for URL construction and envelope keys.
- Android and iOS dispatch changes must be reviewed together unless the change is explicitly platform-specific.
- A Dart-only green CI result cannot validate a native route change.
- Pull requests must declare MethodChannel and JSON compatibility impact in the template.
- There is no protocol version field in the current envelope, so backward compatibility must be maintained by preserving existing fields and adding optional fields where possible.
