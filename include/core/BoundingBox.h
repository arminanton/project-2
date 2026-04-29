/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BoundingBox.h
 * Purpose: Defines rectangles used by range queries and tree pruning.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_BOUNDING_BOX_H
#define GEOPULSE_CORE_BOUNDING_BOX_H

namespace geopulse
{
namespace core
{

/**
         * @brief Axis-aligned rectangle in projected mile coordinates.
         *
         * Used to define search boundaries for range queries and to compute
         * minimum distances during tree traversal. This allows search
         * algorithms to aggressively prune branches that cannot contain
         * a closer point.
         */
struct BoundingBox
{
    /** @brief Left edge in projected miles. */
    double minX = 0.0;

    /** @brief Right edge in projected miles. */
    double maxX = 0.0;

    /** @brief Bottom edge in projected miles. */
    double minY = 0.0;

    /** @brief Top edge in projected miles. */
    double maxY = 0.0;

    /** @brief Builds a zero-sized box at the origin. */
    BoundingBox();

    /**
             * @brief Builds a box from explicit projected-mile edges.
             *
             * @param minXValue The leftmost boundary.
             * @param maxXValue The rightmost boundary.
             * @param minYValue The bottom boundary.
             * @param maxYValue The top boundary.
             */
    BoundingBox(
        double minXValue, double maxXValue, double minYValue, double maxYValue
    );

    /** @brief Width in projected miles. */
    double width() const;

    /** @brief Height in projected miles. */
    double height() const;

    /**
             * @brief A valid box has ordered min/max values.
             *
             * The box is flipped or collapsed if minimums exceed maximums.
             * All pruning and intersection algorithms depend on this invariant 
             * to function correctly.
             */
    bool isValid() const;
};

} // namespace core
} // namespace geopulse

#endif
