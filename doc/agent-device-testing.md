# Agent-Driven Device Testing

This document defines the engineering interface between the flutter_matter device-test app, a local host CLI, and an Agent. It does not implement Matter test cases or wire the bridge into the app UI. Those responsibilities belong to the device-test app runner and the app bootstrap.

## Goals

- Let an Agent observe semantic test state without reading screenshots on every step.
- Let the Agent send one idempotent command at a time to the test app.
- Keep the app as the WebSocket client so Android and physical iOS devices can connect to a Mac-hosted server.
- Expose every operation through a JSON CLI that an Agent can call from a shell.
- Keep all device-test evidence free of device identifiers and provisioning secrets.

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
                                      +---- declarative test runner
                                      +---- semantic state and events
                                      +---- screenshot and report payloads
```

The host is a long-running `serve` process. Other CLI commands use a loopback-only control HTTP server created by that process. The test app connects outbound to the LAN WebSocket endpoint. The app never needs to expose an inbound HTTP server, which keeps behavior consistent on Android and physical iOS.

The protocol deliberately does not use TLS. It is intended only for a trusted private development LAN. Do not expose the WebSocket port to the public internet.

## Component Boundaries

| Component | Responsibility |
| --- | --- |
| `device_test_app/lib/src/agent/protocol.dart` | Protocol v1 message envelopes, typed payload models, validation, and opaque IDs. |
| `device_test_app/lib/src/agent/agent_bridge_client.dart` | Reconnect loop, sequence generation, command deduplication, command serialization, and artifact delivery. |
| `tool/device_test_agent.dart` | Device discovery, explicit selection, LAN WebSocket server, local control server, platform restart/screenshot helpers, and report persistence. |
| `.agents/skills/flutter-matter-device-test/SKILL.md` | Agent-safe workflow, user-selection rules, external-action routing, and evidence requirements. |

The app bridge is UI-independent. The app bootstrap should create it after collecting runtime metadata and provide a command handler backed by the test runner.

## Protocol V1

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

`command_id` is present only when a message belongs to a command exchange. The protocol name and version are mandatory and are checked by both sides.

| Type | Direction | Purpose |
| --- | --- | --- |
| `hello` | App to host | App identity, controller metadata, plugin commit, capabilities, and app instance ID. |
| `state` | App to host | Semantic runner phase, counters, current test, prompt, and sanitized details. |
| `event` | App to host | Monotonic progress or failure information. |
| `command` | Host to app | A named command with JSON arguments and an idempotency key. |
| `command_result` | App to host | Terminal command status and sanitized result data. |
| `screenshot` | App to host | Base64 image bytes correlated with a command. |
| `report` | App to host | Sanitized schema v1 JSON plus the matching Markdown summary. |
| `error` | Both | Protocol or command failure that does not necessarily close the socket. |

### Sequence Rules

- Each sender increments `sequence` for every transmitted message.
- The host rejects a non-increasing command sequence within one WebSocket connection.
- The app continues its sequence across reconnects instead of resetting the sequence on every socket.
- `hello.instance_id` identifies one app process. A new app process may reset to sequence one, and the host resets its acceptance baseline when the instance ID changes.
- The app records the last host sequence per connection. A new socket resets that host-input baseline because the CLI process may have restarted.

### Command Idempotency

The host must reuse a command ID when retrying the same logical operation. The app bridge keeps a bounded cache of terminal outcomes. A duplicate command ID does not execute the handler again; the app resends the cached screenshot, report, and a `command_result` with status `duplicate`.

The host allows one outstanding command per controller session. The app executes received commands serially even if a non-conforming host sends more than one.

### Reconnect Behavior

`AgentBridgeClient`:

- Reconnects with capped exponential backoff.
- Sends `hello` first after every reconnect.
- Resends the latest semantic state after `hello`.
- Buffers new events while disconnected with a bounded queue.
- Continues sequence numbers for the lifetime of the app process.
- Preserves command deduplication results across reconnects.
- Reports its connection state as `stopped`, `connecting`, `connected`, or `waitingToReconnect`.

The host marks the app disconnected when the WebSocket closes. A command waiting at that moment fails with `app_disconnected`; the Agent may retry the same command ID after the app reconnects.

## App Hello Data

The app should send only reviewer-safe metadata:

- App name, version, build, and test-app commit.
- The exact flutter_matter plugin commit under test.
- Controller platform and app build identifier.
- Device model and OS version.
- Capability names such as `state`, `event`, `command`, `screenshot`, and `report`.
- An opaque app-instance ID generated by the app process.

Do not include serial numbers, UDIDs, BLE addresses, Wi-Fi SSIDs, passwords, setup codes, onboarding payloads, certificates, or private keys.

## Semantic State and Prompts

The runner should publish semantic state whenever its phase changes. Typical statuses are `idle`, `running`, `waiting_for_app`, `waiting_for_agent_android`, `waiting_for_human`, `passed`, `failed`, `not_run`, and `stopped`.

A `waiting_for_agent_android` state may include a prompt with channel `agent_android`. This is limited to Android system or permission UI that an Agent can operate through the installed mobile MCP tooling. A prompt with channel `human` means the Agent must ask the operator to act on a physical Matter device or a physical iOS system surface.

State and event messages should describe the test ID, completed count, and next action. They must not contain raw logs or provisioning secrets.

## Host Device Discovery

`devices` discovers:

- Android devices through `adb devices -l` and `adb shell getprop`.
- iOS devices through `xcrun devicectl list devices --json-output`.
- iOS fallback devices through `idevice_id` and `ideviceinfo` when CoreDevice returns no usable devices.

Each candidate contains `id`, `short_id`, `platform`, `model`, `os_version`, `name`, `state`, `connection`, and `usable`. Public JSON never includes the internal iOS UDID captured for `idevicescreenshot`.

## Explicit Device Selection

The CLI never selects a default device.

- `devices` only lists candidates.
- `serve` always requires an explicit `--device`.
- Missing selection returns `device_selection_required` with all candidates.
- A selector may be an exact ID, a unique exact name, or a unique ID prefix.
- An ambiguous selector returns the matching candidates.
- An unavailable selected device returns `device_unavailable`.

When several physical phones are connected, the Agent must present an interactive user choice and show platform, model, OS version, and `short_id`. The full ID is retained for the subsequent `--device` argument but is not displayed in the choice.

When a virtual commissionee is required, the Agent must ask a separate question and choose a distinct Android device. The controller and virtual commissionee cannot be the same device.

## CLI Commands

Run commands from the plugin repository root.

```bash
fvm dart run tool/device_test_agent.dart devices
```

```bash
fvm dart run tool/device_test_agent.dart serve \
  --device <explicit-id> \
  --port 8765
