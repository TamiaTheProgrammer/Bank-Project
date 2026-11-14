#include "bank/Security.h"

#include "bank/Errors.h"

namespace bank::security {

std::string generateSalt(std::size_t length) {
    // TODO: std::random_device + std::uniform_int_distribution over hex digits.
    BANK_TODO();
}

std::string hashPin(const std::string& pin, const std::string& salt, int iterations) {
    // TODO: start h = FNV-1a(salt + pin); repeat `iterations` times h = FNV-1a(h + salt);
    // return as 16 hex chars.
    BANK_TODO();
}

bool verifyPin(const std::string& pin, const std::string& salt, const std::string& expectedHash) {
    BANK_TODO();
}

bool isValidPinFormat(const std::string& pin) { BANK_TODO(); }

bool constantTimeEquals(const std::string& a, const std::string& b) { BANK_TODO(); }

} // namespace bank::security
