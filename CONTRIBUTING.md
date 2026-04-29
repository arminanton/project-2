# Contributing

## Purpose

This repository is a solo course project, but it follows a disciplined GitHub workflow so the
full development history remains reviewable, reproducible, and aligned with the course template
expectations.

## Core Rules

- Use GitHub issues, milestones, branches, commits, and pull requests.
- Keep changes small enough to review, test, and explain.
- Prefer test-backed development for parsing, preprocessing, geometry helpers, and query
  correctness.
- Keep the repository buildable on standard C++14 toolchains.
- Update documentation and the changelog in the same pull request that changes behavior,
  workflow, performance, or recovery semantics.
- Keep meaningful comments. Do not remove useful comments from existing code unless you replace
  them with a more accurate version.

## Bootstrap Rule

The repository may require one initial bootstrap commit on `main` before branch protection,
settings sync, and local hooks are fully active. After that bootstrap step, use the normal
issue, branch, commit, and pull request workflow for every change.

## Branching Model

- `main` is the protected integration branch.
- Create one branch per issue.

Recommended branch prefixes:

- `feat/` for new features
- `fix/` for bug fixes
- `redo/` for structural rework without changing intended feature scope
- `docs/` for documentation changes
- `test/` for new or revised tests
- `chore/` for maintenance and repository setup
- `perf/` for benchmark and performance work
- `vuls/` for vulnerability or security-hardening work

Examples:

- `feat/csv-reader`
- `feat/kdtree-nearest`
- `redo/query-refinement`
- `docs/testing-strategy`

## Issue and Pull Request Flow

1. Open or refine the GitHub issue.
2. Create a branch from that issue.
3. Make focused commits that reference the issue number.
4. Run local build, test, format, and lint commands before opening the pull request.
5. Open a pull request using the project template.
6. Update `CHANGELOG.md` if the pull request changes behavior, performance, workflow,
   documentation, or recovery behavior.
7. Use a pull request title that can also serve as the final squash merge commit message.
8. Squash merge into `main`.

## Commit Message Format

Commit messages must follow this format:

`<type>: <short description> (Issue #<number>)`

Allowed types:

- `feat`
- `fix`
- `redo`
- `docs`
- `test`
- `chore`
- `perf`
- `vuls`

Examples:

- `feat: add CSV parsing pipeline (Issue #4)`
- `test: verify quadtree range queries (Issue #13)`
- `redo: simplify shared query API (Issue #8)`

## Pull Request and Merge Message Rules

- The pull request title should be short, direct, and suitable for the final squash merge commit
  message.
- The final squash merge commit message should keep the mandated format, such as
  `feat: implement CSV parsing pipeline (Issue #4)`.
- Link the pull request to the relevant issue.
- Update `CHANGELOG.md` before merging the pull request. Follow `CHANGELOG.guide.md` when adding
  the new top entry. Leave `PR #000` as a placeholder until the real pull request number exists, then update it in a final branch commit before merge.

## Versioning Rules

The repository uses this version format:

`<major>.<phase>.<release>`

Meaning:

- `major` tracks the broad project generation and stays `0` while the project remains pre-release
- `phase` tracks the current implementation wave and may loosely follow milestone progression
- `release` increments for each merged change inside the current phase

Do not use GitHub issue numbers, milestone IDs, or pull request numbers as direct version components. Keep those identifiers in the changelog entry instead.

Examples:

- `0.0.1` bootstrap governance release
- `0.0.2` second foundational repository release in the same phase
- `0.1.1` first merged change in the first implementation phase

## Code Commenting Standard

Source files, header files, and tests should follow the commenting style already used in prior
course submissions.

Required patterns:

- Start major `.h`, `.hpp`, `.cpp`, and test files with a file header banner comment.
- Use section divider comments for major areas of a file.
- Add comments before classes, structs, helper functions, and public methods.
- Use short inline comments for important fields, invariants, or edge-sensitive values.
- Explain intent in plain English. Do not rely only on code-level restatement.
- In tests, explain the scenario, why it matters, and what is being verified.

Comment rules:

- Preserve useful comments during rewrites and refactors.
- Replace outdated comments immediately when code behavior changes.
- Keep comments compatible with the formatter. Do not write comment layouts that depend on manual
  line wrapping.

## Naming and Namespace Rules

- Do not use `using namespace std;` in this repository.
- Do not use blanket namespace imports in headers.
- Use `CamelCase` for classes and structs.
- Use `camelBack` for public methods, free functions, local variables, and parameters.
- Use `_camelBack` for private helper methods and private data members.
- Keep names aligned with `docs/naming.md` and repository lint rules.

## Local Setup

Common commands:

```bash
make configure
make build
make test
make format
make lint
make run
make benchmark
```

If local git hooks are present, enable them after cloning and after the bootstrap setup on
`main` is complete:

```bash
bash scripts/setup-hooks.sh
```

## Style and Static Analysis

The repository uses:

- `clang-format` for formatting
- `clang-tidy` for linting and static checks
- optional `cpplint` integration through the style wrapper script when installed locally

`clang-format` preserves the project comment style through the repository-level format file, and
`clang-tidy` works best with a CMake compilation database. `cpplint` rules are defined in `CPPLINT.cfg` and are executed by the shared lint script when the tool is installed locally.

## Data Handling

- Do not commit the full NYC dataset to the repository.
- Keep large datasets under `data/local/`, which is ignored by git.
- Use committed samples under `data/samples/` for tests and quick local runs.
- Keep checkpoint and resume files out of version control.

## Documentation Expectations

Update the relevant files when needed:

- `README.md`
- `docs/architecture.md`
- `docs/operations.md`
- `docs/recovery.md`
- `docs/testing.md`
- `docs/design/technical-design.md`
- `CHANGELOG.md`

## IDE Integration

- VS Code uses the committed `.vscode/` workspace files for formatting, tasks, and CMake-backed IntelliSense.
- CLion automatically detects `.clang-format` at the project root. It also uses `.clang-tidy` when project files are preferred over IDE settings.
- `cpplint` is not a native CLion inspection. Run it through `make lint` or `bash scripts/check-style.sh`, which keeps CLion and terminal workflows aligned.
