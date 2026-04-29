/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    LinearScanIndex.h
 * Purpose:    Declares the brute-force baseline spatial index.
 * ============================================================================
 */

#ifndef GEOPULSE_INDEX_LINEAR_SCAN_INDEX_H
#define GEOPULSE_INDEX_LINEAR_SCAN_INDEX_H

#include "index/SpatialIndex.h"

namespace geopulse
{
namespace index
{

/** @brief Brute-force index used as the correctness oracle. */
class LinearScanIndex : public SpatialIndex
{
public:
    /** @brief Starts with no attached point vector. */
    LinearScanIndex();

    /** @brief Human-readable algorithm name for reports. */
    std::string name() const override;

    /** @brief Keeps a non-owning pointer to the loaded point vector. */
    void build(const std::vector<core::Point>& points) override;

    /** @brief Checks every point and returns the closest one. */
    core::NearestResult nearest(const core::Point& query) const override;

    /** @brief Checks every point against a circular radius. */
    core::RecordIdList radiusQuery(
        const core::Point& center, double radiusMiles
    ) const override;

    /** @brief Checks every point against a bounding rectangle. */
    core::RecordIdList rangeQuery(const core::BoundingBox& box) const override;

    /** @brief Returns the attached point-vector size. */
    std::size_t size() const override;

private:
    const std::vector<core::Point>* _points; // Data view.
};

} // namespace index
} // namespace geopulse

#endif
