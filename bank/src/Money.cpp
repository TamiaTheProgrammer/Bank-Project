#include "bank/Money.h"

#include <ostream>

#include "bank/Errors.h"

namespace bank {

Money Money::fromCents(std::int64_t cents) { return Money(cents); }

Money Money::fromDollars(std::int64_t dollars, int cents) {
    // TODO: validate 0 <= cents <= 99; handle negative dollars (-3, 7 -> -$3.07); check overflow.
    BANK_TODO();
}

Money Money::parse(const std::string& text) {
    // TODO: trim, optional '-', optional '$', digits with optional ',' groups,
    // optional '.' + 1 or 2 digits. Reject anything else with InvalidAmountError.
    BANK_TODO();
}

bool Money::isZero() const { BANK_TODO(); }
bool Money::isNegative() const { BANK_TODO(); }
bool Money::isPositive() const { BANK_TODO(); }

std::string Money::toString() const {
    // TODO: sign, '$', thousands separators, always two decimals.
    BANK_TODO();
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
