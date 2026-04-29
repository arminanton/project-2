/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BenchmarkRunner.cpp
 * Purpose:    Runs all comparable spatial-index benchmarks.
 * ============================================================================
 */

#include "benchmark/BenchmarkRunner.h"

#include "benchmark/BenchmarkInternals.h"
#include "index/KDTree.h"
#include "index/LinearScanIndex.h"
#include "index/QuadTree.h"

namespace geopulse
{
namespace benchmark
{

/** @brief Builds Linear Scan, KD-tree, and Quadtree over the same data. */
BenchmarkReport BenchmarkRunner::run(
    const data::DataSet& dataSet, const BenchmarkOptions& options
) const
{
    BenchmarkReport report;
    report.pointCount = dataSet.points.size();
    report.radiusMiles = options.radiusMiles;
    report.rangeHalfSizeMiles = options.rangeHalfSizeMiles;
    const std::vector<core::Point> queries =
        chooseQueries(dataSet.points, options.queryCount);
    report.queryCount = queries.size();

    index::LinearScanIndex baseline;
    report.results.push_back(benchmarkIndex(
        &baseline, dataSet.points, queries, options, baseline, true
    ));

    index::KDTree kdTree;
    report.results.push_back(benchmarkIndex(
        &kdTree, dataSet.points, queries, options, baseline, false
    ));

    index::QuadTree quadTree;
    report.results.push_back(benchmarkIndex(
        &quadTree, dataSet.points, queries, options, baseline, false
    ));
    return report;
}

} // namespace benchmark
} // namespace geopulse
