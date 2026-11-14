#include "bank/SavingsAccount.h"

#include <utility>

#include "bank/Errors.h"

namespace bank {

SavingsAccount::SavingsAccount(AccountId id, CustomerId owner, std::string nickname,
                               SimDate opened, Settings settings)
    : Account(id, owner, std::move(nickname), opened), settings_(settings) {}

Money SavingsAccount::availableToWithdraw() const {
    // TODO: balance (no overdraft), 0 if not active.
    BANK_TODO();
}

const Transaction& SavingsAccount::withdraw(Money amount, const SimDate& date,
                                            const std::string& description, TxId txId) {
    // TODO: Account::withdraw, ++withdrawalsThisMonth_, and if over the max,
    // post excessWithdrawalFee (decide: block instead? document your choice).
    BANK_TODO();
}

void SavingsAccount::recordDailyBalance() {
    // TODO: dailyBalanceSumCents_ += balance; ++daysRecorded_.
    BANK_TODO();
}

std::vector<Transaction> SavingsAccount::applyMonthEnd(const SimDate& date, TxId& nextTxId) {
    // TODO: average = sum / days; interest = monthlyInterest(...); post Interest;
    // below-minimum fee; reset counters.
    BANK_TODO();
}

Money SavingsAccount::monthlyInterest(Money averageDailyBalance, std::int64_t annualRateBp,
                                      int daysInMonth, int daysInYear) {
    // TODO: avg * rate * daysInMonth / daysInYear, rounded to the cent.
    BANK_TODO();
}

std::string SavingsAccount::serializeSettings() const { BANK_TODO(); }
void SavingsAccount::loadSettings(const std::string& kv) { BANK_TODO(); }

} // namespace bank
