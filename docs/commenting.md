# Commenting Standard

## Purpose
GeoPulse follows the comment style already used in prior course submissions. Comments are treated as
part of the deliverable because they make implementation decisions easy to review. Comments are required
across the project, not only in non-obvious code.

## File Header Pattern
Start major `.h`, `.hpp`, `.cpp`, and test files with a banner comment block.

Recommended pattern:

```cpp
// ========================================
// Name: Guilherme Armin Da Silva Anton
// UFID: 2641-9801
// COP3530 Project 2 - GeoPulse
// File: <filename>
// Purpose: <short file purpose>
// ========================================
```

## Required Comment Types
- file header banner comments
- section divider comments for major groups of logic
- class and struct intent comments
- helper function intent comments
- test scenario comments
- short inline comments for fields, invariants, and edge-sensitive values

## Writing Rules
- Explain intent in plain English.
- Keep comments accurate and specific.
- Update comments when behavior changes.
- Do not remove useful comments unless you replace them with a better version.
- Keep comments formatter-friendly. Avoid manual alignment that depends on fragile spacing.

## Test Comments
In tests, explain:
- the scenario
- why the scenario matters
- what the assertions are proving


## Practical Rule
Do not treat comments as rare exceptions. File headers, section dividers, public methods, helper methods, tests, and important member fields should all carry comments in the same explanatory style shown in prior course submissions.


## Naming and Namespace Alignment
Comments should use the same terminology as the code. Class and struct names should be written in `CamelCase`, public methods in `camelBack`, and private helpers or private members with their leading underscore when applicable. Do not add comments that suggest `using namespace std;` is acceptable. Use explicit `std::` names in examples and comments.
