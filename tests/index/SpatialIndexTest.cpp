/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    SpatialIndexTest.cpp
 * Purpose:    Compares KD-tree and Quadtree against the linear scan oracle.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "core/BoundingBox.h"
#include "core/Projection.h"
#include "index/KDTree.h"
#include "index/LinearScanIndex.h"
#include "index/QuadTree.h"
#include "query/ResultComparator.h"

namespace
{

std::vector<geopulse::core::Point> tinyPoints()
{
    std::vector<geopulse::core::Point> points;
    points.push_back(geopulse::core::makePoint(0, 40.7128, -74.0060));
    points.push_back(geopulse::core::makePoint(1, 40.6892, -73.9927));
    points.push_back(geopulse::core::makePoint(2, 40.7500, -73.9970));
    points.push_back(geopulse::core::makePoint(3, 40.8267, -73.9225));
    return points;
}

void buildAll(
    geopulse::index::LinearScanIndex* scan,
    geopulse::index::KDTree* kdTree,
    geopulse::index::QuadTree* quadTree,
    const std::vector<geopulse::core::Point>& points
)
{
    scan->build(points);
    kdTree->build(points);
    quadTree->build(points);
}

} // namespace

TEST_CASE("Trees match linear scan for nearest query", "[index]")
{
    const std::vector<geopulse::core::Point> points = tinyPoints();
    geopulse::index::LinearScanIndex scan;
    geopulse::index::KDTree kdTree;
    geopulse::index::QuadTree quadTree;
    buildAll(&scan, &kdTree, &quadTree, points);
    const geopulse::core::Point query =
        geopulse::core::makePoint(99, 40.7130, -74.0061);
    REQUIRE(
        geopulse::query::sameNearest(scan.nearest(query), kdTree.nearest(query))
    );
    REQUIRE(
        geopulse::query::sameNearest(
            scan.nearest(query), quadTree.nearest(query)
        )
    );
}

TEST_CASE("Trees match linear scan for radius query", "[index]")
{
    const std::vector<geopulse::core::Point> points = tinyPoints();
    geopulse::index::LinearScanIndex scan;
    geopulse::index::KDTree kdTree;
    geopulse::index::QuadTree quadTree(1, 10);
    buildAll(&scan, &kdTree, &quadTree, points);
    const geopulse::core::Point query = points[0];
    REQUIRE(
        geopulse::query::sameRecordSet(
            scan.radiusQuery(query, 5.0), kdTree.radiusQuery(query, 5.0)
        )
    );
    REQUIRE(
        geopulse::query::sameRecordSet(
            scan.radiusQuery(query, 5.0), quadTree.radiusQuery(query, 5.0)
        )
    );
}
