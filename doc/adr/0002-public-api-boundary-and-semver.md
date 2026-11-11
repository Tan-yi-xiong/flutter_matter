# ADR 0002: Public API Boundary and Semantic Versioning

- Status: Accepted
- Date: 2026-11-11

## Context

The package exports many low-level Matter types because callers need paths, state models, TLV values, and callback interfaces. The `src/` directory also contains implementation classes that are used by tests but are not intended as consumer imports. Without an explicit boundary, accidental export changes and direct `src/` imports become undocumented compatibility risks.

## Decision

- The only supported consumer import is `package:flutter_matter/flutter_matter.dart`.
- Every top-level symbol exported by that library is public API and is listed in `doc/public-api.md`.
- Direct imports under `package:flutter_matter/src/...` are internal implementation paths. Tests may use them; application code must not.
- Public exports follow Semantic Versioning.
- Before `1.0.0`, a breaking change may be released in a minor version, but it must be explicitly marked in the pull request and `CHANGELOG.md` and include migration guidance.
- After `1.0.0`, breaking public API changes require a major version.
- Deprecated APIs use Dart's `@Deprecated` annotation and include the replacement. Keep deprecated APIs for at least one minor release when technically feasible.
- MethodChannel URLs, JSON envelopes, and callback semantics are separate compatibility surfaces and require the same review as Dart API changes.
- New public symbols must be exported from `lib/flutter_matter.dart` and added to the public API documentation and export golden test.

The project does not introduce an external API-diff service in this phase. The export list is guarded by `test/public_api_test.dart`, and reviewers inspect signatures, defaults, and wire behavior manually.

## Consequences

- Removing or adding an exported path without updating the golden test fails the root test suite.
- The golden test detects export-list drift, but it does not prove that every method signature or default value remained compatible.
- Public API documentation must be updated with any supported surface change.
- Consumers get a stable import boundary and explicit migration expectations.
