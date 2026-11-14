#pragma once
// Abstract base for every account type.
#include <cstdint>
#include <string>
#include <vector>

#include "bank/Money.h"
#include "bank/SimDate.h"
#include "bank/Transaction.h"

namespace bank {

using CustomerId = std::uint64_t;

enum class AccountType { Checking, Savings, Credit };
enum class AccountStatus { Active, Frozen, Closed };

std::string toString(AccountType t);
std::string toString(AccountStatus s);
AccountType accountTypeFromString(const std::string& s);
AccountStatus accountStatusFromString(const std::string& s);

class Account {
public:
    Account(AccountId id, CustomerId owner, std::string nickname, SimDate opened);
    virtual ~Account() = default;

    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;

    // --- identity ---
    AccountId id() const { return id_; }
    CustomerId owner() const { return owner_; }
    const std::string& nickname() const { return nickname_; }
    void setNickname(std::string name);
    SimDate openedOn() const { return opened_; }
    virtual AccountType type() const = 0;

    // --- state ---
    Money balance() const { return balance_; }
    AccountStatus status() const { return status_; }
    void freeze();
    void unfreeze();
    // Only allowed when balance is exactly zero. Throws otherwise.
    void close();

    // Money you could take out right now (balance + overdraft, or credit available).
    virtual Money availableToWithdraw() const = 0;

    // --- money movement (Bank calls these; they record a Transaction) ---
    // Each validates: amount > 0, account active, type-specific limits.
    virtual const Transaction& deposit(Money amount, const SimDate& date,
                                       const std::string& description, TxId txId);
    virtual const Transaction& withdraw(Money amount, const SimDate& date,
                                        const std::string& description, TxId txId);

    // Records a transaction of any type without rule checks (fees, interest,
    // transfers, reversals, loading from disk). Updates balance.
    const Transaction& post(TxType type, Money signedAmount, const SimDate& date,
                            const std::string& description, TxId txId,
                            AccountId counterparty = 0, TxId reverses = 0);

    // --- history ---
    const std::vector<Transaction>& history() const { return history_; }
    std::vector<Transaction> historyBetween(const SimDate& from, const SimDate& to) const;
    Transaction* findTransaction(TxId id);

    // --- month-end hooks (Bank calls on the last day of each month) ---
    // Return the transactions created (interest, fees). Default: none.
    virtual std::vector<Transaction> applyMonthEnd(const SimDate& date, TxId& nextTxId);
    // Called once per simulated day for daily-balance interest. Default: no-op.
    virtual void recordDailyBalance();

    // --- persistence helpers ---
    // Type-specific settings as "key=value;key=value" (Storage writes this out).
    virtual std::string serializeSettings() const = 0;
    virtual void loadSettings(const std::string& kv) = 0;
    void restoreState(Money balance, AccountStatus status); // used by Storage only

protected:
    void requireActive() const;           // throws AccountFrozenError / AccountClosedError
    static void requirePositive(Money m);  // throws InvalidAmountError

    Money balance_;
    AccountStatus status_ = AccountStatus::Active;
    std::vector<Transaction> history_;

private:
    AccountId id_;
    CustomerId owner_;
    std::string nickname_;
    SimDate opened_;
};

} // namespace bank
