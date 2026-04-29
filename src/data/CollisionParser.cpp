/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CollisionParser.cpp
 * Purpose:    Validates CSV fields before turning them into spatial points.
 * ============================================================================
 */

#include "data/CollisionParser.h"

#include <cmath>
#include <cstdlib>

#include "core/Projection.h"

namespace geopulse
{
namespace data
{
namespace
{

std::string fieldAt(const CsvRow& row, std::size_t index)
{
    return index < row.size() ? row[index] : std::string();
}

bool parseDoubleStrict(const std::string& text, double* value)
{
    if (text.empty() || value == nullptr)
    {
        return false;
    }
    char* end = nullptr;
    const double parsed = std::strtod(text.c_str(), &end);
    if (end == text.c_str() || *end != '\0' || !std::isfinite(parsed))
    {
        return false;
    }
    *value = parsed;
    return true;
}

int parseIntOrZero(const std::string& text)
{
    return text.empty()
               ? 0
               : static_cast<int>(std::strtol(text.c_str(), nullptr, 10));
}

} // namespace

/** Attempts to parse one collision row into an accepted record and point. */
CollisionParseResult parseCollisionRow(
    const CsvRow& row,
    const CollisionColumns& columns,
    std::size_t sourceRowNumber,
    std::size_t recordIndex
)
{
    CollisionParseResult result;
    const std::string latitudeText = fieldAt(row, columns.latitude);
    const std::string longitudeText = fieldAt(row, columns.longitude);
    if (latitudeText.empty() || longitudeText.empty())
    {
        result.missingCoordinate = true;
        result.rejectionReason = "missing coordinate";
        return result;
    }
    double latitude = 0.0;
    double longitude = 0.0;
    if (!parseDoubleStrict(latitudeText, &latitude) ||
        !parseDoubleStrict(longitudeText, &longitude) ||
        !core::isValidLatitudeLongitude(latitude, longitude))
    {
        result.invalidCoordinate = true;
        result.rejectionReason = "invalid coordinate";
        return result;
    }
    result.accepted = true;
    result.record.sourceRowNumber = sourceRowNumber;
    result.record.collisionId = fieldAt(row, columns.collisionId);
    result.record.crashDate = fieldAt(row, columns.crashDate);
    result.record.crashTime = fieldAt(row, columns.crashTime);
    result.record.borough = fieldAt(row, columns.borough);
    result.record.latitude = latitude;
    result.record.longitude = longitude;
    result.record.personsInjured =
        parseIntOrZero(fieldAt(row, columns.personsInjured));
    result.record.personsKilled =
        parseIntOrZero(fieldAt(row, columns.personsKilled));
    result.point = core::makePoint(recordIndex, latitude, longitude);
    return result;
}

} // namespace data
} // namespace geopulse
