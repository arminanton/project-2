# Testing

## Purpose

GeoPulse uses test-backed development to keep parsing, preprocessing, recovery, and query logic
correct from the start.

The test suite proves that the advanced indexes return the same logical results as the brute-force
linear-scan baseline.

## Framework

The project vendors the Catch2 amalgamated source under `tests/catch2/`.

## Test Layers Implemented

### 1. Core Unit Tests

Covered by `tests/core/test_geometry.cpp`.

Validated behavior:

- coordinate validation
- latitude/longitude projection
- distance helpers
- bounding-box containment
- bounding-box intersection
- minimum distance from point to box

### 2. CSV and Data Loader Tests

Covered by `tests/data/test_data_loader.cpp`.

Validated behavior:

- quoted commas
- escaped quotes
- mixed valid/invalid sample data
- missing-coordinate exclusion
- invalid-coordinate exclusion
- checkpoint JSON round-trip

### 3. Spatial Index Correctness Tests

Covered by `tests/index/test_spatial_indexes.cpp`.

Validated behavior:

- Linear Scan, KD-tree, and Quadtree build paths
- nearest-neighbor agreement
- radius-query set agreement
- rectangular range-query set agreement
- empty index behavior

### 4. Benchmark Smoke Tests

Covered by `tests/benchmark/test_benchmark.cpp`.

Validated behavior:

- benchmark runner includes Linear Scan, KD-tree, and Quadtree
- advanced structures are correctness-checked against Linear Scan
- benchmark report text is generated

## Test Commands

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

The full local CSV is not required for unit tests. The test suite uses committed sample fixtures
under `data/samples/`.

## Full Dataset Validation

For the uploaded full CSV snapshot, the Release CLI load completed with:

```text
total rows: 2,246,476
accepted coordinate rows: 2,005,745
excluded rows: 240,731
missing-coordinate rows: 240,625
invalid-coordinate rows: 106
```

The same full CSV benchmark completed with all KD-tree and Quadtree correctness checks passing
against Linear Scan.
