/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    QuadTree.h
 * Purpose:    Declares a from-scratch point-region Quadtree.
 * ============================================================================
 */

#ifndef GEOPULSE_INDEX_QUAD_TREE_H
#define GEOPULSE_INDEX_QUAD_TREE_H

#include <array>
#include <memory>

#include "core/Constants.h"
#include "index/SpatialIndex.h"

namespace geopulse
{
namespace index
{

/** @brief Quadtree recursively divides the map into four rectangles. */
class QuadTree : public SpatialIndex
{
public:
    /** @brief Builds a tree using the shared project tuning constants. */
    QuadTree();

    /** @brief Lets tests force small leaves and shallow depth limits. */
    QuadTree(std::size_t capacity, int maxDepth);

    std::string name() const override;
    void build(const std::vector<core::Point>& points) override;
    core::NearestResult nearest(const core::Point& query) const override;
    core::RecordIdList radiusQuery(
        const core::Point& center, double radiusMiles
    ) const override;
    core::RecordIdList rangeQuery(const core::BoundingBox& box) const override;
    std::size_t size() const override;

private:
    /** @brief One quadrant node; leaves keep points until capacity is hit. */
    struct Node
    {
        explicit Node(const core::BoundingBox& nodeBounds, int nodeDepth);
        bool isLeaf() const;

        core::BoundingBox bounds;        // Rectangle owned by this node.
        std::vector<core::Point> points; // Leaf points.
        std::array<std::unique_ptr<Node>, 4> children; // Kids.
        int depth = 0; // Guard against duplicate-point splits.
    };

    enum ChildIndex
    {
        kSouthWest = 0,
        kSouthEast = 1,
        kNorthWest = 2,
        kNorthEast = 3
    };

    void _insert(Node* node, const core::Point& point);
    void _subdivide(Node* node);
    int _childIndexFor(const Node& node, const core::Point& point) const;
    core::BoundingBox _childBoundsFor(const Node& node, int childIndex) const;
    void _range(
        const Node* node,
        const core::BoundingBox& box,
        core::RecordIdList* results
    ) const;
    void _radius(
        const Node* node,
        const core::Point& center,
        double radiusSquared,
        core::RecordIdList* results
    ) const;
    void _nearest(
        const Node* node, const core::Point& query, core::NearestResult* best
    ) const;

    std::unique_ptr<Node> _root; // Owns the recursive tree.
    std::size_t _capacity = core::constants::kQuadNodeCapacity;
    int _maxDepth = core::constants::kQuadMaxDepth;
    std::size_t _size = 0; // Cached point count.
};

} // namespace index
} // namespace geopulse

#endif
