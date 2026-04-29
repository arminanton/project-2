/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    DataLoaderContext.h
 * Purpose:    Declares shared loader context helpers.
 * ============================================================================
 */

#ifndef GEOPULSE_SRC_DATA_DATA_LOADER_CONTEXT_H
#define GEOPULSE_SRC_DATA_DATA_LOADER_CONTEXT_H

#include <fstream>
#include <string>

#include "data/Checkpoint.h"
#include "data/CollisionColumns.h"
#include "data/CsvReader.h"
#include "data/DataLoader.h"

namespace geopulse
{
namespace data
{
namespace loader
{

/** @brief Carries validated setup data through the loading pipeline. */
struct LoadContext
{
    std::string sourcePath;
    DataLoaderOptions options;
    FileIdentity identity;
    CollisionColumns columns;
    std::string headerSignature;
    std::string checkpointPath;
    std::string cachePath;
};

LoadContext createContext(
    const std::string& sourcePath,
    const DataLoaderOptions& options,
    CsvReader* reader
);
bool tryLoadCompleted(const LoadContext& context, DataSet* dataSet);
bool tryResumePartial(
    const LoadContext& context,
    CsvReader* reader,
    DataSet* dataSet,
    std::ofstream* cache
);
bool openFreshCache(const LoadContext& context, std::ofstream* cache);
void parseRows(
    const LoadContext& context,
    CsvReader* reader,
    DataSet* dataSet,
    std::ofstream* cache
);
void publishProgress(
    const LoadContext& context, const DataSet& dataSet, const CsvReader& reader
);
void writeProgressCheckpoint(
    const LoadContext& context,
    const CsvReader& reader,
    const DataSet& dataSet,
    bool complete
);
void writeCompleteCheckpoint(
    const LoadContext& context, const CsvReader& reader, const DataSet& dataSet
);

} // namespace loader
} // namespace data
} // namespace geopulse

#endif
