# Agent-Driven Device Testing

This document defines the operational interface between the flutter_matter device-test app, a Mac-hosted CLI, and an Agent. The app owns the declarative Matter runner and state projection; the host owns discovery, explicit controller selection, transport, command serialization, and report retrieval.

## Goals

- Let an Agent observe semantic test state without taking a screenshot on every step.
- Let the Agent send one idempotent command at a time to the test app.
- Keep the app as the WebSocket client so Android and physical iOS controllers can connect to a Mac-hosted server.
- Expose every operation through a JSON CLI that an Agent can call from a shell.
- Keep all evidence free of device identifiers, provisioning secrets, certificates, private keys, and raw logs.
- Use Wi-Fi/IP commissioning with real Matter hardware for every device run; do not run BLE discovery/commissioning or submit virtual-device evidence.

## Topology

```text
Agent shell
  |
  | JSON CLI
  v
tool/device_test_agent.dart
  |                                  loopback only
  +---- control HTTP server <------ status, wait, command, stop
  |
  +---- LAN WebSocket server -------- device_test_app AgentBridgeClient
                                      |
                                      +---- RunCoordinator and test cases
                                      +---- semantic state and events
                                      +---- prompt projection
                                      +---- screenshot and report payloads
```

`serve` is the long-running host process. Other CLI commands use the loopback-only control HTTP server created by that process. The test app connects outward to the LAN WebSocket endpoint and does not expose an inbound HTTP server. This keeps behavior consistent for Android and physical iOS.

The WebSocket deliberately does not use TLS or authentication. Use it only on a trusted private development LAN, and never expose the port to the public internet.

## Component boundaries

| Component | Responsibility |
| --- | --- |
| [`protocol.dart`](../device_test_app/lib/src/agent/protocol.dart) | Protocol v1 envelopes, typed payload models, validation, and opaque IDs. |
| [`agent_bridge_client.dart`](../device_test_app/lib/src/agent/agent_bridge_client.dart) | Reconnect loop, sequence generation, command deduplication, serial command execution, and artifact delivery. |
| [`run_coordinator.dart`](../device_test_app/lib/src/application/run_coordinator.dart) | Fixed profile execution, prompt handling, failure policy, persistence, and formal report construction. |
| [`device_test_app_controller.dart`](../device_test_app/lib/src/app/device_test_app_controller.dart) | UI state projection, prompt broker integration, report validation, sharing, resume, and purge. |
| [`device_test_agent.dart`](../tool/device_test_agent.dart) | Device discovery, mandatory selection, LAN WebSocket server, loopback control server, platform restart and screenshot helpers, and report persistence. |
| [`SKILL.md`](../.agents/skills/flutter-matter-device-test/SKILL.md) | Mandatory Agent workflow, user-selection rules, prompt routing, evidence rules, and cleanup. |

The app bridge is UI-independent. The app owns command handling for the runner and projects the same coordinator state used by the visible UI.

## Protocol v1

Every message is a UTF-8 JSON object with this envelope:

```json
{
  "protocol": "flutter_matter.device_test_agent",
  "version": 1,
  "type": "state",
  "sequence": 7,
  "message_id": "message-...",
  "sent_at": "2026-11-11T12:00:00.000Z",
  "command_id": "command-...",
  "payload": {}
}
```

`command_id` is present only when a message belongs to a command exchange. The protocol name and version are mandatory and checked by both sides.

| Type | Direction | Purpose |
| --- | --- | --- |
| `hello` | App to host | App identity, controller metadata, plugin commit, capabilities, and app instance ID. |
| `state` | App to host | Semantic runner phase, mode, counters, current test, prompt, and sanitized details. |
| `event` | App to host | Monotonic progress or failure information. |
| `command` | Host to app | A named command with JSON arguments and an idempotency key. |
| `command_result` | App to host | Terminal command status and sanitized result data. |
| `screenshot` | App to host | Base64 image bytes correlated with a command. |
| `report` | App to host | Sanitized schema v2 JSON and the matching Markdown summary. |
| `error` | Both | Protocol or command failure that does not necessarily close the socket. |

### Sequence rules

- Each sender increments `sequence` for every transmitted message.
- The host rejects a non-increasing sequence within one WebSocket connection.
- The app continues its sequence across reconnects.
- `hello.instance_id` identifies one app process. A new app process may reset to sequence one; the host resets its acceptance baseline when the instance ID changes.
- The app records the last host sequence per connection. A new socket resets that host-input baseline because the CLI process may have restarted.

