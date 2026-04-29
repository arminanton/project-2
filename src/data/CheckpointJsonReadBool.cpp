/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CheckpointJsonReadBool.cpp
 * Purpose:    Parses boolean values from the JSON subset written by GeoPulse.
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

/** @brief Reads a boolean property from the checkpoint text. */
bool readBool(const std::string& text, const std::string& key, bool* value)
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
    const std::size_t first = text.find_first_not_of(" \t\r\n", start);
    *value = first != std::string::npos && text.find("true", first) == first;
    return true;
}

} // namespace checkpoint_json
} // namespace data
} // namespace geopulse
