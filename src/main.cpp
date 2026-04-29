/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    main.cpp
 * Purpose:    Starts GeoPulse and delegates all behavior to CliApplication.
 * ============================================================================
 */

#include "ui/CliApplication.h"

/** Keeps main tiny so business logic stays testable in normal classes. */
int main(int argc, char* argv[])
{
    const geopulse::ui::CliApplication application;
    return application.run(argc, argv);
}
