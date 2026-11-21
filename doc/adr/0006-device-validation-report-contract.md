# ADR 0006: Device Validation Report Contract

- Status: Accepted
- Date: 2026-11-11

## Context

`flutter_matter` depends on native Matter behavior that the required Dart CI gate cannot exercise. ADR 0005 established manual evidence in pull requests, but it did not define how device results should be recorded consistently across Android, physical iOS, and Matter commissionees.

The repository also expects the example application to evolve into a dedicated device-test app. That app should emit a reviewable result instead of requiring contributors to reconstruct ad hoc commands and tables for every pull request.

## Decision

Device validation follows this order and contract:

- Use a Matter On/Off commissionee.
- Test both Android and physical iOS controllers against the selected commissionee when a change affects shared behavior.
- Define a versioned JSON report schema and a Markdown summary generated from the same result data.
- Require a device-behavior pull request to include the affected platform report and sanitized attachments.
- Require a stable release-preparation pull request to include one clean P0 cycle for Android and one clean P0 cycle for iOS against the release candidate.
- Keep evidence submission manual through pull request comments and attachments.

The initial report schema version is `1`. Fixed P0 cases cover build/install, Wi-Fi/IP discovery readiness, Wi-Fi/IP commissioning, operational connection, On/Off invocation, On/Off subscription, and NodeLabel persistence. P1 and P2 results remain in the report but do not replace the required P0 result.

The future dedicated device-test app owns report generation and self-validation. This repository phase defines the contract and documentation only; it does not introduce a self-hosted runner, an Actions hardware job, or an executable report validator.

## Consequences

- Contributors have one stable format for device evidence across current manual runs and the future test app.
- Reviewers can compare Android and iOS results without interpreting unrelated free-form reports.
- Stable releases remain manual and depend on maintainer review of formal device evidence.
- A stale report, missing platform result, or mismatched commit is treated as unverified.
- Sensitive provisioning data and device identifiers must remain outside the report and public attachments.
- Implementing the future app must conform to the schema instead of inventing a separate reporting format.

## Amendment (2026-11-12): Wi-Fi/IP commissioning contract

A later repository decision moved active validation to Wi-Fi/IP commissioning with a Matter commissionee. The report schema moved from version `1` to version `2` with 12 fixed tests that use the `ip_discovery` and `ip_commissioning` IDs instead of the former BLE test IDs. The decision text above is preserved as history.

## Amendment (2026-11-12): Schema v3 and dual-path commissioning discovery

The active device-validation contract moved from schema version `2` to version `3`. The former `ip_discovery` and `ip_commissioning` cases are replaced by `commissioning_discovery` and `commissioning`. The app now starts BLE and Wi-Fi/IP commissionable discovery concurrently, records the first matching transport as `commissioning_transport`, and does not retry commissioning through the other transport after a failure. The report requires a Wi-Fi `network_transport` and does not record device provenance. Thread models and secure-storage branches remain in the codebase for future adaptation but are not part of the active validation flow. The earlier amendments remain as historical decisions.

## Amendment (2026-11-12): Schema v4 and direct-SDK commissioning

The active device-validation contract moved from schema version `3` to version `4`. The retired `commissioning_discovery` case and `commissioning_transport` report field are removed. The app no longer performs its own BLE or mDNS commissionee scan; it passes the raw onboarding payload directly to the Matter SDK, which performs commissionee discovery and commissioning. A commissioning failure is preserved and is not retried in the same Run.

The fixed matrix is now 11 tests, and the quick profile is a four-test iteration path. The report still requires a Wi-Fi `network_transport`, does not record device provenance, and describes the invalid-setup-passcode negative test as using a well-formed setup payload with a deliberately incorrect setup passcode and the same discriminator. The test app derives that negative-test payload locally and keeps it only in platform-secure storage. The earlier amendments remain as historical decisions.

## Amendment (2026-11-18): Eight-test matrix and operator-owned commissionee reset

At that time the fixed matrix contained 8 tests: 7 P0 tests, including the retired invalid-setup-passcode negative case, plus the P1 test `app_restart`. The `quick` profile contains 4 tests.

Runs are one-shot and interrupted Runs are never resumed. Every commissioned Run adds one fabric to the commissionee. The post-Run cleanup card purges stored Run secrets and records operator confirmation; it does not reset the commissionee or remove the fabric. A clean cycle therefore starts with an explicit commissionee factory reset and an open commissioning window.

The schema v4 artifact and source test catalog were authoritative until this schema v5 amendment.

## Amendment (2026-11-21): Schema v5 retires the invalid-setup-passcode case

The active device-validation contract moved from schema version `4` to version `5`. The invalid-setup-passcode negative case is removed from the fixed matrix because its second-commissioning-window workflow introduced a test-design dependency rather than a reliable cross-platform release signal. The current matrix contains 7 tests: 6 P0 tests plus the P1 `app_restart` test. The `quick` profile remains a four-test iteration path.

The v5 report schema requires exactly the 7 current test IDs, caps summary counts at 7, and rejects v4 evidence so stale eight-test reports cannot satisfy the release gate. The earlier amendments remain historical decisions.

## Related Documents

- [Device Validation](../device-validation.md)
- [Device Test Report Contract](../device-test-report.md)
- [Device Test Report Schema](../device-test-report.schema.json)
- [ADR 0005: Dart-Only CI and Pull Request Evidence](0005-dart-only-ci-and-pr-evidence.md)
