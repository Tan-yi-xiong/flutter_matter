---
name: flutter-matter-device-test
description: Execute flutter_matter device validation through the dedicated test app's Agent bridge and JSON CLI. Use when asked to run quick or full physical-device tests, drive the test app, or collect sanitized PR evidence. Requires explicit user device selection.
---

# Flutter Matter Device Test

Run flutter_matter device validation without guessing which phone or commissionee to use.

## Hard Rules

1. Never auto-select a controller. Run `devices` and inspect the candidates first.
2. When multiple phones are connected, require an interactive user choice before starting `serve`. Use the native question/selection UI when available.
3. Each user-facing choice must show `platform`, `model`, `os_version`, and `short_id`. Do not display the full device ID in the choice label.
4. Pass the selected candidate's full `id` to `serve --device`. Never omit `--device`.
5. Prefer a real Matter On/Off device as the commissionee.
6. If no real Matter device is available, ask a separate interactive question to select an Android device for the virtual commissionee.
7. The virtual commissionee must be a distinct Android device from the controller. The controller may be Android or physical iOS.
8. Never use the first candidate, the only candidate, a previous selection, or a remembered ID as an implicit default when a user choice is required.
9. Never retry a failed P0 test to manufacture a passing result.
10. Do not put device IDs, UDIDs, SSIDs, passwords, setup codes, onboarding payloads, certificates, or private keys in reports or PR text.

## Preconditions

- Work from the `flutter_matter` repository root.
- Use `fvm dart` and `fvm flutter` when FVM is available.
- The dedicated device-test app is built and installed on the selected controller.
- A real Matter commissionee is prepared, or a second Android phone is available as the virtual commissionee.
- The Mac and phones are on the same trusted private LAN.
- The app's `AgentBridgeClient` points at the `serve` WebSocket endpoint.

## Step 1: Discover Devices

```bash
fvm dart run tool/device_test_agent.dart devices
```

Read the JSON result. Treat `device_selection_required: true` as a workflow invariant.

If at least two controller candidates exist, present an interactive choice. Example options:

- `Android / Essential PH-1 / Android 12 / ph1.lan:5555`
- `Android / Xiaomi Mi 10 / Android 13 / 192.16...5555`
- `iOS / iPhone 16 Pro / iOS 27.2 / 96E5E2...F8AB`

Use the `short_id` only for display. Keep the full `id` in your own state for the next command.

If a candidate is `usable: false`, explain its state and do not start a session with it.

## Step 2: Select the Commissionee

### Real Matter Device

Ask the operator which physical On/Off device will be used. The operator must be able to change its state physically, through a vendor app, or through a commissionee UI.

### Virtual Commissionee

If no real Matter device is available, ask a second interactive question:

> Select the distinct Android phone that will run the virtual Matter commissionee. It cannot be the same device as the controller.

Show the same `platform / model / os_version / short_id` fields. Never reuse the controller selection automatically.

For either commissionee type, verify that its Matter setup code is available to the controller workflow, but do not paste the setup code into logs or reports.

## Step 3: Start the Host Session

```bash
fvm dart run tool/device_test_agent.dart serve --device <selected-controller-id>
```

Start `serve` as a long-lived process. It prints one JSON object with:

- `websocket_endpoint`
- `selected_device`
- `control_port`
- `artifact_directory`

If it returns `session_already_running`, run `status`. Reuse only the same explicitly selected controller; otherwise stop the old session first.

If it returns `device_selection_required` or `device_not_found`, return to the device-choice step. Do not infer a device.

## Step 4: Wait for the App Bridge

```bash
fvm dart run tool/device_test_agent.dart wait --for connected --timeout-seconds 120
```

A socket alone is not enough. Wait for `app_connected: true` after the app sends `hello`.

Inspect `status` if the wait times out. Common fixes:

- Launch the test app on the selected controller.
- Confirm the app is configured with the printed `websocket_endpoint`.
- Confirm the Mac and phone share the private LAN.
- Restart the app with `restart-app` and wait again.

Do not switch the selected device without asking the user.

## Step 5: Start the Run

Use a stable command ID and reuse the same ID only when retrying the same logical command after a transport failure.

Quick run:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-json '{"mode":"quick"}' \
  --command-id <stable-quick-command-id> \
  --timeout-seconds 1200
```

Full run:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-json '{"mode":"full"}' \
  --command-id <stable-full-command-id> \
  --timeout-seconds 3600
```

A formal PR report requires `mode: full`. A quick run is development feedback and is not formal acceptance evidence.

## Step 6: Process Prompts

