/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    QueryEngineTest.cpp
 * Purpose:    Tests the coordinate-facing query facade.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "core/Projection.h"
#include "index/LinearScanIndex.h"
#include "query/QueryEngine.h"

TEST_CASE("QueryEngine safely handles a missing index", "[query]")
{
    geopulse::query::QueryEngine engine(nullptr);
    REQUIRE_FALSE(engine.nearest(40.0, -73.0).found);
    REQUIRE(engine.radius(40.0, -73.0, 1.0).empty());
    REQUIRE(engine.range(40.0, 41.0, -74.0, -73.0).empty());
}

TEST_CASE("QueryEngine projects coordinates before querying", "[query]")
{
    std::vector<geopulse::core::Point> points;
    points.push_back(geopulse::core::makePoint(0, 40.0, -73.0));
    geopulse::index::LinearScanIndex scan;
    scan.build(points);
    geopulse::query::QueryEngine engine(&scan);
    REQUIRE(engine.nearest(40.0, -73.0).recordIndex == 0);
    REQUIRE(engine.radius(40.0, -73.0, 0.1).size() == 1);
}
