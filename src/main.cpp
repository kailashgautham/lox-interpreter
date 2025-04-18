#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string read_file_contents(const std::string& filename);

bool interpret_character(int line_number, const char& c);

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        std::string file_contents = read_file_contents(argv[2]);
        bool parsing_error = false;
        if (!file_contents.empty()) {
            for (const char& c : file_contents) {
                if (!interpret_character(1, c)) {
                    parsing_error = true;
                }
            }
        }
        std::cout << "EOF  null" << std::endl; // Placeholder, remove this line when implementing the scanner
        if (parsing_error) {
            return 65;
        }
        return 0;
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

bool interpret_character(int line_number, const char& c) {
    switch (c) {
        case '(':
            std::cout << "LEFT_PAREN ( null" << std::endl;
            break;
        case ')':
            std::cout << "RIGHT_PAREN ) null" << std::endl;
            break;
        case '{':
            std::cout << "LEFT_BRACE { null" << std::endl;
            break;
        case '}':
            std::cout << "RIGHT_BRACE } null" << std::endl;
            break;
        case '*':
            std::cout << "STAR * null" << std::endl;
            break;
        case '.':
            std::cout << "DOT . null" << std::endl;
            break;
        case ',':
            std::cout << "COMMA , null" << std::endl;
            break;
        case ';':
            std::cout << "SEMICOLON ; null" << std::endl;
            break;
        case '+':
            std::cout << "PLUS + null" << std::endl;
            break;
        case '-':
            std::cout << "MINUS - null" << std::endl;
            break;
        default:
            fprintf(stderr, "[Line %d] Error: Unexpected character: %c\n", line_number, c);
            break;
    }
}
