#include "register.h"
#include "table.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#ifndef DATAFILE_MANAGER_H
#define DATAFILE_MANAGER_H

constexpr size_t page_size = 4096;

struct Page {
    char data[page_size];
};

class DatafileManager {
  private:
    std::fstream file;
    size_t actual_page = 2;
    size_t actual_size = 0;

  public:
    DatafileManager(std::string path);

    bool read_page(size_t page_id, Page &page);
    bool write_page(size_t page_id, Page &page);
    size_t new_page();

    void save(Table &table);
    void save(Register &reg);
};

#endif
