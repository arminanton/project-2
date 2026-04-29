/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CsvReader.cpp
 * Purpose:    Opens CSV files and reads parsed header/data rows.
 * ============================================================================
 */

#include "data/CsvReader.h"

#include <fstream>

namespace geopulse
{
namespace data
{

/** @brief Opens the CSV and records its size for progress reporting. */
bool CsvReader::open(const std::string& path)
{
    _input.open(path.c_str(), std::ios::in | std::ios::binary);
    if (!_input.is_open())
    {
        return false;
    }
    _input.seekg(0, std::ios::end);
    _fileSize = static_cast<std::uint64_t>(_input.tellg());
    _input.seekg(0, std::ios::beg);
    _byteOffset = 0;
    _rowNumber = 0;
    return true;
}

/** @brief Reads the header but does not count it as a data row. */
bool CsvReader::readHeader(CsvRow* header)
{
    std::string record;
    if (header == nullptr || !_readRecord(&record))
    {
        return false;
    }
    *header = parseCsvRecord(record);
    _rowNumber = 0;
    return true;
}

/** @brief Reads the next logical data row. */
bool CsvReader::readRow(CsvRow* row)
{
    std::string record;
    if (row == nullptr || !_readRecord(&record))
    {
        return false;
    }
    *row = parseCsvRecord(record);
    ++_rowNumber;
    return true;
}

/** @brief Seeks to a previously checkpointed byte position. */
bool CsvReader::seekTo(std::uint64_t byteOffset, std::uint64_t rowNumber)
{
    if (!_input.is_open())
    {
        return false;
    }
    _input.clear();
    _input.seekg(static_cast<std::streamoff>(byteOffset), std::ios::beg);
    _byteOffset = byteOffset;
    _rowNumber = rowNumber;
    return !_input.fail();
}

} // namespace data
} // namespace geopulse
