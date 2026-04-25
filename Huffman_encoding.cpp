#include "Huffman_encoding.h"

#include <iostream>

void Huffman_encoding(const std::string &inFile, const std::string &outFile) {
       std::ifstream in(inFile, std::ios::binary);
        if (!in) {
            std::cerr<<"Error opening file"<<std::endl;
            return;
        }
        std::ofstream out(outFile, std::ios::binary);
    if (!out) {
        std::cerr<<"Error opening file"<<std::endl;
        return;
    }
       uint64_t histogram[ALPHABET];
       buildHistogram(in, histogram);
       Node* root=Huffman::buildTree(histogram);
        if (root==nullptr) {
            std::cerr<<"Error in buildTree()"<<std::endl;
            return;
        }
       Code table[ALPHABET];
       Code current;
       Huffman::populate(root,current,table);
        uint16_t unique_symbols=countUniqueSymbols(histogram);
        Header header;
        header.signature=MAGIC;
        header.tree_size =(3*unique_symbols)-1;
        header.file_size=getFileSize(inFile);
        out.write(reinterpret_cast<char*>(&header),sizeof(header));
        dumpTree(root,out);
        ///go back at the beginning of the file
        in.clear();
        in.seekg(0);
        Write_Bit writer(out);
        char c;
        while (in.get(c)) {
            uint8_t symbol=static_cast<uint8_t>(c);
            Code code=table[symbol];
            for (uint32_t i=0;i< code.size();i++) {
                writer.write(code.getBit(i));
            }
        }
        writer.flush();

        in.close();
        out.close();
}
