# Contributing

Thank you for contributing to `flutter_matter`. This document defines the minimum
verification and evidence expected for every pull request.

## CI scope

The required `Dart check and tests` workflow verifies:

- Dart dependency resolution.
- Dart static analysis errors.
- Root plugin Dart tests when `test/**/*_test.dart` files exist.
- Example Dart tests under `example/test/`.

The workflow does not compile Android or iOS native code, run native unit tests,
run integration or device tests, validate package publication, or check
formatting. Passing CI therefore means that Dart analysis and Dart tests passed;
it does not prove that native builds or real-device behavior are correct.

## Local prerequisites

The repository uses Flutter `3.41.0`. Prefer FVM when it is configured:

```bash
fvm flutter pub get
cd example
fvm flutter pub get
```

If FVM is unavailable, use a Flutter SDK at the same version and replace
`fvm flutter` with `flutter`.

## Required verification

Run the checks that apply to the files and behavior changed by the pull request.
The following commands are the baseline expectations.

Dart analysis and tests:

```bash
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
cd example
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

The iOS check intentionally uses a device build because the vendored Matter
framework currently contains an iPhoneOS slice only.

## Pull request evidence

Every pull request must use the repository PR template. For each verification
row, provide:

- The exact command or manual scenario.
- The platform, device, OS, or toolchain used.
- The result: `Passed`, `Failed`, or `Not run`.
- A link to a workflow run, log, screenshot, recording, or other safe evidence.
- A reason and risk statement when the result is `Not run`.

Do not use vague statements such as "tested locally" without a command, result,
or affected-platform explanation. Do not include credentials, tokens, private
keys, personal provisioning data, or unsanitized private logs.

A check may be marked `Not run` when it does not apply or when the required
hardware or toolchain is unavailable. The author must explain why it was not
run, what remains unverified, and what risk the reviewer is accepting.

## Platform expectations

This package exposes both Android and iOS implementations. A change to a shared
Dart API, MethodChannel route, JSON shape, callback contract, or native behavior
must declare verification for both platforms unless the change is explicitly
documented as platform-specific.

For changes involving commissioning or device behavior, describe the relevant
manual scenarios, including where applicable:

- BLE commissioning.
- Wi-Fi commissioning, including open Wi-Fi.
- Thread credentials.
- ICD registration.
- Attribute read, write, invoke, and subscribe.
- Reconnect, disconnect, and unpair behavior.

## Public API and compatibility

Call out any change to exported Dart types, method signatures, default values,
MethodChannel names, URL hosts, paths, or JSON envelopes. Breaking changes must
be identified as such and include the intended versioning or migration impact.

## Review and merge

Reviewers must use `docs/pr-review-checklist.md`. A green CI result is necessary
but not sufficient for approval. Reviewers must verify that the declared
evidence covers the changed code path and affected platforms.

The `main` branch requires a pull request and the `Dart check and tests` status
check. Repository administrators retain an emergency bypass. Bypass use does not
remove the obligation to document verification.

## Documentation language

All repository documentation, workflow comments, pull request templates, and
review guidance must be written in English. Preserve non-English text only when
it is a required user-facing string or an exact quoted reference.

Update `README.md` or `CHANGELOG.md` when behavior, configuration, or public
usage changes.
