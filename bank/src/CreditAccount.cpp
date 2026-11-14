#include "bank/CreditAccount.h"

#include <utility>

#include "bank/Errors.h"

namespace bank {

CreditAccount::CreditAccount(AccountId id, CustomerId owner, std::string nickname,
                             SimDate opened, Settings settings)
    : Account(id, owner, std::move(nickname), opened), settings_(settings) {}

Money CreditAccount::availableToWithdraw() const { BANK_TODO(); }
Money CreditAccount::amountOwed() const { BANK_TODO(); }

const Transaction& CreditAccount::deposit(Money amount, const SimDate& date,
                                          const std::string& description, TxId txId) {
    // TODO: a payment. Reject if it would take balance above 0 (or allow a credit
    // balance — your call, write it down). Add to paidSinceStatement_.
    BANK_TODO();
}

const Transaction& CreditAccount::withdraw(Money amount, const SimDate& date,
                                           const std::string& description, TxId txId) {
    // TODO: amount <= availableToWithdraw() else LimitExceededError.
    BANK_TODO();
}

void CreditAccount::recordDailyBalance() { BANK_TODO(); }

std::vector<Transaction> CreditAccount::applyMonthEnd(const SimDate& date, TxId& nextTxId) {
    // TODO: interest on average daily owed; new statement:
    // minimumDue_ = max(floor, owed * minPaymentBp) capped at owed;
    // dueDate_ = date + graceDays; paidSinceStatement_ = 0.
    BANK_TODO();
}

std::vector<Transaction> CreditAccount::checkPaymentDue(const SimDate& today, TxId& nextTxId) {
    // TODO: if hasOpenStatement_ and today > dueDate_ and paid < minimumDue_:
    // post lateFee once, close the statement.
    BANK_TODO();
}

std::string CreditAccount::serializeSettings() const { BANK_TODO(); }
void CreditAccount::loadSettings(const std::string& kv) { BANK_TODO(); }

} // namespace bank
