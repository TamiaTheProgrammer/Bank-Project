#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "bank/Account.h"
#include "bank/SimDate.h"

namespace bank {

class Customer {
public:
    Customer(CustomerId id, std::string fullName, std::string email,
             std::string phone, SimDate joined);

    CustomerId id() const { return id_; }
    const std::string& fullName() const { return fullName_; }
    const std::string& email() const { return email_; }
    const std::string& phone() const { return phone_; }
    SimDate joined() const { return joined_; }

    // Validate before setting (email has one '@' and a '.', phone digits only, name non-empty).
    void setFullName(std::string name);
    void setEmail(std::string email);
    void setPhone(std::string phone);

    // --- authentication ---
    void setPin(const std::string& newPin);          // validates format, salts + hashes
    // Throws AccountLockedError when locked; AuthenticationError on wrong PIN.
    // Locks after maxFailedAttempts consecutive failures.
    void authenticate(const std::string& pin);
    bool isLocked() const { return locked_; }
    void unlock();                                   // admin action
    int failedAttempts() const { return failedAttempts_; }
    static constexpr int maxFailedAttempts = 3;

    // --- accounts owned ---
    const std::vector<AccountId>& accountIds() const { return accountIds_; }
    void addAccount(AccountId id);
    void removeAccount(AccountId id);

    // --- persistence ---
    const std::string& pinSalt() const { return pinSalt_; }
    const std::string& pinHash() const { return pinHash_; }
    void restoreAuth(std::string salt, std::string hash, int failed, bool locked);

private:
    CustomerId id_;
    std::string fullName_, email_, phone_;
    SimDate joined_;
    std::string pinSalt_, pinHash_;
    int failedAttempts_ = 0;
    bool locked_ = false;
    std::vector<AccountId> accountIds_;
};

} // namespace bank
