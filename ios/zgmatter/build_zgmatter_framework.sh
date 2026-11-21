#!/bin/bash
#
# Build a ZGMatter.framework from the pinned official connectedhomeip commit.
#
# The source tree is never hand-edited in this repository.  For every build we:
#   1. create a clean detached worktree at UPSTREAM_SHA,
#   2. apply the small feature patches in ios/zgmatter/patches,
#   3. mechanically rename the Darwin framework's public API/products,
#   4. build with the official Xcode project,
#   5. validate the custom API and copy the framework into flutter_matter.
#
# Usage:
#   ios/zgmatter/build_zgmatter_framework.sh [options]
#
# Options:
#   --connectedhomeip-dir DIR  Official connectedhomeip checkout. Required
#                              unless ZGMATTER_CONNECTEDHOMEIP_DIR is set.
#   --out DIR                  Build root (default: ${TMPDIR:-/tmp}/zgmatter-build)
#   --deps-root DIR            Bootstrapped connectedhomeip tree used as a
#                              dependency cache. If omitted, dependencies are
#                              initialized in the generated worktree.
#   --flutter-dir DIR          flutter_matter checkout to update (default:
#                              the checkout containing this script)
#   --no-copy                  Do not copy the built framework into flutter_matter
#   --keep-worktree            Keep the generated upstream worktree after the build
#   --bootstrap-deps           Initialize dependencies in the generated worktree
#                              even when a dependency cache is available
#   -h, --help                 Show this help
#
# Environment overrides:
#   ZGMATTER_CONNECTEDHOMEIP_DIR  Official connectedhomeip checkout (required
#                                 unless --connectedhomeip-dir is passed)
#   ZGMATTER_OUT_DIR              Build root override
#   ZGMATTER_UPSTREAM_REMOTE      Official repository URL
#   ZGMATTER_DEPLOYMENT_TARGET    iOS deployment target (default: 14.0)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PLUGIN_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PATCHES_DIR="$SCRIPT_DIR/patches"
UPSTREAM_SHA_FILE="$SCRIPT_DIR/UPSTREAM_SHA"
RENAME_TOOL="$SCRIPT_DIR/rename_mtr_to_zgmtr.py"

UPSTREAM_REMOTE="${ZGMATTER_UPSTREAM_REMOTE:-https://github.com/project-chip/connectedhomeip.git}"
DEPLOYMENT_TARGET="${ZGMATTER_DEPLOYMENT_TARGET:-14.0}"
CONNECTEDHOMEIP_DIR="${ZGMATTER_CONNECTEDHOMEIP_DIR:-}"
OUT_DIR="${ZGMATTER_OUT_DIR:-${TMPDIR:-/tmp}/zgmatter-build}"
DEPS_ROOT=""
FLUTTER_DIR="$PLUGIN_ROOT"
COPY_TO_FLUTTER=1
KEEP_WORKTREE=0
BOOTSTRAP_DEPS=0

# Modules selected by upstream's `checkout_submodules.py --platform darwin`.
# They are also the dependency roots we can reuse from an existing checkout.
DARWIN_SUBMODULES=(
  examples/common/QRCode/repo
  third_party/abseil-cpp/src
  third_party/boringssl/repo/src
  third_party/editline/repo
  third_party/fuzztest
  third_party/googletest
  third_party/jsoncpp/repo
  third_party/libdatachannel/repo
  third_party/libtrustymatter/repo
  third_party/libwebsockets/repo
  third_party/mbedtls/repo
  third_party/miniaudio/repo
  third_party/nanopb/repo
  third_party/nlassert/repo
  third_party/nlio/repo
  third_party/openthread/repo
  third_party/perfetto/repo
  third_party/pigweed/repo
  third_party/uriparser/repo
)

usage() {
  awk 'NR > 1 { if ($0 == "set -euo pipefail") exit; sub(/^# ?/, ""); print }' "$0"
}

