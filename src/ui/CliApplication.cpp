/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CliApplication.cpp
 * Purpose:    Implements top-level command dispatch.
 * ============================================================================
 */

#include "ui/CliApplication.h"

#include <iostream>
#include <stdexcept>

#include "app/GeoPulseFacade.h"
#include "data/DataLoader.h"
#include "ui/ArgumentParser.h"
#include "ui/Menu.h"

namespace geopulse
{
namespace ui
{

/** @brief Runs one command-line request and returns a process exit code. */
int CliApplication::run(int argc, char* argv[]) const
{
    const CliOptions options = parseArguments(argc, argv);
    app::GeoPulseFacade facade;
    if (!options.valid)
    {
        std::cerr << "GeoPulse error: " << options.errorMessage << "\n\n";
        std::cerr << usageText();
        return 2;
    }
    if (options.showVersion)
    {
        std::cout << facade.versionText();
        return 0;
    }
    if (options.showHelp || options.dataPath.empty())
    {
        std::cout << usageText();
        return 0;
    }
    try
    {
        data::DataLoaderOptions loadOptions;
        loadOptions.enableRecovery = options.resume;
        loadOptions.reuseCompletedCache = options.resume;
        data::DataLoader loader;
        const data::DataSet dataSet =
            loader.load(options.dataPath, loadOptions);
        std::cout << facade.summaryText(dataSet);
        if (options.benchmark)
        {
            benchmark::BenchmarkOptions benchmarkOptions;
            std::cout << '\n'
                      << facade.benchmarkText(dataSet, benchmarkOptions);
        }
        if (options.interactive)
        {
            Menu menu(&std::cin, &std::cout);
            return menu.run(dataSet);
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << "GeoPulse error: " << exception.what() << '\n';
        return 1;
    }
    return 0;
}

} // namespace ui
} // namespace geopulse
