/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Version.h
 * Purpose: Gives the application version to the command line interface.
 * ============================================================================
 */

#ifndef GEOPULSE_CORE_VERSION_H
#define GEOPULSE_CORE_VERSION_H

#include "core/Constants.h"

namespace geopulse
{
namespace core
{

/** @brief Returns the semantic project version string. */
inline const char* getVersion() { return constants::kVersion; }

} // namespace core
} // namespace geopulse

#endif
