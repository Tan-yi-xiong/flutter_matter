# ZGMatter framework build

`flutter_matter` vendors an iPhoneOS arm64 `ZGMatter.framework` under
`ios/frameworks/ZGMatter.framework`. The framework is generated from the
official Project CHIP stack plus a small, reviewed set of ZG feature patches.
The pipeline lives in `ios/zgmatter/` so the plugin repository is the single
place to maintain the framework source inputs and build procedure.

## Source and layout

The build is pinned by `ios/zgmatter/UPSTREAM_SHA`. The current pin is the
official `connectedhomeip` `v1.6.1-branch` commit:

```text
da8f6a0bffb72ddcb6a0817df710270f1f59bc2c
```

The tool directory contains:

```text
ios/zgmatter/
├── UPSTREAM_SHA
├── build_zgmatter_framework.sh
├── rename_mtr_to_zgmtr.py
├── README.md
└── patches/
```

The six patches preserve the ZG feature contract that is not available through
the official public Objective-C API: subscription ID delivery, pre-encoded
batch attribute writes, subscription shutdown, raw TLV data, fabric index, and
commissioning-stage forwarding.

## Path contract

The official `connectedhomeip` checkout is an external input. It has no default
location and must be supplied explicitly:

```bash
export ZGMATTER_CONNECTEDHOMEIP_DIR=/absolute/path/to/connectedhomeip
```

or:

```bash
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip
```

The command-line argument wins when both are present. The script fails before
building if neither is set, or if the path is not a Git worktree.

Paths inside `ios/zgmatter/` are resolved relative to the script:

- `PATCHES_DIR=$SCRIPT_DIR/patches`
- `UPSTREAM_SHA_FILE=$SCRIPT_DIR/UPSTREAM_SHA`
- `RENAME_TOOL=$SCRIPT_DIR/rename_mtr_to_zgmtr.py`
- `PLUGIN_ROOT=$SCRIPT_DIR/../..`

The `flutter_matter` destination defaults to `$PLUGIN_ROOT`, but can be
overridden with `--flutter-dir` when running the script from another checkout.
The output root defaults to `${TMPDIR:-/tmp}/zgmatter-build` and can be
overridden with `--out` or `ZGMATTER_OUT_DIR`. Relative command-line paths are
resolved from the caller's working directory before the script changes
directories.

Dependency caching is optional. Pass `--deps-root` with an already
bootstrapped connectedhomeip checkout. When omitted, the script initializes
Darwin submodules and the Pigweed environment inside the generated worktree.
No implicit local dependency path is used.

## Prerequisites

- macOS with Xcode and the iPhoneOS SDK
- Python 3
- Git with submodule support
- CocoaPods 1.17 when validating the example workspace
- A local official `connectedhomeip` checkout containing the pinned SHA

The framework is physical-device arm64 only. The simulator is not supported.

## Build and validate

From the `flutter_matter` repository root:

```bash
export ZGMATTER_CONNECTEDHOMEIP_DIR=/absolute/path/to/connectedhomeip

# Validate without replacing the vendored framework.
ios/zgmatter/build_zgmatter_framework.sh --no-copy

# Build and copy the validated framework into ios/frameworks/.
ios/zgmatter/build_zgmatter_framework.sh
```

Useful options:

```bash
# Explicit output and dependency cache paths.
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip \
  --out "$TMPDIR/zgmatter-build" \
  --deps-root /absolute/path/to/bootstrapped-connectedhomeip

# Keep the generated source worktree after a failed patch.
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip \
  --keep-worktree

# Initialize dependencies from scratch when no cache exists.
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip \
  --bootstrap-deps
```

The build writes `build-info.txt`, `xcodebuild.log`, and symbol/header evidence
to the output directory. It verifies the arm64 Mach-O binary, the ZG public
methods and headers, `ZGCSRInfo`/`ZGAttestationInfo`, and the absence of the
legacy custom BLE classes.

## Updating upstream

1. Update `ios/zgmatter/UPSTREAM_SHA`.
2. Run the script with `--no-copy`.
3. If a patch fails `git apply --check`, use `--keep-worktree` and rebase the
   affected patch against the official `MTR`-named source.
4. Re-run all patch checks and the full framework validation.
5. Only then copy the verified framework into `ios/frameworks/ZGMatter.framework`.

A failed patch is expected when upstream changes the surrounding source. This
is a safety boundary: the script stops before producing a framework with a
silently missing feature.

## Release verification

After a framework build/copy:

```bash
cd example/ios
pod install
xcodebuild -quiet \
  -workspace Runner.xcworkspace \
  -scheme Runner \
  -configuration Debug \
  -sdk iphoneos \
  -destination 'generic/platform=iOS' \
  CODE_SIGNING_ALLOWED=NO CODE_SIGN_IDENTITY= build
```

Record the upstream SHA and framework binary SHA-256 from
`build-info.txt` in the release evidence. Do not publish a framework built from
an uncommitted upstream pin.

## Platform notes

- The plugin and example target iOS 16.1 or later.
- The vendored framework has no simulator slice; use a physical arm64 device or
  a no-codesign device build.
- The custom subscription-ID method uses the underlying iOS 17 subscription API
  availability even though the other ZG extensions retain their original
  availability annotations.
- The generated framework intentionally does not carry the legacy
  `ZGMTRBleManager` or `ZGMTRBlePlatformDelegate` overrides. Official Darwin
  BLE implementation files remain part of the upstream framework.
