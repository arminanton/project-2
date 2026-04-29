/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataLoaderRecovery.cpp
 * Purpose:    Handles completed-cache and partial-resume loader recovery.
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
namespace
{

/** @brief Copies checkpoint counters into DataSet statistics. */
void applyStats(
    const LoadContext& context, const CheckpointState& state, DataSet* dataSet
)
{
    dataSet->statistics.totalRows = state.lastRowNumber;
    dataSet->statistics.acceptedRows = state.acceptedRows;
    dataSet->statistics.excludedRows = state.excludedRows;
    dataSet->statistics.missingCoordinateRows = state.missingRows;
    dataSet->statistics.invalidCoordinateRows = state.invalidRows;
    dataSet->statistics.fileSizeBytes = context.identity.fileSize;
}

} // namespace

/** Loads a complete previous accepted cache when the user allows reuse. */
bool tryLoadCompleted(const LoadContext& context, DataSet* dataSet)
{
    CheckpointState state;
    if (!context.options.reuseCompletedCache ||
        !readCheckpoint(context.checkpointPath, &state) || !state.complete)
    {
        return false;
    }
    if (!checkpointMatches(
            state, context.sourcePath, context.identity, context.headerSignature
        ))
    {
        return false;
    }
    if (!loadAcceptedCache(state.cachePath, state.acceptedRows, dataSet))
    {
        return false;
    }
    applyStats(context, state, dataSet);
    return true;
}

/** Resumes an incomplete load by rebuilding memory from the accepted cache. */
bool tryResumePartial(
    const LoadContext& context,
    CsvReader* reader,
    DataSet* dataSet,
    std::ofstream* cache
)
{
    CheckpointState state;
    if (!context.options.enableRecovery ||
        !readCheckpoint(context.checkpointPath, &state) || state.complete)
    {
        return false;
    }
    if (!checkpointMatches(
            state, context.sourcePath, context.identity, context.headerSignature
        ))
    {
        return false;
    }
    if (!loadAcceptedCache(state.cachePath, state.acceptedRows, dataSet))
    {
        return false;
    }
    applyStats(context, state, dataSet);
    return reader->seekTo(state.byteOffset, state.lastRowNumber) &&
           openCache(state.cachePath, true, cache);
}

} // namespace loader
} // namespace data
} // namespace geopulse
