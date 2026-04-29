/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CheckpointPaths.cpp
 * Purpose:    Implements file identity and checkpoint path helpers.
 * ============================================================================
 */

#include "data/Checkpoint.h"
#include <cerrno>

#include <cstdio>
#include <sys/stat.h>

namespace geopulse
{
namespace data
{

/** @brief Reads file size and modification time for checkpoint validation. */
FileIdentity readFileIdentity(const std::string& path)
{
    struct stat info;
    FileIdentity identity;
    if (stat(path.c_str(), &info) != 0)
    {
        return identity;
    }
    identity.fileSize = static_cast<std::uint64_t>(info.st_size);
    identity.modificationTime = static_cast<std::uint64_t>(info.st_mtime);
    identity.valid = true;
    return identity;
}

/** @brief Builds the default checkpoint filename beside the source CSV. */
std::string defaultCheckpointPath(const std::string& sourcePath)
{
    return sourcePath + ".geopulse.checkpoint.json";
}

/** Builds the default accepted-record cache filename beside the source CSV. */
std::string defaultCachePath(const std::string& sourcePath)
{
    return sourcePath + ".geopulse.accepted.tsv";
}

/** @brief Removes a file when it exists; missing files are also success. */
bool removeFileIfExists(const std::string& path)
{
    if (path.empty())
    {
        return true;
    }
    return std::remove(path.c_str()) == 0 || errno == ENOENT;
}

} // namespace data
} // namespace geopulse
