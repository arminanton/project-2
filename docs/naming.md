# Naming and Namespace Rules

## Purpose
GeoPulse follows the naming style already used in prior course submissions, but it avoids blanket namespace imports so the code remains explicit and reviewable.

## Namespace Rule
- Do not use `using namespace std;` in this repository.
- Do not place blanket `using namespace ...;` directives in headers.
- Narrow `using std::...;` declarations may be used inside a small `.cpp` scope when they improve readability without hiding ownership or type origin.

## Identifier Rules
- namespaces: `lower_case`
- classes and structs: `CamelCase`
- free functions and public methods: `camelBack`
- private helper methods: `_camelBack`
- local variables and parameters: `camelBack`
- private data members: `_camelBack`
- constants: prefer descriptive names and keep them consistent within the owning scope

## Practical Examples
- class: `KDTree`
- struct: `BoundingBox`
- public method: `radiusQuery`
- private helper: `_splitNode`
- private member: `_root`
- local variable: `rowCount`

## Why This Rule Exists
This style matches the readable, explanatory style used in prior course submissions while keeping ownership, helpers, and public APIs easy for TAs to inspect.
