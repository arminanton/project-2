/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    DataLoaderContext.cpp
 * Purpose:    Opens the CSV and validates its schema before loading rows.
 * ============================================================================
 */

#include "data/DataLoaderContext.h"

#include <stdexcept>

namespace geopulse
{
namespace data
{
namespace loader
{

/** @brief Opens the input file and resolves all required CSV columns. */
LoadContext createContext(
    const std::string& sourcePath,
    const DataLoaderOptions& options,
    CsvReader* reader
)
{
    if (reader == nullptr)
    {
        throw std::runtime_error("internal loader reader was null");
    }
    LoadContext context;
    context.sourcePath = sourcePath;
    context.options = options;
    context.identity = readFileIdentity(sourcePath);
    if (!context.identity.valid || !reader->open(sourcePath))
    {
        throw std::runtime_error("unable to open dataset file: " + sourcePath);
    }
    CsvRow header;
    if (!reader->readHeader(&header))
    {
        throw std::runtime_error("dataset file has no header: " + sourcePath);
    }
    context.headerSignature = stableSignature(joinHeaderSignature(header));
    context.columns = resolveCollisionColumns(header);
    if (!context.columns.valid)
    {
        throw std::runtime_error(missingColumnMessage(context.columns));
    }
    context.checkpointPath = options.checkpointPath.empty()
                                 ? defaultCheckpointPath(sourcePath)
                                 : options.checkpointPath;
    context.cachePath = options.cachePath.empty() ? defaultCachePath(sourcePath)
                                                  : options.cachePath;
    return context;
}

} // namespace loader
} // namespace data
} // namespace geopulse
