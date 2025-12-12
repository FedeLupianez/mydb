#include "../include/datafile_manager.h"
#include <cstring>

DatafileManager::DatafileManager(std::string path) {
    file = std::fstream(path, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        file.open("database.db", std::ios::out | std::ios::binary);
        file.close();
        file.open("database.db", std::ios::in | std::ios::out | std::ios::binary);
    }
}

bool DatafileManager::read_page(size_t page_id, Page &page) {
    file.seekg(page_id * page_size, std::ios::beg);
    if (!file.good()) return (false);
    file.read(page.data, page_size);
    return file.good();
}

bool DatafileManager::write_page(size_t page_id, Page &page) {
    file.seekp(page_id * page_size, std::ios::beg);
    if (!file.good()) return (false);
    file.write(page.data, page_size);

    actual_size += sizeof(page.data);
    if (actual_size > page_size) {
        actual_page++;
        actual_size = 0;
    }

    file.flush();
    return file.good();
}

size_t DatafileManager::new_page() {
    file.seekp(0, std::ios::end);
    size_t page_id = file.tellp() / page_size;
    Page empty{};
    file.write(empty.data, page_size);
    file.flush();
    return page_id;
}

void DatafileManager::save(Table &table) {
    Page page{};
    memcpy(page.data, &table, sizeof(table));
    write_page(actual_page, page);
    std::cout << "saved table of " << sizeof(table) << std::endl;
}

void DatafileManager::save(Register &reg) {
    Page page{};
    memcpy(page.data, &reg, sizeof(reg));
    write_page(actual_page, page);
    std::cout << "saved register of " << sizeof(reg) << std::endl;
}
