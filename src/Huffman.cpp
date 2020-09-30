#include "Huffman.h"


// =============================HuffmanNode=============================

HuffmanNode::HuffmanNode(char symbol, size_t frequency) {
    word_ = symbol;
    left_child_ = nullptr;
    right_child_ = nullptr;
    frequency_ = frequency;
}


HuffmanNode::HuffmanNode(HuffmanNode *first, HuffmanNode *second) {
    word_ = first->word_ + second->word_;
    left_child_ = std::unique_ptr<HuffmanNode>(first);
    right_child_ = std::unique_ptr<HuffmanNode>(second);
    frequency_ = first->frequency_ + second->frequency_;
}


std::string HuffmanNode::get_word() const {
    return word_;
}


HuffmanNode *HuffmanNode::get_left_child() const {
    return left_child_.get();
}


HuffmanNode *HuffmanNode::get_right_child() const {
    return right_child_.get();
}


size_t HuffmanNode::get_frequency() const {
    return frequency_;
}


// =============================HuffmanTree=============================


bool HuffmanTree::Comparator::operator()(const HuffmanNode *first, const HuffmanNode *second) const {
    if (first->get_frequency() < second->get_frequency()) {
        return true;
    }
    if (first->get_frequency() == second->get_frequency()) {
        return first->get_word() < second->get_word();
    }
    return false;
}


void HuffmanTree::init(const std::unordered_map<char, size_t> &table) {
    std::set<HuffmanNode *, Comparator> heap;

    HuffmanNode *node = nullptr;
    for (auto element : table) {
        node = new HuffmanNode(element.first, element.second);
        heap.insert(node);
        size_ += 1;
    }

    while (heap.size() > 1) {
        HuffmanNode *first = *heap.begin();
        heap.erase(heap.begin());
        HuffmanNode *second = *heap.begin();
        heap.erase(heap.begin());
        node = new HuffmanNode(first, second);
        heap.insert(node);
        size_ += 1;
    }

    root_ = std::unique_ptr<HuffmanNode>(node);
}


void HuffmanTree::clear() {
    root_ = nullptr;
    size_ = 0;
}


HuffmanNode *HuffmanTree::get_root() const {
    return root_.get();
}

size_t HuffmanTree::size() const {
    return size_;
}
