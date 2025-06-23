#include "utils.h"
#include <iostream>
#include <windows.h>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printSuccess(const std::string& message) {
    std::cout << GREEN << BOLD << "[✓] " << message << RESET << std::endl;
}

void printError(const std::string& message) {
    std::cerr << RED << BOLD << "[✗] " << message << RESET << std::endl;
}

void printInfo(const std::string& message) {
    std::cout << BLUE << BOLD << "[i] " << RESET << BLUE << message << RESET << std::endl;
}

void printTitle(const std::string& message) {
    std::cout << ORANGE << BOLD << message << RESET << std::endl;
}

void printSubTitle(const std::string& message) {
    std::cout << CYAN << BOLD << message << RESET << std::endl;
}

void printWarning(const std::string& message) {
    std::cout << ORANGE << BOLD << "[⚠] " << RESET << ORANGE << message << RESET << std::endl;
}

void askForInput(const std::string& message) {
    std::cout << BLUE << BOLD << "[i] " << RESET << BLUE << message << RESET;
    std::cout.flush();
}