#include "Huffman_decoding.h"
#include <fstream>
#include <cstdint>
#include <iostream>
#include "ReadBit.h"

void Huffman_decoding(const std::string &inFile, std::ostream &out) {
    std::ifstream in(inFile, std::ios::binary);
    if (!in) {
        std::cerr<<"Error opening file"<<std::endl;
        return;
    }

    Header header;
    in.read(reinterpret_cast<char*>(&header), sizeof(Header));
    if (!in) {
        std::cerr<<"Error reading file header"<<std::endl;
        return;
    }
    if (header.signature != MAGIC) {
        std::cerr<<"Invalid file"<<std::endl;
        return;
    }
    uint16_t ts;
    ts=header.tree_size;
    uint8_t tree_dump[ts];
    array_dumptree(in,ts,tree_dump);
    if (!in) {
        std::cerr<<"Error reading tree dump"<<std::endl;
        return;
    }
    Node* root=Huffman::reconstruct(tree_dump,ts);
    if (root==nullptr) {
        std::cerr<<"Error reading tree dump"<<std::endl;
        return;
    }
    Read_Bit reader(in);
    Node* current=root;
    uint64_t decoded_symbols=0;
    uint8_t bit;
    while (decoded_symbols < header.file_size && reader.read(bit)) {
        if (bit == 0) {
            current=current->getLeft();
        }
        else
            current=current->getRight();
        if (current->isLeaf()) {
            out.put(static_cast<char>(current->get_symbol()));
            decoded_symbols++;
            current=root;
        }
    }
    in.close();

}
