#include "bank/ConsoleUI.h"

#include <iostream>
#include <utility>

#include "bank/Errors.h"

namespace bank {

ConsoleUI::ConsoleUI(Bank& bank, std::string dataDir) : bank_(bank), dataDir_(std::move(dataDir)) {}

void ConsoleUI::run() {
    // TODO: loop welcomeMenu() until quit. Wrap each action in
    // try { ... } catch (const BankError& e) { printError(e.what()); }
    BANK_TODO();
}

void ConsoleUI::welcomeMenu() { BANK_TODO(); }
void ConsoleUI::registerCustomer() { BANK_TODO(); }
void ConsoleUI::loginFlow() { BANK_TODO(); }
void ConsoleUI::customerMenu(CustomerId who) { BANK_TODO(); }
void ConsoleUI::showAccounts(CustomerId who) { BANK_TODO(); }
void ConsoleUI::openAccountFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::depositFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::withdrawFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::transferFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::historyFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::statementFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::profileFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::closeAccountFlow(CustomerId who) { BANK_TODO(); }
void ConsoleUI::adminMenu() { BANK_TODO(); }
void ConsoleUI::advanceTimeFlow() { BANK_TODO(); }

std::optional<std::string> ConsoleUI::promptLine(const std::string& label) {
    // TODO: print label, std::getline; return nullopt on EOF or "q".
    BANK_TODO();
}
std::optional<int> ConsoleUI::promptInt(const std::string& label, int min, int max) { BANK_TODO(); }
std::optional<Money> ConsoleUI::promptMoney(const std::string& label) { BANK_TODO(); }
std::optional<std::string> ConsoleUI::promptPin(const std::string& label) { BANK_TODO(); }
std::optional<AccountId> ConsoleUI::pickAccount(CustomerId who, const std::string& label) { BANK_TODO(); }
bool ConsoleUI::confirm(const std::string& question) { BANK_TODO(); }

void ConsoleUI::printHeader(const std::string& title) const { BANK_TODO(); }
void ConsoleUI::printError(const std::string& msg) const { std::cout << "  ! " << msg << "\n"; }
void ConsoleUI::printSuccess(const std::string& msg) const { BANK_TODO(); }
void ConsoleUI::pause() const { BANK_TODO(); }

void ConsoleUI::autosave() {
    // TODO: bank_.saveTo(dataDir_); catch PersistenceError and warn, don't crash.
    BANK_TODO();
}

} // namespace bank
