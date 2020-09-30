#pragma once


#include <iostream>
#include <vector>
#include <climits>


class BitOstream {
public:
    explicit BitOstream(std::ostream &out);
    ~BitOstream();

    BitOstream &operator<<(bool bit);
    BitOstream &operator<<(const std::vector<bool> &data);
    void flush();

private:
    size_t index_cur_bit_ = 0;
    uint8_t cur_byte_ = 0;
    std::ostream &out_;

};


class BitIstream {
public:
    explicit BitIstream(std::istream &in);

    BitIstream &operator>>(bool &bit);
    void operator>>(std::vector<bool> &data);

private:
    size_t index_cur_bit_ = 0;
    uint8_t cur_byte_ = 0;
    std::istream &in_;

    void update();

};
