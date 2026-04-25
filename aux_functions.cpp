#include "aux_functions.h"
void buildHistogram(std::ifstream& in, uint64_t hist[ALPHABET]) {
    for (int i=0; i<ALPHABET; i++) {
        hist[i] = 0;
    }
    char c;
    while (in.get(c)) {
        uint8_t symbol = static_cast<uint8_t>(c);
        hist[symbol]++;
    }
    hist[0]++;
    hist[255]++;
}
uint16_t countUniqueSymbols(uint64_t hist[256]) {
    uint16_t count=0;
    for (int i=0; i<ALPHABET; i++) {
        if (hist[i]>0) {
            count++;
        }
    }
    return count;
}

void dumpTree(Node *root, std::ofstream &out) {
    /**
    * Salvează structura arborelui în fișier (serializare) folosind parcurgerea în post-ordine.
    * Scrie 'L' urmat de simbol pentru frunze și 'I' pentru nodurile interne.
    */
    if (root==NULL) {
        return;
    }
    dumpTree(root->getLeft(), out);
    dumpTree(root->getRight(), out);
    if (root->isLeaf()) {
        out.put('L');
        out.put(static_cast<char>(root->get_symbol()));
    }
    else {
        out.put('I');
    }
}

void array_dumptree(std::ifstream &in, uint16_t tree_size, uint8_t tree_dump[]) {
    /**
    * Încarcă structura serializată a arborelui din fișier direct într-un buffer (vector).
    * Citește binar un număr de 'tree_size' octeți.
    */
    in.read(reinterpret_cast<char*>(tree_dump), tree_size);

}

uint64_t getFileSize(const std::string &Filename) {
    /**
    * Returnează dimensiunea fișierului în octeți.
    * Returnează 0 dacă fișierul nu poate fi accesat sau nu există.
    */
    std::error_code ec;
    std::uintmax_t size = std::filesystem::file_size(Filename, ec);
    if (ec) {
        return 0;
    }
    return static_cast<uint64_t>(size);
}
