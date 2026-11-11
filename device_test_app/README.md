# flutter_matter_device_test_app

Dedicated physical-device validation app for `flutter_matter`.

The app runs on Android and physical iOS controllers. It is not published with the plugin and is not part of the required Dart CI gate. Every Run, including quick iteration, uses qualified real Matter hardware over Wi-Fi/IP commissioning; BLE discovery and BLE commissioning are not used in any Run.

## Test profiles

| Profile | Contents | Evidence role |
| --- | --- | --- |
| `quick` | `build_install`, `ip_discovery`, `ip_commissioning`, `operational_connect`, `onoff_invoke` | Iteration feedback only |
| `full` | All 12 fixed tests in [../doc/device-test-report.md](../doc/device-test-report.md) | The only formal PR/release evidence |

Only a completed `full` run can produce formal evidence. A P0 failure is preserved and never retried inside the same Run. Every device run, including `quick` iteration, uses qualified real Matter hardware; virtual commissionees are not supported.

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

The Agent must pass `start_run` setup material through `--args-file`, not `--args-json`, and must never print or commit that file.

## Physical-device roles

- Use a qualified real Matter On/Off commissionee for every Run, including quick iteration. Virtual commissionees are not supported.
- The commissionee must already be connected to the same trusted Wi-Fi/LAN as the controller and Mac host.
- Open a commissioning window on the commissionee before starting the Run.
- BLE discovery, BLE pre-scanning, and GATT commissioning are not used in any Run.
- Do not use an isolated guest network that blocks mDNS/IP commissioning or the Agent WebSocket connection.

## Prerequisites

- Android: physical device, USB or ADB-over-Wi-Fi access, and local-network connectivity.
- iOS: physical iPhone, valid local signing, a Matter Extension, the matching App Group, and the required Bonjour and local-network declarations.
- Xcode and CocoaPods tooling are required for iOS development builds.
- The real commissionee must advertise Matter commissionable service records on the LAN.

## Security and evidence hygiene

Never put setup codes, onboarding payloads, Wi-Fi SSIDs or passwords, Thread operational datasets, full UDIDs, serial numbers, certificates, private keys, or raw logs in reports or PR text. Use the in-app purge action before handing a device to another user. Purge is required because iOS Keychain items can survive app uninstallation.

Real-device CI is intentionally out of scope. Attach full-run JSON and Markdown reports to the PR manually and verify that the report plugin commit matches the PR head. All app UI, protocol strings, and repository documentation are English.

## Further documentation

- App architecture and manual flow: [../doc/device-test-app.md](../doc/device-test-app.md)
- Agent bridge, CLI, and protocol: [../doc/agent-device-testing.md](../doc/agent-device-testing.md)
- Evidence contract: [../doc/device-test-report.md](../doc/device-test-report.md)
- Validation policy: [../doc/device-validation.md](../doc/device-validation.md)
