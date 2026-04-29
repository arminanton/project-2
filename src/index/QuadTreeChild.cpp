/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    QuadTreeChild.cpp
 * Purpose:    Computes Quadtree child assignment and child bounds.
 * ============================================================================
 */

#include "index/QuadTree.h"

namespace geopulse
{
namespace index
{

/** @brief Chooses exactly one child using half-open midpoint rules. */
int QuadTree::_childIndexFor(const Node& node, const core::Point& point) const
{
    const double midX = (node.bounds.minX + node.bounds.maxX) / 2.0;
    const double midY = (node.bounds.minY + node.bounds.maxY) / 2.0;
    const bool east = point.xMiles >= midX;
    const bool north = point.yMiles >= midY;
    if (north)
    {
        return east ? kNorthEast : kNorthWest;
    }
    return east ? kSouthEast : kSouthWest;
}

/** @brief Builds the rectangle owned by one child quadrant. */
core::BoundingBox QuadTree::_childBoundsFor(
    const Node& node, int childIndex
) const
{
    const double midX = (node.bounds.minX + node.bounds.maxX) / 2.0;
    const double midY = (node.bounds.minY + node.bounds.maxY) / 2.0;
    if (childIndex == kSouthWest)
    {
        return core::BoundingBox(
            node.bounds.minX, midX, node.bounds.minY, midY
        );
    }
    if (childIndex == kSouthEast)
    {
        return core::BoundingBox(
            midX, node.bounds.maxX, node.bounds.minY, midY
        );
    }
    if (childIndex == kNorthWest)
    {
        return core::BoundingBox(
            node.bounds.minX, midX, midY, node.bounds.maxY
        );
    }
    return core::BoundingBox(midX, node.bounds.maxX, midY, node.bounds.maxY);
}

} // namespace index
} // namespace geopulse
