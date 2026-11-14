#pragma once
// PIN hashing. This is a learning project: a salted, iterated FNV/simple hash is
// fine here, but say so in your README — real banks use bcrypt/argon2.
#include <string>

namespace bank::security {

std::string generateSalt(std::size_t length = 16);           // random hex chars
std::string hashPin(const std::string& pin, const std::string& salt, int iterations = 10000);
bool verifyPin(const std::string& pin, const std::string& salt, const std::string& expectedHash);
bool isValidPinFormat(const std::string& pin);               // 4–6 digits, not all same, not 1234

// Compares in constant time so timing doesn't leak how many chars matched.
bool constantTimeEquals(const std::string& a, const std::string& b);

} // namespace bank::security
