/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * COP3530 Project 2 - GeoPulse
 * File:    CheckpointTest.cpp
 * Purpose:    Tests checkpoint serialization and stale-file rejection.
 * ============================================================================
 */

#include "catch_amalgamated.hpp"

#include <fstream>

#include "data/Checkpoint.h"

TEST_CASE("Checkpoint round trip preserves loader state", "[data]")
{
    geopulse::data::CheckpointState state;
    state.sourcePath = "sample.csv";
    state.cachePath = "sample.cache";
    state.headerSignature = "header";
    state.fileSize = 10;
    state.modificationTime = 20;
    state.acceptedRows = 3;
    state.complete = true;

    REQUIRE(
        geopulse::data::writeCheckpoint("checkpoint_round_trip.json", state)
    );
    geopulse::data::CheckpointState read;
    REQUIRE(
        geopulse::data::readCheckpoint("checkpoint_round_trip.json", &read)
    );
    REQUIRE(read.sourcePath == state.sourcePath);
    REQUIRE(read.acceptedRows == 3);
    REQUIRE(read.complete);
}

TEST_CASE("Checkpoint identity detects changed source files", "[data]")
{
    geopulse::data::CheckpointState state;
    state.sourcePath = "old.csv";
    state.headerSignature = "header";
    state.fileSize = 10;
    state.modificationTime = 20;
    const geopulse::data::FileIdentity identity{10, 21, true};
    REQUIRE_FALSE(
        geopulse::data::checkpointMatches(state, "old.csv", identity, "header")
    );
}
