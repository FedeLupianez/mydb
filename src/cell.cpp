#include "../include/cell.h"

void Cell::clear() {
    if (type == Type::STRING) {
        string.clear();
        string.shrink_to_fit();
    }
    type = Type::NONE;
}

std::string Cell::get_as_string() {
    if (type == Type::INT) return std::to_string(integer);
    if (type == Type::FLOAT) return std::to_string(real);
    if (type == Type::STRING) return string;
    return "";
}

void Cell::assign(int value) {
    type = Type::INT;
    integer = value;
    string.clear();
}

void Cell::assign(float value) {
    type = Type::FLOAT;
    real = value;
    string.clear();
}

void Cell::assign(std::string value) {
    type = Type::STRING;
    string = std::move(value);
}
