/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CheckpointMatch.cpp
 * Purpose:    Checks whether a checkpoint still belongs to the source CSV.
 * ============================================================================
 */

#include "data/Checkpoint.h"

namespace geopulse
{
namespace data
{

/** @brief Rejects stale checkpoints before the loader trusts cached records. */
bool checkpointMatches(
    const CheckpointState& state,
    const std::string& sourcePath,
    const FileIdentity& identity,
    const std::string& headerSignature
)
{
    return state.sourcePath == sourcePath &&
           state.fileSize == identity.fileSize &&
           state.modificationTime == identity.modificationTime &&
           state.headerSignature == headerSignature;
}

} // namespace data
} // namespace geopulse
