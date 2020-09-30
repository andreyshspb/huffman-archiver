#include "doctest.h"
#include "HuffmanArchiver.h"
#include "BitStream.h"

#include <sstream>


TEST_CASE("Compress: Empty file") {
    std::stringstream input;
    std::stringstream output;

    HuffmanArchiver archiver;
    HuffmanStatistic statistic = archiver.compress(input, output);

    size_t size_table = 1;
    output.read(reinterpret_cast<char *>(&size_table), sizeof(size_table));
    CHECK(size_table == 0);

    CHECK(output.str().size() == 8);

    CHECK(statistic.input_size == 0);
    CHECK(statistic.output_size == 0);
    CHECK(statistic.additional_size == 8);
}


TEST_CASE("Compress: Small data") {
    std::stringstream input("aa");
    std::stringstream output;

    HuffmanArchiver archiver;
    HuffmanStatistic statistic = archiver.compress(input, output);

    size_t size_table = 0;
    char symbol = 0;
    size_t frequency = 0;
    output.read(reinterpret_cast<char *>(&size_table), sizeof(size_table));
    output.read(&symbol, sizeof(symbol));
    output.read(reinterpret_cast<char *>(&frequency), sizeof(frequency));
    CHECK(size_table == 1);
    CHECK(symbol == 'a');
    CHECK(frequency == 2);

    std::vector<bool> data;
    BitIstream stream(output);
    stream >> data;
    std::vector<bool> correct{
        false,
        false,
        false, false, false, false, false, false
    };
    CHECK(data == correct);

    CHECK(output.str().size() == 18);

    CHECK(statistic.input_size == 2);
    CHECK(statistic.output_size == 1);
    CHECK(statistic.additional_size == 17);
}


TEST_CASE("Compress: General data") {
    std::stringstream input("Good boy, Maxi,  good boy");
    std::stringstream output;

    HuffmanArchiver archiver;
    HuffmanStatistic statistic = archiver.compress(input, output);

    std::unordered_map<char, size_t> table;
    size_t size_table = 0;
    output.read(reinterpret_cast<char *>(&size_table), sizeof(size_table));
    for (size_t i = 0; i < size_table; i++) {
        char symbol = 0;
        size_t frequency = 0;
        output.read(&symbol, sizeof(symbol));
        output.read(reinterpret_cast<char *>(&frequency), sizeof(frequency));
        table[symbol] = frequency;
    }
    CHECK(size_table == 12);
    CHECK(table['G'] == 1);
    CHECK(table['o'] == 6);
    CHECK(table['d'] == 2);
    CHECK(table['b'] == 2);
    CHECK(table['y'] == 2);
    CHECK(table[','] == 2);
    CHECK(table['M'] == 1);
    CHECK(table['a'] == 1);
    CHECK(table['x'] == 1);
    CHECK(table['i'] == 1);
    CHECK(table['g'] == 1);
    CHECK(table[' '] == 5);

    std::vector<bool> data;
    BitIstream stream(output);
    stream >> data;
    std::vector<bool> correct{
        true, false, true, true, false,
        false, true,
        false, true,
        true, true, true, false,
        false, false,
        true, true, false, true,
        false, true,
        true, false, false,
        true, false, true, false,
        false, false,
        true, false, true, true, true,
        true, true, false, false, false,
        true, true, true, true, true,
        true, true, true, true, false,
        true, false, true, false,
        false, false,
        false, false,
        true, true, false, false, true,
        false, true,
        false, true,
        true, true, true, false,
        false, false,
        true, true, false, true,
        false, true,
        true, false, false,
        false, false, false, false, false, false
    };
    CHECK(data == correct);

    CHECK(output.str().size() == 127);

    CHECK(statistic.input_size == 25);
    CHECK(statistic.output_size == 11);
    CHECK(statistic.additional_size == 116);
}


TEST_CASE("Extract: Empty file") {
    std::stringstream input;
    std::stringstream buffer;
    std::stringstream output;

    HuffmanArchiver archiver;
    HuffmanStatistic statistic1 = archiver.compress(input, buffer);
    HuffmanStatistic statistic2 = archiver.extract(buffer, output);
    CHECK(input.str() == output.str());

    CHECK(statistic2.input_size == statistic1.output_size);
    CHECK(statistic2.output_size == statistic1.input_size);
    CHECK(statistic2.additional_size == statistic1.additional_size);
}


TEST_CASE("Extract: General data") {
    std::stringstream input("Ковёр задавал стиль всей комнате.\n");
    std::stringstream buffer;
    std::stringstream output;

    HuffmanArchiver archiver;

    HuffmanStatistic statistic1 = archiver.compress(input, buffer);
    HuffmanStatistic statistic2 = archiver.extract(buffer, output);
    CHECK(input.str() == output.str());

    CHECK(statistic2.input_size == statistic1.output_size);
    CHECK(statistic2.output_size == statistic1.input_size);
    CHECK(statistic2.additional_size == statistic1.additional_size);
}

