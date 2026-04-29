# GeoPulse

GeoPulse is a C++14 command-line project for University of Florida
COP3530 Project 2. It compares spatial search over the NYC Motor Vehicle
Collisions dataset using three comparable structures:

1. Linear Scan, used as the exact correctness oracle.
2. KD-tree, implemented from scratch.
3. Quadtree, implemented from scratch.

The two non-trivial assignment structures are the KD-tree and Quadtree.
Linear Scan remains in the project because every optimized answer is checked
against a simple brute-force baseline.

## Assignment Coverage

GeoPulse satisfies the core Project 2 source-code requirements:

- uses C++14;
- uses a public dataset with more than 100,000 rows;
- implements two non-trivial comparable data structures from scratch;
- compares correctness and benchmark performance for the same task;
- includes a README with build and run instructions;
- includes local Catch2 tests;
- includes GitHub, Git LFS, VS Code, CLion, CMake, and quality-tool setup;
- includes a TeX-built final report under `docs/report/`.

The final YouTube video URL still must be recorded and inserted into the
report before Canvas submission.

## Repository Layout

```text
include/       Public headers grouped by module.
src/           Implementation files grouped by module.
tests/         Catch2 tests and public sample integration test.
data/samples/ Small committed CSV fixture for tests and demos.
data/local/   Ignored location for the full local CSV.
docs/report/  Final report TeX source, PDF, and rendered proof pages.
scripts/      Dataset, formatting, hook, and style helper scripts.
.vscode/      VS Code build, debug, and task configuration.
.github/      GitHub settings, pull request template, CI, and code owners.
```

## Build and Test

Use a clean build directory:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

The executable is named `geopulse` even though the CMake target is `Main`.
The test executable is named `geopulse_tests` even though the CMake target is
`Tests`.

## Run on the Public Sample

```bash
./build/geopulse --version
./build/geopulse --help
./build/geopulse --data data/samples/mixed_collisions_small.csv
./build/geopulse --data data/samples/mixed_collisions_small.csv --benchmark
```

Expected public sample load output:

```text
Dataset summary
total rows: 8
accepted coordinate rows: 6
excluded rows: 2
missing-coordinate rows: 1
invalid-coordinate rows: 1
```

## Run on the Full Dataset

Place the full CSV at:

```text
data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

Then run:

```bash
./build/geopulse \
    --data data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv \
    --benchmark
```

The full CSV is intentionally not committed. `data/local/` is ignored so a
large working dataset does not enter normal Git history.

## Recovery Mode

Normal benchmark runs do not write recovery files. To enable resumable loading:

```bash
./build/geopulse \
    --data data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv \
    --resume
```

Recovery mode writes a checkpoint JSON file and accepted-record TSV cache next
to the source CSV. The cache is required because a byte offset alone cannot
restore already-parsed in-memory records after a restart.

## Current Verified Dataset Counts

For the uploaded NYC collision CSV snapshot:

```text
total rows: 2246476
accepted coordinate rows: 2005745
excluded rows: 240731
missing-coordinate rows: 240625
invalid-coordinate rows: 106
```

Rows are accepted only when latitude and longitude are present, parse as finite
numbers, and fall inside legal latitude/longitude ranges.

## Local Quality Tools

Optional local quality commands:

```bash
make format
make lint
```

`clang-format`, `clang-tidy`, and `cpplint` are optional local tools and are not
required for CMake or Gradescope-style builds. The active Catch2 suite includes
a style guard that checks student `.h` and `.cpp` files outside `tests/catch2/` for the agreed
100-line and 80-column budgets, required banners, and CamelCase
local test filenames.

## Version

Current version: `0.2.0`.
