/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    IndexUtils.h
 * Purpose:    Declares helper functions shared by the spatial indexes.
 * ============================================================================
 */

#ifndef GEOPULSE_INDEX_INDEX_UTILS_H
#define GEOPULSE_INDEX_INDEX_UTILS_H

#include <vector>

#include "core/BoundingBox.h"
#include "core/Point.h"
#include "core/QueryTypes.h"

namespace geopulse
{
namespace index
{

bool axisLess(const core::Point& left, const core::Point& right, int axis);
double axisValue(const core::Point& point, int axis);
bool isBetterCandidate(
    const core::Point& candidate,
    double distanceSquared,
    const core::NearestResult& best
);
core::BoundingBox boundsForPoints(const std::vector<core::Point>& points);

} // namespace index
} // namespace geopulse

#endif
