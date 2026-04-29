/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    KDTreeNearest.cpp
 * Purpose:    Implements nearest-neighbor search for the KD-tree.
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

/** @brief Starts a branch-and-bound nearest-neighbor search. */
core::NearestResult KDTree::nearest(const core::Point& query) const
{
    core::NearestResult best;
    _nearest(_root.get(), query, &best);
    return best;
}

/** Searches the likely side first, then prunes the far side when safe. */
void KDTree::_nearest(
    const Node* node, const core::Point& query, core::NearestResult* best
) const
{
    if (node == nullptr || best == nullptr)
    {
        return;
    }
    const double distance = core::distanceSquared(node->point, query);
    if (isBetterCandidate(node->point, distance, *best))
    {
        best->found = true;
        best->recordIndex = node->point.recordIndex;
        best->distanceSquared = distance;
    }
    const double delta =
        axisValue(query, node->axis) - axisValue(node->point, node->axis);
    const Node* nearNode = delta < 0.0 ? node->left.get() : node->right.get();
    const Node* farNode = delta < 0.0 ? node->right.get() : node->left.get();
    _nearest(nearNode, query, best);
    if (!best->found ||
        delta * delta <=
            best->distanceSquared + core::constants::kDistanceTolerance)
    {
        _nearest(farNode, query, best);
    }
}

} // namespace index
} // namespace geopulse
