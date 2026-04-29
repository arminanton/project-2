/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Projection.h
 * Purpose: Converts latitude and longitude into planar mile coordinates.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_PROJECTION_H
#define GEOPULSE_CORE_PROJECTION_H

#include "core/Point.h"

namespace geopulse
{
namespace core
{

/** @brief Holds the projected x/y coordinates used by the indexes. */
struct ProjectedCoordinate
{
    /** @brief East-west distance coordinate in miles. */
    double xMiles = 0.0;

    /** @brief North-south distance coordinate in miles. */
    double yMiles = 0.0;
};

/** @brief Validates that lat/lon are finite and within legal range. */
bool isValidLatitudeLongitude(double latitude, double longitude);

/** @brief Projects latitude/longitude into a local NYC mile plane. */
ProjectedCoordinate projectLatitudeLongitude(double latitude, double longitude);

/** @brief Creates a complete point for a valid collision record. */
Point makePoint(std::size_t recordIndex, double latitude, double longitude);

} // namespace core
} // namespace geopulse

#endif
