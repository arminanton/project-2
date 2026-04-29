/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    GeoPulseFacade.h
 * Purpose:    Exposes testable application behavior without stdout capture.
 * ============================================================================
 */

#ifndef GEOPULSE_APP_GEOPULSE_FACADE_H
#define GEOPULSE_APP_GEOPULSE_FACADE_H

#include <string>

#include "benchmark/BenchmarkRunner.h"
#include "data/DataLoader.h"

namespace geopulse
{
namespace app
{

/**
 * @brief Public application service used by CLI and integration tests.
 *
 * The facade returns strings instead of printing directly. That makes command
 * behavior easy to test with exact expected output.
 */
class GeoPulseFacade
{
public:
    /** @brief Returns the version line printed by --version. */
    std::string versionText() const;

    /** @brief Formats already-loaded dataset statistics. */
    std::string summaryText(const data::DataSet& dataSet) const;

    /** @brief Loads a CSV file and returns its formatted summary. */
    std::string loadSummary(
        const std::string& sourcePath, const data::DataLoaderOptions& options
    ) const;

    /** @brief Runs a benchmark and returns the printable report text. */
    std::string benchmarkText(
        const data::DataSet& dataSet, const benchmark::BenchmarkOptions& options
    ) const;
};

} // namespace app
} // namespace geopulse

#endif
