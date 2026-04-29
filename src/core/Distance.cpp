/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Distance.cpp
 * Purpose: Implements distance math for all comparable indexes.
 * ============================================================================
 */

#include "core/Distance.h"

#include <cmath>

#include "core/Constants.h"

namespace geopulse
{
namespace core
{

/** @brief Converts degree input to radians for trigonometric calls. */
double degToRad(double degrees) { return degrees * constants::kPi / 180.0; }

/**
 * @brief Computes squared distance to avoid expensive square roots.
 *
 * Since distance functions are monotonic for positive values, squared
 * distances strictly preserve that order. Square roots are expensive 
 * and completely unnecessary for nearest-neighbor or radius checks.
 */
double distanceSquared(double leftX, double leftY, double rightX, double rightY)
{
    const double dx = leftX - rightX;
    const double dy = leftY - rightY;
    return dx * dx + dy * dy;
}

/** @brief Computes squared distance between two projected points. */
double distanceSquared(const Point& left, const Point& right)
{
    return distanceSquared(
        left.xMiles, left.yMiles, right.xMiles, right.yMiles
    );
}

/** @brief Computes human-readable distance between two projected points. */
double distanceMiles(const Point& left, const Point& right)
{
    return std::sqrt(distanceSquared(left, right));
}

} // namespace core
} // namespace geopulse