require_value() {
  if [[ $# -lt 2 ]]; then
    echo "ERROR: $1 requires a value" >&2
    usage >&2
    exit 2
  fi
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --connectedhomeip-dir)
      require_value "$@"
      CONNECTEDHOMEIP_DIR="$2"
      shift 2
      ;;
    --out)
      require_value "$@"
      OUT_DIR="$2"
      shift 2
      ;;
    --deps-root)
      require_value "$@"
      DEPS_ROOT="$2"
      shift 2
      ;;
    --flutter-dir)
      require_value "$@"
      FLUTTER_DIR="$2"
      shift 2
      ;;
    --no-copy)
      COPY_TO_FLUTTER=0
      shift
      ;;
    --keep-worktree)
      KEEP_WORKTREE=1
      shift
      ;;
    --bootstrap-deps)
      BOOTSTRAP_DEPS=1
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage >&2
      exit 2
      ;;
  esac
done

if [[ -z "$CONNECTEDHOMEIP_DIR" ]]; then
  echo "ERROR: set --connectedhomeip-dir or ZGMATTER_CONNECTEDHOMEIP_DIR to an official connectedhomeip checkout" >&2
  exit 2
fi
if ! resolved_path="$(cd "$CONNECTEDHOMEIP_DIR" 2>/dev/null && pwd)"; then
  echo "ERROR: connectedhomeip directory does not exist: $CONNECTEDHOMEIP_DIR" >&2
  exit 2
fi
CONNECTEDHOMEIP_DIR="$resolved_path"
if ! git -C "$CONNECTEDHOMEIP_DIR" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  echo "ERROR: connectedhomeip path is not a Git worktree: $CONNECTEDHOMEIP_DIR" >&2
  exit 2
fi

if [[ -n "$DEPS_ROOT" ]]; then
  if ! resolved_path="$(cd "$DEPS_ROOT" 2>/dev/null && pwd)"; then
    echo "ERROR: dependency root does not exist: $DEPS_ROOT" >&2
    exit 2
  fi
  DEPS_ROOT="$resolved_path"
fi

if [[ -n "$FLUTTER_DIR" ]]; then
  if ! resolved_path="$(cd "$FLUTTER_DIR" 2>/dev/null && pwd)"; then
    echo "ERROR: flutter_matter directory does not exist: $FLUTTER_DIR" >&2
    exit 2
  fi
  FLUTTER_DIR="$resolved_path"
fi

[[ -f "$UPSTREAM_SHA_FILE" ]] || { echo "ERROR: missing $UPSTREAM_SHA_FILE" >&2; exit 1; }
[[ -d "$PATCHES_DIR" ]] || { echo "ERROR: missing $PATCHES_DIR" >&2; exit 1; }
[[ -f "$RENAME_TOOL" ]] || { echo "ERROR: missing $RENAME_TOOL" >&2; exit 1; }

mkdir -p "$OUT_DIR"
OUT_DIR="$(cd "$OUT_DIR" && pwd)"

UPSTREAM_SHA="$(tr -d '[:space:]' < "$UPSTREAM_SHA_FILE")"
SOURCE_DIR="$OUT_DIR/source"
BUILD_ROOT="$OUT_DIR/build"
OBJ_ROOT="$OUT_DIR/obj"
BUILD_LOG="$OUT_DIR/xcodebuild.log"
FRAMEWORK="$BUILD_ROOT/Release-iphoneos/ZGMatter.framework"

echo "=== ZGMatter build ==="
echo "  upstream : $UPSTREAM_SHA"
echo "  source   : $CONNECTEDHOMEIP_DIR"
echo "  out      : $OUT_DIR"
echo "  deps     : ${DEPS_ROOT:-bootstrap from upstream submodules}"
echo "  flutter  : $FLUTTER_DIR"

