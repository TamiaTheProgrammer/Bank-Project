#include "bank/Account.h"

#include <utility>

#include "bank/Errors.h"

namespace bank {

std::string toString(AccountType t) { BANK_TODO(); }
std::string toString(AccountStatus s) { BANK_TODO(); }
AccountType accountTypeFromString(const std::string& s) { BANK_TODO(); }
AccountStatus accountStatusFromString(const std::string& s) { BANK_TODO(); }

Account::Account(AccountId id, CustomerId owner, std::string nickname, SimDate opened)
    : id_(id), owner_(owner), nickname_(std::move(nickname)), opened_(opened) {}

void Account::setNickname(std::string name) { BANK_TODO(); }
void Account::freeze() { BANK_TODO(); }
void Account::unfreeze() { BANK_TODO(); }
void Account::close() { BANK_TODO(); }

const Transaction& Account::deposit(Money amount, const SimDate& date,
                                    const std::string& description, TxId txId) {
    // TODO: requireActive(), requirePositive(amount), then post(TxType::Deposit, ...).
    BANK_TODO();
}

const Transaction& Account::withdraw(Money amount, const SimDate& date,
                                     const std::string& description, TxId txId) {
    // TODO: requireActive(), requirePositive(amount),
    // amount <= availableToWithdraw() else InsufficientFundsError, then post(...).
    BANK_TODO();
}

const Transaction& Account::post(TxType type, Money signedAmount, const SimDate& date,
                                 const std::string& description, TxId txId,
                                 AccountId counterparty, TxId reverses) {
    // TODO: balance_ += signedAmount; build Transaction; push_back; return history_.back().
    BANK_TODO();
}

std::vector<Transaction> Account::historyBetween(const SimDate& from, const SimDate& to) const {
    BANK_TODO();
}

Transaction* Account::findTransaction(TxId id) { BANK_TODO(); }

std::vector<Transaction> Account::applyMonthEnd(const SimDate&, TxId&) { return {}; }
void Account::recordDailyBalance() {}

void Account::restoreState(Money balance, AccountStatus status) {
    balance_ = balance;
    status_ = status;
}

void Account::requireActive() const { BANK_TODO(); }
void Account::requirePositive(Money m) { BANK_TODO(); }

} // namespace bank
