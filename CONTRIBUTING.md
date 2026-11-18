# Contributing

Keep changes focused, preserve public contracts, and provide verification another reviewer can reproduce.

## Before you start

Use Flutter 3.41.0 from `.fvmrc`:

```sh
fvm flutter pub get
```

If FVM is unavailable, use Flutter 3.41.0 and replace `fvm flutter` with `flutter`.

Useful references:

- [Getting started](doc/getting-started.md)
- [Commissioning](doc/commissioning.md)
- [Device operations](doc/device-operations.md)
- [Architecture](ARCHITECTURE.md)
- [Public API](doc/public-api.md)
- [Platform support](doc/platform-support.md)
- [Device test app](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/device_test_app/README.md)
- [Device validation](doc/device-validation.md)
- [Device test report contract](doc/device-test-report.md)
- [Release process](doc/releasing.md)

## Common checks

| Change area | Minimum checks |
| --- | --- |
| Dart library | `fvm flutter analyze --no-fatal-infos --no-fatal-warnings` and `fvm flutter test` |
| Android example | `cd example && fvm flutter build apk --debug` |
| iOS example | `cd example && fvm flutter build ios --debug --no-codesign` on macOS |
| Device test app | `cd device_test_app && fvm flutter analyze --no-fatal-infos --no-fatal-warnings && fvm flutter test` |
| Package/release | `fvm dart pub publish --dry-run` and `doc/releasing.md` |
| Documentation | Markdown links, code fences, and `git diff --check` |

The example Android build requires the separately downloaded Google Home SDK:

```sh
export GOOGLE_MATTER_SDK_REPO=/absolute/path/to/home.android.sdk_1_11_1/repo
cd example
fvm flutter build apk --debug
```

Do not commit the SDK repository or generated build artifacts.

## CI boundary

The required `Dart check and tests` workflow resolves dependencies from `.fvmrc`, runs non-fatal Dart analysis, and runs the root `test/` suite. It does not compile native code, run device behavior, validate publication, or enforce formatting.

Native builds and Matter behavior belong in PR evidence. A green Dart gate proves only that the Dart layer passed.

## Public contracts

The only supported consumer import is:

```dart
import 'package:flutter_matter/flutter_matter.dart';
```

Direct `src/` imports are internal except in tests. When changing the public surface:

- Export new symbols from `lib/flutter_matter.dart`.
- Update [Public API](doc/public-api.md).
- Update `test/public_api_test.dart` when the export list changes.
- Update `test/method_channel_contract_test.dart` when URL construction or JSON envelopes change.
- Identify breaking changes and migration impact.

Export paths and core envelopes are automated; method-level compatibility still requires review.

## Device behavior

A change affects device behavior when it touches commissioning, BLE, discovery, Wi-Fi/Thread provisioning, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel behavior, or native Matter code.

For those changes:

1. Use a Matter On/Off commissionee.
2. Run the `full` device-test profile and produce schema v4 JSON plus generated Markdown.
3. Confirm the report commit matches the PR head.
4. Attach sanitized evidence.
5. Cover Android and physical iOS for shared behavior, or document the platform exception.

Do not retry a failed commissioning or P0 test in the same Run. Do not treat an example build or Dart test as device evidence.

## Pull requests

Fill out the repository PR template and include:

- the problem and expected behavior;
- affected platforms and compatibility impact;
- exact commands or scenarios with results;
- safe evidence links;
- untested behavior and remaining risk;
- documentation and changelog impact.

Use [the review checklist](doc/pr-review-checklist.md) for reviewer expectations. Never attach setup codes, onboarding payloads, Wi-Fi credentials, device identifiers, serial numbers, UDIDs, certificates, private keys, or raw private logs.

## Documentation

Repository documentation and review text are written in English. Use `README.md` as the landing page, `doc/getting-started.md` for the first successful integration, `doc/commissioning.md` and `doc/device-operations.md` for task guidance, and `doc/public-api.md`/`doc/platform-support.md` for reference material. For runnable examples, link to a specific file and symbol under `example/` instead of copying the full implementation. Update the relevant page or `CHANGELOG.md` when behavior, configuration, or public usage changes.
