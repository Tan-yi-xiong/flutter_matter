# Device test report contract

A device-test Run produces reviewable evidence through two files generated from the same in-memory result:

- `device-test-report.json`: sanitized schema v4 data.
- `device-test-report.md`: human-readable summary for the pull request.

Formal evidence requires the `full` profile and a real Matter commissionee. The app passes the raw onboarding payload to the Matter SDK, which performs discovery and commissioning.

## Schema

The current schema version is `4`. Versions `1`, `2`, and `3` are retired and must not be accepted as device evidence.

Keep these aligned at version 4:

- [JSON Schema](device-test-report.schema.json)
- [Example report](device-test-report.example.json)
- device-test app model and validator
- Agent CLI validator
- Markdown renderer
- this document and the pull-request template

A required-field, type, status, ID, or content-rule change requires a new schema version and corresponding documentation update. Unknown schema versions are invalid evidence.

## Required data

| Area | Required content |
| --- | --- |
| Run | `generated_at`, test-app name/version/commit, and exact `plugin_commit` |
| Controller | `android` or `ios`, device model, OS version, app build |
| Commissionee | Parsed `vendor_id`, `product_id`, and `network_transport: "wifi"` |
| Summary | `passed`, `failed`, or `not_run`, plus counts |
| Tests | Every fixed test ID with status, duration, optional notes, and optional relative evidence filenames |
| Sanitization | Explicit review confirmation and policy version |

Do not include commissionee model, firmware, external state-change method, user-entered identity, serial numbers, UDIDs, Wi-Fi SSIDs/passwords, setup codes, onboarding payloads, BLE addresses, certificates, private keys, or raw logs.

## Fixed test IDs

| Priority | ID | Requirement |
| --- | --- | --- |
| P0 | `build_install` | APK or signed iOS app installs and launches |
| P0 | `commissioning` | PASE completes through SDK-managed discovery with `errorCode == 0` within 120 seconds |
| P0 | `operational_connect` | CASE returns a valid connect context within 30 seconds |
| P1 | `app_restart` | Persisted credentials reload and CASE reconnects without recommissioning; native-controller teardown is out of scope |
| P0 | `onoff_invoke` | Off, On, and Toggle succeed within 10 seconds and change state |
| P0 | `onoff_subscription` | Initial state and a command-triggered update arrive within 15 seconds |
| P0 | `node_label_read_write` | A written NodeLabel is read back unchanged |
| P0 | `invalid_setup_passcode` | A well-formed payload with a deliberately incorrect, same-discriminator passcode fails clearly without a crash |

All 8 IDs must appear exactly once in `tests`. Priority is derived from the ID and is not duplicated in each result. A P0 entry cannot be omitted. P1 may be `not_run` only with a reason.

## Run rules

- The app does not scan for BLE or mDNS commissionees itself.
- The app delegates discovery and commissioning to the Matter SDK.
- No commissioning-transport field is reported.
- A commissioning failure is preserved and ends commissioning work in that Run.
- The app purges old Run secrets and resets controller identities before persisting a new Run.
- Runs are one-shot; interrupted Runs are discarded and not resumed.
- The app writes JSON and Markdown atomically only after the Run reaches a terminal state when possible.

## Summary rules

- `passed`: `network_transport` is `wifi`, every P0 is `passed`, and every P1 is `passed` or `not_run` with a reason.
- `failed`: any test is `failed`.
- `not_run`: any P0 is `not_run`.
- Counts derive from the 8 entries in `tests` and must total 8.
- A P1 failure is valid report data and requires maintainer review.

## Markdown summary

The generated summary should contain:

```markdown
### Device validation summary

- Plugin commit: `<40-character SHA>`
- Test app: `<name> <version> (<commit>)`
- Controller: `<android|ios> / <model> / <OS>`
- Commissionee: vendor `<vendor_id>` / product `<product_id>`
- Network transport: `wifi`
- Overall result: `<passed|failed|not_run>`

| ID | Priority | Result | Duration | Notes |
| --- | --- | --- | --- | --- |
| ... | ... | ... | ... | ... |

#### P1 notes
#### Evidence files
#### Sanitization
```

The Markdown must describe the same run, commits, controller, commissionee, transport, results, and evidence filenames as the JSON.

## App responsibilities

The device-test app must:

1. Use the selected controller and commissionee.
2. Delegate discovery and commissioning through the raw onboarding payload.
3. Reject unsupported `start_run` and report fields.
4. Block the Run when pre-run cleanup fails.
5. Keep cached Wi-Fi credentials in secure storage and out of state, logs, screenshots, and reports.
6. Set `plugin_commit` from the exercised checkout and the test-app commit from build metadata.
7. Derive summary counts and result from the test entries.
8. Apply the sanitization policy before writing evidence.
9. Validate its JSON against the schema before declaring the report complete.

The post-Run cleanup card purges Run secrets and emits operator confirmation. It does not reset the commissionee. Every Run adds a fabric, so factory-reset the commissionee or remove the fabric before the next clean cycle.

## Pull request submission

For a device-behavior pull request:

1. Paste the generated Markdown into the Device Validation section.
2. Upload sanitized JSON and any sanitized evidence in a pull-request comment.
3. Link those files from the summary and PR section.
4. Confirm `plugin_commit` matches the PR head.
5. Regenerate evidence after any device-relevant code change.

For a stable release, provide separate Android and iOS reports for the candidate commit. Both must use schema v4 and a Matter commissionee.

## Failure handling

- Missing report or attachment: treat the change as unverified.
- Stale commit: request a new report from the current PR head.
- Wrong schema or non-Wi-Fi transport: reject as formal evidence.
- Retired commissionee or transport fields: reject and regenerate from a v4 source.
- Sensitive attachment: remove it, regenerate the report, and rotate exposed credentials.
- Invalid app output: keep the result local and record the blocker; do not hand-edit sensitive data into an attachment.
