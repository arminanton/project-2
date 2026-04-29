/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    ResultComparatorTest.cpp
 * Purpose:    Tests normalized comparisons for benchmark correctness checks.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include "query/ResultComparator.h"

TEST_CASE("ResultComparator ignores result ordering", "[query]")
{
    geopulse::core::RecordIdList left;
    left.push_back(3);
    left.push_back(1);
    geopulse::core::RecordIdList right;
    right.push_back(1);
    right.push_back(3);
    REQUIRE(geopulse::query::sameRecordSet(left, right));
}

TEST_CASE("ResultComparator detects different nearest answers", "[query]")
{
    geopulse::core::NearestResult left;
    geopulse::core::NearestResult right;
    left.found = true;
    right.found = true;
    left.recordIndex = 1;
    right.recordIndex = 2;
    REQUIRE_FALSE(geopulse::query::sameNearest(left, right));
}
