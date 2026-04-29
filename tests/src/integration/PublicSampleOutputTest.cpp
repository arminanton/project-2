/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    PublicSampleOutputTest.cpp
 * Purpose:    Verifies the public sample dataset has exact expected output.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "app/GeoPulseFacade.h"
#include "helpers/TestHelpers.h"

TEST_CASE("Public sample summary output is exact", "[integration]")
{
    geopulse::app::GeoPulseFacade facade;
    geopulse::data::DataLoaderOptions options;
    const std::string actual = facade.loadSummary(
        geopulse::tests::sourcePath("data/samples/mixed_collisions_small.csv"),
        options
    );
    const std::string expected = "Dataset summary\n"
                                 "total rows: 8\n"
                                 "accepted coordinate rows: 6\n"
                                 "excluded rows: 2\n"
                                 "missing-coordinate rows: 1\n"
                                 "invalid-coordinate rows: 1\n";
    geopulse::tests::requireOutput(actual, expected);
}
