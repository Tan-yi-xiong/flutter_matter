---
name: flutter-matter-device-test
description: Execute flutter_matter device validation through the dedicated test app's Agent bridge and JSON CLI. Use when asked to run quick or full physical-device tests, drive the test app, or collect sanitized PR evidence. Requires explicit user device selection.
---

# Flutter Matter Device Test

Run `flutter_matter` device validation without guessing which phone or commissionee to use. Prefer real Matter hardware. Use the official Android Virtual Matter Device App only as a controlled functional fallback.

## Hard rules

1. Work from the `flutter_matter` repository root and use `fvm dart` / `fvm flutter` when FVM is available.
2. Never auto-select a controller. Run `devices` and inspect candidates first.
3. When multiple phones are connected, show a native interactive user-choice prompt before starting `serve`. Never infer a choice from connection order, platform, model, installed packages, or previous use.
4. Show `platform`, `model`, `os_version`, and `short_id` in user choices. Do not display the full device ID in the label; retain the full ID privately for `serve`.
5. Always pass the selected candidate's full ID to `serve --device`.
6. Prefer a qualified real Matter On/Off commissionee.
7. If no real Matter device is available, ask a separate interactive question for the distinct Android phone that will run the official Project CHIP Virtual Matter Device App. It cannot be the controller.
8. Android and physical iOS controllers may test either real Matter hardware or the distinct Android virtual commissionee.
9. `quick` contains five iteration tests and is never formal evidence. Formal PR/release evidence requires a completed `full` run with all 13 tests.
10. Never retry a failed P0 test in the same Run to manufacture a passing result.
11. Do not put full UDIDs, serial numbers, SSIDs, passwords, setup codes, onboarding payloads, certificates, private keys, or raw logs in reports, screenshots, or PR text.
12. Use structured state first. Take a screenshot only when semantic state is insufficient for a decision.
13. Real-device CI is out of scope. Reports are manually attached to the PR and must match its head commit.

## Preconditions

- The dedicated device-test app is built and installed on the selected controller.
- A real Matter commissionee is prepared, or a second Android phone runs the official Project CHIP Virtual Matter Device App.
- The Mac and phones share a trusted private LAN that permits the WebSocket connection.
- The app is configured with the endpoint printed by `serve`.
- `adb` is available for Android devices; Xcode `devicectl` or libimobiledevice is available for iOS devices.

## Step 1: Discover devices

```bash
fvm dart run tool/device_test_agent.dart devices
```

Read the JSON result. Treat `device_selection_required: true` as a workflow invariant.

When multiple controller candidates exist, present an interactive choice using:

```text
platform / model / os_version / short_id
```

Examples:

- `Android / Essential PH-1 / Android 12 / ph1.lan:5555`
- `iOS / iPhone 16 Pro / iOS 27.2 / 96E5E2...F8AB`

Use `short_id` only for display. Keep the full ID in your own state for the next command. If a candidate is `usable: false`, explain its state and do not start a session with it.

## Step 2: Select the commissionee

### Real Matter device

Ask the operator which physical On/Off device will be used. The operator must be able to change its state physically, through a vendor app, or through the commissionee UI. Record the choice and fallback reason in the PR narrative without exposing provisioning secrets.

### Virtual commissionee

If no real Matter device is available, ask a second interactive question:

> Select the distinct Android phone that will run the virtual Matter commissionee. It cannot be the same device as the controller.

Show the same `platform / model / os_version / short_id` fields. Never reuse the controller selection automatically. Reject the selected controller if the user selects it and ask again.

For either commissionee type, verify that its setup payload is available to the controller workflow, but do not paste it into logs, screenshots, reports, or PR text.

## Step 3: Start the host session

```bash
fvm dart run tool/device_test_agent.dart serve \
  --device <selected-controller-id> \
  --port 8765
```

Start `serve` as a long-lived process. It prints one JSON object with:

- `websocket_endpoint`
- `selected_device`
- `control_port`
- `artifact_directory`

If it returns `session_already_running`, run `status`. Reuse only the same explicitly selected controller; otherwise ask the user before stopping the old session.

If it returns `device_selection_required` or `device_not_found`, return to the device-choice step. Do not infer a device.

## Step 4: Launch the app and wait for the bridge

Read `websocket_endpoint` from the `serve` startup JSON. Treat it as operational data, not as a provisioning secret. Build, install, and launch the app with the endpoint and explicit controller ID:

