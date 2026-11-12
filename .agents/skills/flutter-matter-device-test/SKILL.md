---
name: flutter-matter-device-test
description: Execute flutter_matter device validation through the dedicated test app's Agent bridge and JSON CLI. Use when asked to run quick or full physical-device tests, drive the test app, or collect sanitized PR evidence. Requires explicit user device selection.
---

# Flutter Matter Device Test

Run `flutter_matter` device validation without guessing which phone or commissionee to use. The device-test app is the authoritative runner for Matter commissionees and does not inspect device provenance. It discovers the commissionee concurrently over BLE and Wi-Fi/IP, uses the first matching transport, and records the actual transport in schema v3 evidence.

## Hard rules

1. Work from the `flutter_matter` repository root and use `fvm dart` / `fvm flutter` when FVM is available.
2. Never auto-select a controller. Run `devices` and inspect candidates first.
3. When multiple phones are connected, show a native interactive user-choice prompt before starting `serve`. Never infer a choice from connection order, platform, model, installed packages, or previous use.
4. Show `platform`, `model`, `os_version`, and `short_id` in user choices. Do not display the full device ID in the label; retain the full ID privately for `serve`.
5. Always pass the selected candidate's full ID to `serve --device`.
6. Use a Matter On/Off commissionee for every device Run. Do not infer or record device provenance.
7. Never select, force, or describe a commissioning transport in `start_run`. The app starts BLE and Wi-Fi/IP discovery concurrently and uses the first matching transport.
8. If commissioning fails on the selected transport, preserve the failure and stop the Run. Do not retry or fall back to the other transport in the same Run.
9. Do not send Thread commissioning material or Thread-specific setup fields.
10. `quick` contains five iteration tests and is never formal evidence. Formal PR/release evidence requires a completed `full` run with all 12 fixed tests.
11. Never retry a failed P0 test in the same Run to manufacture a passing result.
12. Do not put full UDIDs, serial numbers, SSIDs, passwords, setup codes, onboarding payloads, certificates, private keys, or raw logs in reports, screenshots, or PR text.
13. Use structured state first. Take a screenshot only when semantic state is insufficient for a decision.
14. Hardware-in-the-loop CI is out of scope. Reports are manually attached to the PR and must match its head commit.

## Preconditions

- The dedicated device-test app is built and installed on the selected controller.
- A Matter On/Off commissionee is available and in an open commissioning window after a factory reset.
- The commissionee supports BLE commissionable discovery, Wi-Fi/IP commissionable discovery, or both.
- The controller has connectivity to the target Wi-Fi network for provisioning and the CASE/control stage.
- The Mac and phones share a trusted private LAN that permits the WebSocket connection.
- The app is configured with the endpoint printed by `serve`.
- `adb` is available for Android devices; Xcode `devicectl` or libimobiledevice is available for iOS devices.

Do not run a host-side `_matterc._udp` preflight gate before the Run. A valid Run may be led by either BLE or Wi-Fi/IP discovery; absence of an mDNS advertisement alone does not block the Run.

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

Ask the operator which physical On/Off device will be used. The operator must be able to confirm that it is factory-reset and currently has an open commissioning window. Record the choice in the PR narrative without exposing provisioning secrets.

Do not paste the setup payload, mDNS instance names, hostnames, discriminators, BLE addresses, or any discovery identifiers into evidence.

## Step 3: Start the host session

```bash
fvm dart run tool/device_test_agent.dart serve \
  --device <selected-controller-id> \
  --port 8765
```

Start `serve` as a long-lived process. It prints one JSON object with `websocket_endpoint`, `selected_device`, `control_port`, and `artifact_directory`, then continues running.

## Step 4: Build or connect the app

Build and launch the app through the wrapper with the printed endpoint:

```bash
fvm dart run tool/device_test_app.dart run \
  --device <selected-controller-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

The wrapper injects the current Git commit metadata and the app reads `AGENT_WS_URL` at compile time. If the app is already installed with the same endpoint, launch it directly instead.

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

## Step 4A: Collect setup information interactively

Use Codex interactive prompts to collect every required setup decision. Do not infer setup data from chat history, command flags, connection order, or previous runs.

Ask for, at minimum:

1. Run mode: `quick` or `full`.
2. Setup code or QR setup payload for the selected commissionee.
3. Wi-Fi SSID.
4. Wi-Fi password. Treat an empty password as valid only for an open network.
5. Explicit confirmation that the selected commissionee is factory-reset and has an open commissioning window.

Never ask for or accept:

- Commissionee model or firmware.
- A state-change method or state-change notes.
- Commissioning transport.
- Network transport.
- Controller-clean status.
- Secrets-purged status.

When the answers arrive, immediately write them only into the transient `start_run` argument file. Do not repeat secret values in chat, logs, screenshots, reports, or PR text.

## Step 5: Start the run

Use a stable command ID and reuse the same ID only when retrying the same logical command after a transport failure. Because `start_run` includes provisioning material, put its arguments in a temporary JSON file under the ignored build directory. Never print the file, paste its contents into chat, or commit it.

```bash
mkdir -p build/device-test-agent
chmod 700 build/device-test-agent
```

Use exactly this minimal structure, replacing values only in the local file:

```json
{
  "mode": "quick",
  "setup_code": "<setup-code-or-qr-payload>",
  "wifi_ssid": "<ssid>",
  "wifi_password": "<password-or-empty-for-open-network>",
  "clean_cycle": {
    "commissionee_clean": true
  }
}
```

For formal evidence, set `"mode": "full"` in the same local file and use a new stable command ID. Only `mode`, `setup_code`, `wifi_ssid`, `wifi_password`, and `clean_cycle` are accepted. Any extra field must be rejected instead of silently ignored.

Quick iteration run:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-file build/device-test-agent/run-args.json \
  --command-id <stable-quick-command-id> \
  --timeout-seconds 1200
```

