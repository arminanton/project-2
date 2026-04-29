/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CheckpointJson.h
 * Purpose:    Declares tiny JSON helpers for checkpoint persistence.
 * ============================================================================
 */

#ifndef GEOPULSE_SRC_DATA_CHECKPOINT_JSON_H
#define GEOPULSE_SRC_DATA_CHECKPOINT_JSON_H

#include <cstdint>
#include <iosfwd>
#include <string>

namespace geopulse
{
namespace data
{
namespace checkpoint_json
{

std::string escape(const std::string& value);
void writeString(
    std::ostream* output,
    const std::string& key,
    const std::string& value,
    bool last
);
void writeNumber(
    std::ostream* output, const std::string& key, std::uint64_t value, bool last
);
void writeBool(
    std::ostream* output, const std::string& key, bool value, bool last
);
bool readString(
    const std::string& text, const std::string& key, std::string* value
);
bool readNumber(
    const std::string& text, const std::string& key, std::uint64_t* value
);
bool readBool(const std::string& text, const std::string& key, bool* value);

} // namespace checkpoint_json
} // namespace data
} // namespace geopulse

#endif
