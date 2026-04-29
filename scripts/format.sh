#!/bin/bash
# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: format.sh
# Purpose: Applies clang-format to local GeoPulse C++ source files.
# ========================================

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
CLANG_FORMAT_BIN="${CLANG_FORMAT:-clang-format}"

cd "$ROOT_DIR"

if ! command -v "$CLANG_FORMAT_BIN" >/dev/null 2>&1; then
    echo "ERROR: clang-format was not found in PATH."
    exit 1
fi

mapfile -t files < <(bash scripts/source-files.sh)

if [ "${#files[@]}" -eq 0 ]; then
    echo "No C++ source files found to format."
    exit 0
fi

"$CLANG_FORMAT_BIN" -i "${files[@]}"
echo "Formatted ${#files[@]} file(s)."
