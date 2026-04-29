/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    Checkpoint.h
 * Purpose:    Defines checkpoint metadata for resumable dataset loading.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_CHECKPOINT_H
#define GEOPULSE_DATA_CHECKPOINT_H

#include <cstdint>
#include <string>

namespace geopulse
{
namespace data
{

/** @brief Identifies the source file so stale checkpoints are rejected. */
struct FileIdentity
{
    std::uint64_t fileSize = 0; // File size in bytes.
    std::uint64_t modificationTime = 0; // Last modified time.
    bool valid = false; // True when stat information was read.
};

/** @brief Checkpoint state mirrors loader progress and accepted cache. */
struct CheckpointState
{
    std::string sourcePath; // CSV path used when saved.
    std::string cachePath; // Accepted-record cache path.
    std::string headerSignature; // Stable header fingerprint.
    std::uint64_t fileSize = 0; // Source size at checkpoint time.
    std::uint64_t modificationTime = 0; // Source modified time.
    std::uint64_t lastRowNumber = 0; // Last completed CSV row.
    std::uint64_t byteOffset = 0; // Safe resume byte offset.
    std::uint64_t acceptedRows = 0; // Accepted rows so far.
    std::uint64_t excludedRows = 0; // Rejected rows so far.
    std::uint64_t missingRows = 0; // Rows missing coordinates.
    std::uint64_t invalidRows = 0; // Rows with invalid coordinates.
    bool complete = false; // True when the load finished cleanly.
};

FileIdentity readFileIdentity(const std::string& path);
std::string defaultCheckpointPath(const std::string& sourcePath);
std::string defaultCachePath(const std::string& sourcePath);
std::string stableSignature(const std::string& text);
bool writeCheckpoint(const std::string& path, const CheckpointState& state);
bool readCheckpoint(const std::string& path, CheckpointState* state);
bool removeFileIfExists(const std::string& path);
bool checkpointMatches(
    const CheckpointState& state,
    const std::string& sourcePath,
    const FileIdentity& identity,
    const std::string& headerSignature
);

} // namespace data
} // namespace geopulse

#endif
