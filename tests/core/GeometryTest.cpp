/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    GeometryTest.cpp
 * Purpose:    Tests coordinate validation, projection, distance, and boxes.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "core/BoundingBox.h"
#include "core/BoundingBoxQueries.h"
#include "core/Distance.h"
#include "core/Projection.h"

TEST_CASE("Coordinate validator rejects impossible values", "[core]")
{
    REQUIRE(geopulse::core::isValidLatitudeLongitude(40.0, -73.0));
    REQUIRE_FALSE(geopulse::core::isValidLatitudeLongitude(91.0, -73.0));
    REQUIRE_FALSE(geopulse::core::isValidLatitudeLongitude(40.0, -181.0));
}

TEST_CASE("Projected points keep original coordinates", "[core]")
{
    const geopulse::core::Point point =
        geopulse::core::makePoint(7, 40.7128, -74.0060);
    REQUIRE(point.recordIndex == 7);
    REQUIRE(point.latitude == Catch::Approx(40.7128));
    REQUIRE(point.longitude == Catch::Approx(-74.0060));
}

TEST_CASE("Distance is zero for the same point", "[core]")
{
    const geopulse::core::Point point =
        geopulse::core::makePoint(0, 40.0, -73.0);
    REQUIRE(
        geopulse::core::distanceSquared(point, point) == Catch::Approx(0.0)
    );
}

TEST_CASE("Bounding boxes contain, intersect, and measure distance", "[core]")
{
    const geopulse::core::Point point =
        geopulse::core::makePoint(0, 40.0, -73.0);
    const geopulse::core::BoundingBox box(
        point.xMiles - 1.0,
        point.xMiles + 1.0,
        point.yMiles - 1.0,
        point.yMiles + 1.0
    );
    REQUIRE(geopulse::core::contains(box, point));
    REQUIRE(geopulse::core::intersects(box, box));
    REQUIRE(
        geopulse::core::minDistanceSquaredTo(box, point.xMiles, point.yMiles) ==
        Catch::Approx(0.0)
    );
}
