# GeoPulse Style Guide

**Inline comments on member declarations:**
- **Allowed only** when using `// ` (line comment), **and** the entire line fits within 80 columns.
- **Forbidden:** `/**< @brief ... */` trailing-style Doxygen comments. They force awkward wraps, repeat themselves, and produce noise like "True when oracle agrees" three times in a row.
- **Forbidden:** any trailing comment that pushes the line past 80 columns. Move it to the preceding line.
- **Public members** that need external-facing API documentation use a preceding `/** @brief ... */` block on its own line above the declaration.
- **Private/internal members** with non-obvious purpose use a preceding `// ...` line comment.
- **Self-evident members** (e.g., `int count = 0;` named clearly) get **no** comment. Naming carries the weight.
