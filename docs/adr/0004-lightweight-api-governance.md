# ADR 0004: Lightweight API Governance

- Status: Accepted
- Date: 2026-11-11

## Context

The plugin exposes a broad low-level surface, but the repository does not yet have an established API-diff pipeline, release automation, or stable native test harness. A heavyweight external API comparison tool would add maintenance cost before the public contract and release process are mature.

The highest immediate risks are accidental export changes and accidental changes to MethodChannel URL/JSON envelopes.

## Decision

Adopt lightweight API governance in the first engineering phase:

- Maintain a golden export-path test in `test/public_api_test.dart`.
- Maintain MethodChannel contract tests for URL construction, request parameters, result envelopes, and channel invocation.
- Maintain `docs/public-api.md` as the human-readable symbol inventory and compatibility policy.
- Require pull requests to describe public Dart API, MethodChannel, JSON, and compatibility impact.
- Use `docs/pr-review-checklist.md` for manual compatibility review.
- Do not add an external API-diff tool or automated native ABI comparison in this phase.

The tests are deliberately focused on high-value drift detection, not on generating a complete language-level API snapshot.

## Consequences

- Export changes are visible and testable without an external service.
- Wire-contract mistakes are caught for the covered paths.
- Method signature and default-value changes still require manual review.
- The approach can later be replaced or supplemented by an API-diff tool if release volume or compatibility risk justifies it.
- Any future upgrade must preserve the existing tests or explicitly migrate their coverage.
