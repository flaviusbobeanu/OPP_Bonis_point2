#pragma once
#include "defines.h"
#include "code.h"
#include "node.h"
class Huffman{
public:
    static Node* buildTree(uint64_t hist[ALPHABET]);
    static void populate(Node* r,Code& current,Code table[ALPHABET]);
    static Node* reconstruct(uint8_t tree_dump[],uint16_t n);
};
