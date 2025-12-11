#include <iostream>
#ifndef COMMANDS_H
#define COMMANDS_H

namespace commands {
constexpr std::string_view EXIT = "exit";
constexpr std::string_view CREATE = "create";
constexpr std::string_view LIST = "list";
constexpr std::string_view DROP = "drop";
constexpr std::string_view CLEAR = "clear";
constexpr std::string_view INSERT = "insert";
constexpr std::string_view SELECT = "select";

}; // namespace commands

#endif
