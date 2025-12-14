#include "../include/table.h"

void Table::add_header(std::pair<std::string, std::string> header) {
    headers.push_back(header);
}

void Table::add_register(Register new_register) {
    new_register.set_id(this->new_register_id);
    new_register_id++;
    registers.push_back(new_register);
}

void Table::remove_register(int index) {
    registers.erase(registers.begin() + index);
}

Register *Table::get_register(int index) {
    return &this->registers[index];
}

int *Table::get_indexes(std::vector<std::string> &columns) {
    int *indexes = new int[columns.size()];
    int last_append = 0;
    for (std::string column : columns) {
        for (int i = 0; i < headers.size(); ++i) {
            if (column == headers[i].first) {
                indexes[last_append] = i;
                last_append++;
            }
        }
    }
    return indexes;
}

std::pair<std::string, std::string> Table::get_header(int index) {
    return headers[index];
}

std::vector<Register> Table::view_cols(std::vector<std::string> &columns) {
    // Obtener los index
    if (columns.size() == 1 && columns[0] == "*") {
        std::cout << "all\n";
        return registers;
    }
    int *indexes = get_indexes(columns);
    std::vector<Register> selected_registers;
    for (Register &reg : registers) {
        Register new_register;
        for (int i = 0; i < columns.size(); i++) {
            int index = indexes[i];
            Cell &cell = reg[index];
            new_register.add_cell(cell);
        }
        selected_registers.push_back(new_register);
    }
    delete indexes;
    return selected_registers;
}

Register &Table::create_register(std::vector<std::string> &columns, std::vector<std::string> &values) {
    Register new_register;
    for (int i = 0; i < columns.size(); i++) {
        Cell new_cell;
        // defino el tipo de la celda
        const std::string column_type = this->headers[i].second;
        if (values[i][0] == '\'' && values[i][values[i].size() - 1] == '\'' && column_type == "string") {
            values[i] = values[i].substr(1, values[i].size() - 2);
            new_cell.set(std::string(values[i]));
        }
        if (column_type == "int") {
            new_cell.set(std::stoi(values[i]));
        }
        if (column_type == "float") {
            new_cell.set(std::stof(values[i]));
        }
        new_register.add_cell(new_cell);
    }
    this->add_register(new_register);
    return this->registers[this->registers.size() - 1];
}
