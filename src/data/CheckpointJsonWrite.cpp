/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CheckpointJsonWrite.cpp
 * Purpose:    Writes simple JSON fields used by checkpoint files.
 * ============================================================================
 */

#include "data/Checkpoint.h"
#include "data/CheckpointJson.h"

#include <ostream>

namespace geopulse
{
namespace data
{
namespace checkpoint_json
{

/** Escapes only the characters that can break our generated JSON strings. */
std::string escape(const std::string& value)
{
    std::string escaped;
    for (std::size_t index = 0; index < value.size(); ++index)
    {
        const char current = value[index];
        if (current == '\\' || current == '"')
        {
            escaped.push_back('\\');
        }
        escaped.push_back(current);
    }
    return escaped;
}

/** @brief Writes a quoted JSON string property. */
void writeString(
    std::ostream* output,
    const std::string& key,
    const std::string& value,
    bool last
)
{
    *output << "  \"" << key << "\": \"" << escape(value) << "\"";
    *output << (last ? "\n" : ",\n");
}

/** @brief Writes an unsigned JSON number property. */
void writeNumber(
    std::ostream* output, const std::string& key, std::uint64_t value, bool last
)
{
    *output << "  \"" << key << "\": " << value;
    *output << (last ? "\n" : ",\n");
}

/** @brief Writes a JSON boolean property. */
void writeBool(
    std::ostream* output, const std::string& key, bool value, bool last
)
{
    *output << "  \"" << key << "\": " << (value ? "true" : "false");
    *output << (last ? "\n" : ",\n");
}

} // namespace checkpoint_json
} // namespace data
} // namespace geopulse
