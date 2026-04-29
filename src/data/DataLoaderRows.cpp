/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataLoaderRows.cpp
 * Purpose:    Parses each CSV row and updates statistics.
 * ============================================================================
 */

#include "data/DataLoaderContext.h"

#include "data/DataCache.h"
#include "data/CollisionParser.h"

namespace geopulse
{
namespace data
{
namespace loader
{
namespace
{

/** @brief Adds one accepted row to the dataset and optional recovery cache. */
void acceptRow(
    DataSet* dataSet, std::ofstream* cache, const CollisionParseResult& parsed
)
{
    dataSet->records.push_back(parsed.record);
    dataSet->points.push_back(parsed.point);
    ++dataSet->statistics.acceptedRows;
    appendRecordToCache(cache, parsed.record);
}

/** @brief Adds one rejected row to the correct statistics buckets. */
void rejectRow(DataSet* dataSet, const CollisionParseResult& parsed)
{
    ++dataSet->statistics.excludedRows;
    dataSet->statistics.missingCoordinateRows +=
        parsed.missingCoordinate ? 1 : 0;
    dataSet->statistics.invalidCoordinateRows +=
        parsed.invalidCoordinate ? 1 : 0;
}

} // namespace

/** @brief Parses all remaining rows from the current reader position. */
void parseRows(
    const LoadContext& context,
    CsvReader* reader,
    DataSet* dataSet,
    std::ofstream* cache
)
{
    CsvRow row;
    dataSet->statistics.fileSizeBytes = context.identity.fileSize;
    while (reader->readRow(&row))
    {
        dataSet->statistics.totalRows = reader->rowNumber();
        const CollisionParseResult parsed = parseCollisionRow(
            row, context.columns, reader->rowNumber(), dataSet->records.size()
        );
        parsed.accepted ? acceptRow(dataSet, cache, parsed)
                        : rejectRow(dataSet, parsed);
        if (context.options.enableRecovery &&
            context.options.checkpointIntervalRows > 0 &&
            dataSet->statistics.totalRows %
                    context.options.checkpointIntervalRows ==
                0)
        {
            writeProgressCheckpoint(context, *reader, *dataSet, false);
        }
        if (context.options.progressCallback &&
            context.options.progressIntervalRows > 0 &&
            dataSet->statistics.totalRows %
                    context.options.progressIntervalRows ==
                0)
        {
            publishProgress(context, *dataSet, *reader);
        }
    }
}

} // namespace loader
} // namespace data
} // namespace geopulse
