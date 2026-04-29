/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    QuadTreeNearest.cpp
 * Purpose:    Implements nearest-neighbor search for the Quadtree.
 * ============================================================================
 */

#include "index/QuadTree.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "core/BoundingBoxQueries.h"
#include "core/Constants.h"
#include "core/Distance.h"
#include "index/IndexUtils.h"

namespace geopulse
{
namespace index
{

/** @brief Starts a branch-and-bound nearest-neighbor search. */
core::NearestResult QuadTree::nearest(const core::Point& query) const
{
    core::NearestResult best;
    _nearest(_root.get(), query, &best);
    return best;
}

/** @brief Searches child boxes from closest to farthest for better pruning. */
void QuadTree::_nearest(
    const Node* node, const core::Point& query, core::NearestResult* best
) const
{
    if (node == nullptr || best == nullptr)
    {
        return;
    }
    const double boxDistance =
        core::minDistanceSquaredTo(node->bounds, query.xMiles, query.yMiles);
    if (best->found && boxDistance > best->distanceSquared +
                                         core::constants::kDistanceTolerance)
    {
        return;
    }
    for (std::size_t index = 0; index < node->points.size(); ++index)
    {
        const double distance =
            core::distanceSquared(node->points[index], query);
        if (isBetterCandidate(node->points[index], distance, *best))
        {
            best->found = true;
            best->recordIndex = node->points[index].recordIndex;
            best->distanceSquared = distance;
        }
    }
    std::vector<std::pair<double, const Node*>> ordered;
    for (std::size_t index = 0; index < node->children.size(); ++index)
    {
        const Node* child = node->children[index].get();
        if (child != nullptr)
        {
            ordered.push_back(
                std::make_pair(
                    core::minDistanceSquaredTo(
                        child->bounds, query.xMiles, query.yMiles
                    ),
                    child
                )
            );
        }
    }
    std::sort(ordered.begin(), ordered.end());
    for (std::size_t index = 0; index < ordered.size(); ++index)
    {
        _nearest(ordered[index].second, query, best);
    }
}

} // namespace index
} // namespace geopulse
