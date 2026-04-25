#include "node.h"
Node::Node(uint8_t s,uint64_t f,Node* left,Node* right) {
    this->symbol=s;
    this->frequency=f;
    this->left=left;
    this->right=right;
}
bool Node::isLeaf() {
    return this->left==nullptr && this->right==nullptr;
}
uint8_t Node::get_symbol() {
    return this->symbol;
}
uint64_t Node::get_frequency() {
    return this->frequency;
}
Node* join(Node* l,Node* r) {
    if(l==nullptr || r==nullptr)
        return nullptr;
    return new Node('$',l->frequency+r->frequency,l,r);
}
Node* Node::getLeft() {
    return this->left;
}
Node* Node::getRight() {
    return this->right;
}