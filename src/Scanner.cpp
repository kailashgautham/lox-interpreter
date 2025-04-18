#include <string>
#include <utility>
#include <iostream>
#include <iomanip>

enum ErrorType {
    INVALID_TOKEN,
    INCOMPLETE_LITERAL
};

class Scanner {
public:
    explicit Scanner(std::string file_contents)
        : file_contents(std::move(file_contents)), line_number(1), is_parsing_error(false) {
    }

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

    bool match_next_char(const char &c) {
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
                fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", this->line_number,
                        this->file_contents[this->char_number]);
                break;
            case INCOMPLETE_LITERAL:
                fprintf(stderr, "[line %d] Error: Unterminated string.\n", this->line_number);
                break;
        }
        this->is_parsing_error = true;
    }

    static void print_formatted_number(std::string &number_literal, bool decimal_found) {
        const long double num = std::stold(number_literal);

        std::ostringstream oss1;
        oss1 << std::fixed << std::setprecision(4) << num;
        std::string first = oss1.str();
        first = first.substr(0, std::min(number_literal.size(), first.size()));
        std::string second = oss1.str();
        second.erase(second.find_last_not_of('0') + 1);
        if (second.back() == '.') {
            decimal_found = false;
            second.pop_back();
        }
        if (!decimal_found) {
            second += ".0";
        }

        std::cout << "NUMBER " << first << " " << second << std::endl;
    }

    void process_number_literal() {
        std::string number_literal;
        bool decimal_found = false;
        int decimal_places = 0;
        while (this->char_number < file_contents.size()) {
            if (std::isdigit(this->file_contents[this->char_number]) ||
                (this->file_contents[this->char_number] == '.' && !decimal_found)) {
                if (this->file_contents[this->char_number] == '.') {
                    if (this->char_number < file_contents.size() - 1 && std::isdigit(
                            this->file_contents[this->char_number + 1])) {
                        decimal_found = true;
                    } else {
                        break;
                    }
                }
                if (decimal_found && std::isdigit(this->file_contents[this->char_number])) {
                    decimal_places++;
                }
                number_literal += this->file_contents[this->char_number];
                this->char_number++;
            } else {
                break;
            }
        }
        print_formatted_number(number_literal, decimal_found);
    }

    void process_identifier() {
        std::string identifier;
        while (this->char_number < file_contents.size()) {
            if (std::isalnum(this->file_contents[this->char_number]) || this->file_contents[this->char_number] == '_') {
                identifier += this->file_contents[this->char_number];
                this->char_number++;
            } else {
                break;
            }
        }
        std::cout << "IDENTIFIER " << identifier << " null" << std::endl;
    }

    void interpret_character() {
        if (this->is_quote_open && this->file_contents[this->char_number] != '"') {
            this->current_literal += this->file_contents[this->char_number];
            return;
        }

        if (std::isdigit(this->file_contents[this->char_number])) {
            process_number_literal();
            if (this->char_number == file_contents.size()) {
                return;
            }
        }

        if (std::isalpha(this->file_contents[this->char_number]) || this->file_contents[this->char_number] == '_') {
            process_identifier();
            if (this->char_number == file_contents.size()) {
                return;
            }
        }

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
                    skip_to_next_line();
                }
                break;
            case '\n':
                this->line_number++;
            case ' ':
            case '\r':
            case '\t':
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
                print_error(ErrorType::INVALID_TOKEN);
                break;
        }
    }
};
