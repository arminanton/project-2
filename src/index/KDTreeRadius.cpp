/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    KDTreeRadius.cpp
 * Purpose:    Implements radius queries for the KD-tree.
 * ============================================================================
 */

#include "index/KDTree.h"

#include "core/Constants.h"
#include "core/Distance.h"
#include "index/IndexUtils.h"

namespace geopulse
{
namespace index
{

/** @brief Returns all records within the requested mile radius. */
core::RecordIdList KDTree::radiusQuery(
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

/** @brief Searches only subtrees whose split plane can intersect the circle. */
void KDTree::_radius(
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
    if (core::distanceSquared(node->point, center) <=
        radiusSquared + core::constants::kDistanceTolerance)
    {
        results->push_back(node->point.recordIndex);
    }
    const double delta =
        axisValue(center, node->axis) - axisValue(node->point, node->axis);
    const Node* nearNode = delta < 0.0 ? node->left.get() : node->right.get();
    const Node* farNode = delta < 0.0 ? node->right.get() : node->left.get();
    _radius(nearNode, center, radiusSquared, results);
    if (delta * delta <= radiusSquared + core::constants::kDistanceTolerance)
    {
        _radius(farNode, center, radiusSquared, results);
    }
}

} // namespace index
} // namespace geopulse
