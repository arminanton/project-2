#!/bin/bash
# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: check-style.sh
# Purpose: Runs optional local format, tidy, and cpplint checks.
# ========================================

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
CLANG_FORMAT_BIN="${CLANG_FORMAT:-clang-format}"
CLANG_TIDY_BIN="${CLANG_TIDY:-clang-tidy}"
CPPLINT_BIN="${CPPLINT:-cpplint}"
BUILD_DIR="${BUILD_DIR:-build}"

cd "$ROOT_DIR"

if ! command -v "$CLANG_FORMAT_BIN" >/dev/null 2>&1; then
    echo "ERROR: clang-format was not found in PATH."
    exit 1
fi

mapfile -t files < <(bash scripts/source-files.sh)

if [ "${#files[@]}" -gt 0 ]; then
    echo "Checking formatting with clang-format..."
    "$CLANG_FORMAT_BIN" --dry-run --Werror "${files[@]}"
fi

if command -v "$CLANG_TIDY_BIN" >/dev/null 2>&1; then
    if [ -f "$BUILD_DIR/compile_commands.json" ]; then
        echo "Running clang-tidy..."
        mapfile -t cpp_files < <(
            printf '%s\n' "${files[@]}" | grep -E '\.(cpp|cc|cxx)$' || true
        )
        if [ "${#cpp_files[@]}" -gt 0 ]; then
            "$CLANG_TIDY_BIN" -p "$BUILD_DIR" "${cpp_files[@]}"
        fi
    else
        echo "Skipping clang-tidy: $BUILD_DIR/compile_commands.json missing."
        echo "Run 'make configure' first."
    fi
else
    echo "Skipping clang-tidy because it is not installed."
fi

if command -v "$CPPLINT_BIN" >/dev/null 2>&1; then
    echo "Running cpplint..."
    "$CPPLINT_BIN" --quiet "${files[@]}"
else
    echo "Skipping cpplint because it is not installed."
fi

if grep -RIn --exclude-dir=tests/catch2 --include='*.h' \
    --include='*.hpp' --include='*.cpp' --include='*.cc' \
    --include='*.cxx' '^using namespace std;$' include src tests; then
    echo "ERROR: 'using namespace std;' is not allowed."
    exit 1
fi

echo "Style checks completed successfully."
