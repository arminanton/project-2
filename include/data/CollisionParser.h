/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CollisionParser.h
 * Purpose:    Converts CSV rows into validated collision records.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_COLLISION_PARSER_H
#define GEOPULSE_DATA_COLLISION_PARSER_H

#include <cstddef>
#include <string>

#include "core/Point.h"
#include "data/CollisionColumns.h"
#include "data/CollisionRecord.h"

namespace geopulse
{
namespace data
{

/** @brief Describes whether one CSV row became an accepted spatial point. */
struct CollisionParseResult
{
    bool accepted = false;          // True when a record and point exist.
    bool missingCoordinate = false; // Coordinate was empty.
    bool invalidCoordinate = false; // Coordinate failed validation.
    std::string rejectionReason;    // Human-readable reject reason.
    CollisionRecord record;         // Parsed collision metadata.
    core::Point point;              // Lightweight indexed point.
};

/** @brief Parses and validates one collision row from the CSV file. */
CollisionParseResult parseCollisionRow(
    const CsvRow& row,
    const CollisionColumns& columns,
    std::size_t sourceRowNumber,
    std::size_t recordIndex
);

} // namespace data
} // namespace geopulse

#endif
