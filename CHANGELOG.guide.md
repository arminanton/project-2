# CHANGELOG Guide

## Purpose
`CHANGELOG.md` records one entry per released version. In this project, a released version maps to one issue and one pull request, not to each individual commit inside that issue.

## Rules
- Use one changelog entry per issue / PR / released version.
- Multiple commits inside the same issue should refine the same future changelog draft until the final issue commit is ready.
- Update the real `CHANGELOG.md` only in the final commit for that issue.
- Keep `PR #000` as a placeholder until the real pull request exists.

## Header Format
```md
## YYYY-MM-DD | v<major>.<phase>.<release> | PR #000 | <type> | <title> (Issue #<number>)
```

## Example
```md
## 2026-03-14 | v0.0.1 | PR #000 | chore | Bootstrap repository governance and proposal baseline (Issue #1)
```

## Release-Level Managed Files
When a new version is introduced, check whether the following files also require coordinated changes:
- `CMakeLists.txt`
- `include/core/Version.h`
- `CHANGELOG.md`

Coordinate future versions of those changes carefully so the released repository state stays consistent when the related issue is ready to land.
