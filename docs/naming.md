# Naming and Namespace Rules

## Purpose

GeoPulse follows the naming style already used in prior
course submissions, but it avoids blanket namespace
imports so the code remains explicit and reviewable.

This document is subordinate to `skills.md`. If anything
here conflicts with `skills.md`, `skills.md` wins.

## Namespace Rule

- Do not use `using namespace std;` in this repository.
- Do not place blanket `using namespace ...;` directives
  in headers.
- Narrow `using std::...;` declarations may be used
  inside a small `.cpp` scope when they improve
  readability without hiding ownership or type origin.

## Identifier Rules

- namespaces: `lower_case`
- classes and structs: `CamelCase`
- free functions and public methods: `camelBack`
- private helper methods: `_camelBack`
- local variables and parameters: `camelBack`
- private data members: `_camelBack`
- anonymous-namespace helper functions in `.cpp` files:
  `_camelBack` (treated as private helpers)
- constants: prefer descriptive names and keep them
  consistent within the owning scope. Constants follow
  the casing convention of the scope they live in
  (file-scope `kCamelBack` or `CamelBack` are both
  acceptable as long as one form is used consistently
  within the file).

## What is NOT prefixed with `_`

The leading underscore marks PRIVATE OWNERSHIP. It is not
applied to:

- public methods (regardless of whether they are virtual,
  override, or final)
- virtual override implementations of public-base methods,
  even when declared `private` in the derived class — the
  override inherits the base method's name verbatim
- constructors, destructors, copy/move special members,
  and operator overloads
- protected members exposed for derived-class use that are
  effectively part of an internal API contract
- function parameters and local variables in any scope

The underscore is for class-private members, class-private
helper methods, and `.cpp` anonymous-namespace helpers
only.

## Practical Examples

- class: `KDTree`
- struct: `BoundingBox`
- public method: `radiusQuery`
- private helper method: `_splitNode`
- private member: `_root`
- anonymous-ns helper: `_parseHeaderRow` (in a .cpp file)
- local variable: `rowCount`
- parameter: `path`

## Why This Rule Exists

This style matches the readable, explanatory style used in
prior course submissions while keeping ownership,
helpers, and public APIs easy for TAs to inspect. The
explicit "what is NOT prefixed" list exists because a
prior automated session over-applied the underscore to
override methods, which is wrong — virtual overrides keep
their base-class name regardless of access level in the
derived class.
