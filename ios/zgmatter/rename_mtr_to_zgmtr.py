#!/usr/bin/env python3
"""Generate the ZGMatter Darwin framework from the upstream Matter framework.

The upstream framework uses the ``MTR`` class prefix and the ``Matter`` product
name.  ZGMatter must not collide with Apple's built-in Matter framework, so this
tool applies the same mechanical prefix/product rename every time.  It is
deliberately limited to the Darwin framework tree; upstream C++ sources and
generated cluster code are never copied or rewritten.

Usage:
    rename_mtr_to_zgmtr.py SRC DST
    rename_mtr_to_zgmtr.py --in-place ROOT
"""

from __future__ import annotations

import argparse
import re
import shutil
from pathlib import Path

TEXT_SUFFIXES = {
    ".apinotes",
    ".cpp",
    ".h",
    ".json",
    ".m",
    ".md",
    ".mm",
    ".modulemap",
    ".pbxproj",
    ".plist",
    ".sh",
    ".swift",
    ".txt",
    ".xcconfig",
    ".xcscheme",
}

PRODUCT_FILENAMES = {
    "Matter.apinotes": "ZGMatter.apinotes",
    "Matter.modulemap": "ZGMatter.modulemap",
    "Matter.xcconfig": "ZGMatter.xcconfig",
    "Matter.Debug.xcconfig": "ZGMatter.Debug.xcconfig",
    "Matter.Release.xcconfig": "ZGMatter.Release.xcconfig",
    "MatterTests.xcconfig": "ZGMatterTests.xcconfig",
    "MatterTests-Bridging-Header.h": "ZGMatterTests-Bridging-Header.h",
    "Matter.h": "ZGMatter.h",
    "Matter_Private.h": "ZGMatter_Private.h",
    "Matter_Private.modulemap": "ZGMatter_Private.modulemap",
}


def transform_content(content: str) -> str:
    """Rename the public product/prefix without double-prefixing existing ZG names."""
    # API symbols: MTRFoo, MTR_LOGFoo, MTRErrorDomain, ...
    content = re.sub(r"(?<!ZG)MTR(?=[A-Z0-9_]|$)", "ZGMTR", content)

    # Legacy classes without an MTR prefix are also generic enough to collide
    # with Apple's Matter framework. Keep the existing ZG names used by
    # flutter_matter's native adapter.
    content = re.sub(r"(?<!ZG)\bCSRInfo\b", "ZGCSRInfo", content)
    content = re.sub(r"(?<!ZG)\bAttestationInfo\b", "ZGAttestationInfo", content)

    # Multi-word product names must be handled before the standalone token.
    content = re.sub(r"(?<!ZG)MatterTests", "ZGMatterTests", content)
    content = re.sub(r"(?<!ZG)Matter_Private", "ZGMatter_Private", content)

    # Product/module/framework references: Matter, Matter.framework,
    # <Matter/MTRBaseDevice.h>, module Matter, Matter.xcodeproj, ...
    content = re.sub(r"(?<!ZG)\bMatter\b", "ZGMatter", content)

    # Xcode product/config names that are not covered by MATTER token replacement.
    content = content.replace("src/darwin/Framework", "src/darwin/ZGMatter")
    content = content.replace("PRODUCT_BUNDLE_IDENTIFIER = com.csa.matter", "PRODUCT_BUNDLE_IDENTIFIER = com.zengge.ZGMatter")
    content = content.replace("com.csa.matter", "com.zengge.ZGMatter")
    return content


def transform_filename(name: str) -> str:
    if name in PRODUCT_FILENAMES:
        return PRODUCT_FILENAMES[name]
    if name.startswith("MTR"):
        return "ZGMTR" + name[3:]
    if name.startswith("Matter") and Path(name).suffix in TEXT_SUFFIXES:
        return "ZGMatter" + name[6:]
    return name


def transform_directory(name: str) -> str:
    if name == "Matter.xcodeproj":
        return "ZGMatter.xcodeproj"
    if name.startswith("MTR"):
        return "ZGMTR" + name[3:]
    return name


def rewrite_text(path: Path) -> bool:
    try:
        content = path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return False
    transformed = transform_content(content)
    if transformed == content:
        return False
    path.write_text(transformed, encoding="utf-8")
    return True


def rename_tree(root: Path) -> tuple[int, int]:
    """Rename files/directories in-place and rewrite text content."""
    renamed = 0
    for path in sorted(root.rglob("*"), key=lambda p: len(p.parts), reverse=True):
        new_name = transform_directory(path.name) if path.is_dir() else transform_filename(path.name)
        if new_name != path.name:
            path.rename(path.with_name(new_name))
            renamed += 1

    changed = 0
    for path in root.rglob("*"):
        if path.is_file() and path.suffix in TEXT_SUFFIXES:
            changed += int(rewrite_text(path))
    return renamed, changed


def copy_tree(src: Path, dst: Path) -> tuple[int, int]:
    renamed = 0
    changed = 0
    for source in sorted(src.rglob("*")):
        rel = source.relative_to(src)
        rel_parts = list(rel.parts)
        rel_parts[-1] = transform_filename(rel_parts[-1])
        rel_parts = [transform_directory(part) for part in rel_parts[:-1]] + [rel_parts[-1]]
        target = dst.joinpath(*rel_parts)
        if source.is_dir():
            target.mkdir(parents=True, exist_ok=True)
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(source, target)
            renamed += int(target.name != source.name)
            if target.suffix in TEXT_SUFFIXES:
                changed += int(rewrite_text(target))
    return renamed, changed


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("src", type=Path, help="source framework tree")
    parser.add_argument("dst", nargs="?", type=Path, help="destination (copy mode)")
    parser.add_argument("--in-place", action="store_true", help="rename the source tree in place")
    args = parser.parse_args()

    if not args.src.is_dir():
        parser.error(f"source directory not found: {args.src}")

    if args.in_place:
        if args.dst is not None:
            parser.error("--in-place does not accept a destination")
        renamed, changed = rename_tree(args.src)
        print(f"Renamed in-place: {renamed} paths, {changed} text files")
        return 0

    if args.dst is None:
        parser.error("missing destination (or pass --in-place)")
    if args.dst.exists():
        parser.error(f"destination already exists: {args.dst}")

    args.dst.mkdir(parents=True)
    renamed, changed = copy_tree(args.src, args.dst)
    print(f"Copied to {args.dst}: {renamed} paths renamed, {changed} text files")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
