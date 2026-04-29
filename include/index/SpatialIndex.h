/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    SpatialIndex.h
 * Purpose:    Defines the common interface for comparable spatial indexes.
 * ============================================================================
 */

#ifndef GEOPULSE_INDEX_SPATIAL_INDEX_H
#define GEOPULSE_INDEX_SPATIAL_INDEX_H

#include <cstddef>
#include <string>
#include <vector>

#include "core/BoundingBox.h"
#include "core/Point.h"
#include "core/QueryTypes.h"

namespace geopulse
{
namespace index
{

/**
 * @brief Common API that lets benchmarks compare structures fairly.
 *
 * Inheritance is appropriate here because the project intentionally compares
 * multiple interchangeable implementations of the same spatial operations.
 */
class SpatialIndex
{
public:
    /** @brief Virtual destructor allows deleting through this interface. */
    virtual ~SpatialIndex() {}

    /** @brief Human-readable algorithm name. */
    virtual std::string name() const = 0;

    /** @brief Builds the structure from shared point data. */
    virtual void build(const std::vector<core::Point>& points) = 0;

    /** @brief Finds the closest indexed point to query. */
    virtual core::NearestResult nearest(const core::Point& query) const = 0;

    /** @brief Finds all records within radiusMiles of center. */
    virtual core::RecordIdList radiusQuery(
        const core::Point& center, double radiusMiles
    ) const = 0;

    /** @brief Finds all records inside the projected box. */
    virtual core::RecordIdList rangeQuery(
        const core::BoundingBox& box
    ) const = 0;

    /** @brief Returns the number of indexed points. */
    virtual std::size_t size() const = 0;
};

} // namespace index
} // namespace geopulse

#endif
