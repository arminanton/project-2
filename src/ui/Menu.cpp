/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    Menu.cpp
 * Purpose:    Implements the optional interactive query menu.
 * ============================================================================
 */

#include "ui/Menu.h"

#include <iomanip>
#include <iostream>

#include "index/QuadTree.h"
#include "query/QueryEngine.h"

namespace geopulse
{
namespace ui
{
namespace
{

/** @brief Reads one coordinate pair from the menu input stream. */
bool readCoordinate(std::istream* input, double* latitude, double* longitude)
{
    return input != nullptr && latitude != nullptr && longitude != nullptr &&
           (*input >> *latitude >> *longitude);
}

} // namespace

/** @brief Stores streams so tests can use string streams if needed. */
Menu::Menu(std::istream* input, std::ostream* output) :
    _input(input),
    _output(output)
{
}

/** @brief Runs a compact menu backed by a Quadtree for quick demonstrations. */
int Menu::run(const data::DataSet& dataSet) const
{
    index::QuadTree tree;
    tree.build(dataSet.points);
    query::QueryEngine engine(&tree);
    *_output << "Interactive menu\n";
    *_output << "1 nearest\n2 radius\n3 range\n4 exit\n";
    int choice = 0;
    while (_input != nullptr && *_input >> choice)
    {
        if (choice == 4)
        {
            return 0;
        }
        double latitude = 0.0;
        double longitude = 0.0;
        if (!readCoordinate(_input, &latitude, &longitude))
        {
            *_output << "invalid coordinate input\n";
            return 2;
        }
        if (choice == 1)
        {
            const core::NearestResult result =
                engine.nearest(latitude, longitude);
            *_output << "nearest record index: " << result.recordIndex << '\n';
        }
        else if (choice == 2)
        {
            double radius = 0.0;
            *_input >> radius;
            *_output << "radius matches: "
                     << engine.radius(latitude, longitude, radius).size()
                     << '\n';
        }
        else
        {
            double maxLatitude = 0.0;
            double maxLongitude = 0.0;
            *_input >> maxLatitude >> maxLongitude;
            *_output
                << "range matches: "
                << engine.range(latitude, maxLatitude, longitude, maxLongitude)
                       .size()
                << '\n';
        }
    }
    return 0;
}

} // namespace ui
} // namespace geopulse
