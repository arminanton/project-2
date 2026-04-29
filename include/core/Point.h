/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Point.h
 * Purpose: Defines the lightweight point stored by spatial indexes.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_POINT_H
#define GEOPULSE_CORE_POINT_H

#include <cstddef>

namespace geopulse
{
namespace core
{

/**
 * @brief Represents one collision in original and projected units.
 *
 * The recordIndex points to DataSet::records, avoiding copying large
 * string fields into tree nodes while allowing query results to find the
 * original CSV data for printing.
 */
struct Point
{
    /** @brief Position of the CollisionRecord in the record vector. */
    std::size_t recordIndex = 0;

    /** @brief Original latitude from the CSV file. */
    double latitude = 0.0;

    /** @brief Original longitude from the CSV file. */
    double longitude = 0.0;

    /** @brief Projected horizontal coordinate measured in miles. */
    double xMiles = 0.0;

    /** @brief Projected vertical coordinate measured in miles. */
    double yMiles = 0.0;
};

} // namespace core
} // namespace geopulse

#endif
