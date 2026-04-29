/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Constants.h
 * Purpose: Keeps shared numeric and text constants in one place.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_CONSTANTS_H
#define GEOPULSE_CORE_CONSTANTS_H

#include <cstdint>
#include <cstddef>

namespace geopulse
{
namespace core
{
namespace constants
{

/** @brief Application version used by the CLI and report. */
constexpr const char* kVersion = "0.2.0";

/** @brief Earth-mile approximation for the NYC planar projection. */
constexpr double kMilesPerLatitudeDegree = 69.0;

/** @brief Reference latitude keeps x distances realistic near NYC. */
constexpr double kNycReferenceLatitude = 40.7128;

/** @brief Pi value required since C++14 lacks std::numbers. */
constexpr double kPi = 3.14159265358979323846;

/** @brief Small tolerance for equal floating-point distances. */
constexpr double kDistanceTolerance = 1.0e-12;

/** @brief Tree axes: 0 means x/longitude, 1 means y/latitude. */
constexpr int kAxisCount = 2;
constexpr int kXAxis = 0;
constexpr int kYAxis = 1;

/** @brief Quadtree tuning to prevent very deep duplicate splits. */
constexpr double kRootPaddingMiles = 0.001;
constexpr std::size_t kQuadNodeCapacity = 32;
constexpr int kQuadMaxDepth = 28;

/** @brief Data loading progress defaults. */
constexpr std::uint64_t kCheckpointIntervalRows = 100000;
constexpr std::uint64_t kProgressIntervalRows = 250000;

/** @brief Benchmark defaults used by the command line report. */
constexpr std::size_t kBenchmarkQueryCount = 5;
constexpr double kBenchmarkRadiusMiles = 0.5;
constexpr double kBenchmarkRangeHalfMiles = 0.5;

} // namespace constants
} // namespace core
} // namespace geopulse

#endif
