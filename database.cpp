#include "database.h"
#include <utility>

void Database::add_table(std::string name, std::vector<std::pair<std::string, std::string>> data) {
    Table new_table = Table(name, data);
    new_table.set_id(new_table_id);
    for (int i = 0; i < data.size(); i++) {
        new_table.add_header(data[i]);
    }
    this->new_table_id++;
    this->tables[name] = std::make_unique<Table>(new_table);

    std::cout << "Created table " << blue(name) << " with :\n";
    for (int i = 0; i < data.size(); i++) {
        std::pair<std::string, std::string> header = new_table.get_header(i);
        std::cout << yellow(header.first) << " type: " << blue(header.second) << std::endl;
    }
}

void Database::remove_table(std::string table_name) {
    this->tables.erase(table_name);
}

void Database::list_tables() {
    for (auto &table : this->tables) {
        std::cout << table.first << std::endl;
    }
}

std::vector<Register> Database::select(std::string table_name, std::vector<std::string> &columns) {
    auto table = this->tables.find(table_name);
    if (table != this->tables.end()) {
        return table->second->view_cols(columns);
    }
    return std::vector<Register>();
}

void Database::insert(std::string table_name, std::vector<std::string> &columns, std::vector<std::string> &values) {
    auto result = this->tables.find(table_name);
    if (result == this->tables.end()) {
        std::cout << red("Table not found") << std::endl;
        return;
    }
    Table *table = result->second.get();
    table->create_register(columns, values);
}
