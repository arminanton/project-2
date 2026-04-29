/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    QuadTreeNode.cpp
 * Purpose:    Implements small Quadtree node helpers.
 * ============================================================================
 */

#include "index/QuadTree.h"

namespace geopulse
{
namespace index
{

/** @brief Creates a node with fixed rectangular bounds and a depth value. */
QuadTree::Node::Node(const core::BoundingBox& nodeBounds, int nodeDepth) :
    bounds(nodeBounds),
    depth(nodeDepth)
{
}

/** @brief Leaf nodes have no child quadrants. */
bool QuadTree::Node::isLeaf() const { return children[0].get() == nullptr; }

/** @brief Creates a Quadtree with assignment-friendly default tuning. */
QuadTree::QuadTree() = default;

/** @brief Allows tests to use tiny capacities and shallow depths. */
QuadTree::QuadTree(std::size_t capacity, int maxDepth) :
    _capacity(capacity),
    _maxDepth(maxDepth)
{
}

std::string QuadTree::name() const { return "Quadtree"; }

std::size_t QuadTree::size() const { return _size; }

} // namespace index
} // namespace geopulse
