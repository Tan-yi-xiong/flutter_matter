# Pull request

## Summary

<!-- What changed, why, and what outcome should reviewers expect? -->

## Scope

- [ ] Android
- [ ] iOS
- [ ] Both Android and iOS
- [ ] Dart library
- [ ] Example app
- [ ] Device test app or Agent tooling
- [ ] Documentation, CI, or release metadata

## Compatibility

- [ ] No public Dart, MethodChannel, JSON, or callback contract change
- [ ] Public Dart API change
- [ ] MethodChannel or wire-format change
- [ ] Breaking change

<!-- Describe migration, versioning, and compatibility impact. -->

## Verification

Use `Passed`, `Failed`, or `Not run`. For `Not run`, include the reason and remaining risk. Link reproducible evidence when available. Exact commands and toolchains are in [CONTRIBUTING](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/CONTRIBUTING.md).

| Check                         | Result | Evidence or notes |
| ----------------------------- | ------ | ----------------- |
| Dart analyze and plugin tests |        |                   |
| Android example build         |        |                   |
| iOS no-codesign build         |        |                   |
| Device test app checks/build  |        |                   |
| Manual or device scenario     |        |                   |

**Toolchain and device:**

- [ ] The selected evidence covers the changed code path and affected platforms.
- [ ] Evidence links contain no credentials, device identifiers, or raw private logs.

## Device validation

<!-- Required for commissioning, BLE, networking, controller lifecycle, Interaction Model, callbacks, MethodChannel, or native Matter changes. -->

- [ ] Not applicable; explain why below
- [ ] `full` profile used with a Matter commissionee
- [ ] Schema v4 report matches the current PR head
- [ ] Android report attached/linked
- [ ] iOS report attached/linked
- [ ] Shared behavior covered on both platforms, or the exception is explained
- [ ] Sanitized JSON is attached or linked
- [ ] Optional screenshots are sanitized

**Reason or platform exception:**

**Plugin commit under test:**

**Android result and evidence:**

**iOS result and evidence:**

<details>
<summary>Generated device-test-report.md</summary>

```markdown
Paste the generated report here.
```

</details>

## Risks

<!-- List affected behavior that was not verified and the risk reviewers must accept. -->

## Documentation and changelog

- [ ] Documentation updated, or not required
- [ ] `CHANGELOG.md` updated, or not required
