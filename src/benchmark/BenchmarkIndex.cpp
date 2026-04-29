/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BenchmarkIndex.cpp
 * Purpose:    Times one index and compares it with linear scan.
 * ============================================================================
 */

#include "benchmark/BenchmarkInternals.h"

#include <chrono>

#include "query/ResultComparator.h"

namespace geopulse
{
namespace benchmark
{
namespace
{

using Clock = std::chrono::steady_clock;

/** @brief Converts a measured duration into milliseconds. */
double elapsedMs(const Clock::time_point& start, const Clock::time_point& end)
{
    return std::chrono::duration<double, std::milli>(end - start).count();
}

} // namespace

/** @brief Builds, queries, times, and validates one spatial index. */
AlgorithmBenchmarkResult benchmarkIndex(
    index::SpatialIndex* spatialIndex,
    const std::vector<core::Point>& points,
    const std::vector<core::Point>& queries,
    const BenchmarkOptions& options,
    const index::LinearScanIndex& baseline,
    bool baselineAlgorithm
)
{
    AlgorithmBenchmarkResult result;
    result.algorithm = spatialIndex->name();
    const Clock::time_point buildStart = Clock::now();
    spatialIndex->build(points);
    result.buildMilliseconds = elapsedMs(buildStart, Clock::now());
    result.nearestCorrect = true;
    result.radiusCorrect = true;
    result.rangeCorrect = true;
    double nearestTotal = 0.0;
    double radiusTotal = 0.0;
    double rangeTotal = 0.0;
    for (std::size_t index = 0; index < queries.size(); ++index)
    {
        const core::Point& query = queries[index];
        const Clock::time_point nearStart = Clock::now();
        const core::NearestResult nearest = spatialIndex->nearest(query);
        nearestTotal += elapsedMs(nearStart, Clock::now());
        const Clock::time_point radiusStart = Clock::now();
        const core::RecordIdList radius =
            spatialIndex->radiusQuery(query, options.radiusMiles);
        radiusTotal += elapsedMs(radiusStart, Clock::now());
        const core::BoundingBox box =
            boxAround(query, options.rangeHalfSizeMiles);
        const Clock::time_point rangeStart = Clock::now();
        const core::RecordIdList range = spatialIndex->rangeQuery(box);
        rangeTotal += elapsedMs(rangeStart, Clock::now());
        result.nearestCorrect &=
            baselineAlgorithm ||
            query::sameNearest(nearest, baseline.nearest(query));
        result.radiusCorrect &=
            baselineAlgorithm ||
            query::sameRecordSet(
                radius, baseline.radiusQuery(query, options.radiusMiles)
            );
        result.rangeCorrect &=
            baselineAlgorithm ||
            query::sameRecordSet(range, baseline.rangeQuery(box));
        result.radiusMatches = radius.size();
        result.rangeMatches = range.size();
    }
    const double divisor =
        queries.empty() ? 1.0 : static_cast<double>(queries.size());
    result.nearestMilliseconds = nearestTotal / divisor;
    result.radiusMilliseconds = radiusTotal / divisor;
    result.rangeMilliseconds = rangeTotal / divisor;
    return result;
}

} // namespace benchmark
} // namespace geopulse
