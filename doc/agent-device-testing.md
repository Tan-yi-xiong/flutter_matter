# Agent-driven device testing

The Agent interface connects the device-test app to a Mac-hosted CLI. The app owns the Matter runner and report generation. The host owns device discovery, WebSocket transport, command serialization, and artifact retrieval.

This document describes the protocol and CLI contract. The mandatory operating sequence lives in the repository Skill, [`.agents/skills/flutter-matter-device-test/SKILL.md`](../.agents/skills/flutter-matter-device-test/SKILL.md).

## Topology

```text
Agent
  | JSON CLI
  v
tool/device_test_agent.dart
  | loopback control HTTP       | trusted-LAN WebSocket
  v                             v
CLI commands                 device_test_app
                                | RunCoordinator and cases
                                | SDK-managed commissioning
                                | sanitized state and reports
```

The phone connects outward to the Mac. The host's control server binds to loopback. The WebSocket uses no TLS or authentication, so use it only on a trusted private development LAN.

## Components

- `protocol.dart`: protocol v1 envelopes and typed payloads.
- `agent_bridge_client.dart`: reconnect, sequencing, deduplication, command serialization, and artifact delivery.
- `run_coordinator.dart`: profiles, cases, failures, state, and report construction.
- `device_test_agent.dart`: device discovery, server, CLI, screenshots, app restart, and report persistence.
- `SKILL.md`: user selection, prompt routing, evidence rules, and cleanup.

## Protocol v1

Every message is a UTF-8 JSON object:

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

`command_id` is present only for command exchanges.

| Type | Direction | Purpose |
| --- | --- | --- |
| `hello` | App to host | App/controller metadata, commits, capabilities, instance ID |
| `state` | App to host | Semantic phase, mode, progress, current test, prompt |
| `event` | App to host | Monotonic progress and failure events |
| `command` | Host to app | Named command with arguments and idempotency key |
| `command_result` | App to host | Terminal command status and safe result |
| `screenshot` | App to host | Base64 image correlated with a command |
| `report` | App to host | Sanitized schema v4 JSON and matching Markdown |
| `error` | Both | Protocol or command error |

Sequence rules:

- Each sender increments `sequence` for every message.
- The host rejects a non-increasing sequence on one connection.
- The app continues its sequence across reconnects.
- `hello.instance_id` identifies one app process.
- A host session has one explicitly selected controller and one outstanding command.

### Hello

`hello` contains app name/version/build/commit, plugin commit, public controller metadata, capabilities, and `instance_id`. It must not contain serial numbers, UDIDs, BLE addresses, SSIDs, passwords, setup codes, onboarding payloads, certificates, or private keys.

### State

`state` contains:

- `run_id` and `status`;
- `mode`: `none`, `quick`, or `full`;
- `current_test_id`;
- monotonic `completed_tests` / `total_tests`;
- short reviewer-safe `message`;
- optional `prompt` and sanitized `details`.

Typical status values are `idle`, `running`, `waiting_for_agent_android`, `waiting_for_human`, `passed`, `failed`, `not_run`, and `stopped`.

A prompt contains `prompt_id`, `channel`, `title`, `instructions`, optional `action` and `test_id`, `confirm_label`, `can_skip`, and `skip_requires_reason`.

## Device selection

`devices` lists usable and unusable candidates without selecting one.

When multiple controllers are connected, the Agent must ask which phone to use. It must not select from connection order, platform, or previous runs.

The selected controller ID is passed explicitly to `serve` and the app run command. Platform screenshots and mobile automation must target that exact controller.

## Setup input

Ask the user only for:

1. `mode`: `quick` or `full`.
2. `setup_code`: QR setup payload or manual setup code.
3. `wifi_ssid`.
4. `wifi_password`, or an empty string for open Wi-Fi.

Do not ask for commissionee model, firmware, state-change method, controller-clean state, secrets-purged state, or commissioning transport. The protocol rejects unsupported fields.

Write `start_run` input to a transient file under `build/device-test-agent/` with restrictive permissions. Never print the file, pass secrets through `--args-json`, paste values into chat, or commit the file.

```json
{
  "mode": "quick",
  "setup_code": "<setup-code-or-qr-payload>",
  "wifi_ssid": "<ssid>",
  "wifi_password": "<password-or-empty-for-open-network>"
}
```

Use `full` for formal evidence. Delete the file when the command reaches a terminal result.

## CLI

```sh
fvm dart run tool/device_test_agent.dart devices
```

Start a session with an explicit controller:

```sh
fvm dart run tool/device_test_agent.dart serve \
  --device <explicit-id> \
  --port 8765
```

`serve` prints one startup object with `websocket_endpoint`, `selected_device`, `control_port`, and `artifact_directory`, then stays running.

