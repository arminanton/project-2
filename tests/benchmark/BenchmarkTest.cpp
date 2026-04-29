/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    BenchmarkTest.cpp
 * Purpose:    Tests benchmark correctness reporting without asserting timings.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "benchmark/BenchmarkRunner.h"
#include "data/DataLoader.h"
#include "helpers/TestHelpers.h"

TEST_CASE("Benchmark reports all three algorithms as correct", "[benchmark]")
{
    geopulse::data::DataLoader loader;
    geopulse::data::DataLoaderOptions loadOptions;
    const geopulse::data::DataSet dataSet = loader.load(
        geopulse::tests::sourcePath("data/samples/mixed_collisions_small.csv"),
        loadOptions
    );
    geopulse::benchmark::BenchmarkRunner runner;
    geopulse::benchmark::BenchmarkOptions options;
    const geopulse::benchmark::BenchmarkReport report =
        runner.run(dataSet, options);
    REQUIRE(report.results.size() == 3);
    for (std::size_t index = 0; index < report.results.size(); ++index)
    {
        REQUIRE(report.results[index].nearestCorrect);
        REQUIRE(report.results[index].radiusCorrect);
        REQUIRE(report.results[index].rangeCorrect);
    }
    REQUIRE(report.toText().find("KD-tree") != std::string::npos);
    REQUIRE(report.toText().find("Quadtree") != std::string::npos);
}
