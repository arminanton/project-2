/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    QueryEngine.cpp
 * Purpose:    Implements the coordinate-aware query facade.
 * ============================================================================
 */

#include "query/QueryEngine.h"

#include "core/BoundingBox.h"
#include "core/BoundingBoxFactory.h"
#include "core/Projection.h"

namespace geopulse
{
namespace query
{

/** @brief Stores a non-owning pointer to an already-built spatial index. */
QueryEngine::QueryEngine(const index::SpatialIndex* spatialIndex) :
    _index(spatialIndex)
{
}

/** Runs nearest-neighbor search after projecting the query coordinate. */
core::NearestResult QueryEngine::nearest(
    double latitude, double longitude
) const
{
    if (_index == nullptr)
    {
        return core::NearestResult();
    }
    return _index->nearest(core::makePoint(0, latitude, longitude));
}

/** @brief Runs a circular radius query in miles. */
core::RecordIdList QueryEngine::radius(
    double latitude, double longitude, double radiusMiles
) const
{
    if (_index == nullptr)
    {
        return core::RecordIdList();
    }
    return _index->radiusQuery(
        core::makePoint(0, latitude, longitude), radiusMiles
    );
}

/** @brief Runs a rectangular latitude/longitude range query. */
core::RecordIdList QueryEngine::range(
    double minLatitude,
    double maxLatitude,
    double minLongitude,
    double maxLongitude
) const
{
    if (_index == nullptr)
    {
        return core::RecordIdList();
    }
    const core::BoundingBox box = core::boundingBoxFromLatitudeLongitude(
        minLatitude, maxLatitude, minLongitude, maxLongitude
    );
    return _index->rangeQuery(box);
}

} // namespace query
} // namespace geopulse
