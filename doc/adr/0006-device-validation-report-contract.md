# ADR 0006: Device Validation Report Contract

- Status: Accepted
- Date: 2026-11-11

## Context

`flutter_matter` depends on native Matter behavior that the required Dart CI gate cannot exercise. ADR 0005 established manual evidence in pull requests, but it did not define how device results should be recorded consistently across Android, physical iOS, real Matter hardware, and virtual commissionees.

The repository also expects the example application to evolve into a dedicated device-test app. That app should emit a reviewable result instead of requiring contributors to reconstruct ad hoc commands and tables for every pull request.

## Decision

Device validation follows this order and contract:

- Use a qualified real Matter On/Off device first.
- Use the Project CHIP Android Virtual Device App only when a qualified real device is unavailable or does not meet the required capabilities.
- Test both Android and physical iOS controllers against the selected commissionee when a change affects shared behavior.
- Define a versioned JSON report schema and a Markdown summary generated from the same result data.
- Require a device-behavior pull request to include the affected platform report and sanitized attachments.
- Require a stable release-preparation pull request to include one clean P0 cycle for Android and one clean P0 cycle for iOS against the release candidate.
- Keep evidence submission manual through pull request comments and attachments.

The initial report schema version is `1`. Fixed P0 cases cover build/install, BLE discovery, BLE commissioning, operational connection, On/Off invocation, On/Off subscription, and NodeLabel persistence. P1 and P2 results remain in the report but do not replace the required P0 result.

The future dedicated device-test app owns report generation and self-validation. This repository phase defines the contract and documentation only; it does not introduce a self-hosted runner, an Actions hardware job, or an executable report validator.

## Consequences

- Contributors have one stable format for device evidence across current manual runs and the future test app.
- Reviewers can compare Android and iOS results without interpreting unrelated free-form reports.
- Stable releases remain manual and depend on maintainer review of real-device or virtual-device evidence.
- A stale report, missing platform result, or mismatched commit is treated as unverified.
- Sensitive provisioning data and device identifiers must remain outside the report and public attachments.
- Implementing the future app must conform to the schema instead of inventing a separate reporting format.

## Related Documents

- [Device Validation](../device-validation.md)
- [Device Test Report Contract](../device-test-report.md)
- [Device Test Report Schema](../device-test-report.schema.json)
- [ADR 0005: Dart-Only CI and Pull Request Evidence](0005-dart-only-ci-and-pr-evidence.md)
