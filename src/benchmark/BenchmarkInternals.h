/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    BenchmarkInternals.h
 * Purpose:    Declares private helpers for benchmark implementation files.
 * ============================================================================
 */

#ifndef GEOPULSE_SRC_BENCHMARK_BENCHMARK_INTERNALS_H
#define GEOPULSE_SRC_BENCHMARK_BENCHMARK_INTERNALS_H

#include <vector>

#include "benchmark/BenchmarkRunner.h"
#include "core/BoundingBox.h"
#include "index/LinearScanIndex.h"
#include "index/SpatialIndex.h"

namespace geopulse
{
namespace benchmark
{

std::vector<core::Point> chooseQueries(
    const std::vector<core::Point>& points, std::size_t requestedCount
);
core::BoundingBox boxAround(const core::Point& point, double halfSizeMiles);
AlgorithmBenchmarkResult benchmarkIndex(
    index::SpatialIndex* spatialIndex,
    const std::vector<core::Point>& points,
    const std::vector<core::Point>& queries,
    const BenchmarkOptions& options,
    const index::LinearScanIndex& baseline,
    bool baselineAlgorithm
);

} // namespace benchmark
} // namespace geopulse

#endif
