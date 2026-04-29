/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    BenchmarkRunner.h
 * Purpose:    Declares benchmark result types and runner facade.
 * ============================================================================
 */

#ifndef GEOPULSE_BENCHMARK_BENCHMARK_RUNNER_H
#define GEOPULSE_BENCHMARK_BENCHMARK_RUNNER_H

#include <cstddef>
#include <string>
#include <vector>

#include "core/Constants.h"
#include "data/DataSet.h"

namespace geopulse
{
namespace benchmark
{

/** @brief One printed row in the benchmark table. */
struct AlgorithmBenchmarkResult
{
    std::string algorithm;            // Algorithm label
    double buildMilliseconds = 0.0;   // Index build time
    double nearestMilliseconds = 0.0; // Average nearest time
    double radiusMilliseconds = 0.0;  // Average radius time
    double rangeMilliseconds = 0.0;   // Average range time
    bool nearestCorrect = false;   // True if nearest search matches linear scan
    bool radiusCorrect = false;    // True if radius search matches linear scan
    bool rangeCorrect = false;     // True if range search matches linear scan
    std::size_t radiusMatches = 0; // Number of points found by radius search
    std::size_t rangeMatches = 0;  // Number of points found by range search
};

/** @brief Complete benchmark output that can be printed or tested. */
struct BenchmarkReport
{
    std::size_t pointCount = 0; // Number of indexed points
    std::size_t queryCount = 0; // Number of query samples
    double radiusMiles = core::constants::kBenchmarkRadiusMiles;
    double rangeHalfSizeMiles = core::constants::kBenchmarkRangeHalfMiles;
    std::vector<AlgorithmBenchmarkResult> results; // Rows

    /** @brief Formats the report as a deterministic text table. */
    std::string toText() const;
};

/** @brief Tunable benchmark settings. */
struct BenchmarkOptions
{
    std::size_t queryCount = core::constants::kBenchmarkQueryCount;
    double radiusMiles = core::constants::kBenchmarkRadiusMiles;
    double rangeHalfSizeMiles = core::constants::kBenchmarkRangeHalfMiles;
};

/** @brief Builds all indexes, times them, checks against Linear Scan. */
class BenchmarkRunner
{
public:
    /** @brief Runs the full benchmark suite on a loaded dataset. */
    BenchmarkReport run(
        const data::DataSet& dataSet, const BenchmarkOptions& options
    ) const;
};

} // namespace benchmark
} // namespace geopulse

#endif
