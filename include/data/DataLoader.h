/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    DataLoader.h
 * Purpose:    Exposes CSV loading with optional checkpoint recovery.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_DATA_LOADER_H
#define GEOPULSE_DATA_DATA_LOADER_H

#include <cstdint>
#include <functional>
#include <string>

#include "data/DataSet.h"

namespace geopulse
{
namespace data
{

/** @brief Progress snapshot used by optional user-interface callbacks. */
struct LoadProgress
{
    std::uint64_t rowsProcessed = 0; // Logical rows processed.
    std::uint64_t acceptedRows = 0; // Accepted rows so far.
    std::uint64_t excludedRows = 0; // Excluded rows so far.
    std::uint64_t bytesRead = 0; // Current input byte offset.
    std::uint64_t totalBytes = 0; // Source file size.
    double percentComplete = 0.0; // Approximate file progress.
};

/** @brief Options keep recovery optional to avoid benchmark cache overhead. */
struct DataLoaderOptions
{
    bool enableRecovery = false; // Write checkpoint/cache files.
    bool reuseCompletedCache = false; // Trust a completed cache.
    std::uint64_t checkpointIntervalRows = 100000;
    std::uint64_t progressIntervalRows = 250000;
    std::string checkpointPath; // Optional checkpoint override.
    std::string cachePath; // Optional cache path override.
    std::function<void(const LoadProgress&)> progressCallback;
};

/** @brief Loads the collision CSV into records and indexable points. */
class DataLoader
{
public:
    /** @brief Reads sourcePath and returns accepted records, points, counts. */
    DataSet load(
        const std::string& sourcePath, const DataLoaderOptions& options
    ) const;
};

} // namespace data
} // namespace geopulse

#endif
