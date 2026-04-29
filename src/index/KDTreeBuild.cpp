/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    KDTreeBuild.cpp
 * Purpose:    Builds the KD-tree with median partitions.
 * ============================================================================
 */

#include "index/KDTree.h"

#include <algorithm>

#include "core/Constants.h"
#include "index/IndexUtils.h"

namespace geopulse
{
namespace index
{

/** @brief Creates an empty KD-tree. */
KDTree::KDTree() = default;

std::string KDTree::name() const { return "KD-tree"; }

/** @brief Copies points once, then rearranges them into a balanced tree. */
void KDTree::build(const std::vector<core::Point>& points)
{
    std::vector<core::Point> working = points;
    _size = working.size();
    _root = _build(&working, 0, working.size(), 0);
}

/** @brief Recursively chooses the median point along alternating axes. */
std::unique_ptr<KDTree::Node> KDTree::_build(
    std::vector<core::Point>* points,
    std::size_t begin,
    std::size_t end,
    int depth
)
{
    if (points == nullptr || begin >= end)
    {
        return std::unique_ptr<Node>();
    }
    const int axis = depth % core::constants::kAxisCount;
    const std::size_t median = begin + (end - begin) / 2;
    std::nth_element(
        points->begin() + static_cast<std::ptrdiff_t>(begin),
        points->begin() + static_cast<std::ptrdiff_t>(median),
        points->begin() + static_cast<std::ptrdiff_t>(end),
        [axis](const core::Point& left, const core::Point& right)
        { return axisLess(left, right, axis); }
    );
    std::unique_ptr<Node> node = std::make_unique<Node>();
    node->point = (*points)[median];
    node->axis = axis;
    node->left = _build(points, begin, median, depth + 1);
    node->right = _build(points, median + 1, end, depth + 1);
    return node;
}

std::size_t KDTree::size() const { return _size; }

} // namespace index
} // namespace geopulse
