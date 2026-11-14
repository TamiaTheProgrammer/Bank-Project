#pragma once
// Exception hierarchy for the bank. The UI catches BankError and shows what().
#include <stdexcept>
#include <string>

namespace bank {

// Marks a function you still need to implement. Remove each use as you go.
#define BANK_TODO() throw std::logic_error(std::string("TODO: implement ") + __func__)

class BankError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidAmountError    : public BankError { public: using BankError::BankError; };
class InsufficientFundsError: public BankError { public: using BankError::BankError; };
class AccountNotFoundError  : public BankError { public: using BankError::BankError; };
class CustomerNotFoundError : public BankError { public: using BankError::BankError; };
class AccountFrozenError    : public BankError { public: using BankError::BankError; };
class AccountClosedError    : public BankError { public: using BankError::BankError; };
class LimitExceededError    : public BankError { public: using BankError::BankError; };
class AuthenticationError   : public BankError { public: using BankError::BankError; };
class AccountLockedError    : public BankError { public: using BankError::BankError; };
class PersistenceError      : public BankError { public: using BankError::BankError; };

} // namespace bank
