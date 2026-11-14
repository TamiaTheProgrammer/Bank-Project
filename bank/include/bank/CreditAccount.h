#pragma once
#include "bank/Account.h"

namespace bank {

// Credit line. Balance is <= 0 (negative = amount owed). "Withdraw" = spend/
// cash advance; "deposit" = payment. Interest on owed balance, minimum payment
// due each month, late fee if missed.
struct CreditSettings {
    Money creditLimit          = Money::fromDollars(2000);
    std::int64_t aprBp         = 2499;                    // 24.99%
    std::int64_t minPaymentBp  = 300;                     // 3% of owed
    Money minPaymentFloor      = Money::fromDollars(25);
    Money lateFee              = Money::fromDollars(30);
    int graceDays              = 21;                      // payment due N days after statement
};

class CreditAccount : public Account {
public:
    using Settings = CreditSettings;

    CreditAccount(AccountId id, CustomerId owner, std::string nickname,
                  SimDate opened, Settings settings = {});

    AccountType type() const override { return AccountType::Credit; }
    Money availableToWithdraw() const override; // creditLimit + balance

    Money amountOwed() const;                   // -balance, never negative
    const Transaction& deposit(Money amount, const SimDate& date,
                               const std::string& description, TxId txId) override; // payment, can't overpay past 0 (or decide)
    const Transaction& withdraw(Money amount, const SimDate& date,
                                const std::string& description, TxId txId) override;

    std::vector<Transaction> applyMonthEnd(const SimDate& date, TxId& nextTxId) override;
    void recordDailyBalance() override;

    // Bank calls this each day; charges late fee when the due date passes unpaid.
    std::vector<Transaction> checkPaymentDue(const SimDate& today, TxId& nextTxId);

    std::string serializeSettings() const override;
    void loadSettings(const std::string& kv) override;

    const Settings& settings() const { return settings_; }
    Money minimumPaymentDue() const { return minimumDue_; }
    SimDate paymentDueDate() const { return dueDate_; }
    Money paidSinceStatement() const { return paidSinceStatement_; }

private:
    Settings settings_;
    Money minimumDue_;
    SimDate dueDate_;
    bool hasOpenStatement_ = false;
    Money paidSinceStatement_;
    std::int64_t dailyOwedSumCents_ = 0;
    int daysRecorded_ = 0;
};

} // namespace bank
