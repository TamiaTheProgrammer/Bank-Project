#pragma once
// A calendar date plus a simulated clock the user can move forward.
#include <iosfwd>
#include <string>

namespace bank {

class SimDate {
public:
    SimDate() = default;               // 2026-01-01
    SimDate(int year, int month, int day); // throws std::invalid_argument if invalid

    static SimDate parse(const std::string& isoText); // "YYYY-MM-DD"

    int year() const;
    int month() const;
    int day() const;

    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);

    SimDate addDays(int n) const;
    SimDate addMonths(int n) const;     // clamps day: Jan 31 + 1 month = Feb 28/29
    SimDate firstOfNextMonth() const;
    bool isLastDayOfMonth() const;

    int daysUntil(const SimDate& other) const; // other - this, in days

    std::string toString() const;       // "YYYY-MM-DD"

    bool operator==(const SimDate& o) const;
    bool operator!=(const SimDate& o) const;
    bool operator<(const SimDate& o) const;
    bool operator<=(const SimDate& o) const;

private:
    int year_ = 2026, month_ = 1, day_ = 1;
};

std::ostream& operator<<(std::ostream& os, const SimDate& d);

// The bank's "now". Only Bank advances it.
class SimClock {
public:
    explicit SimClock(SimDate start = SimDate{}) : today_(start) {}
    const SimDate& today() const { return today_; }
    void set(const SimDate& d) { today_ = d; }
    void advanceDays(int n);
private:
    SimDate today_;
};

} // namespace bank
