#include "cell.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#ifndef REGISTER_H
#define REGISTER_H

class Register {
  private:
    std::vector<Cell> cells;
    int register_id = 0;

  public:
    Register(std::vector<Cell> new_cells = {}, int new_id = 0);

    void add_cell(Cell new_cell) {
        this->cells.push_back(new_cell);
    }

    void set_id(int new_id) {
        this->register_id = new_id;
    }

    std::vector<Cell> get_cells() {
        return cells;
    }

    void remove_cell(int index);
    Cell &operator[](int index);
    void print();
    ~Register() {}
};

#endif
