#pragma once
// The service layer. The only class the UI talks to. Owns all customers,
// accounts, the clock and ID counters.
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "bank/Account.h"
#include "bank/CheckingAccount.h"
#include "bank/CreditAccount.h"
#include "bank/Customer.h"
#include "bank/SavingsAccount.h"
#include "bank/SimDate.h"

namespace bank {

struct Statement {
    AccountId accountId = 0;
    SimDate from, to;
    Money openingBalance, closingBalance;
    Money totalIn, totalOut, interest, fees;
    std::vector<Transaction> lines;
};

struct BankSummary {
    std::size_t customers = 0, accounts = 0, transactions = 0;
    Money totalDeposits;   // sum of positive balances
    Money totalOwed;       // sum of negative balances (credit + overdraft)
};

class Bank {
public:
    explicit Bank(std::string name = "C++ Community Bank", SimDate start = SimDate{});

    const std::string& name() const { return name_; }
    const SimDate& today() const { return clock_.today(); }

    // --- customers ---
    CustomerId createCustomer(const std::string& fullName, const std::string& email,
                              const std::string& phone, const std::string& pin);
    Customer& customer(CustomerId id);                 // throws CustomerNotFoundError
    const Customer& customer(CustomerId id) const;
    std::vector<const Customer*> findCustomersByName(const std::string& partial) const;
    Customer& login(CustomerId id, const std::string& pin); // authenticate wrapper

    // --- accounts ---
    AccountId openChecking(CustomerId owner, const std::string& nickname, Money openingDeposit);
    AccountId openSavings(CustomerId owner, const std::string& nickname, Money openingDeposit);
    AccountId openCredit(CustomerId owner, const std::string& nickname, Money creditLimit);
    void closeAccount(CustomerId requester, AccountId id);  // must be owner, balance 0
    Account& account(AccountId id);                    // throws AccountNotFoundError
    const Account& account(AccountId id) const;
    std::vector<const Account*> accountsOf(CustomerId owner) const;

    // --- money movement (all check that requester owns the source account) ---
    TxId deposit(CustomerId requester, AccountId to, Money amount, const std::string& memo = "");
    TxId withdraw(CustomerId requester, AccountId from, Money amount, const std::string& memo = "");
    // Atomic: either both sides post or neither does.
    TxId transfer(CustomerId requester, AccountId from, AccountId to, Money amount,
                  const std::string& memo = "");
    // Admin: posts an opposite transaction and marks the original reversed.
    TxId reverseTransaction(AccountId accountId, TxId txId, const std::string& reason);

    // --- time ---
    // Moves the clock forward one day at a time: records daily balances, checks
    // credit due dates, runs month-end on the last day of each month.
    void advanceDays(int days);
    void advanceToEndOfMonth();

    // --- reporting ---
    Statement statement(AccountId id, const SimDate& from, const SimDate& to) const;
    std::string formatStatement(const Statement& s) const;
    bool exportStatementCsv(const Statement& s, const std::string& path) const;
    Money netWorth(CustomerId owner) const;
    BankSummary summary() const;

    // --- persistence ---
    void saveTo(const std::string& directory) const;
    static Bank loadFrom(const std::string& directory);

    // --- for Storage only ---
    TxId nextTxId() { return nextTxId_++; }
    void restoreCounters(CustomerId nextCustomer, AccountId nextAccount, TxId nextTx);
    void restoreClock(const SimDate& d) { clock_.set(d); }
    void adoptCustomer(std::unique_ptr<Customer> c);
    void adoptAccount(std::unique_ptr<Account> a);
    CustomerId peekNextCustomerId() const { return nextCustomerId_; }
    AccountId peekNextAccountId() const { return nextAccountId_; }
    TxId peekNextTxId() const { return nextTxId_; }
    std::vector<const Customer*> allCustomers() const;
    std::vector<const Account*> allAccounts() const;

private:
    void requireOwner(CustomerId requester, const Account& a) const;
    void runMonthEnd();

    std::string name_;
    SimClock clock_;
    std::map<CustomerId, std::unique_ptr<Customer>> customers_;
    std::map<AccountId, std::unique_ptr<Account>> accounts_;
    CustomerId nextCustomerId_ = 1001;
    AccountId nextAccountId_ = 100000001;
    TxId nextTxId_ = 1;
};

} // namespace bank
