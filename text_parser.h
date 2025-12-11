#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

namespace TextParser {

inline std::string lower(std::string string) {
    for (char c : string) {
        c = std::tolower(c);
    }
    return string;
}

inline std::vector<std::string> split(std::string command, std::string delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    int left = 0;
    int right = 0;

    while ((right = command.find(delimiter, left)) != std::string::npos) {
        token = command.substr(left, right - left);
        if (token == "") continue;
        tokens.push_back(token);
        left = right + delimiter.length();
    }
    token = command.substr(left);
    tokens.push_back(token);

    return tokens;
}

inline bool is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

inline std::string replace(std::string string, std::string to_replace, std::string replacement) {
    size_t pos = 0;
    while ((pos = string.find(to_replace, pos)) != std::string::npos) {

        string.replace(pos, to_replace.length(), replacement);
        pos += replacement.length();
    }
    return string;
}

inline std::string erase(std::string string, std::string to_erase) {
    auto pos = string.find(to_erase);
    if (pos == std::string::npos) return string;
    return string.erase(pos, to_erase.length());
}

inline std::string erase_parenthesis(std::string command) {
    std::string first = erase(command, "(");
    return erase(first, ")");
}

inline std::string strip(std::string string) {
    return replace(string, " ", "");
}

inline std::string clean(std::string input) {
    return TextParser::erase_parenthesis(TextParser::strip(input));
}

inline std::vector<std::string> tokenize(std::string input, char delimiter = ' ') {
    input = TextParser::lower(input);
    std::vector<std::string> tokens;
    std::string actual_token;
    bool parentesis_active = false;

    for (char c : input) {
        if (c == '(') {
            parentesis_active = true;
        }
        if (c == ')') {
            parentesis_active = false;
            if (actual_token != "") {
                tokens.push_back(actual_token);
                actual_token = "";
            }
        }

        if (c == delimiter && !parentesis_active) {
            tokens.push_back(actual_token);
            actual_token = "";
        } else {
            actual_token += c;
        }
    }
    if (actual_token != "") tokens.push_back(actual_token);
    return tokens;
}

}; // namespace TextParser

#endif