```bash
fvm dart run tool/device_test_app.dart run \
  --device <selected-controller-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

Run this as a long-lived development process. The wrapper injects the current Git commit metadata and the app reads `AGENT_WS_URL` at compile time. If the app is already installed with the same endpoint, launch it directly instead.

```bash
fvm dart run tool/device_test_agent.dart wait --for connected --timeout-seconds 120
```

A socket alone is not enough. Wait for `app_connected: true` after the app sends `hello`.

If the wait times out:

1. Confirm the app is running on the selected controller.
2. Confirm the installed build used the printed `websocket_endpoint`.
3. Confirm the Mac and phone share the trusted private LAN.
4. Run `restart-app`, then wait again.
5. Inspect `status` and report the failure.

Do not switch the selected device without asking the user again.

## Step 5: Start the run

Use a stable command ID and reuse the same ID only when retrying the same logical command after a transport failure. Because `start_run` includes provisioning material, put its arguments in a temporary JSON file under the ignored build directory. Never print the file, paste its contents into chat, or commit it.

```bash
mkdir -p build/device-test-agent
chmod 700 build/device-test-agent
```

The file must contain the full setup object. Use placeholders here and replace them only in the local file:

```json
{
  "mode": "quick",
  "commissionee_type": "real",
  "model": "<commissionee-model>",
  "firmware": "<firmware-version>",
  "network_transport": "wifi",
  "state_change_method": "physical_control",
  "setup_code": "<setup-code-or-qr-payload>",
  "wifi_ssid": "<ssid>",
  "wifi_password": "<password>",
  "clean_cycle": {
    "controller_clean": true,
    "commissionee_clean": true,
    "secrets_purged": true
  }
}
```

For a virtual commissionee, use `"commissionee_type":"virtual"`, include a non-empty `fallback_reason`, and set `"virtual_fallback_confirmed": true`. For Thread, use `"network_transport":"thread"` and `thread_operational_dataset`. For `"state_change_method":"other"`, include non-empty `state_change_notes`.

Quick iteration run:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-file build/device-test-agent/run-args.json \
  --command-id <stable-quick-command-id> \
  --timeout-seconds 1200
```

Formal evidence run: set `"mode":"full"` in the same local file and use a new stable command ID:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-file build/device-test-agent/run-args.json \
  --command-id <stable-full-command-id> \
  --timeout-seconds 3600
```

Only `mode: full` produces formal PR or release evidence. A quick run is development feedback and must not be attached as acceptance evidence. Keep the argument file until the terminal result is known; delete it afterward without printing its contents.

## Step 6: Process prompts

Poll or wait for meaningful conditions:

```bash
fvm dart run tool/device_test_agent.dart status
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_agent_android --timeout-seconds 600
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_human --timeout-seconds 600
```

Read the latest state and prompt.

### `agent_android` prompt

The prompt applies only to the selected Android controller. Use the installed mobile automation capability to inspect that controller screen and perform the smallest requested action, such as accepting a Bluetooth or local-network permission.

Before acting:

1. Verify the automation target matches the selected controller ID.
2. Perform the smallest requested action.
3. Re-read the test-app state or event stream.
4. Confirm the prompt only after the state or visible outcome proves the action succeeded.

```bash
fvm dart run tool/device_test_agent.dart command \
  --name confirm_prompt \
  --args-json '{"prompt_id":"<current-prompt-id>"}' \
  --command-id <stable-prompt-command-id>
```

Do not use mobile automation to operate physical Matter state changes or iOS system surfaces.

### `human` prompt

Pause and ask the operator to perform the physical Matter, commissionee, or physical iOS action. State the test ID and exact requested action. Wait for operator confirmation, then confirm the prompt and verify that app state moves out of `waiting_for_human`.

```bash
fvm dart run tool/device_test_agent.dart command \
  --name confirm_prompt \
  --args-json '{"prompt_id":"<current-prompt-id>"}' \
  --command-id <stable-prompt-command-id>
```

If the prompt allows skipping or must be failed, use `skip_prompt` or `fail_prompt` with the current `prompt_id` and a concrete reason. Do not claim a human action succeeded until the app reports the next semantic state or the operator explicitly confirms it.

### App restart checkpoint

When state becomes `waiting_for_app`, the `app_restart` case requires a controller app process restart. Use the host restart command or the selected device's mobile automation, wait for the bridge to reconnect, then resume the persisted Run:

```bash
fvm dart run tool/device_test_agent.dart restart-app
fvm dart run tool/device_test_agent.dart wait --for connected --timeout-seconds 120
fvm dart run tool/device_test_agent.dart command \
  --name resume_run \
  --command-id <stable-resume-command-id>
