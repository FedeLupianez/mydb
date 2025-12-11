#ifndef CELL_H
#define CELL_H

#include "types.h"
#include <stdexcept>
#include <string>

struct Cell {
    Type type;

    union {
        int integer;
        double real;
    };

    std::string string;

    // Métodos públicos
    void clear();

    template <typename T> void set(const T &value) {
        clear();
        assign(value);
    }

    template <typename T> T get_value() {
        if (type == Type::INT) return integer;
        if (type == Type::FLOAT) return real;
        if (type == Type::STRING) return string;
        throw std::runtime_error("Tipo inválido");
    }

    std::string get_as_string();

  private:
    void assign(int value);
    void assign(float value);
    void assign(std::string value);
};

#endif
