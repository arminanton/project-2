/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    Menu.h
 * Purpose:    Declares the optional interactive query menu.
 * ============================================================================
 */

#ifndef GEOPULSE_UI_MENU_H
#define GEOPULSE_UI_MENU_H

#include <iosfwd>

#include "data/DataSet.h"

namespace geopulse
{
namespace ui
{

/** @brief Small menu for manually trying queries after the dataset loads. */
class Menu
{
public:
    /** @brief Stores non-owning input/output stream pointers. */
    Menu(std::istream* input, std::ostream* output);

    /** @brief Builds indexes and runs the menu loop. */
    int run(const data::DataSet& dataSet) const;

private:
    std::istream* _input;  // User command input stream.
    std::ostream* _output; // User-visible output stream.
};

} // namespace ui
} // namespace geopulse

#endif
