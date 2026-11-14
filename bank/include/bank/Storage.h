#pragma once
// Saves and loads the whole bank as plain text files in one directory:
//   bank.meta        name, today, ID counters, format version
//   customers.csv    one row per customer
//   accounts.csv     one row per account (+ settings column)
//   transactions.csv one row per transaction
// Writes go to *.tmp then rename, so a crash never leaves half a file.
#include <string>
#include <vector>

namespace bank {

class Bank;

namespace storage {

constexpr int kFormatVersion = 1;

void save(const Bank& bank, const std::string& directory);
Bank load(const std::string& directory);   // throws PersistenceError with file + line

// CSV helpers (handle commas, quotes and newlines inside fields).
std::string escapeCsv(const std::string& field);
std::vector<std::string> splitCsvLine(const std::string& line);

// Writes text to path via a temp file + rename.
void writeFileAtomically(const std::string& path, const std::string& contents);

} // namespace storage
} // namespace bank
