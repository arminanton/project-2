/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CheckpointHash.cpp
 * Purpose:    Implements a stable header signature for checkpoint validation.
 * ============================================================================
 */

#include "data/Checkpoint.h"

#include <sstream>

namespace geopulse
{
namespace data
{

/**
 * Computes a tiny FNV-1a hash for stable, deterministic checkpoint matching.
 *
 * The value is not cryptographic. It is only a compact identity for the header
 * row so a checkpoint from a different CSV schema is not reused by mistake.
 */
std::string stableSignature(const std::string& text)
{
    std::uint64_t hash = 1469598103934665603ULL;
    for (std::size_t index = 0; index < text.size(); ++index)
    {
        hash ^= static_cast<unsigned char>(text[index]);
        hash *= 1099511628211ULL;
    }
    std::ostringstream output;
    output << std::hex << hash;
    return output.str();
}

} // namespace data
} // namespace geopulse