# Remove task-created output trees without relying on shell globs.  The source
# path is a registered worktree when it already exists, so unregister it first.
if git -C "$SOURCE_DIR" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  git -C "$CONNECTEDHOMEIP_DIR" worktree remove --force "$SOURCE_DIR"
elif [[ -e "$SOURCE_DIR" || -L "$SOURCE_DIR" ]]; then
  python3 - "$SOURCE_DIR" <<'PY'
import shutil
import sys
from pathlib import Path
p = Path(sys.argv[1])
if p.is_symlink() or p.is_file():
    p.unlink()
else:
    shutil.rmtree(p)
PY
fi
git -C "$CONNECTEDHOMEIP_DIR" worktree prune

python3 - "$BUILD_ROOT" "$OBJ_ROOT" <<'PY'
import shutil
import sys
from pathlib import Path
for raw in sys.argv[1:]:
    p = Path(raw)
    if p.exists():
        shutil.rmtree(p)
PY

if ! git -C "$CONNECTEDHOMEIP_DIR" cat-file -e "$UPSTREAM_SHA^{commit}" 2>/dev/null; then
  echo "Fetching pinned upstream commit..."
  git -C "$CONNECTEDHOMEIP_DIR" -c fetch.recurseSubmodules=no fetch --depth 1 --no-tags \
    "$UPSTREAM_REMOTE" "$UPSTREAM_SHA"
fi

echo "Creating clean upstream worktree..."
git -C "$CONNECTEDHOMEIP_DIR" worktree add --detach "$SOURCE_DIR" "$UPSTREAM_SHA"

