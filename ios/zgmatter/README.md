# ZGMatter framework build tools

This directory contains the reproducible build pipeline for the vendored
`ios/frameworks/ZGMatter.framework`. The framework is generated from the pinned
official `connectedhomeip` commit in [`UPSTREAM_SHA`](UPSTREAM_SHA), with six
small feature patches and a mechanical `MTR`/`Matter` to `ZGMTR`/`ZGMatter`
rename applied in a clean detached worktree.

## Layout

```text
ios/zgmatter/
├── UPSTREAM_SHA
├── build_zgmatter_framework.sh
├── rename_mtr_to_zgmtr.py
└── patches/
```

## Prerequisites

- macOS with Xcode and the iPhoneOS SDK
- CocoaPods when validating the plugin through the example workspace
- Python 3 for the rename tool
- A local official `connectedhomeip` checkout containing the pinned commit

The `connectedhomeip` checkout is an external input and has no default
location. Pass it with `--connectedhomeip-dir` or set
`ZGMATTER_CONNECTEDHOMEIP_DIR`. Paths inside this tool directory are resolved
relative to the script and never use a machine-specific default.

## Build

From the `flutter_matter` repository root:

```bash
export ZGMATTER_CONNECTEDHOMEIP_DIR=/absolute/path/to/connectedhomeip
ios/zgmatter/build_zgmatter_framework.sh
```

Or pass the checkout explicitly:

```bash
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip
```

The script creates a temporary clean worktree, checks every patch with
`git apply --check`, applies the patches, performs the rename, builds an
iPhoneOS arm64 framework, validates the expected symbols and headers, and
copies the result into `ios/frameworks/ZGMatter.framework`.

Common variants:

```bash
# Validate without replacing the vendored framework.
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip \
  --no-copy

# Reuse an already bootstrapped dependency checkout.
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip \
  --deps-root /absolute/path/to/bootstrapped-connectedhomeip

# Keep the generated worktree for patch debugging.
ios/zgmatter/build_zgmatter_framework.sh \
  --connectedhomeip-dir /absolute/path/to/connectedhomeip \
  --keep-worktree
```

Use `--bootstrap-deps` on a clean connectedhomeip checkout when no dependency
cache is available.

## Updating upstream

1. Update `UPSTREAM_SHA`.
2. Run with `--no-copy` first.
3. If a patch fails, inspect the retained worktree and rebase the affected
   patch against the official `MTR`-named source.
4. Re-run the full validation before copying the framework into
   `ios/frameworks/ZGMatter.framework`.

A patch failure is intentional fail-fast behavior: the script stops instead of
silently producing a framework with missing ZG functionality.

See [`../../doc/zgmatter-build.md`](../../doc/zgmatter-build.md) for the full
maintainer guide and validation evidence.
