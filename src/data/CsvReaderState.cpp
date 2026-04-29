/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CsvReaderState.cpp
 * Purpose:    Implements small CsvReader state accessors.
 * ============================================================================
 */

#include "data/CsvReader.h"

namespace geopulse
{
namespace data
{

/** @brief Creates a closed reader. */
CsvReader::CsvReader() = default;

std::uint64_t CsvReader::byteOffset() const { return _byteOffset; }

std::uint64_t CsvReader::rowNumber() const { return _rowNumber; }

std::uint64_t CsvReader::fileSize() const { return _fileSize; }

bool CsvReader::isOpen() const { return _input.is_open(); }

} // namespace data
} // namespace geopulse
