/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    GeoPulseFacade.cpp
 * Purpose:    Implements testable GeoPulse application behavior.
 * ============================================================================
 */

#include "app/GeoPulseFacade.h"

#include <sstream>

#include "core/Version.h"

namespace geopulse
{
namespace app
{

/** @brief Returns the exact version line printed by the command line. */
std::string GeoPulseFacade::versionText() const
{
    return std::string("GeoPulse v") + core::getVersion() + "\n";
}

/** @brief Formats deterministic dataset counts for public sample tests. */
std::string GeoPulseFacade::summaryText(const data::DataSet& dataSet) const
{
    std::ostringstream output;
    output << "Dataset summary\n";
    output << "total rows: " << dataSet.statistics.totalRows << '\n';
    output << "accepted coordinate rows: " << dataSet.statistics.acceptedRows
           << '\n';
    output << "excluded rows: " << dataSet.statistics.excludedRows << '\n';
    output << "missing-coordinate rows: "
           << dataSet.statistics.missingCoordinateRows << '\n';
    output << "invalid-coordinate rows: "
           << dataSet.statistics.invalidCoordinateRows << '\n';
    return output.str();
}

/** @brief Loads a CSV and returns a deterministic summary. */
std::string GeoPulseFacade::loadSummary(
    const std::string& sourcePath, const data::DataLoaderOptions& options
) const
{
    data::DataLoader loader;
    return summaryText(loader.load(sourcePath, options));
}

/** @brief Runs and formats a full benchmark report. */
std::string GeoPulseFacade::benchmarkText(
    const data::DataSet& dataSet, const benchmark::BenchmarkOptions& options
) const
{
    benchmark::BenchmarkRunner runner;
    return runner.run(dataSet, options).toText();
}

} // namespace app
} // namespace geopulse
