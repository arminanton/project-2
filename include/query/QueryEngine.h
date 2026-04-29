/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    QueryEngine.h
 * Purpose:    Converts user coordinates into index query calls.
 * ============================================================================
 */

#ifndef GEOPULSE_QUERY_QUERY_ENGINE_H
#define GEOPULSE_QUERY_QUERY_ENGINE_H

#include "index/SpatialIndex.h"

namespace geopulse
{
namespace query
{

/** @brief Thin facade that hides projection details from menus and tests. */
class QueryEngine
{
public:
    /** @brief Uses a non-owning pointer to an already-built index. */
    explicit QueryEngine(const index::SpatialIndex* spatialIndex);

    /** @brief Finds the closest record to a latitude/longitude coordinate. */
    core::NearestResult nearest(double latitude, double longitude) const;

    /** @brief Finds records inside a radius measured in miles. */
    core::RecordIdList radius(
        double latitude, double longitude, double radiusMiles
    ) const;

    /** @brief Finds records inside a latitude/longitude rectangle. */
    core::RecordIdList range(
        double minLatitude,
        double maxLatitude,
        double minLongitude,
        double maxLongitude
    ) const;

private:
    const index::SpatialIndex* _index; // Non-owning index view.
};

} // namespace query
} // namespace geopulse

#endif
