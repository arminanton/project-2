/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CollisionColumns.h
 * Purpose:    Maps NYC CSV column names to parser indexes.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_COLLISION_COLUMNS_H
#define GEOPULSE_DATA_COLLISION_COLUMNS_H

#include <cstddef>
#include <string>
#include <vector>

#include "data/CsvReader.h"

namespace geopulse
{
namespace data
{

/** @brief Holds resolved column positions from the CSV header row. */
struct CollisionColumns
{
    std::size_t crashDate = 0; // CRASH DATE column index.
    std::size_t crashTime = 0; // CRASH TIME column index.
    std::size_t borough = 0; // BOROUGH column index.
    std::size_t latitude = 0; // LATITUDE column index.
    std::size_t longitude = 0; // LONGITUDE column index.
    std::size_t personsInjured = 0; // Injury count index.
    std::size_t personsKilled = 0; // Fatality count index.
    std::size_t collisionId = 0; // COLLISION_ID column index.
    bool valid = false; // True when all required columns exist.
    std::vector<std::string> missingColumns; // Missing names.
};

/** @brief Finds required NYC collision columns from the header row. */
CollisionColumns resolveCollisionColumns(const CsvRow& header);

/** @brief Joins a header into a stable value used by checkpoints. */
std::string joinHeaderSignature(const CsvRow& header);

/** @brief Formats a message listing missing required columns. */
std::string missingColumnMessage(const CollisionColumns& columns);

} // namespace data
} // namespace geopulse

#endif
