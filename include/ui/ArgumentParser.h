/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    ArgumentParser.h
 * Purpose:    Declares command-line option parsing.
 * ============================================================================
 */

#ifndef GEOPULSE_UI_ARGUMENT_PARSER_H
#define GEOPULSE_UI_ARGUMENT_PARSER_H

#include <string>

namespace geopulse
{
namespace ui
{

/** @brief Parsed command-line options plus validation feedback. */
struct CliOptions
{
    bool showHelp = false;    // Print usage and exit.
    bool showVersion = false; // Print version and exit.
    bool benchmark = false;   // Run benchmark after loading.
    bool resume = false;      // Enable checkpoint/cache recovery.
    bool interactive = false; // Open menu after loading.
    bool valid = true;        // False when an argument is rejected.
    std::string dataPath;     // CSV path supplied after --data.
    std::string errorMessage; // Message printed for invalid input.
};

/** @brief Converts argc/argv into validated options. */
CliOptions parseArguments(int argc, char* argv[]);

/** @brief Returns the multi-line command help text. */
std::string usageText();

} // namespace ui
} // namespace geopulse

#endif
