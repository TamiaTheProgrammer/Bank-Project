#pragma once
// Everything that reads std::cin or writes std::cout lives here, nowhere else.
// A future GUI would replace this class and reuse Bank unchanged.
#include <optional>
#include <string>

#include "bank/Bank.h"

namespace bank {

class ConsoleUI {
public:
    ConsoleUI(Bank& bank, std::string dataDir);
    void run(); // main loop until the user quits

private:
    // --- screens ---
    void welcomeMenu();          // login, register, admin, advance time, quit
    void registerCustomer();
    void loginFlow();
    void customerMenu(CustomerId who);
    void showAccounts(CustomerId who);
    void openAccountFlow(CustomerId who);
    void depositFlow(CustomerId who);
    void withdrawFlow(CustomerId who);
    void transferFlow(CustomerId who);
    void historyFlow(CustomerId who);
    void statementFlow(CustomerId who);
    void profileFlow(CustomerId who);   // change name/email/phone/PIN
    void closeAccountFlow(CustomerId who);
    void adminMenu();
    void advanceTimeFlow();

    // --- input helpers (loop until valid or the user types 'q') ---
    std::optional<std::string> promptLine(const std::string& label);
    std::optional<int> promptInt(const std::string& label, int min, int max);
    std::optional<Money> promptMoney(const std::string& label);
    std::optional<std::string> promptPin(const std::string& label);
    std::optional<AccountId> pickAccount(CustomerId who, const std::string& label);
    bool confirm(const std::string& question);

    // --- output helpers ---
    void printHeader(const std::string& title) const;
    void printError(const std::string& msg) const;
    void printSuccess(const std::string& msg) const;
    void pause() const;

    void autosave();

    Bank& bank_;
    std::string dataDir_;
};

} // namespace bank
