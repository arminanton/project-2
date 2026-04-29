/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CsvReaderRecord.cpp
 * Purpose:    Reads one logical CSV record, including quoted newlines.
 * ============================================================================
 */

#include "data/CsvReader.h"

namespace geopulse
{
namespace data
{

/** @brief Reads through newline only when that newline is outside quotes. */
bool CsvReader::_readRecord(std::string* record)
{
    if (record == nullptr || !_input.is_open())
    {
        return false;
    }
    record->clear();
    bool quoted = false;
    char current = '\0';
    while (_input.get(current))
    {
        ++_byteOffset;
        record->push_back(current);
        if (current == '"')
        {
            if (quoted && _input.peek() == '"')
            {
                _input.get(current);
                ++_byteOffset;
                record->push_back(current);
                continue;
            }
            quoted = !quoted;
        }
        if (!quoted && current == '\n')
        {
            break;
        }
    }
    return !record->empty();
}

} // namespace data
} // namespace geopulse
