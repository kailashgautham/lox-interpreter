#include <iostream>
#include <queue>
#include <stack>
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
    std::stack<std::string> groups;
    void process_expr() {
        if (std::isdigit(this->file_contents[this->char_number])) {
            const std::string number_literal = process_number_literal();
            if (!groups.empty()) {
                groups.top() += " " + number_literal;
            } else {
                std::cout << number_literal << std::endl;
            }
        } else if (std::isalpha(this->file_contents[this->char_number])) {
            const std::string expr = process_word(true);
            if (!groups.empty()) {
                groups.top() += " " + expr;
            } else {
                std::cout << expr << std::endl;
            }
        } else if (this->file_contents[this->char_number] == '"') {
            this->char_number++;
            const std::string expr = process_string_literal();
            if (!groups.empty()) {
                groups.top() += " " + expr;
            } else {
                std::cout << expr << std::endl;
            }
        } else if (this->file_contents[this->char_number] == '(') {
            std::string new_group = "(group";
            this->groups.push(std::move(new_group));
        }
        if (this->file_contents[this->char_number] == ')') {
            groups.top() += ')';
            const std::string top_group = groups.top();
            groups.pop();
            if (!groups.empty()) {
                groups.top() += " " + top_group;
            } else {
                std::cout << top_group << std::endl;
            }
        }
    }

    std::string process_string_literal() {
        std::string expr;
        while (this->char_number < file_contents.size() && this->file_contents[this->char_number] != '"') {
            expr += this->process_word(false);
            if (this->char_number < file_contents.size() && this->file_contents[this->char_number] != '"') {
                expr += this->file_contents[this->char_number];
                this->char_number++;
            }
        }
        return expr;
    }


    std::string process_number_literal() {
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
        return number_literal;
    }

    std::string process_word(const bool is_keyword) {
        std::string expr;
        while (this->char_number < file_contents.size()) {
            if (
                (is_keyword && !std::isalpha(this->file_contents[this->char_number])) ||
                (!is_keyword && this->file_contents[this->char_number] == '"')
            ) {
                break;
            }
            expr += this->file_contents[this->char_number];
            this->char_number++;
        }
        return expr;
    }
};
