#include "writebit.h"
/// out -output file, opened as output stream
Write_Bit::Write_Bit(std::ofstream &o): out{o}, buffer{0}, bitIndex{0} {

}

void Write_Bit::write(uint8_t bit) {
    if (bit==1) {
        buffer |= (1<<bitIndex);
    }
    bitIndex++;
    if (bitIndex==8) {
        out.put(static_cast<char>(buffer));///write the byte into the file
        buffer = 0;
        bitIndex = 0;
    }
}
void Write_Bit::flush() {
    if (bitIndex > 0) {
        out.put(static_cast<char>(buffer));
        buffer = 0;
        bitIndex = 0;
    }
}