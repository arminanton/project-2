/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataCacheCodec.cpp
 * Purpose:    Escapes and unescapes strings stored in the TSV recovery cache.
 * ============================================================================
 */

#include "data/DataCache.h"

#include <sstream>

namespace geopulse
{
namespace data
{

/** Escapes tabs and line breaks so one accepted record stays on one line. */
std::string cacheEscape(const std::string& value)
{
    std::ostringstream output;
    for (std::size_t index = 0; index < value.size(); ++index)
    {
        const char current = value[index];
        if (current == '\\')
        {
            output << "\\\\";
        }
        else if (current == '\t')
        {
            output << "\\t";
        }
        else if (current == '\n')
        {
            output << "\\n";
        }
        else if (current == '\r')
        {
            output << "\\r";
        }
        else
        {
            output << current;
        }
    }
    return output.str();
}

/** Reverses cacheEscape while loading a previous accepted-record cache. */
std::string cacheUnescape(const std::string& value)
{
    std::ostringstream output;
    bool escaped = false;
    for (std::size_t index = 0; index < value.size(); ++index)
    {
        const char current = value[index];
        if (escaped)
        {
            output
                << (current == 't'   ? '\t'
                    : current == 'n' ? '\n'
                    : current == 'r' ? '\r'
                                     : current);
            escaped = false;
        }
        else if (current == '\\')
        {
            escaped = true;
        }
        else
        {
            output << current;
        }
    }
    return output.str();
}

} // namespace data
} // namespace geopulse
