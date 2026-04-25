#pragma once
#include "defines.h"
class Node {
private:
    Node* left;
    Node* right;
    uint8_t symbol;
    uint64_t frequency;
public:
    Node(uint8_t s,uint64_t f,Node* left,Node* right);
    bool isLeaf();
    uint8_t get_symbol();
    uint64_t get_frequency();
    Node* getLeft();
    Node* getRight();
    friend Node* join(Node* l,Node* r);

};