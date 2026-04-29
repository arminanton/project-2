/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    ArgumentParserTest.cpp
 * Purpose:    Tests valid and invalid command-line parsing scenarios.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "helpers/TestHelpers.h"

using geopulse::tests::parseCommand;
using geopulse::tests::requireCondition;
using geopulse::tests::requireUnsuccessful;

TEST_CASE("Parser accepts help command", "[cli]")
{
    const geopulse::ui::CliOptions options =
        parseCommand({"geopulse", "--help"});
    requireCondition(options.valid && options.showHelp);
}

TEST_CASE("Parser accepts benchmark data command", "[cli]")
{
    const geopulse::ui::CliOptions options =
        parseCommand({"geopulse", "--data", "sample.csv", "--benchmark"});
    requireCondition(options.valid && options.benchmark);
    REQUIRE(options.dataPath == "sample.csv");
}

TEST_CASE("Parser rejects at least five incorrect commands", "[cli]")
{
    requireUnsuccessful(parseCommand({"geopulse", "--unknown"}));
    requireUnsuccessful(parseCommand({"geopulse", "--data"}));
    requireUnsuccessful(parseCommand({"geopulse", "--radius"}));
    requireUnsuccessful(parseCommand({"geopulse", "--data", "x", "--bad"}));
    requireUnsuccessful(parseCommand({"geopulse", "--nearest", "40"}));
}