echo "Applying ZGMatter feature patches..."
for patch in "$PATCHES_DIR"/*.patch; do
  echo "  + $(basename "$patch")"
  git -C "$SOURCE_DIR" apply --check "$patch"
  git -C "$SOURCE_DIR" apply "$patch"
done

echo "Generating ZGMatter names..."
mv "$SOURCE_DIR/src/darwin/Framework" "$SOURCE_DIR/src/darwin/ZGMatter"
python3 "$RENAME_TOOL" --in-place "$SOURCE_DIR/src/darwin/ZGMatter"

if [[ "$BOOTSTRAP_DEPS" -eq 1 || -z "$DEPS_ROOT" ]]; then
  echo "Initializing upstream Darwin submodules..."
  (
    cd "$SOURCE_DIR"
    python3 scripts/checkout_submodules.py --shallow --platform darwin
    PW_ENVSETUP_NO_BANNER=1 PW_ENVSETUP_QUIET=1 bash -c '. scripts/activate.sh'
  )
  export CHIP_NO_SUBMODULES=1
  export CHIP_NO_ACTIVATE=1
else
  echo "Reusing bootstrapped dependencies from $DEPS_ROOT"

  if [[ ! -e "$SOURCE_DIR/.environment" ]]; then
    ln -s "$DEPS_ROOT/.environment" "$SOURCE_DIR/.environment"
  fi

  missing_submodules=()
  for rel in "${DARWIN_SUBMODULES[@]}"; do
    dst="$SOURCE_DIR/$rel"
    src="$DEPS_ROOT/$rel"
    if [[ -d "$src" ]]; then
      python3 - "$dst" "$src" <<'PY'
import os
import sys
from pathlib import Path
dst = Path(sys.argv[1])
src = Path(sys.argv[2])
if dst.is_symlink():
    if dst.resolve() != src.resolve():
        dst.unlink()
elif dst.exists():
    if dst.is_dir() and not any(dst.iterdir()):
        dst.rmdir()
    else:
        raise SystemExit(f"refusing to replace non-empty dependency path: {dst}")
if not dst.exists():
    dst.symlink_to(src.resolve(), target_is_directory=True)
PY
    elif [[ -d "$dst" && ! -L "$dst" ]] && [[ -z "$(ls -A "$dst" 2>/dev/null)" ]]; then
      missing_submodules+=("$rel")
    elif [[ ! -e "$dst" ]]; then
      missing_submodules+=("$rel")
    fi
  done

  if [[ ${#missing_submodules[@]} -gt 0 ]]; then
    echo "Fetching dependencies not present in the cache:"
    printf '  - %s\n' "${missing_submodules[@]}"
    git -C "$SOURCE_DIR" -c submodule.recurse=false submodule update --init --depth 1 \
      "${missing_submodules[@]}"
  fi

  if [[ -f "$DEPS_ROOT/build_overrides/pigweed_environment.gni" ]]; then
    cp "$DEPS_ROOT/build_overrides/pigweed_environment.gni" \
      "$SOURCE_DIR/build_overrides/pigweed_environment.gni"
  else
    cat > "$SOURCE_DIR/build_overrides/pigweed_environment.gni" <<'GN'
# Generated by build_zgmatter_framework.sh.
declare_args() {
  pw_env_setup_CIPD_PIGWEED = get_path_info("../.environment/cipd/packages/pigweed", "abspath")
  pw_env_setup_CIPD_ZAP = get_path_info("../.environment/cipd/packages/zap", "abspath")
  pw_env_setup_PACKAGE_ROOT = get_path_info("../.environment/packages", "abspath")
  pw_env_setup_VIRTUAL_ENV = get_path_info("../.environment/pigweed-venv", "abspath")
}
GN
  fi

  # The dependency cache is already bootstrapped; skip repeated network-heavy
  # submodule/activation work inside the Xcode Run Script phase.
  export CHIP_NO_SUBMODULES=1
  export CHIP_NO_ACTIVATE=1
fi

PIGWEED_ROOT="$SOURCE_DIR/.environment/cipd/packages/pigweed"
if [[ ! -x "$PIGWEED_ROOT/gn" || ! -x "$PIGWEED_ROOT/bin/ninja" ]]; then
  echo "ERROR: Pigweed gn/ninja not found under $PIGWEED_ROOT" >&2
  exit 1
fi
export PATH="$PIGWEED_ROOT:$PIGWEED_ROOT/bin:$PATH"

echo "Building ZGMatter.framework..."
set +e
(
  cd "$SOURCE_DIR"
  unset CLANG_TARGET_TRIPLE_VARIANTS
  xcodebuild -quiet \
    -project src/darwin/ZGMatter/ZGMatter.xcodeproj \
    -scheme "ZGMatter Framework" \
    -configuration Release \
    -sdk iphoneos \
    -destination "generic/platform=iOS" \
    ARCHS=arm64 \
    IPHONEOS_DEPLOYMENT_TARGET="$DEPLOYMENT_TARGET" \
    LLVM_TARGET_TRIPLE_OS_VERSION="ios$DEPLOYMENT_TARGET" \
    CODE_SIGNING_ALLOWED=NO \
    CODE_SIGN_IDENTITY="" \
    SYMROOT="$BUILD_ROOT" \
    OBJROOT="$OBJ_ROOT" \
    build
) >"$BUILD_LOG" 2>&1
BUILD_RC=$?
set -e

if [[ $BUILD_RC -ne 0 ]]; then
  echo "ERROR: xcodebuild failed. Last log lines:" >&2
  tail -n 160 "$BUILD_LOG" >&2
  exit $BUILD_RC
fi

BINARY="$FRAMEWORK/ZGMatter"
[[ -f "$BINARY" ]] || { echo "ERROR: missing $BINARY" >&2; exit 1; }

echo "Validating framework..."
FILE_OUTPUT="$OUT_DIR/file.txt"
LIPO_OUTPUT="$OUT_DIR/lipo.txt"
NM_OUTPUT="$OUT_DIR/nm.txt"
file "$BINARY" > "$FILE_OUTPUT"
lipo -info "$BINARY" > "$LIPO_OUTPUT"
grep -q 'Mach-O 64-bit dynamically linked shared library arm64' "$FILE_OUTPUT"
grep -q 'arm64' "$LIPO_OUTPUT"

STRINGS_OUTPUT="$OUT_DIR/strings.txt"
nm -arch arm64 "$BINARY" > "$NM_OUTPUT"
strings "$BINARY" > "$STRINGS_OUTPUT"

assert_symbol() {
  local symbol="$1"
  if ! grep -Fq -- "$symbol" "$NM_OUTPUT"; then
    echo "ERROR: missing symbol: $symbol" >&2
    exit 1
  fi
}

assert_symbol '-[ZGMTRBaseDevice customSubscribeToAttributePaths:'
assert_symbol '-[ZGMTRBaseDevice writeAttributeRequests:'
assert_symbol '-[ZGMTRBaseDevice shutdownSubscription:scopedNodeId:]'
assert_symbol '-[ZGMTRDeviceController_Concrete getFabricIndex]'
assert_symbol 'ZGMTRDataValueNSDataDecodableType'
grep -Fq 'onCommissioningStatusUpdate:commissioningStage:error:' "$STRINGS_OUTPUT"
grep -Fq 'dispatchCommissioningStatusUpdate:stage:error:' "$STRINGS_OUTPUT"
grep -Fq '_OBJC_CLASS_$_ZGCSRInfo' "$NM_OUTPUT"
grep -Fq '_OBJC_CLASS_$_ZGAttestationInfo' "$NM_OUTPUT"

if grep -Eq '_OBJC_CLASS_\$_(CSRInfo|AttestationInfo|ZGMTRBleManager|ZGMTRBlePlatformDelegate)$' "$NM_OUTPUT"; then
  echo "ERROR: forbidden unprefixed/custom-BLE class found" >&2
  exit 1
fi
if [[ -n "$(find "$FRAMEWORK/Headers" -maxdepth 1 -name 'MTR*.h' -print -quit)" ]]; then
  echo "ERROR: unprefixed MTR public header found" >&2
  exit 1
fi

for declaration in \
  customSubscribeToAttributePaths \
  writeAttributeRequests \
  shutdownSubscription \
  getFabricIndex \
  onCommissioningStatusUpdate; do
  if ! grep -Rq "$declaration" "$FRAMEWORK/Headers"; then
    echo "ERROR: missing public declaration: $declaration" >&2
    exit 1
  fi
done

SHA256="$(shasum -a 256 "$BINARY" | awk '{print $1}')"
cat > "$OUT_DIR/build-info.txt" <<EOF
upstream_sha=$UPSTREAM_SHA
deployment_target=$DEPLOYMENT_TARGET
framework=$FRAMEWORK
binary_sha256=$SHA256
build_log=$BUILD_LOG
EOF

echo "  framework : $FRAMEWORK"
echo "  sha256    : $SHA256"

if [[ "$COPY_TO_FLUTTER" -eq 1 ]]; then
  if [[ -z "$FLUTTER_DIR" || ! -d "$FLUTTER_DIR" ]]; then
    echo "WARNING: flutter_matter checkout not found; framework was not copied" >&2
  else
    DEST="$FLUTTER_DIR/ios/frameworks/ZGMatter.framework"
    TMP_DEST="$DEST.new.$$"
    mkdir -p "$(dirname "$DEST")"
    python3 - "$TMP_DEST" <<'PY'
import shutil
import sys
from pathlib import Path
p = Path(sys.argv[1])
if p.exists():
    shutil.rmtree(p)
PY
    cp -R "$FRAMEWORK" "$TMP_DEST"
    python3 - "$DEST" <<'PY'
import shutil
import sys
from pathlib import Path
p = Path(sys.argv[1])
if p.exists():
    shutil.rmtree(p)
PY
    mv "$TMP_DEST" "$DEST"
    echo "Copied framework to $DEST"
  fi
fi

if [[ "$KEEP_WORKTREE" -eq 0 ]]; then
  git -C "$CONNECTEDHOMEIP_DIR" worktree remove --force "$SOURCE_DIR"
  git -C "$CONNECTEDHOMEIP_DIR" worktree prune
fi

echo "Done."
