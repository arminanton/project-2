/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataCacheLoad.cpp
 * Purpose:    Loads accepted rows from the recovery cache.
 * ============================================================================
 */

#include "data/DataCache.h"

#include <cstdlib>
#include <fstream>
#include <vector>

#include "core/Projection.h"

namespace geopulse
{
namespace data
{
namespace
{

/** @brief Splits the tab-separated cache format into raw fields. */
std::vector<std::string> splitTabs(const std::string& line)
{
    std::vector<std::string> fields;
    std::string field;
    for (std::size_t index = 0; index < line.size(); ++index)
    {
        if (line[index] == '\t')
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field.push_back(line[index]);
        }
    }
    fields.push_back(field);
    return fields;
}

} // namespace

/** Loads all accepted records that were written before an interruption. */
bool loadAcceptedCache(
    const std::string& cachePath, std::uint64_t expectedRows, DataSet* dataSet
)
{
    if (dataSet == nullptr)
    {
        return false;
    }
    std::ifstream input(cachePath.c_str(), std::ios::in | std::ios::binary);
    if (!input.is_open())
    {
        return false;
    }
    std::string line;
    while (std::getline(input, line))
    {
        const std::vector<std::string> fields = splitTabs(line);
        if (fields.size() != 9)
        {
            return false;
        }
        CollisionRecord record;
        record.sourceRowNumber = std::strtoull(fields[0].c_str(), nullptr, 10);
        record.collisionId = cacheUnescape(fields[1]);
        record.crashDate = cacheUnescape(fields[2]);
        record.crashTime = cacheUnescape(fields[3]);
        record.borough = cacheUnescape(fields[4]);
        record.latitude = std::strtod(fields[5].c_str(), nullptr);
        record.longitude = std::strtod(fields[6].c_str(), nullptr);
        record.personsInjured =
            static_cast<int>(std::strtol(fields[7].c_str(), nullptr, 10));
        record.personsKilled =
            static_cast<int>(std::strtol(fields[8].c_str(), nullptr, 10));
        const std::size_t index = dataSet->records.size();
        dataSet->records.push_back(record);
        dataSet->points.push_back(
            core::makePoint(index, record.latitude, record.longitude)
        );
    }
    return dataSet->records.size() == expectedRows;
}

} // namespace data
} // namespace geopulse
