# Contributing

Thank you for contributing to `flutter_matter`. This document defines the minimum verification, evidence, and compatibility expectations for every pull request.

## Documentation map

- Architecture and runtime boundaries: [`ARCHITECTURE.md`](ARCHITECTURE.md)
- Public API inventory and versioning: [`doc/public-api.md`](doc/public-api.md)
- Platform and toolchain baseline: [`doc/platform-support.md`](doc/platform-support.md)
- Physical-device process and matrix: [`doc/device-validation.md`](doc/device-validation.md)
- Device-test app architecture and local commands: [`doc/device-test-app.md`](doc/device-test-app.md)
- Agent-driven device testing: [`doc/agent-device-testing.md`](doc/agent-device-testing.md)
- Device-test report contract: [`doc/device-test-report.md`](doc/device-test-report.md)
- Device-test report schema: [`doc/device-test-report.schema.json`](doc/device-test-report.schema.json)
- Reviewer checklist: [`doc/pr-review-checklist.md`](doc/pr-review-checklist.md)
- Architecture decisions: [`doc/adr/`](doc/adr/)
- Release process: [`doc/releasing.md`](doc/releasing.md)
- Security policy: [`SECURITY.md`](SECURITY.md)
- Third-party notices: [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md)

## CI scope

The required `Dart check and tests` workflow verifies:

- Flutter version resolution from `.fvmrc`.
- Dart dependency resolution.
- Dart static analysis errors using non-fatal info and warning classification.
- Plugin Dart tests in the root `test/` suite.

The workflow does not run example tests, compile Android or iOS native code, run native unit tests, run integration or device tests, validate package publication, or enforce formatting. Passing CI therefore means that Dart analysis and root Dart tests passed; it does not prove native builds or device behavior. Native builds, device validation, and package publication are reviewed separately from the required Dart gate.

Automated tests cover `test/**/*_test.dart` at the plugin root only. `example/**` is a build and manual demonstration target and is never an automated test target. `device_test_app/**` has local unit tests but is not part of the required CI workflow.

## Local prerequisites

The repository uses Flutter `3.41.0`, pinned in `.fvmrc`. Prefer FVM:

```bash
fvm flutter pub get
```

If FVM is unavailable, use Flutter `3.41.0` and replace `fvm flutter` with `flutter`. The `pubspec.yaml` lower bounds remain unchanged, but Flutter 3.41.0 is the only currently validated Flutter version.

The documented platform baseline is in [`doc/platform-support.md`](doc/platform-support.md). In particular, iOS validation requires Xcode 16.4 or later and CocoaPods 1.17 on macOS, and the vendored Matter framework supports physical iPhoneOS arm64 devices only. Record the exact Xcode version used in the pull request evidence.

## Required verification

Run the checks that apply to the files and behavior changed by the pull request.

Dart analysis and root plugin tests:

```bash
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
```

Android compile check:

```bash
cd example
fvm flutter build apk --debug
```

iOS compile check, on macOS only:

```bash
cd example
fvm flutter build ios --debug --no-codesign
```

The iOS check intentionally uses a device build because the vendored Matter framework currently contains an iPhoneOS arm64 slice only. Simulator results are not valid plugin evidence.

For behavior changes, also describe the exact manual scenario and the physical device, OS, and relevant network conditions. The scenario must be specific enough for another person to reproduce.

## Example application

The `example/` application exists to build and exercise the plugin manually. It is not part of the automated test contract and must not be added to required CI as a test target. Use it for Android/iOS builds and for physical-device functional verification.

## Device test app

The dedicated validation app lives in `device_test_app/`. Run its local checks when changing the app, Agent bridge, report generation, or device-test Skill:

```bash
cd device_test_app
fvm flutter pub get
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
```

Official app builds should use the repository wrapper so commit metadata is injected:

```bash
fvm dart run tool/device_test_app.dart check
fvm dart run tool/device_test_app.dart build-apk
fvm dart run tool/device_test_app.dart build-ios
```

The `quick` profile is for iteration only. Formal device evidence requires the `full` profile and both generated report files. Agent-driven runs must use `$flutter-matter-device-test`; when multiple phones are connected, the Agent must prompt the user and must not infer a selection.

## Pull request evidence

Every pull request must use the repository PR template. For each verification row, provide:

- The exact command or manual scenario.
- The platform, device, OS, or toolchain used.
- The result: `Passed`, `Failed`, or `Not run`.
- A link to a workflow run, log, screenshot, recording, or other safe evidence.
- A reason and risk statement when the result is `Not run`.

Do not use vague statements such as "tested locally" without a command, result, or affected-platform explanation. Do not include credentials, tokens, private keys, personal provisioning data, or unsanitized private logs.

A check may be marked `Not run` when it does not apply or when the required hardware or toolchain is unavailable. The author must explain why it was not run, what remains unverified, and what risk the reviewer is accepting.