### Command idempotency

Reuse a command ID only when retrying the same logical operation. The app keeps a bounded cache of terminal outcomes. A duplicate command ID does not execute the handler again; the app resends cached artifacts and a `command_result` with status `duplicate`.

The host allows one outstanding command per controller session. The app executes received commands serially even if a non-conforming host sends more than one.

### Reconnect behavior

`AgentBridgeClient`:

- Reconnects with capped exponential backoff.
- Resends `hello` and the latest semantic state after each reconnect.
- Buffers bounded state and event messages while disconnected and drops the oldest messages if the buffer limit is exceeded.
- Reports `stopped`, `connecting`, `connected`, or `waitingToReconnect`.

If the socket closes while a command is waiting, the command fails with `app_disconnected`. The Agent may retry the same command ID after the app reconnects.

## Device discovery and controller selection

`devices` discovers:

- Android devices through `adb devices -l` and `adb shell getprop`.
- iOS devices through `xcrun devicectl list devices --json-output`.
- iOS fallback devices through `idevice_id` and `ideviceinfo` when CoreDevice returns no usable candidate.

Each public candidate contains `id`, `short_id`, `platform`, `model`, `os_version`, `name`, `state`, `connection`, and `usable`. Public JSON does not include the internal iOS UDID used by screenshot tooling.

A qualified real Matter On/Off device is required for formal acceptance. It must already be connected to the same trusted Wi-Fi/LAN as the controller and in an open commissioning window. The Android Virtual Matter Device App path is retired; the Agent must not select or operate a virtual commissionee in any Run.

The host CLI never selects a controller by default:

- `devices` only lists candidates.
- `serve` always requires an explicit `--device`.
- A missing selector returns `device_selection_required` with all candidates.
- A selector may be an exact ID, a unique exact name, or a unique ID prefix.
- An ambiguous selector returns the matching candidates.
- An unavailable selected device returns `device_unavailable`.

When more than one phone is connected, the Agent must show an interactive user prompt with `platform`, `model`, `os_version`, and `short_id`, then pass the selected full ID to `serve --device`. The full ID is retained for the command but is not shown as the choice label. Never choose the first, only, previous, or remembered candidate automatically.

The Agent must not choose or operate a virtual commissionee in any Run, including quick iteration. If the operator cannot provide real Matter hardware, stop before starting any device Run and report that validation is blocked.

## CLI commands

Run commands from the repository root.

| Command | Required input | Result |
| --- | --- | --- |
| `devices` | None | Lists usable and unusable candidates without selecting one. |
| `serve` | Explicit `--device` | Starts the LAN WebSocket server, loopback control server, and one controller session. |
| `status` | Active session | Returns connection state, latest app state, prompt, and selected public device metadata. |
| `wait` | `--for connected` or `--for state --value <state>` | Blocks until the condition or timeout. |
| `command` | `--name`, one of `--args-json` or `--args-file`, `--command-id` | Sends one idempotent runner command and returns its terminal result. |
| `screenshot` | Optional `--output` | Captures an app screenshot, with platform fallback if disconnected. |
| `report` | Optional `--output-dir` | Pulls and validates report JSON and Markdown. |
| `restart-app` | Active session or explicit `--device` | Restarts the selected controller app. |
| `stop` | Active session | Stops the host session. |

```bash
fvm dart run tool/device_test_agent.dart devices
```

```bash
fvm dart run tool/device_test_agent.dart serve \
  --device <explicit-id> \
  --port 8765
```

`serve` prints one startup JSON object with `websocket_endpoint`, `selected_device`, `control_port`, and `artifact_directory`, then remains running. Use a fixed WebSocket port when the installed app is built with a stable endpoint.

Build, install, and launch the app with the printed endpoint and the same explicit controller ID:

