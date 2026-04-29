/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BenchmarkReport.cpp
 * Purpose:    Formats benchmark results as a readable text table.
 * ============================================================================
 */

#include "benchmark/BenchmarkRunner.h"

#include <iomanip>
#include <sstream>

namespace geopulse
{
namespace benchmark
{
namespace
{

/** @brief Converts booleans to compact table values. */
std::string yesNo(bool value) { return value ? "yes" : "no"; }

/** @brief Writes one benchmark table row. */
void writeRow(std::ostringstream* output, const AlgorithmBenchmarkResult& row)
{
    *output << std::left << std::setw(14) << row.algorithm << std::right
            << std::fixed << std::setprecision(3) << std::setw(12)
            << row.buildMilliseconds << std::setw(14) << row.nearestMilliseconds
            << std::setw(14) << row.radiusMilliseconds << std::setw(14)
            << row.rangeMilliseconds << std::setw(11)
            << yesNo(row.nearestCorrect) << std::setw(12)
            << yesNo(row.radiusCorrect) << std::setw(11)
            << yesNo(row.rangeCorrect) << '\n';
}

} // namespace

/** Converts the report into deterministic headings with timed numeric rows. */
std::string BenchmarkReport::toText() const
{
    std::ostringstream output;
    output << "GeoPulse benchmark report\n";
    output << "Indexed points: " << pointCount << '\n';
    output << "Query samples: " << queryCount << '\n';
    output << "Radius query miles: " << radiusMiles << '\n';
    output << "Range half-size miles: " << rangeHalfSizeMiles << "\n\n";
    output << std::left << std::setw(14) << "Algorithm" << std::right
           << std::setw(12) << "Build ms" << std::setw(14) << "Nearest ms"
           << std::setw(14) << "Radius ms" << std::setw(14) << "Range ms"
           << std::setw(11) << "NN ok" << std::setw(12) << "Radius ok"
           << std::setw(11) << "Range ok" << '\n';
    for (std::size_t index = 0; index < results.size(); ++index)
    {
        writeRow(&output, results[index]);
    }
    if (!results.empty())
    {
        const AlgorithmBenchmarkResult& finalRow = results.back();
        output << "\nLast sample result counts: radius="
               << finalRow.radiusMatches << ", range=" << finalRow.rangeMatches
               << '\n';
    }
    return output.str();
}

} // namespace benchmark
} // namespace geopulse
