# Device Test Report Contract

The device-test report is the reviewable evidence produced by a physical-device validation run. The dedicated device-test app must emit both a machine-readable JSON report and a Markdown summary from the same in-memory result data.

The dedicated app implements this contract and includes a local report validator. The app and its tests are outside the required CI gate.

Formal acceptance requires a Matter commissionee. The app passes the raw onboarding payload directly to the Matter SDK, which performs commissionee discovery and commissioning. Device provenance is not part of the report contract.

## Output files

The test app must write these files into a user-selected output directory:

- `device-test-report.json`: the complete sanitized result, conforming to [`device-test-report.schema.json`](device-test-report.schema.json).
- `device-test-report.md`: a human-readable summary for the pull request description.

Both files must describe the same run. The Markdown summary must contain the same plugin commit, test-app commit, controller platform, commissionee identity and network transport, test results, and evidence file names as the JSON report.

## Schema version

The current schema version is `4`. Schema versions `1`, `2`, and `3` are retired and must not be accepted as device evidence. The schema artifact, example report, app model, app validator, Agent CLI validator, Markdown renderer, documentation, and PR template must remain aligned at version `4`.

A removal, rename, type change, status change, required-field change, or report-content rule change requires a new schema version and an update to this document and the PR template. Reports with an unknown or unsupported `schema_version` must not be accepted as release evidence.

Old v2 and v3 reports and old Run snapshots are not migrated.

## Required data

| Area | Required content |
| --- | --- |
| Run identity | `generated_at`, test-app name/version/commit, and the exact `plugin_commit` under test |
| Controller | `android` or `ios`, device model, OS version, and app build identifier |
| Commissionee | Automatically parsed integer `vendor_id` and `product_id`, and `wifi` network transport |
| Summary | Overall `passed`, `failed`, or `not_run`; counts for each status |
| Tests | A `tests` object keyed by every fixed P0, P1, and P2 test ID, each with result, duration, optional notes, and optional relative evidence filenames |
| Sanitization | Explicit confirmation that the report and attachments were reviewed for sensitive data |

The report must not include commissionee model, firmware, external state-change method, external state-change notes, or user-entered identity fields. Commissionee discovery and commissioning are delegated to the Matter SDK. Device model and OS version refer to the controller and are sufficient for controller traceability.

Do not add serial numbers, iOS UDIDs, Wi-Fi SSIDs, Wi-Fi passwords, setup codes, onboarding payloads, BLE addresses, certificates, or private keys to any field.

## Fixed test IDs

| Priority | Test ID | Requirement |
| --- | --- | --- |
| P0 | `build_install` | Android APK or signed iOS app installs and launches |
| P0 | `commissioning` | PASE/commissioning completes through SDK-managed discovery with `errorCode == 0` within 120 seconds |
| P0 | `operational_connect` | CASE connection returns a valid connect context within 30 seconds |
| P0 | `onoff_invoke` | Off, On, and Toggle succeed within 10 seconds and change state |
| P0 | `onoff_subscription` | Initial state and an external update arrive within 15 seconds |
| P0 | `node_label_persistence` | NodeLabel write/read succeeds and survives a commissionee restart |
| P1 | `app_restart` | Controller restart reconnects without recommissioning |
| P1 | `factory_reset_recommission` | A later factory reset and commissioning cycle succeeds |
| P2 | `invalid_setup_passcode` | A well-formed setup payload with a deliberately incorrect, same-discriminator setup passcode produces a clear non-zero failure without a crash |
| P2 | `invalid_wifi_password` | Provisioning fails clearly without reporting false success |
| P2 | `remove_fabric_ui` | Existing remove/delete-device UI behavior is recorded accurately |

All 11 IDs must appear exactly once as keys in the `tests` object. The priority is determined by the test ID, so it is not duplicated inside each result. Unavailable P1 or P2 scenarios must be represented as `not_run` with a reason; they must not be omitted. A required P0 scenario cannot be omitted, and a stable release requires every P0 entry to be `passed`.

## Commissioning rules

- The app does not scan for BLE or mDNS commissionees itself.
- The app supplies the raw onboarding payload to the Matter SDK.
- The Matter SDK performs commissionee discovery and commissioning; no commissioning-transport field is reported.
- After commissioning fails, the Run preserves the failure and stops. It does not retry commissioning in the same Run.

## Summary rules

- The overall result is `passed` only when `network_transport` is `wifi`, every P0 test is `passed`, and every non-P0 test is either `passed` or `not_run` with a reason.
- The overall result is `failed` when any test is `failed`, especially any P0 test.
- The overall result is `not_run` when any P0 test is `not_run`.
- Counts must be calculated from the `tests` object and must total 11.
- P2 failures are valid report data but require explicit maintainer risk acceptance before a stable release.

## Markdown summary template

The generated Markdown should follow this structure:

```markdown
### Device validation summary

- Plugin commit: `<40-character SHA>`
- Test app: `<name> <version> (<commit>)`
- Controller: `<android|ios>` / `<device model>` / `<OS version>`
- Commissionee: vendor `<vendor_id>` / product `<product_id>`
- Network transport: `wifi`
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

1. Use the selected controller and commissionee from [`device-validation.md`](device-validation.md).
2. Delegate discovery and commissioning to the Matter SDK through the raw onboarding payload.
3. Reject unsupported `start_run` fields and unsupported report fields instead of silently ignoring them.
4. Automatically purge old Run secrets and controller identities before a Run, and block the Run if cleanup fails.
5. Keep cached Wi-Fi credentials in secure storage and exclude them from all state, logs, screenshots, and reports.
6. Emit both output files atomically only after the run is complete.
7. Set `plugin_commit` from the plugin checkout actually exercised by the test app.
8. Set the test-app commit from the test app's own build metadata.
9. Parse vendor and product identity from the commissionee payload automatically.
10. Derive the summary counts and result from the recorded test entries and their documented priorities.
11. Mark unavailable P1/P2 tests as `not_run` with a reason; never replace a failed P0 with a retry result.
12. Apply the sanitization policy before writing files; the app emits JSON and Markdown only.
13. Validate its own JSON against this schema before declaring the run complete.
14. Mark the report as failed or not run when a required P0 result is missing, failed, or not run, while still writing a reviewable report when possible.

## Pull request submission

For a device-behavior pull request:

1. Paste `device-test-report.md` into the Device Validation section of the PR description.
2. Upload the sanitized JSON and sanitized evidence files in a PR comment.
3. Add the uploaded file links to the Markdown summary and PR section.
4. Confirm that the report commit matches the PR head.
5. Update the report after any code change that could affect device behavior.

For a stable release-preparation pull request, provide separate Android and iOS reports against the candidate commit. Both reports must use a Matter commissionee and schema v4. Device provenance is not part of the report contract.

## Failure handling

- If the report or attachment is missing, reviewers must treat the change as unverified.
- If the report commit is stale, request a new report against the current PR head.
- If the schema is not v4 or `network_transport` is not `wifi`, reviewers must reject the report as formal evidence.
- If a report contains retired commissionee model, firmware, state-change, or commissioning-transport fields, reject it and regenerate from a schema v4 source.
- If an attached file contains sensitive data, remove the attachment, regenerate the report, and rotate any exposed credential.
- If the test app cannot emit a valid report, keep the run result local and record the blocker; do not hand-edit sensitive data into an attachment.
