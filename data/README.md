# Data Layout

## Purpose
This directory separates local working data, committed samples, and optional repository-tracked snapshots.

## Directory Rules
- `data/local/` stores large local datasets used during normal development. This directory is ignored by git except for `.gitkeep`.
- `data/samples/` stores small committed CSV samples for tests and quick local runs.
- `data/snapshots/` stores optional immutable dataset snapshots that may be committed with Git LFS.

## Recommended Working Dataset Path
Save the full NYC collision CSV here during development:

```text
data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

## Optional Snapshot Path
If you want a committed archival copy, place it here and track it with Git LFS:

```text
data/snapshots/nyc/2026-03-07/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

## Git LFS Setup
Run this once after cloning the repository if you plan to store the archival snapshot in git:

```bash
git lfs install
```

The repository already tracks `data/snapshots/**/*.csv` through `.gitattributes`.

## Verified Snapshot Metadata
The project proposal and design documents refer to a local snapshot obtained on **2026-03-07 at 7:43 PM local time**.

Verified counts for that snapshot:
- 2,246,476 total data rows
- 29 header columns
- 2,005,851 rows with valid latitude and longitude
- 240,625 rows missing at least one coordinate

## Replication
Use `scripts/download-dataset.sh` to download the official CSV and `scripts/verify-dataset.py` to verify row counts and coordinate completeness.