## Device validation reports

Device-behavior changes must use the physical-device process in [`doc/device-validation.md`](doc/device-validation.md). A change affects device behavior when it changes commissioning, BLE, networking, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel behavior, or native Matter code.

For every affected controller platform, the pull request must include:

- The generated Markdown summary from `device-test-report.md`.
- A sanitized `device-test-report.json` attachment conforming to `device-test-report.schema.json`.
- Optional sanitized screenshots or other bounded evidence that exercise the changed behavior.
- A report `plugin_commit` equal to the current pull request head.

The dedicated device-test app generates the JSON and Markdown files automatically in the `full` profile. An interim manual report is acceptable only when it conforms to the same schema and contract, and it must not claim to be generated by the app.

Shared behavior requires Android and physical iOS reports. An explicitly platform-specific change requires the affected platform report and a clear statement that the other platform is unaffected. Documentation, CI, packaging, and non-device Dart changes may mark device validation as `Not applicable` with a reason.

Attach reports and evidence in pull request comments and link them from the Device Validation section. All repository attachments are public. Do not include device serial numbers, iOS UDIDs, Wi-Fi credentials, setup codes, onboarding payloads, BLE addresses, certificates, private keys, or complete raw logs.

Stable release-preparation pull requests must include separate Android and iOS clean-cycle P0 reports for the candidate commit. Use a Matter commissionee that satisfies the documented capability requirements; the report contract does not record device provenance.

## Platform expectations

This package exposes both Android and iOS implementations. A change to a shared Dart API, MethodChannel route, JSON shape, callback contract, or native behavior must declare verification for both platforms unless the change is explicitly documented as platform-specific.

Current platform exceptions are:

- NSD is Android-only.
- `dataVersionFilters` in subscriptions is Android-only.
- iOS `pairDevice` requires `onboardingPayload`.
- iOS does not support simulator builds with the current `ZGMatter` binary.

For changes involving commissioning or device behavior, describe the relevant manual scenarios, including where applicable:

- BLE commissioning.
- Wi-Fi commissioning, including open Wi-Fi.
- Thread credentials.
- ICD registration.
- Attribute read, write, invoke, and subscribe.
- Reconnect, disconnect, and unpair behavior.

Where the dedicated report format applies, the report and attachments replace vague manual summaries; do not duplicate sensitive details from the report into free-form notes.

## Public API and compatibility

Call out any change to exported Dart types, method signatures, default values, exported paths, MethodChannel names, URL hosts, paths, JSON envelopes, or callback semantics.

- The only supported consumer import is `package:flutter_matter/flutter_matter.dart`.
- Direct `src/` imports are internal except in tests.
- New public symbols must be exported from `lib/flutter_matter.dart`, documented in [`doc/public-api.md`](doc/public-api.md), and reflected in `test/public_api_test.dart` when the export surface changes.
- MethodChannel contract changes must update `test/method_channel_contract_test.dart` and receive compatibility review.
- Breaking changes must be identified as such and include the intended versioning or migration impact.

The project currently uses lightweight governance rather than an external API-diff tool. Export-path drift and core wire envelopes are automated; method-level compatibility remains a reviewer responsibility.

## Package and release changes

Changes to package metadata, `LICENSE`, third-party notices, public documentation paths, or release automation must also pass:

```bash
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
fvm dart pub publish --dry-run
fvm dart run tool/release.dart validate --tag vX.Y.Z
fvm dart run tool/release.dart notes --version X.Y.Z
```

The required Dart check remains unchanged. The `Release` workflow is a manual preflight before tagging and a tag-triggered GitHub Release process after merge; it never publishes to pub.dev. Follow [`doc/releasing.md`](doc/releasing.md) for the complete runbook.

## Security reports

Do not disclose suspected vulnerabilities in a public issue. Use [GitHub Private Vulnerability Reporting](https://github.com/Tan-yi-xiong/flutter_matter/security/advisories/new) and follow [`SECURITY.md`](SECURITY.md).

## Review and merge

Reviewers must use [`doc/pr-review-checklist.md`](doc/pr-review-checklist.md). A green CI result is necessary but not sufficient for approval. Reviewers must verify that the declared evidence covers the changed code path and affected platforms.

Device-behavior pull requests require the versioned report and attachments described above. A stable release cannot proceed unless the release-preparation pull request contains passing Android and iOS P0 reports for the candidate commit.

The `main` branch requires a pull request and the `Dart check and tests` status check. Repository administrators retain an emergency bypass. Bypass use does not remove the obligation to document verification.

## Documentation language

All repository documentation, workflow comments, pull request templates, and review guidance must be written in English. Preserve non-English text only when it is a required user-facing string or an exact quoted reference.

Update `README.md`, the relevant documentation page, or `CHANGELOG.md` when behavior, configuration, or public usage changes.
