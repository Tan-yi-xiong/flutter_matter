# Release process

Releases are source-only GitHub Releases. Creating a tag validates the exact commit, generates a deterministic source archive and checksum, and creates a GitHub Release from `CHANGELOG.md`. Publishing to pub.dev remains a manual maintainer action.

## Release contract

- Tags use stable `vX.Y.Z` names; pre-release suffixes are not supported.
- `pubspec.yaml` and the matching `CHANGELOG.md` heading use the same `X.Y.Z`.
- Release notes are the content under the exact `## X.Y.Z` heading and stop at the next level-two heading.
- GitHub Releases contain `flutter_matter-X.Y.Z.tar.gz` and its `.sha256` checksum.
- The workflow does not publish APKs, IPAs, framework archives, or pub.dev packages.

## Prepare the release

1. Choose the version using the [public API versioning policy](public-api.md#versioning-and-deprecation).
2. Set the version in `pubspec.yaml`.
3. Move relevant `Unreleased` entries under a new `## X.Y.Z` heading in `CHANGELOG.md`.
4. Update public API, platform, architecture, and migration documentation.
5. Confirm all new or changed documentation is in English.
6. Merge the release-preparation pull request into `main`; do not tag a pull-request branch.

## Device validation

The release-preparation pull request is the durable record of stable-release device validation. It must include separate reports for Android and physical iOS against the release-candidate commit.

Each report must:

- use schema version 4 and include `device-test-report.json` plus its generated Markdown summary;
- identify the exact candidate commit in `plugin_commit`;
- contain one complete clean P0 cycle;
- use a Matter On/Off commissionee and record `network_transport: "wifi"`;
- preserve failed results instead of retrying a failed commissioning or P0 within the same Run;
- include P1 results and reasons for any `not_run` entry;
- contain no device identifiers, provisioning secrets, certificates, private keys, or raw logs.

Factory-reset the commissionee before each clean cycle. A completed Run leaves a test fabric behind; the app's post-Run cleanup card only purges Run secrets and records operator confirmation, so it is not a substitute for resetting the commissionee.

Do not tag a stable release when a report is missing, stale, failed, not run, or produced from the wrong commit. Device validation is not run in hosted CI.

## Local verification

From the repository root:

```sh
fvm flutter pub get
fvm flutter analyze --no-fatal-infos --no-fatal-warnings
fvm flutter test
fvm dart pub publish --dry-run
fvm dart run tool/release.dart validate --tag vX.Y.Z
fvm dart run tool/release.dart notes --version X.Y.Z
git diff --check
git status --short
```

`dart pub publish --dry-run` must exit with 0 warnings. The release tool must report the expected archive name, and `notes` must print only the matching release section.

## GitHub preflight

After the release commit is on `main`, run the workflow from the default branch:

```sh
gh workflow run release.yml --ref main
gh run list --workflow release.yml --limit 1
```

A manual dispatch stops after validation and archive generation. Confirm the `Validate release` job passes and the source checksum exists. It does not create a GitHub Release.

## Create the release

Confirm the device-validation reports are present and still accessible, then create an annotated tag from the release commit:

```sh
git switch main
git pull --ff-only
git tag -a vX.Y.Z -m "flutter_matter X.Y.Z"
git push origin vX.Y.Z
```

The tag runs validation and creates the GitHub Release. Do not move or reuse a tag. If the Release already exists, resolve its state manually instead of overwriting it.

## Publish to pub.dev

After verifying the GitHub Release, publish the tagged source:

```sh
git fetch --tags
git switch --detach vX.Y.Z
fvm flutter pub get
fvm dart pub publish
```

Authenticate as a package publisher and complete the pub.dev confirmation flow. Verify the published version and changelog. Never reuse or move a version after pub.dev accepts it.

## Failures

- If validation fails before GitHub Release creation, fix through a new pull request and rerun only while the tag still points to the intended commit.
- If a GitHub Release exists with incomplete assets or notes, repair it manually; do not replace a published release silently.
- If pub.dev rejects or fails publication, keep the GitHub Release immutable and use a new version unless pub.dev confirms nothing was accepted.
- Security issues follow [SECURITY.md](../SECURITY.md), not the public release checklist.
