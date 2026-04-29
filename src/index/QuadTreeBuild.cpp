/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    QuadTreeBuild.cpp
 * Purpose:    Builds the Quadtree by inserting points into quadrants.
 * ============================================================================
 */

#include "index/QuadTree.h"

#include "index/IndexUtils.h"

namespace geopulse
{
namespace index
{

/** @brief Builds a tree rooted at a bounding box containing every point. */
void QuadTree::build(const std::vector<core::Point>& points)
{
    _root.reset();
    _size = points.size();
    if (points.empty())
    {
        return;
    }
    _root = std::make_unique<Node>(boundsForPoints(points), 0);
    for (std::size_t index = 0; index < points.size(); ++index)
    {
        _insert(_root.get(), points[index]);
    }
}

/** @brief Inserts a point, splitting a full leaf when more depth is allowed. */
void QuadTree::_insert(Node* node, const core::Point& point)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->isLeaf())
    {
        if (node->points.size() < _capacity || node->depth >= _maxDepth)
        {
            node->points.push_back(point);
            return;
        }
        _subdivide(node);
    }
    const int childIndex = _childIndexFor(*node, point);
    _insert(node->children[childIndex].get(), point);
}

/** @brief Creates four child boxes and redistributes old leaf points. */
void QuadTree::_subdivide(Node* node)
{
    if (node == nullptr || !node->isLeaf())
    {
        return;
    }
    for (int index = 0; index < 4; ++index)
    {
        node->children[index] = std::make_unique<Node>(
            _childBoundsFor(*node, index), node->depth + 1
        );
    }
    std::vector<core::Point> oldPoints = node->points;
    node->points.clear();
    for (std::size_t index = 0; index < oldPoints.size(); ++index)
    {
        _insert(node, oldPoints[index]);
    }
}

} // namespace index
} // namespace geopulse
