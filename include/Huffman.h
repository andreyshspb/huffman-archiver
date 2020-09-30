#pragma once


#include <string>
#include <unordered_map>
#include <set>
#include <memory>


class HuffmanNode {
public:
    HuffmanNode() = delete;
    HuffmanNode(char symbol, size_t frequency);
    HuffmanNode(HuffmanNode *first, HuffmanNode *second);

    std::string get_word() const;
    HuffmanNode *get_left_child() const;
    HuffmanNode *get_right_child() const;
    size_t get_frequency() const;

private:
    std::string word_;
    std::unique_ptr<HuffmanNode> left_child_;
    std::unique_ptr<HuffmanNode> right_child_;
    size_t frequency_;

};


class HuffmanTree {
public:

    struct Comparator {
        bool operator()(const HuffmanNode *first, const HuffmanNode *second) const;
    };

    HuffmanTree() = default;

    void init(const std::unordered_map<char, size_t> &table);
    void clear();

    HuffmanNode *get_root() const;
    size_t size() const;

private:
    std::unique_ptr<HuffmanNode> root_ = nullptr;
    size_t size_ = 0;

};
