# Operations

## Purpose
This document explains how to build, run, format, lint, and benchmark GeoPulse during local development.

## Local Dataset Placement
Place the full NYC CSV under:

```text
data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

Do not commit the full dataset.

## Common Commands
```bash
make configure
make build
make test
make run
make benchmark
make format
make lint
```

## Normal Development Flow
1. Open an issue.
2. Create a branch for that issue.
3. Implement the change with comments and tests.
4. Run local build, test, and style checks.
5. Open a pull request.
6. Update `CHANGELOG.md` if needed.
7. Squash merge into `main`.

## Benchmark Notes
Benchmarks should be run in `Release` mode and only after correctness has been verified against the brute-force baseline.


## IDE Setup
### VS Code
Use the committed `.vscode/settings.json`, `.vscode/tasks.json`, and `.vscode/extensions.json` files. These settings enable format-on-save for C and C++ files, point IntelliSense at CMake Tools, and expose build, test, format, and lint tasks in the editor.

### CLion
CLion automatically detects `.clang-format` in the project tree and can prefer `.clang-tidy` files over IDE settings. Use the project Make targets or `scripts/check-style.sh` to run `cpplint`, since `cpplint` is not a built-in CLion inspection.


## IDE Build and Debug Support
The repository includes `CMakePresets.json` so CLion and VS Code can share the same Debug and Release configure/build settings. VS Code can use the committed `.vscode/` workspace files, while CLion can import the same presets and detect `.clang-format` and `.clang-tidy` from the project root.


## Dataset Snapshot Operations
- Run `make lfs-init` before adding a repository-tracked archival CSV under `data/snapshots/`.
- Keep the working CSV under `data/local/`.
