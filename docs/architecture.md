# Architecture

## Purpose
GeoPulse is a C++14 command-line application that compares two spatial data structures, a KD-tree and a Quadtree, against a brute-force baseline for nearest-neighbor, radius, and rectangular range queries over a large collision dataset.

This document defines the intended module boundaries, dependency direction, runtime responsibilities, and recovery placement.

## Architectural Goals
- Keep the code modular without unnecessary depth.
- Separate ingestion, indexing, benchmarking, and user interaction.
- Keep correctness measurable by comparing advanced indexes against the brute-force baseline.
- Support progress reporting and safe resume during large-file parsing.
- Keep the design compatible with standard C++14 toolchains.
- Preserve clear comments and readable headers in files.

## Module Layout
Recommended source layout:

```text
include/
  core/
  data/
  index/
  query/
  benchmark/
  ui/

src/
  data/
  index/
  query/
  benchmark/
  ui/

tests/
  catch2/
docs/
data/
```

## Primary Modules

### `core`
Shared domain and geometry components.

Expected contents:
- `Point`
- `BoundingBox`
- distance helpers
- query option structs
- query result structs
- shared type aliases

This module should have no dependency on the CLI and no direct dependency on CSV parsing.

### `data`
Dataset ingestion and preprocessing.

Expected responsibilities:
- CSV streaming
- row validation
- coordinate parsing
- preprocessing filters
- checkpoint and recovery state
- progress tracking

This module produces valid-coordinate records for indexing and benchmarking.

### `index`
Index implementations and the shared query interface.

Expected contents:
- `SpatialIndex` interface
- `LinearScanIndex`
- `KDTree`
- `QuadTree`

Each implementation should expose a consistent query surface so benchmark code and CLI code do not need structure-specific branching for normal operations.

### `query`
Query orchestration and shared query semantics.

Expected responsibilities:
- nearest-neighbor request handling
- radius query handling
- rectangular range query handling
- result normalization where needed

This layer should remain thin. Query logic should live mostly inside the index implementations.

### `benchmark`
Benchmark orchestration and timing.

Expected responsibilities:
- repeated query execution
- timing via `std::chrono`
- fairness rules for comparison
- correctness cross-checks against the brute-force baseline
- summary formatting for CLI and report use

### `ui`
Menu-driven command-line interface.

Expected responsibilities:
- display menus
- prompt for input
- validate command-level input
- call application services
- present results and benchmark summaries
- show ingestion progress and resume prompts

## Dependency Direction
Preferred dependency flow:

`ui -> benchmark / index / data -> core`

Rules:
- `core` should not depend on higher layers.
- `data` may depend on `core`.
- `index` may depend on `core`.
- `benchmark` may depend on `index` and `core`.
- `ui` may depend on all operational layers, but should not embed low-level parsing or traversal logic.

## Recovery Components
Recovery belongs to the ingestion workflow, not the index layer.

Recommended state objects:
- `ParseCheckpoint`
- `ParseProgress`
- `ResumePolicy`

Checkpoints should record:
- source file path
- file size
- file modification timestamp
- header signature
- last successful row number
- byte offset after the last successful row
- valid-record count
- excluded-record count

This state should be written atomically so a crash or interruption does not leave a corrupted resume file.

## Runtime Flow
1. User selects dataset path.
2. Data layer checks for a matching checkpoint.
3. If a valid checkpoint exists, the CLI offers resume.
4. Data layer parses and preprocesses the CSV while surfacing progress.
5. Valid-coordinate records are stored in memory.
6. Indexes are built from the valid-coordinate records.
7. CLI routes queries to the selected structure.
8. Benchmark layer compares correctness and query time across implementations.

## Commenting Standards
`.h` and `.cpp` files should keep a file header comment and focused internal comments for non-obvious logic. Comments should explain intent, invariants, pruning rules, recovery semantics, and edge handling. Comments should not be removed without replacing them with a more accurate version. Use `docs/commenting.md` as the repository-level guide.

## Design Constraints
- Use `std::unique_ptr` for owned tree nodes.
- Avoid storing redundant metadata inside tree nodes when a lighter reference is sufficient.
- Keep large local datasets outside version control.
- Keep sample datasets committed for tests and quick local runs.
- Keep third-party files, such as Catch2 amalgamated sources, isolated from local formatting rules.

## Header and Source Layout

GeoPulse uses the standard C++ split between `include/` and `src/`. Header files live under `include/` and provide declarations that can be shared across the application and tests. Source files live under `src/` and provide the corresponding implementations.

This means an include such as `#include "core/Version.h"` resolves to `include/core/Version.h`, because the repository `include/` directory is added to the target include paths in `CMakeLists.txt`. The root-level CLion template `main.cpp` is not part of the GeoPulse build and has been removed so that `src/main.cpp` is the only application entry point.

