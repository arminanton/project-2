/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    StyleGuardTest.cpp
 * Purpose:    Enforces file budgets, comments, and basic naming rules.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include <fstream>
#include <string>
#include <vector>

#include "helpers/StyleGuardHelpers.h"
#include "helpers/TestHelpers.h"

namespace
{

/** @brief Checks constraints that do not need optional style tools. */
void checkOneFile(const std::string& path)
{
    std::ifstream input(path.c_str());
    REQUIRE(input.is_open());
    std::string line;
    std::size_t lineCount = 0;
    bool sawBanner = false;
    while (std::getline(input, line))
    {
        ++lineCount;
        sawBanner = sawBanner ||
                    (lineCount == 1 &&
                     (line == "// ========================================" ||
                      line.find("/* ================================") == 0));
        INFO(path << ":" << lineCount);
        REQUIRE(line.size() <= 80);
        const std::string banned = "using namespace " + std::string("std;");
        REQUIRE(line.find(banned) == std::string::npos);
    }
    INFO(path);
    REQUIRE(lineCount <= 100);
    REQUIRE(sawBanner);
    geopulse::tests::style_guard::requireCamelCaseTestName(path);
}

} // namespace

TEST_CASE("Student source and test files respect style rules", "[style]")
{
    std::vector<std::string> files;
    geopulse::tests::style_guard::collectFiles(
        geopulse::tests::sourcePath("include"), &files
    );
    geopulse::tests::style_guard::collectFiles(
        geopulse::tests::sourcePath("src"), &files
    );
    geopulse::tests::style_guard::collectFiles(
        geopulse::tests::sourcePath("tests"), &files
    );
    REQUIRE_FALSE(files.empty());
    for (std::size_t index = 0; index < files.size(); ++index)
    {
        checkOneFile(files[index]);
    }
}
