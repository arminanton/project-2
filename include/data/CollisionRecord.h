/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CollisionRecord.h
 * Purpose:    Defines the accepted collision fields kept in memory.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_COLLISION_RECORD_H
#define GEOPULSE_DATA_COLLISION_RECORD_H

#include <cstddef>
#include <string>

namespace geopulse
{
namespace data
{

/** @brief Stores metadata needed to display or explain a collision result. */
struct CollisionRecord
{
    std::size_t sourceRowNumber = 0; // Original CSV row number.
    std::string collisionId; // NYC collision identifier.
    std::string crashDate; // Crash date as exported.
    std::string crashTime; // Crash time as exported.
    std::string borough; // Optional NYC borough value.
    double latitude = 0.0; // Accepted latitude.
    double longitude = 0.0; // Accepted longitude.
    int personsInjured = 0; // Parsed injury count.
    int personsKilled = 0; // Parsed fatality count.
};

} // namespace data
} // namespace geopulse

#endif
