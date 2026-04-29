/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BoundingBoxQueries.cpp
 * Purpose: Implements geometric predicates and measurements for bounding boxes.
 * ============================================================================
 */

#include "core/BoundingBoxQueries.h"

#include <algorithm>

#include "core/Distance.h"

namespace geopulse
{
namespace core
{

bool contains(const BoundingBox& box, const Point& point)
{
    // A point is inside the box if it sits within both horizontal
    // and vertical boundaries.
    return point.xMiles >= box.minX && point.xMiles <= box.maxX &&
           point.yMiles >= box.minY && point.yMiles <= box.maxY;
}

bool intersects(const BoundingBox& a, const BoundingBox& b)
{
    // Rectangles overlap iff their X and Y projections overlap.
    // Equivalently: neither box is entirely left/right or above/below
    // the other.
    return a.maxX >= b.minX && a.minX <= b.maxX && a.maxY >= b.minY &&
           a.minY <= b.maxY;
}

double minDistanceSquaredTo(
    const BoundingBox& box, double xMiles, double yMiles
)
{
    // The closest point on the box to an arbitrary query coordinate
    // is found by clamping the query's X and Y independently into
    // [minX, maxX] and [minY, maxY]. If inside, both clamps are
    // no-ops and the result is the query itself, giving distance zero.
    const double closestX = std::max(box.minX, std::min(xMiles, box.maxX));
    const double closestY = std::max(box.minY, std::min(yMiles, box.maxY));

    return distanceSquared(xMiles, yMiles, closestX, closestY);
}

} // namespace core
} // namespace geopulse
