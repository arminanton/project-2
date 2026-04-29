/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    BenchmarkQueries.cpp
 * Purpose:    Chooses deterministic benchmark query samples.
 * ============================================================================
 */

#include "benchmark/BenchmarkInternals.h"

#include <algorithm>

namespace geopulse
{
namespace benchmark
{

/** @brief Selects evenly spaced points so benchmark queries are repeatable. */
std::vector<core::Point> chooseQueries(
    const std::vector<core::Point>& points, std::size_t requestedCount
)
{
    std::vector<core::Point> queries;
    if (points.empty() || requestedCount == 0)
    {
        return queries;
    }
    const std::size_t count = std::min(requestedCount, points.size());
    if (count == 1)
    {
        queries.push_back(points[points.size() / 2]);
        return queries;
    }
    for (std::size_t index = 0; index < count; ++index)
    {
        const std::size_t pointIndex =
            index * (points.size() - 1) / (count - 1);
        queries.push_back(points[pointIndex]);
    }
    return queries;
}

/** @brief Creates a square range query around a point in projected miles. */
core::BoundingBox boxAround(const core::Point& point, double halfSizeMiles)
{
    return core::BoundingBox(
        point.xMiles - halfSizeMiles,
        point.xMiles + halfSizeMiles,
        point.yMiles - halfSizeMiles,
        point.yMiles + halfSizeMiles
    );
}

} // namespace benchmark
} // namespace geopulse
