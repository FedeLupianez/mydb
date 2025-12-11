#include "register.h"

Register::Register(std::vector<Cell> new_cells, int new_id) {
    cells = new_cells;
    register_id = new_id;
}

void Register::remove_cell(int index) {
    cells.erase(cells.begin() + index);
}

Cell &Register::operator[](int index) {
    return cells[index];
}

void Register::print() {
    for (Cell &cell : cells) {
        std::cout << cell.get_as_string() << " ";
    }
    std::cout << std::endl;
}
