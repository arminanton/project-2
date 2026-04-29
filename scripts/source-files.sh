#!/bin/bash
# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: source-files.sh
# Purpose: Lists local C++ files for format and lint scripts.
# ========================================

set -euo pipefail

if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    git ls-files '*.h' '*.hpp' '*.cpp' '*.cc' '*.cxx' \
        ':!:tests/catch2/*' ':!:build/*'
else
    find include src tests -type f \
        \( -name '*.h' -o -name '*.hpp' -o -name '*.cpp' \
        -o -name '*.cc' -o -name '*.cxx' \) \
        ! -path 'tests/catch2/*' ! -path '*/build/*' | sort
fi
