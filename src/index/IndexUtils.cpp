/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    IndexUtils.cpp
 * Purpose:    Implements helper functions shared by index algorithms.
 * ============================================================================
 */

#include "index/IndexUtils.h"

#include <algorithm>
#include <cmath>

#include "core/Constants.h"

namespace geopulse
{
namespace index
{

/** Orders points by one axis and then record id for deterministic trees. */
bool axisLess(const core::Point& left, const core::Point& right, int axis)
{
    const double leftValue = axisValue(left, axis);
    const double rightValue = axisValue(right, axis);
    if (leftValue == rightValue)
    {
        return left.recordIndex < right.recordIndex;
    }
    return leftValue < rightValue;
}

/** @brief Returns either x or y based on the split axis. */
double axisValue(const core::Point& point, int axis)
{
    return axis == core::constants::kXAxis ? point.xMiles : point.yMiles;
}

/** @brief Applies deterministic nearest-neighbor tie-breaking. */
bool isBetterCandidate(
    const core::Point& candidate,
    double distanceSquared,
    const core::NearestResult& best
)
{
    if (!best.found)
    {
        return true;
    }
    if (distanceSquared + core::constants::kDistanceTolerance <
        best.distanceSquared)
    {
        return true;
    }
    return std::fabs(distanceSquared - best.distanceSquared) <=
               core::constants::kDistanceTolerance &&
           candidate.recordIndex < best.recordIndex;
}

/** @brief Computes a padded root box that safely contains every point. */
core::BoundingBox boundsForPoints(const std::vector<core::Point>& points)
{
    core::BoundingBox bounds(
        points[0].xMiles, points[0].xMiles, points[0].yMiles, points[0].yMiles
    );
    for (std::size_t index = 1; index < points.size(); ++index)
    {
        bounds.minX = std::min(bounds.minX, points[index].xMiles);
        bounds.maxX = std::max(bounds.maxX, points[index].xMiles);
        bounds.minY = std::min(bounds.minY, points[index].yMiles);
        bounds.maxY = std::max(bounds.maxY, points[index].yMiles);
    }
    bounds.minX -= core::constants::kRootPaddingMiles;
    bounds.maxX += core::constants::kRootPaddingMiles;
    bounds.minY -= core::constants::kRootPaddingMiles;
    bounds.maxY += core::constants::kRootPaddingMiles;
    return bounds;
}

} // namespace index
} // namespace geopulse
