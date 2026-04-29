/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    LinearScanMeta.cpp
 * Purpose:    Implements simple LinearScanIndex lifecycle methods.
 * ============================================================================
 */

#include "index/LinearScanIndex.h"

namespace geopulse
{
namespace index
{

/** @brief Creates an empty scan index. */
LinearScanIndex::LinearScanIndex() :
    _points(nullptr)
{
}

std::string LinearScanIndex::name() const { return "Linear Scan"; }

/** @brief Stores a safe reference to the project-owned point vector. */
void LinearScanIndex::build(const std::vector<core::Point>& points)
{
    _points = &points;
}

std::size_t LinearScanIndex::size() const
{
    return _points == nullptr ? 0 : _points->size();
}

} // namespace index
} // namespace geopulse
