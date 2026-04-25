#pragma once
#include<fstream>
#include<cstdint>
class Write_Bit {
private:
    std::ofstream& out;
    uint8_t buffer;
    uint8_t bitIndex;
public:
    Write_Bit(std::ofstream& o);
    void write(uint8_t bit);
    void flush();

};