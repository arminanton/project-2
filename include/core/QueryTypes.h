/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    QueryTypes.h
 * Purpose: Defines shared query result containers.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_QUERY_TYPES_H
#define GEOPULSE_CORE_QUERY_TYPES_H

#include <cstddef>
#include <limits>
#include <vector>

namespace geopulse
{
namespace core
{

/** @brief Stores the best answer found by a nearest-neighbor search. */
struct NearestResult
{
    /** @brief False means the index did not contain any points. */
    bool found = false;

    /** @brief Index of the winning record in DataSet::records. */
    std::size_t recordIndex = 0;

    /** @brief Squared miles are kept to avoid repeated square roots. */
    double distanceSquared = std::numeric_limits<double>::infinity();
};

/** @brief Query results are record indexes into DataSet::records. */
using RecordIdList = std::vector<std::size_t>;

} // namespace core
} // namespace geopulse

#endif
