#include <filesystem>
#include <iostream>

#include "bank/Bank.h"
#include "bank/ConsoleUI.h"
#include "bank/Errors.h"

int main(int argc, char** argv) {
    const std::string dataDir = argc > 1 ? argv[1] : "data";

    try {
        bank::Bank b = std::filesystem::exists(dataDir + "/bank.meta")
                           ? bank::Bank::loadFrom(dataDir)
                           : bank::Bank{};
        bank::ConsoleUI ui(b, dataDir);
        ui.run();
        b.saveTo(dataDir);
    } catch (const std::logic_error& e) {
        // BANK_TODO() lands here until you implement things.
        std::cerr << e.what() << "\n";
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