```

Verify that state leaves `waiting_for_app` and the interrupted test resumes at its saved checkpoint. Do not start a new Run.

## Step 7: Verify progress

Use structured state first:

```bash
fvm dart run tool/device_test_agent.dart wait --for state --value running --timeout-seconds 1800
fvm dart run tool/device_test_agent.dart wait --for state --value passed --timeout-seconds 1800
```

Use a screenshot only when semantic state is insufficient:

```bash
fvm dart run tool/device_test_agent.dart screenshot \
  --output build/device-test-agent/screenshots/<test-id>.png
```

Do not include provisioning credentials or raw logs in screenshots.

## Step 8: Pull and verify the report

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
2. The run mode is `full`.
3. All P0 test IDs are `passed`.
4. Non-P0 statuses and `not_run` reasons are reviewed.
5. The Markdown and JSON describe the same run.
6. Sanitization is confirmed.
7. The report contains no full device identifiers or provisioning secrets.

Attach the JSON and Markdown to the PR manually. If the commit does not match the PR head, rebuild from the PR head, reinstall, and start a fresh Run; do not attach the stale report.

## No-P0-retry policy

A P0 `failed`, error, timeout, or crash is evidence. Do not rerun that P0 merely to obtain a green result.

You may retry a command when the failure is clearly a transport failure and the app never executed it. Reuse the same command ID for that transport retry. If the app executed the test and reported `failed`, preserve the report and report the failure to the user.

P1 and P2 results may be `not_run` with a concrete reason. P2 failures require explicit maintainer risk acceptance.

## Step 9: Purge reminder

After collecting evidence, remind the user to clean up:

- Remove the test fabric from the controller.
- Factory-reset or recommission the real commissionee as appropriate.
- Remove credentials and app data from the virtual commissionee.
- Clear test-only Wi-Fi or Thread credentials.
- Purge app secrets through the command interface after the Run is no longer active:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name purge_secrets \
  --command-id <stable-purge-command-id>
```

- Stop the host session if it is no longer needed:

```bash
fvm dart run tool/device_test_agent.dart stop
```

Do not execute destructive purge steps without user confirmation.

## Error handling

| Error | Agent action |
| --- | --- |
| `device_selection_required` | Show candidates and ask the user. Never choose automatically. |
| `device_not_found` | Re-run `devices`; do not reuse a stale ID. |
| `device_unavailable` | Explain the state and ask the user to make the device usable or choose again. |
| `session_already_running` | Inspect `status`; ask before stopping the old session. |
| `app_disconnected` | Use `restart-app`, wait for `connected`, and retry only the same unexecuted command ID. |
| `command_in_progress` | Wait for the existing command outcome before sending another. |
| `command_timeout` | Inspect status, state, and events. Do not send a different command ID for the same logical test. |
| `args_file_*` | Correct the local argument file or path. Never print its contents; reuse the same command ID only for a retry of the same unexecuted command. |
| `invalid_arguments` | Re-read the `start_run` schema and correct the local argument file without exposing secrets in chat. |
| `report_not_ready` | Wait for the Report validation state to become valid, then retry `report`. |
| `screenshot_unavailable` | Use the host platform screenshot fallback and inspect the current state. |
| `plugin_commit_mismatch` | Rebuild/reinstall from the PR head and start a fresh Run; do not attach the report. |
| `report_sensitive_data` | Do not attach the report. Remove the invalid copy, correct the source, regenerate, and re-review. |
| `wait_timeout` | Inspect `status` and semantic state; use a screenshot only if needed. Do not silently change devices. |

## Completion checklist

- The controller was explicitly chosen by the user whenever multiple phones were connected.
- The virtual commissionee, when used, was selected separately and is distinct from the controller.
- `serve` used the explicit controller ID.
- The app bridge connected and reported the expected controller metadata.
- The run used a stable command ID, an `--args-file` input, and the required mode.
- The temporary Run argument file was deleted without printing its contents.
- Android prompts were handled only on the selected controller and verified through semantic state.
- Human prompts were explicitly handed to the operator.
- The formal report is from a `full` run and matches the PR head.
- Sanitization was verified and no P0 failure was retried to hide a result.
- The user received the fabric, commissionee, credential, and app-data purge reminder.
