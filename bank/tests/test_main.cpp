// A tiny test runner so you need no libraries. Swap for GoogleTest/Catch2 later
// if you like. Add a TEST(...) for every case listed in the guide's Testing section.
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "bank/Bank.h"
#include "bank/Errors.h"
#include "bank/Money.h"
#include "bank/SimDate.h"

namespace {
struct TestCase { std::string name; std::function<void()> fn; };
std::vector<TestCase>& registry() { static std::vector<TestCase> r; return r; }
struct Registrar { Registrar(const char* n, std::function<void()> f) { registry().push_back({n, std::move(f)}); } };
struct Failure { std::string msg; };
} // namespace

#define TEST(name) \
    static void name(); \
    static Registrar reg_##name(#name, name); \
    static void name()

#define CHECK(cond) \
    do { if (!(cond)) throw Failure{std::string(__FILE__) + ":" + std::to_string(__LINE__) + "  CHECK(" #cond ")"}; } while (0)

#define CHECK_THROWS_AS(expr, Ex) \
    do { bool caught = false; try { (void)(expr); } catch (const Ex&) { caught = true; } catch (const std::logic_error&) { throw; } catch (...) {} \
         if (!caught) throw Failure{std::string(__FILE__) + ":" + std::to_string(__LINE__) + "  expected " #Ex}; } while (0)

using namespace bank;

// ---------------- Money ----------------
TEST(money_parse_basic) {
    CHECK(Money::parse("12.34").cents() == 1234);
    CHECK(Money::parse("$1,000").cents() == 100000);
    CHECK(Money::parse("-0.07").cents() == -7);
}
TEST(money_parse_rejects_garbage) {
    CHECK_THROWS_AS(Money::parse("12.345"), InvalidAmountError);
    CHECK_THROWS_AS(Money::parse("abc"), InvalidAmountError);
    CHECK_THROWS_AS(Money::parse(""), InvalidAmountError);
}
TEST(money_to_string) {
    CHECK(Money::fromCents(123456).toString() == "$1,234.56");
    CHECK(Money::fromCents(-5).toString() == "-$0.05");
}

// ---------------- SimDate ----------------
TEST(date_leap_years) {
    CHECK(SimDate::isLeapYear(2024));
    CHECK(!SimDate::isLeapYear(2100));
    CHECK(SimDate::isLeapYear(2000));
}
TEST(date_add_months_clamps) {
    CHECK(SimDate(2026, 1, 31).addMonths(1) == SimDate(2026, 2, 28));
}

// TODO: add the rest from the guide (accounts, transfers, interest, persistence...).

int main() {
    int passed = 0, failed = 0, todo = 0;
    for (auto& t : registry()) {
        try {
            t.fn();
            ++passed;
            std::cout << "[ PASS ] " << t.name << "\n";
        } catch (const Failure& f) {
            ++failed;
            std::cout << "[ FAIL ] " << t.name << "\n         " << f.msg << "\n";
        } catch (const std::logic_error& e) {
            ++todo; // BANK_TODO() not implemented yet
            std::cout << "[ TODO ] " << t.name << "  (" << e.what() << ")\n";
        } catch (const std::exception& e) {
            ++failed;
            std::cout << "[ FAIL ] " << t.name << "  threw: " << e.what() << "\n";
        }
    }
    std::cout << "\n" << passed << " passed, " << failed << " failed, " << todo << " not implemented\n";
    return failed == 0 ? 0 : 1;
}