| Command | Purpose |
| --- | --- |
| `status` | Current connection, state, prompt, and public device metadata |
| `wait --for connected` | Wait for the app bridge |
| `wait --for state --value <state>` | Wait for a semantic state |
| `command --name <name> --args-file <path> --command-id <id>` | Send one idempotent runner command |
| `screenshot` | Capture the selected controller, with platform fallback |
| `report` | Pull and validate JSON plus Markdown |
| `restart-app` | Recover the controller app or bridge |
| `stop` | Stop the host session |

Build and launch the app with the printed endpoint and the same controller:

```sh
fvm dart run tool/device_test_app.dart run \
  --device <explicit-id> \
  -- --dart-define=AGENT_WS_URL=<websocket_endpoint>
```

The wrapper injects Git commit metadata. The app stores `AGENT_WS_URL` at compile time and reconnects to the host without restarting.

Useful waits:

```sh
fvm dart run tool/device_test_agent.dart wait --for connected --timeout-seconds 120
fvm dart run tool/device_test_agent.dart wait --for state --value running --timeout-seconds 600
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_agent_android --timeout-seconds 600
```

## Commands

A command payload contains `name` and an `arguments` object. The envelope supplies a non-empty `command_id`. Results contain `status` (`completed`, `failed`, or `duplicate`), `data`, and optional `error_code` and `error_message`.

Screenshots and reports arrive as separate artifact messages before the terminal `command_result`.

| Name | Arguments | Meaning |
| --- | --- | --- |
| `start_run` | Setup object above | Validate, clean, and start a Run |
| `stop_run` | `{}` | Stop without manufacturing a passing report |
| `purge_secrets` | `{}` | Purge stored Run secrets after the Run is inactive |
| `confirm_prompt` | `{"prompt_id":"<id>"}` | Confirm a verified active prompt |
| `skip_prompt` | `{"prompt_id":"<id>","reason":"..."}` | Skip when allowed |
| `fail_prompt` | `{"prompt_id":"<id>","reason":"..."}` | Fail the active test with a reason |
| `screenshot` | Optional `label` | Return a screenshot artifact |
| `report` | Optional `run_id` | Return the validated report when ready |

Prompt commands require the current `prompt_id`; a stale decision cannot resolve a later prompt. Keep one command outstanding and reuse the same command ID only when retrying the same unexecuted command.

## Run behavior

Before a Run starts, the app purges stale Run state, old provisioning secrets, orphaned keys, and controller identities. Cleanup failure blocks the Run.

The app supplies the raw onboarding payload to the Matter SDK. The SDK performs discovery and commissioning; the app does not scan for BLE or mDNS commissionees and does not report a commissioning transport. A commissioning failure is preserved and stops the Run.

Runs are one-shot and never resumed. `app_restart` rebuilds the controller runtime inside the current Run and reconnects without recommissioning; it is not a recovery path for an interrupted Run.

A P0 failure or P0 `not_run` blocks later P0 cases and fills dependent results with reasons. No P0 failure is retried in the same Run.

## Prompts

`agent_android` applies only to Android system or permission UI on the selected controller. Verify mobile automation is targeting that controller, perform the smallest requested action, and re-read app state before confirming.

`human` requires the Agent to pause and ask the operator. This covers physical commissionee actions and physical iOS system surfaces. Do not claim success until state changes or the operator explicitly confirms completion.

If a prompt is unresolved after three minutes, use `skip_prompt` with a concrete reason when allowed. Never fabricate confirmation or leave a prompt waiting indefinitely.

## Report verification

Before writing report files, the host verifies:

- protocol and schema versions;
- exactly 8 fixed test IDs;
- result and duration types;
- summary counts and overall consistency;
- `vendor_id`, `product_id`, and `network_transport: "wifi"`;
- absence of retired commissioning-transport fields;
- `plugin_commit` matches repository HEAD;
- test-app commit is a 40-character lowercase SHA;
- sanitization confirmation and forbidden sensitive values.

The app generates Markdown from the same validated result. A human reviews the report before attaching it to a pull request.

## Runtime files

```text
.dart_tool/device_test_agent/session.json
build/device-test-agent/
```

The session descriptor contains process ID, loopback port, LAN WebSocket endpoint, selected public device metadata, and artifact directory. It is ignored operational state. Screenshots and reports default to `build/device-test-agent/`.

## Non-goals

- TLS, authentication, or public exposure.
- An MCP server.
- Automatic controller selection.
- Host-side commissionee scanning or readiness gating.
- Commissioning-transport selection or fallback.
- Automated physical commissionee control.
- Automated iOS system dialogs.
- Hardware-in-the-loop CI or automatic evidence upload.

## Tests

Bridge tests cover hello-first ordering, state replay, monotonic sequence, command deduplication, and artifact ordering. Host CLI tests cover ADB parsing, explicit selection, selector resolution, and removal of private iOS identifiers from public JSON. These tests validate mechanics, not Matter device behavior.
