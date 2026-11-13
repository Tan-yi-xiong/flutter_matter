# flutter_matter_device_test_app

Dedicated physical-device validation app for `flutter_matter`.

The app runs on Android and physical iOS controllers. It is not published with the plugin and is not part of the required Dart CI gate. Every Run uses a Matter commissionee. The app passes the raw onboarding payload directly to the Matter SDK, which performs commissionee discovery and commissioning. Device provenance is not part of the report contract. A commissioning failure is preserved and never retried in the same Run.

## Test profiles

| Profile | Contents | Evidence role |
| --- | --- | --- |
| `quick` | `build_install`, `commissioning`, `operational_connect`, `onoff_invoke` | Iteration feedback only |
| `full` | All 11 fixed tests in [../doc/device-test-report.md](../doc/device-test-report.md) | The only formal PR/release evidence |

Only a completed `full` run can produce formal evidence. A P0 failure is preserved and never retried inside the same Run. Every device run, including `quick` iteration, uses a Matter commissionee.

## Setup

The setup flow requires only:

- Run mode: `quick` or `full`.
- Setup code or QR setup payload.
- Target Wi-Fi SSID.
- Wi-Fi password, or an empty value for an open network.

A commissionee factory reset is optional and happens after a finished Run (every Run adds one fabric); the Runner screen offers an optional post-Run cleanup action.

The app does not ask for model, firmware, state-change method, commissioning transport, controller-clean state, or secrets-purged state. It parses vendor and product identity from the commissionee payload automatically.

Before a Run starts, the app purges old run secrets and resets controller identities for the current platform. Cleanup failure blocks the Run. The app may cache the latest Wi-Fi SSID and password in secure storage and offers an explicit clear action; cached credentials never appear in state, reports, logs, or screenshots.

## Local checks

```bash
cd device_test_app
fvm flutter pub get
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
```

Official builds should be run from the repository root so commit metadata is injected through [../tool/device_test_app.dart](../tool/device_test_app.dart):

```bash
fvm dart run tool/device_test_app.dart check
fvm dart run tool/device_test_app.dart build-apk
fvm dart run tool/device_test_app.dart build-ios
fvm dart run tool/device_test_app.dart run --device <device-id>
```

The wrapper requires a clean tracked Git worktree and injects `PLUGIN_COMMIT` and `TEST_APP_COMMIT`. It prevents reports from claiming the wrong source revision.

For Agent mode, launch the app with the WebSocket endpoint printed by `tool/device_test_agent.dart serve`:

```bash
fvm dart run tool/device_test_app.dart run \
  --device <device-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

The Agent must collect the minimal setup data with Codex interactive prompts, pass `start_run` material through `--args-file`, not `--args-json`, and must never print or commit that file.

## Physical-device roles

- Use a Matter On/Off commissionee for every Run, including quick iteration. The app does not inspect or record device provenance.
- Confirm that the commissionee is discoverable by the Matter SDK through its supported commissioning transports.
- Confirm that the commissionee has an open commissioning window before starting the Run; a factory reset is optional and preferred after a finished Run.
- Do not add a host-side BLE/mDNS scan or readiness gate: commissionee discovery is delegated to the Matter SDK.
- Do not use an isolated guest network that blocks BLE setup, Wi-Fi/IP commissioning, CASE, or the Agent WebSocket connection.

## Prerequisites

- Android: physical device, USB or ADB-over-Wi-Fi access, and local-network connectivity.
- iOS: physical iPhone, valid local signing, a Matter Extension, the matching App Group, and the required Bonjour, Bluetooth, and local-network declarations.
- Xcode and CocoaPods tooling are required for iOS development builds.
- The controller must be able to reach the target Wi-Fi network for provisioning and CASE/control.

## Security and evidence hygiene

Never put setup codes, onboarding payloads, Wi-Fi SSIDs or passwords, full UDIDs, serial numbers, certificates, private keys, or raw logs in reports or PR text. Use the in-app purge action before handing a device to another user. Purge is required because iOS Keychain items can survive app uninstallation.

Hardware-in-the-loop CI is intentionally out of scope. Attach full-run JSON and Markdown reports to the PR manually and verify that the report plugin commit matches the PR head. Reports must use schema v4. All app UI, protocol strings, and repository documentation are English.

## Further documentation

- App architecture and manual flow: [../doc/device-test-app.md](../doc/device-test-app.md)
- Agent bridge, CLI, and protocol: [../doc/agent-device-testing.md](../doc/agent-device-testing.md)
- Evidence contract: [../doc/device-test-report.md](../doc/device-test-report.md)
- Validation policy: [../doc/device-validation.md](../doc/device-validation.md)