```bash
fvm dart run tool/device_test_app.dart run \
  --device <explicit-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

The wrapper injects the current Git commit metadata. The app reads `AGENT_WS_URL` at compile time, connects outward to that endpoint, and reconnects without restarting the app.

```bash
fvm dart run tool/device_test_agent.dart status
fvm dart run tool/device_test_agent.dart wait --for connected --timeout-seconds 120
fvm dart run tool/device_test_agent.dart wait --for state --value running --timeout-seconds 600
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_agent_android --timeout-seconds 600
```

Create the Run argument file under the ignored build directory. It contains provisioning material, so never print the file, paste its contents into chat, or commit it.

```bash
mkdir -p build/device-test-agent
chmod 700 build/device-test-agent
```

Example structure for a real Wi-Fi/IP commissionee:

```json
{
  "mode": "quick",
  "commissionee_type": "real",
  "model": "<commissionee-model>",
  "firmware": "<firmware-version>",
  "commissioning_transport": "ip",
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

For formal evidence, keep `"commissionee_type": "real"`, `"commissioning_transport": "ip"`, and `"network_transport": "wifi"`. Thread is outside the current formal acceptance contract. When `state_change_method` is `other`, include non-empty `state_change_notes`.

Start a run with a stable command ID and the argument file:

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-file build/device-test-agent/run-args.json \
  --command-id <stable-id> \
  --timeout-seconds 1200
```

Use `"mode":"full"` and an appropriate timeout for formal evidence. Retain the file until the command outcome is terminal, then delete it without printing its contents. Every Run, including `quick`, must include `"commissioning_transport":"ip"` and `"network_transport":"wifi"`; it must not run BLE discovery or commissioning.

```bash
fvm dart run tool/device_test_agent.dart screenshot \
  --output build/device-test-agent/screenshots/current.png
```

The screenshot command requests an app screenshot through the bridge. If the app is disconnected or the bridge command fails, the host falls back to `adb exec-out screencap -p` or `idevicescreenshot`.

```bash
fvm dart run tool/device_test_agent.dart report \
  --output-dir build/device-test-agent/reports/<run-id>
```

The command verifies the report and writes `device-test-report.json` and `device-test-report.md` under the requested directory.

```bash
fvm dart run tool/device_test_agent.dart restart-app
fvm dart run tool/device_test_agent.dart stop
```

`restart-app` uses the active session's selected device by default and requires `--device` without an active session. Android uses an ADB force-stop and launcher start; iOS uses `xcrun devicectl device process launch --device <id> --terminate-existing <bundle-id>`.

## Command payload contract

A command payload contains:

- `name`: the runner command name.
- `arguments`: a JSON object, for example `{"mode":"full"}`.

The envelope supplies the required non-empty `command_id`. A command result contains `status` (`completed`, `failed`, or `duplicate`), `data`, and optional `error_code` and `error_message`. Artifacts are delivered as separate `screenshot` and `report` messages before the terminal `command_result`.

## Command contract

The app routes the following commands. Prompt commands require the current `prompt_id` from semantic state so a stale decision cannot resolve a later prompt.

| Name | Arguments | Meaning |
| --- | --- | --- |
| `start_run` | Full setup object with `mode` | Validate and start a `quick` or `full` Run. |
| `stop_run` | `{}` | Stop the current Run without manufacturing a passing report. |
| `resume_run` | `{}` | Resume the persisted unfinished Run. |
| `purge_secrets` | `{}` | Purge stored setup and network secrets after the Run is no longer active. |
| `confirm_prompt` | `{"prompt_id":"<id>"}` | Confirm the referenced active prompt after the requested action was verified. |
| `skip_prompt` | `{"prompt_id":"<id>","reason":"<reason>"}` | Skip the referenced prompt when skipping is allowed. |
| `fail_prompt` | `{"prompt_id":"<id>","reason":"<reason>"}` | Fail the referenced active test with an operator-provided reason. |
| `screenshot` | `{"label":"<optional>"}` | Return an app screenshot payload. |
| `report` | `{"run_id":"<optional>"}` | Return the validated sanitized report payload when ready. |

Requiring `setup_code`, Wi-Fi credentials, or Thread material in `start_run` is deliberate: it keeps the Agent workflow deterministic. Use `--args-file`, never `--args-json`, for that command. Secret values are transient command input and must not appear in state, events, command results, reports, screenshots, logs, or chat.

Every command must preserve command-ID idempotency and one-outstanding-command semantics. The repository Skill identifies the current prompt from semantic state and resolves it only after verifying the requested action.

## Hello and state payloads

`hello` advertises reviewer-safe app identity:

- `instance_id`, `app_name`, `app_version`, `app_build`, `app_commit`
- `plugin_commit`, `controller_platform`, `device_model`, `os_version`
- `capabilities`, including `state`, `event`, `command`, `screenshot`, `report`, `start_run`, `resume_run`, prompt commands, and `purge_secrets`

It must not contain serial numbers, UDIDs, BLE addresses, SSIDs, passwords, setup codes, onboarding payloads, certificates, or private keys.

`state` contains:

| Field | Meaning |
| --- | --- |
| `run_id` | Opaque current run identifier. |
| `status` | Semantic runner phase. |
| `mode` | `none`, `quick`, or `full`. |
| `current_test_id` | Current fixed test ID when applicable. |
| `completed_tests` / `total_tests` | Monotonic progress counters. |
| `message` | Short reviewer-safe status text. |
| `prompt` | Current actionable prompt, if any. |
| `details` | Sanitized, versioned context for diagnostics. |

A prompt contains `prompt_id`, `channel`, `title`, `instructions`, optional `action` and `test_id`, `confirm_label`, `can_skip`, and `skip_requires_reason`.

## Semantic state and prompts

Typical state values are `idle`, `running`, `waiting_for_app`, `waiting_for_agent_android`, `waiting_for_human`, `passed`, `failed`, `not_run`, and `stopped`. State includes run ID, mode, current test ID, completed and total counts, and sanitized details.

A prompt with channel `agent_android` applies only to Android system or permission UI on the selected controller. The Agent must verify its mobile automation target matches the selected controller, perform the smallest requested action, and re-read app state before reporting success.

A prompt with channel `human` requires the Agent to pause and ask the operator. This covers physical Matter hardware, commissionee state changes, and physical iOS system surfaces. The Agent must not claim success until app state changes or the operator explicitly confirms completion.

State, events, and prompts must not contain raw logs or provisioning secrets.

## Agent loop

The repository Skill enforces this sequence:

1. Run `devices` and inspect every candidate.
2. Ask the user to select the controller; never auto-select.
3. Confirm the operator has prepared the selected real Matter device on the same trusted Wi-Fi/LAN with its commissioning window open.
4. Start `serve` with the explicit controller ID.
5. Launch or connect the app and wait for the bridge connection.
6. Start `quick` for iteration or `full` for formal evidence with a stable command ID.
7. Resolve `agent_android` prompts on the selected Android controller only.
8. Route `human` prompts to the operator and verify the semantic state transition.
9. Use structured status, state, and events first; use screenshots only when visual confirmation is needed.
10. Pull and verify the full report.
11. Preserve P0 failures; never retry a P0 in the same Run to obtain a green result.
12. Remind the operator to purge fabrics, credentials, commissionee data, and app secrets.

## Report verification

The host performs structural checks before writing report files:

- Envelope and report schema versions are supported.
- All 12 fixed test IDs occur exactly once.
- Test statuses and durations have valid types.
- Summary counts match the `tests` object.
- Overall result is consistent with P0 and failure rules.
- Formal evidence records a real commissionee, `commissioning_transport: ip`, and `network_transport: wifi`.
- `plugin_commit` matches the current repository HEAD.
- Test-app commit is a 40-character lowercase Git SHA.
- Sanitization is explicitly confirmed.
- Forbidden keys and obvious sensitive values are rejected.

The app performs complete JSON Schema validation and generates Markdown from the same result object. A human must review the final report before attaching it to a PR. Report files must never contain full UDIDs, serial numbers, SSIDs, passwords, setup codes, certificates, private keys, or raw logs.

## Runtime files

The host stores its local session descriptor at:

```text
.dart_tool/device_test_agent/session.json
```

It contains the process ID, loopback control port, LAN WebSocket endpoint, selected public device metadata, and artifact directory. It is ignored operational state.

Default screenshots and reports are written under:

```text
build/device-test-agent/
```

## Non-goals

- TLS, authentication, or public-network exposure.
- An MCP server.
- Automatic device selection.
- Automated control of physical Matter hardware.
- Automated iOS system-dialog interaction.
- Real-device CI or automatic evidence upload.
- BLE discovery or commissioning in formal acceptance.
- Submitting a virtual-commissionee report as formal evidence.

## Verification coverage

Agent bridge tests use fake WebSocket channels to verify hello-first ordering, latest-state replay, monotonic sequence across reconnect, command-ID deduplication, and artifact ordering before command results.

Host CLI tests use fake device candidates to verify ADB parsing, mandatory explicit selection, exact and ambiguous selector handling, and removal of the internal iOS UDID from public JSON.

These tests validate protocol and workflow mechanics only. They are not a substitute for physical-device validation.
