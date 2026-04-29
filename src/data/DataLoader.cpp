/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    DataLoader.cpp
 * Purpose:    Coordinates CSV loading, validation, and optional recovery.
 * ============================================================================
 */

#include "data/DataLoader.h"

#include <chrono>
#include <stdexcept>

#include "data/DataLoaderContext.h"

namespace geopulse
{
namespace data
{

/** Loads the dataset and returns records plus lightweight spatial points. */
DataSet DataLoader::load(
    const std::string& sourcePath, const DataLoaderOptions& options
) const
{
    const auto startedAt = std::chrono::steady_clock::now();
    CsvReader reader;
    const loader::LoadContext context =
        loader::createContext(sourcePath, options, &reader);

    DataSet dataSet;
    if (loader::tryLoadCompleted(context, &dataSet))
    {
        return dataSet;
    }

    std::ofstream cache;
    const bool resumed =
        loader::tryResumePartial(context, &reader, &dataSet, &cache);
    if (!resumed && !loader::openFreshCache(context, &cache))
    {
        throw std::runtime_error("unable to open recovery cache");
    }

    loader::parseRows(context, &reader, &dataSet, &cache);
    loader::writeCompleteCheckpoint(context, reader, dataSet);
    const auto finishedAt = std::chrono::steady_clock::now();
    dataSet.statistics.elapsedSeconds =
        std::chrono::duration<double>(finishedAt - startedAt).count();
    return dataSet;
}

} // namespace data
} // namespace geopulse
