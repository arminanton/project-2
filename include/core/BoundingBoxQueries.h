/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BoundingBoxQueries.h
 * Purpose: Defines geometric predicates and measurements for bounding boxes.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_BOUNDING_BOX_QUERIES_H
#define GEOPULSE_CORE_BOUNDING_BOX_QUERIES_H

#include "core/BoundingBox.h"
#include "core/Point.h"

namespace geopulse
{
namespace core
{

/** @brief Returns true when a point lies inside the rectangle. */
bool contains(const BoundingBox& box, const Point& point);

/** @brief Returns true when this box overlaps another box. */
bool intersects(const BoundingBox& a, const BoundingBox& b);

/**
         * @brief Lower-bound squared distance from a coordinate to this box.
         *
         * If the coordinate lies inside the box, the distance is exactly zero.
         * This is the fundamental heuristic that enables fast spatial pruning.
         */
double minDistanceSquaredTo(
    const BoundingBox& box, double xMiles, double yMiles
);

} // namespace core
} // namespace geopulse

#endif
