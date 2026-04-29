#!/usr/bin/env python3
# ========================================
# Name: Guilherme Armin Da Silva Anton
# UFID: 2641-9801
# COP3530 Project 2 - GeoPulse
# File: verify-dataset.py
# Purpose: Verifies row counts and coordinate validity for the NYC CSV.
# ========================================

"""Verify dataset row counts and coordinate completeness for GeoPulse."""

import csv
import math
import sys
from pathlib import Path


def is_strict_coordinate(latitude_text: str, longitude_text: str) -> bool:
    """Return True when both coordinate strings are finite legal values."""
    try:
        latitude = float(latitude_text)
        longitude = float(longitude_text)
    except ValueError:
        return False

    return (
        math.isfinite(latitude)
        and math.isfinite(longitude)
        and -90.0 <= latitude <= 90.0
        and -180.0 <= longitude <= 180.0
    )


def main() -> int:
    """Read one CSV path argument and print validation counts."""
    if len(sys.argv) != 2:
        print("Usage: python3 scripts/verify-dataset.py <csv-path>")
        return 1

    path = Path(sys.argv[1])
    if not path.exists():
        print(f"File not found: {path}")
        return 1

    total = 0
    non_empty_coords = 0
    missing_coords = 0
    strict_valid_coords = 0
    invalid_numeric_coords = 0

    with path.open(
        "r",
        encoding="utf-8",
        errors="replace",
        newline="",
    ) as handle:
        reader = csv.DictReader(handle)
        header_columns = len(reader.fieldnames or [])
        for row in reader:
            total += 1
            lat = (row.get("LATITUDE") or "").strip()
            lon = (row.get("LONGITUDE") or "").strip()
            if lat and lon:
                non_empty_coords += 1
                if is_strict_coordinate(lat, lon):
                    strict_valid_coords += 1
                else:
                    invalid_numeric_coords += 1
            else:
                missing_coords += 1

    print(f"File: {path}")
    print(f"Header columns: {header_columns}")
    print(f"Total rows: {total}")
    print(f"Rows with non-empty coordinates: {non_empty_coords}")
    print("Rows accepted by strict validation: "
          f"{strict_valid_coords}")
    print(f"Rows missing latitude or longitude: {missing_coords}")
    print("Rows with non-empty invalid coordinates: "
          f"{invalid_numeric_coords}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
