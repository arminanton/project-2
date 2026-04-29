/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    TestHelpers.h
 * Purpose:    Provides small helpers that keep Catch2 tests readable.
 * ============================================================================
 */

#ifndef GEOPULSE_TESTS_HELPERS_TEST_HELPERS_H
#define GEOPULSE_TESTS_HELPERS_TEST_HELPERS_H

#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "ui/ArgumentParser.h"

namespace geopulse
{
namespace tests
{

/** @brief Builds an absolute path to a repository file for local tests. */
inline std::string sourcePath(const std::string& relativePath)
{
    return std::string(GEOPULSE_SOURCE_DIR) + "/" + relativePath;
}

/** @brief Checks exact text output and prints a helpful Catch2 comparison. */
inline void requireOutput(
    const std::string& actual, const std::string& expected
)
{
    REQUIRE(actual == expected);
}

/** @brief Checks a named boolean condition. */
inline void requireCondition(bool condition) { REQUIRE(condition); }

/** @brief Checks that a parsed command was rejected. */
inline void requireUnsuccessful(const ui::CliOptions& options)
{
    REQUIRE_FALSE(options.valid);
    REQUIRE_FALSE(options.errorMessage.empty());
}

/** @brief Checks that a container has the expected size. */
template <typename Container>
void requireBulk(const Container& values, std::size_t expectedSize)
{
    REQUIRE(values.size() == expectedSize);
}

/** @brief Parses a vector of argument strings as if they came from main. */
inline ui::CliOptions parseCommand(std::vector<std::string> args)
{
    std::vector<char*> raw;
    for (std::size_t index = 0; index < args.size(); ++index)
    {
        raw.push_back(&args[index][0]);
    }
    return ui::parseArguments(static_cast<int>(raw.size()), raw.data());
}

} // namespace tests
} // namespace geopulse

#endif
