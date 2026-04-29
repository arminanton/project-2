/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    ResultComparator.cpp
 * Purpose:    Implements normalized comparison helpers for benchmarks.
 * ============================================================================
 */

#include "query/ResultComparator.h"

#include <algorithm>

namespace geopulse
{
namespace query
{

/** @brief Sorts ids so tree traversal order cannot cause false mismatches. */
core::RecordIdList normalized(core::RecordIdList values)
{
    std::sort(values.begin(), values.end());
    return values;
}

/** @brief Compares query results as sets of record ids. */
bool sameRecordSet(core::RecordIdList left, core::RecordIdList right)
{
    return normalized(left) == normalized(right);
}

/** @brief Compares the selected record and whether a result exists. */
bool sameNearest(
    const core::NearestResult& left, const core::NearestResult& right
)
{
    if (left.found != right.found)
    {
        return false;
    }
    return !left.found || left.recordIndex == right.recordIndex;
}

} // namespace query
} // namespace geopulse