```

`serve` prints one startup JSON object and remains running. Start it in a long-lived shell or background process. Stop it with the `stop` command or an interrupt signal.

```bash
fvm dart run tool/device_test_agent.dart status
fvm dart run tool/device_test_agent.dart wait --for connected --timeout-seconds 120
fvm dart run tool/device_test_agent.dart wait --for state --value running --timeout-seconds 600
fvm dart run tool/device_test_agent.dart wait --for state --value waiting_for_agent_android --timeout-seconds 600
```

```bash
fvm dart run tool/device_test_agent.dart command \
  --name start_run \
  --args-json '{"mode":"quick"}' \
  --command-id <stable-id> \
  --timeout-seconds 1200
```

```bash
fvm dart run tool/device_test_agent.dart screenshot \
  --output build/device-test-agent/screenshots/current.png
```

The screenshot command first requests an app screenshot through the bridge. If the app is disconnected or the bridge command fails, the host falls back to `adb exec-out screencap -p` or `idevicescreenshot`.

```bash
fvm dart run tool/device_test_agent.dart report \
  --output-dir build/device-test-agent/reports/<run-id>
```

The report command requests the sanitized schema v1 JSON and Markdown payload, verifies the report structure and plugin commit, and writes:

- `device-test-report.json`
- `device-test-report.md`

```bash
fvm dart run tool/device_test_agent.dart restart-app
fvm dart run tool/device_test_agent.dart stop
```

`restart-app` uses the active session's selected device by default. Without an active session it requires `--device`.

- Android uses `adb shell am force-stop` followed by a launcher start.
- iOS uses `xcrun devicectl device process launch --device <id> --terminate-existing <bundle-id>`.

## Reserved Commands

The bridge is generic, but the device-test app should implement these command names:

| Name | Arguments | Meaning |
| --- | --- | --- |
| `start_run` | `{"mode":"quick"}` or `{"mode":"full"}` | Start the declarative runner. |
| `stop_run` | `{}` | Stop the current run without manufacturing a passing report. |

The app may add runner-specific commands. New command names must preserve the same command ID and command-result semantics.

## Agent Loop

The repository skill requires this sequence:

1. Run `devices` and observe all candidates.
2. Ask the user to select the controller when multiple phones are connected.
3. Start `serve` with the explicit controller ID.
4. Wait for the app bridge to connect.
5. Start a quick or full run with a stable command ID.
6. For `agent_android` prompts, use the installed mobile MCP/Android automation to act on the controller device.
7. For `human` prompts, ask the operator to act on the physical Matter device or iOS system UI.
8. Use status, state, events, and screenshots to verify progress.
9. Pull the report and verify that `plugin_commit` equals the PR head.
10. Never retry a P0 failure to manufacture a passing report.
11. Remind the operator to remove the fabric, reset the commissionee, clear app data, and reset the virtual commissionee.

## Report Verification

The host performs structural checks before writing report files:

- Envelope and report schema versions are supported.
- All 13 fixed test IDs occur exactly once.
- Test statuses and durations have valid types.
- Summary counts match the tests object.
- Overall summary result is consistent with P0 and failure rules.
- `plugin_commit` matches the current repository HEAD.
- Test-app commit is a 40-character lowercase Git SHA.
- Sanitization is explicitly confirmed.
- Forbidden keys and obvious sensitive text are rejected.

The app remains responsible for complete JSON Schema validation, Markdown generation from the same result object, and final human review before attaching evidence to a pull request.

## Error Codes

| Code | Meaning |
| --- | --- |
| `device_selection_required` | A selection or more specific selector is required. |
| `device_not_found` | The explicit selector matched no candidate. |
| `device_unavailable` | The selected device is not ready. |
| `session_already_running` | One controller session is already active. |
| `no_active_session` | A session command was called without `serve`. |
| `app_disconnected` | The test app WebSocket is not connected. |
| `command_in_progress` | Another command is already outstanding. |
| `command_timeout` | The app did not complete the command before the deadline. |
| `plugin_commit_mismatch` | Report evidence belongs to a different plugin commit. |
| `report_sensitive_data` | Report JSON contains a forbidden field or value. |

## Runtime Files

The host stores its local session descriptor at:

```text
.dart_tool/device_test_agent/session.json
```

The file contains the process ID, loopback control port, LAN WebSocket endpoint, selected public device metadata, and artifact directory. It is local operational state and is covered by the ignored `.dart_tool/` directory.

Default screenshots and reports are written under:

```text
build/device-test-agent/
```

## Non-Goals

- TLS, authentication, or public-network exposure.
- An MCP server.
- Automated Matter test case implementation.
- Automatic device selection.
- Automated control of physical Matter hardware.
- Automated iOS system-dialog interaction.
- Evidence upload to GitHub Actions.

## Verification

Agent bridge tests use fake WebSocket channels to verify:

- Hello-first ordering.
- Latest-state replay.
- Monotonic sequence across reconnect.
- Command ID deduplication.
- Artifact ordering before command results.

Host CLI tests use fake device candidates to verify:

- ADB output parsing.
- Mandatory explicit selection.
- Exact and ambiguous selector handling.
- Removal of the internal iOS UDID from public JSON.
