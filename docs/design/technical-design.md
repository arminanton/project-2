# Technical Design

## 1. Purpose

GeoPulse is a C++14 command-line application that compares a brute-force linear scan, a KD-tree,
and a Quadtree for geospatial queries over the NYC Motor Vehicle Collisions dataset.

## 2. Current Implementation

The project is implemented around a reusable `geopulse_lib` CMake target. The CLI executable and
the Catch2 test executable both link to this library so application behavior and test behavior use
the same compiled code.

Main modules:

- `core`: geometry, projection, distance, bounding boxes, query result types
- `data`: CSV reader, collision parser, data loader, checkpoint/cache recovery
- `index`: shared `SpatialIndex` interface, `LinearScanIndex`, `KDTree`, `QuadTree`
- `query`: result normalization and comparison helpers
- `benchmark`: build/query timing and correctness comparison
- `ui`: argument parser, CLI application, interactive menu

## 3. Dataset Rules

The uploaded CSV snapshot contains:

- 2,246,476 total rows
- 29 header columns
- 2,005,851 rows with non-empty latitude and longitude
- 240,625 rows missing latitude or longitude
- 106 rows with non-empty but invalid numeric coordinates
- 2,005,745 rows accepted by GeoPulse strict numeric validation

GeoPulse accepts a row only when latitude and longitude are present, parse as finite doubles, and
fall inside legal geographic ranges.

## 4. Coordinate Model

Rows retain original latitude/longitude for display. Indexes use projected planar miles for fast
distance comparisons and pruning.

Projection:

```text
yMiles = latitude * 69.0
xMiles = longitude * cos(reference_latitude) * 69.172
reference_latitude = 40.7128 degrees
```

This is appropriate for localized NYC comparisons and keeps all three indexes on identical
distance semantics.

## 5. CSV Ingestion

`CsvReader` streams logical CSV records. It handles:

- quoted commas
- escaped quotes
- quoted newlines
- CRLF or LF line endings

`CollisionParser` resolves required columns from the header by name rather than relying on fixed
column indexes.

## 6. Recovery

`--resume` enables:

```text
<dataset>.geopulse.checkpoint.json
<dataset>.geopulse.accepted.tsv
```

The checkpoint alone is not enough because the program needs the accepted records parsed before the
checkpoint byte offset. Therefore the accepted-record cache is part of the recovery design.

## 7. Spatial Index Contract

All structures implement:

```text
build(points)
nearest(point)
radiusQuery(center, radiusMiles)
rangeQuery(box)
size()
```

`LinearScanIndex` is the correctness oracle. KD-tree and Quadtree results are normalized and
compared against it.

## 8. KD-tree

The KD-tree uses median splitting with alternating projected axes:

```text
axis 0 = xMiles
axis 1 = yMiles
```

Nearest and radius queries prune the far branch when the split-plane distance cannot improve the
current result. Range queries prune by the active split axis.

## 9. Quadtree

The Quadtree is a point-region tree with configurable leaf capacity and maximum depth. It uses
half-open child assignment rules internally so a point on a boundary belongs to exactly one child.
Nearest-neighbor search orders children by minimum distance from the query to each child box.

## 10. Benchmarking

`BenchmarkRunner` measures:

- build time
- nearest-neighbor query time
- radius query time
- rectangular range query time
- correctness agreement with Linear Scan

Benchmarks run on deterministic sample points selected from the loaded dataset.
