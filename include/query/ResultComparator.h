/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    ResultComparator.h
 * Purpose:    Declares normalized result comparison helpers.
 * ============================================================================
 */

#ifndef GEOPULSE_QUERY_RESULT_COMPARATOR_H
#define GEOPULSE_QUERY_RESULT_COMPARATOR_H

#include "core/QueryTypes.h"

namespace geopulse
{
namespace query
{

/** @brief Returns a sorted copy so traversal order does not matter. */
core::RecordIdList normalized(core::RecordIdList values);

/** @brief Compares two record lists as mathematical sets. */
bool sameRecordSet(core::RecordIdList left, core::RecordIdList right);

/** @brief Compares nearest-neighbor answers with deterministic ties. */
bool sameNearest(
    const core::NearestResult& left, const core::NearestResult& right
);

} // namespace query
} // namespace geopulse

#endif
