/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    QuadTreeRadius.cpp
 * Purpose:    Implements circular radius queries for the Quadtree.
 * ============================================================================
 */

#include "index/QuadTree.h"

#include "core/BoundingBoxQueries.h"
#include "core/Constants.h"
#include "core/Distance.h"

namespace geopulse
{
namespace index
{

/** @brief Returns every record within the requested radius. */
core::RecordIdList QuadTree::radiusQuery(
    const core::Point& center, double radiusMiles
) const
{
    core::RecordIdList results;
    if (radiusMiles < 0.0)
    {
        return results;
    }
    _radius(_root.get(), center, radiusMiles * radiusMiles, &results);
    return results;
}

/** @brief Prunes quadrants whose bounding boxes are farther than the radius. */
void QuadTree::_radius(
    const Node* node,
    const core::Point& center,
    double radiusSquared,
    core::RecordIdList* results
) const
{
    if (node == nullptr || results == nullptr)
    {
        return;
    }
    if (core::minDistanceSquaredTo(node->bounds, center.xMiles, center.yMiles) >
        radiusSquared + core::constants::kDistanceTolerance)
    {
        return;
    }
    for (std::size_t index = 0; index < node->points.size(); ++index)
    {
        if (core::distanceSquared(node->points[index], center) <=
            radiusSquared + core::constants::kDistanceTolerance)
        {
            results->push_back(node->points[index].recordIndex);
        }
    }
    for (std::size_t index = 0; index < node->children.size(); ++index)
    {
        _radius(node->children[index].get(), center, radiusSquared, results);
    }
}

} // namespace index
} // namespace geopulse
