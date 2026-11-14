#include "bank/CheckingAccount.h"

#include <utility>

#include "bank/Errors.h"

namespace bank {

CheckingAccount::CheckingAccount(AccountId id, CustomerId owner, std::string nickname,
                                 SimDate opened, Settings settings)
    : Account(id, owner, std::move(nickname), opened), settings_(settings) {}

Money CheckingAccount::availableToWithdraw() const {
    // TODO: balance + overdraftLimit, but 0 if frozen/closed.
    BANK_TODO();
}

const Transaction& CheckingAccount::withdraw(Money amount, const SimDate& date,
                                             const std::string& description, TxId txId) {
    // TODO:
    //  1. withdrawnOn(date) + amount <= dailyWithdrawalLimit else LimitExceededError
    //  2. Account::withdraw(...)
    //  3. if the balance went from >= 0 to < 0, post an overdraft Fee
    //     (needs its own TxId: think about how — see the guide, "Transactions").
    BANK_TODO();
}

Money CheckingAccount::withdrawnOn(const SimDate& date) const { BANK_TODO(); }

void CheckingAccount::recordDailyBalance() {
    // TODO: track lowestBalanceThisMonth_.
    BANK_TODO();
}

std::vector<Transaction> CheckingAccount::applyMonthEnd(const SimDate& date, TxId& nextTxId) {
    // TODO: charge monthlyFee unless lowestBalanceThisMonth_ >= feeWaiverMinBalance;
    // reset monthly trackers.
    BANK_TODO();
}

std::string CheckingAccount::serializeSettings() const { BANK_TODO(); }
void CheckingAccount::loadSettings(const std::string& kv) { BANK_TODO(); }

} // namespace bank
