#include "colors.h"
#include "datafile_manager.h"
#include "table.h"
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#ifndef DATABASE_H
#define DATABASE_H

class Database {
  private:
    int database_id = 0;
    int new_table_id = 0;
    std::map<std::string, std::unique_ptr<Table>> tables;
    DatafileManager dfm = DatafileManager("database.db");

  public:
    Database(int new_id) {
        this->database_id = new_id;
        std::cout << "Database id: " << this->database_id << std::endl;
        Page temp_page{};
        this->dfm.read_page(1, temp_page);
        std::cout << "saved data : " << temp_page.data << std::endl;
    };

    void add_table(std::string name = "", std::vector<std::pair<std::string, std::string>> data = {});

    void remove_table(std::string table_name);

    void list_tables();

    std::vector<Register> select(std::string table_name, std::vector<std::string> &columns);

    void insert(std::string table_name, std::vector<std::string> &columns, std::vector<std::string> &values);
};
#endif
