#include "HuffmanArchiver.h"
#include "BitStream.h"


void HuffmanStatistic::clear() {
    input_size = 0;
    output_size = 0;
    additional_size = 0;
}


std::ostream &operator<<(std::ostream &out, const HuffmanStatistic &statistic) {
    out << statistic.input_size << '\n';
    out << statistic.output_size << '\n';
    out << statistic.additional_size;
    return out;
}


HuffmanStatistic HuffmanArchiver::compress(std::istream &input, std::ostream &output) {
    clear();
    read_decompression_file(input);
    input.clear();
    input.seekg(0);
    build_tree();
    build_code_table();
    write_compression_file(input, output);
    return statistic_;
}


HuffmanStatistic HuffmanArchiver::extract(std::istream &input, std::ostream &output) {
    clear();
    read_compression_file(input);
    build_tree();
    build_code_table();
    build_decode_table();
    write_decompression_file(input, output);
    return statistic_;
}


void HuffmanArchiver::clear() {
    frequency_table_.clear();
    huffman_tree_.clear();
    code_table_.clear();
    decode_table_.clear();
    statistic_.clear();
}


void HuffmanArchiver::read_decompression_file(std::istream &input) {
    std::string buffer;
    buffer.resize(buffer_size);
    while (!input.eof()) {
        std::fill(buffer.begin(), buffer.end(), '\0');
        input.read(buffer.data(), buffer_size * sizeof(char));
        for (auto symbol : buffer) {
            if (symbol == '\0') {
                break;
            }
            frequency_table_[symbol] += 1;
            statistic_.input_size += 1;
        }
    }
    statistic_.additional_size = frequency_table_.size() * (sizeof(char) + sizeof(size_t));
    statistic_.additional_size += sizeof(size_t);
}


void HuffmanArchiver::write_compression_file(std::istream &input, std::ostream &output) {
    size_t count_letters = frequency_table_.size();
    output.write(reinterpret_cast<char *>(&count_letters), sizeof(count_letters));
    for (auto element : frequency_table_) {
        char symbol = element.first;
        size_t frequency = element.second;
        output.write(&symbol, sizeof(symbol));
        output.write(reinterpret_cast<char *>(&frequency), sizeof(frequency));
    }

    BitOstream out(output);
    std::string buffer;
    buffer.resize(buffer_size);
    while (!input.eof()) {
        std::fill(buffer.begin(), buffer.end(), '\0');
        input.read(buffer.data(), buffer_size * sizeof(char));
        for (auto symbol : buffer) {
            if (symbol == '\0') {
                break;
            }
            for (auto bit : code_table_[symbol]) {
                out << (bit == '1');
                statistic_.output_size += 1;
            }
        }
    }
    statistic_.output_size = (statistic_.output_size + CHAR_BIT - 1) / CHAR_BIT;
}


void HuffmanArchiver::read_compression_file(std::istream &input) {
    size_t count_letters = 0;
    input.read(reinterpret_cast<char *>(&count_letters), sizeof(count_letters));
    for (size_t i = 0; i < count_letters; i++) {
        char symbol = 0;
        size_t frequency = 0;
        input.read(&symbol, sizeof(symbol));
        input.read(reinterpret_cast<char *>(&frequency), sizeof(frequency));
        frequency_table_[symbol] = frequency;
    }
    statistic_.additional_size = frequency_table_.size() * (sizeof(char) + sizeof(size_t));
    statistic_.additional_size += sizeof(size_t);
}


void HuffmanArchiver::write_decompression_file(std::istream &input, std::ostream &output) {
    size_t count_letters = 0;
    for (const auto &element : frequency_table_) {
        count_letters += element.second;
    }

    BitIstream in(input);
    std::vector<char> type_bit = {'0', '1'};
    std::string buffer;
    while (statistic_.output_size < count_letters) {
        bool bit = false;
        in >> bit;
        buffer += type_bit[bit];
        if (decode_table_[buffer] != '\0') {
            output.write(&decode_table_[buffer], sizeof(decode_table_[buffer]));
            buffer.clear();
            statistic_.output_size += 1;
        }
        statistic_.input_size += 1;
    }
    statistic_.input_size = (statistic_.input_size + CHAR_BIT - 1) / CHAR_BIT;
}


void HuffmanArchiver::build_tree() {
    huffman_tree_.init(frequency_table_);
}


void HuffmanArchiver::build_code_table() {
    std::string start_code;
    if (huffman_tree_.size() == 1) {
        start_code = "0";
    }
    HuffmanNode *root = huffman_tree_.get_root();
    fill(root, start_code);
}


void HuffmanArchiver::build_decode_table() {
    for (const auto &element : code_table_) {
        decode_table_[element.second] = element.first;
    }
}


void HuffmanArchiver::fill(HuffmanNode *node, const std::string &code) {
    if (node == nullptr) {
        return;
    }
    if (node->get_left_child() == nullptr || node->get_right_child() == nullptr) {
        code_table_[node->get_word().front()] = code;
        return;
    }
    fill(node->get_left_child(), code + '0');
    fill(node->get_right_child(), code + '1');
}

