#include <iostream>
#include <string>

class Parser {
public:
    explicit Parser(std::string file_contents)
    : file_contents(std::move(file_contents)), line_number(1), char_number(0), is_parsing_error(false) {
    }

    [[nodiscard]] bool get_is_parsing_error() const {
        return this->is_parsing_error;
    }

    void interpret_file_contents() {
        if (!this->file_contents.empty()) {
            for (; this->char_number < file_contents.size(); this->char_number++) {
                process_expr();
            }
        }
    }

private:
    std::string file_contents;
    int line_number;
    int char_number;
    bool is_parsing_error;

    void process_expr() {
        if (std::isdigit(this->file_contents[this->char_number])) {
            process_number_literal();
        }

        else if (std::isalpha(this->file_contents[this->char_number])) {
            process_keyword();
        }
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
        if (!decimal_found) {
            number_literal += ".0";
        }
        std::cout << number_literal << std::endl;
    }

    void process_keyword() {
        std::string expr;
        while (this->char_number < file_contents.size()) {
            if (std::isspace(this->file_contents[this->char_number])) {
                break;
            }
            expr += this->file_contents[this->char_number];
            this->char_number++;
        }
        std::cout << expr << std::endl;
    }
};
