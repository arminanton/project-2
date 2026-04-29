# Changelog

## v0.2.0

### Added

- Final C++14 implementation with SRP-focused modules under `include/` and
  `src/`.
- Scratch-built KD-tree and Quadtree implementations for comparable spatial
  indexing.
- Linear Scan baseline used as the exact correctness oracle.
- Streaming CSV reader with quoted commas, escaped quotes, and quoted-newline
  support.
- Strict numeric latitude/longitude validation.
- Data loader, checkpoint JSON, and accepted-record TSV cache for optional
  recovery mode.
- Query support for nearest-neighbor, radius, and rectangular range operations.
- Benchmark runner that verifies KD-tree and Quadtree answers against Linear
  Scan before reporting timings.
- Catch2 tests for command parsing, sample output, CSV parsing, data loading,
  recovery-cache reuse, geometry, index correctness, edge cases, benchmarks,
  and production style budgets.
- TeX final report, built PDF, and 600-DPI rendered proof pages.
- GitHub Actions CI workflow.

### Changed

- Version updated to `0.2.0`.
- CMake now exposes `geopulse_lib`, `Main`, and `Tests` targets.
- Catch2 is isolated from project warnings-as-errors.
- README now documents final build, test, sample, full-dataset, and recovery
  workflows.
- `.clang-format` now targets 80 columns, Allman braces, no tabs, no argument
  bin packing, and indented namespaces.
- `.clang-tidy` now documents the optional analyzer, bugprone, performance,
  readability, and modernize checks used for local review.

### Fixed

- The executable now implements the planned `--data`, `--benchmark`,
  `--resume`, and `--interactive` flows.
- `main.cpp` is now a thin launcher that delegates to `CliApplication`.
- Checkpoint recovery stores accepted records, not only a byte offset.
- Dataset parsing counts logical CSV records rather than physical lines.
