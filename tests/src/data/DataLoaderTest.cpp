/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    DataLoaderTest.cpp
 * Purpose:    Tests dataset loading, parser validation, and recovery files.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "data/DataLoader.h"
#include "helpers/TestHelpers.h"

TEST_CASE("DataLoader counts accepted and rejected sample rows", "[data]")
{
    geopulse::data::DataLoader loader;
    geopulse::data::DataLoaderOptions options;
    const geopulse::data::DataSet dataSet = loader.load(
        geopulse::tests::sourcePath("data/samples/mixed_collisions_small.csv"),
        options
    );
    REQUIRE(dataSet.statistics.totalRows == 8);
    REQUIRE(dataSet.statistics.acceptedRows == 6);
    REQUIRE(dataSet.statistics.excludedRows == 2);
    REQUIRE(dataSet.statistics.missingCoordinateRows == 1);
    REQUIRE(dataSet.statistics.invalidCoordinateRows == 1);
}

TEST_CASE("DataLoader can write and reuse completed recovery cache", "[data]")
{
    geopulse::data::DataLoader loader;
    geopulse::data::DataLoaderOptions options;
    options.enableRecovery = true;
    options.reuseCompletedCache = true;
    options.checkpointPath = "sample_checkpoint.json";
    options.cachePath = "sample_cache.tsv";
    const std::string sample =
        geopulse::tests::sourcePath("data/samples/mixed_collisions_small.csv");
    const geopulse::data::DataSet first = loader.load(sample, options);
    const geopulse::data::DataSet second = loader.load(sample, options);
    REQUIRE(first.records.size() == second.records.size());
    REQUIRE(second.statistics.acceptedRows == 6);
}
