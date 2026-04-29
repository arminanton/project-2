/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Distance.h
 * Purpose: Defines distance helpers shared by all spatial indexes.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_DISTANCE_H
#define GEOPULSE_CORE_DISTANCE_H

#include "core/Point.h"

namespace geopulse
{
namespace core
{

/** @brief Converts degrees to radians for trigonometric formulas. */
double degToRad(double degrees);

/** @brief Returns squared planar distance between two coordinates. */
double distanceSquared(
    double leftX, double leftY, double rightX, double rightY
);

/** @brief Returns squared planar distance between two points. */
double distanceSquared(const Point& left, const Point& right);

/** @brief Returns planar distance in miles between two points. */
double distanceMiles(const Point& left, const Point& right);

} // namespace core
} // namespace geopulse

#endif
