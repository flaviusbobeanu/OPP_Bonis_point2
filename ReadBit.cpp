#include "ReadBit.h"
#include <cstdint>

Read_Bit::Read_Bit(std::ifstream &i): in{i}, buffer{0}, bitIndex {8} {}
bool Read_Bit::read(uint8_t& bit) {
    if (bitIndex == 8) {
        char c;
        if (!in.get(c))
            return false;
        buffer = static_cast<uint8_t>(c);
        bitIndex = 0;

    }
    bit=(buffer >> bitIndex)&1;
    bitIndex++;
    return true;
}