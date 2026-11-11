## Summary

<!-- Describe the problem, the change, and the expected outcome. -->

## Scope

- [ ] Android
- [ ] iOS
- [ ] Both platforms
- [ ] Dart library only
- [ ] Example app only
- [ ] Device test app or Agent tooling
- [ ] Documentation or CI only

## Public API and compatibility impact

- [ ] No public Dart API or MethodChannel contract changes
- [ ] Public Dart API changed
- [ ] Native plugin interface changed
- [ ] MethodChannel URL or JSON envelope changed
- [ ] Breaking change

<!-- Describe compatibility, migration, or versioning impact for every selected item above. -->

## Verification Evidence

Use `Passed`, `Failed`, or `Not run` in the result column. Do not delete rows that
do not apply. For `Not run`, explain the reason and the remaining risk. Include
safe evidence links or summaries; never include credentials or private keys.

Automated tests cover the plugin root `test/` suite only. `example/**` is a
build and manual demonstration target, not an automated test target. Device test
app checks are local and are not part of required CI.

| Check | Command or manual scenario | Platform / device | Result | Evidence | Not run reason |
| --- | --- | --- | --- | --- | --- |
| Dart analyze | `flutter analyze --no-fatal-infos --no-fatal-warnings` | Host |  |  |  |
| Plugin Dart tests | `flutter test` (`test/` only) | Host |  |  |  |
| Android debug build | `cd example && flutter build apk --debug` | Android build host |  |  |  |
| iOS no-codesign build | `cd example && flutter build ios --debug --no-codesign` | macOS |  |  |  |
| Device test app analyze/tests | `cd device_test_app && flutter analyze --no-fatal-infos --no-fatal-warnings && flutter test` | Host |  |  |  |
| Device test app Android build | `fvm dart run tool/device_test_app.dart build-apk` | Android build host |  |  |  |
| Device test app iOS build | `fvm dart run tool/device_test_app.dart build-ios` | macOS |  |  |  |
| Manual functional test | Describe the exact scenario | Device and OS |  |  |  |
| Regression or negative scenario | Describe the exact scenario | Device and OS |  |  |  |

## Device Validation

<!-- Required for changes affecting commissioning, BLE, networking, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel behavior, or native Matter code. Follow doc/device-validation.md and doc/device-test-report.md. Mark Not applicable only for changes that cannot affect device behavior. -->

- [ ] Not applicable; explain why in the field below
- [ ] Qualified real Matter device used
- [ ] Wi-Fi/IP commissioning used; no BLE discovery or GATT commissioning

**Applicability or not-applicable reason:**

**Plugin commit under test:**

**Test app version and commit, or interim manual report:**

**Commissionee model, firmware, and state-change method:**

**Commissioning transport and network transport:** `<ip / wifi>`

**Controller and commissionee confirmed on the same trusted LAN:** `<Yes|No>`

**Android result:** `<Passed|Failed|Not run>` — `<report and attachment links>`

**iOS result:** `<Passed|Failed|Not run>` — `<report and attachment links>`

**Virtual commissionee use:** `Not used` — virtual commissionees are not supported; every device run, including quick iteration, uses real Matter hardware.

<details>
<summary>Generated Markdown device-test-report summary</summary>

```markdown
Paste `device-test-report.md` here.
```

</details>

- [ ] The report commit matches the current PR head.
- [ ] Sanitized JSON is attached in a PR comment and linked above.
- [ ] Any screenshots attached manually are sanitized and linked above.
- [ ] Both Android and iOS reports are present for shared behavior, or the platform exception is explained.
- [ ] The reports and attachments contain no device identifiers, provisioning secrets, certificates, keys, or raw logs.

## Untested areas and risks

<!-- List every affected behavior that was not verified and the risk reviewers must accept. -->

## Documentation and changelog

- [ ] Documentation updated, or the change does not require documentation updates
- [ ] `CHANGELOG.md` updated, or the change does not require a changelog entry

## Author checklist

- [ ] I ran every applicable check listed above and reported the actual result.
- [ ] I did not leave any verification field blank.
- [ ] I identified all affected platforms and native behavior.
- [ ] I did not run or report `example/**` as an automated test target.
- [ ] I described public API and compatibility impact.
- [ ] I included no credentials, tokens, private keys, or unsanitized private logs.
- [ ] I reviewed all added or modified documentation and confirmed it is English.
- [ ] For device-behavior changes, I supplied full-profile reports for every affected platform using the repository report contract.
- [ ] Agent-driven runs used `$flutter-matter-device-test` and requested a user choice when multiple phones were connected.

## Reviewer checklist

- [ ] The verification evidence covers the changed code path and affected platforms.
- [ ] Every `Not run` item has a reason and an explicit remaining-risk statement.
- [ ] Public API, MethodChannel, JSON, and compatibility impacts were reviewed.
- [ ] Android and iOS behavior were considered, with any platform exception justified.
- [ ] Documentation and changelog impact was reviewed.
- [ ] All added or modified documentation is English.
- [ ] A green CI result was not treated as proof of native compilation or device behavior.
- [ ] Device-behavior evidence uses the versioned report contract, matches the PR head, and covers every affected platform.
- [ ] No P0 failure was retried in the same Run to manufacture a green result.
- [ ] Formal evidence used a qualified real Matter device over Wi-Fi/IP commissioning without BLE discovery or GATT commissioning.
- [ ] Attached reports and screenshots contain no credentials, device identifiers, provisioning secrets, certificates, keys, or raw logs.
