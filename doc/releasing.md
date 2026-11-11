# Release Process

This repository produces source-only GitHub Releases and keeps pub.dev publication as an explicit maintainer action. The release workflow validates the exact commit, creates a source archive and checksum, and records release notes from `CHANGELOG.md`.

## Release Contract

- Release tags use stable `vX.Y.Z` names only. Pre-release suffixes are not supported.
- `pubspec.yaml` version and the matching `CHANGELOG.md` heading must use the same `X.Y.Z` version.
- The CHANGELOG heading must be exactly `## X.Y.Z`; the release notes end at the next level-two heading.
- GitHub Releases contain `flutter_matter-X.Y.Z.tar.gz` and its `.sha256` checksum.
- No APK, IPA, framework archive, or other build artifact is published.
- The workflow never publishes to pub.dev and never needs a pub.dev token.

## Prepare the Release Commit

1. Choose the version according to the repository's semantic-versioning policy.
2. Set the exact version in `pubspec.yaml`.
3. Move the relevant `Unreleased` entries into a new `## X.Y.Z` section in `CHANGELOG.md`.
4. Update platform, API, architecture, and migration documentation required by the change.
5. Confirm every new or changed documentation file is written in English.
6. Open and merge a pull request into `main`; do not tag a pull-request branch.

## Device Validation Before Tagging

The release-preparation pull request is also the durable record for stable-release device validation. It must include separate Android and physical iOS reports against the release-candidate commit.

Each report must:

- Conform to schema version `1` and provide both `device-test-report.json` and its generated Markdown summary.
- Identify an exact `plugin_commit` equal to the candidate commit.
- Cover one complete clean P0 cycle for the controller platform.
- Use a qualified real Matter On/Off device first, or the Android Virtual Device App fallback with a documented reason.
- Include optional sanitized screenshots or other manually captured bounded evidence; the app itself emits JSON and Markdown only.
- Record P1 and P2 results, including reasons for `not_run` entries and any accepted P2 failures.

Both platform reports must show every required P0 case as `passed`. Do not create a stable tag when a report is missing, stale, failed, not run, mixed between real and virtual commissionees, or missing a clean-cycle statement.

The repository does not run device validation in CI and does not use a self-hosted hardware runner for this process.

## Local Verification

Run from the repository root:

```bash
fvm flutter pub get
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
fvm dart pub publish --dry-run
fvm dart run tool/release.dart validate --tag vX.Y.Z
fvm dart run tool/release.dart notes --version X.Y.Z
git diff --check
git status --short
```

`dart pub publish --dry-run` must exit successfully without warnings. `tool/release.dart validate` must report the expected archive name, and `notes` must print only the matching release section.

## GitHub Preflight

After the release commit is on `main`, run the workflow manually from the default branch:

```bash
gh workflow run release.yml --ref main
gh run list --workflow release.yml --limit 1
```

A manual dispatch stops after validation and archive generation. It does not create a GitHub Release. Inspect the `Validate release` job and its summary, and confirm the source archive checksum is present.

## Create the Release

Before tagging, confirm the device-validation requirements above are satisfied in the release-preparation pull request and that the attached evidence is still accessible.

Use the merge commit on `main` and create an annotated tag:

```bash
git switch main
git pull --ff-only
git tag -a vX.Y.Z -m "flutter_matter X.Y.Z"
git push origin vX.Y.Z
```

The tag runs the same validation and then creates the GitHub Release with the CHANGELOG notes, source archive, and checksum. A rerun fails if the Release already exists; do not overwrite or reuse a published release. Resolve the existing release state manually before retrying.

## Publish to pub.dev

After the GitHub Release is verified, publish the exact tagged source manually:

```bash
git fetch --tags
git switch --detach vX.Y.Z
fvm flutter pub get
fvm dart pub publish
```

Authenticate as a package publisher and complete the pub.dev confirmation flow. Verify the published version and changelog on `https://pub.dev/packages/flutter_matter`.

Never reuse or move a version after it has been published to pub.dev. If publication fails before the server accepts the archive, correct the issue and use a new version rather than replacing a published tag.

## Failure Handling

- If validation fails before the GitHub Release is created, fix the issue through a new pull request and rerun the workflow on the same tag only when the tag still points to the intended commit.
- If the GitHub Release exists but assets or notes are incomplete, verify and repair it manually; do not silently replace a published release.
- If pub.dev publication fails, keep the GitHub Release immutable and follow the new-version path unless pub.dev confirms that nothing was accepted.
- Security issues must follow [`SECURITY.md`](../SECURITY.md), not the public release checklist.
- Third-party licensing obligations are documented in [`THIRD_PARTY_NOTICES.md`](../THIRD_PARTY_NOTICES.md).
