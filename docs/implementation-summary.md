# GeoPulse Implementation Summary

## Scope Completed

This implementation turns the bootstrap repository into a working C++14 CLI project.

Implemented components:

- reusable `geopulse_lib` CMake library target
- `geopulse` CLI executable
- `geopulse_tests` Catch2 test executable
- core point, projection, distance, and bounding-box helpers
- robust streaming CSV reader for logical CSV rows
- collision header mapping by column name
- strict numeric coordinate validation
- dataset loading and preprocessing
- optional checkpoint/cache recovery with `--resume`
- brute-force `LinearScanIndex`
- median-split `KDTree`
- point-region `QuadTree`
- shared query result normalization
- benchmark runner
- sample CSV fixture
- GitHub Actions CI

## Key Design Decisions

### Strict coordinate validation

The original verification script counted rows with non-empty latitude and longitude. GeoPulse now
uses a stricter rule: coordinates must be present, parse as finite doubles, and fall inside legal
latitude/longitude ranges.

For the uploaded CSV snapshot:

```text
Total rows: 2,246,476
Rows with non-empty coordinates: 2,005,851
Rows accepted by strict numeric coordinate validation: 2,005,745
Rows missing latitude or longitude: 240,625
Rows with non-empty but invalid numeric coordinates: 106
```

### Logical CSV records

The CSV reader now handles quoted commas, escaped quotes, and quoted newlines. This matters because
counting physical lines produced one extra row on the full CSV snapshot.

### Recovery cache

A checkpoint byte offset is not enough to resume a stopped load because accepted records already
parsed into memory would be lost. `--resume` therefore writes both:

```text
<dataset>.geopulse.checkpoint.json
<dataset>.geopulse.accepted.tsv
```

Normal benchmark runs keep recovery disabled to avoid extra disk-write overhead.

### Projection

All indexes use the same planar-mile projection for NYC-local comparisons:

```text
xMiles = longitude * cos(40.7128 degrees) * 69.172
yMiles = latitude * 69.0
```

This keeps Linear Scan, KD-tree, and Quadtree distance semantics identical.

## Validation Performed

### Debug test build

```text
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

Result:

```text
100% tests passed, 0 tests failed out of 1
```

The single CTest target runs all Catch2 test cases.

### GCC compatibility build

```text
cmake -S . -B build_gcc -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build_gcc --parallel 2
ctest --test-dir build_gcc --output-on-failure
```

Result:

```text
100% tests passed, 0 tests failed out of 1
```

### Full dataset load

Command:

```text
./build_release/geopulse --data /mnt/data/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

Observed result:

```text
total rows: 2,246,476
accepted coordinate rows: 2,005,745
excluded rows: 240,731
missing-coordinate rows: 240,625
invalid-coordinate rows: 106
```

### Full dataset benchmark

Command:

```text
./build_release/geopulse --data /mnt/data/nyc_motor_vehicle_collisions_h9gi-nx95.csv --benchmark
```

Observed result:

```text
Indexed points: 2,005,745
Query samples: 5
Radius query miles: 0.5
Range half-size miles: 0.5

Algorithm         Build ms    Nearest ms     Radius ms      Range ms      NN ok   Radius ok   Range ok
Linear Scan          0.000        17.139        14.960        26.467        yes         yes        yes
KD-tree           1180.286         0.041         0.581         0.156        yes         yes        yes
Quadtree          2992.648         0.017         0.897         0.364        yes         yes        yes
```

The exact timings are environment-dependent. The correctness columns are the important validation:
both KD-tree and Quadtree matched Linear Scan for nearest-neighbor, radius, and range queries.
