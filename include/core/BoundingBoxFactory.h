/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BoundingBoxFactory.h
 * Purpose: Provides constructors mapping geographic coordinates to boxes.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_BOUNDING_BOX_FACTORY_H
#define GEOPULSE_CORE_BOUNDING_BOX_FACTORY_H

#include "core/BoundingBox.h"

namespace geopulse
{
namespace core
{

/**
         * @brief Creates a projected box from latitude/longitude limits.
         *
         * Converts raw geographic coordinates into our internal flat projection
         * before constructing the box. This ensures all subsequent spatial math
         * operates in miles rather than degrees.
         */
BoundingBox boundingBoxFromLatitudeLongitude(
    double minLatitude,
    double maxLatitude,
    double minLongitude,
    double maxLongitude
);

} // namespace core
} // namespace geopulse

#endif
