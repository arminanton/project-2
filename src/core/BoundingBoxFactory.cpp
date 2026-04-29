/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BoundingBoxFactory.cpp
 * Purpose: Implements construction of boxes from geographic coordinates.
 * ============================================================================
 */

#include "core/BoundingBoxFactory.h"

#include "core/Projection.h"

namespace geopulse
{
namespace core
{

BoundingBox boundingBoxFromLatitudeLongitude(
    double minLatitude,
    double maxLatitude,
    double minLongitude,
    double maxLongitude
)
{
    // Standard distance math fails directly on lat/lon degrees, so we
    // project the low and high corners onto a flat mile grid first.
    const ProjectedCoordinate low =
        projectLatitudeLongitude(minLatitude, minLongitude);

    const ProjectedCoordinate high =
        projectLatitudeLongitude(maxLatitude, maxLongitude);

    return BoundingBox(low.xMiles, high.xMiles, low.yMiles, high.yMiles);
}

} // namespace core
} // namespace geopulse
