# Device Test App

The dedicated device-test app lives in [`device_test_app/`](../device_test_app/). It is the primary manual and Agent-driven validation surface for `flutter_matter`. It is not published with the plugin and is not covered by the required Dart CI gate.

The app emits versioned evidence instead of relying on ad-hoc command transcripts. Formal evidence must use the `full` profile and the report contract in [device-test-report.md](device-test-report.md). Physical-device validation has not yet been completed; this repository records that status only after a qualified run and reviewer-safe report are available.

## Test profiles

| Profile | Tests | Formal evidence |
| --- | --- | --- |
| `quick` | `build_install`, `ble_discovery`, `ble_commissioning`, `operational_connect`, `onoff_invoke` | No |
| `full` | All 13 fixed tests from the report contract | Yes, when all required P0 tests pass |

`quick` is intended for developer iteration and never satisfies PR or release evidence. A `full` run is the only formal evidence source.

## Full validation order

1. `build_install`
2. `ble_discovery`
3. `ble_commissioning`
4. `operational_connect`
5. `onoff_invoke`
6. `onoff_subscription`
7. `node_label_persistence`
8. `app_restart`
9. `factory_reset_recommission`
10. `invalid_setup_passcode`
11. `bluetooth_disabled`
12. `invalid_wifi_password`
13. `remove_fabric_ui`

A P0 failure or skip ends the current Run. Dependent tests are recorded as `not_run` with a reason. A P0 test is never retried inside the same Run to manufacture a green result.

A failed `app_restart` result is recorded before recovery. A failed `factory_reset_recommission` stops the remaining destructible sequence. P2 failures are recorded and require explicit maintainer risk acceptance.

## Runtime architecture

The app separates pure domain logic from hardware and platform adapters:

- **Domain:** fixed test catalog, results, resumable Run state, and the report model.
- **Application:** `RunCoordinator`, the 13 fixed test cases, profiles, operator prompts, failure policy, and run recovery.
- **Agent:** protocol v1, state and event projection, and the reconnecting bridge client.
- **Infrastructure:** BLE, Matter controller and certificate services, adapters for application ports, `ProvisioningSecretStore`, `FileRunPersistence`, report files, platform information, and sharing.
- **Presentation:** Home, Setup, Runner, prompt dialogs, Results, and the application controller.

Widgets never call hardware APIs directly. The UI controller and Agent observe the same `RunCoordinator` state and event streams, while infrastructure adapters implement the hardware-facing application ports.

The app is designed for Android and physical iOS controllers. Real Matter hardware is preferred; the Android Virtual Matter Device App is a functional fallback. Physical iOS and Android controllers can both test real hardware or that virtual commissionee.

## Controller and commissionee roles

- **Controller:** the Android or physical iOS phone running `device_test_app`. It creates controller identity, discovers BLE commissionees, commissions the device, connects over CASE, invokes and subscribes to OnOff, and manages fabric state.
- **Commissionee:** a qualified real Matter On/Off device when available. It is the preferred target.
- **Virtual fallback:** a distinct Android phone running the official Project CHIP Android Virtual Matter Device App. For an Android controller this is the canonical two-Android-phone topology; a physical iOS controller can test the same distinct Android commissionee.

When the virtual fallback is selected, the run must record the reason that real hardware was unavailable. The controller and virtual commissionee must be separate devices; they cannot be the same phone.

When multiple phones are connected, the Agent must ask the user to choose the controller. It must also ask a separate question for the virtual commissionee and reject the controller phone. The Agent never selects a phone by connection order, platform, or previous use.

## Persistence and secrets

A Run is stored under the app Documents directory:

```text
runs/<run_id>/
  run_state.json
  device-test-report.json
  device-test-report.md
```

`run_state.json` is written atomically and stores the complete recoverable state, including the session, execution state, target node ID, app-restart checkpoint, and active prompt. Terminal and corrupt run-state files are ignored when selecting an unfinished run for recovery.

Setup codes, onboarding payloads, Wi-Fi credentials, Thread operational datasets, controller private key material, and certificates are kept in platform secure storage, not in `run_state.json` or report files. Secrets remain until the operator selects the purge action. iOS Keychain entries can survive app uninstallation, so uninstall is not a substitute for purge.

The app does not write screenshots, raw logs, or event transcripts into formal reports. Real-device CI is intentionally out of scope: attach the full-run JSON and Markdown report to the PR manually and require the report plugin commit to match the PR head.

## Platform requirements

### Android

- Minimum SDK 24, compile/target SDK 36, arm64 only.
- BLE, nearby-device, camera, location, Wi-Fi, multicast, internet, and LAN cleartext access.
- Android controllers use the custom FlutterBluePlus GATT/BTP path implemented by the app infrastructure.
- A second Android phone can run the official Project CHIP Virtual Matter Device App as the commissionee.

### iOS

- Physical iPhone only; simulator builds are not valid evidence because the vendored Matter framework has no simulator slice.
- Deployment target 16.1.
- Runner and Matter Extension must share the configured App Group.
- The app needs Matter Allow Setup Payload, Bluetooth, Bonjour, Local Network, Camera, and Location declarations.
- Physical signing and provisioning are local maintainer configuration. The repository can verify `--no-codesign` builds only.

## Agent mode

Agent mode uses a Mac-hosted trusted-LAN WebSocket service and the JSON CLI implemented in [agent-device-testing.md](agent-device-testing.md). The phone connects outward to the Mac. The CLI binds its control surface to loopback and exposes status, waits, commands, screenshots, report pull, app restart, and session shutdown.

The app reads the Mac endpoint from the compile-time `AGENT_WS_URL` define. Launch it with the explicit controller ID and the endpoint printed by `serve`:

```bash
fvm dart run tool/device_test_app.dart run \
  --device <device-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

Use the repository Skill at [repository Skill](../.agents/skills/flutter-matter-device-test/SKILL.md) for mandatory device selection, prompt routing, sensitive `--args-file` handling, and evidence collection.

## Local commands

```bash
cd device_test_app
fvm flutter pub get
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
```

Official runs should use the repository wrapper so commit metadata is injected:

```bash
fvm dart run tool/device_test_app.dart check
fvm dart run tool/device_test_app.dart build-apk
fvm dart run tool/device_test_app.dart build-ios
fvm dart run tool/device_test_app.dart run --device <device-id>
```

The wrapper requires a clean tracked worktree and injects `PLUGIN_COMMIT` and `TEST_APP_COMMIT`. A report whose plugin commit does not match the PR head is not valid evidence.

## Troubleshooting

- **Bridge does not connect:** confirm `serve` is running, the app has the printed WebSocket endpoint, the Mac and phone are on the same trusted LAN, and the network permits the connection.
- **No commissionee discovered:** enable Bluetooth, confirm commissionee pairing mode, verify the setup payload, and keep the phones on a non-isolated network.
- **Commissioning fails:** verify the setup code and network credentials without recording them, then stop and preserve the failed result rather than retrying a P0 in the same Run.
- **Report unavailable:** ensure the run was a completed `full` run and all required P0 tests have a valid result.
- **Wrong commit in report:** rebuild from the PR head with the wrapper, install the new app, and start a fresh Run.
- **Secrets or device identifiers are visible:** do not attach the report. Purge the invalid copy, correct the source, regenerate from app state, and re-review the output.
