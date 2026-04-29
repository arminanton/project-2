/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    KDTreeRange.cpp
 * Purpose:    Implements rectangular range queries for the KD-tree.
 * ============================================================================
 */

#include "core/Constants.h"
#include "core/BoundingBoxQueries.h"
#include "index/KDTree.h"

namespace geopulse
{
namespace index
{

/** @brief Returns all records whose projected point lies in the rectangle. */
core::RecordIdList KDTree::rangeQuery(const core::BoundingBox& box) const
{
    core::RecordIdList results;
    if (!box.isValid())
    {
        return results;
    }
    _range(_root.get(), box, &results);
    return results;
}

/** Uses the split axis to avoid branches that cannot cross the query box. */
void KDTree::_range(
    const Node* node, const core::BoundingBox& box, core::RecordIdList* results
) const
{
    if (node == nullptr || results == nullptr)
    {
        return;
    }
    if (core::contains(box, node->point))
    {
        results->push_back(node->point.recordIndex);
    }
    if (node->axis == core::constants::kXAxis)
    {
        if (box.minX <= node->point.xMiles)
        {
            _range(node->left.get(), box, results);
        }
        if (box.maxX >= node->point.xMiles)
        {
            _range(node->right.get(), box, results);
        }
        return;
    }
    if (box.minY <= node->point.yMiles)
    {
        _range(node->left.get(), box, results);
    }
    if (box.maxY >= node->point.yMiles)
    {
        _range(node->right.get(), box, results);
    }
}

} // namespace index
} // namespace geopulse
