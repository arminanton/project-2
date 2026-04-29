/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CheckpointRead.cpp
 * Purpose:    Loads checkpoint files used by recovery mode.
 * ============================================================================
 */

#include "data/Checkpoint.h"

#include <fstream>
#include <sstream>

#include "data/CheckpointJson.h"

namespace geopulse
{
namespace data
{
namespace
{

/** @brief Reads all text from an input file into a single string. */
std::string readAll(std::ifstream* input)
{
    std::ostringstream text;
    text << input->rdbuf();
    return text.str();
}

} // namespace

/** @brief Reads a checkpoint created by writeCheckpoint. */
bool readCheckpoint(const std::string& path, CheckpointState* state)
{
    if (state == nullptr)
    {
        return false;
    }
    std::ifstream input(path.c_str(), std::ios::in);
    if (!input.is_open())
    {
        return false;
    }
    const std::string json = readAll(&input);
    const bool stringsOk =
        checkpoint_json::readString(json, "sourcePath", &state->sourcePath) &&
        checkpoint_json::readString(json, "cachePath", &state->cachePath) &&
        checkpoint_json::readString(
            json, "headerSignature", &state->headerSignature
        );
    return stringsOk &&
           checkpoint_json::readNumber(json, "fileSize", &state->fileSize) &&
           checkpoint_json::readNumber(
               json, "modificationTime", &state->modificationTime
           ) &&
           checkpoint_json::readNumber(
               json, "lastRowNumber", &state->lastRowNumber
           ) &&
           checkpoint_json::readNumber(
               json, "byteOffset", &state->byteOffset
           ) &&
           checkpoint_json::readNumber(
               json, "acceptedRows", &state->acceptedRows
           ) &&
           checkpoint_json::readNumber(
               json, "excludedRows", &state->excludedRows
           ) &&
           checkpoint_json::readNumber(
               json, "missingRows", &state->missingRows
           ) &&
           checkpoint_json::readNumber(
               json, "invalidRows", &state->invalidRows
           ) &&
           checkpoint_json::readBool(json, "complete", &state->complete);
}

} // namespace data
} // namespace geopulse
