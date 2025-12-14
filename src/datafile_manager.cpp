#include "../include/datafile_manager.h"
#include <cstddef>
#include <cstring>

DatafileManager::DatafileManager(std::string path) : file(path, std::ios::in | std::ios::out | std::ios::binary) {
    if (!file.is_open()) {
        file.clear();
        file.open(path, std::ios::out | std::ios::binary);
        file.close();
        file.open(path, std::ios::in | std::ios::out | std::ios::binary);
    }
}

bool DatafileManager::read_page(size_t page_id, Page &page) {
    file.seekg(page_id * page_size, std::ios::beg);
    if (!file.good()) return (false);
    file.read(page.data, page_size);
    if (file.bad()) {
        return false;
    }
    file.clear();
    return true;
}

size_t DatafileManager::get_writed_size(size_t page_id) {
    Page temp_page{};
    if (!read_page(page_id, temp_page)) {
        return 0;
    }
    for (int i = page_size - 1; i >= 0; --i) {
        if (temp_page.data[i] != 0) {
            return i + 1;
        }
    }
    return 0;
}

bool DatafileManager::write_page(size_t page_id, Page &page, size_t size) {
    // Me aseguro de no sobreescribir datos
    size_t actual_page_size = get_writed_size(page_id);
    file.seekp((page_id * page_size) + actual_page_size, std::ios::beg);
    if (!file.good()) return (false);
    file.write(page.data, size);

    actual_size += size;
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
    size_t table_size = 0;

    // Nombre
    std::string name = table.get_name();
    memcpy(page.data, name.c_str(), name.size() * sizeof(char));
    table_size += name.size() * sizeof(char);

    // Headers
    std::vector<std::pair<std::string, std::string>> headers = table.get_headers();
    std::string headers_text = "(";

    for (int i = 0; i < headers.size() - 1; i++) {
        std::string end = (i == headers.size() - 2) ? "" : ",";
        headers_text += headers[i].first + ":" + headers[i].second + end;
    }
    headers_text += ")";

    memcpy(page.data + table_size, headers_text.c_str(), headers_text.size() * sizeof(char));
    table_size += headers_text.size() * sizeof(char);

    write_page(tables_page, page, table_size);
    std::cout << "saved table " << name << " of " << table_size << " bytes" << std::endl;
}

void DatafileManager::save(Register &reg) {
    Page page{};
    size_t actual_reg_size = 0;
    for (Cell &cell : reg.get_cells()) {
        memcpy(page.data + actual_reg_size, cell.get_as_string().c_str(), cell.get_as_string().size());
        actual_reg_size += cell.get_as_string().size();
    }
    write_page(actual_page, page, actual_reg_size);
    std::cout << "saved register of " << actual_reg_size << std::endl;
}
