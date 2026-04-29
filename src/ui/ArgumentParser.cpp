/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    ArgumentParser.cpp
 * Purpose:    Implements command-line validation.
 * ============================================================================
 */

#include "ui/ArgumentParser.h"

namespace geopulse
{
namespace ui
{

/** @brief Converts argv into a structured options object. */
CliOptions parseArguments(int argc, char* argv[])
{
    CliOptions options;
    for (int index = 1; index < argc; ++index)
    {
        const std::string argument = argv[index];
        if (argument == "--help" || argument == "-h")
        {
            options.showHelp = true;
        }
        else if (argument == "--version")
        {
            options.showVersion = true;
        }
        else if (argument == "--benchmark")
        {
            options.benchmark = true;
        }
        else if (argument == "--resume")
        {
            options.resume = true;
        }
        else if (argument == "--interactive")
        {
            options.interactive = true;
        }
        else if (argument == "--data" && index + 1 < argc)
        {
            options.dataPath = argv[++index];
        }
        else
        {
            options.valid = false;
            if (argument == "--data")
            {
                options.errorMessage = "--data requires a CSV file path";
            }
            else
            {
                options.errorMessage = "unknown argument: " + argument;
            }
            return options;
        }
    }
    return options;
}

} // namespace ui
} // namespace geopulse