Formal evidence run:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-file build/device-test-agent/run-args.json \
  --command-id <stable-full-command-id> \
  --timeout-seconds 3600
```

Only `mode: full` produces formal PR or release evidence. Keep the argument file until the terminal result is known; delete it afterward without printing its contents.

Before the Run starts, the app automatically purges old run provisioning secrets and resets controller identities for the current platform. The user does not certify those cleanup steps. If automatic cleanup fails, the app must block the new Run before creating secrets or starting a test.

## Step 6: Process prompts

Poll or wait for meaningful conditions:

```bash
fvm dart run tool/device_test_agent.dart status
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_agent_android --timeout-seconds 600
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_human --timeout-seconds 600
```

Read the latest state and prompt.

### `agent_android` prompt

The prompt applies only to the selected Android controller. Use the installed mobile automation capability to inspect that controller screen and perform the smallest requested action, such as accepting a local-network permission.

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
3. The report schema version is `3`.
4. `vendor_id` and `product_id` are present, and `network_transport` is `wifi`.
5. `commissioning_transport` records the actual selected path, `ble` or `ip`.
6. All P0 test IDs are `passed`.
7. Non-P0 statuses and `not_run` reasons are reviewed.
8. The Markdown and JSON describe the same run.
9. Sanitization is confirmed.
10. The report contains no full device identifiers or provisioning secrets.

Attach the JSON and Markdown to the PR manually. If the commit does not match the PR head, rebuild from the PR head, reinstall, and start a fresh Run; do not attach the stale report.

## No-P0-retry and no-transport-fallback policy

A P0 `failed`, error, timeout, or crash is evidence. Do not rerun that P0 merely to obtain a green result.

After discovery selects a transport and commissioning fails, do not retry through BLE or Wi-Fi/IP in the same Run. Preserve the failure, report it to the user, and require a new Run only as an explicit new validation decision.

You may retry a command when the failure is clearly a transport failure and the app never executed it. Reuse the same command ID for that transport retry. If the app executed the test and reported `failed`, preserve the report and report the failure to the user.

P1 and P2 results may be `not_run` with a concrete reason. P2 failures require explicit maintainer risk acceptance.

## Step 9: Purge reminder

After collecting evidence, remind the user to clean up:

- Remove the test fabric from the controller.
- Factory-reset or recommission the commissionee as appropriate.
- Clear test-only Wi-Fi credentials through the app's explicit cache-clear action when they are no longer needed.
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
| `invalid_arguments` | Re-read the minimal `start_run` schema and correct the local argument file without exposing secrets in chat. |
| `cleanup_failed` | Do not start the Run. Preserve the local state and report the cleanup failure. |
| `commissioning_failed` | Preserve the failure. Do not retry through the other transport in the same Run. |
| `report_not_ready` | Wait for the Report validation state to become valid, then retry `report`. |
| `screenshot_unavailable` | Use the host platform screenshot fallback and inspect the current state. |
| `plugin_commit_mismatch` | Rebuild/reinstall from the PR head and start a fresh Run; do not attach the report. |
| `report_sensitive_data` | Do not attach the report. Remove the invalid copy, correct the source, regenerate, and re-review. |
| `wait_timeout` | Inspect `status` and semantic state; use a screenshot only if needed. Do not silently change devices. |

## Completion checklist

- The controller was explicitly chosen by the user whenever multiple phones were connected.
- The run used a Matter commissionee selected by the operator.
- The app performed concurrent BLE and Wi-Fi/IP discovery and selected the first matching transport.
- No commissioning failure was retried through the other transport in the same Run.
- Setup data was collected through Codex interactive prompts using only the minimal required fields.
- `serve` used the explicit controller ID.
- The app bridge connected and reported the expected controller metadata.
- The run used a stable command ID, an `--args-file` input, and the required mode.
- The temporary Run argument file was deleted without printing its contents.
- Automatic cleanup ran or a cleanup failure blocked the Run before persistence.
- Android prompts were handled only on the selected controller and verified through semantic state.
- Human prompts were explicitly handed to the operator.
- The formal report is schema v3, from a `full` run, and matches the PR head.
- Sanitization was verified and no P0 failure was retried to hide a result.
- The user received the fabric, commissionee, credential, and app-data purge reminder.
