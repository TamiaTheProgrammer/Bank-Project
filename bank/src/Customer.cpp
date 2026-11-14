#include "bank/Customer.h"

#include <utility>

#include "bank/Errors.h"
#include "bank/Security.h"

namespace bank {

Customer::Customer(CustomerId id, std::string fullName, std::string email,
                   std::string phone, SimDate joined)
    : id_(id), joined_(joined) {
    // TODO: call the validating setters instead of assigning directly.
    fullName_ = std::move(fullName);
    email_ = std::move(email);
    phone_ = std::move(phone);
}

void Customer::setFullName(std::string name) { BANK_TODO(); }
void Customer::setEmail(std::string email) { BANK_TODO(); }
void Customer::setPhone(std::string phone) { BANK_TODO(); }

void Customer::setPin(const std::string& newPin) { BANK_TODO(); }

void Customer::authenticate(const std::string& pin) {
    // TODO: locked -> AccountLockedError. verify; on fail ++failedAttempts_,
    // lock at maxFailedAttempts, throw AuthenticationError ("2 attempts left").
    // On success reset failedAttempts_.
    BANK_TODO();
}

void Customer::unlock() { BANK_TODO(); }
void Customer::addAccount(AccountId id) { BANK_TODO(); }
void Customer::removeAccount(AccountId id) { BANK_TODO(); }

void Customer::restoreAuth(std::string salt, std::string hash, int failed, bool locked) {
    pinSalt_ = std::move(salt);
    pinHash_ = std::move(hash);
    failedAttempts_ = failed;
    locked_ = locked;
}

} // namespace bank
