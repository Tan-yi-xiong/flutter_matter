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

## Related Documents

- [Device Validation](../device-validation.md)
- [Device Test Report Contract](../device-test-report.md)
- [Device Test Report Schema](../device-test-report.schema.json)
- [ADR 0005: Dart-Only CI and Pull Request Evidence](0005-dart-only-ci-and-pr-evidence.md)
