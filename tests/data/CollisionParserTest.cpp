/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CollisionParserTest.cpp
 * Purpose:    Tests row validation before the loader stores accepted records.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "data/CollisionParser.h"

namespace
{

/** @brief Builds the minimum header mapping used by parser unit tests. */
geopulse::data::CollisionColumns columns()
{
    geopulse::data::CollisionColumns value;
    value.crashDate = 0;
    value.crashTime = 1;
    value.borough = 2;
    value.latitude = 3;
    value.longitude = 4;
    value.personsInjured = 5;
    value.personsKilled = 6;
    value.collisionId = 7;
    value.valid = true;
    return value;
}

} // namespace

TEST_CASE("CollisionParser accepts numeric coordinates", "[data]")
{
    const geopulse::data::CsvRow row = {
        "01/01/2024", "12:00", "BROOKLYN", "40.7", "-73.9", "2", "0", "99"
    };
    const geopulse::data::CollisionParseResult result =
        geopulse::data::parseCollisionRow(row, columns(), 4, 0);
    REQUIRE(result.accepted);
    REQUIRE(result.record.collisionId == "99");
    REQUIRE(result.record.personsInjured == 2);
}

TEST_CASE("CollisionParser rejects missing coordinates", "[data]")
{
    const geopulse::data::CsvRow row = {
        "01/01/2024", "12:00", "", "", "-73.9", "", "", "7"
    };
    const geopulse::data::CollisionParseResult result =
        geopulse::data::parseCollisionRow(row, columns(), 4, 0);
    REQUIRE_FALSE(result.accepted);
    REQUIRE(result.missingCoordinate);
}

TEST_CASE("CollisionParser rejects non-finite coordinates", "[data]")
{
    const geopulse::data::CsvRow row = {
        "01/01/2024", "12:00", "", "nan", "-73.9", "", "", "7"
    };
    const geopulse::data::CollisionParseResult result =
        geopulse::data::parseCollisionRow(row, columns(), 4, 0);
    REQUIRE_FALSE(result.accepted);
    REQUIRE(result.invalidCoordinate);
}
