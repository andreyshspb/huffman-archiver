#include "BitStream.h"


BitOstream::BitOstream(std::ostream &out) : out_(out) {}


BitOstream::~BitOstream() {
    flush();
}


BitOstream &BitOstream::operator<<(bool bit) {
    auto value = static_cast<uint8_t>(bit);
    cur_byte_ |= static_cast<uint8_t>(value << index_cur_bit_++);
    if (index_cur_bit_ == CHAR_BIT) {
        flush();
    }
    return *this;
}


BitOstream &BitOstream::operator<<(const std::vector<bool> &data) {
    for (auto element : data) {
        *this << element;
    }
    return *this;
}


void BitOstream::flush() {
    if (index_cur_bit_ == 0) {
        return;
    }
    out_.write(reinterpret_cast<char *>(&cur_byte_), sizeof(cur_byte_));
    index_cur_bit_ = 0;
    cur_byte_ = 0;
}


BitIstream::BitIstream(std::istream &in) : in_(in) {
    in_.read(reinterpret_cast<char *>(&cur_byte_), sizeof(cur_byte_));
}


BitIstream &BitIstream::operator>>(bool &bit) {
    bit = (static_cast<uint8_t >(cur_byte_ >> index_cur_bit_++) & 1u) == 1u;
    if (index_cur_bit_ == CHAR_BIT) {
        update();
    }
    return *this;

}


void BitIstream::operator>>(std::vector<bool> &data) {
    while (!in_.eof()) {
        bool bit = false;
        *this >> bit;
        data.push_back(bit);
    }
}


void BitIstream::update() {
    in_.read(reinterpret_cast<char *>(&cur_byte_), sizeof(cur_byte_));
    index_cur_bit_ = 0;
}
