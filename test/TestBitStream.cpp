#include "doctest.h"
#include "BitStream.h"

#include <sstream>


TEST_CASE("BitOstream: Empty data") {
    std::ostringstream out;
    std::vector<bool> data;

    BitOstream stream(out);
    stream << data;
    stream.flush();

    CHECK(out.str().empty());
}


TEST_CASE("BitOstream: Small data") {
    std::ostringstream out1;
    std::ostringstream out2;
    std::ostringstream out3;
    std::vector<bool> data1{true};
    std::vector<bool> data2{true, false, false, true, true};
    std::vector<bool> data3{false, false, false, false, true, true, true, true};

    BitOstream stream1(out1);
    BitOstream stream2(out2);
    BitOstream stream3(out3);
    stream1 << data1;
    stream2 << data2;
    stream3 << data3;
    stream1.flush();
    stream2.flush();
    stream3.flush();

    CHECK(out1.str()[0] == static_cast<char>(1));
    CHECK(out2.str()[0] == static_cast<char>(1 + 8 + 16));
    CHECK(out3.str()[0] == static_cast<char>(16 + 32 + 64 + 128));

    CHECK(out1.str().size() == 1);
    CHECK(out2.str().size() == 1);
    CHECK(out3.str().size() == 1);
}


TEST_CASE("BitOstream: General data") {
    std::ostringstream out;
    std::vector<bool> data{true, false, true, true, false, false, true, false,
                           true, true, true, false, false, false, false, true,
                           false, false, true, false, false, false, true, false,
                           false, false, true, false};

    BitOstream stream(out);
    stream << data;
    stream.flush();

    CHECK(out.str()[0] == static_cast<char>(1 + 4 + 8 + 64));
    CHECK(out.str()[1] == static_cast<char>(1 + 2 + 4 + 128));
    CHECK(out.str()[2] == static_cast<char>(4 + 64));
    CHECK(out.str()[3] == static_cast<char>(4));

    CHECK(out.str().size() == 4);
}


TEST_CASE("BitIstream: Empty data") {
    std::stringstream stream;
    std::vector<bool> data;

    std::vector<bool> result;
    BitOstream ostream(stream);
    ostream << data;
    BitIstream istream(stream);
    istream >> result;

    CHECK(result == data);
}


TEST_CASE("BitIstream: Small data") {
    std::stringstream stream1;
    std::stringstream stream2;
    std::stringstream stream3;
    std::vector<bool> data1{true};
    std::vector<bool> data2{true, false, false, true, true};
    std::vector<bool> data3{false, false, false, false, true, true, true, true};

    std::vector<bool> result1;
    std::vector<bool> result2;
    std::vector<bool> result3;
    BitOstream ostream1(stream1);
    BitOstream ostream2(stream2);
    BitOstream ostream3(stream3);
    ostream1 << data1;
    ostream2 << data2;
    ostream3 << data3;
    ostream1.flush();
    ostream2.flush();
    ostream3.flush();
    BitIstream istream1(stream1);
    BitIstream istream2(stream2);
    BitIstream istream3(stream3);
    istream1 >> result1;
    istream2 >> result2;
    istream3 >> result3;

    while (data1.size() % CHAR_BIT != 0) {
        data1.push_back(false);
    }
    CHECK(result1 == data1);
    while (data2.size() % CHAR_BIT != 0) {
        data2.push_back(false);
    }
    CHECK(result2 == data2);
    while (data3.size() % CHAR_BIT != 0) {
        data3.push_back(false);
    }
    CHECK(result3 == data3);
}


TEST_CASE("BitIstream: General test") {
    std::stringstream stream;
    std::vector<bool> data{true, false, true, true, false, false, true, false,
                           true, true, true, false, false, false, false, true,
                           false, false, true, false, false, false, true, false,
                           false, false, true, false};

    std::vector<bool> result;
    BitOstream ostream(stream);
    ostream << data;
    ostream.flush();
    BitIstream istream(stream);
    istream >> result;

    while (data.size() % CHAR_BIT != 0) {
        data.push_back(false);
    }
    CHECK(result == data);
}



