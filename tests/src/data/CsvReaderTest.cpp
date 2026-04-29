/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CsvReaderTest.cpp
 * Purpose:    Tests CSV parsing edge cases before data loading uses them.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include <fstream>

#include "data/CsvReader.h"

TEST_CASE("CSV parser keeps commas inside quoted fields", "[data]")
{
    const geopulse::data::CsvRow row =
        geopulse::data::parseCsvRecord("a,\"b,c\",d\n");
    REQUIRE(row.size() == 3);
    REQUIRE(row[1] == "b,c");
}

TEST_CASE("CSV parser turns doubled quotes into one quote", "[data]")
{
    const geopulse::data::CsvRow row =
        geopulse::data::parseCsvRecord("\"say \"\"hi\"\"\",x\n");
    REQUIRE(row[0] == "say \"hi\"");
    REQUIRE(row[1] == "x");
}

TEST_CASE("CSV reader treats quoted newline as one logical row", "[data]")
{
    const std::string path = "quoted_newline_test.csv";
    std::ofstream output(path.c_str());
    output << "A,B\n";
    output << "\"one\ntwo\",3\n";
    output.close();

    geopulse::data::CsvReader reader;
    REQUIRE(reader.open(path));
    geopulse::data::CsvRow header;
    geopulse::data::CsvRow row;
    REQUIRE(reader.readHeader(&header));
    REQUIRE(reader.readRow(&row));
    REQUIRE(row.size() == 2);
    REQUIRE(row[0] == "one\ntwo");
    REQUIRE(reader.rowNumber() == 1);
}
