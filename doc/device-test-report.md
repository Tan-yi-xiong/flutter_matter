# Device Test Report Contract

The device-test report is the reviewable evidence produced by a physical-device validation run. The dedicated device-test app must emit both a machine-readable JSON report and a Markdown summary from the same in-memory result data.

The dedicated app implements this contract and includes a local report validator. The app and its tests are outside the required CI gate.

## Output files

The test app must write these files into a user-selected output directory:

- `device-test-report.json`: the complete sanitized result, conforming to [`device-test-report.schema.json`](device-test-report.schema.json).
- `device-test-report.md`: a human-readable summary for the pull request description.

Both files must describe the same run. The Markdown summary must contain the same plugin commit, test-app commit, controller platform, commissionee type, test results, and evidence file names as the JSON report.

## Schema version

The initial schema version is `1`. A compatible addition, such as an optional non-sensitive field, may keep the version when the schema remains backward compatible. A removal, rename, type change, status change, or required-field change requires a new schema version and an update to this document and the PR template.

Reports with an unknown or unsupported `schema_version` must not be accepted as release evidence.

## Required data

| Area | Required content |
| --- | --- |
| Run identity | `generated_at`, test-app name/version/commit, and the exact `plugin_commit` under test |
| Controller | `android` or `ios`, device model, OS version, and app build identifier |
| Commissionee | `real` or `virtual`, model, firmware, BLE commissioning transport, network transport, and external state-change method |
| Summary | Overall `passed`, `failed`, or `not_run`; counts for each status |
| Tests | A `tests` object keyed by every fixed P0, P1, and P2 test ID, each with result, duration, optional notes, and optional relative evidence filenames |
| Sanitization | Explicit confirmation that the report and attachments were reviewed for sensitive data |

Device models and OS versions are sufficient for traceability. Do not add serial numbers, iOS UDIDs, Wi-Fi SSIDs, Wi-Fi passwords, setup codes, onboarding payloads, BLE addresses, certificates, or private keys to any field.

## Fixed test IDs

| Priority | Test ID | Requirement |
| --- | --- | --- |
| P0 | `build_install` | Android APK or signed iOS app installs and launches |
| P0 | `ble_discovery` | Correct commissionee is discovered within 15 seconds |
| P0 | `ble_commissioning` | Commissioning completes with `errorCode == 0` within 120 seconds |
| P0 | `operational_connect` | CASE connection returns a valid connect context within 30 seconds |
| P0 | `onoff_invoke` | Off, On, and Toggle succeed within 10 seconds and change state |
| P0 | `onoff_subscription` | Initial state and an external update arrive within 15 seconds |
| P0 | `node_label_persistence` | NodeLabel write/read succeeds and survives a commissionee restart |
| P1 | `app_restart` | Controller restart reconnects without recommissioning |
| P1 | `factory_reset_recommission` | A later factory reset and full commissioning succeeds |
| P2 | `invalid_setup_passcode` | An invalid passcode returns a clear non-zero failure without a crash |
| P2 | `bluetooth_disabled` | Commissioning fails clearly when Bluetooth is unavailable |
| P2 | `invalid_wifi_password` | Provisioning fails clearly without reporting false success |
| P2 | `remove_fabric_ui` | Existing remove/delete-device UI behavior is recorded accurately |

All 13 IDs must appear exactly once as keys in the `tests` object. The priority is determined by the test ID, so it is not duplicated inside each result. Unavailable P1 or P2 scenarios must be represented as `not_run` with a reason; they must not be omitted. A required P0 scenario cannot be omitted, and a stable release requires every P0 entry to be `passed`.

## Summary rules

- The overall result is `passed` only when every P0 test is `passed` and every non-P0 test is either `passed` or `not_run` with a reason.
- The overall result is `failed` when any test is `failed`, especially any P0 test.
- The overall result is `not_run` when any P0 test is `not_run`.
- Counts must be calculated from the `tests` object and must total 13.
- P2 failures are valid report data but require explicit maintainer risk acceptance before a stable release.

## Markdown summary template

The generated Markdown should follow this structure:

```markdown
### Device validation summary

- Plugin commit: `<40-character SHA>`
- Test app: `<name> <version> (<commit>)`
- Controller: `<android|ios>` / `<device model>` / `<OS version>`
- Commissionee: `<real|virtual>` / `<model>` / `<firmware>`
- Commissioning transport: `ble`
- Overall result: `<passed|failed|not_run>`

| ID | Priority | Result | Duration | Notes |
| --- | --- | --- | --- | --- |
| `build_install` | P0 | `passed` | `1234 ms` | |
| ... | ... | ... | ... | ... |

#### P1 and P2 notes

Summarize non-P0 failures or `not_run` reasons.

#### Evidence files

- `<relative evidence filename>`

#### Sanitization

Confirmed: no device identifiers, provisioning secrets, certificates, private keys, or raw logs are attached.
```

The dedicated app may render the table automatically. Manual interim reports must preserve the same information; they must not claim to have been generated by the dedicated app.

## Test-app responsibilities

The dedicated app must:

1. Use the selected commissionee and controller path from [`device-validation.md`](device-validation.md).
2. Enforce the clean-cycle and real-device-first rules rather than allowing a caller to silently skip them.
3. Emit both output files atomically only after the run is complete.
4. Set `plugin_commit` from the plugin checkout actually exercised by the test app.
5. Set the test-app commit from the test app's own build metadata.
6. Derive the summary counts and result from the recorded test entries and their documented priorities.
7. Mark unavailable P1/P2 tests as `not_run` with a reason; never replace a failed P0 with a retry result.
8. Apply the sanitization policy before writing files; the app emits JSON and Markdown only.
9. Validate its own JSON against this schema before declaring the run complete.
10. Mark the report as failed or not run when a required P0 result is missing, failed, or not run, while still writing a reviewable report when possible.

## Pull request submission

For a device-behavior pull request:

1. Paste `device-test-report.md` into the Device Validation section of the PR description.
2. Upload the sanitized JSON and sanitized evidence files in a PR comment.
3. Add the uploaded file links to the Markdown summary and PR section.
4. Confirm that the report commit matches the PR head.
5. Update the report after any code change that could affect device behavior.

For a stable release-preparation pull request, provide separate Android and iOS reports against the candidate commit. When the virtual-device fallback is used, both reports must use that same commissionee type and include the reason a qualified real device was unavailable.

## Failure handling

- If the report or attachment is missing, reviewers must treat the change as unverified.
- If the report commit is stale, request a new report against the current PR head.
- If an attached file contains sensitive data, remove the attachment, regenerate the report, and rotate any exposed credential.
- If the test app cannot emit a valid report, keep the run result local and record the blocker; do not hand-edit sensitive data into an attachment.
