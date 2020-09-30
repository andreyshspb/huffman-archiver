#include "CLI.h"


bool DataCLI::operator==(const DataCLI &other) const {
    bool check1 = mode == other.mode;
    bool check2 = input == other.input;
    bool check3 = output == other.output;
    return check1 && check2 && check3;
}


DataCLI HuffmanCLI::operator()(int argc, char *argv[]) {
    clear();

    for (int i = 1; i < argc; i++) {
        parameters_.emplace_back(argv[i]);
    }
    parse();

    if (count_mode_ == 0) {
        throw ExceptionCLI("There is not a mode flag");
    }
    if (count_input_ == 0) {
        throw ExceptionCLI("There is not a flag for input file");
    }
    if (count_output_ == 0) {
        throw ExceptionCLI("There is not a flag for output file");
    }

    if (count_mode_ > 1) {
        throw ExceptionCLI("There are too much the mode flags");
    }
    if (count_input_ > 1) {
        throw ExceptionCLI("There are too much flags for input file");
    }
    if (count_output_ > 1) {
        throw ExceptionCLI("There are too much flags for output file");
    }

    return {mode_, input_, output_};
}


void HuffmanCLI::clear() {
    parameters_.clear();
    mode_ = compress;
    input_.clear();
    output_.clear();
    count_mode_ = 0;
    count_input_ = 0;
    count_output_ = 0;
    index_cur_element_ = 0;
}


void HuffmanCLI::parse() {
    std::string element = parameters_[index_cur_element_++];
    if (element == "-c") {
        count_mode_ += 1;
        mode_ = compress;
    } else if (element == "-u") {
        count_mode_ += 1;
        mode_ = extract;
    } else if (element == "-f" || element == "--file") {
        count_input_ += 1;
        if (index_cur_element_ == parameters_.size()) {
            throw ExceptionCLI("There is not a path to file after flag " + element);
        }
        input_ = parameters_[index_cur_element_++];
    } else if (element == "-o" || element == "--output") {
        count_output_ += 1;
        if (index_cur_element_ == parameters_.size()) {
            throw ExceptionCLI("There is not a path to file after flag " + element);
        }
        output_ = parameters_[index_cur_element_++];
    } else {
        throw ExceptionCLI("Correct flag expected instead -- " + element);
    }
    if (index_cur_element_ < parameters_.size()) {
        parse();
    }
}

