# flutter_matter device test app

Dedicated Android and physical-iOS validation app for `flutter_matter`. It is not published with the plugin and is not part of the required Dart CI gate.

Every Run uses a Matter commissionee. The app passes the raw onboarding payload to the Matter SDK, which performs discovery and commissioning. A commissioning failure is preserved and is not retried in the same Run.

## Profiles and execution

| Profile | Contents | Role |
| --- | --- | --- |
| `quick` | Build/install, commissioning, operational connection, OnOff invoke | Developer iteration |
| `full` | All 8 fixed tests | Formal PR and release evidence |

Only a completed `full` Run produces formal evidence. See [Device Test Report Contract](../doc/device-test-report.md) for the fixed IDs, timeouts, schema v4 fields, and result rules.

A P0 failure or P0 `not_run` blocks later P0 work and ends the Run. Dependent cases are recorded as `not_run` with a reason. P1 failures are recorded without blocking the remaining sequence. No P0 failure is retried in the same Run.

`app_restart` rebuilds the controller runtime from persisted controller credentials and reconnects without recommissioning. It is a test case, not a resumable Run.

## Setup and lifecycle

Provide only:

- Run mode: `quick` or `full`.
- QR setup payload or manual setup code.
- Target Wi-Fi SSID.
- Wi-Fi password, or an empty value for an open network.

The app parses vendor and product identity from the payload. Before persisting new secrets, it removes stale Run state, purges old provisioning secrets and orphaned keys, and resets controller identities for the current platform. Cleanup failure blocks the Run.

The app then supplies the raw onboarding payload to the Matter SDK, executes the selected profile, and records terminal results. Runs are one-shot: interrupted Runs are discarded and never resumed. A completed `full` Run writes JSON and Markdown from the same result object.

## Application structure

- **Domain:** fixed test catalog, priorities, outcomes, and report model.
- **Application:** `RunCoordinator`, profiles, cases, prompts, failure policy, and one-shot lifecycle.
- **Infrastructure:** Matter controller and certificate services, SDK-managed commissioning, secure storage, platform information, report files, and sharing.
- **Presentation:** setup, runner, prompt, result, and cleanup screens.

The UI and Agent bridge observe the same coordinator state and event streams. Widgets do not call native APIs directly.

## Local checks

```sh
cd device_test_app
fvm flutter pub get
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
```

Official builds run from the repository root so commit metadata is injected:

```sh
fvm dart run tool/device_test_app.dart check
fvm dart run tool/device_test_app.dart build-apk
fvm dart run tool/device_test_app.dart build-ios
fvm dart run tool/device_test_app.dart run --device <device-id>
```

The wrapper requires a clean tracked worktree and injects `PLUGIN_COMMIT` and `TEST_APP_COMMIT`.

## Agent mode

Agent mode uses a Mac-hosted trusted-LAN WebSocket service and JSON CLI. The phone connects outward to the Mac; the CLI control server stays on loopback.

From the repository root, launch the app with the endpoint printed by `serve`:

```sh
fvm dart run tool/device_test_agent.dart serve --device <device-id> --port 8765

fvm dart run tool/device_test_app.dart run \
  --device <device-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

Agent-driven validation must use `$flutter-matter-device-test`, ask the user to choose when multiple phones are connected, pass `start_run` material through a transient `--args-file`, and never print or commit that file.

See [Agent-Driven Device Testing](../doc/agent-device-testing.md) for protocol, commands, prompts, artifacts, and failure handling.

## Requirements

- Android: physical device, ADB access, local-network connectivity, and host-app permissions from [Getting started](../doc/getting-started.md). The app uses `minSdk 24`, `compileSdk 36`, and arm64.
- iOS: physical iPhone, development signing, Matter Extension, matching App Group, and the required Bonjour, Bluetooth, and local-network declarations. Simulator builds are invalid evidence.
- Commissionee: Matter On/Off device with NodeLabel support and an open commissioning window.
- Network: the controller can reach the target Wi-Fi network for provisioning and CASE.

When no physical commissionee is available, use the bundled Android virtual device as described in [Device Validation](../doc/device-validation.md).

## Cleanup and secrets

Every commissioned Run adds one fabric to the commissionee. The post-Run **Commissionee cleanup** card purges the Run's stored secrets and records operator confirmation; it does not reset or modify the commissionee.

Factory-reset the commissionee or remove the test fabric before the next clean cycle. A failed or interrupted Run can also leave a fabric behind.

Setup codes, onboarding payloads, Wi-Fi credentials, controller private keys, and certificates stay in platform secure storage. They are excluded from reports, logs, screenshots, Agent state, and event transcripts. The separate Wi-Fi credential cache is removed only by its explicit clear action. On iOS, uninstalling the app is not a purge because Keychain items can survive.

## Troubleshooting

- **Bridge does not connect:** verify `serve`, the `AGENT_WS_URL` endpoint, the trusted LAN, and firewall access.
- **No commissionee found:** confirm an open commissioning window and SDK-visible discovery. For the Android VDA, follow the restart quirk in [Device Validation](../doc/device-validation.md).
- **Commissioning fails:** preserve the failure and stop. Do not retry commissioning in the same Run.
- **Stale report:** rebuild from the PR head, reinstall, and start a new Run.
- **Sensitive output found:** do not attach it. Purge the invalid evidence, correct the source, and regenerate the report.

## Evidence hygiene

Never put setup codes, onboarding payloads, Wi-Fi credentials, full UDIDs, serial numbers, certificates, private keys, or raw logs in reports or pull-request text. Hardware-in-the-loop CI is intentionally out of scope. Attach completed reports manually and verify that the report commit matches the pull-request head.
