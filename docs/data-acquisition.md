# Data Acquisition

## Purpose
This document records how the GeoPulse dataset snapshot was obtained and how it can be reproduced later.

## Dataset
- **Dataset Name:** NYC OpenData Motor Vehicle Collisions - Crashes
- **Dataset Page:** https://data.cityofnewyork.us/Public-Safety/Motor-Vehicle-Collisions-Crashes/h9gi-nx95
- **Official CSV Export URL:** https://data.cityofnewyork.us/api/views/h9gi-nx95/rows.csv?accessType=DOWNLOAD

## Snapshot Used for This Project
- **Acquisition Timestamp:** 2026-03-07 19:43 local time
- **Local Filename:** `nyc_motor_vehicle_collisions_h9gi-nx95.csv`
- **Verified File Size:** 472,383,893 bytes
- **Header Columns:** 29
- **Total Data Rows:** 2,246,476
- **Rows with Valid Coordinates:** 2,005,851
- **Rows Missing Latitude or Longitude:** 240,625

## Download Command
The dataset was downloaded with:

```bash
curl -L "https://data.cityofnewyork.us/api/views/h9gi-nx95/rows.csv?accessType=DOWNLOAD" \
  -o data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

A helper script is also included:

```bash
bash scripts/download-dataset.sh
```

## Verification Command
The row and coordinate counts were verified locally with:

```bash
python3 scripts/verify-dataset.py data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

Expected output for the March 7, 2026 snapshot:
- `Header columns: 29`
- `Total rows: 2246476`
- `Rows with valid coordinates: 2005851`
- `Rows missing latitude or longitude: 240625`

## Git LFS Snapshot Workflow
If you want to keep an archival copy in the repository, initialize Git LFS locally first:

```bash
git lfs install
```

Then copy the verified snapshot into the dated snapshot path:

```bash
mkdir -p data/snapshots/nyc/2026-03-07
cp data/local/nyc_motor_vehicle_collisions_h9gi-nx95.csv \
  data/snapshots/nyc/2026-03-07/nyc_motor_vehicle_collisions_h9gi-nx95.csv
```

The repository already tracks `data/snapshots/**/*.csv` through Git LFS in `.gitattributes`.

## Preprocessing Rule
Only records with valid latitude and longitude are inserted into the brute-force baseline, KD-tree, and Quadtree indexes.

## Git Storage Policy
- Keep the working CSV under `data/local/`, which is ignored by git.
- If an archival copy is required in the repository, store it under `data/snapshots/nyc/2026-03-07/` and track it with Git LFS.
- Keep sample fixtures under `data/samples/` for tests and quick local runs.
