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
