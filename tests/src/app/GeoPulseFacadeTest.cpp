/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    GeoPulseFacadeTest.cpp
 * Purpose:    Tests facade output without capturing stdout.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "app/GeoPulseFacade.h"
#include "core/Version.h"

TEST_CASE("Facade prints the current version line", "[app]")
{
    geopulse::app::GeoPulseFacade facade;
    const std::string expected =
        std::string("GeoPulse v") + geopulse::core::getVersion() + "\n";
    REQUIRE(facade.versionText() == expected);
}

TEST_CASE("Facade formats an empty dataset summary", "[app]")
{
    geopulse::app::GeoPulseFacade facade;
    geopulse::data::DataSet dataSet;
    const std::string text = facade.summaryText(dataSet);
    REQUIRE(text.find("Dataset summary") != std::string::npos);
    REQUIRE(text.find("accepted coordinate rows: 0") != std::string::npos);
}
