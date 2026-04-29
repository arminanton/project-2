/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CheckpointIo.cpp
 * Purpose:    Saves checkpoint files used by recovery mode.
 * ============================================================================
 */

#include "data/Checkpoint.h"

#include <cstdio>
#include <fstream>

#include "data/CheckpointJson.h"

namespace geopulse
{
namespace data
{

/** @brief Writes checkpoint state through a temporary file. */
bool writeCheckpoint(const std::string& path, const CheckpointState& state)
{
    const std::string tempPath = path + ".tmp";
    std::ofstream output(tempPath.c_str(), std::ios::out | std::ios::trunc);
    if (!output.is_open())
    {
        return false;
    }
    output << "{\n";
    checkpoint_json::writeString(
        &output, "sourcePath", state.sourcePath, false
    );
    checkpoint_json::writeString(&output, "cachePath", state.cachePath, false);
    checkpoint_json::writeString(
        &output, "headerSignature", state.headerSignature, false
    );
    checkpoint_json::writeNumber(&output, "fileSize", state.fileSize, false);
    checkpoint_json::writeNumber(
        &output, "modificationTime", state.modificationTime, false
    );
    checkpoint_json::writeNumber(
        &output, "lastRowNumber", state.lastRowNumber, false
    );
    checkpoint_json::writeNumber(
        &output, "byteOffset", state.byteOffset, false
    );
    checkpoint_json::writeNumber(
        &output, "acceptedRows", state.acceptedRows, false
    );
    checkpoint_json::writeNumber(
        &output, "excludedRows", state.excludedRows, false
    );
    checkpoint_json::writeNumber(
        &output, "missingRows", state.missingRows, false
    );
    checkpoint_json::writeNumber(
        &output, "invalidRows", state.invalidRows, false
    );
    checkpoint_json::writeBool(&output, "complete", state.complete, true);
    output << "}\n";
    output.close();
    if (!output)
    {
        return false;
    }
    removeFileIfExists(path);
    return std::rename(tempPath.c_str(), path.c_str()) == 0;
}

} // namespace data
} // namespace geopulse
