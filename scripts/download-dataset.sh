#!/bin/bash
# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: download-dataset.sh
# Purpose: Downloads the NYC collision CSV to the local data folder.
# ========================================

set -euo pipefail

OUT_PATH="${1:-data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv}"
URL="https://data.cityofnewyork.us/api/views/h9gi-nx95/rows.csv"
QUERY="accessType=DOWNLOAD"

mkdir -p "$(dirname "$OUT_PATH")"

echo "Downloading dataset to: $OUT_PATH"
curl -L "${URL}?${QUERY}" -o "$OUT_PATH"

echo "Download complete."
echo "Run: python3 scripts/verify-dataset.py \"$OUT_PATH\""
