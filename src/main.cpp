#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Tokenizer.cpp"
#include "Parser.cpp"

std::string read_file_contents(const std::string& filename);

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program <command> <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        const std::string file_contents = read_file_contents(argv[2]);
        auto* scanner = new Tokenizer(file_contents);
        scanner->interpret_file_contents();
        const bool is_parsing_error = scanner->get_is_parsing_error();
        delete scanner;
        if (is_parsing_error) {
            return 65;
        }
    } else if (command == "parse") {
        const std::string file_contents = read_file_contents(argv[2]);
        auto* parser = new Parser(file_contents);
        parser->interpret_file_contents();
        delete parser;
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }
    return 0;
}

std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
