#include "bank/Transaction.h"

#include "bank/Errors.h"

namespace bank {

std::string toString(TxType t) {
    // TODO: switch over every TxType -> "Deposit", "Withdrawal", ...
    BANK_TODO();
}

TxType txTypeFromString(const std::string& s) { BANK_TODO(); }

std::string formatRow(const Transaction& tx) {
    // TODO: fixed-width columns, e.g.
    // 2026-03-04  Withdrawal     -$40.00     $1,210.55   ATM cash
    BANK_TODO();
}

} // namespace bank
