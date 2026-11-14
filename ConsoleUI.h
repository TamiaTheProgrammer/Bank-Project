#pragma once
// One immutable line in an account's history.
#include <cstdint>
#include <string>

#include "bank/Money.h"
#include "bank/SimDate.h"

namespace bank {

using TxId = std::uint64_t;
using AccountId = std::uint64_t;

enum class TxType {
    Deposit,
    Withdrawal,
    TransferIn,
    TransferOut,
    Interest,        // interest earned (savings) or charged (credit)
    Fee,
    Reversal,
    OpeningDeposit,
};

std::string toString(TxType t);
TxType txTypeFromString(const std::string& s); // throws on unknown

struct Transaction {
    TxId id = 0;
    SimDate date;
    TxType type = TxType::Deposit;
    Money amount;             // signed: + money in, - money out
    Money balanceAfter;
    std::string description;
    AccountId counterparty = 0; // other account for transfers, else 0
    TxId reverses = 0;          // for Reversal: id of the reversed tx, else 0
    bool reversed = false;      // set true once something reverses it
};

// Formats one row for statements: date, type, amount, balance, description.
std::string formatRow(const Transaction& tx);

} // namespace bank
