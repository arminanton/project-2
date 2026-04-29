/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    IndexEdgeTest.cpp
 * Purpose:    Tests spatial-index edge cases separate from invalid commands.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "core/Projection.h"
#include "index/KDTree.h"
#include "index/LinearScanIndex.h"
#include "index/QuadTree.h"

TEST_CASE("Empty indexes return no nearest result", "[edge]")
{
    std::vector<geopulse::core::Point> points;
    geopulse::index::KDTree kdTree;
    kdTree.build(points);
    const geopulse::core::Point query =
        geopulse::core::makePoint(0, 40.0, -73.0);
    REQUIRE_FALSE(kdTree.nearest(query).found);
}

TEST_CASE("Negative radius returns an empty result", "[edge]")
{
    const geopulse::core::Point point =
        geopulse::core::makePoint(0, 40.0, -73.0);
    std::vector<geopulse::core::Point> points;
    points.push_back(point);
    geopulse::index::LinearScanIndex scan;
    scan.build(points);
    REQUIRE(scan.radiusQuery(point, -1.0).empty());
}

TEST_CASE("Nearest tie chooses smaller record index", "[edge]")
{
    std::vector<geopulse::core::Point> points;
    points.push_back(geopulse::core::makePoint(1, 40.0, -73.0));
    points.push_back(geopulse::core::makePoint(0, 40.0, -73.0));
    geopulse::index::LinearScanIndex scan;
    scan.build(points);
    REQUIRE(scan.nearest(points[0]).recordIndex == 0);
}