Poll or wait for meaningful conditions:

```bash
fvm dart run tool/device_test_agent.dart status
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_agent_android --timeout-seconds 600
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_human --timeout-seconds 600
```

Read the latest state and prompt.

### `agent_android` Prompt

The prompt applies to the Android controller. Use the installed mobile MCP/Android automation capability to inspect the controller screen and perform the requested system action, for example accepting a Bluetooth or local-network permission.

Before acting:

1. Verify the mobile MCP target matches the selected controller ID.
2. Perform the smallest requested action.
3. Re-read the test-app state or event stream.
4. Report the observed result, not merely that a tap was sent.

Do not use mobile MCP to operate physical Matter state changes or iOS system surfaces.

### `human` Prompt

Pause and ask the operator to perform the physical or iOS action. State the test ID and exact requested action. Wait for the operator's confirmation and verify the app moved out of `waiting_for_human`.

Do not claim a human action succeeded until the app reports the next semantic state or the operator confirms it.

## Step 7: Verify Progress and Capture Evidence

Use structured state first:

```bash
fvm dart run tool/device_test_agent.dart wait --for state --value running --timeout-seconds 1800
fvm dart run tool/device_test_agent.dart wait --for state --value passed --timeout-seconds 1800
```

Use a screenshot only when visual confirmation is needed:

```bash
fvm dart run tool/device_test_agent.dart screenshot \
  --output build/device-test-agent/screenshots/<test-id>.png
```

Do not inspect or include raw provisioning credentials in screenshots.

## Step 8: Pull the Report

For a formal full run:

```bash
fvm dart run tool/device_test_agent.dart report \
  --output-dir build/device-test-agent/reports/<run-id>
```

The command writes and prints:

- `device-test-report.json`
- `device-test-report.md`
- `plugin_commit_matches_head`
- the report summary

Verify:

1. `plugin_commit` equals `git rev-parse HEAD` for the tested PR.
2. All P0 test IDs are `passed`.
3. Non-P0 statuses and `not_run` reasons are reviewed.
4. The Markdown and JSON describe the same run.
5. The report contains no device identifiers or provisioning secrets.

Attach the JSON and Markdown to the PR or link them according to the repository's device-validation policy.

## No-P0-Retry Policy

A P0 `failed`, error, timeout, or crash is evidence. Do not rerun that P0 merely to get a green result.

You may retry a command when the failure is clearly a transport failure and the app never executed it. Reuse the same command ID for that transport retry. If the app executed the test and reported `failed`, preserve the report and report the failure to the user.

P1 and P2 results may be `not_run` with a concrete reason. P2 failures require maintainer risk acceptance.

## Step 9: Purge Reminder

After collecting evidence, remind the user to clean up:

- Remove the test fabric from the controller.
- Factory-reset or recommission the real commissionee as appropriate.
- Remove credentials and app data from the virtual commissionee.
- Clear test-only Wi-Fi or Thread credentials.
- Stop the host session if it is no longer needed:

```bash
fvm dart run tool/device_test_agent.dart stop
```

Do not execute destructive purge steps without user confirmation.

## Error Handling

| Error | Agent action |
| --- | --- |
| `device_selection_required` | Show candidates and ask the user. Never choose automatically. |
| `device_not_found` | Re-run `devices`; do not reuse a stale ID. |
| `session_already_running` | Inspect `status`; stop only after confirming the old session is no longer needed. |
| `app_disconnected` | Use `restart-app`, then wait for `connected`. Reuse the same command ID only when retrying the same unexecuted command. |
| `command_in_progress` | Wait for the existing command outcome before sending another. |
| `command_timeout` | Inspect status/events. Do not send a different command ID for the same logical test. |
| `plugin_commit_mismatch` | Rebuild/reinstall from the PR head and rerun; do not attach the report. |
| `report_sensitive_data` | Ask the app owner to remove the field/value and regenerate the report. |
| `wait_timeout` | Inspect `status`, screenshot, and app logs. Do not silently change devices. |

## Completion Checklist

- Controller was explicitly chosen by the user when multiple devices were connected.
- Virtual commissionee, when used, was chosen separately and is distinct.
- `serve` used the explicit controller ID.
- The app bridge connected and reported the expected controller metadata.
- The run used a stable command ID and the required mode.
- Agent Android prompts were verified through state, not assumed from a tap.
- Human prompts were explicitly handed to the operator.
- The full report matches the PR head and has a clean sanitization confirmation.
- No P0 test was retried to hide a failure.
- The user received the fabric, commissionee, credential, and app-data purge reminder.
