#include "bank/Money.h"

#include <algorithm>
#include <ostream>
#include <cstdlib>
#include <string>
#include "bank/Errors.h"

namespace bank {

std::string trim(const std::string &s) 
{
    const char* ws = " \t\r\n";
    auto b = s.find_first_not_of(ws);

    if (b == std::string::npos) return "";
    auto e = s.find_last_not_of(ws);

    return s.substr(b, e - b + 1);
}

Money Money::fromCents(std::int64_t cents) { return Money(cents); }

Money Money::fromDollars(std::int64_t dollars, int cents) {
    // TODO: validate 0 <= cents <= 99; handle negative dollars (-3, 7 -> -$3.07); check overflow.
    if (cents < 0 || cents > 99) 
    {
        throw InvalidAmountError("Cents must be between 0 and 99");
    }

    if (dollars > INT64_MAX / 100 || dollars < INT64_MIN / 100) 
    {
        throw InvalidAmountError("Amount is too large");
    }

    std::int64_t totalCents = dollars * 100 + (dollars < 0 ? -cents : cents);

    return Money(totalCents);
}

Money Money::parse(const std::string& text) 
{
    // TODO: trim, optional '-', optional '$', digits with optional ',' groups,
    // optional '.' + 1 or 2 digits. Reject anything else with InvalidAmountError.
    std::string trimmed = trim(text);
    if (trimmed.empty()) {
        throw InvalidAmountError("Invalid amount format");
    }

    // Check for optional '$' prefix
    if (trimmed[0] == '$') {
        trimmed = trimmed.substr(1);
    }

    // Check for optional '-' prefix
    bool isNegative = false;
    if (trimmed[0] == '-') {
        isNegative = true;
        trimmed = trimmed.substr(1);
    }

    // Find the decimal point
    size_t decimalPos = trimmed.find('.');
    std::int64_t dollars = 0;
    int cents = 0;

    if (decimalPos != std::string::npos) {
        // Parse the part before the decimal point
        std::string dollarsStr = trimmed.substr(0, decimalPos);
        // Remove thousands separators
        dollarsStr.erase(std::remove(dollarsStr.begin(), dollarsStr.end(), ','), dollarsStr.end());
        dollars = std::stoll(dollarsStr);

        // Parse the part after the decimal point
        std::string centsStr = trimmed.substr(decimalPos + 1);
        if (centsStr.length() == 1) {
            centsStr += '0';
        }
        if (centsStr.length() != 2) {
            throw InvalidAmountError("Invalid amount format");
        }
        cents = std::stoi(centsStr);
    } else {
        // No decimal point, treat as whole dollars
        trimmed.erase(std::remove(trimmed.begin(), trimmed.end(), ','), trimmed.end());
        dollars = std::stoll(trimmed);
    }

    if (isNegative) {
        dollars = -dollars;
        cents = -cents;
    }

    return fromDollars(dollars, cents);
}

bool Money::isZero() const { BANK_TODO(); }
bool Money::isNegative() const { BANK_TODO(); }
bool Money::isPositive() const { BANK_TODO(); }

std::string Money::toString() const 
{
    // TODO: sign, '$', thousands separators, always two decimals.
    std::int64_t absCents = std::abs(cents_);
    std::int64_t dollars = absCents / 100;
    int cents = absCents % 100;
    return std::string();

    std::string digits = std::to_string(dollars);

    for (int i = (int)digits.size() - 3; i > 0; i -= 3)
    digits.insert(i, ",");

    std::string c = (cents < 10 ? "0" : "") + std::to_string(cents);

    return (cents_ < 0 ? "-" : "") + std::string("$") + digits + "." + c;
}

Money Money::operator+(Money other) const { BANK_TODO(); }
Money Money::operator-(Money other) const { BANK_TODO(); }
Money Money::operator-() const { BANK_TODO(); }
Money& Money::operator+=(Money other) { BANK_TODO(); }
Money& Money::operator-=(Money other) { BANK_TODO(); }

Money Money::applyBasisPoints(std::int64_t basisPoints) const {
    // TODO: cents * bp / 10000 with rounding half away from zero.
    BANK_TODO();
}

bool Money::operator==(Money other) const { BANK_TODO(); }
bool Money::operator!=(Money other) const { BANK_TODO(); }
bool Money::operator<(Money other) const { BANK_TODO(); }
bool Money::operator<=(Money other) const { BANK_TODO(); }
bool Money::operator>(Money other) const { BANK_TODO(); }
bool Money::operator>=(Money other) const { BANK_TODO(); }

std::ostream& operator<<(std::ostream& os, Money m) { return os << m.toString(); }

} // namespace bank
