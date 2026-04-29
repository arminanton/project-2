/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Projection.cpp
 * Purpose: Implements coordinate validation and NYC projection helpers.
 * ============================================================================
 */

#include "core/Projection.h"

#include <cmath>

#include "core/Constants.h"
#include "core/Distance.h"

namespace geopulse
{
namespace core
{

/**
         * @brief Validates coordinates before entering spatial structures.
         *
         * Empty fields are rejected by the CSV parser first. Here we only
         * guard against mathematically invalid floating-point values
         * and coordinates that lie outside the Earth's boundaries.
         */
bool isValidLatitudeLongitude(double latitude, double longitude)
{
    return std::isfinite(latitude) && std::isfinite(longitude) &&
           latitude >= -90.0 && latitude <= 90.0 && longitude >= -180.0 &&
           longitude <= 180.0;
}

/**
         * @brief Projects lat/lon to a local plane measured in miles.
         *
         * NYC covers a small enough area that this simple projection keeps
         * distances accurate while avoiding expensive spherical math 
         * inside every tree traversal query.
         */
ProjectedCoordinate projectLatitudeLongitude(double latitude, double longitude)
{
    const double referenceRadians = degToRad(constants::kNycReferenceLatitude);
    ProjectedCoordinate projected;
    projected.xMiles = longitude * std::cos(referenceRadians) *
                       constants::kMilesPerLatitudeDegree;
    projected.yMiles = latitude * constants::kMilesPerLatitudeDegree;
    return projected;
}

/** @brief Creates the point object used by indexing structures. */
Point makePoint(std::size_t recordIndex, double latitude, double longitude)
{
    const ProjectedCoordinate projected =
        projectLatitudeLongitude(latitude, longitude);
    Point point;
    point.recordIndex = recordIndex;
    point.latitude = latitude;
    point.longitude = longitude;
    point.xMiles = projected.xMiles;
    point.yMiles = projected.yMiles;
    return point;
}

} // namespace core
} // namespace geopulse
