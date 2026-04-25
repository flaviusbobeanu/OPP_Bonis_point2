#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>

#include "Huffman_encoding.h"
#include "Huffman_decoding.h"
#include "aux_functions.h"
#include "defines.h"

void printHelp() {
    std::cout<<"Usage ./: "<<std::endl;
    std::cout<<"huffman encode [-h] [-i infile] [-o outfile] [-s]" << std::endl;
    std::cout<<" huffman decode [-h] [-i infile] [-o outfile] [-s]"<<std::endl;
}
void printEncodeHelp() {
    std::cout<<"Usage ./: "<<std::endl;
    std::cout<<"huffman encode [-h] [-i infile] [-o outfile] [-s]" << std::endl;

}
void printDecodeHelp() {
    std::cout<<"Usage ./: "<<std::endl;
    std::cout<<"huffman decode [-h] [-i infile] [-o outfile] [-s]" << std::endl;

}
///copy the content of stdin in a temporary file
void copyStdinToTempFile(const std::string& tempFileName) {
    std::ofstream temp(tempFileName,std::ios::binary);
    if (!temp) {
        std::cerr<<"Error creating temporary input file"<<std::endl;
    }
   char c;
    while (std::cin.get(c)) {
        temp.put(c);
    }
    temp.close();
}
int main(int argc, char* argv[]) {

    // 🔥 HELP GLOBAL (merge oricând)
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-h") {
            printHelp();
            return 0;
        }
    }

    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string mode = argv[1];
    if (mode != "encode" && mode != "decode") {
        std::cerr << "Invalid mode\n";
        printHelp();
        return 1;
    }

    std::string infile;
    std::string outfile;
    bool show_statistics = false;

    // 🔹 PARSARE ARGUMENTE
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-i") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value after -i\n";
                return 1;
            }
            infile = argv[++i];
        }
        else if (arg == "-o") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value after -o\n";
                return 1;
            }
            outfile = argv[++i];
        }
        else if (arg == "-s") {
            show_statistics = true;
        }
        else {
            std::cerr << "Unknown argument: " << arg << "\n";
            return 1;
        }
    }

    // 🔥 EXECUȚIE

    if (mode == "encode") {
        if (outfile.empty()) {
            std::cerr << "No output file specified\n";
            return 1;
        }

        std::string input = infile;
        const std::string temp = "temp.bin";
        bool temp_used = false;

        if (input.empty()) {
            copyStdinToTempFile(temp);
            input = temp;
            temp_used = true;
        }

        uint64_t original = getFileSize(input);
        Huffman_encoding(input, outfile);
        uint64_t compressed = getFileSize(outfile);

        if (show_statistics) {
            double saving = (original != 0)
                ? 100.0 * (1.0 - (double)compressed / original)
                : 0.0;

            std::cout << "Original:   " << original << " bytes\n";
            std::cout << "Compressed: " << compressed << " bytes\n";
            std::cout << "Saving:     " << saving << "%\n";
        }

        if (temp_used) {
            std::remove(temp.c_str());
        }
    }

    else { // decode
        if (infile.empty()) {
            std::cerr << "No input file specified\n";
            return 1;
        }

        if (outfile.empty()) {
            Huffman_decoding(infile, std::cout);
        } else {
            std::ofstream out(outfile, std::ios::binary);
            if (!out) {
                std::cerr << "Error opening output file\n";
                return 1;
            }
            Huffman_decoding(infile, out);
        }
    }

    return 0;
}