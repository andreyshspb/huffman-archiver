#pragma once


#include <string>
#include <vector>


enum ProgramMode {
    compress,
    extract
};


struct DataCLI {
    ProgramMode mode;
    std::string input;
    std::string output;
    bool operator==(const DataCLI &other) const;
};


class ExceptionCLI : std::exception {
public:
    explicit ExceptionCLI(std::string message) : message_(std::move(message)) {}
    const char* what() const noexcept override { return message_.c_str(); }
private:
    std::string message_;
};


class HuffmanCLI {
public:
    HuffmanCLI() = default;

    DataCLI operator()(int argc, char *argv[]);

private:
    std::vector<std::string> parameters_;
    ProgramMode mode_ = compress;
    std::string input_;
    std::string output_;

    size_t count_mode_ = 0;
    size_t count_input_ = 0;
    size_t count_output_ = 0;

    size_t index_cur_element_ = 0;

    void clear();

    void parse();

};
