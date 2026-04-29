/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    StyleGuardHelpers.h
 * Purpose:    Provides reusable helpers for the local style guard test.
 * ============================================================================
 */

#ifndef GEOPULSE_TESTS_HELPERS_STYLE_GUARD_HELPERS_H
#define GEOPULSE_TESTS_HELPERS_STYLE_GUARD_HELPERS_H

#include <cctype>
#include <dirent.h>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "catch_amalgamated.hpp"

namespace geopulse
{
namespace tests
{
namespace style_guard
{

/** @brief Returns true when a path ends with the requested suffix. */
inline bool hasEnding(const std::string& value, const std::string& ending)
{
    return value.size() >= ending.size() &&
           value.substr(value.size() - ending.size()) == ending;
}

/** @brief Uses POSIX stat because the project is intentionally C++14. */
inline bool isDirectory(const std::string& path)
{
    struct stat info;
    return stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode);
}

/** @brief Third-party Catch2 files are not expected to match student style. */
inline bool isCheckedCodeFile(const std::string& path)
{
    return path.find("/tests/catch2/") == std::string::npos &&
           (hasEnding(path, ".h") || hasEnding(path, ".cpp"));
}

/** @brief Recursively collects local C++ files for style checks. */
inline void collectFiles(
    const std::string& directory, std::vector<std::string>* files
)
{
    DIR* handle = opendir(directory.c_str());
    if (handle == nullptr)
    {
        return;
    }
    dirent* entry = nullptr;
    while ((entry = readdir(handle)) != nullptr)
    {
        const std::string name = entry->d_name;
        if (name == "." || name == "..")
        {
            continue;
        }
        const std::string path = directory + "/" + name;
        if (isDirectory(path))
        {
            collectFiles(path, files);
        }
        else if (isCheckedCodeFile(path))
        {
            files->push_back(path);
        }
    }
    closedir(handle);
}

/** @brief Test files use CamelCase names, except skipped external Catch2. */
inline void requireCamelCaseTestName(const std::string& path)
{
    if (path.find("/tests/") == std::string::npos)
    {
        return;
    }
    const std::size_t slash = path.find_last_of('/');
    const char first = path[slash + 1];
    REQUIRE(std::isupper(static_cast<unsigned char>(first)) != 0);
}

} // namespace style_guard
} // namespace tests
} // namespace geopulse

#endif
