#pragma once
#include <fstream>
#include <cstdint>
class Read_Bit {
public:
    Read_Bit(std::ifstream& i);
    bool read(uint8_t& bit);
private:
    std::ifstream& in;
    uint8_t buffer;
    uint8_t bitIndex;
};