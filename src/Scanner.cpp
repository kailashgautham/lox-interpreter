#include <string>
#include <utility>
#include <iostream>

class Scanner {
public:
    explicit Scanner(std::string file_contents)
        : file_contents(std::move(file_contents)), line_number(1), is_parsing_error(false) { }

    [[nodiscard]] bool get_is_parsing_error() const {
        return this->is_parsing_error;
    }

    void interpret_file_contents() {
        if (!this->file_contents.empty()) {
            for (int i = 0; i < file_contents.size(); i++) {
                interpret_character(i);
            }
        }
        std::cout << "EOF  null" << std::endl;
    }

private:
    std::string file_contents;
    int line_number;
    bool is_parsing_error;

    bool match_next_char(int& i, const char& c) const {
        if (i + 1 == file_contents.size() || file_contents[i + 1] != c) {
            return false;
        }
        i++;
        return true;
    }

    void skip_to_next_line(int& i) const {
        while (i < file_contents.size() && file_contents[i] != '\n') {
            i++;
        }
    }

    void interpret_character(int& i) {
        switch (this->file_contents[i]) {
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
            case '!':
                if (this->match_next_char(i, '=')) {
                    std::cout << "BANG_EQUAL != null" << std::endl;
                } else {
                    std::cout << "BANG ! null" << std::endl;
                }
                break;
            case '<':
                if (this->match_next_char(i, '=')) {
                    std::cout << "LESS_EQUAL <= null" << std::endl;
                } else {
                    std::cout << "LESS < null" << std::endl;
                }
                break;
            case '>':
                if (this->match_next_char(i, '=')) {
                    std::cout << "GREATER_EQUAL >= null" << std::endl;
                } else {
                    std::cout << "GREATER > null" << std::endl;
                }
                break;
            case '=':
                if (this->match_next_char(i, '=')) {
                    std::cout << "EQUAL_EQUAL == null" << std::endl;
                } else {
                    std::cout << "EQUAL = null" << std::endl;
                }
                break;
            case '/':
                if (!this->match_next_char(i, '/')) {
                    std::cout << "SLASH / null" << std::endl;
                } else {
                    skip_to_next_line(i);
                }
                break;
            case '\n':
                this->line_number++;
            case ' ':
            case '\r':
            case '\t':
                break;
            default:
                fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", this->line_number, this->file_contents[i]);
                this->is_parsing_error = true;
        }
    }
};
