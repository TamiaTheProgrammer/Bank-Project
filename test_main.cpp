cmake_minimum_required(VERSION 3.16)
project(BankSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Core banking logic: no I/O to the console lives here.
add_library(bank_core
    src/Money.cpp
    src/SimDate.cpp
    src/Transaction.cpp
    src/Account.cpp
    src/CheckingAccount.cpp
    src/SavingsAccount.cpp
    src/CreditAccount.cpp
    src/Customer.cpp
    src/Security.cpp
    src/Bank.cpp
    src/Storage.cpp
)
target_include_directories(bank_core PUBLIC include)

if(MSVC)
    target_compile_options(bank_core PRIVATE /W4)
else()
    # -Wno-unused-parameter hides noise from the TODO stubs; remove it once you are done.
    target_compile_options(bank_core PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# Console front end.
add_executable(bank src/ConsoleUI.cpp src/main.cpp)
target_link_libraries(bank PRIVATE bank_core)

# Tests (tiny built-in framework, no dependencies).
enable_testing()
add_executable(bank_tests tests/test_main.cpp)
target_link_libraries(bank_tests PRIVATE bank_core)
add_test(NAME bank_tests COMMAND bank_tests)

# Debug builds: cmake -DSANITIZE=ON ..
option(SANITIZE "Build with address and UB sanitizers" OFF)
if(SANITIZE AND NOT MSVC)
    foreach(t bank_core bank bank_tests)
        target_compile_options(${t} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${t} PRIVATE -fsanitize=address,undefined)
    endforeach()
endif()
