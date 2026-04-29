/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataCache.cpp
 * Purpose:    Writes accepted rows for true resume support.
 * ============================================================================
 */

#include "data/DataCache.h"

#include <iomanip>

namespace geopulse
{
namespace data
{

/** @brief Opens the recovery cache either for append or replacement. */
bool openCache(const std::string& path, bool append, std::ofstream* output)
{
    if (output == nullptr)
    {
        return false;
    }
    const std::ios::openmode mode = std::ios::out | std::ios::binary |
                                    (append ? std::ios::app : std::ios::trunc);
    output->open(path.c_str(), mode);
    return output->is_open();
}

/** @brief Appends one accepted collision to the recovery cache. */
void appendRecordToCache(std::ofstream* cache, const CollisionRecord& record)
{
    if (cache == nullptr || !cache->is_open())
    {
        return;
    }
    (*cache) << record.sourceRowNumber << '\t'
             << cacheEscape(record.collisionId) << '\t'
             << cacheEscape(record.crashDate) << '\t'
             << cacheEscape(record.crashTime) << '\t'
             << cacheEscape(record.borough) << '\t' << std::setprecision(17)
             << record.latitude << '\t' << std::setprecision(17)
             << record.longitude << '\t' << record.personsInjured << '\t'
             << record.personsKilled << '\n';
}

} // namespace data
} // namespace geopulse
