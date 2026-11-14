#include "bank/Storage.h"

#include "bank/Bank.h"
#include "bank/Errors.h"

namespace bank::storage {

void save(const Bank& bank, const std::string& directory) {
    // TODO: create directory (std::filesystem::create_directories), then write
    // bank.meta, customers.csv, accounts.csv, transactions.csv atomically.
    BANK_TODO();
}

Bank load(const std::string& directory) {
    // TODO: read bank.meta (check version), customers, accounts (construct right
    // subclass from type column, loadSettings, restoreState), then transactions
    // (append to history WITHOUT changing balance — or rebuild balance and
    // compare to the stored one as a corruption check). Restore counters + clock.
    BANK_TODO();
}

std::string escapeCsv(const std::string& field) { BANK_TODO(); }
std::vector<std::string> splitCsvLine(const std::string& line) { BANK_TODO(); }
void writeFileAtomically(const std::string& path, const std::string& contents) { BANK_TODO(); }

} // namespace bank::storage
