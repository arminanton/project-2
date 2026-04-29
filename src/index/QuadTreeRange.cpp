/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    QuadTreeRange.cpp
 * Purpose:    Implements rectangular range queries for the Quadtree.
 * ============================================================================
 */

#include "index/QuadTree.h"

#include "core/BoundingBoxQueries.h"

namespace geopulse
{
namespace index
{

/** @brief Returns all records in the query rectangle. */
core::RecordIdList QuadTree::rangeQuery(const core::BoundingBox& box) const
{
    core::RecordIdList results;
    if (!box.isValid())
    {
        return results;
    }
    _range(_root.get(), box, &results);
    return results;
}

/** @brief Skips entire quadrants whose boxes do not intersect the query box. */
void QuadTree::_range(
    const Node* node, const core::BoundingBox& box, core::RecordIdList* results
) const
{
    if (node == nullptr || results == nullptr ||
        !core::intersects(node->bounds, box))
    {
        return;
    }
    for (std::size_t index = 0; index < node->points.size(); ++index)
    {
        if (core::contains(box, node->points[index]))
        {
            results->push_back(node->points[index].recordIndex);
        }
    }
    for (std::size_t index = 0; index < node->children.size(); ++index)
    {
        _range(node->children[index].get(), box, results);
    }
}

} // namespace index
} // namespace geopulse
