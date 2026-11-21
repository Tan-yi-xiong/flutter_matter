# Pull request review checklist

Use the PR template for submitted evidence. Use [Contributing](../CONTRIBUTING.md), [Device validation](device-validation.md), and [Device test report contract](device-test-report.md) for the authoritative rules.

## Scope and verification

- [ ] The PR template is complete and the changed behavior matches the selected scope.
- [ ] Every check has `Passed`, `Failed`, or `Not run`; each `Not run` has a reason and residual risk.
- [ ] The evidence covers the changed code path, not only a neighboring build or test.
- [ ] A green Dart gate is not treated as proof of native compilation or device behavior.
- [ ] The report `plugin_commit`, when required, matches the PR head.

## Compatibility and platforms

- [ ] Exported Dart symbols, constructors, defaults, deprecations, and documented paths were reviewed.
- [ ] MethodChannel hosts, paths, arguments, envelopes, and callback semantics were reviewed.
- [ ] Public API and contract tests were updated where the exported or wire surface changed.
- [ ] Breaking changes identify versioning and migration impact.
- [ ] Shared behavior has Android and physical-iOS evidence; platform-specific changes justify the exception.
- [ ] iOS simulator results are not accepted as plugin evidence.

## Device evidence

- [ ] Device-behavior changes use the `full` profile, a Matter commissionee, and schema v5 JSON plus generated Markdown.
- [ ] The report records `network_transport: "wifi"`, vendor/product IDs, and no retired commissionee model, firmware, state-change, or commissioning-transport fields.
- [ ] All required P0 results are `passed`; any P1 failure has an explicit maintainer risk decision.
- [ ] Failed commissioning or P0 cases were not retried in the same Run.
- [ ] The Run starts from a factory-reset commissionee, and any remaining test fabric is handled before the next clean cycle.
- [ ] Attached reports and screenshots are sanitized; no credentials, serial numbers, UDIDs, setup payloads, certificates, private keys, or raw logs are present.

## Code, security, and documentation

- [ ] Native compile evidence is present when Kotlin, Objective-C, Swift, or bundled Matter inputs changed.
- [ ] Error-path changes include regression or negative-case evidence when practical and follow the [Error handling](error-handling.md) contract.
- [ ] Dart-facing errors and native logs do not include raw stack traces, setup payloads, credentials, certificates, private keys, or full request JSON.
- [ ] Workflow changes do not add unnecessary permissions, secrets, or unsafe triggers.
- [ ] Third-party code and binaries have a documented source or are otherwise reviewable.
- [ ] Public usage changes update `README.md`, the relevant `doc/` page, or `CHANGELOG.md`.
- [ ] All repository documentation and review text is in English.

## Merge gate

- [ ] Required evidence is present, current, and internally consistent.
- [ ] Untested behavior and accepted risk are explicitly recorded.
- [ ] No sensitive material is present in the PR body, comments, reports, or attachments.

Do not approve when required evidence is missing, stale, mismatched to the head, or contradicted by the implementation.
