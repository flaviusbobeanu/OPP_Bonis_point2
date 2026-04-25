#include "code.h"
Code::Code(): top{0} {
    for (int i=0; i<MAX_CODE_SIZE; i++)
        bits[i] = 0;
}
bool Code::isEmpty() const{
    return top==0;
}
bool Code::isFull() const {
    return top==MAX_CODE_SIZE*8;
}
uint32_t Code::size() const {
    return top;
}
bool Code::push(uint8_t b) {
    if (top==MAX_CODE_SIZE*8)
        return false;
    uint32_t byteIndex = top/8;
    uint32_t bitIndex = top%8;
    if (b==1)
        bits[byteIndex] |= (1<<bitIndex);
    else
        bits[byteIndex] &= ~(1<<bitIndex);
    top++;
    return true;
}
bool Code::pop(uint8_t& b) {
    if (top==0)
        return false;
    top--;
    uint32_t byteIndex = top/8;
    uint32_t bitIndex = top%8;
    b= (bits[byteIndex]>>bitIndex)&1;
    bits[byteIndex] &= ~(1<<bitIndex);
    return true;
}

uint8_t Code::getBit(uint32_t poz) const {
    uint32_t byteIndex = poz/8;
    uint32_t bitIndex = poz%8;
    return (bits[byteIndex]>>bitIndex)&1;
}
