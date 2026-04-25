#include "huffman.h"

#include <queue>
#include <stack>

struct Compare {
    bool operator()( Node* l, Node* r) const {
        return l->get_frequency() > r->get_frequency();
    }
};
Node* Huffman::buildTree(uint64_t hist[256]) {
    std::priority_queue<Node*,std::deque<Node*>,Compare> pq;
    for (int i=0;i<ALPHABET;i++) {
        if (hist[i]) {
             Node* n;
            n=new Node((uint8_t)i,hist[i],nullptr,nullptr);
            pq.push(n);
        }
    }
    while (pq.size()>1) {
        Node* left=pq.top();
        pq.pop();
        Node* right=pq.top();
        pq.pop();
        Node* parent= join(left,right);
        pq.push(parent);
    }
    if (pq.empty()) {
        return nullptr;
    }
    return pq.top();
}
void Huffman::populate(Node* r,Code& current,Code table[ALPHABET]) {
    if (r==nullptr) {
        return;
    }
    if (r->isLeaf()) {
        table[r->get_symbol()]=current;
        return;
    }
    uint8_t bit;
    current.push(0);
    populate(r->getLeft(),current,table);
    current.pop(bit);
    current.push(1);
    populate(r->getRight(),current,table);
    current.pop(bit);
}

Node *Huffman::reconstruct(uint8_t tree_dump[], uint16_t n) {
    std::stack<Node*> st;
    for (uint16_t i=0;i<n;i++) {
        if (tree_dump[i]=='L') {
            if (i+1==n)
                return nullptr;

            uint8_t s=tree_dump[i+1];
            uint64_t f=0;
            Node* n1=new Node(s,f,nullptr,nullptr);
            i++;
            st.push(n1);
        }
        else
            if (tree_dump[i]=='I') {
                if (st.size()<2)
                    return nullptr;
                Node* right;
                Node* left;
                right=st.top();
                st.pop();
                left=st.top();
                st.pop();
                Node* parent=join(left,right);
                st.push(parent);
            }
    }
        if (st.empty())
            return nullptr;
        return st.top();


}
