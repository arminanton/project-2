/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataLoaderProgress.cpp
 * Purpose:    Publishes progress and writes recovery checkpoints.
 * ============================================================================
 */

#include "data/DataLoaderContext.h"

namespace geopulse
{
namespace data
{
namespace loader
{

/** @brief Reports loader progress when a callback was supplied. */
void publishProgress(
    const LoadContext& context, const DataSet& dataSet, const CsvReader& reader
)
{
    if (!context.options.progressCallback)
    {
        return;
    }
    LoadProgress progress;
    progress.rowsProcessed = dataSet.statistics.totalRows;
    progress.acceptedRows = dataSet.statistics.acceptedRows;
    progress.excludedRows = dataSet.statistics.excludedRows;
    progress.bytesRead = reader.byteOffset();
    progress.totalBytes = context.identity.fileSize;
    if (progress.totalBytes > 0)
    {
        progress.percentComplete = 100.0 * progress.bytesRead /
                                   static_cast<double>(progress.totalBytes);
    }
    context.options.progressCallback(progress);
}

/** @brief Writes one resumable checkpoint at the current reader position. */
void writeProgressCheckpoint(
    const LoadContext& context,
    const CsvReader& reader,
    const DataSet& dataSet,
    bool complete
)
{
    CheckpointState state;
    state.sourcePath = context.sourcePath;
    state.cachePath = context.cachePath;
    state.headerSignature = context.headerSignature;
    state.fileSize = context.identity.fileSize;
    state.modificationTime = context.identity.modificationTime;
    state.lastRowNumber = dataSet.statistics.totalRows;
    state.byteOffset = reader.byteOffset();
    state.acceptedRows = dataSet.statistics.acceptedRows;
    state.excludedRows = dataSet.statistics.excludedRows;
    state.missingRows = dataSet.statistics.missingCoordinateRows;
    state.invalidRows = dataSet.statistics.invalidCoordinateRows;
    state.complete = complete;
    writeCheckpoint(context.checkpointPath, state);
}

/** @brief Writes the final completed checkpoint after parsing reaches EOF. */
void writeCompleteCheckpoint(
    const LoadContext& context, const CsvReader& reader, const DataSet& dataSet
)
{
    if (context.options.enableRecovery)
    {
        writeProgressCheckpoint(context, reader, dataSet, true);
    }
}

} // namespace loader
} // namespace data
} // namespace geopulse
