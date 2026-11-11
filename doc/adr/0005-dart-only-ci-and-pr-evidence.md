# ADR 0005: Dart-Only CI and Pull Request Evidence

- Status: Accepted
- Date: 2026-11-11

## Context

The plugin depends on native Matter SDKs and physical-device behavior. A hosted Ubuntu workflow cannot build the iOS framework or execute a meaningful Matter commissioning test. Adding native build and device infrastructure to required CI now would make the merge gate slow, fragile, and dependent on hardware capacity.

The project still needs a fast signal for Dart compilation and the supported Dart-layer test suite.

## Decision

The required `Dart check and tests` workflow:

- Runs on Ubuntu.
- Installs the Flutter version from `.fvmrc`.
- Resolves plugin dependencies.
- Runs `flutter analyze --no-fatal-infos --no-fatal-warnings`.
- Runs the plugin root test suite with `flutter test`.

The workflow does not run example tests, Android or iOS native builds, native unit tests, integration tests, device tests, package publication checks, or formatting checks.

Automated tests cover `test/**/*_test.dart` at the plugin root only. `example/**` is a build and manual demonstration target and is never an automated test target.

Every pull request must provide evidence in the repository template for each applicable row:

- Dart analyze.
- Plugin Dart tests.
- Android debug build.
- iOS device/no-codesign build.
- Manual functional scenario.
- Regression or negative scenario.

A row may be marked `Not run` only with a reason and an explicit statement of residual risk. A reviewer must decide whether that risk is acceptable.

`main` requires a pull request and the `Dart check and tests` status check. Repository administrators may bypass the ruleset in an emergency, but bypass does not remove the evidence obligation.

## Consequences

- The required gate is fast and focused on Dart compilation and tests.
- A green check does not prove that Android or iOS native code builds, that the package is publishable, or that a physical device works.
- Reviewers must inspect declared build/manual evidence rather than treating CI as a complete verification system.
- Example tests are not a supported contribution target; use example builds and device scenarios instead.
- Native or self-hosted runners can be added later through a new decision without coupling that infrastructure to the first-phase gate.
