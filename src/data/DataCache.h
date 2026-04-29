/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    DataCache.h
 * Purpose:    Declares accepted-record cache helpers for recovery mode.
 * ============================================================================
 */

#ifndef GEOPULSE_SRC_DATA_DATA_CACHE_H
#define GEOPULSE_SRC_DATA_DATA_CACHE_H

#include <cstdint>
#include <fstream>
#include <string>

#include "data/CollisionRecord.h"
#include "data/DataSet.h"

namespace geopulse
{
namespace data
{

std::string cacheEscape(const std::string& value);
std::string cacheUnescape(const std::string& value);
bool openCache(const std::string& path, bool append, std::ofstream* output);
void appendRecordToCache(std::ofstream* cache, const CollisionRecord& record);
bool loadAcceptedCache(
    const std::string& cachePath, std::uint64_t expectedRows, DataSet* dataSet
);

} // namespace data
} // namespace geopulse

#endif
