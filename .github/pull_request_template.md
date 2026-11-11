## Summary

<!-- Describe the problem, the change, and the expected outcome. -->

## Scope

- [ ] Android
- [ ] iOS
- [ ] Both platforms
- [ ] Dart library only
- [ ] Example app only
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
build and manual demonstration target, not an automated test target.

| Check | Command or manual scenario | Platform / device | Result | Evidence | Not run reason |
| --- | --- | --- | --- | --- | --- |
| Dart analyze | `flutter analyze --no-fatal-infos --no-fatal-warnings` | Host |  |  |  |
| Plugin Dart tests | `flutter test` (`test/` only) | Host |  |  |  |
| Android debug build | `cd example && flutter build apk --debug` | Android build host |  |  |  |
| iOS no-codesign build | `cd example && flutter build ios --debug --no-codesign` | macOS |  |  |  |
| Manual functional test | Describe the exact scenario | Device and OS |  |  |  |
| Regression or negative scenario | Describe the exact scenario | Device and OS |  |  |  |

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

## Reviewer checklist

- [ ] The verification evidence covers the changed code path and affected platforms.
- [ ] Every `Not run` item has a reason and an explicit remaining-risk statement.
- [ ] Public API, MethodChannel, JSON, and compatibility impacts were reviewed.
- [ ] Android and iOS behavior were considered, with any platform exception justified.
- [ ] Documentation and changelog impact was reviewed.
- [ ] All added or modified documentation is English.
- [ ] A green CI result was not treated as proof of native compilation or device behavior.
