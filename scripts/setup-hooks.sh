#!/bin/bash
# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: setup-hooks.sh
# Purpose: Enables the repository's local Git hook directory.
# ========================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

cd "$ROOT_DIR"

git config core.hooksPath .githooks
chmod +x .githooks/pre-push
chmod +x .githooks/commit-msg

echo "Git hooks configured to use .githooks/."
echo "Pre-push and commit-msg protections are now active."
