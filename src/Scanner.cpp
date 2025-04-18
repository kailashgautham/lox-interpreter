#include <string>
#include <utility>
#include <iostream>

enum ErrorType {
    INVALID_TOKEN,
    INCOMPLETE_LITERAL
};
class Scanner {
public:
    explicit Scanner(std::string file_contents)
        : file_contents(std::move(file_contents)), line_number(1), is_parsing_error(false) { }

    [[nodiscard]] bool get_is_parsing_error() const {
        return this->is_parsing_error;
    }

    void interpret_file_contents() {
        if (!this->file_contents.empty()) {
            for (; this->char_number < file_contents.size(); this->char_number++) {
                interpret_character();
            }
        }
        if (this->is_quote_open) {
            this->print_error(ErrorType::INCOMPLETE_LITERAL);
        }
        std::cout << "EOF  null" << std::endl;
    }

private:
    std::string file_contents;
    std::string current_literal;
    int line_number;
    int char_number;
    bool is_parsing_error;
    bool is_quote_open = false;

    bool match_next_char(const char& c) {
        if (this->char_number + 1 == file_contents.size() || file_contents[this->char_number + 1] != c) {
            return false;
        }
        this->char_number++;
        return true;
    }

    void skip_to_next_line() {
        while (this->char_number < file_contents.size() && file_contents[this->char_number] != '\n') {
            this->char_number++;
        }
        if (this->char_number < file_contents.size()) {
            this->line_number++;
        }
    }

    void print_error(const ErrorType error_type) {
        switch (error_type) {
            case INVALID_TOKEN:
                fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", this->line_number, this->file_contents[this->char_number]);
                this->is_parsing_error = true;
                break;
            case INCOMPLETE_LITERAL:
                fprintf(stderr, "[line %d] Error: Unterminated string.\n", this->line_number);
                break;
        }
    }

    void interpret_character() {
        switch (this->file_contents[this->char_number]) {
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
                if (this->match_next_char('=')) {
                    std::cout << "BANG_EQUAL != null" << std::endl;
                } else {
                    std::cout << "BANG ! null" << std::endl;
                }
                break;
            case '<':
                if (this->match_next_char('=')) {
                    std::cout << "LESS_EQUAL <= null" << std::endl;
                } else {
                    std::cout << "LESS < null" << std::endl;
                }
                break;
            case '>':
                if (this->match_next_char('=')) {
                    std::cout << "GREATER_EQUAL >= null" << std::endl;
                } else {
                    std::cout << "GREATER > null" << std::endl;
                }
                break;
            case '=':
                if (this->match_next_char('=')) {
                    std::cout << "EQUAL_EQUAL == null" << std::endl;
                } else {
                    std::cout << "EQUAL = null" << std::endl;
                }
                break;
            case '/':
                if (!this->match_next_char('/')) {
                    std::cout << "SLASH / null" << std::endl;
                } else {
                    if (this->is_quote_open) {
                        this->current_literal += this->match_next_char('/');
                    } else {
                        skip_to_next_line();
                    }
                }
                break;
            case '\n':
                this->line_number++;
            case ' ':
            case '\r':
            case '\t':
                if (this->is_quote_open) {
                    this->current_literal += this->file_contents[this->char_number];
                }
                break;
            case '"':
                if (!this->is_quote_open) {
                    this->is_quote_open = true;
                } else {
                    std::cout << "STRING \"" << this->current_literal << "\" " << this->current_literal << std::endl;
                    this->is_quote_open = false;
                    this->current_literal = "";
                }
                break;
            default:
                if (this->is_quote_open) {
                    this->current_literal += this->file_contents[this->char_number];
                } else {
                    print_error(ErrorType::INVALID_TOKEN);
                }
        }
    }
};
