#include "../include/colors.h"
#include "../include/database.h"
#include "../include/text_parser.h"

#include "../include/commands.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

void process_command(Database &db, std::string input) {
    std::vector<std::string> tokens = TextParser::tokenize(input);
    if (tokens.size() == 0) {
        return;
    }
    const std::string command = tokens[0];
    if (command == commands::CLEAR) {
        system("clear");
        return;
    }

    if (command == commands::CREATE) {
        if (tokens.size() < 5) {
            throw std::runtime_error("Usage: create table <name> <headers>");
        }

        std::string type = tokens[1];
        std::string name = tokens[2];

        std::string headers = TextParser::erase_parenthesis(tokens[3]);

        std::vector<std::string> columns = TextParser::split(headers, ",");

        std::vector<std::pair<std::string, std::string>> data;

        // Obtengo los valores y el tipo de cada dato
        for (int i = 0; i < columns.size(); i++) {
            if (columns[i][0] == ' ') {
                columns[i] = columns[i].substr(1, columns[i].size() - 1);
            }
            if (columns[i][columns[i].length() - 1] == ' ') {
                columns[i] = columns[i].substr(0, columns[i].size() - 1);
            }
            std::vector<std::string> result = TextParser::split(columns[i], " ");
            std::string value, type;
            value = result[0];
            type = result[1];
            data.push_back({value, type});
        }

        if (type == "table") {
            db.add_table(name, data);
        }
        if (type == "index") {
            std::cout << "creating index " << name << std::endl;
            return;
        }
    }

    if (command == commands::LIST) {
        db.list_tables();
    }

    if (command == commands::INSERT) {
        std::string table_name = tokens[2];
        std::vector<std::string> columns = TextParser::tokenize(TextParser::erase_parenthesis(input), ',');

        std::vector<std::string> values;
        bool is_values = false;
        for (std::string &token : tokens) {
            if (is_values) {
                std::string new_token = TextParser::clean(token);
                std::cout << new_token << std::endl;
                values = TextParser::split(new_token, ",");
                db.insert(table_name, columns, values);
                break;
            }
            if (token == "values") {
                is_values = true;
            }
        }
    }

    if (command == commands::SELECT) {
        std::vector<std::string> cols = TextParser::split(tokens[1], ",");
        std::string table_name = tokens[3];
        std::cout << red("Selecting ") << cols[0] << " from " << table_name << std::endl;
        std::vector<Register> result = db.select(table_name, cols);
        for (Register reg : result) {
            reg.print();
        }
    }
}

int main() {
    Database db = Database(1);
    std::cout << "Database initialized\n";

    bool running = true;
    while (running) {
        std::string command;
        std::cout << RED << "\n> " << RESET;
        std::getline(std::cin, command);
        if (command == commands::EXIT) {
            running = false;
        }
        process_command(db, command);
    }
    return (0);
}
