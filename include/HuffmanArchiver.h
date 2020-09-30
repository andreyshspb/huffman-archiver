#pragma once


#include "Huffman.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>


struct HuffmanStatistic {
    HuffmanStatistic() = default;

    void clear();

    friend std::ostream &operator<<(std::ostream &out, const HuffmanStatistic &statistic);

    size_t input_size = 0;
    size_t output_size = 0;
    size_t additional_size = 0;
};


std::ostream &operator<<(std::ostream &out, const HuffmanStatistic &statistic);


class HuffmanArchiver {
public:
    HuffmanArchiver() = default;

    HuffmanStatistic compress(std::istream &input, std::ostream &output);
    HuffmanStatistic extract(std::istream &input, std::ostream &output);

private:
    static constexpr size_t buffer_size = 128;

    std::unordered_map<char, size_t> frequency_table_;
    HuffmanTree huffman_tree_;
    std::unordered_map<char, std::string> code_table_;
    std::unordered_map<std::string, char> decode_table_;
    HuffmanStatistic statistic_;

    void clear();

    void read_decompression_file(std::istream &input);
    void write_compression_file(std::istream &input, std::ostream &output);

    void read_compression_file(std::istream &input);
    void write_decompression_file(std::istream &input, std::ostream &output);

    void build_tree();
    void build_code_table();
    void build_decode_table();

    void fill(HuffmanNode *node, const std::string &code);
};

