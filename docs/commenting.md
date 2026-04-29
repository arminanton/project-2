# Commenting Standard

## Purpose

GeoPulse follows the comment style already used in prior
course submissions. Comments are treated as part of the
deliverable because they make implementation decisions easy
to review. Comments are required across the project, not
only in non-obvious code.

This document is subordinate to `skills.md`. If anything
here conflicts with `skills.md`, `skills.md` wins.

## File Header Pattern

Start every `.h`, `.hpp`, `.cpp`, and test file in scope
with the canonical block-comment banner:

```cpp
/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    <filename>
 * Purpose: <short file purpose>
 * ============================================================================
 */
```

The `// ====` line-comment banner form is FORBIDDEN.
StyleGuardTest rejects it.

## Required Comment Types

- File header banner (the `/* === */` block above)
- Class and struct intent comments (Doxygen block above
  the type)
- Public method documentation (Doxygen — see "Doxygen
  rules" below)
- Helper function intent comments
- Test scenario comments
- Inline comments for fields, invariants, and edge-
  sensitive values when their role is not self-evident
  from the name

Note: section-divider comments (`// === Section ===` or
similar) inside file bodies are FORBIDDEN. Use semantic
file splits instead when a file's logic clusters into
distinct groups.

## Doxygen Rules

The single-line `/** @brief ... */` form is permitted ONLY
for zero-parameter, single-return-value accessors and
predicates whose name fully telegraphs behavior
(`size()`, `empty()`, `isValid()`).

The full block form is REQUIRED whenever a function has
parameters, a non-trivial return contract, throws
exceptions, or has invariants worth documenting. The block
MUST include:

- `@brief` summary
- `@param` for every parameter
- `@return` if return is non-void and not self-evident
- `@throws` for any documented exception path

**Information conservation:** Existing `@param`,
`@return`, and `@throws` tags MUST NOT be deleted as part
of refactoring. Tightening wording is fine. Removing tags
is a regression and must be reverted.

Trailing `/**< ... */` member comments are FORBIDDEN.
Use a plain `// ...` line above the member instead.

## Writing Rules

- Explain intent in plain English. Explain WHY, the
  invariant, the gotcha, or the role in the broader
  system. Never paraphrase syntax or type.
- Voice: senior CS student tutoring a beginner.
  Mechanically precise, not poetic.
- Keep comments accurate and specific.
- Update comments when behavior changes.
- Do NOT remove useful comments unless you replace them
  with at least equivalent information. A diff that
  removes documentation without replacement is a
  regression.
- Keep comments formatter-friendly. `.clang-format` has
  `ReflowComments: false`, so manual line breaks are
  preserved — wrap comments at 80 columns yourself.

## Test Comments

In tests, explain:

- the scenario being exercised
- why the scenario matters (what bug or invariant it
  guards against)
- what the assertions are proving

## Practical Rule

Do not treat comments as rare exceptions. File headers,
public methods, helper methods, tests, and important
member fields should all carry comments in the same
explanatory style shown in prior course submissions.

## Naming and Namespace Alignment

Comments should use the same terminology as the code.
Class and struct names in `CamelCase`, public methods in
`camelBack`, private helpers and private members with
their leading underscore. Do not add comments that
suggest `using namespace std;` is acceptable. Use explicit
`std::` qualification in examples and comments.
