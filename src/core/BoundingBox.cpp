/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    BoundingBox.cpp
 * Purpose: Implements rectangle checks used by range and pruning logic.
 * ============================================================================
 */

#include "core/BoundingBox.h"

namespace geopulse
{
namespace core
{

BoundingBox::BoundingBox() = default;

BoundingBox::BoundingBox(
    double minXValue, double maxXValue, double minYValue, double maxYValue
) :
    minX(minXValue),
    maxX(maxXValue),
    minY(minYValue),
    maxY(maxYValue)
{
}

double BoundingBox::width() const { return maxX - minX; }

double BoundingBox::height() const { return maxY - minY; }

bool BoundingBox::isValid() const
{
    // The box is flipped or collapsed if minimums exceed maximums.
    return minX <= maxX && minY <= maxY;
}

} // namespace core
} // namespace geopulse
