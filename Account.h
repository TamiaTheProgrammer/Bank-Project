#pragma once
#include "bank/Account.h"

namespace bank {

// Earns monthly interest on average daily balance. Limited withdrawals per
// month; no overdraft; minimum balance or a fee.
struct SavingsSettings {
    std::int64_t annualRateBp   = 400;                     // 4.00% APR, basis points
    int maxWithdrawalsPerMonth  = 6;
    Money excessWithdrawalFee   = Money::fromDollars(10);
    Money minimumBalance        = Money::fromDollars(100);
    Money belowMinimumFee       = Money::fromDollars(5);
};

class SavingsAccount : public Account {
public:
    using Settings = SavingsSettings;

    SavingsAccount(AccountId id, CustomerId owner, std::string nickname,
                   SimDate opened, Settings settings = {});

    AccountType type() const override { return AccountType::Savings; }
    Money availableToWithdraw() const override;

    const Transaction& withdraw(Money amount, const SimDate& date,
                                const std::string& description, TxId txId) override;

    std::vector<Transaction> applyMonthEnd(const SimDate& date, TxId& nextTxId) override;
    void recordDailyBalance() override;

    std::string serializeSettings() const override;
    void loadSettings(const std::string& kv) override;

    const Settings& settings() const { return settings_; }
    int withdrawalsThisMonth() const { return withdrawalsThisMonth_; }

    // Interest for a month from the average daily balance. Pure function, test it directly.
    static Money monthlyInterest(Money averageDailyBalance, std::int64_t annualRateBp,
                                 int daysInMonth, int daysInYear);

private:
    Settings settings_;
    int withdrawalsThisMonth_ = 0;
    std::int64_t dailyBalanceSumCents_ = 0; // add balance each day
    int daysRecorded_ = 0;
};

} // namespace bank
