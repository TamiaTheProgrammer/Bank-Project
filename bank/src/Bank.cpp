#include "bank/Bank.h"

#include <utility>

#include "bank/Errors.h"
#include "bank/Storage.h"

namespace bank {

Bank::Bank(std::string name, SimDate start) : name_(std::move(name)), clock_(start) {}

// ---------- customers ----------
CustomerId Bank::createCustomer(const std::string& fullName, const std::string& email,
                                const std::string& phone, const std::string& pin) {
    // TODO: make_unique<Customer>(nextCustomerId_++, ...), setPin, insert, return id.
    BANK_TODO();
}
Customer& Bank::customer(CustomerId id) { BANK_TODO(); }
const Customer& Bank::customer(CustomerId id) const { BANK_TODO(); }
std::vector<const Customer*> Bank::findCustomersByName(const std::string& partial) const {
    // TODO: case-insensitive substring match.
    BANK_TODO();
}
Customer& Bank::login(CustomerId id, const std::string& pin) { BANK_TODO(); }

// ---------- accounts ----------
AccountId Bank::openChecking(CustomerId owner, const std::string& nickname, Money openingDeposit) {
    // TODO: check customer exists; create; post OpeningDeposit if > 0; link to customer.
    BANK_TODO();
}
AccountId Bank::openSavings(CustomerId owner, const std::string& nickname, Money openingDeposit) {
    // TODO: same, but require openingDeposit >= minimumBalance.
    BANK_TODO();
}
AccountId Bank::openCredit(CustomerId owner, const std::string& nickname, Money creditLimit) {
    BANK_TODO();
}
void Bank::closeAccount(CustomerId requester, AccountId id) { BANK_TODO(); }
Account& Bank::account(AccountId id) { BANK_TODO(); }
const Account& Bank::account(AccountId id) const { BANK_TODO(); }
std::vector<const Account*> Bank::accountsOf(CustomerId owner) const { BANK_TODO(); }

// ---------- money movement ----------
TxId Bank::deposit(CustomerId requester, AccountId to, Money amount, const std::string& memo) {
    BANK_TODO();
}
TxId Bank::withdraw(CustomerId requester, AccountId from, Money amount, const std::string& memo) {
    BANK_TODO();
}
TxId Bank::transfer(CustomerId requester, AccountId from, AccountId to, Money amount,
                    const std::string& memo) {
    // TODO: validate EVERYTHING first (owner, from != to, both active, amount > 0,
    // funds/limits). Only then post TransferOut and TransferIn. Nothing can throw
    // between the two posts, so the transfer is atomic.
    BANK_TODO();
}
TxId Bank::reverseTransaction(AccountId accountId, TxId txId, const std::string& reason) {
    // TODO: find tx; refuse if already reversed or is itself a Reversal; post the
    // opposite amount; mark original reversed. For transfers, reverse both sides.
    BANK_TODO();
}

// ---------- time ----------
void Bank::advanceDays(int days) {
    // TODO: for each day: every account recordDailyBalance(); credit accounts
    // checkPaymentDue(); if today is last day of month -> runMonthEnd(); clock_.advanceDays(1).
    BANK_TODO();
}
void Bank::advanceToEndOfMonth() { BANK_TODO(); }
void Bank::runMonthEnd() { BANK_TODO(); }

// ---------- reporting ----------
Statement Bank::statement(AccountId id, const SimDate& from, const SimDate& to) const {
    BANK_TODO();
}
std::string Bank::formatStatement(const Statement& s) const { BANK_TODO(); }
bool Bank::exportStatementCsv(const Statement& s, const std::string& path) const { BANK_TODO(); }
Money Bank::netWorth(CustomerId owner) const { BANK_TODO(); }
BankSummary Bank::summary() const { BANK_TODO(); }

// ---------- persistence ----------
void Bank::saveTo(const std::string& directory) const { storage::save(*this, directory); }
Bank Bank::loadFrom(const std::string& directory) { return storage::load(directory); }

void Bank::restoreCounters(CustomerId nextCustomer, AccountId nextAccount, TxId nextTx) {
    nextCustomerId_ = nextCustomer;
    nextAccountId_ = nextAccount;
    nextTxId_ = nextTx;
}
void Bank::adoptCustomer(std::unique_ptr<Customer> c) { BANK_TODO(); }
void Bank::adoptAccount(std::unique_ptr<Account> a) { BANK_TODO(); }
std::vector<const Customer*> Bank::allCustomers() const { BANK_TODO(); }
std::vector<const Account*> Bank::allAccounts() const { BANK_TODO(); }

void Bank::requireOwner(CustomerId requester, const Account& a) const { BANK_TODO(); }

} // namespace bank
