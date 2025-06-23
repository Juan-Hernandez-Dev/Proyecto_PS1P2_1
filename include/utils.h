#ifndef UTILS_H
#define UTILS_H

#include <string>

// Reset all attributes
#define RESET   "\033[0m"
// Text colors
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[37m"

// Custom colors
#define ORANGE  "\033[38;2;255;165;0m"  // RGB(255,165,0)
#define BLUE    "\033[38;2;55;231;255m"  // RGB(0,119,190)
#define CYAN    "\033[38;2;255;205;160m"

// Background colors
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

// Text styles
#define BOLD      "\033[1m"
#define DIM       "\033[2m"
#define UNDERLINE "\033[4m"
#define BLINK     "\033[5m"
#define REVERSE   "\033[7m"

// Function to clear the console
void clearScreen();

// Colored output functions
void printSuccess(const std::string& message);
void printError(const std::string& message);
void printInfo(const std::string& message);
void printTitle(const std::string& message);
void printSubTitle(const std::string& message);
void printWarning(const std::string& message);
void askForInput(const std::string& message);

#endif // UTILS_H