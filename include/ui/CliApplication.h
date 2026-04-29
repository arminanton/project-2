/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CliApplication.h
 * Purpose:    Declares the command-line application entry facade.
 * ============================================================================
 */

#ifndef GEOPULSE_UI_CLI_APPLICATION_H
#define GEOPULSE_UI_CLI_APPLICATION_H

namespace geopulse
{
namespace ui
{

/** @brief Owns command dispatch, keeping main.cpp intentionally tiny. */
class CliApplication
{
public:
    /** @brief Parses arguments, loads data, and selects the requested mode. */
    int run(int argc, char* argv[]) const;
};

} // namespace ui
} // namespace geopulse

#endif
