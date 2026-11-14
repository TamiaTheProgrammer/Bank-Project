#pragma once
#include "bank/Account.h"

namespace bank {

// Everyday account: overdraft allowed up to a limit, daily withdrawal cap,
// monthly maintenance fee waived above a minimum balance.
struct CheckingSettings {
    Money overdraftLimit      = Money::fromDollars(200);
    Money overdraftFee        = Money::fromDollars(35);  // per withdrawal that goes negative
    Money dailyWithdrawalLimit= Money::fromDollars(1000);
    Money monthlyFee          = Money::fromDollars(5);
    Money feeWaiverMinBalance = Money::fromDollars(1500);
};

class CheckingAccount : public Account {
public:
    using Settings = CheckingSettings;

    CheckingAccount(AccountId id, CustomerId owner, std::string nickname,
                    SimDate opened, Settings settings = {});

    AccountType type() const override { return AccountType::Checking; }
    Money availableToWithdraw() const override;

    const Transaction& withdraw(Money amount, const SimDate& date,
                                const std::string& description, TxId txId) override;

    std::vector<Transaction> applyMonthEnd(const SimDate& date, TxId& nextTxId) override;
    void recordDailyBalance() override;

    std::string serializeSettings() const override;
    void loadSettings(const std::string& kv) override;

    const Settings& settings() const { return settings_; }
    Money withdrawnOn(const SimDate& date) const; // sum of withdrawals that day

private:
    Settings settings_;
    Money lowestBalanceThisMonth_; // for fee waiver
};

} // namespace bank
