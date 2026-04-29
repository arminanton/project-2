/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataLoaderFresh.cpp
 * Purpose:    Handles opening a fresh accepted-record cache for new loads.
 * ============================================================================
 */

#include "data/DataLoaderContext.h"

#include "data/DataCache.h"

namespace geopulse
{
namespace data
{
namespace loader
{

/** Opens a fresh accepted-record cache for a fresh recovery-enabled load. */
bool openFreshCache(const LoadContext& context, std::ofstream* cache)
{
    if (!context.options.enableRecovery)
    {
        return true;
    }
    removeFileIfExists(context.cachePath);
    return openCache(context.cachePath, false, cache);
}

} // namespace loader
} // namespace data
} // namespace geopulse
