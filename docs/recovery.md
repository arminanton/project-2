# Recovery

## Purpose

GeoPulse supports optional recoverable CSV ingestion for large local files. The normal loader path
does not write recovery artifacts, which keeps benchmark runs fast. Passing `--resume` enables
checkpoint and cache files next to the source CSV.

## Recovery Model

Recovery is row-based and uses two files:

```text
<dataset>.geopulse.checkpoint.json
<dataset>.geopulse.accepted.tsv
```

The checkpoint stores parser progress and file identity. The accepted-record cache stores every
accepted record that has already been parsed. This cache is required because in-memory vectors are
lost after a process stops. A byte offset alone is not sufficient to resume a full in-memory
dataset.

## Checkpoint Contents

The checkpoint contains:

- source file path
- accepted-record cache path
- file size
- file modification timestamp
- stable header signature
- last completed logical CSV row number
- byte offset after the last completed logical row
- accepted row count
- excluded row count
- completion flag

## Resume Validation

A saved checkpoint is valid only if:

- the file path matches
- the file size matches
- the modification timestamp matches
- the header signature matches
- the accepted-record cache exists
- the cache row count matches the checkpoint accepted-row count

If validation fails, GeoPulse discards the resume attempt and starts parsing from the beginning.

## CSV Row Boundary Rule

The `CsvReader` reads logical CSV records, not just physical lines. It handles quoted commas,
escaped quotes, and quoted newlines. Checkpoints are advanced only after a complete logical CSV row
has been parsed and counted.

## Completion Behavior

After a successful `--resume` load, GeoPulse writes a checkpoint marked `complete=true`. A later
`--resume` run may reuse the completed accepted-record cache if the dataset identity still matches.

## Progress Reporting

The CLI reports:

- percentage complete
- total logical rows processed
- accepted rows
- excluded rows

Progress is based on bytes read relative to the input file size.
