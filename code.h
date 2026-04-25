#pragma once
#include "defines.h"
class Code {
private:
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
public:
    Code();
    bool isEmpty() const;
    bool isFull() const;
    uint32_t size() const;
    bool push(uint8_t b);
    bool pop(uint8_t& b);
    uint8_t getBit(uint32_t poz) const;
};