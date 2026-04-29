/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CheckpointJsonRead.cpp
 * Purpose:    Reads the small JSON subset written by GeoPulse checkpoints.
 * ============================================================================
 */

#include "data/CheckpointJson.h"

#include <cstdlib>

namespace geopulse
{
namespace data
{
namespace checkpoint_json
{
namespace
{

/** @brief Locates the value portion after a JSON property name. */
std::size_t valueStart(const std::string& text, const std::string& key)
{
    const std::string token = "\"" + key + "\"";
    const std::size_t keyPos = text.find(token);
    if (keyPos == std::string::npos)
    {
        return std::string::npos;
    }
    const std::size_t colon = text.find(':', keyPos + token.size());
    return colon == std::string::npos ? colon : colon + 1;
}

} // namespace

/** @brief Reads a quoted string property from the checkpoint text. */
bool readString(
    const std::string& text, const std::string& key, std::string* value
)
{
    const std::size_t start = text.find('"', valueStart(text, key));
    if (start == std::string::npos || value == nullptr)
    {
        return false;
    }
    std::string result;
    for (std::size_t index = start + 1; index < text.size(); ++index)
    {
        const char current = text[index];
        if (current == '"')
        {
            *value = result;
            return true;
        }
        if (current == '\\' && index + 1 < text.size())
        {
            ++index;
        }
        result.push_back(text[index]);
    }
    return false;
}

/** @brief Reads an unsigned integer property from the checkpoint text. */
bool readNumber(
    const std::string& text, const std::string& key, std::uint64_t* value
)
{
    if (value == nullptr)
    {
        return false;
    }
    const std::size_t start = valueStart(text, key);
    if (start == std::string::npos)
    {
        return false;
    }
    *value = std::strtoull(text.c_str() + start, nullptr, 10);
    return true;
}

} // namespace checkpoint_json
} // namespace data
} // namespace geopulse
