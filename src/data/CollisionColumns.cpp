/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CollisionColumns.cpp
 * Purpose:    Resolves required NYC collision CSV columns by name.
 * ============================================================================
 */

#include "data/CollisionColumns.h"

#include <sstream>

namespace geopulse
{
namespace data
{
namespace
{

/** @brief Finds one column name and records a missing name when absent. */
void requireColumn(
    const CsvRow& header,
    const std::string& name,
    std::size_t* target,
    CollisionColumns* columns
)
{
    for (std::size_t index = 0; index < header.size(); ++index)
    {
        if (header[index] == name)
        {
            *target = index;
            return;
        }
    }
    columns->missingColumns.push_back(name);
}

} // namespace

/** @brief Resolves all columns needed by the project from the CSV header. */
CollisionColumns resolveCollisionColumns(const CsvRow& header)
{
    CollisionColumns columns;
    requireColumn(header, "CRASH DATE", &columns.crashDate, &columns);
    requireColumn(header, "CRASH TIME", &columns.crashTime, &columns);
    requireColumn(header, "BOROUGH", &columns.borough, &columns);
    requireColumn(header, "LATITUDE", &columns.latitude, &columns);
    requireColumn(header, "LONGITUDE", &columns.longitude, &columns);
    requireColumn(
        header, "NUMBER OF PERSONS INJURED", &columns.personsInjured, &columns
    );
    requireColumn(
        header, "NUMBER OF PERSONS KILLED", &columns.personsKilled, &columns
    );
    requireColumn(header, "COLLISION_ID", &columns.collisionId, &columns);
    columns.valid = columns.missingColumns.empty();
    return columns;
}

/** Joins header cells into a stable string used for checkpoint identity. */
std::string joinHeaderSignature(const CsvRow& header)
{
    std::ostringstream output;
    for (std::size_t index = 0; index < header.size(); ++index)
    {
        if (index > 0)
        {
            output << '|';
        }
        output << header[index];
    }
    return output.str();
}

/** Builds a helpful error message when a dataset is not the expected schema. */
std::string missingColumnMessage(const CollisionColumns& columns)
{
    std::ostringstream output;
    output << "dataset is missing required columns";
    for (std::size_t index = 0; index < columns.missingColumns.size(); ++index)
    {
        output << (index == 0 ? ": " : ", ") << columns.missingColumns[index];
    }
    return output.str();
}

} // namespace data
} // namespace geopulse
