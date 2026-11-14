#pragma once
// Money stored as a whole number of cents. Never use double for balances.
#include <cstdint>
#include <iosfwd>
#include <string>

namespace bank {

class Money {
public:
    constexpr Money() = default;

    // Factories
    static Money fromCents(std::int64_t cents);
    static Money fromDollars(std::int64_t dollars, int cents = 0);
    // Parses "12", "12.5", "12.50", "-3.07", "$1,234.56". Throws InvalidAmountError.
    static Money parse(const std::string& text);

    std::int64_t cents() const { return cents_; }
    bool isZero() const;
    bool isNegative() const;
    bool isPositive() const;

    // "$1,234.56" or "-$12.00"
    std::string toString() const;

    // Arithmetic (check for int64 overflow and throw)
    Money operator+(Money other) const;
    Money operator-(Money other) const;
    Money operator-() const;
    Money& operator+=(Money other);
    Money& operator-=(Money other);

    // Multiply by a rate given in basis points (1 bp = 0.01%). Rounds half away from zero.
    // e.g. $100.00 at 250 bp -> $2.50
    Money applyBasisPoints(std::int64_t basisPoints) const;

    // Comparison
    bool operator==(Money other) const;
    bool operator!=(Money other) const;
    bool operator<(Money other) const;
    bool operator<=(Money other) const;
    bool operator>(Money other) const;
    bool operator>=(Money other) const;

private:
    explicit constexpr Money(std::int64_t cents) : cents_(cents) {}
    std::int64_t cents_ = 0;
};

std::ostream& operator<<(std::ostream& os, Money m);

} // namespace bank
