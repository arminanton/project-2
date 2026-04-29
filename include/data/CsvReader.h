/* ============================================================================
 * Name:    Guilherme Armin Da Silva Anton
 * UFID:    2641-9801
 * Project: COP3530 Project 2 - GeoPulse
 * File:    CsvReader.h
 * Purpose: Reads CSV records, including quoted newlines, from a file.
 * ============================================================================
 */

#ifndef GEOPULSE_DATA_CSV_READER_H
#define GEOPULSE_DATA_CSV_READER_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace geopulse
{
namespace data
{

/** @brief A CSV row is a list of already-unquoted field strings. */
using CsvRow = std::vector<std::string>;

/**
 * @brief Parses one complete CSV record into individual fields.
 *
 * @param record A raw string representing a single, unparsed CSV line.
 * @return A vector of unquoted strings extracted from the record.
 */
CsvRow parseCsvRecord(const std::string& record);

/**
 * @brief Streams CSV records without loading the full file into memory.
 *
 * The reader counts logical CSV records, not physical lines. This distinction
 * matters because quoted fields may legally contain newline characters.
 */
class CsvReader
{
public:
    /** @brief Creates a reader with no open file. */
    CsvReader();

    /**
     * @brief Opens a CSV file and records its size for progress output.
     * @param path The absolute or relative path to the CSV file.
     * @return True if the file was successfully opened, false otherwise.
     */
    bool open(const std::string& path);

    /**
     * @brief Reads and parses the header row.
     * @param header Pointer to a CsvRow to store the parsed field names.
     * @return True if a header was read, false if the file is empty.
     */
    bool readHeader(CsvRow* header);

    /**
     * @brief Reads and parses the next logical data row.
     * @param row Pointer to a CsvRow to store the parsed fields.
     * @return True if a row was successfully read, false on EOF or error.
     */
    bool readRow(CsvRow* row);

    /**
     * @brief Moves to a previously checkpointed byte offset and row.
     * @param byteOffset The physical position in the file stream.
     * @param rowNumber The logical number of rows read up to this point.
     * @return True if the seek succeeded, false if invalid.
     */
    bool seekTo(std::uint64_t byteOffset, std::uint64_t rowNumber);

    /** @brief Returns the next safe input byte offset. */
    std::uint64_t byteOffset() const;

    /** @brief Returns the number of logical data rows already read. */
    std::uint64_t rowNumber() const;

    /** @brief Returns the opened file size in bytes. */
    std::uint64_t fileSize() const;

    /** @brief Returns true when the stream is currently open. */
    bool isOpen() const;

private:
    // Reads a single raw string representing one CSV record from the stream.
    bool _readRecord(std::string* record);

    std::ifstream _input;          // Owns the file stream by RAII
    std::uint64_t _byteOffset = 0; // Offset after last record
    std::uint64_t _rowNumber = 0;  // Logical rows read
    std::uint64_t _fileSize = 0;   // Size captured at open time
};

} // namespace data
} // namespace geopulse

#endif
