# Pull Request Review Checklist

This checklist applies to every pull request targeting `main`. The `Dart check and tests` workflow is the only required automated check, so the reviewer must explicitly validate the author's declared evidence.

## Before reviewing the code

- Confirm the PR template is fully completed.
- Identify the affected platforms, public interfaces, native code paths, and user-visible behavior.
- Check that the summary and scope agree with the actual diff.
- Treat an administrator bypass as a process exception, not as proof of correctness.
- Confirm the automated test scope is the root plugin `test/` suite only.

## Verification evidence

- Require an exact command or manual scenario for every reported test.
- Require the platform, device, OS, or toolchain used.
- Require a concrete result and safe evidence.
- Reject vague statements such as "tested locally" without supporting detail.
- Reject evidence that does not exercise the changed behavior.
- Reject blank rows and ensure every empty result is represented as `Not run`.
- For `Not run`, confirm that the reason is credible and that the remaining risk is stated.
- Decide explicitly whether the remaining risk is acceptable for this change.
- Do not accept `example/**` tests as automated evidence; the example is a build and manual demonstration target.

## Platform coverage

- Verify both Android and iOS when shared Dart, MethodChannel, JSON, callback, or native behavior changes.
- Verify Android-specific changes on Android.
- Verify iOS-specific changes on iOS.
- Confirm Android evidence states the JDK and Gradle/AGP context when the build toolchain is relevant.
- Confirm iOS evidence states the Xcode, CocoaPods, and physical arm64 device context when the build or behavior is relevant.
- Reject iOS simulator evidence as support for the current vendored Matter framework.
- Accept a single-platform review only when the PR clearly documents why the other platform is unaffected.

## Public API and compatibility

- Check changes to exported Dart symbols, constructors, methods, defaults, exported paths, and deprecations.
- Check MethodChannel host, path, argument, result, and callback formats.
- Verify that public API documentation is updated when the exported surface changes.
- Verify that `test/public_api_test.dart` is updated when the export-path golden changes.
- Verify that `test/method_channel_contract_test.dart` covers changed URL or envelope behavior.
- Identify breaking changes and require appropriate versioning and migration notes.
- Reject undocumented changes to existing wire formats or callback semantics.
- Remember that lightweight tests cover export paths and core envelopes; method-level compatibility remains a manual review responsibility.

## Native and functional behavior

- Confirm native compile checks were declared when Kotlin or Objective-C/Swift code changed.
- Confirm device or manual evidence was declared when commissioning, BLE, Wi-Fi, Thread, ICD, subscription, reconnect, or unpair behavior changed.
- Require regression or negative-case evidence where a change alters an error path.
- Record which scenarios remain unverified and whether that risk is acceptable.

## Documentation and changelog

- Confirm public usage changes are reflected in `README.md`, `docs/`, or `CHANGELOG.md` when appropriate.
- Confirm all repository documentation, workflow comments, and review guidance are written in English.
- Preserve non-English text only when it is a required user-facing string or an exact quoted reference.

## Security

- Check that logs, screenshots, recordings, and evidence links contain no credentials, tokens, private keys, or private provisioning data.
- Confirm workflow changes do not introduce write permissions, secrets, or unsafe `pull_request_target` usage.
- Confirm third-party code and binaries have a documented source or are otherwise reviewable.

## Approval and merge

- Do not approve when required evidence is missing or does not match the change.
- Do not treat a green `Dart check and tests` result as proof that Android or iOS native code builds.
- Request additional evidence when the remaining risk is not acceptable.
- Confirm the PR scope, verification, documentation, and compatibility statements are internally consistent before approval.

## Related documents

- [Contributing](../CONTRIBUTING.md)
- [Architecture](../ARCHITECTURE.md)
- [Public API](public-api.md)
- [Platform support](platform-support.md)
- [ADR 0005: Dart-only CI and PR evidence](adr/0005-dart-only-ci-and-pr-evidence.md)

## Insufficient evidence examples

- "Works on my machine" with no command or result.
- A Dart test result used to claim Android or iOS native compilation.
- A successful Android build used to claim that an iOS behavior works.
- A successful example Dart test used as native or functional evidence.
- `Not run` with no explanation.
- A screenshot that hides the relevant error or device state.
- A public API change without a compatibility section.
