#include "text_parser.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#ifndef TABLE_H
#define TABLE_H
#include "register.h"

class Table {
  private:
    int new_register_id = 0;
    int id;
    std::string name;
    std::vector<Register> registers;
    std::vector<std::pair<std::string, std::string>> headers;

  public:
    Table(std::string name = "", std::vector<std::pair<std::string, std::string>> headers = {})
        : name(name), headers(headers) {}

    void set_id(int id) {
        this->id = id;
    }
    void add_header(std::pair<std::string, std::string> header);

    void add_register(Register new_register);

    void remove_register(int index);

    Register *get_register(int index);

    int *get_indexes(std::vector<std::string> &columns);

    std::pair<std::string, std::string> get_header(int index);

    std::vector<Register> view_cols(std::vector<std::string> &columns);

    void create_register(std::vector<std::string> &columns, std::vector<std::string> &values);
};

#endif
