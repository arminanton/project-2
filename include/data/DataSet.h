/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataSet.h
 * Purpose:    Defines loaded dataset containers and statistics.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_DATA_SET_H
#define GEOPULSE_DATA_DATA_SET_H

#include <cstdint>
#include <vector>

#include "core/Point.h"
#include "data/CollisionRecord.h"

namespace geopulse
{
namespace data
{

/** @brief Counts accepted, rejected, and measured rows during loading. */
struct LoadStatistics
{
    std::uint64_t totalRows = 0;             // Logical CSV rows read.
    std::uint64_t acceptedRows = 0;          // Rows stored as points.
    std::uint64_t excludedRows = 0;          // Missing plus invalid rows.
    std::uint64_t missingCoordinateRows = 0; // Empty coord rows.
    std::uint64_t invalidCoordinateRows = 0; // Bad coord rows.
    std::uint64_t fileSizeBytes = 0;         // Source file size.
    double elapsedSeconds = 0.0;             // Loader wall time.
};

/** @brief Holds all records and lightweight points indexed by algorithms. */
struct DataSet
{
    std::vector<CollisionRecord> records; // Accepted records.
    std::vector<core::Point> points;      // Indexable coordinates.
    LoadStatistics statistics;            // Counts and loader timing.
};

} // namespace data
} // namespace geopulse

#endif
