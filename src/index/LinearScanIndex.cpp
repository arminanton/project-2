/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    LinearScanIndex.cpp
 * Purpose:    Implements brute-force spatial queries.
 * ============================================================================
 */

#include "index/LinearScanIndex.h"

#include "core/BoundingBoxQueries.h"
#include "core/Distance.h"
#include "index/IndexUtils.h"

namespace geopulse
{
namespace index
{

/** @brief Checks every point and returns the deterministic closest record. */
core::NearestResult LinearScanIndex::nearest(const core::Point& query) const
{
    core::NearestResult best;
    if (_points == nullptr)
    {
        return best;
    }
    for (std::size_t index = 0; index < _points->size(); ++index)
    {
        const core::Point& point = (*_points)[index];
        const double distance = core::distanceSquared(point, query);
        if (isBetterCandidate(point, distance, best))
        {
            best.found = true;
            best.recordIndex = point.recordIndex;
            best.distanceSquared = distance;
        }
    }
    return best;
}

/** @brief Returns every point inside the requested radius. */
core::RecordIdList LinearScanIndex::radiusQuery(
    const core::Point& center, double radiusMiles
) const
{
    core::RecordIdList results;
    if (_points == nullptr || radiusMiles < 0.0)
    {
        return results;
    }
    const double radiusSquared = radiusMiles * radiusMiles;
    for (std::size_t index = 0; index < _points->size(); ++index)
    {
        const core::Point& point = (*_points)[index];
        if (core::distanceSquared(point, center) <= radiusSquared)
        {
            results.push_back(point.recordIndex);
        }
    }
    return results;
}

/** @brief Returns every point inside the requested rectangle. */
core::RecordIdList LinearScanIndex::rangeQuery(
    const core::BoundingBox& box
) const
{
    core::RecordIdList results;
    if (_points == nullptr || !box.isValid())
    {
        return results;
    }
    for (std::size_t index = 0; index < _points->size(); ++index)
    {
        if (core::contains(box, (*_points)[index]))
        {
            results.push_back((*_points)[index].recordIndex);
        }
    }
    return results;
}

} // namespace index
} // namespace geopulse
