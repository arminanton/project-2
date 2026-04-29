/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    KDTree.h
 * Purpose:    Declares a from-scratch two-dimensional KD-tree.
 * ============================================================================
 */

#ifndef GEOPULSE_INDEX_KD_TREE_H
#define GEOPULSE_INDEX_KD_TREE_H

#include <memory>

#include "index/SpatialIndex.h"

namespace geopulse
{
namespace index
{

/** @brief KD-tree splits points by alternating x and y median partitions. */
class KDTree : public SpatialIndex
{
public:
    /** @brief Builds an empty tree that can be reused with build(). */
    KDTree();

    /** @brief Human-readable algorithm name for reports. */
    std::string name() const override;

    /** @brief Copies points once, then organizes them into median nodes. */
    void build(const std::vector<core::Point>& points) override;

    /** @brief Finds the closest indexed point to the query point. */
    core::NearestResult nearest(const core::Point& query) const override;

    /** @brief Returns all points within radiusMiles of center. */
    core::RecordIdList radiusQuery(
        const core::Point& center, double radiusMiles
    ) const override;

    /** @brief Returns all points inside a projected bounding box. */
    core::RecordIdList rangeQuery(const core::BoundingBox& box) const override;

    /** @brief Returns the number of points stored in the tree. */
    std::size_t size() const override;

private:
    /** @brief One recursive split node in the KD-tree. */
    struct Node
    {
        core::Point point; // Median point stored at this node.
        int axis = 0; // Split axis: x first, then y, repeated.
        std::unique_ptr<Node> left; // Smaller split side.
        std::unique_ptr<Node> right; // Larger split side.
    };

    std::unique_ptr<Node> _build(
        std::vector<core::Point>* points,
        std::size_t begin,
        std::size_t end,
        int depth
    );
    void _nearest(
        const Node* node, const core::Point& query, core::NearestResult* best
    ) const;
    void _radius(
        const Node* node,
        const core::Point& center,
        double radiusSquared,
        core::RecordIdList* results
    ) const;
    void _range(
        const Node* node,
        const core::BoundingBox& box,
        core::RecordIdList* results
    ) const;

    std::unique_ptr<Node> _root; // Owns the full recursive tree.
    std::size_t _size = 0; // Cached size for O(1) reporting.
};

} // namespace index
} // namespace geopulse

#endif
