#include "bank/SimDate.h"

#include <ostream>
#include <stdexcept>

#include "bank/Errors.h"

namespace bank {

SimDate::SimDate(int year, int month, int day) {
    // TODO: validate month 1..12, day 1..daysInMonth; throw std::invalid_argument.
    BANK_TODO();
}

SimDate SimDate::parse(const std::string& isoText) { BANK_TODO(); }

int SimDate::year() const { return year_; }
int SimDate::month() const { return month_; }
int SimDate::day() const { return day_; }

bool SimDate::isLeapYear(int year) { BANK_TODO(); }
int SimDate::daysInMonth(int year, int month) { BANK_TODO(); }

SimDate SimDate::addDays(int n) const { BANK_TODO(); }
SimDate SimDate::addMonths(int n) const { BANK_TODO(); }
SimDate SimDate::firstOfNextMonth() const { BANK_TODO(); }
bool SimDate::isLastDayOfMonth() const { BANK_TODO(); }
int SimDate::daysUntil(const SimDate& other) const { BANK_TODO(); }

std::string SimDate::toString() const { BANK_TODO(); }

bool SimDate::operator==(const SimDate& o) const { BANK_TODO(); }
bool SimDate::operator!=(const SimDate& o) const { BANK_TODO(); }
bool SimDate::operator<(const SimDate& o) const { BANK_TODO(); }
bool SimDate::operator<=(const SimDate& o) const { BANK_TODO(); }

std::ostream& operator<<(std::ostream& os, const SimDate& d) { return os << d.toString(); }

void SimClock::advanceDays(int n) { today_ = today_.addDays(n); }

} // namespace bank
