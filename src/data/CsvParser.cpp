/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CsvParser.cpp
 * Purpose:    Splits one complete CSV record into field strings.
 * ============================================================================
 */

#include "data/CsvReader.h"

namespace geopulse
{
namespace data
{

/**
 * Parses RFC-style CSV quotes used by the NYC export.
 *
 * Commas split fields only outside quotes. Two quotes inside a quoted field
 * become one literal quote character.
 */
CsvRow parseCsvRecord(const std::string& record)
{
    CsvRow fields;
    std::string field;
    bool quoted = false;

    for (std::size_t index = 0; index < record.size(); ++index)
    {
        const char current = record[index];
        const bool doubledQuote = quoted && current == '"' &&
                                  index + 1 < record.size() &&
                                  record[index + 1] == '"';

        if (doubledQuote)
        {
            field.push_back('"');
            ++index;
        }
        else if (current == '"')
        {
            quoted = !quoted;
        }
        else if (!quoted && current == ',')
        {
            fields.push_back(field);
            field.clear();
        }
        else if (!quoted && (current == '\n' || current == '\r'))
        {
            continue;
        }
        else
        {
            field.push_back(current);
        }
    }

    fields.push_back(field);
    return fields;
}

} // namespace data
} // namespace geopulse
