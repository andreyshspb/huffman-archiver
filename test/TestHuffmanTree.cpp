#include "doctest.h"
#include "Huffman.h"


#include <vector>


TEST_CASE ("Frequency table is empty") {
    std::unordered_map<char, size_t> table;

    HuffmanTree tree;
    tree.init(table);
    CHECK(tree.get_root() == nullptr);
    CHECK(tree.size() == 0);
}


TEST_CASE ("Frequency table has only one element") {
    std::unordered_map<char, size_t> table;
    table['a'] = 10;

    HuffmanTree tree;
    tree.init(table);
    CHECK(tree.size() == 1);

    HuffmanNode *root = tree.get_root();
    CHECK(root->get_word() == "a");
    CHECK(root->get_left_child() == nullptr);
    CHECK(root->get_right_child() == nullptr);
    CHECK(root->get_frequency() == 10);
}


void dfs1(HuffmanNode *node, std::vector<std::string> &path) {
    if (node == nullptr) {
        return;
    }
    dfs1(node->get_left_child(), path);
    path.push_back(node->get_word());
    dfs1(node->get_right_child(), path);
}

void dfs2(HuffmanNode *node, std::vector<size_t> &path) {
    if (node == nullptr) {
        return;
    }
    dfs2(node->get_left_child(), path);
    path.push_back(node->get_frequency());
    dfs2(node->get_right_child(), path);
}

TEST_CASE ("General case") {
    std::unordered_map<char, size_t> table;
    table['a'] = 22;
    table['b'] = 12;
    table['c'] = 2;
    table['d'] = 25;
    table['e'] = 61;
    table['f'] = 56;
    table['g'] = 29;
    table['h'] = 32;
    table['.'] = 20;
    table['x'] = 33;
    table['y'] = 67;
    table['z'] = 9;

    HuffmanTree tree;
    tree.init(table);
    CHECK(tree.size() == 23);

    std::vector<std::string> path1;
    dfs1(tree.get_root(), path1);
    std::vector<std::string> correct1{
        "y", "yx.a", "x", "x.a", ".",
        ".a", "a", "yx.aczbdfegh", "c",
        "cz", "z", "czb", "b", "czbd",
        "d", "czbdf", "f", "czbdfegh",
        "e", "egh", "g", "gh", "h"
    };
    CHECK(path1 == correct1);

    std::vector<size_t> path2;
    dfs2(tree.get_root(), path2);
    std::vector<size_t> correct2{
        67, 142, 33, 75, 20, 42, 22,
        368, 2, 11, 9, 23, 12, 48, 25,
        104, 56, 226, 61, 122, 29, 61, 32
    };
    CHECK(path2 == correct2);
}

