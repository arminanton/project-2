/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Usage.cpp
 * Purpose:    Provides the command-line help text.
 * ============================================================================
 */

#include "ui/ArgumentParser.h"

#include <sstream>

namespace geopulse
{
namespace ui
{

/** Returns command documentation shown by --help and validation errors. */
std::string usageText()
{
    std::ostringstream output;
    output << "GeoPulse spatial benchmark CLI\n";
    output << "Usage:\n";
    output << "  geopulse --help\n";
    output << "  geopulse --version\n";
    output << "  geopulse --data <csv>\n";
    output << "  geopulse --data <csv> --benchmark\n";
    output << "  geopulse --data <csv> --benchmark --resume\n";
    output << "  geopulse --data <csv> --interactive\n";
    output << "Options:\n";
    output << "  --data <csv>   Load the collision CSV file.\n";
    output << "  --benchmark    Compare Linear Scan, KD-tree, and "
              "Quadtree.\n";
    output << "  --resume       Enable recovery while loading.\n";
    output << "  --interactive  Open a small query menu after loading.\n";
    output << "  --version      Print the application version.\n";
    output << "  --help         Print this help text.\n";
    return output.str();
}

} // namespace ui
} // namespace geopulse
