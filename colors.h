#include <iostream>
#include <string>
#ifndef COLORS_H
#define COLORS_H

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

inline void print_error(std::string message) {
    std::cout << RED << message << RESET << std::endl;
}

inline std::string green(std::string message) {
    return GREEN + message + RESET;
}

inline std::string red(std::string message) {
    return RED + message + RESET;
}

inline std::string yellow(std::string message) {
    return YELLOW + message + RESET;
}

inline std::string blue(std::string message) {
    return BLUE + message + RESET;
}
#endif
